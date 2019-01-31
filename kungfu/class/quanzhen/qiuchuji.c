// qiu.c 丘处机
// Modified By action@SJ 2008/8/12
// Update By action@SJ 2009/2/21

#include <ansi.h>
#include <get_place.h>

inherit NPC;
//inherit F_MASTER;
mixed qixing();
mixed qzjf_jianjue();
int do_qingjiao();
string ask_duan();
string ask_fengxue();
int ask_chujian();
int ask_fangqi();
object get_where();

string ask_tonggui();

#define QUESTDIR "quest/射雕英雄传/"
#define QUESTDIR1 "quest/射雕英雄传/风雪惊变/"
#define QUESTDIR2 "quest/射雕英雄传/江南七怪/"

void create()
{
		set_name("丘处机", ({"qiu chuji", "qiu"}));
		set("long",
					"他就是江湖上人称‘长春子’的丘处机丘真人，他方面大耳，\n"
					"满面红光，剑目圆睁，双眉如刀，相貌威严，平生疾恶如仇。\n");
		set("title","全真七子之四");
		set("gender", "男性");
		set("age", 26);
		set("nickname",HIM"长春子"NOR);
		set("shen_type",1);
		set("attitude", "peaceful");

		set("str", 50);
		set("int", 55);
		set("con", 50);
		set("dex", 50);

	    set("max_qi", 48000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 200);

		set("jingli", 7000);
		
set("eff_jingli", 7000);

		set("combat_exp", 12000000);

        set_skill("force", 480);
        set_skill("xiantian-gong", 480);
        set_skill("sword", 480);
        set_skill("quanzhen-jianfa",480);
        set_skill("dodge", 480);
        set_skill("jinyan-gong", 480);
        set_skill("parry", 480);
        set_skill("strike", 480);
        set_skill("haotian-zhang", 480);
        set_skill("literate", 250);
		set_skill("tiangang-beidouzhen",480);
 
        set_skill("leg", 480);
        set_skill("yuanyang-lianhuantui", 480);

		set_skill("taoism",200);
	    set_skill("medicine", 200);
        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("strike", "haotian-zhang");
		map_skill("parry", "quanzhen-jianfa");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg","yuanyang-lianhuantui");
		prepare_skill("strike","haotian-zhang");

	    create_family("全真教", 2, "弟子");

	    set("inquiry", ([               
                "全真剑气" : (: qzjf_jianjue :),
			    "风雪惊变" : (: ask_fengxue :),
				"救人" : (: ask_duan :),
			   "七星绝命剑" : (: qixing :),
			   "全真锄奸" : (: ask_chujian :),
			   "放弃" : (: ask_fangqi :),
				"同归剑法" : (: ask_tonggui :),
           ]));		       
                    

        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                 (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.qixing" :),
                (: perform_action, "sword.ding" :),
				(: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.lian" :),
				(: exert_function, "daojue" :),
					(: exert_function, "wuqi" :),
					(: exert_function, "yusuo" :),
               
        }));
        	setup();
	carry_object("/d/wudang/obj/greenrobe")->wear();
	carry_object("/clone/weapon/sword")->wield();
	//add_money("silver",50);
}


void init()
{
	object me, ob;
	::init();
	ob = this_player();
	me = this_object();

	add_action("do_qingjiao", "qingjiao");

}

