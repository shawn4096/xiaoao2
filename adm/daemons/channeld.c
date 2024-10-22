// channeld.c
// Modify by Yu Jue 1997, 添加了门派频道
// Modify by Yu Jue 1998-3-5, 优化
// add declare channel By bbb 2000-9-17
// add irc channel by augx@sj 9/24/2001
// add group channel by augx@sj 4/11/2002

#include <ansi.h>
#include <mudlib.h>
#include <net/daemons.h>
#include <net/dns.h>
#include <net/macros.h>

#define SEV_REMOTE       (AUX_PATH+"remote_q.c")

string channel_filter(object me,string input);

mapping channels = ([
	"declare":([
		"msg_speak": HIY "【信息】%s：%s\n" NOR,
		"wiz_only": 7,
		 "read_only": -1
	]),
	"debug":([
		"msg_speak": HIR "【调试】%s：%s\n" NOR,
		"msg_emote": HIR "【调试】%s\n" NOR,
		"read_only": 6,
		"wiz_only": 1
	]),
	"err": ([
		"msg_speak": HIR "【错误】%s：%s\n" NOR,
		"msg_emote": HIR "【错误】%s\n" NOR,
		"read_only": 6,
		"wiz_only": 1
	]),
	"sys": ([
		"msg_speak": HIR "【系统】%s：%s\n" NOR,
		"msg_emote": HIR "【系统】%s\n" NOR,
		"msg_color": HIR,
		"read_only": 6,
		"wiz_only": 1
	]),
	"imm": ([
		"msg_speak": HIY "【" HIM "顾问" HIY "】%s：%s\n" NOR,
		"msg_emote": HIY "【" HIM "顾问" HIY "】%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 1
	]),
	"app": ([
		"msg_speak": HIY "【" HIC "巫师" HIY "】%s：%s\n" NOR,
		"msg_emote": HIY "【" HIC "巫师" HIY "】%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 1
	]),
	"wiz": ([
		"msg_speak": HIY "【" HIG "仙人" HIY "】%s：%s\n" NOR,
		"msg_emote": HIY "【" HIG "仙人" HIY "】%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 1
	]),
	"arch": ([
		"msg_speak": HIY "【龙神】%s：%s\n" NOR,
		"msg_emote": HIY "【龙神】%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 4
	]),
	"ass": ([
		"msg_speak": HIY "【" HIR "神官" HIY "】%s：%s\n" NOR,
		"msg_emote": HIY "【" HIR "神官" HIY "】%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 5
	]),
	"adm": ([
		"msg_speak": HIY "【" HIW "天神" HIY "】%s：%s\n" NOR,
		"msg_emote": HIY "【" HIW "天神" HIY "】%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 6
	]),
	"chat": ([
		"msg_speak": HIC "【闲聊】%s：%s\n" NOR,
		"msg_color": HIC,
		"msg_emote": HIC "【闲聊】%s\n" NOR
	]),
	"trade": ([
		"msg_speak": HIY "【交易】%s：%s\n" NOR,
		"msg_color": HIY,
		"msg_emote": HIY "【交易】%s\n" NOR
	]),
	"sr": ([
		"exp": 500000,
		"forward": "chat"
	]),
	"rumor":([
		"msg_speak": HIM "【谣言】%s：%s\n" NOR,
		"msg_emote": HIM "【谣言】%s\n" NOR,
		"msg_color": HIM,
		"anonymous": "某人"
	]),
	"party":([
		"msg_speak": HIG "【门派】%s：%s\n" NOR,
		"msg_emote": HIG "【门派】%s\n" NOR,
		"msg_color": HIG,
		"party_only": 1
	]),
	"sj": ([
		"exp": 200000,
		"intermud": 1,
		"msg_speak": HIW "【书剑】%s：%s\n" NOR,
		"msg_emote": HIW "【书剑】%s\n" NOR,
		"msg_color": HIW
	]),
	"irc": ([
		"exp": 10000,
		"msg_speak": HIW "【聊天室】%s：%s\n" NOR,
		"msg_emote": HIW "【聊天室】%s\n" NOR,
		"msg_color": HIW
	]),
	"group": ([
		"exp": 100000,
		"msg_speak": HIY "【帮派】%s：%s\n" HIY,
		"msg_emote": HIY "【帮派】%s\n" HIY,
		"msg_color": HIY
	]),//R -> Y
]);

