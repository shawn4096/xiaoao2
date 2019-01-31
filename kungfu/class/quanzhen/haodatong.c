// hao.c 郝大通
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_ruqin();
string ask_xiaoxi();

string* weizhi=({"半山亭","试剑岩","观日台","乡间小道","山麓","终南山下","遇真宫"});

void create()
{
        set_name("郝大通", ({"hao datong", "hao"}));
        set("gender", "男性");
        set("age", 34);
        set("class", "taoist");
        set("nickname",HIG"广宁子"NOR);
        set("long",
                "他就是全真七子中的郝大通郝真人。他身材微胖，象个富翁模\n"
                "样，身上穿的道袍双袖皆无。\n" );
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 30);
        set("int", 29);
        set("con", 29);
        set("dex", 29);

        set("title","全真七子之六");
        set("qi", 34500);
        set("max_qi", 34500);
		set("eff_qi",34500);
        set("jing", 5200);
        set("max_jing", 5200);
        set("neili", 24700);
        set("max_neili", 24700);
        set("jiali", 200);
        set("level", 18);
        set("combat_exp", 9400000);

        set_skill("force", 450);
        set_skill("xiantian-gong", 450);
        set_skill("sword", 450);
        set_skill("quanzhen-jianfa",450);
        set_skill("dodge", 450);
        set_skill("jinyan-gong", 450);
        set_skill("parry", 450);
        set_skill("literate",250);
        set_skill("strike", 450);
        set_skill("haotian-zhang", 450);
        set_skill("taoism",200);
	    set_skill("medicine", 200);
        set_skill("tiangang-beidouzhen", 450);
		set_skill("leg", 200);
        set_skill("yuanyang-lianhuantui", 450);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
		map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("strike","haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",
			    "抵抗蒙古入侵" : (:ask_ruqin:),
				"消息" : (:ask_xiaoxi:),

        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="男性")
       {
		   command("say 你一个女人家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于坤丹的修炼我不擅长！\n");
		   command("say 你还是去寻找下师叔清静散人孙不二，看他是否收你？\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 1500000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(1.5m)");
               return;
       }
	   if (ob->query("party/gongji") < 3000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(需要3000点门派贡献值)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say 你非我门中嫡传弟子，来此作甚？");
              return;

	   }
	   if (ob->query_skill("xiantian-gong",1) < 300) {
               command("say 我全真教一身功夫全在先天功，你先天功不足300，来此作甚？。");
               return;
       }
	 
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("title", "全真七子亲传弟子");
       ob->set("class","taoism");
	   return;
}