string ask_fengxue()
{	
	object me;
	me=this_player();
	if (!me->query(QUESTDIR1+"over"))
	{
		return "射雕英雄传第一章节尚未完成，无法启动第二章节\n";
	}
	
	if (me->query(QUESTDIR2+"over"))
	{
		return "我已经和江南七怪约定各带一名弟子再来比试了，你还不速速去找郭杨二人后人。\n";
	}
	
	if ((time()-me->query("quest/射雕英雄传/time"))<86400)
	{
		return "你今天已经很累了，先去休息一下吧！\n";
	}
	
	
	
	message_vision(HIR"$N将先前牛家村发生一些事情原原本本说给了丘处机听，丘处机大为震惊！\n"NOR,me);
	command("angry ");
	command("say 居然有这种事？\n");
	command("say 那么杨贤弟和郭贤弟一家岂不是因为贫道而受到牵连么？\n");
	command("say 不行，我必须要去找到郭贤弟的夫人和杨贤弟的夫人包惜弱，否则我心难安！\n");
	command("say 你知道这件事是谁干的么？我也好有个追查的线索！\n");
	me->set_temp(QUESTDIR2+"start",1);
	me->set(QUESTDIR2+"start",1);
	return "虽刀山火海必不辞也！\n";

}
string ask_duan()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR2+"start"))
	{
		return "来来，我们再喝一杯！\n";
	}
	message_vision(HIY"$N告诉丘处机，此时怀疑是当地官兵所为，至于为何特意围剿牛家村，着实令人不解！\n而且杨铁心、包惜弱虽下落不明，但李萍却为这段天德所掳走，据说有人看到在杭州兵营一带出现！\n"NOR,me);
	command("consider ");
	command("say 既然杨兄弟和包惜弱没见到尸体，那说明他们没有被害！\n");
	command("say 我马上去救援他们二人，免得再遭毒手,我去寻找杨贤弟和其夫人！\n");
	command("say 你先去杭州兵营一带打探查看，看到底是何原因发生这起冤案！？\n");
	me->delete_temp(QUESTDIR2+"start");
	me->set_temp(QUESTDIR2+"hzdatan",1);
	return "朝廷命官居然随便杀人，还有没有天理了？！\n";

}

void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="男性")
       {
		   command("say 你一个女人家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于坤丹的修炼我不擅长！\n");
		   command("say 你还是去寻找下师妹清静散人孙不二，看他是否收你？\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 2000000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(2m)");
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
	   if (ob->query_skill("xiantian-gong",1) < 350) {
               command("say 我全真教一身功夫全在先天功，你先天功不足350，来此作甚？。");
               return;
       }
	 
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("title", "全真七子亲传弟子");
       ob->set("class","taoism");
	   return;
}

mixed qzjf_jianjue()
{
	object me = this_player();
	object ob = this_object();
	int exp, time, night;
	mixed *local;
	night = 0;
	local = localtime(time() * 60);
	if (local[2] < 5 || local[2] >= 19) night = 1;

	if( me->query("family/family_name") != "全真教" )
		return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？";
    if (!me->query("quest/qz/dichuan"))
	{
		return "你非我大全真嫡传弟子，我为什么要告诉你？";
	}
    if (!night) 
	  return "我现在无法看见天空中北斗七星，又如何指导你学习全真剑法的剑诀精髓。\n";
  
    if (!me->query(QUESTDIR2+"over"))
	{
		return "你尚未走完射雕英雄传第二章节流程，来了也白搭！\n";
	}
	if (me->query_skill("quanzhen-jianfa",1)<450)
	{
		return "全真剑法需要达到450大飞阶段方可修习！\n";
	}
	if (me->query_skill("force",1)<450)
	{
		return "全真剑法需要基本内功达到450大飞阶段方可修习！\n";
	}
	if (me->query("family/family_name")!="全真教")
	{
		return "你并非全真教弟子！\n";
	}
	if ((time()-me->query("quest/qz/qzjf/jianqi/time"))<86400)
	{
		return "你来的太频繁了！\n";
	}
	if (me->query("quest/qz/qzjf/jianqi/pass"))
	{
		return "你已经解开这个谜题了！\n";
	}
  
  

	if( me->query("quest/qzjf/jianjue") )
		return RANK_D->query_respect(me) + "，你的剑诀造诣已经不在本道之下了，又何故开此玩笑呢？";

    if( me->query_skill("quanzhen-jianfa", 1) < 300 )
		return RANK_D->query_respect(me) + "，你的剑法造诣不够，还无法领悟我派剑法的精要所在！";

	time = time() - me->query("qzjf/jianjue/time");
	if( me->query("qzjf/jianjue/time") && time < 86400 && !wizardp(me) )
		return "嗯？你不是刚来请教过我剑诀吗？还是再努力段时间吧！";

	if( me->query_temp("marks/qzjf/qingjiao") )
		return RANK_D->query_respect(me) + "，我刚才不是已经回答你了吗？";

	message_vision(CYN"$N严肃的看着$n，慢慢说道：“我派的全真剑法讲究的是道家观测宇宙星斗北斗七星变换之道，取千变万化、无穷无尽之原理，\n"
	"如不是亲身体会估计很难领悟，近来你的武功已有所小成，如果你有信心，可以来向我请教一下。("HIY"qingjiao"CYN")”\n"NOR, ob, me);

	me->set_temp("marks/qzjf/qingjiao", 1);
	return 1;
}