mapping ircs = ([
	"irc_channel": ([
		"room_name": "聊天室",
		"creator": "irc",
		"invite": 1,
		"passwd": "nopasswd",
		"user": ({ }),
		"master": ({ })
	]),
]);

int block_chat = 0;
int block_party = 0;
int block_rumor = 0;
int block_sr = 1;
int block_sj = 0;
int block_irc = 0;
int block_group = 0;
string party,group,groupid;

string last_rumor, last_rumor_id;

string query_last_rumor() { return last_rumor_id + "："+ last_rumor; }

string query(string arg)
{
	if (arg == "channel_id")
		return "频道精灵";
}

void create()
{
	seteuid(getuid());	// This is required to pass intermud access check.
}

void do_remote_channel(object me, string verb, string arg)
{
        object *obs;
        string msg;
        
        if (undefinedp(channels[verb]) || ! userp(me))
                return;
        // Ok, I will direct send the message to those people listening us.
        obs = users();
        msg = sprintf(channels[verb]["msg_emote"], arg);
        msg = replace_string(msg,"\n","");
        msg += "\n";
        message("channel:" + verb, msg, obs);
        // 向各个站点发送EMOTE信息
        if (channels[verb]["intermud"] && find_object(DNS_MASTER))
        {
        	GWIZ->send_msg(verb,me->query("id"), me->name(1),arg, 1);
        }
}

