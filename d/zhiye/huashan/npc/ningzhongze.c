// NPC: /d/huashan/npc/ningzhongze.c
// Date: Look 99/03/25
// Lklv Modify at 2001.10.18
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_jianzong();
string ask_wushuang();
int do_qingjiao();
void create()
{
        set_name("宁中则",({"ning zhongze","ning"}));
        set("title","华山派第十三代掌门夫人");
		set("nickname",HIC"无双无对，宁氏一剑"NOR);
        set("long", "她是个不让须眉的女中豪杰，华山派君子剑岳不群的夫人。\n");
        set("gender", "女性");
        set("age", 40);
        set("attitude", "friendly");
        set("per", 28);
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("max_qi",3000);
        set("max_jing", 2000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("eff_jingli", 2000);
        set("jiali", 50);
        set("combat_exp", 4500000);
        set("score", 9000);
        set("quest/hsjf/wushuang","pass");
       
        set_skill("cuff",   350);

		set_skill("strike",   350);
        set_skill("hunyuan-zhang",   350);

		set_skill("sword",  380);
        set_skill("dodge",  350);
        set_skill("force",  400);
        set_skill("parry",  350);
        set_skill("literate",200);
        set_skill("poyu-quan", 350);
        set_skill("huashan-qigong", 400);
        set_skill("huashan-jianfa", 380);
        set_skill("huashan-shenfa", 350);
        set_skill("zhengqi-jue", 200);
		set_skill("ziyin-yin", 200);
        map_skill("force", "huashan-qigong");
        map_skill("dodge", "huashan-shenfa");
 
	    map_skill("strike", "hunyuan-zhang");

		map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");
	    map_skill("cuff","poyu-quan");

	    prepare_skill("strike", "huanyuan-zhang");

        set("chat_chance_combat",60);
        set("chat_msg_combat", ({
		    (: perform_action, "sword.jianzhang" :),
			(: perform_action, "sword.wushuang" :),
			(: exert_function, "yujianshi" :),
	    }));
		set("inquiry", ([
		
		 "无双无对宁氏一剑"	: (: ask_wushuang :),
         //"剑气之争"      : (: ask_qizong :),
         "华山剑宗"      : (: ask_jianzong :),
	    ]));

	    create_family("华山派",13,"弟子");

        setup();

	carry_object(BINGQI_D("sword"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
}
void init()
{
   ::init();
   add_action("do_qingjiao", "qingjiao");
}
void attempt_apprentice(object ob)
{
        mapping fam;
        if ( mapp(fam=ob->query("family"))
         && (string)fam["family_name"] != "华山派"
         && (int)ob->query("is/huashan")==1 ) {
		message_vision("$N！你这个华山派的叛徒还回来干什么 ？\n", ob );
		command("slap "+ob->query("id"));
		return;
        }
	if ( ob->query("fengset")) {
		command("say 你不是已经拜了剑宗的前辈为师了么？");
		return;
	}
		        if(ob->query("quest/huashan")=="剑宗"){
                command("heng");
                command("say 哼哼！剑宗弟子早已离开华山，不再是华山派弟子，你又来这里，难道是想争夺这掌门之位？");
                return;
        }
        if( (string)ob->query("gender") != "女性" ) {
                command ("say 对不起，我只收女弟子。");
                return;
        }
		if ( ob->query_skill("huashan-qigong",1) <300 ){
		command("say 我只收女徒，" + RANK_D->query_respect(ob) + "你的华山气功不足300，还是请回吧。");
		return;
	}
        if ((int)ob->query("shen") < 1000000) {
		command("say 我华山派乃是堂堂名门正派，对弟子要求极严,不足1m。");
		command("say 在德行方面，" + RANK_D->query_respect(ob) + "是否还做得不够？");
		return;
        }
        command("say 咦，不错的小女孩嘛，我就收下你了。");
        command("recruit " + ob->query("id"));
	    ob->set("title","华山派气宗亲传弟子");
        ob->set("quest/huashan","气宗");
        return;
}


string ask_jianzong()
{
   object me=this_player();
   if (me->query("family/family_name")!="华山派" )
     return "你不是华山弟子，来打听这个问题，想要何为？\n";
   if (me->query("quest/huashan")=="剑宗" )
     return "你已经是剑宗弟子，早已被开除出华山，来此何为？\n";
   if (me->query_skill("huashan-jianfa",1)<100)
     return "你还是好好练习武技吧，你如此弱小，知道这么多也不好。？\n";
   command("sigh "+me->query("id"));
   command("say 当初剑宗和气宗本是一家，后来因为所见不和，导致本门内剑气之分，具体详情还是去问你师傅去吧。\n");
   me->set_temp("jianzong/askning",1);
   return "宁中则仿佛想起了什么往事，脸上带有极其惊惧的神情.\n";

}

string ask_wushuang()
{
   
    object me=this_player();
  
   //if (!arg || arg!="无双无对宁氏一剑")
   //  return notify_fail("我创造如此厉害的剑法你居然都记不住，你到底要问什么？\n");
   if (me->query("family/family_name")!="华山派" )
      return "你不是华山弟子，来打听这个问题，想要何为？\n";
   if (me->query("quest/huashan")=="剑宗" )
      return "你已经是剑宗弟子，早已被开除出华山，来此何为？\n";
   if (me->query_skill("huashan-jianfa",1)<300)
      return "你还是好好练习武技吧，你如此弱小，知道这么多也不好。？\n";
   if (me->query("hsjj/wushuang")=="pass")
      return "你已经习得无双无对宁氏一剑，还来啰嗦什么？\n";
   if (time()-me->query("hs/wushuang/time")<86400)
      return "你的解密时间不足，来的太勤快些了？\n";
   
   if (!present("yue buqun",environment(me)))
   {
	   
       me->delete_temp("wushuang/askning1");
	   me->set_temp("wushuang/askning2",1);
       return "宁中则说道，” 无双无对乃是我自己根据华山剑法创造一门剑法绝技,你若真想学习，可以向我请教(qingjiao)。“\n";
	  
   }else {
      
	   me->set_temp("wushuang/askning1",1);
	   return "宁中则说道，”这里人多眼杂，怕有奸细，既然你想学，就到东练武场等我，我一会就到。“\n";
   }

}

int do_qingjiao()
{
      int i,j;
      object me, ob, weapon, weapon1;

	  me = this_player();
	  ob = this_object();
      weapon=me->query_temp("weapon");
	  weapon1 = ob->query_temp("weapon");
      if (!me->query_temp("wushuang/askning2"))
        return notify_fail("你要请教什么？\n");
      if (!weapon||weapon->query("skill_type")!="sword")
         return notify_fail("真是蠢材，你不用剑如何与你师娘对招？\n");
	  if (!weapon1)
         return notify_fail("你师娘手中无剑，施展不了华山绝技无双无对！\n");
	  if (me->query_skill_mapped("sword")!="huashan-jianfa"||me->query_skill_mapped("parry")!="huashan-jianfa")
	     return notify_fail("你没有激发华山剑法，如何能领悟岳夫人的绝技！\n");
     
	  message_vision(HIG"$N对着$n说道：“请师娘指点【无双无对，宁氏一剑】绝技！”\n"NOR, me,ob);
	  ob->add_temp("apply/damage",-100);
	  ob->set("jiali",1);
	  COMBAT_D->do_attack(ob, me, weapon, 1);
		
	 
	  message_vision(HIC"\n\n$n侧过身来，从一名女弟子腰间拔出一柄长剑，向$N说道：“使快剑！”$N道：“是！”嗤的一声\n"+
	                 "长剑绕过了$n的身子，剑锋向$n后腰勾了转来。$n弹身纵出，更不理会$N从后削来的一剑，手中\n"
                     +"长剑径取$N胸口，也是快捷无伦。两人以快打快，尽是进手招数，并无一招挡架防身。瞬息之间，师徒俩已拆了二十余招。\n"NOR,me,ob);
      COMBAT_D->do_attack(ob, me, weapon, 1);
	  COMBAT_D->do_attack(ob, me, weapon, 1);
	  //COMBAT_D->do_attack(ob, me, weapon, 1);
	  COMBAT_D->do_attack(ob, me, weapon, 1);	 
	 message_vision(HIY"\n\n却见二人越斗越快，$N到得后来，已无暇再说任何话语，每逢给$N一剑制住，只是摇头示意\n"
                        +"$n长剑使得兴发，突然间一声清啸，剑锋闪烁不定，围着$N身围疾刺，银光飞舞，众人看得眼\n"
						+"都花了。猛地里她一剑挺出，直刺$N心口，当真是捷如闪电，势若奔雷。$N大吃一惊，叫道：“师娘！\n"
						+"其时长剑剑尖已刺破$N衣衫。$n右手向前疾送，长剑护手已碰到$N的胸膛，眼见这一剑是在$N身上\n"
						+"对穿而过，直没至柄。只听得叮叮当当之声不绝，一片片寸来长的断剑掉在$N的脚边。$n哈哈一笑，\n"
						+"缩回手来，只见$n手中的长剑已只剩下一个剑柄。\n"NOR,me,ob);
   	  COMBAT_D->do_attack(ob, me, weapon, 1);
	  COMBAT_D->do_attack(ob, me, weapon, 1);	 
	i=random(10);
	j=random(me->query("kar"));
	if (me->query("kar")<31
		&&j>=25
		&&i>5	)
	{
       message_vision(HIG"\n\n$N灵光一闪，忽然明白了这无双无对宁氏一剑的奥秘，不禁欣喜若狂。\n"NOR,me);
	   command("smile "+me->query("id"));
	   command("say 真心不错，能在这么短时间内领悟此招绝技，你的悟性真是不赖。\n");
	   command("chat 恭喜"+me->query("name")+"解开无双无对宁氏一剑。\n");
	   command("chat* congra "+me->query("id"));	 
	   command("chat* pat "+me->query("id"));
	   log_file("quest/wushuang",sprintf("%s(%s)终于解开无双无对宁氏一剑，威力大增。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("hs/wushuang/fail"),me->query("combat_exp"),me));
	   me->set("hsjj/wushuang","pass");	  
	   destruct(ob);
	   me->delete_temp("wushuang/askning2");
	   return 1;
	}
	else
	{
		message_vision(HIY"\n\n$N虽然看了一遍无双无对，宁氏一剑，但并未彻底领悟此招绝技。\n"NOR,me);
		log_file("quest/wushaung",sprintf("%8s%-10s解密无双无对宁氏一剑失败，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/slbw/fail"),me->query("combat_exp"),me));
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("hs/wushuang/fail",1);
		me->set("hs/wushuang/time",time());
		me->delete_temp("wushuang/askning2");
	    destruct(ob);
        return 1; 
	}   
   return 1;

}
int prevent_learn(object ob, string skill)
{
	
	if (skill=="ziyin-yin"||skill=="zhengqi-jue")
	{
		write("这种功夫只能靠个人从书中参悟所得，你从师父这儿能学到什么?\n");
		return 1;
	}
	return 0;
}