int do_qingjiao()
{
	object me, ob, weapon, weapon1;
	int i,j;
	me = this_player();
	ob = this_object();

	weapon1 = ob->query_temp("weapon");

	if( !me->query_temp("marks/qzjf/qingjiao") ) return notify_fail("什么？\n");

	if( me->is_busy() || me->is_fighting() ) return notify_fail("你正忙着呢。\n");

	if( ob->is_busy() || ob->is_fighting() ) return notify_fail(ob->name()+"正忙着呢。\n");

	if( me->query("qi") < me->query("max_qi")*9/10 )
		return notify_fail("你现在状态不佳，还是等会再请教吧！\n");

	if( me->query("eff_qi") < me->query("max_qi")/2 )
		return notify_fail("你现在重伤在身，还是等会再请教吧！\n");
	if ((time()-me->query("quest/qz/qzjf/jianqi/time"))<86400)
	{
		command("say 你来的太频繁了，修道最忌讳心浮气躁！你当休息一天再来！\n");
		return 1;
	}
	if( !weapon = present("qixing jian", me) ) 
	{
		message_vision(CYN"$N对$n说：“请师傅对徒儿进行指点"+RANK_D->query_self(me)+"的全真剑法剑诀！”\n"NOR, me, ob);
		message_vision(CYN"$n说：“" + RANK_D->query_respect(me) + "还是先去找我师傅王重阳取来七星宝剑吧！”\n"NOR, me, ob);
		me->start_busy(1);
		return 1;
	} else {
		me->start_busy(1);
		message_vision(CYN"$N对着$n将长剑交给师傅说道：“请师傅指点"+RANK_D->query_self(me)+"的全真剑法剑诀！”\n"NOR, me, ob);
		me->delete_temp("marks/qzjf/qingjiao");
		me->set("qzjf/jianjue/time", time());
		me->set("qzjf/jianjue/exp", me->query("combat_exp"));

		if( weapon1 ) weapon1->unequip(ob); 
		weapon->move(ob);
		weapon->wield(ob);
		ob->set("jiali", 0);
		ob->set("neili", query("max_neili")*2 );
		ob->set("jingli", query("eff_jingli")*2 );
		message_vision(HIW"$n默念全真剑诀，“"HBRED+HIW"认星先从北斗来，由北往西再展开”。"NOR+HIW"”顿时剑气纵横，将$N攻个措手不及！"NOR, me, ob);
		ob->set_temp("qzjf/jianjue", 1);
		COMBAT_D->do_attack(ob, me, weapon, 1);
		if( me->query("qi") >= me->query("max_qi")*1/10 ) COMBAT_D->do_attack(ob, me, weapon, 1);
		if( me->query("qi") >= me->query("max_qi")*1/10 ) COMBAT_D->do_attack(ob, me, weapon, 1);
		if( me->query("qi") >= me->query("max_qi")*1/10 ) {
			message_vision(HIW"$n默念全真剑诀，“"HBMAG+HIW"斗柄东指，天下皆春；斗柄南指，天下皆夏。"NOR+HIW"”右手猛的运剑回转，左手终南指法之「一阳指」随劲而起！"NOR, me, ob); 
			weapon->unequip(ob); 
			COMBAT_D->do_attack(ob, me, 0, 1);
			weapon->wield(ob);
		}
		if( me->query("qi") >= me->query("max_qi")*1/10 ) COMBAT_D->do_attack(ob, me, weapon, 1);
		if( me->query("qi") >= me->query("max_qi")*1/10 ) {
			message_vision(HIW"$n默念全真剑诀，“"HBBLU+HIW"斗柄西指，天下皆秋；斗柄北指，天下皆冬。"NOR+HIW"”紧接着"+weapon->name()+HIW"猛的回转再次刺出！"NOR, me, ob);
			COMBAT_D->do_attack(ob, me, weapon, 1);
		}
		ob->delete_temp("qzjf/jianjue");

		if( me->query("qi") < me->query("max_qi")*1/20 ) {
			message_vision(CYN"$n非常失望的对$N说到：“"+me->name()+"，你武功未成，还是等你打好基础再说！”\n"NOR, me, ob);
			weapon->unequip(ob); 
			destruct(weapon);
			if( weapon1 ) weapon1->wield(ob);
			me->start_busy(1);
			me->set_temp("marks/失败", 1);
			return 1;
		}
		weapon->unequip(ob); 
		weapon->move(me);
		message_vision(CYN"\n$n将七星宝剑交还给$N，愉快的说着：“"+me->name()+"，你自己慢慢琢磨下我所使用的剑诀吧！”\n"NOR, me, ob);
		if( weapon1 ) weapon1->wield(ob);
		message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
	//调用判断函数
		call_out("ask_jianqi",1+random(3));
		message_vision(HIY"丘处机对$N说，“你很不错，这全真剑法乃是我大全真的核心武技，看你能否领悟了！”\n"NOR,me);

		/*if( random(me->query("kar")) > 25) 
		{	// 随机福源
			message_vision(HIW"$N突然捕捉住交手瞬间的一幕，自言自语：“前后左右，全无定向，后发制人，先发制于人。”渐渐领悟出全真剑法的真谛。\n", me);
			tell_object(me, BYEL"恭喜你，你于" + NATURE_D->game_time() + "领悟了全真剑诀。\n"NOR);
			me->set("quest/qz/qzjf/jianqi/pass", 1);
		} else {
			message_vision(HIC"$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n", me);
			me->set_temp("marks/失败", 1);
		}*/
	}
	return 1;
}
string ask_jianqi()
{
	object me;
	int i,j;
	me=this_player();
	
	me->set_temp("quest/qz/qzjf/jianqi/askqiu",1);
	
	command("say 事先声明，你向我请教需要扣除你的门派贡献值每次100点，如果不够你没资格请教我。\n\n\n\n");
	
    command("say 好吧，既然你如此努力，我就告诉你其中诀窍。\n");
    command("whisper "+me->query("id"));
	  
	if (me->is_busy())
	{
	  return "你正在忙碌中!\n";
	}
	me->start_busy(10);
	if (me->query("party/gongji")<100)
	{
		return "你的门派功绩不够\n";
	}
	
	me->add("party/gongji",-100);
	
		command("say 你听懂了么。\n");
		command("pat "+me->query("id"));
		
		if (QUEST_D->questing(me,3,80,0,"qz/qzjf/jianqi"))		
		{
			tell_object(me,HIC"\n你听了的丘处机的亲自指点，联想起早期自己所用全真剑法的种种心得，两下印照。\n"NOR);
			message_vision(HIW"$N突然捕捉住交手瞬间的一幕，自言自语：“前后左右，全无定向，后发制人，先发制于人。”渐渐领悟出全真剑法的真谛。\n", me);
			tell_object(me, BYEL"恭喜你，你于" + NATURE_D->game_time() + "领悟了全真剑诀。\n"NOR);
			//me->set("quest/qz/qzjf/jianqi/pass", 1);
			//log_file("quest/qzjfjianqi", sprintf("%8s(%8s) 失败%d次后，学到全真剑法剑气绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			//	me->name(1),me->query("id"), me->query("quest/qz/qzjf/jianqi/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest");
			me->start_busy(2);
			return "恭喜解密全真剑法绝技绝技成功!\n";
			
		}	
	   else
		{
			//log_file("quest/qztonggui", sprintf("%8s(%8s) 解密全真剑法绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			//	me->name(1),me->query("id"), me->query("quest/qz/qzjf/jianqi/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"你听了丘处机的指点，可是对全真剑法绝技的奥妙全然不得要领。\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			//me->add("quest/qz/qzjf/jianqi/fail",1);
			//me->set("quest/qz/qzjf/jianqi/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest");
			//me->start_busy(2);
			return "非常遗憾解密全真剑法绝技失败"+me->query("quest/qz/qzjf/jianqi/fail")+"次。\n";
		}

}

