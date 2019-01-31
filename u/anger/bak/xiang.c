// xiang.c 向问天
// Finish by action@SJ 2009.1.6
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_jiuwen();

void create()
{
        set_name("向问天", ({ "xiang wentian", "xiang", "wentian"}));
        set("long", "只见他容貌清瘦，身形高大，颏下疏疏朗朗一丛花白长须，垂在胸前，\n"+
		"背上负着一个包袱，再看他腰间时，却无弯刀。\n");
        set("title",HIY"日月神教 "HIW"光明左使"NOR);
        set("gender", "男性");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 4000);
        set("max_jing", 5200);
        set("eff_jingli", 5500);
        set("jiali", 200);
        set("combat_exp", 9400000);

        set_skill("strike", 460);
        set_skill("blade", 220);
        set_skill("club", 460);
        set_skill("parry", 460);
        set_skill("dodge", 460);
        set_skill("force", 460);
        set_skill("literate", 160);

        set_skill("tianmo-gun",460);
        set_skill("tianmo-zhang",460);
        set_skill("tianmo-dao",200);
        set_skill("huanmo-wubu",460);
        set_skill("tianmo-gong",460);
        set_skill("tianmo-jue",200);

        map_skill("force", "tianmo-gong");
        map_skill("parry", "tianmo-gun");
        map_skill("blade", "tianmo-dao");
        map_skill("club", "tianmo-gun");
        map_skill("dodge", "huanmo-wubu");
        map_skill("strike", "tianmo-zhang");

        prepare_skill("strike", "tianmo-zhang");
        set("inquiry", ([
                 //"秘密" : (: ask_mimi :),
		         "旧闻" : (: ask_jiuwen:),
			     //"金猿神魔" : (: ask_jinyuan:),
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
		        "向问天拿起酒壶，灌了一大口，道：“好酒！”\n",
					"哼哼，梅庄四友....哪儿究竟隐藏着什么秘密呢？”\n",
					"令狐冲那小子有点意思。”\n",
					"可惜，我日月十大长老围攻华山，一去不回，到底发生了什么事？。”\n",
					"我大日月的核心武技遗失不少，否则焉有左老儿的横行霸道！”\n",
        }));
        create_family("日月神教", 6, "长老");
        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: perform_action, "club.luanwu" :),
				(: perform_action, "club.zhenfeng" :),
                (: exert_function, "tianmo" :),
        }));
		
        setup();

        carry_object(MISC_D("cloth"))->wear();  
        carry_object(BINGQI_D("club"))->wield();      
}

void attempt_apprentice(object ob)
{
     if(ob->query_skill("tianmo-gong",1) < 350 ||
      ob->query_skill("tianmo-zhang",1) < 350 ||
        ob->query_skill("tianmo-dao",1) < 350){
        command("say 你的武功还不够娴熟，再回去练练吧。");
        return;
        }
     command("say 好，我正想招兵买马救教主出来，看来你还不错嘛，就收下你了。");
     command("recruit " + ob->query("id"));
     ob->set("title","日月神教光明左使座下堂主");
}


int ask_jiuwen()
{
     object me=this_player();
     if (me->query("family/family_name")!="日月神教")
         return notify_fail("你不是我神教弟子来此瞎打听作甚？\n");

	 if (me->query_skill("tianmo-gong",1)<449)
		 return notify_fail("你的天魔功力太弱，不足450，还是好好练功去吧。");
     
	
		
		 command("say 我曾听任教主提到，十大长老围攻华山之战役，不知为何竟然全部失踪。\n");
		 command("think ");
		 command("say 那时候我神教英雄辈出，金猿神魔张乘风、张乘云兄弟，一套天魔棍法横扫天下。\n");
		 command("say 还有大力神魔范松长老的大力神魔斧更是威震江湖。\n");
		 command("sigh ");
		 command("say 谁要是能帮我找到黑木令，我就告诉他真相。\n");
		 command("heng ");
		 me->set_temp("hssb/askxiang",1);
		 return 1;
		 //command("");
		//随即 选择需要礼物，然后满意了就告诉他去华山。。
}

int accept_object(object who, object obj)
{
	object me;
	obj =present("heimu ling", who);
	me = this_player();
    if (!me->query_temp("hssb/askxiang")) {
	    command("say 你弄些乱七八糟的东西糊弄我？\n");	
		return 1;
    }

	if (me->query_temp("hostage/linggived")&& obj->query("id")=="heimu ling")
	{
		//me->set_temp("hostage/job_1",2);
		
		me->delete_temp("hostage/linggived");
		write(HIY"向问天将这块黑木令拿在手中翻来覆去的看着。\n"NOR);
        write(CYN"向问天在哪儿自言自语起来，脸上亦喜亦忧。\n"NOR);
		
		command("say 既然你替我找到了这块黑木令，那我就把这个消息告诉你。\n");
		command("say 十大长老围攻华山一去不回，我怀疑他们中了对方的奸计。\n");
		command("say 也就说，如果你去华山后山附近转悠转悠说不定有什么惊人的发现。\n");
		command("say 不过生死有命，富贵在天，我看你还是随缘的好。凡事不必强求。\n");
		me->set_temp("hssb/juejiasked",1);
		destruct(obj);
		return 1;
	}else {
        command("say 你瞎折腾什么？\n");
	    return 0;
	}

}