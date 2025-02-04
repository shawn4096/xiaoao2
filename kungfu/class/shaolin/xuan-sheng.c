// By Spiderii

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_yjj();
int ask_tztg();

void create()
{
        object ob;
        set_name("玄生大师", ({
                "xuansheng dashi",
                "xuansheng",
                "dashi",
        }));
        set("long",
                "他是一位白须白眉的老僧，身穿一袭银丝棕黄袈裟。他身材瘦高，\n"
                "太阳穴微微突起，坐在铺垫上参禅。\n"
        );


        set("nickname", "证道院首座");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 25000);
        set("max_jing", 7000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 200);
        set("combat_exp", 12500000);
        set("score", 500000);

        set_skill("force", 450);
        set_skill("yijin-jing", 450);
        set_skill("dodge", 450);
        set_skill("shaolin-shenfa", 450);
        set_skill("parry", 450);        
        set_skill("strike", 450);
        set_skill("cuff", 450);
        set_skill("leg", 450);
        set_skill("finger", 450);
        set_skill("staff", 450);
        set_skill("strike", 450);
        set_skill("jingang-quan", 450);
        set_skill("wuchang-zhang", 450);
        set_skill("ruying-suixingtui", 450);    
        set_skill("mohe-zhi", 450);
        set_skill("banruo-zhang", 450);
		 set_skill("hand", 450);
        set_skill("qianye-shou", 450);
        set_skill("buddhism", 160);
        set_skill("literate", 140);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("finger", "mohe-zhi");
        map_skill("strike", "banruo-zhang");
        map_skill("leg", "ruying-suixingtui");
        map_skill("staff", "wuchang-zhang");
        map_skill("parry", "wuchang-zhang");
		map_skill("hand", "qianye-shou");

        prepare_skill("hand", "qianye-shou");
        prepare_skill("leg", "ruying-suixingtui");
         set("chat_chance_combat", 70);
	    set("chat_msg_combat", ({
		(: perform_action, "leg.ruying" :),
		(: perform_action, "hand.qianshou" :),
		(: exert_function, "jingang" :),
	    }));
        create_family("少林派", 36, "弟子");

        set("inquiry", ([
                "易筋经": (: ask_yjj :),
				"铁帚腿功": (: ask_tztg :),
        ]));


        setup();

        if (clonep()) {
                ob = unew(BINGQI_D("jiuhuan-zhang"));                
                if (!ob) ob = unew(BINGQI_D("chanzhang"));
                ob->move(this_object());
                ob->wield();
                carry_object("/d/shaolin/obj/xuan-cloth")->wear();
        }
       
}


void attempt_apprentice(object ob)
{
        object me; 
        mapping ob_fam, my_fam;
        string name;

        me = this_object();
        my_fam  = me->query("family");

        name = ob->query("name");

        if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "少林派")
        {
                command("say " + RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
        }

        if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "少林派") 
        {
                command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能在寺内学艺。");
                return;
        }

        if ( ob_fam["generation"] <= my_fam["generation"] )
        {
                command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
                return;
        }

        if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..1] == "澄")
        {
                command("say " + ob_fam["master_name"] + "的徒弟怎麽跑到我这儿来了，哈哈哈 !");
                command("recruit " + ob->query("id"));
        }
        else
        {
                command("say " + RANK_D->query_respect(ob) + "，你辈份不合，不能越级拜师。");
                return;
        }

        return;
}
int ask_yjj()
{        
        
        object me = this_player();
        string msg;
        if (me->query_temp("azhu/mask")==1)
        {
			msg = HIY"玄生大师说道:易筋经乃是本寺镇寺之宝,是我少林七十二绝技的武学总纲。\n"NOR;
			 msg+= HIY"玄生大师说道:可惜当年鄙寺一时疏于防范,被一女施主假扮我寺中僧侣将之窃去。\n"NOR;
			msg+= HIY"玄生大师说道:此后鄙寺广派门下弟子四处找寻,却至今未曾有任何消息。\n"NOR;
			msg+= HIY"玄生大师说道:掌门方丈师兄为此面壁思过,忏悔不已。\n"NOR;
			 msg+= HIY"玄生大师说道:施主有此一问,莫非.........???!\n"NOR;
			message_vision(msg, me);
			me->set_temp("azhu/mask2",1);
			return 1;
		}
		message_vision(HIC"玄生大师问道：“你打听这些做什么？”\n"NOR, me);
        return 1;


}
int ask_tztg()
{        
        
        object me = this_player();
        string msg;
        if (me->query_skill("shaolin-tantui",1)<450)
		{
			command("say 你少林弹腿功力不足450，请打好基础后再来！\n");
			return 1;
        }
		if (me->query_skill("ruying-suixingtui",1)<450)
		{
			command("say 你如影随形腿功力不足450，请打好基础后再来！\n");
			return 1;
        }
		if (me->query("family/family_name")!="少林派")
		{
			command("say 你和我少林派无缘无故，来此打听这个绝技作甚？！\n");
			return 1;
        }
		if (me->query_skill("yijin-jing",1)<450)
		{
			command("say 你少林易筋经功力不足450，请打好基础后再来！\n");
			return 1;
        }
		if (time()-me->query("quest/sl/rysxt/tiezhou/time")<86400)
		{
			command("say 虽说勤快修持乃是本份，但你来的太频繁了，容易走火入魔！\n");
			return 1;
        }
		command("say 如影随形腿乃是本寺七十二绝技之一,是我少林腿法中巅峰绝技。\n");
		command("say 这铁帚腿功乃是将全身精血运于腿部，使得腿部坚如钢铁，宛如铁帚一样。\n");
		command("say 你如果想修习此技能，还是去第七般若堂处，询问下澄灵罗汉\n");
		me->set_temp("rysxt/askstart",1);
		return 1;


}

int accept_object(object me, object obj)
{
        object letter;
        if ((string)obj->query("id")=="shense baofu") {
        message("vision",me->name()+"给玄生大师一个深色包袱。\n",environment(me),
            ({me}));
        letter = unew("/d/mr/npc/obj/letter");
        if (me->query_temp("azhu/mask2") < 1) return notify_fail (CYN"玄生大师说道：你给我这个做什么?\n"NOR);  

        command("thank "+me->query("id"));
        command("say 啊.........!没想到老衲有生之年,还能得见此真经。");
        command("say 冥冥中果然因果报应循环不止,那位女施主能有此善念,当可赎昔日罪过,善哉,善哉!");
        letter->move(me);        
        message_vision("$n递给$N一封书信。\n", me, this_object() );
        command("say 这位"+RANK_D->query_respect(me)+",麻烦你替贫僧回转那位女施主鄙寺掌门书信一封,有劳了。");
        me->set_temp("azhu/mask3",1);

        remove_call_out("destroying");
        call_out("destroying", 1, this_object(), obj);
        return 1;
        }
        return 0;
}

void destroying(object me,object obj)
{
        destruct(obj);
        return;
}





