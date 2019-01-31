//yunzhonghe.c 云中鹤
// cre by sohu

inherit NPC;
#include <ansi.h>
string ask_duan1();
string ask_duan2();
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"

int do_kill(object me, object ob);

void create()
{
        set_name("云中鹤", ({ "yunzhong he", "he"}) );
		set("title",HIW"穷凶极"HIR"恶"NOR);
        set("gender", "男性" );
        set("age", 42);
        set("str", 20);
        set("con", 20);
        set("dex", 40);
        set("int", 25);
        set("per", 10);
   		set("attitude", "peaceful");

		set("max_qi", 20000);
		set("max_jing", 4000);
		set("eff_jingli", 4000);
        set("max_neili", 12000);
        set("neili", 12000);
		set("jiali", 170);
        
        set("long","这人是个长脸瘦高个的中年人，面色蜡黄，一双眼睛极为淫荡，往那一站，似乎是一个竹竿子。\n",);
		//set("env/一阳指","三叠");
        set("combat_exp", 8000000+random(500000));
        set("shen", -180000);

        set("chat_chance_combat", 40);
        set("chat_msg_combat",({ 
		(: perform_action, "staff.feizhang" :), 
		(: exert_function, "huntian" :),
	    }));

        set_skill("parry", 420);
        set_skill("dodge", 420);
        set_skill("force", 420);
        set_skill("strike", 420);
        set_skill("lianhua-zhang", 420);
        set_skill("literate", 100);
        set_skill("staff", 420);
        set_skill("fengmo-zhang", 420);
        set_skill("xiaoyaoyou", 420);
        set_skill("huntian-qigong", 420);
        //set_skill("tianlong-xiang", 450);

		map_skill("dodge", "xiaoyaoyou");
		map_skill("parry", "fengmo-zhang");
		map_skill("staff", "fengmo-zhang");
		map_skill("force", "huntian-qigong");
		prepare_skill("strike","lianhua-zhang");
/*
		set("inquiry", ([
		"段誉" : (: ask_duan2 :),
		"name" : (: ask_duan1 :),
		"段延庆" : (: ask_duan1 :),
	]));
*/
	    setup();
	    carry_object("/clone/weapon/gangzhang")->wield();
	    carry_object("/d/dali/npc/obj/pao")->wear();
}
/*
 void init()
{       
        object me,ob;
        ob = this_player(); 
        me = this_object();
        ::init();
        if( interactive(ob)
          && ob->query_temp(QUESTDIR1+"kill")){
         me->query("kill_id",ob->query("id"));
         call_out("kill_ob",1, ob); 
         }
}

string ask_duan1()
{
	object me,ob;
	ob=this_player();
	me=this_object();

	me->set_name("段延庆", ({ "duan yanqing", "duan","yanqing"}) );
	me->set("title",HIC"四大恶人"NOR);
	me->set("nickname",HIG"恶贯满盈"NOR);
	if(!ob->query_temp(QUESTDIR1+"kill")) ob->set_temp(QUESTDIR1+"ask1",1);
	return "老夫便是四大恶人中的老大：段延庆！";
}

string ask_duan2()
{
        object me,ob;
        ob=this_player();
        me=this_object();

	if( !ob->query(QUESTDIR1+"over") && ob->query(QUESTDIR1+"pass_shanlu") && ob->query_temp(QUESTDIR1+"ask1")) {
		command("hehe " + ob->query("id"));
		me->set("kill_id",ob->query("id"));
		call_out("do_kill", 1, me, ob);
		return "想救段誉？送死来了！";
	}
	else return "你问这个干什么？";
}

int do_kill(object me, object ob)
{
	me->kill_ob(ob);
	ob->fight_ob(me);
	call_out("checking", 0, me, ob);
 	return 1;
}

void checking(object me, object ob)
{
	if (!ob) return;
	if (!me) return;
	if (!ob->query_temp(QUESTDIR1+"kill")) {
		if (me->query("qi")*10/me->query("max_qi") < 5 
		|| me->query("eff_qi")*10/me->query("max_qi") < 5 ){
			ob->set_temp(QUESTDIR1+"kill",1);
			message_vision(HIR"$n看见$N向后一跳，逃向一片大树林。\n"NOR, me, ob);
			message_vision(HIG"$n大声喝道：哪里跑！$n紧紧追了过去。\n"NOR, me, ob);
			ob->move("/d/dali/wuliang/shanlin-1");
			destruct(me);
		}
		else 
			call_out("checking", 1, me, ob);
	}
}

void die()
{
	  object me;
	  object ob=this_object();
      if ( ob->query("kill_id")
                  && userp(me=present(ob->query("kill_id"),environment(ob)))
		  && me->query(QUESTDIR1+"pass_shanlu") 
		  && !me->query_temp(QUESTDIR1+"kill")
		  && !me->query(QUESTDIR1+"over")) {
		me->set("quest/天龙八部/time", time());
		me->set("quest/天龙八部/combat_exp", me->query("combat_exp"));
		me->delete_temp("quest/天龙八部");
		me->delete_temp("quest/busy");
		log_file("quest/TLBB", sprintf("%s(%s) 砍死段延庆，失败。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
		command("sneer");
		message_vision(HIR"\n$N惨笑道：你杀了我，这辈子别想找到段誉了。\n"NOR, this_object());
		tell_object(me,HIG"\n看来，营救的事情只能由其他人完成，你还是暂时回避一下。\n"NOR);
	}
	::die();
}

void unconcious()
{
	die();
}
*/