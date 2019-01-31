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
	set("max_jingli", 10000);
	set("eff_jingli", 10000);
	set("jingli", 10000);
	set("max_neili", 10000);
	set("neili", 10000);
	set("no_heal",1);
	set("no_ansuan",1);
    set("no_bark", 1);
	/*
	add_temp("apply/defense", 200);
	add_temp("apply/armor", 200);
	add_temp("apply/damage", 100);
*/
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
	if( interactive(ob = this_player())){
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}	
}

void greeting(object ob)
{
	object me = this_object();

	if (!ob
	 || !present(ob)
	 || me->query_temp("target") != ob->query("id"))
		return;

	if (ob->query_temp("ry/ry_job")){
		if (environment(me)->query("no_fight") || environment(me)->query("sleep_room")) {	
			  message_vision(HIR""+me->name()+"自言自语道：这里太狭小了。\n"NOR,ob);
				me->random_move();				
			
		} else {			
			if (ob->query_temp("ry/ry_job/杀"))
			{			
			 remove_call_out("dest");
			 call_out("dest", 600);
			 remove_call_out("do_kill");
			 call_out("do_kill", 0, ob);
			}
		}
	}
}

int do_kill(object ob)
{
	object me = this_object();
	if(!ob) return 0;
	
	message_vision(HIR""+me->name()+"对着$N发出一阵阴笑，说道：既然向问天派你这个" + RANK_D->query_rude(ob)+ "来了，那也就只能算你命短了！\n\n"NOR,ob);	
	remove_call_out("checking");
	call_out("checking", 2, me, ob);
	//::do_kill(ob);
	me->kill_ob(ob);
}

int checking(object me, object ob)
{
	int ret =  ::checking(me,ob);
	if(!ret) return 0;
	remove_call_out("checking");
	call_out("checking", 1, me, ob);
        if(!living(ob) && living(me) && me->query("jing")>0 && me->query("jingli")>0 && me->query("qi")>0  ){
		remove_call_out("checking");		
		tell_room(environment(me), "\n"+me->query("name")+"大笑道：向问天就派来这样的废物吗？转身几个起落就不见了。\n");
		destruct(me);
		 return 1;
	}	
}


void kill_ob(object ob)
{
	object me = this_object();
	
	if(!ob->query_temp("ry/ry_job") || (me->query_temp("target") != ob->query("id"))) {		
		
		me->set("eff_jing",me->query("max_jing"));
		me->set("jing",me->query("max_jing"));
		me->set("eff_qi",me->query("max_qi"));
		me->set("qi",me->query("max_qi"));
		me->clear_conditions_by_type("poison");
		command("say 我与你往日无冤，近日无仇！");
        me->kill_ob(ob);	
		return;
	}
	else command("say 是逆贼向问天派你来的吧！");	
	::kill_ob(ob);
}

void die()
{
	object me,ob;
	me = this_object();	
	if (me->query_temp("target"))
	{
	ob = find_player(me->query_temp("target"));
	if (ob->query_temp("ry/ry_job/请")) tell_room(environment(ob), "\n你把需要邀请的人杀死了，任务失败。\n");	
	}
	::die();
}


void dest()
{
	message_vision("$N好象突然想起什么事，急急忙忙的走开了。\n", this_object());
	destruct(this_object());
}
