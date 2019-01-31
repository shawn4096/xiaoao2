// Modify By River@SJ
//Modify By Renlai@xa

inherit FIGHTER;
//inherit F_UNIQUE;
#include <ansi.h>

int do_kill(object me);
int do_kick(string target);

string *first_title = ({"青龙堂","白虎堂","朱雀堂","玄武堂","梅庄","光明左使座下","光明右使座下","总坛"});
string *second_title = ({ "舵主","香主","门主","长老","堂主","旗主", "朝奉"});

void create()
{
	string title;
	
	title = first_title[random(sizeof(first_title))];
	title += second_title[random(sizeof(second_title))];
	set_name("无名氏",({"wuming shi"}));
		
	set("long","这家伙一付凶神恶煞的模样。\n");
	set("title", HIW+title+NOR);
	set("age", 30 + random(30));
	
	set("combat_exp", 8000000);
	set("meitude", "peaceful");
	set("str", 30);
	set("dex", 30);
	set("int", 30);
	set("con", 30);
	set("max_qi", 30000);
	set("max_jing", 20000);
	set("max_neili", 10000);
	set("neili", 10000);
	set("no_heal",1);
	set("no_ansuan",1);
    set("no_bark", 1);
	
	add_temp("apply/defense", 200);
	add_temp("apply/armor", 200);
	add_temp("apply/damage", 100);

	setup();
	carry_object(ARMOR_D("yexing-yi"))->wear();	
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :)
	}) );
	if (clonep())
		call_out("dest", 900);
}
void init()
{
	object ob;
	::init();
	//add_action("do_kick","kick");   
/*	if( interactive(ob = this_player())){
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
	*/
}

void kill_ob(object ob)
{
	object me = this_object();
	
	if(!ob->query("ry/ry_job")) {		
		
		me->set("eff_jing",me->query("max_jing"));
		me->set("jing",me->query("max_jing"));
		me->set("eff_qi",me->query("max_qi"));
		me->set("qi",me->query("max_qi"));
		me->clear_conditions_by_type("poison");
		command("say 我与你往日无冤，近日无仇！");	
		return;
	}
	else command("say 是向问天派你来的吧！");	
	::kill_ob(ob);
}


void dest()
{
	message_vision("$N好象突然想起什么事，急急忙忙的走开了。\n", this_object());
	destruct(this_object());
}