varargs int do_channel(object me, string verb, string arg, int emote)
{
	int cost, count, semote , rnow;
	object *ob;
	string *tuned_ch, who, rname;
	
	int pub = 1;
	
	// Check if this is a channel emote.
	if (verb[<1] == '*') {
		emote = 1;
		verb = verb[0..<2];
	}
	/*if (wizardp(me) && wiz_level(me) != 5 && INTERMUD_MUD_NAME != "SJMUD" && !me->query("env/chat"))
	    switch (verb) {
		case "chat":
		case "party":
		case "sr":
		case "sj":
		case "irc":
		case "group":
			return notify_fail("嘘……小声点！\n");
	}*/
	if (undefinedp(channels[verb])) return 0;
	if (userp(me) && !wizardp(me) && this_player() == this_player(1) && strlen(strip(arg)) > 100)
		arg = arg[0..99];
	if (userp(me) && !wizardp(me) && me->query("combat_exp") < channels[verb]["exp"])
		return notify_fail("你还要再努力一段时间才能使用这个频道。\n");
	if (userp(me) && wiz_level(me) < channels[verb]["wiz_only"])
		return 0;

	// check if one can write to channels
	if (me->query("chblk_on")) {
		if (!wizardp(me))
			return notify_fail("你的所有频道都被关闭了！\n");
		//only block a wiz's rumor and chat...
		me->set("chblk_rumor", 1);
		me->set("chblk_chat", 1);
	}

	// check if rumor or chat is blocked
	if (!userp(me) && !wizardp(me)) {
		if (block_chat && verb == "chat" )
			return notify_fail("系统的闲聊频道被关闭了！请使用 sr 频道。\n");
		if (block_party && verb == "party" )
			return notify_fail("系统的门派频道被关闭了！\n");
		if (block_rumor && verb == "rumor" )
			return notify_fail("系统的谣言频道被关闭了！\n");
		if (block_sj && verb == "sj" )
			return notify_fail("系统的书剑频道被关闭了！\n");
		if (block_sr && verb == "sr" )
			return notify_fail("系统的高级闲聊频道被关闭了！\n");
		if (block_irc && verb == "irc" )
			return notify_fail("系统的聊天室频道被关闭了！\n");
		if (block_group && verb == "group" )
			return notify_fail("系统的帮派频道被关闭了！\n");
	}

	if (channels[verb]["forward"])
		verb = channels[verb]["forward"];

	if (me->query("chblk_"+verb)) {
		if (verb == "party") return notify_fail("你的门派频道被关闭了！\n");
		if (verb == "rumor") return notify_fail("你的谣言频道被关闭了！\n");
		if (verb == "chat") return notify_fail("你的闲聊频道被关闭了！\n");
		if (verb == "sj") return notify_fail("你的书剑频道被关闭了！\n");
		if (verb == "irc") return notify_fail("你的聊天室频道被关闭了！\n");
		if (verb == "group") return notify_fail("你的帮派频道被关闭了！\n");
	}

	if (emote && !channels[verb]["msg_emote"])
		return notify_fail("这个频道不支持动作。\n");
	if (!stringp(arg) || arg == "") {
		arg = "...";
		if (emote) arg = "自言自语地不知道在说些什么。";
	}
	
	if (channels[verb]["party_only"] && !me->query("family/family_name"))
		return notify_fail("你还是先加入一个门派再说吧。\n");

	if (channels[verb]["party_only"]) {
		if (wizardp(me) && stringp(me->query("env/party")) && strlen(me->query("env/party")) > 3)
			party = me->query("env/party");
		else party = me->query("family/family_name");
		channels[verb]["msg_speak"] = HIG "【"+party+"】%s：%s\n" NOR;
		channels[verb]["msg_emote"] = HIG "【"+party+"】%s\n" NOR;
	}

	// Support of group channel
	if( verb == "group" ) {
		if( wizardp(me) && stringp(me->query("env/group")) && strlen(me->query("env/group"))>3 )
			groupid = me->query("env/group");
		else
			groupid = me->query("group/id");
		group = GROUP_D->get_group_name(groupid);
		if( group == "" )
			return notify_fail("请先加入一个帮派。\n");
		channels[verb]["msg_speak"] = HIY "【"+group+HIY"】%s：%s\n" NOR;
		channels[verb]["msg_emote"] = HIY "【"+group+HIY"】%s\n" NOR;
	}

	// If we speaks something in this channel, then must tune it in.
	if (userp(me)) {
		tuned_ch = me->query("channels");
		if (!pointerp(tuned_ch)) me->set("channels", ({ verb }));
		else if (member_array(verb, tuned_ch)==-1) me->set("channels", tuned_ch + ({ verb }));
		if (wiz_level(me) < channels[verb]["read_only"])
			return notify_fail(verb + "频道已经打开了。\n");
	}

	if (verb == "rumor") {
		last_rumor = arg;
		last_rumor_id = userp(me)?me->query("id"):base_name(me);
	}

	// Support of channel emote
	who = channels[verb]["anonymous"];
	if (who && userp(me) && !wizardp(me) && !random(5)) {
		who = me->query("name");
		me->set_temp("rumor_show", uptime() + 30);
	}
	if (emote) {
		string vb, emote_arg,mud;
		
		if (channels[verb]["intermud"] && me->query("id"))
			who = me->query("name")+"("+capitalize(me->query("id"))+"@"+Mud_name()+")";
		if (sscanf(arg, "%s %s", vb, emote_arg) != 2){
			vb = arg;
			emote_arg = "";
		}
		
		if (channels[verb]["intermud"] && sscanf(emote_arg, "%s@%s", emote_arg, mud) == 2 && upper_case(mud) != INTERMUD_MUD_NAME )
                {
                		count = me->add_temp("shujian_count", 1);
				if (count < 0 || count > 6) count = 6;
				cost = 20;
				while (--count)
					cost += cost;
				if (me->query("jingli") < cost)
					return notify_fail("你的精力不足了。\n");
				me->receive_damage("jingli", cost);                		
                                SEV_REMOTE->send_remote_q(mud, verb, me->query("id"), emote_arg, vb);
                                write("网路讯息已送出，请稍候。\n");
                                return 1;
		}
		
		arg = 0;
		if (vb[0] < 128)
			arg = EMOTE_D->do_emote(me, vb, emote_arg, 1, who);
		if (!arg) {
			if (vb[0] < 128)
				return notify_fail("你想表达什么？\n");
			if (userp(me) && !wizardp(me))
				foreach (int item in vb) {
					if (item == ' ') break;
					if (item == '(')
						return notify_fail("不准伪造频道信息！\n");
				}
				
			if(userp(me) && !wizardp(me)) vb = channel_filter(me,vb);
			
			arg = (who?who:me->name()) + vb;
			if (emote_arg)
				arg += " " + emote_arg;
		} else semote = 1;
	}
	else
	{
		if(userp(me) && !wizardp(me)) arg = channel_filter(me,arg);
	}
	
	if (stringp(arg)) {
		string color;
		
		if (stringp(color = channels[verb]["msg_color"]) && color != NOR)
			arg = replace_string(arg, NOR, CSI+"0m"+color);
		else
			arg = strip(arg);
	}
	
	if(verb=="group" || verb=="irc") pub = 0;

	if (strsrch(arg, "\n【闲聊】") > 0)
		return notify_fail("不准伪造闲聊信息！\n");
	if (strsrch(arg, "\n【谣言】") > 0)
		return notify_fail("不准伪造谣言信息！\n");
	if (strsrch(arg, "\n【"+party+"】") > 0)
		return notify_fail("不准伪造门派信息！\n");
	if (strsrch(arg, "\n【"+group+"】") > 0)
		return notify_fail("不准伪造帮派信息！\n");
	if (pub && arg == me->query_temp("last_channel_msg"))
		return notify_fail("用公共频道说话请不要重复相同的讯息。\n");

	if (who) {
		if (userp(me) && !wizardp(me)) {
			count = me->add_temp("rumor_count", 1);
			if (count < 0 || count > 6)
				count = 6;
			cost = 20;
			while (--count)
				cost += cost;
			if (me->query("jingli") < cost)
				return notify_fail("你已经没有足够的精力散布谣言了。\n");
			me->receive_damage("jingli", cost);
		}
	} else {
		if (me->query_temp("rumor_count") > 0)
			me->add_temp("rumor_count", -1);
		if (userp(me) || !stringp(who = me->query("channel_id")))
			who = me->query("name") + "(" + capitalize(me->query("id")) + ")";
	}

	// Support of irc channel
	if( verb == "irc" ) {
		if( stringp(me->query_temp("irc/room_sayin")) ) {
			rname = me->query_temp("irc/room_sayin");
			me->delete_temp("irc/room_sayin");
		}
		else {
			rnow = (int)me->query_temp("irc/room");
			if( rnow<1 || rnow>5 ) return notify_fail("请先设定您要说话的聊天室！\n");
			rname = me->query_temp(sprintf("irc/room%d",rnow));
		}
		if( !stringp(rname) || rname=="" || undefinedp(ircs[rname]) ) return notify_fail("您要说话的聊天室不存在！\n");

		channels[verb]["msg_speak"] = HIW "【"+ircs[rname]["room_name"]+"】%s：%s\n" NOR;
		channels[verb]["msg_emote"] = HIW "【"+ircs[rname]["room_name"]+"】%s\n" NOR;
		rname += ":";
	}
	else rname = "";

	// Ok, now send the message to those people listening us.
	ob = filter_array( users(), "filter_listener", this_object(), verb );

	if (emote) {
		if (userp(me)) {
			object *tmp = filter_array(ob, (: wizardp :));
			ob -= tmp;
			message( "channel:" + verb, rname + sprintf(channels[verb]["msg_emote"],
				"("+capitalize(me->query("id"))+")" + arg ), tmp );
		}
		message("channel:" + verb, rname + sprintf( channels[verb]["msg_emote"], arg ), ob);
	} else {
		if (userp(me) && channels[verb]["anonymous"]) {
			object *tmp = filter_array(ob, (: wizardp :));
			ob -= tmp;
			message( "channel:" + verb, rname + sprintf(channels[verb]["msg_speak"],
				who+"("+capitalize(me->query("id"))+")", arg ), tmp );
		}
		message( "channel:" + verb, rname + sprintf( channels[verb]["msg_speak"], who, arg ), ob );
	}

	if (arrayp(channels[verb]["extra_listener"])) {
		channels[verb]["extra_listener"] -= ({ 0 });
		if (sizeof(channels[verb]["extra_listener"]))
			channels[verb]["extra_listener"]->relay_channel(me, verb, arg, emote); //Add emote by LinuX@SJ for Channel Log
	}

	if (pub && userp(me) && !wizardp(me)) {
		int t = uptime();

		if (!semote && strlen(arg) > 5)
			if (arg[0] >= ' ' && stringp(me->query_temp("last_channel_msg"))
			&& strlen(me->query_temp("last_channel_msg")) > 5
			&& (me->query_temp("last_channel_msg")[0..2] == arg[0..2]
			|| me->query_temp("last_channel_msg")[<3..<1] == arg[<3..<1]))
				me->add_temp("channel_repeat", 1);
			else if (me->add_temp("channel_repeat", -1) < 0) {
				if (me->query_temp("robottest") < t-1200)
					me->add_temp("robottest", 20);
				me->delete_temp("channel_repeat");
			}

		if (me->query_temp("channel_repeat") > 3) {
			me->delete_temp("channel_repeat");
			me->set("chblk_"+verb, 1);
			me->add_condition("vote_chblk", 30); // 10 min
			switch (verb) {
				case "chat": verb = "闲聊"; break;
				case "rumor": verb = "谣言"; break;
				case "party": verb = "门派"; break;
				case "sj": verb = "书剑"; break;
				case "irc": verb = "聊天室"; break;
				case "group": verb = "帮派"; break;
				default: verb = "交谈";
			}
			do_channel(this_object(), "rumor",
				"由于讲话太罗嗦，" + me->query("name")
				+"("+capitalize(me->query("id"))+")的" + verb + "频道被噎死了。");
		} else if (me->add_temp("channel_count", 1) > 1) {
			me->delete_temp("channel_count");
			if (me->query_temp("last_channel_time") == t) {
				me->set("chblk_"+verb, 1);
				me->add_condition("vote_chblk", 30); // 10 min
				switch (verb) {
					case "chat": verb = "闲聊"; break;
					case "rumor": verb = "谣言"; break;
					case "party": verb = "门派"; break;
					case "sj": verb = "书剑"; break;
					case "irc": verb = "聊天室"; break;
					case "group": verb = "帮派"; break;
					default: verb = "交谈";
				}
				do_channel(this_object(), "rumor",
					"由于讲话太多太快，" + me->query("name")
					+"("+capitalize(me->query("id"))+")的" + verb + "频道被噎死了。");
			}
			me->set_temp("last_channel_time", t);
		}
		me->set_temp("last_channel_msg", arg);
	}
	
	if(pub && me->query_temp("bad_word") > 3 && !me->query_condition("vote_chblk") )
	{
		//call_out("shoutmsg",0,me->query("name"));
		message("shout", HIC "【通告】" + me->query("name") + "在公开频道讲话中连续含有不雅言词，暂时关闭所有交谈频道，并记录在案，等候处理。\n" NOR,users());
		me->delete_temp("bad_word");
		me->apply_condition("vote_chblk", 40);
               	me->set("chblk_on", 1);
               	me->set("chblk_party",1);
               	me->set("chblk_sj", 1);
	}
		
	if (verb=="sj" && find_object(DNS_MASTER)) GWIZ->send_msg("sj", me->query("id"), me->query("name"), arg, emote);
	return 1;
}

