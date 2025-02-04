// user.c
// modified by Ciwei@SJ for refresh

#include <ansi.h>
#include <origin.h>
#include <user.h>

inherit CHARACTER2;
inherit F_AUTOLOAD;
inherit F_SAVE;
//inherit F_FROZEN;

#include <database.h>
#include <mudlib.h>

void change_frozen(object me,string prop,string type);

void create()
{
	::create();
	set_name("使用者物件", ({ "user object", "user", "object" }) );
}

void terminal_type(string term_type)
{
	set_temp("terminal_type", term_type);
}

void window_size(int x, int y)
{
	set_temp("window_size/x", x);
	set_temp("window_size/y", y);
}

void telnet_suboption(string opt)
{
	set_temp("telnet_suboption", opt);
}

void reset()
{
	if (!query("jingli"))
		set("jingli", 10);
	if (query("potential") < query("max_pot")/2)
		add("potential", 1);
	if (query("thief") > 0)
		add("thief", -1);
	delete_temp("saved");
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
	string id;

	id = geteuid();
	if (!id) id = getuid();
	if (!stringp(id)) return 0;
	return sprintf(DATA_DIR "user/%c/%s", id[0], id);
}

int save()
{
	int res;

	save_autoload();
	res = ::save();
	clean_up_autoload();		// To save memory
	return res;
}

nosave int last_age_set = uptime();

// This function updates player's age, called by heart_beat()
void update_age()
{
	object me = this_object();
	int minute, age = 14, month, day, modify = query("age_modify");
	int gap = uptime() - last_age_set;
	int vip = query("vip/vip_time") - time(); //贵宾 LinuX@SJ

	call_out("change_frozen",1,me,"","all");
	//for refresh 没有呼叫过show_two_screen() 是不会有任何效果 ^_^ by ciwei@SJ
	delete("age_modify");
	add("mud_time", gap);	// 此为实际连线时间 yuj@SJ 2001-09-26
	if (query("mud_age") / 6 > query("combat_exp"))	// 经验增长慢的年龄增长也慢 yuj@SJ 2001-09-26
		add("mud_age", -gap/2);
	minute = add("mud_age", gap) / 60;
	if (minute <=8640) {
		age += minute / 1440;
		day = (minute % 1440) / 4;
	} else {
		minute -= 8640;
		age = 20;
		while ((minute -= age*240 - 3120) >= 0) age++;
		day = (minute + age*240 - 3120) * 360 / (age*240 - 3120);
	}
	month = day / 30;
	set("day", day % 30);
	if (modify > 0)
		while (modify--) {
			add("mud_age", 86400);
			if (age > 19) {
				add("mud_age", (age-19)*14400);
				add("mud_age", 1200*month);
			}
			age++;
		}
	else
		while (modify++) {
			add("mud_age", -86400);
			if (age > 20) {
				add("mud_age", (20-age)*14400);
				add("mud_age", -1200*month);
			}
			age--;
		}
	last_age_set += gap;
		
	if (query("month") != month) {
		set("month", month);
		set("kar", 10+random(21));
		//有关贵宾激活 LinuX@SJ 2004-02-17
		if ( vip > 0 && (me->query("registered") < 3 )) {
                set("registered",3);
                tell_object(me, HBRED+HIY"您的贵宾已经被系统自动激活！\n"NOR);
        	}
        	if ( vip < 0 && (me->query("registered") > 2 )) {
        		set("registered",2);
        		delete("vip/vip_time");
        		delete("vip/vip_start_time");
        		tell_object(me, HBRED+HIY"您的贵宾已经到期，系统已经自动取消您的贵宾！\n"NOR);
        	}
        	if (query("age") != age) {
			set("age", age);
			tell_object(me, "时间过得真快，不知不觉你已经" + chinese_number(age) + "岁了。\n");
		}
		else tell_object(me, "一个月又过去了，现在的运气不知道怎么样。\n");
		save();
	}

	add_temp("online_time", gap);
	add("online_total", gap);
	if (!query_temp("online_time")) {
		int t = time() - query("check_point");

		if (query("registered") < 3) {
			if ((t -= 1800) < 0)
				t = 0;
			if ((t *= 3) < 0)
				t =0;
		} else {
			if ((t -= 300) < 0)
				t = 0;
			if ((t *= 4) < 0)
				t =0;
		}
		if (add("online_total", -t) < 0)
			delete("online_total");
	}
	
	set("check_point", time());
	
	if (!living(me) || wizardp(me) || me->is_ghost() || me->query_temp("quit")) ;

	else if (query("online_total") >= 48*3600 && query("registered") < 3) {
		tell_object(me, BLINK "你上线时间太长，实在支持不住了。\n" NOR);
		receive_damage("jingli", query("eff_jingli")/3);
	} else if (query("online_total") >= 47*3600+1800 && query("registered") < 3)
		tell_object(me, BLINK "你忽然觉得烦闷欲吐，看来该退出休息一会了。\n" NOR);
		
	if(query("online_total")>24*3600 && uptime()-query_temp("warning_time_time") > 10*60 )
	{
		tell_object(me, "你已经连续在书剑奋斗"+chinese_number(query("online_total")/3600)+"小时了，请注意休息。\n");
		me->set_temp("warning_time_time",uptime() );
	}	
	/*
	else if (query_temp("online_time") >= 20*3600) {
		tell_object(me, BLINK "你上线时间太长，实在支持不住了。\n" NOR);
		receive_damage("jingli", query("eff_jingli")/3);
	} else if (query_temp("online_time") >= 19*3600+1800)
		tell_object(me, BLINK "你忽然觉得烦闷欲吐，看来该退出休息一会了。\n" NOR);
	*/
}

