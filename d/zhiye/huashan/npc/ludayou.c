// NPC: /d/huashan/npc/dayou.c
// Date: Look 99/03/25
// Modify By Looklove@SJ 2000/01/07 for add a job
// Lklv Modify at 2001.10.18

#include <ansi.h>
inherit NPC;
string ask_job();
inherit F_MASTER;

void create()
{
        set_name("陆大有", ({ "lu dayou", "lu", "dayou" }));
        set("nickname", "六猴儿");
        set("long",
"陆大有身材很瘦，又长的尖嘴猴腮的，但别看他其貌不扬，他在\n"
"同门中排行第六，是华山派年轻一代中的好手。\n");
        set("gender", "男性");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 13);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);

        set("max_qi", 6000);
        set("max_jing", 3800);
        set("neili", 5000);
        set("max_neili", 5000);
        set("eff_jingli", 3800);

        set("jiali", 150);
        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 250);
        set_skill("dodge", 250);
        set_skill("parry", 250);
        set_skill("sword", 250);
        set_skill("cuff", 250);
        set_skill("huashan-qigong", 250);
        set_skill("huashan-jianfa", 250);
        set_skill("huashan-shenfa", 250);
        set_skill("poyu-quan", 250);
        set_skill("zhengqi-jue", 250);
		set_skill("strike", 250);
		 set_skill("hunyuan-zhang", 250);

        map_skill("force", "huashan-qigong");
        map_skill("dodge", "huashan-shenfa");
        map_skill("parry", "huashan-jianfa");
        map_skill("sword", "huashan-jianfa");
		map_skill("strike", "hunyuan-zhang");
        map_skill("cuff", "poyu-quan");

        prepare_skill("cuff", "poyu-quan");

        create_family("华山派", 14, "弟子");

        set("inquiry", ([
              "砍柴" : (: ask_job :),
        ]));

        setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}


string ask_job()
{
        object ob, me, dao;
        me = this_player();

        if(me->query("family/family_name") != "华山派")
               return "你非我华山弟子，这些活还是不麻烦你了。";
        //if ((int)me->query("combat_exp") >= 30000)
        //if ((int)me->query("combat_exp") >= 2000000)
               // return "你武功已成，还是去给师傅帮忙吧。\n";
        if (me->query("shen") < 1000)
                return "你眼露凶光, 最近是不是做了什么坏事？ ";
        if (me->query_temp("hs/kc_job"))
                return "不是让你去砍柴了吗？怎么还不去？\n";
        if(me->query_condition("job_busy"))
               return "我现在很忙，你一会再来吧。";

        dao = present("chai dao", me);

        if (!dao){
	        ob=new(__DIR__"obj/chaidao");
        	ob->move(me);
        	tell_object(me, "陆大有给你一把柴刀。\n");
        }
        me->set_temp("hs/kc_job",1);
        me->apply_condition("job_busy", 6+random(6));
        command("ok "+me->query("id"));
        return "伙房的仆人来说，他那里现在缺柴禾做饭，你去朝阳峰砍些吧。\n";
}

void init()
{
        object me,ob;
        ::init();

        me = this_player();
        ob = this_object();

	    if (
			//interactive(ob) && 
			me->query_temp("jianzong/askyue")) {
		command("say 不好了，不好了，师父、师娘一回来，刚坐定还没几个时辰，就有好几个人拜山，嵩山、衡山、泰山三派中，都有人在内。\n ");
		command("say 除了这三个人外，还有三个人跟他们一起上来，说是咱们华山派的，当时令人诧异的是师父却不叫他们师兄、师弟。\n");
		command("say 一个人焦黄面皮，说是姓封，叫甚么封不平。还有一个是个道人，另一个则是矮子，都叫‘不’甚么的，倒真是‘不’字辈的人。\n");
		command("say 他们都在玉女峰呢，你赶紧过去看看吧，形势很危急。\n");
		message_vision(HIY"\n\n\n$N听到陆大友如此说法，不禁心中一愣，心想，”他们到底是谁？是不是过去看看？“\n"NOR,me);
		me->delete_temp("jianzong/askyue");	
		me->set_temp("jianzong/asklu",1);	
		return ;
	  }
}
void attempt_apprentice(object ob)
{
       
        if (ob->query("shen") < 20000 ) 
		{
		command("say 我华山派乃是堂堂名门正派，对弟子要求极严,不足20k不要来找我。");
		command("say 在德行方面，" + RANK_D->query_respect(ob) + "是否还做得不够？");
		return;
        }
        if (ob->query_skill("huashan-qigong",1)<150)
        {
			command("say 我华山剑派最重气功，你的华山气功如此差，不足150，别来烦我！");
			return;
        }
        command("say 好吧，我就收下你了,你可要为我们华山派争口气。");
        command("chat* 脸上浮现出一丝笑容，对着"+ob->query("name")+"笑道：我华山定将成为五岳之首。");
        command("recruit " + ob->query("id"));
        ob->set("quest/huashan","气宗");
}
