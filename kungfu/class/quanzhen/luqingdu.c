//鹿清笃
//luqingdu.c
//sohu@xojh
//全真教早期男师傅之一
//
#include <job_mul.h>

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_rumen();
string ask_caiyao();
string ask_gongji();

int do_answer(string arg);

void create()
{
        set_name("鹿清笃", ({"lu qingdu", "lu"}));
        set("gender", "男性");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "他面生横肉，体格强健的青年道士，是全真教入门师傅之一，似乎身怀武艺。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);
		//设定不杀之人
		set("no_kill",1);
		set("no_throw",1);
		set("no_steal",1);

        set("qi", 5000);
        set("max_qi", 5000);
        set("jing", 4000);
        set("max_jing", 4000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 110);
        set("combat_exp", 500000);

        set_skill("force", 220);
        set_skill("xiantian-gong", 220);
        set_skill("leg", 220);
        set_skill("yuanyang-lianhuantui",220);
        set_skill("dodge", 220);
        set_skill("jinyan-gong", 220);
        set_skill("parry", 220);
       // set_skill("strike",140);
        //set_skill("haotian-zhang", 140);
        set_skill("literate",150);
        set_skill("taoism",100);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "yuanyang-lianhuantui");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg", "yuanyang-lianhuantui");
		set("chat_chance_combat", 40);
		set("chat_msg_combat", ({
			(: perform_action, "leg.yuanyang" :),
			//(: perform_action, "leg.lianhuan" :),
			
		}));

        create_family("全真教", 4, "弟子");

        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗,你若入我门来，不好好修炼，看我如何收拾你！\n",			      
                "入教" : (: ask_rumen :),
			    "采药" : (: ask_caiyao :),
               	"教中功绩" : (: ask_gongji :),
                 
        ]) );

        setup();

      //  carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

int init()
{
	add_action("do_answer","answer");

}
string ask_rumen()
{
	object me;
	me=this_player();
	if (me->query("family")&&me->query("family/family_name")!="全真教")
	{
		command("say 你这种作间隙也太假了吧！\n");
		command("say 你已经有门有派，别来烦我！\n");
		return "唉！";
	}
	if (me->query("combat_exp")>10000)
	{
		command("say 你这种老掉牙的套路想混入门派？\n");
		command("say 全真门下只收经验值10k以下的弟子！\n");

		return "真笨!\n";
	}
	if (me->query("shen")<0)
	{
		command("say 你一声戾气，我们是玄门正派好不好？\n");
		return "真无厘头!\n";

	}
	if (me->query_temp("qz/answeryes"))
	{
		command("say 既然你已经答应了，那就先暂时做我门下记名弟子，听我调遣！\n");
		if (me->query("gender")=="女性")
		{
			command("say 尽管你是女子，但这入门的仪式还是不能废了的，修足了贡献值再去拜姬清虚师妹！\n");
		}

		me->set("title","全真教第五代记名弟子");
		me->set("family/family_name","全真教");
		me->set("family/generation",5);
		me->set("party/jiming","鹿清笃");//记名弟子标记
		me->delete_temp("qz");
		return "好好干,跟我混有你的光明前途！\n";
	}
	command("sing ");
	command("say 想入我玄门正宗全真派，你的先通过我的考研才行！\n");
	command("say 老子就是专门负责为大全真招揽人才的\n");
	command("say 你若愿意，我这儿正好有些工作安排你去做！做的好，我可以考虑收你为徒！\n");
	command("say 你可考虑清楚了么？\n");
	me->set_temp("qz/rumen",1);
	return "这可是玄门正宗的大全真教！\n";
}
int do_answer(string arg)
{
	object me;
	me=this_player();
	if (!me->query_temp("qz/rumen"))
	{
		command("say 无缘无故，非奸即盗！\n");
		return 1;
	}
	if (!arg||arg!="愿意")
	{
		return notify_fail("你瞎答应什么？\n");
	}
	message_vision(HIY"$N满脸堆笑，对鹿清笃连声答应，说道，“愿意”！\n"NOR,me);
	me->set_temp("qz/answeryes",1);
	return 1;
}
string ask_caiyao()
{
	object me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		command("say "+me->query("name")+"，你这种人作间隙也太假了吧！\n");
		command("say "+me->query("name")+"，别来烦我！\n");
		return "想蒙混过关？！\n";
	}
	if (me->query_temp("qz/caiyao"))
	{
		command("say "+me->query("name")+"，我不是安排你去采药去了么？是不是偷懒了？\n");
		return "想蒙骗我过关，做梦！\n";
	}
	if (me->query_condition("job_busy"))
	{
		command("say "+me->query("name")+"，你正在工作忙碌中，待会再来？\n");
		return "想蒙骗我过关！\n";

	}
	//控制经验值
	//if (me->query("combat_exp")>200000)
	//{
		//command("say 你经验值已经很高了，这种轻松的活让你师弟来干好了！\n");
		//return "又一个投机取巧的，经验值有那么好拿么！\n";
	//}
	tell_object(me,"鹿清笃对"+me->query("name")+"说道，“你来的正好,掌药道长又来催我了，需要一批中草药。”\n");
	tell_object(me,"鹿清笃对"+me->query("name")+"说道，“你先去终南山下集市中的打铁铺询问铁匠看看，哪儿是否有药锄。”\n");
	tell_object(me,"鹿清笃对"+me->query("name")+"说道，“你去后询问下他。凭我全真教的名义，谅他也不敢难为你！”\n");

	tell_object(me,"鹿清笃对"+me->query("name")+"说道，“然后你去全真教附近的树林区域里去搜寻药材看看。”\n");
	tell_object(me,"鹿清笃对"+me->query("name")+"说道，“采药要诀第一是多搜索，找到后再用药锄挖采，记住了么？！”\n");
	me->set_temp("qz/caiyao",1);
	
	tell_object(me,"鹿清笃对"+me->query("name")+"说道，“挖好药材后到我这儿用所挖的中药材领赏，快去快回！”\n");
	return "在我的主持下，玄门正宗的大全真教必将光大！\n";

}

