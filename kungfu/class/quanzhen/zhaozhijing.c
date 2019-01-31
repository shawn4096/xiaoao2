// zhao.c 赵志敬
// By Lgg,1998.10

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_yanlian();
string ask_start();
string ask_stop();

int do_zhifu(string arg);


void create()
{
        set_name("赵志敬", ({"zhao zhijing", "zhao"}));
        set("gender", "男性");
        set("age", 26);
        set("class", "taoist");
        set("long",
                "他就是全真教第三代弟子中的好手，王处一的大弟子赵志敬。 \n"
                "他相貌端正，但眉宇间似乎隐藏着一丝狡猾的神色。\n"
		"他是一个长须道人，看起来却有些煞气。\n");
        set("attitude", "friendly");
        set("shen_type",-1);
        set("str", 25);
        set("int", 26);
        set("con", 26);
        set("dex", 25);

        set("qi", 15000);
        set("max_qi", 15000);
        set("jing", 5000);
        set("max_jing", 5000);
		set("jingli", 6000);
        set("max_jingli", 6000);
        set("eff_jingli", 6000);

        set("neili", 15000);
        set("max_neili", 15000);
        set("jiali", 200);

        set("combat_exp", 6600000);
		set("quest/qz/xtg/daojue/pass",1);
		set("quest/qz/jyg/shangtianti/pass",1);
		set("quest/quanzhen/sword/lianhuan",1);

        set_skill("force", 380);
        set_skill("xiantian-gong", 380);
        set_skill("sword", 380);
        set_skill("quanzhen-jianfa",380);
        set_skill("dodge", 380);
        set_skill("jinyan-gong", 380);
        set_skill("parry", 380);
        set_skill("strike",380);
        set_skill("haotian-zhang", 380);
        set_skill("literate", 160);
        set_skill("taoism", 160);      
        set_skill("tiangang-beidouzhen", 380);
        set_skill("leg", 380);      
        set_skill("yuanyang-lianhuantui", 380);
        set_skill("jinguan-yusuojue", 350);

		map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
		map_skill("leg", "yuanyang-lianhuantui");

        prepare_skill("strike", "haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("全真教", 3, "弟子");
		set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "sword.ding" :),
			(: perform_action, "sword.sanqing" :),
			(: perform_action, "sword.lian" :),
			(: exert_function, "daojue" :),
			(: perform_action, "dodge.yanwu" :),
		}));

        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",  
				"演练天罡北斗大阵" :  (:ask_yanlian:), 
				"启动北斗大阵" :  (:ask_start:),  
				"放弃" :  (:ask_stop:),  
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
       if (ob->query("family")!="全真教")
       {
		   command("say 你不是全真教弟子居然来找我拜师，奸细吧？\n");
		   return ;

       }
	   if (ob->query("gender")!="男性")
       {
		   command("say 你一个女人家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于坤丹的修炼我不擅长！\n");
		   command("say 你还是去寻找下师叔清静散人孙不二门下弟子程瑶迦师妹，看他是否收你？\n");
		   return ;

       }
	   if ((int)ob->query("shen") < 1200000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(1.2m)");
               return;
       }
	   if (ob->query("party/gongji") < 1500) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(需要1500点门派贡献值)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say 你非我门中嫡传弟子，来此作甚？");
              return;

	   }
 	   if (ob->query_skill("xiantian-gong",1) < 220) {
               command("say 我全真教一身功夫全在先天功，你先天功不足220，来此作甚？。");
               return;
       }
	   if (ob->query_skill("yuanyang-lianhuantui",1) < 220) {
               command("say 你的鸳鸯连环腿不足220，来此作甚？。");
               return;
       }
	   if (ob->query_skill("haotian-zhang",1) < 220) {
               command("say 你的昊天掌不足220，来此作甚？。");
               return;
       }		
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("class","taoism");
	   return;

}
int init()
{
	add_action("do_zhifu",({"zhifu","duihuan","jiaohuan"}));
}


