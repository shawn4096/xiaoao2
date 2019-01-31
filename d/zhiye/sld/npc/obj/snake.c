// snake
//训蛇的标准任务蛇
//by sohu
#include <ansi.h>
inherit NPC;

int snakehd();
int snake_attack_ob(object ob);

void create()
{
	set_name("毒蛇", ({ "du she","snake","she" }) );       
	set("race", "野兽");
	set("long", HIY"这是条小蛇。\n"NOR);
	set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
	set("verbs", ({ "bite" }) );
	set("combat_exp", 1000000);  
	set("no_return",1);
	set("no_clear_up",1);
	set("attitude", "friendly");
	
	//set("qushe/times",10);
	set("str",30);
	set("int",30);
	set("con",30);
	set("dex",30);
	set("kar",30);
	set_weight(1000);
	call_out("dest",120,this_object());
	setup();
}
int dest(object ob)
{
	
	if (!ob) return 0;
	
	if (query_temp("qushe/times")>0) 
	{
		add_temp("qushe/times",-1);

		call_out("dest",1,ob);
	}else
	{
		write(ob->query("name")+"向远处森林蜿蜒而去！\n");
		destruct(ob);
	}

	return 1;
}
nosave string *banned_command = 
	({ "rumor", "sj", "irc", "party", "give", "get", "vote", "ansuan", "fight","sr" });

void do_command(string arg)     
{
	string dir,*cmds;
	object target,owner = query("owner");
    
	if(!arg || arg=="" || !owner ) return;
	
	cmds = explode(arg," ");
        cmds[0] = replace_string(cmds[0],"*","");
        cmds[0] = replace_string(cmds[0]," ","");
        if ( member_array(cmds[0], banned_command)!=-1 ) {
        	tell_object(owner, "蛇不能执行此指令！\n");
		return;
	}
	
	switch(arg) {
		case "e":	dir="east"; break;
		case "w":	dir="west"; break;
		case "n":	dir="north"; break;
		case "s":	dir="south"; break;
		case "ne":	dir="northeast"; break;
		case "nw":	dir="northwest"; break;
		case "se":	dir="southeast"; break;
		case "sw":	dir="southwest"; break;
		case "u":	dir="up"; break;
		case "d":	dir="down"; break;
		case "nu":	dir="northup"; break;
		case "eu":	dir="eastup"; break;
		case "su":	dir="southup"; break;
		case "wu":	dir="westup"; break;
		case "nd":	dir="northdown"; break;
		case "ed":	dir="eastdown"; break;
		case "sd":	dir="southdown"; break;
		case "wd":	dir="westdown"; break;
		case "l":	dir="look"; break;
		case "out": dir="out"; break;
		default:	dir=arg; break;
	}
	/*
	if( cmds[0]=="kill" || cmds[0]=="hit" ) 
	{
		if( sizeof(cmds) > 1 && strlen(cmds[1])>2 && target=present(cmds[1],environment(this_object())) ) {
			if( userp(target) && !target->is_fighting(this_object()) ) {
				tell_object(owner, "蛇不能伤害对自己没有威胁的人类！\n");
				return;
			}
		}
	}*/
	
//	set_name(HIY+owner->query("name")+"的金蛇"NOR, ({ owner->query("id")+"'s jinshe"}) );
	//command(dir);
	
	switch(dir) {
		case "east":		
		case "west":		
		case "north":		
		case "south":		
		case "northeast":	
		case "northwest":	
		case "southeast":
		case "southwest":
		case "up":
		case "down":
		case "northup":
		case "eastup":
		case "southup":
		case "westup":
		case "northdown":
		case "eastdown":
		case "southdown":
		case "westdown":
		case "enter":
		case "out": command(dir); break;
		default: break;
	}
	add_temp("qushe/times",1);
	
	if (query_temp("qushe/times")>(18+random(4)))
	{
		write(HIR"这条"+query("name")+HIR"看起来已经筋疲力尽了！\n");
		die();
	}
	else if (query_temp("qushe/times")>=15)
	{
		write(HIY"这条"+query("name")+HIY"看起来似乎有些累了！\n");
		set_temp("qushe/ok",1);
	}
	else if (query_temp("qushe/times")>10)
	{
		write("这条"+query("name")+"游动稍微有些迟缓！\n");
	}else if (query_temp("qushe/times")>5)
	{
		write("这条"+query("name")+"游动迅捷无比！\n");
	}
	return ;
}