string ask_gongji()
{
	int i;
	object me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		command("say 你这种作间隙也太假了吧！\n");
		command("say 别来烦我！\n");
		return "想蒙混过关？！\n";
	}
	i=me->query("party/gongji");

	command("say "+me->query("name")+"，现在教中功绩为"+chinese_number(i)+"点贡献值。\n");
	
	return "你如此努力，大全真必将名扬天下！\n";

}

int accept_object(object who, object ob)
{
	object sil;
	int gold,getshen;
	//if (ob=all) return 1;
	
	gold=40+random(10);
	//shen=50+random(50);
	if (ob->query("player")==who->query("id")
		//&& who->query_temp("herb/got")
		&&(ob->query("id")=="fu ling"||ob->query("id")=="ju geng"||ob->query("id")=="huang lian"||ob->query("id")=="chuan bei"
		||ob->query("id")=="he shouwu"||ob->query("id")=="jinyin hua"||ob->query("id")=="sheng di"||ob->query("id")=="gouzhi zi"))
	{
	
		getshen=1;
		//奖励
		if (who->query("combat_exp")<200000) 
		{
			TASKREWARD_D->get_reward(who,"全真采药",getshen,0,0,random(2)-1,0,0,0,this_object());


			sil=new("clone/money/silver");
			sil->set("set_amount",gold);
			sil->move(who);
			tell_object(who,HIY"\n鹿清笃随手甩给"+who->query("name")+HIY+chinese_number(gold)+"两白银的奖励！\n"NOR);

		}
		who->set("job_name","全真采药");
	//	who->add("job_time/全真采药",1);
		
		who->apply_condition("job_busy",4);
		//who->apply_condition("job_busy",3);

	//	who->add("shen",shen);

		who->add("party/gongji",2+random(1));//工分2分
		who->delete_temp("qz");
		who->delete_temp("herb");

		command("say "+who->query("name")+"，很好，既然你把这药材给我拿来了，我就给你点下酒钱！\n");


		//预留入门提示接口
		if (random(who->query("party/gongji"))>500 && !who->query("party/rumen"))
		{
			command("pat "+who->query("id"));

			tell_object(who,HIY"\n鹿清笃悄声提醒"+who->query("name")+"道“经过近期一段时间的观察，我觉得你吃苦耐劳，真心不错的好苗子！”\n"NOR);
			tell_object(who,HIY"\n鹿清笃悄声提醒"+who->query("name")+"道“你若愿意我就收下了你！”\n"NOR);
			who->set("party/rumen",1);
		}
		return 1;
	}

}

void attempt_apprentice(object ob)
{
       
	   if (ob->query("gender")!="男性")
       {
		   command("say 你一个姑娘家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于坤丹的修炼我不擅长！\n");
		   command("say 你还是去寻找下师叔程瑶迦门下弟子姬清虚师妹，看她是否收你？\n");
		   return ;

       }
	   if (ob->query("party/jiming")!="鹿清笃")
       {
		   command("say 你不是我鹿清笃的记名弟子，我可不敢收你！\n");
		   command("say 要想成为我的记名弟子很简单，多给我干活，让我看你顺眼！\n");
		   return ;
       }
	   if ((int)ob->query("shen") < 50000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(5k)");
               return;
       }

	   if (ob->query("party/gongji") < 500) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(需要500点门派贡献值)\n");
               return;
       }
	
	   if (!ob->query("party/rumen")) {
               command("say 你还没通过我的考研呢！赶紧干活去！\n");
               return;
       }
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("class","taoism");
	   return;
}
