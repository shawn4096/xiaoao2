//added by tangfeng@SJ 2004


inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"
#define QUESTDIR6 "quest/天龙八部/武功/"

string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();
string ask_for_join();
string ask_baijian();

void create()
{
        set_name("了惑禅师", ({ "liaohuo chanshi","liaohuo","chanshi"}) );
        set("nickname", "漏尽尊者");
        set("long", "了惑禅师是本因方丈的第五位弟子，他年约四十，
红光满面。现掌理寺中待客迎宾之职，别看他笑容可
鞠，行事却最是稳重、沉着。\n");
        set("gender", "男性" );
        set("class", "bonze");
        set("attitude", "friendly");
        set("age", 41);
        set("shen_type", 1);
        set("str", 22);
        set("int", 22);
        set("con", 23);
        set("dex", 22);
        create_family("天龙寺", 14, "弟子");
        set("unique", 1);
        set("qi", 8000);
        set("max_qi", 8000);
        set("jing", 4000);
        set("max_jing", 4000);
        set("neili", 5400);
        set("max_neili", 5400);
        set("jiali", 90);
        set("combat_exp", 3500000);
        set("score", 5000);

        set_skill("force", 280);
        set_skill("qiantian-yiyang", 290);
        set_skill("dodge", 280);
        set_skill("tianlong-xiang", 280);
        set_skill("parry", 280);
        set_skill("duanjia-jianfa", 280);
        set_skill("strike", 280);
        set_skill("sword", 280);
        set_skill("buddhism", 180);
        set_skill("literate", 180);
        set_skill("qingyan-zhang", 280);
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "duanjia-jianfa");
        map_skill("sword", "duanjia-jianfa");
        map_skill("strike", "qingyan-zhang");
        prepare_skill("strike","qingyan-zhang");                
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: exert_function, "qi" :),
				(: exert_function, "jingxin" :),
				(: perform_action, "sword.fenglei" :),
		 }));

		set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
				"拜见枯荣大师"  : (: ask_baijian :),
            		"段誉" : (: askduanyu :),
		            "大理" : "这里便是大理。",
		            "天龙寺" : "这里正是天龙寺，大理段家武学的最高之地。",
		            "天龙有难" : (: tianlonghelp :),
		            "营救" : (: asksave :),
		            "搭救" : (: asksave :),
		            "萧峰" : "江湖人称南慕容、北萧峰，端得一条好汉。",
		            "营救段誉" : (: asksave :),
		            "营救萧峰" : (: askxiaofeng :),
		            "慕容复" : "江湖人称南慕容、北萧峰，听说慕容公子年级轻轻，却无所不精。",
		            "慕容博" : "我听说是，姑苏慕容不出的杰才，可惜英年早逝。",
		            "鸠摩智" : (: askjiumozhi :),
		            "六脉神剑" : "传说的我天龙寺最高绝学，我估计这辈子也未能见到。",
	]));
        setup();
        carry_object(BINGQI_D("changjian"))->wield(); 
        carry_object("/d/tls/obj/jiasha1")->wear(); 
        carry_object("/d/tls/obj/sengxie")->wear();
}
#include "liao.h";
void init()
{
	object me;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
	 	if(me->query(QUESTDIR2+"start")&& !me->query(QUESTDIR2+"over"))
		{
    	command("look "+me->query("id"));
    	command("touch "+me->query("id"));
    	command("say 有这位大侠帮忙，本寺当可高枕无忧了。"); 
		}
	}
	
}
string askjiumozhi()
{
	object me;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  		  command("nod "+me->query("id"));
		  return "听说，大轮寺第一高僧鸠摩智将来我天龙寺佛法交流，真是我大理之幸啊。";
	}
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "这魔僧竟然如此欺负我大理无人，什么吐蕃国第一佛法高僧，狗P狗P。";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "鸠摩智妄为西域第一佛法高僧，所谓口生莲花，全是一派胡言。";
  }
  /*
  大轮明王鸠摩智是吐蕃国的护国法王，但只听说他具大智慧，精通佛法，每隔五年，开坛讲经说法，西域天竺各地的高僧大德，
  云集大雪山大轮寺，执经问难，研讨内典，闻法既毕，无不欢喜赞叹而去。
  */
  command("nod");
	return "大轮明王鸠摩智是吐蕃国的护国法王，但听说他具大智慧，精通佛法，想来武功也是惊人。";
}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("hoho");
  		return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
		  return "乔峰，难不是你所迫出中原，今日所谓搭救不知什么意思。假惺惺！";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "听说那一战，"+me->query("name")+"更是威震武林，端得厉害啊。";
  }
  command("hoho");
	return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
}
string asksave()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start") &&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "小王子素来不喜武学，只爱佛法易经，平易近人，何来援救之说？";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说，前段时间小王子和镇南王又是吵架一番，至今未有回家，不知大侠可否帮助打听一下。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "只是自从万劫谷回来，小王子精神恍惚，不知所中何毒还是受何种内伤。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小王子自万劫谷回来，总是气血不定，内力怪异，才被送往我天龙寺求救来了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "竟然惹出鸠摩智这等高手，但愿王子吉人天相啊。";
  }
  command("hoho");
	return "小王子素来不喜武学，只爱佛法易经，平易近人，何来援救之说？";
}
string askduanyu()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "小王子素来不喜武学，只爱佛法易经。";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说，前段时间小王子和镇南王又是吵架一番，至今未有回家。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多谢大侠搭救小王子。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小王子自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救来了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "竟然惹出鸠摩智这等高手，但愿王子吉人天相啊。";
  }
  command("hoho");
	return "段誉正是镇南王之子。";
}
string tianlonghelp()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"over"))
  {
  	  command("haha");
  		return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
  }
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "听说，大轮寺高僧鸠摩智不日将来我天龙寺，不知是喜是祸。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
		  return "这魔僧竟然如此欺负我大理无人，什么吐蕃国第一佛法高僧，狗P。";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "多谢大侠化解这场天龙危机，还将我大理小王子得以解救。";
  }
  command("hoho");
	return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
}

string ask_baijian()
{
	object me;
	me = this_player();
	
	if (!me->query_temp("jueji/askhyd"))
	{
  		  command("nod "+me->query("id"));
		  command("say 听说，大轮寺第一高僧鸠摩智将来我天龙寺佛法交流，真是我大理之幸啊。");
		  return "他到底来不来还真说不定。";
	}
	command("? ");
    me->delete_temp("jueji/askhyd");
	me->set_temp("jueji/baijian",1);
	return "欢迎鸠摩智大师的弟子来拜见大天龙寺，不过你有什么凭证没有？";	

}

int accept_object(object who, object obj)
{
	
	if (who->query_temp("jueji/baijian")
		&& obj->query("id")=="huangjin baitie"
		)
	{
		who->set_temp("hydjj/receive",1);
		write(HIY"你将黄金拜帖递给了了惑禅师，了惑禅师接过后仔细看了下封皮，果然是大轮寺首座鸠摩智的亲笔题词。\n"NOR);
		command("say 既然是鸠摩智大师的亲传弟子，那就请稍等一会我给里面传个话。");
		command("chat 欢迎大轮寺掌门鸠摩智座下弟子"+who->query("name")+"前来天龙寺！");
		//command("chat 欢迎大轮寺掌门鸠摩智座下弟子前来天龙寺！有请"+);
		write(HIC"不多会，了惑禅师又跑了回来，说了声“师祖叔请阁下到牟尼堂！”，\n"NOR);
		obj->move(this_object());
		destruct(obj);
		who->delete_temp("jueji/baijian");		
		return 0;
	}
}