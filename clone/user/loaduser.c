// loaduser.c

#include <ansi.h>
#include <origin.h>
#include <user.h>

inherit CHARACTER;
inherit F_AUTOLOAD;
inherit F_SAVE;

nosave int last_age_set;
string userid;

varargs void create(string arg)
{
	::create();
	set_name("玩家数据", ({ arg }) );
	userid = arg;
}

void reset()
{
	if (!query("jingli"))
		set("jingli", 10);
	if (!query("qi"))
		set("qi", 1); //renlai加上，防止异常数据
	if (!query("jing"))
		set("jing", 1); //renlai加上，防止异常数据
	if( (int)query("potential") < (int)query("max_pot") )
		add("potential", 1);
	if( (int)query("thief") > 0 )
		add("thief", -1 );
}

int save()
{
	int res;

	save_autoload();
	res = ::save();
	clean_up_autoload();		// To save memory
	return res;
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
	return sprintf(DATA_DIR "user/%c/%s", userid[0], userid);
}

// This function updates player's age, called by heart_beat()
void update_age()
{
	int hour, age = 14;

	// Update the time we spend on mudding, using method from TMI-2 mudlib.
	if( !last_age_set ) last_age_set = time();
	add("mud_age", time() - last_age_set);
	hour = query("mud_age") / 3600;
	//hour =(int)hour*2/3;
	while ((hour -= age + 10) >= 0) age++;
	last_age_set = time();
	set("age", (int)query("age_modify") + age);
	set("month", (hour + age + 10)  * 12 / (age + 10));
}

void setup()
{
	// We want set age first before new player got initialized with
	// random age.
	update_age();

	::setup();
	restore_autoload();
}

private void user_dump(int type)
{
	switch(type) {
		case DUMP_NET_DEAD:
			tell_room( environment(), query("name") + "断线超过"
				+ chinese_number(NET_DEAD_TIMEOUT/60)
				+ "分钟，自动退出这个世界。\n");
			command("quit");
			break;
		case DUMP_IDLE:
			tell_object( this_object(), "对不起，您已经发呆超过 " 
				+ IDLE_TIMEOUT/60 + " 分钟了，请下次再来。\n");
			tell_room( environment(), "一阵风吹来，将发呆中的" + query("name")
				+ "化为一堆飞灰，消失了。\n", ({this_object()}));
			command("quit");
			break;
		default: return;
	}
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.
private void net_dead()
{
	object link_ob;

	set_heart_beat(0);
	if( objectp(link_ob = query_temp("link_ob")) )
		destruct(link_ob);

// adding by Yu Jue 1997-8-17
	if (!environment()) {
		destruct(this_object());
		return;
	}

	// Stop fighting, we'll be back soon.
	remove_all_enemy();

	set_temp("netdead", 1);
	if( userp(this_object()) ) {
		call_out("user_dump", NET_DEAD_TIMEOUT, DUMP_NET_DEAD);
		tell_room(environment(), name() + "断线了。\n", this_object());
		message("channel:sys", HIR "【系统】连线精灵：" NOR
			+ short(1) + HIR " 断线了。\n" NOR,
			filter_array(users(), (: wizardp :)));
	}
}

// reconnect: called by the LOGIN_D when a netdead player reconnects.
void reconnect()
{
	set_heart_beat(1);
	delete_temp("netdead");
	remove_call_out("user_dump");
	tell_object(this_object(), "重新连线完毕。\n");
}