int filter_listener(object ppl, string verb)
{
	mapping ch;

	// Don't bother those in the login limbo.
	if (!environment(ppl)) return 0;

	ch = channels[verb];
	if( ch["wiz_only"] ) return wiz_level(ppl) >= ch["wiz_only"];
	if( ch["party_only"] )
		return ( wizardp(ppl) && (!ppl->query("env/party") || ppl->query("env/party")==party) )
			|| party == ppl->query("family/family_name");
	if( verb == "group" )
		return ( wizardp(ppl) && (!ppl->query("env/group") || ppl->query("env/group")==group) )
			|| groupid == ppl->query("group/id");
	return 1;
}

void register_relay_channel(string channel)
{
	object ob;

	ob = previous_object();
	if (undefinedp(channels[channel]) || !ob) return;
	if (arrayp(channels[channel]["extra_listener"])) {
		if (member_array(ob, channels[channel]["extra_listener"]) >=0) return;
		channels[channel]["extra_listener"] += ({ ob });
	} else
		channels[channel]["extra_listener"] = ({ ob });
}

int set_block(string channel, int d)
{
	if (channel == "chat") block_chat = d;
	if (channel == "party") block_party = d;
	if (channel == "rumor") block_rumor = d;
	if (channel == "sr") block_sr = d;
	if (channel == "sj") block_sj = d;
	if (channel == "irc") block_irc = d;
	if (channel == "group") block_group = d;
	return 1;
}