mixed qixing()
{
	object room;
	object me = this_player();
	object ob = this_object();
	int exp, time, night;
	object* ppl;
    int i,j = 0;

	mixed *local;
	night = 0;
	local = localtime(time() * 60);
	if (local[2] < 5 || local[2] >= 19) night = 1;
    time = time() - me->query("quest/quanzhen/lianzhen/time");
	//判断是否有人在解密
	ppl = users();
	i = sizeof(ppl);
    while(i--)
	{
       if( userp(ppl[i])&& !wizardp(ppl[i])&& ppl[i]->query_temp("quest/qixing/enter"))
	   j++;
    }
	if (j>0)
	{
		command("say 等等！\n");
		return "现在正有人在参悟，稍后！\n";
	}

	if (!me->query("quest/qz/dichuan"))
	{
		command("say 唉！！\n");
		return "你非我大全真嫡传弟子，我为什么要告诉你？\n";
	}
	if (me->query("int")<40)
	{
		command("say 唉！！\n");
		return "你的先天悟性不足40，告诉你也领悟不了？\n";
	}

	if( time < 86400 && !wizardp(me) )
		return "嗯？你不是刚来请教过我七星绝命剑吗？还是再努力段时间吧！\n";
	
	if( me->query("family/family_name") != "全真教" )
		return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？\n";
    if( me->query("family/family_name") != "全真教" )
		return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？\n";
	if( me->query_skill("xiantian-gong",1)<450 )
		return RANK_D->query_respect(me) + "你的先天功不足450，抓紧努力。\n";
    if (!night) 
		return "我现在无法看见天空中北斗七星，又如何指导你学习七星绝命剑法精髓。\n";
 
	if( !me->query("quest/qz/qzjf/qixing/start") )
		return RANK_D->query_respect(me) + ",你天天偷懒，不帮我去锄奸，还想蹭机会？\n";	
	
	if( me->query("quest/qz/qzjf/qixing/pass") )
		return RANK_D->query_respect(me) + ",你已经领悟了七星绝命剑的奥秘，又何故开此玩笑呢？\n";

    if( me->query_skill("quanzhen-jianfa", 1) < 450 )
		return RANK_D->query_respect(me) + "，你的剑法造诣不够，还无法领悟我派剑法的精要所在！\n";

	me->start_busy(5);

	
    me->set_temp("quest/qixing/asked",1);
	message_vision(HIY"$N抬头看了看天空，北斗七星闪耀，长叹一声,良久默然无语。然后异常严肃的看着$n，\n"+
		HIC"慢慢地说道：“家师武功有两大绝世绝技，一为先天功，其二乃是七星绝命剑，以此两大绝世神功名扬天下，\n"+
		HIG"可惜这两大绝技我们七兄弟都没有完全领悟，若领悟其中一项，必然会笑傲江湖，先天功乃绝世武技，\n"+
		"但这七星绝命剑却是家师夜观北斗中所悟，讲究的是宇宙北斗七星变换之道，取千变万化、无穷无尽之原理，\n"+
	   HIR"如不是亲身体会估计很难领悟，近来你的武功已有所小成，如果你有信心参悟透彻，就看你的造化了。\n"NOR, ob, me);
   
    me->move("/d/quanzhen/midong");
	return 1;
}






