// message.c

#include <ansi.h>
#include <dbase.h>
#include <name.h>

#define MAX_STRING_SIZE                 8000
#define MAX_MSG_BUFFER                  100

nosave string *msg_buffer = ({});
nosave int written = 0;

// status of written
#define NONE                    0
#define PROMPT_WRITTEN          1
#define COMMAND_RCVD            2

// flag: enable/disable log
// When the sysytem decide to log a player's message, it
// will call the function enable_message_log() or call the
// function disable_message_log() to stop it. If the flag
// has been set, after I call the receive_message to send
// message to this object, I will call the function 
nosave string log_in = 0;

// Should I be log ?
int is_loging_now()
{
        return log_in != 0;
}

int start_log()
{
        string file;
        if (! is_root(previous_object())) return 0;

        if (log_in) return 0;

        if (! (file = EXAMINE_D->create_log_file(this_object())))
                return 0;

        log_file(file, sprintf("The system log the action of %s(%s) from %s on %s.\n\n",
                               name(1), query("id"),
			       query_ip_name(this_object()), ctime(time())));
        log_in = file;
        return 1;
}

void end_log()
{
        if (! log_in) return;
        if (! is_root(previous_object())) return;

        log_file(log_in, sprintf("The system stop log at %s.\n\n",
	         ctime(time())));
        log_in = 0;
}

void log_command(string msg)
{
	if (! log_in) return;

        log_file(log_in, HIC + ctime(time())[11..18] +
                         HIY "> " + msg + NOR "\n");
}

void log_message(string msg)
{
	if (! log_in) return;

        msg = replace_string(msg, ESC "[256D" ESC "[K", "\n");
        msg = replace_string(msg, ESC "[1A", "");
        log_file(log_in, msg);
}

// What's about flag variable: written ?
// After I written a prompt ">" on the screen, mabye the 
// user has not input command but receive message. So the
// screen may be show as "> YOU ARE RECEIVE MESSAGE"
// that's bad! On this case, I want clear the "> ", so I
// define a flag variable. After I written the prompt I will
// set it, & when the user receive in a command he will call
// the function clear written to tell me that.

string prompt()
{
        string p;
        string prompt, path;
        mixed list;

        if (arrayp(list = query_temp("tell_list")) &&
            sizeof(list) > 1)
                p = HIG "> " NOR;
        else
                p = HIY "> " NOR;

        if (! stringp(prompt = query("env/prompt")))
                return p;

        switch (prompt)
        {
        case "time":
                p = HIC + ctime(time())[11..18] + p;
                break;
        case "date":
                p = HIC + ctime(time())[0..9] + p;
                break;
        case "mud":
                p = HIC + NATURE_D->game_time() + p;
                break;
        case "hp":
                p = HIG + sprintf("%d/%d", query("jing"), query("qi")) + p;
                break;
        case "path":
                if (! wizardp(this_object()) || wiz_level(this_object()) < 3)
                        break;
		if (! stringp(path = query("cwd")))
		{
			path = "/";
			set("cwd", path);
		}
               	p = HIC + path[0..<2] + p;
                break;
        default:
                p = prompt + p;
                break;
        }

        return p;
}

void receive_message(string msgclass, string msg)
{
	string subclass, irc_channel, *chs;
	object me = this_object();

	if (!stringp(msg))
		return;
	if (!userp(me)) {
		me->relay_message(msgclass, msg);
		return;
	}

	if (sscanf(msgclass, "%s:%s", msgclass, subclass) == 2) {
		switch (msgclass) {
			case "channel":
				if (!pointerp(chs = query("channels")) || member_array(subclass, chs)==-1)
					return;
				if ( subclass=="irc" && sscanf(msg,"%s:%s",irc_channel, msg)==2 )
					if ( !(wizardp(me) && me->query("env/test")) &&
					     irc_channel!=(string)query_temp("irc/room1") &&
					     irc_channel!=(string)query_temp("irc/room2") &&
					     irc_channel!=(string)query_temp("irc/room3") &&
					     irc_channel!=(string)query_temp("irc/room4") &&
					     irc_channel!=(string)query_temp("irc/room5") &&
					     irc_channel!="irc_channel" ) 
						return;
				break;
			case "wizard":
				if (subclass != me->query("id") && subclass != wizhood(me))
					return;
			case "outdoor":
				break;
			default:
				return;
		}
	}

	if (msgclass == "outdoor" && (!environment() || !environment()->query("outdoors")))
		return;
	if (msgclass == "wizard" && !wiz_level(me))
		return;
	if (query_temp("block_msg/all")) {
		if (msgclass != "channel")
			return;
		msg = "! " + msg;
	}
	if (query_temp("block_msg/" + msgclass))
		return;
	if (in_input(this_object()) || in_edit(this_object()) ||
            this_object()->is_attach_system() && msgclass != "system")
        {
		if (sizeof(msg_buffer) < MAX_MSG_BUFFER)
			msg_buffer += ({ msg });
	} else
        {
                log_message(msg);
                if (written && ! this_object()->is_attach_system())
                {
			if (written == COMMAND_RCVD)
			{
				written = NONE;
                        	msg = ESC "[256D" ESC "[K" + msg;
			} else
                        	msg = ESC "[256D" ESC "[K" + msg + prompt();
                }

                while (strlen(msg) > MAX_STRING_SIZE)
                {
                        receive(msg[0..MAX_STRING_SIZE - 1]);
                        msg = msg[MAX_STRING_SIZE..<1];
                }
		receive(msg);
        }

}

void clear_written()
{
        written = COMMAND_RCVD;
}

int is_waiting_command()
{
        return (written == PROMPT_WRITTEN);
}

void write_prompt()
{
	if (sizeof(msg_buffer)) {
		write(BOLD "[暂存讯息]\n" NOR);
		foreach (string item in msg_buffer)
			receive(item);
		msg_buffer = ({});
		write(BOLD "[暂存讯息显示完毕]\n" NOR);
	}
	write(HIY "> " NOR);
}
void receive_snoop(string msg)
{
	if ((msg[0..5] == ESC "[256D") && (msg[6..8] != ESC "[K"))
		// Don't snoop prompt
		return;

        msg = replace_string(msg, ESC "[1A", ""); 
        msg = replace_string(msg, NOR, NOR BBLU WHT);
        //msg = replace_string(msg, ESC "[K", NOR ESC "[K" BBLU WHT);
        msg = BBLU WHT + msg + NOR + " " + ESC "[1D";

        while (strlen(msg) > MAX_STRING_SIZE)
        {
                receive(msg[0..MAX_STRING_SIZE - 1]);
                msg = msg[MAX_STRING_SIZE..<1];
        }
	receive(msg);
}