void setup()
{
	// We want set age first before new player got initialized with
	// random age.
	update_age();

	::setup();
	restore_autoload();
}

//private 
void user_dump(int type)
{
	object me = this_object();

	switch(type) {
		case DUMP_NET_DEAD:
			if (!wizardp(me) || !me->query("env/invisibility"))
				tell_room( environment(), query("name") + "断线超过"
					+ chinese_number((uptime()-query_temp("netdead"))/60)
					+ "分钟，自动退出这个世界。\n");
			"/cmds/usr/quit"->main(me);
			break;
		case DUMP_IDLE:
			if (wizardp(me)) break;
			if ( me->query("no_idle_quit")) break;
			tell_object(me, "对不起，您已经发呆超过 "
				+ IDLE_TIMEOUT/60 + " 分钟了，请下次再来。\n");
			if (!wizardp(me) || !me->query("env/invisibility"))
				tell_room(environment(), "一阵风吹来，将发呆中的" + query("name")
					+ "化为一堆飞灰，消失了。\n", me);
			"/cmds/usr/quit"->main(me);
	}
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.
private void net_dead()
{
	object me = this_object();
	object link_ob;

	if (!query_condition("killer"))
		set_heart_beat(0);
	if (objectp(link_ob = query_temp("link_ob"))) {
		link_ob->set("last_on", time());
		link_ob->set("last_from", link_ob->query_temp("last_from"));
		link_ob->save();
		destruct(link_ob);
	}

// adding by Yu Jue 1997-8-17
	if (!environment()) {
		destruct(me);
		return;
	}

	// Stop fighting, we'll be back soon.
	remove_all_enemy();

	set_temp("netdead", uptime());
	if (userp(me)) {
		call_out("user_dump", wiz_level(me)?1:NET_DEAD_TIMEOUT, DUMP_NET_DEAD);
		if (!wizardp(me) || !me->query("env/invisibility"))
			tell_room(environment(), name() + "断线了。\n", me);
		CHANNEL_D->do_channel(load_object(LOGIN_D), wiz_level(me)?"wiz":"sys", short(1) + NOR " 断线了。");
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
/* //writeback//
void namemodify_bbsback(mixed ret)
{
	if(!clonep()) return;
	tell_object(this_object(),"您在论坛的名字已经成功更新。\n");
}
////////////////////////////for refresh frozen///////////////////////

mixed add(string prop, mixed data)
{
	mixed r = ::add(prop,data);
	if(r) change_frozen(this_object(),prop,"db");
	return r;
}
mixed add_temp(string prop, mixed data)
{
	mixed r = ::add_temp(prop,data);
	if(r) change_frozen(this_object(),prop,"temp");
	return r;	
}
int delete_temp(string prop)
{
	int r = ::delete_temp(prop);
	if(r) change_frozen(this_object(),prop,"temp");
	return r;
}
mixed set_temp(string prop, mixed data)
{
	mixed r = ::set_temp(prop,data);
	if(r) change_frozen(this_object(),prop,"temp");
	return r;
}
int delete(string prop)
{
	int r = ::delete(prop);
	if(r) change_frozen(this_object(),prop,"db");
	return r;
} */
//dbquery("UPDATE Users SET U_Name="
//+save_variable(data)+" WHERE U_Username=" 
//+ save_variable(getuid(this_object())));
/* mixed set(string prop, mixed data)
{
	mixed r = ::set(prop,data);
	if(r){
		if(clonep() && prop=="name" && stringp(data) && strlen(data)<=8 &&  previous_object()!=find_object(LOGIN_D) && previous_object()!=find_object(FINGER_D) )
			if(!BBS_D->add_Bbs_Up_Map(WEB_DB_NAME,"UPDATE members SET cname = '"+data+"' WHERE username = '"+getuid(this_object())+"@"+lower_case(INTERMUD_MUD_NAME)+"' limit 1",this_object(),"namemodify_bbsback"))
				tell_object(this_object(),"无法更新您在论坛的名字，请通知论坛主管手动修改。\n");
		change_frozen(this_object(),prop,"db");
	}
	return r;
}
*/
void change_frozen(object me,string prop,string type)
{	
	if(!me->query_temp("show_frozen")) return;
	//最好把这个控制做成玩家不能控制第 ^_^ just login call and refresh call 也就是
	//这个控制变量变化的同时	
	if(type=="all"){
		F_FROZEN->refresh_screen_all(me);
	}
	if(type=="temp"){
		if(prop=="armor/surcoat") F_FROZEN->refresh_surcoat(me);
		if(prop=="armor/boots") F_FROZEN->refresh_boots(me);
		if(prop=="armor/armor") F_FROZEN->refresh_armor(me);
		if(prop=="armor/boots") F_FROZEN->refresh_boots(me);
		if(prop=="armor/cloth") F_FROZEN->refresh_cloth(me);
		if(prop=="weapon") F_FROZEN->refresh_weapon(me);
		if(prop=="apply/jingli") F_FROZEN->refresh_jingli(me);
		if(prop=="apply/force") F_FROZEN->refresh_maxneili(me);
		if(prop=="apply/neili") F_FROZEN->refresh_maxneili(me);
		if(prop=="apply/neili") F_FROZEN->refresh_neili(me);
		if(prop=="apply/jing") F_FROZEN->refresh_jing(me);
		if(prop=="apply/qi") F_FROZEN->refresh_qi(me);
		//if(prop=="") F_FROZEN->refresh_(me);	
	}
	if(type=="db"){
		if(prop=="jingli") F_FROZEN->refresh_jingli(me);	
		if(prop=="eff_jingli") F_FROZEN->refresh_jingli(me);	
		if(prop=="max_jingli") F_FROZEN->refresh_jingli(me);	
		if(prop=="food") F_FROZEN->refresh_food(me);	
		if(prop=="potential") F_FROZEN->refresh_pot(me);	
		if(prop=="max_pot") F_FROZEN->refresh_pot(me);	
		if(prop=="combat_exp") F_FROZEN->refresh_maxneili(me);
		if(prop=="age") F_FROZEN->refresh_maxneili(me);	
		if(prop=="shen") F_FROZEN->refresh_shen(me);	
		if(prop=="neili") F_FROZEN->refresh_neili(me);
		if(prop=="max_neili") F_FROZEN->refresh_neili(me);
		if(prop=="jiali") F_FROZEN->refresh_neili(me);
		if(prop=="combat_exp") F_FROZEN->refresh_exp(me);	
		if(prop=="max_pot") F_FROZEN->refresh_exp(me);	
		if(prop=="water") F_FROZEN->refresh_water(me);	
		if(prop=="jing") F_FROZEN->refresh_jing(me);	
		if(prop=="eff_jing") F_FROZEN->refresh_jing(me);
		if(prop=="max_jing") F_FROZEN->refresh_jing(me);
		if(prop=="qi") F_FROZEN->refresh_qi(me);
		if(prop=="eff_qi") F_FROZEN->refresh_qi(me);
		if(prop=="max_qi") F_FROZEN->refresh_qi(me);
		//if(prop=="") F_FROZEN->refresh_(me);		
	}	
}

/*

//if(type=="skill")
	//{
		//tell_object(this_object(),"有call到这个函数么？\n");
	//	if(prop=="force") refresh_jingli(this_object());
	//	if(prop=="force") refresh_maxneili(this_object());
		//if(prop=="") refresh_(this_object());		
	//}

int skill_improved(string prop)
{
	//tell_object(this_object(),"有call到这个函数么？\n");
	change_frozen(prop,"skill");
}

void set_entire_dbase(mapping db)
{
	::set_entire_dbase(db);
	change_frozen("","all");
}
*/