//全真锄奸 job


int ask_chujian()
{
	object me,jianxi,ling;
	mixed objwhere;
	string str;
	me=this_player();
	
	if (me->query("family/family_name")!="全真教")
	{
		command("say "+me->query("name")+",你不是我教中弟子，来此作甚？\n");
		return 1;
	}
	if (me->query_skill("xiantian-gong",1)<350)
	{
		command("say "+me->query("name")+",这个任务有点危险，你的先天功不足350，来此作甚？\n\n");
		return 1;
	}
	if(me->query("job_name") == "全真锄奸") 
	{
        command("say "+me->query("name")+",你刚结束全真锄奸，还是先休息一会吧。");
	    return 1;

	}
	if(me->query("shen") <0) 
	{
        command("say "+me->query("name")+",你是邪魔外道之辈，胆敢来全真教撒野，难道是嫌弃自己命太硬了么？");
	    return 1;
	}
	
	if (me->query_temp("qzjob/jianxi"))
	{
		command("say "+me->query("name")+",你上一次任务还没完成呢。\n");
	    return 1;
	}
	if (me->query_condition("job_busy"))
	{
		command("say "+me->query("name")+",你正在任务繁忙中，还是先休息一会吧。\n");
	    return 1;
	}
	
	if (me->query_condition("qzjob_jianxi"))
	{
		command("say "+me->query("name")+",你正在执行追杀金国奸细任务中,为啥不赶快去？\n");
	    return 1;
	}

	command("say "+me->query("name")+",我最近发现金国正在派出大量奸细渗透我中原。\n");
	command("say 完颜洪烈派潜入到我大宋境内，图谋不轨。\n");
		
    if (me->query("combat_exp")<300000) 
	{
		command("say 你的经验不足3m，赶紧练功去！\n");
		return 1;
	}                 
				 
	objwhere=get_where();

	if(objwhere) str= get_place(base_name(objwhere))+objwhere->query("short");
	if (present("chongyang ling",me)) 
	{
		command("say 你身上不是还有重阳令么？\n");
		return 1;
	}
	jianxi=new("/d/quanzhen/npc/jinbing");
	
	message_vision(HIY"$n对$N说道，“"+me->query("name")+HIY"，此人乃是金国完颜洪烈的贴身护卫，乔装打扮入我大宋！”\n"NOR,me,this_object());
	message_vision(CYN"$n对$N说道，“据门中飞鸽传书得知，金国奸细应该在"HIY+str+CYN"一带活动，你速去将他除去！\n”"NOR,me,this_object());
	message_vision(CYN"$n对$N说道，“我给你一枚重阳真人所制作的令牌，以便调动教中支援，切记：杀死此贼后交还此令！”\n"NOR,me,this_object());
	
	ling=new("/d/quanzhen/npc/obj/chongyangling");

	ling->set("owner",me->query("id"));
	
	ling->move(me);
	//出现超级spuer npc
	
	if (!random(3))
	{
		message_vision(CYN"$n对$N说道，“据可靠消息，此贼子在护卫中属于高手，你要小心！”\n"NOR,me,this_object());
		me->set_temp("qzjob/super",1);
		ling->set_temp("qzjx/super",1);
		jianxi->set_temp("qzjx/super",1);
		jianxi->set_temp("type_speical");
	}
	
	jianxi->set_temp("target",me->query("id"));
    //设定npc如果20分钟不杀自动消失
	jianxi->apply_condition("npcdie_job",80);
	jianxi->move(objwhere);

	me->set_temp("qzjob/jianxi", 1);
	me->apply_condition("job_busy",20);
	me->apply_condition("qzjob_jianxi",20);
	return 1; 

}  
int ask_fangqi()
{
	
	object me=this_player();
	if (me->query_temp("qzjob"))	{
		
	    message_vision(HIC"丘处机对"+me->query("name")+"长叹一声道，“既然完不成也没关系，下次再来吧。”\n"NOR,me);
		me->delete_temp("qzjob");
		me->apply_condition("job_busy",6+random(5));
		return 1;
	}
	command("say "+me->query("name")+",你到处瞎跑，什么都没干成，要放弃啥呢。\n");
	return 1;

}
//接受物品
int accept_object(object who, object ob)
{
	
	int gold,getshen,jobs;
	
	jobs=who->query("job_time/全真锄奸");
	
	//全真锄奸接口,交付令牌

	if (ob->query_temp("killer")==who->query("id")
		&& ob->query("owner")==who->query("id")
		&& who->query_temp("qzjob/jianxi")		
		&& ob->query("id")=="chongyang ling")
	{
		getshen=1;
		gold=1+random(1);				
		
		who->set("job_name","全真除奸");			
		who->apply_condition("job_busy",3);		
		who->delete_temp("qzjob/jianxi");		
		tell_object(who,RED"\n丘处机随手将"+ob->query("name")+RED+"收入怀中，小心放好！\n"NOR);
		command("say 很好，"+who->query("name")+"，既然你把这这奸细给杀了，为国为民，侠之大者！\n");
		tell_object(who,GRN"\n丘处机拿出门派记录本，给了"+who->query("name")+HIY+chinese_number(gold)+GRN"点的门派功绩的奖励！\n"NOR);
		who->add("party/gongji",gold);

		//预留入门提示接口
		//七星绝命剑
		//悟性40以上，50整数整除
		if (random(who->query("job_time/全真锄奸"))>4000
			&& random(who->query("kar"))>28
			&& who->query("int")>40
			&& !who->query("quest/qz/qzjf/qixing/start")
			&& jobs % 50 ==0	
			&& who->query("quest/qz/dichuan"))
		{
			
				message_vision(HIC"丘处机在远处对$N竖起了大拇指，说道，“你如此辛苦为我大全真铲除奸细，真是不错”！\n"NOR,who);
				command("say "+who->query("name")+"，我就将全真剑法中关于七星绝命剑的信息透漏给你！\n");
				command("chat* thumb "+who->query("id"));
				command("rumor "+who->query("name")+"获得丘处机青睐，获得解密七星绝命剑的机会！\n");
				command("chat "+who->query("name")+"是我全真七子的核心弟子，望江湖同道多多照顾！\n");
				who->set("quest/qz/qzjf/qixing/start",1);
		}
		if (ob->query("super"))
		{
			command("say "+who->query("name")+"，你竟然把这奸细头子都给杀了，我就多奖励点门派功绩！\n");
			tell_object(who,GRN"\n丘处机又给了"+who->query("name")+HIY+chinese_number(gold)+GRN"点的额外门派功绩的奖励！\n"NOR);

			who->add("party/gongji",gold);
			TASKREWARD_D->get_reward(who,"全真锄奸",getshen,0,0,6+random(4),0,0,0,this_object());
		}else
			TASKREWARD_D->get_reward(who,"全真锄奸",getshen,0,0,3+random(4),0,0,0,this_object());
		who->set("job_name", "全真锄奸");
		who->delete_temp("qzjob");
		who->clear_condition("qzjob_jianxi");
		who->apply_condition("job_busy",3);
		who->apply_condition("qzjx_job_busy",4);
		destruct(ob);
		return 1;
	}

}
void die()
{
	object ob;
	ob=this_object();
	
	if (!query_temp("living"))
	{		
		ob = new("/kungfu/class/quanzhen/qiuchuji");
		ob->move("/d/quanzhen/laojundian");
	}
	::die();
}

