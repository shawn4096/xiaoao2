// madayuan.c 马大元
// 
// by sohu@xojh
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "begger.h";
string ask_suohou();
int ask_xiaofeng();


void create()
{
        set_name("马大元", ({ "ma dayuan", "ma"}));
        set("title", HIW"副帮主"NOR);
        set("gb/bags",9);
        set("gender", "男性");
        set("age", 47);
        set("long", "这人是丐帮中的副帮主，人缘极好。\n"
        	    "善于使用锁喉手绝技，驰名江湖。\n");
        set("attitude", "peaceful");
        set("unique", 1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        set("qi", 12400);
        set("max_qi", 12400);
        set("jing", 6000);
        set("max_jing", 6000);
	set("eff_jingli", 6000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 200);
        set("combat_exp", 6500000);

        set_skill("force", 400);
        set_skill("huntian-qigong", 400);
        set_skill("dodge", 400);
        set_skill("xiaoyaoyou", 400);
        set_skill("parry", 400);
        set_skill("hand", 450);
        set_skill("suohou-shou",450);
        set_skill("begging", 90);

        map_skill("force", "huntian-qigong");
        map_skill("parry","suohou-shou");
        map_skill("strike","lianhua-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("hand", "suohou-shou");
        prepare_skill("hand", "suohou-shou");
    	set("chat_chance_combat", 90);
    	set("chat_msg_combat", ({
        	(: perform_action, "hand.suohou" :),
        	(: perform_action, "hand.qinna" :),
        	(: exert_function, "huntian" :),
        }));

        create_family("丐帮", 18, "九袋长老");

        set("inquiry", ([
                "丐帮" : "我们丐帮是天下第一大帮！\n",
                "乔峰" : "他不就是萧峰，我们的前任帮主。\n",
				"锁喉擒拿绝技" : (: ask_suohou :),
        ]));
        setup();
        carry_object(ARMOR_D("bainayi"))->wear();
        carry_object(ARMOR_D("shoes"))->wear();
        carry_object(__DIR__"obj/gb_budai9")->wear();
}

void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "丐帮") {
                command("say 你还是去别的门派看看吧。");
                return;
        }
        if ((int)ob->query("gb/bags") >= 2
         && ob->query("family/family_name") != "丐帮" ) {
                command("say 丐帮可容不下你这种背信弃义的小人！");
                command("kill "+ob->query("id"));
                return;
        }
        if ((int)ob->query("gb/bags") < 3 ) {
                command("say 你在帮中的资历尚浅，过些日子再说吧！");
                return;
        }
        if ( ob->query("shen") <0 || ob->query("shen") < ob->query("combat_exp")/2) {
                command("say 想拜我为师，再多做侠义的事吧。");
                return;
        }
        command("say 好吧，希望" + RANK_D->query_respect(ob) +
        "能好好学习本门武功，将来在江湖中闯出一番作为。");
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf(HIR"丐帮刑堂%s袋弟子"NOR,
                chinese_number(ob->query("gb/bags"))) );
        ob->set("gb/fenduo","刑堂");
        ob->set("class","beggar");
}

string ask_suohou()
{
        object me;
		int i,j,k;
        me = this_player();

        if ( me->query("family/family_name") != "丐帮")
                return RANK_D->query_respect(me) +
                "非我丐帮好汉，不知此话从何谈起？";

        //if ( me->query("family/master_name")!="白世镜" && me->query("family/master_name")!="洪七公" )

			//return RANK_D->query_respect(me) +
               // "不是我刑堂弟子，何出此言？";
		if (me->query_skill("suohou-shou",1)<200)
		{
			return "你的锁喉手等级太低，不足200，告诉你也理解不了。\n";
		}
        if ( me->query("quest/gb/shs/qinna/pass"))
        	return "你已经学会了锁喉！\n？";

        if (time()-me->query("quest/gb/shs/qinna/time")<86400)
                return RANK_D->query_respect(me) +
                "你来的太频繁了！\n";

        //list = filter_array(objects(), (: $1->query("id")=="fa dao":));
        
		command("consider ");
		command("say 这三十六路锁喉擒拿乃是我成名江湖的绝技\n");
		command("say 一旦施展出来，招招不离对方要害。\n");
		command("say 一门攻击技是“锁喉绝技”，一招捏碎对方咽喉，置对方于死地\n");
		command("say 一门就是擒拿术了\n");
		command("say 看你如此有为，我就传授于你，望你好生珍惜这门神技，不要霍乱江湖！\n");
	
        j = 15;
        if(me->query("m-card-vip")) j =  13;
        if(me->query("y-card-vip")) j =  10;
        if(me->query("buyvip"))     j =  5;
	    i=random(j);
	

	//越聪明学习越快。。。
		k=random(me->query("kar"));
		if (me->query("kar")<31
			&&k>=23
			&&i<3)
		{
			message_vision(HIR"\n\n恭喜你！你终于领悟了锁喉擒拿绝技的精髓武技，习得锁喉擒拿手绝技。\n"NOR,me);
			command("chat* haha"+me->query("id"));
			command("chat "+me->query("name")+"用了这么长时间终于领悟了“锁喉擒拿手绝技”，可喜可贺。");
			command("chat "+"我丐帮又多了一条好汉。");
			command("chat* congra"+me->query("id"));
	  
	   log_file("quest/suohoushou",sprintf("%s(%s)受马大元点播，领悟锁喉擒拿手绝技。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),k,j,me->query("quest/gb/shs/qinna/fail"),me->query("combat_exp"),me));
	   
	   me->set("quest/gb/shs/qinna/pass",1);
	   //me->set("title",HIY"NOR);
	   return "锁喉擒拿手，一旦习得，扬名江湖！\n";
	}
	else
	{
		message_vision(HIC"\n\n$N虽然听马大元说了锁喉手的精要，但对于如何使用的劲力法门一时之间却是难以理解。\n"
		+"锁喉手威力并没有发挥出来，看来你还是有待于重新跟马大元请教了。\n"NOR,me);
		log_file("quest/suohoushou",sprintf("%8s%-10s得到马大元的亲自指点锁喉擒拿手，但并没有成功，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),k,j,me->query("quest/gb/shs/qinna/fail"),me->query("combat_exp"),me));
		me->add("quest/gb/shs/qinna/fail",1);
		me->set("quest/gb/shs/qinna/time",time());
		return "我原来一直以为我是最笨的，没想到你比我更笨！\n";
	}  
   
}
