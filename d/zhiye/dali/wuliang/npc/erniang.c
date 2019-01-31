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
        set_name("叶二娘", ({ "ye erniang", "ye","erniang"}) );
		set("title",HIW"无"HIR"恶"HIW"不作"NOR);
        set("gender", "女性" );
		//set("nickname","岳老二");
        set("age", 42);
        set("str", 30);
        set("con", 30);
        set("dex", 40);
        set("int", 25);
        set("per", 10);
   		set("attitude", "peaceful");

		set("max_qi", 25000);
		set("max_jing", 4000);
		set("eff_jingli", 4000);
        set("max_neili", 15000);
        set("neili", 15000);
		set("jiali", 190);
        
        set("long","她的左右脸颊上各有三道血痕，虽然在笑，但她的笑容之中似乎隐藏着无穷愁苦、无限伤心，让人心中对她充满了同情。\n",);
		//set("env/一阳指","三叠");
        set("combat_exp", 9000000+random(500000));
        set("shen", -180000);

        set("chat_chance_combat", 60);
        set("chat_msg_combat",({ 
			(: perform_action, "blade.daozhang" :), 
			(: exert_function, "huntian" :),
	    }));

        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("force", 450);
        set_skill("strike", 450);
        set_skill("tiezhang-zhangfa", 450);
        set_skill("literate", 200);
        set_skill("blade", 450);
        set_skill("liuye-daofa", 450);
        set_skill("shuishangpiao", 450);
        set_skill("guiyuan-tunafa", 450);
        //set_skill("tianlong-xiang", 450);

		map_skill("dodge", "shuishangpiao");
		map_skill("parry", "liuye-daofa");
		map_skill("blade", "liuye-daofa");
		map_skill("force", "guiyuan-tunafa");
		map_skill("strike","tiezhang-zhangfa");
		prepare_skill("strike","tiezhang-zhangfa");
		set("chat_chance_combat", 70);
		set("chat_msg_combat",({
			(: perform_action, "blade.daozhang" :),
			(: perform_action, "strike.qinna" :),
			(: perform_action, "strike.heyi" :),
			(: exert_function, "guiyuan" :)
		}));

		set("inquiry", ([
			//"段誉" : (: ask_duan2 :),
		//"name" : (: ask_duan1 :),
		//"段延庆" : (: ask_duan1 :),
		]));

	    setup();
	    carry_object("/clone/weapon/blade")->wield();
	    carry_object("/d/dali/obj/blackcloth")->wear();
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

	//me->set_name("段延庆", ({ "duan yanqing", "duan","yanqing"}) );
	//me->set("title",HIC"四大恶人"NOR);
	//me->set("nickname",HIG"恶贯满盈"NOR);
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