//检查间隙npc位置
int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
		|| !ob->query("startroom")      // add by Yuj@SJ to void job NPC
		|| ob->query("env/invisibility")
		|| ob->query("no_quest")
		//|| member_array(ob->query("id"), no_kill_list) != -1
		|| userp(ob)
		|| ob->query("attitude")=="aggressive"
		|| ob->query("have_master")
		|| !objectp(room=environment(ob))
		|| room->query("no_fight")
		|| room->query("quest")
		|| room->query("outdoors") == "昆仑翠谷"
		|| room->query("short") == "地下黑拳市"
		|| room->query("short") == "武僧堂"
		|| strsrch(room_name = file_name(room),"/d/") != 0                    //modified by campsun 2004.2.4 为了和bx code兼容
		|| strsrch(room_name, "/d/wizard/") == 0
		|| strsrch(room_name, "/d/wuguan/") == 0
		|| strsrch(room_name, "/d/death/") == 0
		|| strsrch(room_name, "/d/mingjiao/lsd/") == 0
		|| strsrch(room_name, "/d/mingjiao/bhd/") == 0
		|| strsrch(room_name, "/d/shaolin/fumoquan") == 0
		|| strsrch(room_name, "/d/xiakedao/") == 0
		|| strsrch(room_name, "/d/luoyang/") == 0    
		|| strsrch(room_name, "/d/beijing/") == 0
		|| strsrch(room_name, "/d/baituo/") == 0)
		return 0;
	return 1;
}