//////////////////////////// irc functions /////////////////////////
mapping query_all_ircs() { return ircs; }

mapping query_ircs(string v)
{
	if( undefinedp(ircs[v]) ) return 0; else return ircs[v];
}

string query_ircs_creator(object me)
{
	string * k;
	mapping * v;
	int i,j;

	if( (j=sizeof(ircs)) < 1 ) return "";
	k = keys(ircs);
	v = values(ircs);
	for(i=0;i<j;i++) {
		if( v[i]["creator"]==me->query("id") ) return k[i];
	}
	return "";
}

void delete_ircs(string v)
{
	map_delete(ircs,v);
}

int set_ircs(string v , mapping m)
{
	ircs[v] = copy(m);
	return 1;
}

void irc_list(object me)
{
	string * k;
	mapping * v;
	int i,j;

	if( (j=sizeof(ircs)) < 2 ) {
		tell_object(me, "目前没有聊天室被创建。\n");
		return;
	}

	k = keys(ircs);
	v = values(ircs);
	tell_object(me, "目前的聊天室有：\n");
	for(i=0;i<j;i++) {
		if( k[i] == "irc_channel" ) continue;
		tell_object(me, sprintf("%-16s %-10s 创建者：%-10s 加入%-6s密码 加入%-6s邀请 \n",
			v[i]["room_name"], k[i], v[i]["creator"], v[i]["passwd"]=="nopasswd"?"不需要":"需要", v[i]["invite"]==1?"需要":"不需要") );
	}
}

