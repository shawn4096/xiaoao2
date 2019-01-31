// cool980310
// 段延庆
// cool980724
// Modify By River 98/12
// Modify by tangfeng@SJ
// 主要修改了标志的纪录方式；其他无修改

inherit NPC;
#include <ansi.h>
string ask_duan1();
string ask_duan2();
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
string ask_yiyang();

int do_kill(object me, object ob);

void create()
{
        set_name("青袍客", ({ "qingpao ke", "ke"}) );
        set("gender", "男性" );
        set("age", 52);
        set("str", 30);
        set("con", 30);
        set("dex", 30);
        set("int", 25);
        set("per", 10);
   		set("attitude", "friendly");

		set("max_qi", 30000);
		set("max_jing", 30000);
		set("eff_jingli", 30000);
        set("max_neili", 12000);
        set("neili", 12000);
		set("jiali", 150);
        
        set("long","这人是个老者，长须垂胸，面目漆黑。\n",);
		set("env/一阳指","三叠");
        set("combat_exp", 9400000+random(500000));
        set("shen", -8000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat",({ 
		(: perform_action, "finger.sandie" :), 
		(: perform_action, "finger.sanmai" :),
		(: perform_action, "finger.yizhisanmai" :),
	    }));

        set_skill("parry", 480);
        set_skill("dodge", 480);
        set_skill("force", 480);
        set_skill("finger", 480);
        set_skill("buddhism", 150);
        set_skill("literate", 300);
        set_skill("staff", 480);
        set_skill("duanjia-jianfa", 480);
        set_skill("qiantian-yiyang", 480);
        set_skill("yiyang-zhi", 480);
        set_skill("tianlong-xiang", 480);

		map_skill("dodge", "tianlong-xiang");
		map_skill("parry", "yiyang-zhi");
		map_skill("finger", "yiyang-zhi");
		map_skill("force", "qiantian-yiyang");
		prepare_skill("finger","yiyang-zhi");

		set("inquiry", ([
		"段誉" : (: ask_duan2 :),
		"name" : (: ask_duan1 :),
		"段延庆" : (: ask_duan1 :),
		"以剑代指绝技" : (: ask_yiyang :),
	]));

	setup();
	carry_object("/d/dali/npc/obj/pao")->wear();
}
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

string ask_yiyang()
{
     object me,ob;
	 int i,j;
     me=this_player();
     ob=this_object();
	 if( !me->query_temp("yanqing/killhuang") )
	 {
		return "你去替我把黄眉僧给我杀了，我就教你！\n";
	 }
	 if (me->query("family/family_name")!="天龙寺") 
	 {
		command("say 我虽然不是天龙寺弟子，但大理武功也不能轻易外传！\n");
		return "哼！";
	 }
	 if (me->query_skill("qiantian-yiyang",1)<200) 
	 {
		command("say 你的乾天一阳功不足200，用不了以剑代指！\n");
		return "哼！";
	 }
	 if( !me->query(QUESTDIR1+"over") )
	 {
		return "我不认识你，你先找到段誉这小子再说！";
	 }
	 
	 if (time()-me->query("quest/tls/djjf/yanqing/time")<86400)
	 {
			return "你来的太勤快了，懒得理你！";
	 }
	 if (me->query("quest/tls/djjf/yanqing/pass"))
	 {
			return "你已经解开了，别来烦我！";
	 }
	 if (me->query("shen")>-200000)
	 {
			return "你负神高于-200k,一看就不是心狠手辣之徒！";
	 }
	  j = 18;
      if(me->query("m-card-vip")) j =  16;
      if(me->query("y-card-vip")) j =  13;
      if(me->query("buyvip"))     j =  8;
	  if (me->query("class")=="bonze")
	     i=random(j+5);
	  else i= random(j);
	 
	 if(i<6 && random(me->query("kar"))>=20)
	 {
		tell_object(me,HIG"\n你按照段延庆的指点，对以剑带指的一阳指功夫真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIW"你按照段延庆所言，内息沿着经脉不断蓄积，忽然间“波”的一声，在剑端发出一声轻响。\n"NOR);
		tell_object(me,HIY"\n\n你历尽千辛挖苦，终于得偿所愿，将段家剑法中以剑代指绝技融汇贯通。\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/tls/djjf/yanqing/pass",1);
		me->set("title",HIR"恶"+RED"贯满盈传人"NOR);
		me->set("mytitle/quest/erentitle",RED"贯满盈传人"NOR);
		me->start_busy(1);
		me->delete_temp("yanqing");
		
		destruct(ob);
		log_file("quest/djjfyanqing", sprintf("%8s(%8s) 失败%d次后，彻底领悟以剑代指的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/tls/djjf/yanqing/fail"),i,me->query("combat_exp")) );
	    return "恭喜！恭喜！我大理复国又多了个得力助手！\n";
	 }
	 else
	 {
		me->add("quest/tls/djjf/yanqing/fail",1);
		me->set("quest/tls/djjf/yanqing/time",time());
		command("buddha ");
		tell_object(me,HIY"\n\n你听了段延庆的指点，虽然听见了以剑代指的奥秘，可是对以剑代指的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		me->delete_temp("yanqing");
		destruct(ob);

		log_file("quest/djjfyanqing", sprintf("%8s(%8s) 以剑代指解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/tls/djjf/yanqing/fail"),i,me->query("combat_exp")) );
		return "大理一阳指是我大理绝技，我大理复国能到猴年马月啊！\n";
	  }
    	
}

int accept_object(object who, object obj)
{
	
	object duan,me;
	duan =present("duan yanqing", who);
	me = this_player();
    

	if (me->query_temp("yanqing/askzhong")
		&& obj->query("name")=="黄眉和尚的首级"
		&& obj->query("kill_by")==who
		&& obj->query("id")=="shouji")
	{
		
		write(HIY"段延庆高兴滴蹦了起来，似乎对你的好感大增。\n"NOR);
		write(HIC"你把黄眉和尚的人头送给了段延庆！\n"NOR);
		obj->move(this_object());
		destruct(obj);
		command("pat "+who->query("id"));
		me->delete_temp("yanqing/askzhong");
		me->set_temp("yanqing/killhuang",1);
		return 1;
	}

	
}