//获得位置函数

object get_where()
{
	object* living;
	object target;
	int i,j;
	string str;
	
	living = livings();
	
	for (i=0;i < sizeof(living);i++)
	{
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living)-1) continue;
		
		if(check(living[j]) )
		{
			target = living[j];
			str = environment(target)->query("short");
			if( str == "武僧堂"
			 || str == HIR"心禅堂"NOR
			 || str == "金刚伏魔圈" ) continue;
			if( get_place(base_name(environment(target)))!="" )
				break;
		}
	}
	
	if(target && environment(target) ) return environment(target);
	
	return 0;
}
//同归剑法
string ask_tonggui()
{
	object me;
	int i,j;
	me=this_player();
	if (!me->query(QUESTDIR2+"over"))
	{
		return "你尚未走完射雕英雄传第二章节流程，来了也白搭！\n";
	}
	if (me->query_skill("tonggui-jian",1)<450)
	{
		return "同归剑法需要达到450大飞阶段方可修习！\n";
	}
	if (me->query_skill("force",1)<450)
	{
		return "同归剑法需要基本内功达到450大飞阶段方可修习！\n";
	}
	if (me->query("family/family_name")!="全真教")
	{
		return "你并非全真教弟子！\n";
	}
	if (time()-me->query("quest/qz/tgj/tonggui/time")<86400)
	{
		return "你来的太频繁了！\n";
	}
	if (me->query("quest/qz/tgj/tonggui/pass"))
	{
		return "你已经解开这个谜题了！\n";
	}
	command("consider ");
	message_vision(HIY"丘处机对$N说，“你很不错，这同归剑乃是我们全真七子一起参悟武技”\n"NOR,me);

	command("say 你若能练成先天功，原本这同归剑也是不用学的。\n");
	command("say 若全真七子用天罡北斗阵也是不惧西毒这个恶人。\n");
	command("say 但我七人总不能天天在一起，一旦分开为坏人所乘，那就太不值了。\n");
	command("say 为了对付西毒这个大恶人所以创立了这门同归剑法！\n");
	command("say 这样，一旦施展出来，全力强攻，为其他门人挣得一线生机！\n");
	command("say 所以这门剑法大违我全真教的以弱胜强，后发先至的奥意，但也是无奈之举！\n");
	command("say 你既然对这门功夫感兴趣我就传给你，但你要注意这门功夫放弃防御，全力强攻，弊端甚大，慎之慎之！\n");
	me->set_temp("quest/qz/tgj/tonggui/askqiu",1);
	
	command("say 事先声明，你向我请教需要扣除你的门派贡献值每次100点，如果不够你没资格请教我。\n\n\n\n");
	
    command("say 好吧，既然你如此努力，我就告诉你其中诀窍。\n");
    command("whisper "+me->query("id"));
	  
	if (me->is_busy())
	{
	  return "你正在忙碌中!\n";
	}
	me->start_busy(10);
	if (me->query("party/gongji")<100)
	{
		return "你的门派功绩不够\n";
	}
	
	me->add("party/gongji",-100);
	i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		command("say 你听懂了么。\n");
		command("pat "+me->query("id"));
		if( i<4
			&& me->query("kar")<31
			&& j >= 24 ) 
		{
			tell_object(me,HIC"\n你听了的丘处机的亲自指点，联想起早期自己所用同归剑法的种种心得，两下印照。\n"NOR);
			tell_object(me,HIR"\n忽然劳宫穴一股大力传来，你顿时感觉剑法大增，瞬间领悟了这同归剑绝技的运气法门。\n"
						NOR);
			me->set("quest/qz/tgj/tonggui/pass",1);
			log_file("quest/qztonggui", sprintf("%8s(%8s) 失败%d次后，学到同归绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/qz/tgj/tonggui/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest");
			me->start_busy(2);
			return "恭喜解密同归绝技成功!\n";
			
		}	
	   else
		{
			log_file("quest/qztonggui", sprintf("%8s(%8s) 解密同归绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/qz/tgj/tonggui/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"你听了丘处机的指点，可是对同归绝技的奥妙全然不得要领。\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/qz/tgj/tonggui/fail",1);
			me->set("quest/qz/tgj/tonggui/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest");
			me->start_busy(2);
			return "非常遗憾解密同归绝技失败"+me->query("quest/qz/tgj/tonggui/fail")+"次。\n";
		}

	


}