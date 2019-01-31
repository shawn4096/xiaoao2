// By River@SJ
//Modify By Renlai@xa

inherit FIGHTER;
#include <ansi.h>

int do_kill(object me);

void create()
{
	string weapon;
	mapping name, skills;
	int i, j, p;

	i = random(4);

	name = RNAME_D->get_random_name(i);	
	set_name(name["name"], name["id"] + ({ "zhanglao" }));
	set("title", HIR"�Խ�ɽׯ��Ժ"NOR);
	set("gender", (i==0?"Ů��":"����"));
	set("age", 30 + random(40));
	set("long", "�����Խ�ɽׯ�������������书����\n");
	set("combat_exp", 10000000);
	set("meitude", "peaceful");
	set("str", 30);
	set("dex", 30);
	set("int", 30+random(5));
	set("con", 30);

	set("max_qi", 50000);
	set("max_jing", 50000);
	set("max_neili", 15000);
	set("neili", 15000);
	set("eff_jingli", 14000);
    weapon = "none";
	if (!random(4)) 
		weapon = "none";

	setup();

	if (weapon != "none")
		carry_object(BINGQI_D(weapon))->wield();
	
	    carry_object(ARMOR_D("cloth"))->wear();	    

	if (clonep())
		call_out("do_lost", 300);
}

void dest(object ob)
{
	if ( ob ) destruct(ob);
}

void init()
{
	object ob;       

	::init();
	if (interactive(ob = this_player())
	&& query_temp("target") == ob->query("id")) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

int do_kill(object ob)
{	
	object me; 
	me = this_object();
	if(!ob) return 0;	
	message_vision(HIR"\n$n����$N���һ������"+ RANK_D->query_rude(ob)+"���������Խ�ɽׯ���ң���\n\n"NOR,ob,me);
	::kill_ob(ob);
}

void greeting(object ob)
{
	if (!ob
	 || !present(ob)
	 || query_temp("target") != ob->query("id"))
		return;

	ob->add_busy(1);
	set_leader(ob);
	add_busy(1);
	do_kill(ob);
}

void do_lost()
{
	object me;
	me = this_object();
	tell_room(environment(me), CYN+"\n"+name()+"��һ���������Ӳ������ˣ���ת��������Ͳ����ˡ�\n"NOR);
	dest(me);
}

void unconcious()
{
	object me;
	me = this_object();

	tell_room(environment(me), CYN+"\n"+name()+"��һ���������ã�����ת��������Ͳ����ˡ�\n"NOR);
	dest(me);
}