string ask_ruqin()
{
	//改成单人副本 by renlai
	object me,ob;
	int max,i;
	string place,cplace;

	object obj1;
	object *ob_list;
	object ob2;	
	object fbroom;
	object *team;
	me = this_player();
	
	ob = this_object();

	
	team = me->query_team();
	//如果是组队模式
	if (team){		
	   return "你不解散队伍如何接任务。";
	}
	/*if (!wizardp(me))	
              return "暂时关闭,开放日期另行通知!";*/
	if (me->query("shen")<2000000)
	{
		return "一看你就是心术不正之辈，先把正神提高再说！\n";
	}
	if (me->query_skill("force",1)<450)
	{
		return "你的基本内功不足450级，不要逞能！\n";
	}

	if (me->query("menggu"))
	{
		return "你已经投靠了蒙古，难道要找死么？！\n";
	}
	if ( me->query_temp("mgrq_job") )
		return "你不是已经接过蒙古入侵的任务了吗？";	
	
	
	if( !wizardp(me))
	{
		if ( me->query_condition("job_busy") || me->query_condition("mgrq_job"))
			return "您上次任务辛苦了，还是先休息一下再说吧。";

		if (me->query("job_name") == "抗敌蒙古入侵")
			return "您上次任务辛苦了，还是先休息一下再说吧。\n";
		
		if ( me->query("job_name")=="抗敌颂摩崖" )
		return "你刚做完颂摩崖任务。";
			
		if( me->query_temp("mgrq_job") )
			return "我已经给你任务了，你还站在这里做什么？\n";
//调试
	}

			
	command("say 我刚才接到尹志平的飞鸽传书，蒙古以金轮法王为代表的大批高手将围攻本教。\n" );
	command("say 我中原武林危在旦夕，你若有意就联合高手替我本教抵挡这次危机。\n" );	
	
	me->set_temp("mgrq_job",1);
	
	/*
	cplace=weizhi[random(sizeof(weizhi))];
	
	if (cplace=="") cplace=="试剑岩";
	switch (cplace)
	{
		case "试剑岩":
			place="/d/quanzhen/shijianyan";
			break;
		case "半山亭":
			place="/d/quanzhen/banshanting";
			break;
		case "遇真宫":
			place="/d/quanzhen/yuzhengong";
			break;
		case "观日台":
			place="/d/quanzhen/guanritai";
			break;
		case "山麓":
			place="/d/gumu/shanlu1";
			break;
		case "终南山下":
			place="/d/gumu/shanxia";
			break;
		case "乡间小道":
			place="/d/gumu/xiaolu3";
			break;
	}
	*/
	
	// 调试信息
	me->set_temp("mgrq_job/asked",1);
	me->apply_condition("job_busy", 30);	
	command("say "+ me->query("name")+CYN",本教"+HIY+"遇真宫"+CYN"处是蒙古武士北来的必经之地，你速速通过本教暗道埋伏在那里，以便阻挡他们入侵本教。\n");	
	//me->set_temp("qz/mgrqjob/cplace",cplace);
	
	    fbroom= new("/u/anger/yuzhengongfb");
        fbroom->set("backroom","/d/quanzhen/yuzhengong");//返回路径	
        fbroom->set("leader",me);//保存队长		
		me->set_temp("fbroom",fbroom);//记录副本房间，作为cond的判断依据
	    me->set("job_name", "抗敌蒙古入侵");
	
	if (wizardp(me)) {
		me->apply_condition("mgrq_job", 6);
		me->set("neili", me->query("max_neili")*2);
		me->move(fbroom);
		//me->move(place);
	}
	else
		me->apply_condition("mgrq_job", 10);
	
	 
	 message_vision(HIC"$N按下暗道机关，人影一闪，已不在原处。\n"NOR,me);
	 me->move(fbroom);

	return "这批武士中不乏高手，你需多加小心，以策万全，切记切记。\n";
	
}

string ask_xiaoxi()
{
	object me,ob;
	me=this_player();
	if (me->query("quest/qz/xtg/wuqi/start"))
	{
		
		command("say 好，好，真心不错！\n");
		command("thrumb "+me->query("id"));
		command("say 全真教核心根本就是在先天功上，这也是我师父重阳真人获得中神通称号的根本！\n");
		command("say 既然你如此努力，我就告诉你一个当初师父参悟先天功之地！\n");
		command("say 任何人的成功都不是随便得到，无一不是历经千辛万苦！\n");
		command("say 先天功三花聚顶、五气朝元的功夫是先天功的根本！\n");
		if ( me->query("marry"))
		{	
			command("look "+me->query("id"));
			command("say "+me->query("name")+"这娃娃不错，可惜破了先天元阳！\n");
			command("say 这先天根骨能否突破就看你的运气了！\n");
		}

		if (me->query("con")<40)
		{
			command("say 可惜你的先天根骨小于40，无法去修炼，太可惜！\n");
			return "你当努力修炼，强身健体！\n";
		}
		command("say 全真教内功以大师兄的修为最高，全真教全部的功夫都体现在先天功上！\n");
		command("say 大师兄曾提及，师傅当初就是在后山的一处极寒密洞闭关，借助极寒之境最终修成五气朝元！\n");
		
		command("say 你若想去就去碰碰运气吧，看能否再上一层楼！\n");
		command("say 扣除你100点贡献值，你去吧！\n");
		me->add("party/gongji",-100);

		me->set_temp("quest/qz/xtg/wuqi/askhao",1);
	}else {
		command("say 你当好好守卫全真教，为我大全真抵挡蒙古入侵！\n");
	}
	return "全真教先天功天下第一！\n";
}