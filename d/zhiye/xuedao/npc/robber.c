// Modify By River@SJ

inherit FIGHTER;
//inherit F_UNIQUE;
#include <ansi.h>

int do_kill(object me);
int do_kick(string target);

string *first_title = ({"江南陆家","江西花家","江北刘家","江东水家",});
string *second_title = ({ "大侠","弟子","剑侠","侠客","英雄","豪杰","赛孟尝","急公好义", "及时雨"});

void create()
{
	string title;
	
	title = first_title[random(sizeof(first_title))];
	title += second_title[random(sizeof(second_title))];
	

	set_name("无名氏",({"wuming shi"}));
		
	set("long","他神采飞扬，一副正气凌然的样子。\n");
	set("title", HIW+title+NOR);
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

/*	set_skill("huagu-mianzhang", 500);
	set_skill("strike", 500);
	set_skill("xinyuegong", 500);
	set_skill("taiji-shengong", 200);
	set_skill("sword", 500);
	set_skill("dodge", 500);
	set_skill("cuff", 500);
	set_skill("force", 500);
	set_skill("parry", 500);
	set_skill("blade", 500);
	set_skill("hammer", 500);
	set_skill("club", 500);
	set_skill("staff", 500);
	set_skill("whip", 500);
	set_skill("literate",500);
	set("env/no_protect", 1);
*/
/*	set_skill(s_sword, 500);
	set_skill(s_blade, 500);
	set_skill(s_club, 500);
	set_skill(s_whip, 500);
	set_skill(s_staff, 500);
	set_skill(s_dodge, 500);
	map_skill("force", "taiji-shengong");
	map_skill("sword", s_sword);
	map_skill("dodge", s_dodge);
	map_skill("parry", "taizuquan");
	map_skill("hammer", "xinyuegong");
	map_skill("blade", s_blade);
	map_skill("club", s_club);
	map_skill("whip", s_whip);
	map_skill("staff", s_staff);
	map_skill("strike", "huagu-mianzhang");
	prepare_skill("strike", "huagu-mianzhang");
	prepare_skill("cuff", "taizuquan");
*/
	setup();
/*	carry_object(BINGQI_D(weapon))->wield();*/
	carry_object(ARMOR_D("cloth"))->wear();
	add_money("silver", random(10)+20);
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
	if( interactive(ob = this_player())
		&&this_object()->query_temp("target")==ob->query("id")
		&&ob->query_temp("xd/xdzj_job"))
	{
		
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}
////调用可能来自fighter的函数
int do_kill(object ob)
{
	object me = this_object();
	if(!ob) return 0;
	//增加判断是否自己的npc
	if (me->query_temp("target")!=ob->query("id"))
		return notify_fail("他和你无冤无仇，你干嘛要乱杀无辜？\n");
	if (me->query_temp("kicked"))
	{  
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
		ob->set_temp("xd/xdzj_job_lost",1);
		ob->set("qi",100);																			//防止玩家意外死亡
		ob->set("jing",100);
		ob->set("jingli",100);
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

	if (ob->query_temp("xd/xdzj_job")){
		if (environment(me)->query("no_fight")) {
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
/*
void do_lost()
{
	object me,ob;
	me = this_object();
	ob = find_player(me->query_temp("target"));
	if(!ob) return;
	ob->set_temp("xd/xdzj_job_lost",1);
	tell_room(environment(me), "\n"+me->query("name")+"大喊一声：大侠我不奉陪了！转身几个起落就不见了。\n");
	destruct(me);
}

void unconcious()
{
	object me,ob;
	object* obs;
	int i;

	me = this_object();
	ob = find_player(me->query_temp("target"));
	obs = deep_inventory(me);	
	obs = filter_array(obs,(:$1->query("imbued"):));
	i = sizeof(obs);
	while(i--)
	{
		obs[i]->move(environment(me));
		message_vision("$N丢下"+obs[i]->name()+"。\n",me);
	}
	if (!ob) {
		destruct(me);
		return;
	}
	if (!present(ob)) {
		ob->set_temp("xd/xd_job_lost2",1);
		ob->set_temp("xd/xd_job_lost2_man",this_player()->query("name")+"("+this_player()->query("id")+")");
		tell_room(environment(me), "\n"+me->query("name")+"大喊一声：老子不奉陪了！转身几个起落就不见了。\n");
		destruct(me);
		return;
	}
	ob->set_temp("xd/xd_jobok",1);
	tell_room(environment(me), "\n"+me->query("name")+"大喊一声：不好！！转身几个起落就不见了。\n");	
	destruct(me);
}
void die()
{
	object me,ob;

	me = this_object();
	ob = find_player(me->query_temp("target"));
	if (!ob) {
		destruct(me);
		return;
	}
	if (!present(ob)) {
		ob->set_temp("xd/xd_job_lost2",1);
		ob->set_temp("xd/xd_job_lost2_man",this_player()->query("name")+"("+this_player()->query("id")+")");
		tell_room(environment(me), "\n"+me->query("name")+"大喊一声：老子不奉陪了！转身几个起落就不见了。\n");
		destruct(me);
		return;
	}
	
	ob->set_temp("xd/xd_jobok",1);
	::die();
}
*/
