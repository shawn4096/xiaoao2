// snake
//ѵ�ߵı�׼������
//by sohu
#include <ansi.h>
inherit NPC;

int snakehd();
int snake_attack_ob(object ob);

void create()
{
	set_name("����", ({ "du she","snake","she" }) );       
	set("race", "Ұ��");
	set("long", HIY"������С�ߡ�\n"NOR);
	set("limbs", ({ "ͷ��", "����", "�ߴ�", "β��" }) );
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
		write(ob->query("name")+"��Զ��ɭ�����Ѷ�ȥ��\n");
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
        	tell_object(owner, "�߲���ִ�д�ָ�\n");
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
				tell_object(owner, "�߲����˺����Լ�û����в�����࣡\n");
				return;
			}
		}
	}*/
	
//	set_name(HIY+owner->query("name")+"�Ľ���"NOR, ({ owner->query("id")+"'s jinshe"}) );
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
		write(HIR"����"+query("name")+HIR"�������Ѿ���ƣ�����ˣ�\n");
		die();
	}
	else if (query_temp("qushe/times")>=15)
	{
		write(HIY"����"+query("name")+HIY"�������ƺ���Щ���ˣ�\n");
		set_temp("qushe/ok",1);
	}
	else if (query_temp("qushe/times")>10)
	{
		write("����"+query("name")+"�ζ���΢��Щ�ٻ���\n");
	}else if (query_temp("qushe/times")>5)
	{
		write("����"+query("name")+"�ζ�Ѹ���ޱȣ�\n");
	}
	return ;
}