string ask_yanlian()
{
		object ob;
		ob=this_player();
		message_vision(HIG"$N毕恭毕敬的向$n请示能否帮助自己演练天罡北斗大阵的事情！\n"NOR,ob,this_object());
		if ((int)ob->query("shen") < 2000000)
		{
               command("say 神太低，不足2m,切记心思不正是无法体味天心的。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(2m)");
               return "无量天尊！\n";
       }
	   if (ob->query_temp("qz/yanlian/zhifu"))
	   {
		   return "你已经支付了演练费用，赶紧练阵吧!\n";
	   }
	   if (ob->query("family/family_name")!="全真教")
       {
		   command("say 你不是全真教弟子居然来找我演练北斗大阵，奸细吧？\n");
		   return "可笑之极！\n";

       }
	   if (ob->query("party/gongji") < 5000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(需要5000点门派贡献值)\n");
              return "无量天尊！\n";
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say 你非我教中嫡传弟子，来此作甚？");
             return "无量天尊！\n";

	   }
 	   if (ob->query_skill("xiantian-gong",1) < 350) {
               command("say 我全真教一身功夫全在先天功，你先天功不足350，来此作甚？。");
               return "无量天尊！\n";
       }
	   if (ob->query_skill("quanzhen-jianfa",1) < 350) {
               command("say 你的全真剑法不足350，来此作甚？。");
               return "无量天尊！\n";
       }
	   if (ob->query_skill("tiangang-beidouzhen",1) < 350) {
               command("say 你的天罡北斗阵不足350，无法体味天罡北斗心法奥秘？。");
              return "无量天尊！\n";
       }
	   
       command("say "+ob->query("name")+"，你听好了，天下没有免费的午餐，这天罡北斗大阵的演练至少需要七个人。\n");
       command("say 他们分别是，崔志方,、陈志益、申志方、房志起、祁志诚。\n");
	   ob->set_temp("lianzhen/zhao",1);
	   if (!ob->query_temp("lianzhen/cui")||!present("cui zhifang",environment(this_object()))) return "不是跟你说了么，还差崔志方师弟么！\n";
	   if (!ob->query_temp("lianzhen/shen")||!present("shen zhifan",environment(this_object()))) return "不是跟你说了么，还差申志方师弟么！\n";
	   if (!ob->query_temp("lianzhen/chen")||!present("chen zhiyi",environment(this_object()))) return "不是跟你说了么，还差陈志益师弟么！\n";
	   if (!ob->query_temp("lianzhen/fang")||!present("fang zhiqi",environment(this_object()))) return "不是跟你说了么，还差房志起师弟么！\n";
	   if (!ob->query_temp("lianzhen/qi")||!present("qi zhicheng",environment(this_object()))) return "不是跟你说了么，还差祁志诚师弟么！\n";
	   command("say 好，既然人凑齐了，就可以启动大阵演练了！\n");
	   command("say 如果真想修炼这天罡北斗大阵，你需要拿出你的门派贡献值来支付。\n");
	   command("say 每次演练都要耗费一千点(1000)点门派贡献！\n");
	   command("say 另外，我们几个师兄弟天天陪你一起练，每次需要支付一百两黄金。直接从你账上扣掉！\n");
	   command("smile "+ob->query("id"));

	   command("say "+ob->query("name")+"，不知道你是否愿意支付(zhifu)这些费用么？\n");

	   ob->set_temp("qz/yanlian/askzhao",1);
	   return "演练天罡北斗阵太辛苦了！\n";
}
int do_zhifu(string arg)
{	
	object me,ob;
	me=this_player();
	ob=this_object();
	if (!arg||arg!="贡献值演练天罡北斗大阵")
	{
		command("say 你要说[zhifu 贡献值演练天罡北斗大阵]！\n");
		return 1;
	}
	if (me->query("party/gongji")<1000)
	{
		command("say 你的门派贡献值不够！\n");
		return 1;
	}
	if (me->query("balance")<1000000)
	{
		command("say 你银行账号余额不足，别在这消遣老子！\n");
		return 1;
	}

	message_vision(HIC"$N愿意交出自己积攒的五百点门派贡献值和一百两黄金给$n来启动天罡北斗大阵的演练!\n"NOR,me,ob);
	message_vision(HIR"$n提醒你说道，“你虽然交付门派贡献值，但过程中下线或没完成这次演练失败，可与我没有任何关系”!\n"NOR,me,ob);
	//message_vision(HIR"$n提醒你说道，“你虽然交付门派贡献值，但过程中下线或没完成这次演练失败，可与我没有任何关系”!\n"NOR,me,ob);
	me->delete_temp("qz/yanlian");
	
	me->add("party/gongji",-500);
	me->add("balance",-1000000);
	me->set_temp("qz/yanlian/zhifu",1);
	return 1;
	
}

string ask_stop()
{
	object me;
	me=this_player();
	if (!me->query_temp("qz/yanlian/askzhao"))
	{
		return "别捣乱,谁没事吃饱了撑得陪你玩？\n";
	}
	command("say 既然这位师弟愿意支付我等费用，那就开始演练(lianzhen)大阵吧！\n");

	me->delete_temp("lianzhen");
	me->delete_temp("qz");
	return "不行啊！\n";
}

string ask_start()
{
	object me;
	me=this_player();
	if (!me->query_temp("qz/yanlian/zhifu"))
	{
		return "你不愿意支付费用，谁没事吃饱了撑得陪你玩？\n";
	}
	command("say 既然你想放弃那就算了！\n");

	message_vision(HIY"随着赵志敬的话音刚落，其余弟子相继抢占北斗七星的各大位置！\n"
	+"赵志敬抢占了“"HIC"天权"NOR"”位\n"
	+"崔志方抢占了“"HIG"天枢"NOR"”位\n"
	+"陈志益抢占了“"HIY"天璇"NOR"”位\n"
	+"房志起抢占了“"HIM"天玑"NOR"”位\n"
	+"申志凡抢占了“"HIW"玉衡"NOR"”位\n"
	+"祁志诚抢占了“"HIB"开阳"NOR"”位\n"
	+"$N随即踏入阵法之中，抢占了"HIR"摇光"NOR"位\n"NOR,me);
	
	command("say 「天罡北斗阵」要有七人组成,你需要输入“lianzhen name1 name2 name3 name4 name5 name6”即可\n");
	command("say 比如：lianzhen zhang cui chen .....\n ");
	command("say 你听懂了就可以启动大阵了！\n");
	if (me->query("job_name")=="全真练阵")
	{
		command("say 你方才练阵完毕，先休息会！\n");
		return "先去忙点别的！\n";

	}
	me->set_temp("lianzhen/start",1);
	return "天罡北斗大阵乃是我全真的不传之秘！\n";
}