//fuck array 全部使用小写英语
string *fuck = ({
      	"fuck","屁眼","操你妈","干你娘","他妈的",
      	"放屁","鸡巴","阴道","傻b","傻x","tmd","tnnd",
      	"婊子","你丫","丫挺","你妈个","去你妈","日你妈","妓女",
      	"x你妈","赤佬","瘪三","傻逼","蠢蛋","c你妈"
	});

//下面这两个是给Admin Call 的 以便随时更新 再做文件更新的准备

int add_fuck(string arg)
{
	if(!arg) return 0;
	fuck += ({arg});
	return 1;
}
int del_fuck(string arg)
{
	if(!arg) return 0;
	fuck -= ({arg});
	return 1;
}

//过滤
string channel_filter(object me,string input)
{
	string output;
	int i,flag=0;
	
	output = input;
	
        i = strlen(input);
        while (i--) {
                if (input[i] >= 'A' && input[i] <='Z') {input[i]+=32; continue;}
                if (input[i] >= 'a' && input[i] <='z') continue;
                if (input[i] > 128)
                {
                	if(input[i]==163 && !undefinedp(input[i+1]) )
                	{
                		if ( input[i+1]>=193 && input[i+1]<=218 )
                		{
                			input[i+1] = 96;
                			input = input[0..i-1] + input[i+1..<1];
                		}                		
                		if ( input[i+1]>=225 && input[i+1]<=250 )
                		{
                                        input[i+1] = 128;
                			input = input[0..i-1] + input[i+1..<1];
                		}                		                		
                	}
                	continue;
                }
                input = input[0..i-1] + input[i+1..<1];
        }
        
	for(i=0;i<sizeof(fuck);i++){
		if (strsrch(input, fuck[i]) >= 0)
		{
			flag=1;
			//break;
			input = replace_string(input,fuck[i],"×××");
		}
	}
	if(flag)
	{
		output = input+HIY" (含有不文明词语，被系统过滤，并记录在案)"NOR;
		me->add_temp("bad_word",1);
		//		
	}
	return output;
}

void shoutmsg(string arg)
{
	if(!arg) return;
	message("shout", HIC "【通告】" + arg + "在公开频道讲话中含有不雅言词，暂时关闭所有交谈频道，并记录在案，等候处理。\n" NOR,users());
}
