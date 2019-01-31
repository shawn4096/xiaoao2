// Modify By River@SJ

inherit FIGHTER;
//inherit F_UNIQUE;
#include <ansi.h>

int do_kill(object me);
int do_kick(string target);


//string *first_title = ({"华山派","武当派","少林派","天龙寺","丐帮","峨嵋派","全真教","桃花岛"});
string *second_title = ({ "大侠","侠客","亲传弟子","嫡传弟子","长老","精英弟子", "高手"});

void create()
{
	string title;
	
	//title = first_title[random(sizeof(first_title))];
	title=WHT"星宿叛徒"NOR;
	//title=title+this_object()->query("family/family_name");
	//title += second_title[random(sizeof(second_title))];
	set_name("无名氏",({"wuming shi"}));
		
	set("long","这家伙一付道貌岸然的模样，面色平静，时不时面露微笑。\n");
	set("title", title);
	set("age", 20 + random(50));
	
	set("combat_exp", 8000000);
	set("meitude", "peaceful");
	set("str", 25);
	set("dex", 30);
	set("int", 30);
	set("con", 30);
	set("max_qi", 20000);
	set("max_jing", 20000);
	set("max_neili", 5000);
	set("neili", 5000);
	set("no_heal",1);
	set("no_ansuan",1);
    	set("no_bark", 1);

	setup();
/*	carry_object(BINGQI_D(weapon))->wield();*/
	carry_object(ARMOR_D("cloth"))->wear();
	add_money("silver", random(10)+50);
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :)
	}) );
	if (clonep())
		call_out("dest", 800);
}
void init()
{
	object ob;
	::init();
	add_action("do_kick","kick");   
	if( interactive(ob = this_player())){
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}
////调用可能来自fighter的函数
int do_kill(object ob)
{
	object me = this_object();
	if(!ob) return 0;
	if (me->query_temp("kicked")) {  
		message_vision(HIR""+me->name()+"对$N说道：" + RANK_D->query_rude(ob) +"！穷追不舍，既然逃不掉，"+RANK_D->query_self_rude(me) +"跟你拼了！\n\n"NOR,ob);
		me->delete_temp("kicked");
	} else if (me->query_temp("fight_failed")) {
		message_vision(HIR""+me->name()+"对着$N说道：嘿嘿！有胆敢跟过来，"+RANK_D->query_self_rude(me) +"不客气了！\n\n"NOR,ob);
		me->delete_temp("fight_failed");
	} else 
		message_vision(HIR""+me->name()+"对着$N发出一阵阴笑，说道：既然被你这个" + RANK_D->query_rude(ob)+ "撞见了，那也就只能算你命短了！\n\n"NOR,ob);
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
		ob->set_temp("xx/xx_job_lost",1);
		//ob->set("qi",100);																			//防止玩家意外死亡
		//ob->set("jing",100);
		//ob->set("jingli",100);
		tell_room(environment(me), "\n"+me->query("name")+"大喊一声：老子不奉陪了！转身几个起落就不见了。\n");
		destruct(me);
		 return 1;
	}
	if(!ob || environment(ob)!= environment(me)){
		remove_call_out("checking");
		 remove_call_out("do_lost");
		 call_out("do_lost",0);
		 return 1;
	}
}

void greeting(object ob)
{
	object me = this_object();

	if (!ob
	 || !present(ob)
	 || me->query_temp("target") != ob->query("id"))
		return;

	if (ob->query_temp("xx/xx_job")){

		if (environment(me)->query("no_fight") || environment(me)->query("sleep_room")) {
			me->delete_temp("fight_failed");
			me->delete_temp("kicked");
			if (random(2)==0) {
				message_vision(HIR""+me->name()+"看见$N走过来，神色有些异常，赶忙低下了头。\n"NOR,ob);
				tell_object(ob, HIR"你忍不住想狠狠踢(kick)这个家伙一脚。\n"NOR);
			} else {
				message_vision(HIR""+me->name()+"对着$N发出一阵阴笑，说道："+ RANK_D->query_rude(ob)+ "，这里地方太小，有种跟"+ RANK_D->query_self_rude(me) +"到外面比划比划！\n\n"NOR,ob);
				me->random_move();				
			}
			me->set_temp("fight_failed",1);
		} else {		
			ob->add_busy(1);
			me->start_busy(1);
			//remove_call_out("checking");
			//call_out("checking", 1, me, ob);
			remove_call_out("dest");
			call_out("dest", 600);
			remove_call_out("do_kill");
			call_out("do_kill", 0, ob);
		}
	}
}

int do_kick(string target)  
{
	object me = this_object();
	object ob = this_player();
	if (target && present(target, environment()) == me) {	
		if (!me->query_temp("fight_failed")) return 0;	

		message_vision(HIR"$N对着"+me->name()+"一脚踢过去："+ RANK_D->query_rude(me) +"，看你往哪里躲！"+me->name()+"见势不妙，奋力一挣，向外逃窜。\n\n"NOR,ob);
		
		me->random_move();
		me->delete_temp("fight_failed");
		me->set_temp("kicked",1);
		return 1;
	} else {
		return 0;
	}
}

void dest()
{
	destruct(this_object());
}

void do_lost()
{
	object me,ob;
	me = this_object();
	ob = find_player(me->query_temp("target"));
	if(!ob) return;
	ob->set_temp("xx/xx_job_lost",1);
	tell_room(environment(me), "\n"+me->query("name")+"大喊一声：老子不奉陪了！转身几个起落就不见了。\n");
	destruct(me);
}
/*
void unconcious()
{
	object me,ob;

	me = this_object();
	ob = find_player(me->query_temp("target"));
	if (!ob) {
		destruct(me);
		return;
	}
	if (!present(ob)) {
		ob->set_temp("xx/xx_job_lost2",1);
		ob->set_temp("xx/xx_job_lost2_man",this_player()->query("name")+"("+this_player()->query("id")+")");

		tell_room(environment(me), "\n"+me->query("name")+"大喊一声：老子不奉陪了！转身几个起落就不见了。\n");
		destruct(me);
		return;
	}
	
	ob->set_temp("xx/xx_jobok",1);
	::die();
}
*/

void die()
{
	object me,ob;

	me = this_object();
	me->interrupt_me();
	ob = find_player(me->query_temp("target"));
	if (!ob) {
		destruct(me);
		return;
	}
	ob->delete_temp("xx/ob");//这里删除npc对象 by renlai	
	tell_room(environment(me), "\n"+me->query("name")+"大喊一声：老子不奉陪了！转身几个起落就不见了。\n");
	ob->set_temp("xx/xx_jobok",1);
	//::die();
	destruct(me);
}
