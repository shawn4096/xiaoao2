// xinguan.c 心观大师

//先从少林入手
#include <ansi.h>

inherit NPC;
//inherit F_MASTER;

string ask_me();

void create()
{
        object ob;
        set_name("心观大师", ({
                "xinguan dashi",
                "xinguan",
                "dashi",
        }));
        set("long",
				"他是宁波天童寺主持心观大师，一身慈悲刀法闻名江湖，是江湖中出\n"
                "了名的善人，他白须白眉，身穿一袭银丝棕黄袈裟。他身材极瘦，\n"
                "两手更象鸡爪一样。他双目微闭，一副没精打采的模样。\n"
        );


        set("nickname", HIY"天童寺主持"NOR);
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 28000);
        set("max_jing", 10000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 200);
        set("combat_exp", 8000000);
        set("score", 500000);

        set_skill("force", 450);
        set_skill("yijin-jing", 450);
        set_skill("dodge", 450);
        set_skill("shaolin-shenfa", 450);
        set_skill("parry", 450);
        set_skill("claw", 450);
        set_skill("blade", 450);
        set_skill("finger", 450);
        set_skill("cibei-dao", 450);
        set_skill("yizhi-chan", 450);
        set_skill("longzhua-gong", 450);
        set_skill("buddhism", 150);
        set_skill("literate", 250);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("claw", "longzhua-gong");
        map_skill("finger", "yizhi-chan");
        map_skill("blade", "cibei-dao");
        map_skill("parry", "cibei-dao");

        prepare_skill("finger", "yizhi-chan");
        prepare_skill("claw", "longzhua-gong");

      //  create_family("少林派", 36, "弟子");

        set("inquiry", ([
                "慈悲刀绝技"       : (: ask_me :),
           //     "罗汉大阵"         : (: ask_me :)
        ]));

        setup();
        if (clonep()) {                
                ob = unew(BINGQI_D("blade"));               
                if (!ob) ob = unew("/clone/weapon/blade");
                ob->move(this_object());
                ob->wield();
                carry_object("/d/shaolin/obj/xuan-cloth")->wear();
        } 
}


int ask_me()
{
	int i,j;
	object me=this_player();

	if (!me->query_temp("cbd/askxuanbei"))
	{
		command("say 你和我无冤无仇，为何总是来此骚扰老僧！\n");
		return 1;
	}
	if (me->query("quest/sl/cbd/pass"))
	{
		command("say 你已经修习了慈悲刀绝技，不要来此骚扰老僧了！\n");
		me->set("title",YEL"天童寺慈悲刀传人"NOR);
		me->set("mytitle/quest/ttscbdtitle",YEL"天童寺慈悲刀传人"NOR);
		return 1;
	}
	if (time()-me->query("quest/sl/cbd/time")<86400)
	{
		command("say 你太勤宽了，老僧我不堪骚扰！\n");
		return 1;
	}
	j = 18;
    if(me->query("m-card-vip")) j =  16;
    if(me->query("y-card-vip")) j =  13;
    if(me->query("buyvip"))     j =  8;
	if (me->query("class")=="bonze")
	     i=random(j-2);
	  else i= random(j);
 
    if(i<3 && random(me->query("kar"))>=25)
	 {
		tell_object(me,HIG"\n你按照心观大师的指点，对慈悲刀法的真正奥妙似乎有些心得。\n"NOR);
       
		tell_object(me,HIY"\n你历尽千辛万苦，终于得偿所愿，将慈悲刀法融汇贯通。\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/sl/cbd/pass",1);
		me->set("title",YEL"天童寺慈悲刀传人"NOR);
		me->set("mytitle/quest/ttscbdtitle",YEL"天童寺慈悲刀传人"NOR);
		me->start_busy(1);
		log_file("quest/slcibeidao", sprintf("%8s(%8s) 失败%d次后，彻底领悟慈悲刀法的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/sl/cbd/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/sl/cbd/fail",1);
		me->set("quest/sl/cbd/time",time());
		command("buddha ");
		tell_object(me,HIY"你听了心观大师的指点，虽然听见了慈悲刀法的奥秘，可是对慈悲刀法功的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/slcibeidao", sprintf("%8s(%8s) 慈悲刀法解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/sl/cbd/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;

  

}

