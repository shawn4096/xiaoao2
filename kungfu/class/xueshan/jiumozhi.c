// jiumozhi.c 鸠摩智
// by iceland
// Modified by Lklv 2001.10.23
// Modified by tangfeng 2004
// mod by sohu 2014
inherit F_MASTER;
#include <ansi.h>
inherit NPC;
#include "jiumozhi.h"

#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"

string askduanyu();
string ask_hyd();
string ask_lx();
string ask_jueji();
string hyd_jueji();
string ask_jianpin();
string ask_rmdf();
string ask_jiasha();

//int start_condition(object ob);
int power_condition(object me,object ob,int p);

void create()
{
        set_name("鸠摩智", ({ "jiumo zhi", "jiumozhi","zhi" }));
        set("long",@LONG
他身材匀称，脸上神采飞扬，隐隐似有宝光流动，便如是明珠宝玉，自然生辉，
只消向他看得几眼，便生钦仰亲近之意。
LONG
        );
        set("title", HIY "大轮寺掌门" NOR);
        set("gender", "男性");
		set("nickname","大轮明王");
        set("class", "mizong");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 45);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("per", 25);
        set("max_qi", 36500);
        set("eff_jingli", 7500);
        set("max_jing", 6000);
        set("neili", 34000);
        set("max_neili", 34000);
        set("jiali", 250);
        set("combat_exp", 15000000);
        set("score", 290000);
        set("unique", 1);
        set("lx/gree",12);
		set("quest/dls/longxiang/pass",13);
		set("quest/dls/hyd/pass",1);
		set("mishikey",1);

        set_skill("mizong-fofa", 200);
        set_skill("literate", 300);
        set_skill("force", 500);
        set_skill("longxiang-boruo", 500);
        set_skill("dodge", 500);
	    set_skill("poison", 100);
        set_skill("yuxue-dunxing", 500);
		set_skill("hand", 500);
		set_skill("dashou-yin", 500);
        set_skill("strike", 550);
        set_skill("huoyan-dao", 550);
        set_skill("parry", 500 );
        set_skill("staff",500);
        set_skill("wushang-dali",500);

        map_skill("force", "longxiang-boruo");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("strike", "huoyan-dao");
        map_skill("staff","wushang-dali");
        map_skill("parry", "huoyan-dao");
        map_skill("hand", "dashou-yin");

        prepare_skill("strike","huoyan-dao");
        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: exert_function, "shield" :),
				(: exert_function, "longxiang" :),
				(: perform_action, "strike.daoqi" :),
				(: perform_action, "strike.fen" :),
				(: perform_action, "strike.ran" :),
				(: perform_action, "strike.biyan" :),
                (: perform_action, "strike.honglian" :), }));

        create_family("大轮寺", 10, "弟子");
        set("class", "huanxi");
        set("chat_chance", 2);
        set("chat_msg", ({
			"鸠摩智低头沉思，说道：嵩山少林寺，大理天龙寺，哼！我雪山大轮寺哪点比不上？！\n",
			"鸠摩智说道：火焰刀乃天下第一武技，哼有机会我终将杀上天龙寺，掌劈天龙，脚踢少林！\n",
			"鸠摩智将双掌举到眼前瞧了瞧，冷笑了一声：天下能有几人是我的敌手？！\n",
		}) );
		set("inquiry",([
					"段誉" : (: askduanyu :),
					"大轮寺绝技" : (: ask_jueji :),
					"龙象般若功鉴品" : (: ask_jianpin :),
					"燃木刀法绝技" : (: ask_rmdf :),
					"碧烟纵横绝技" : (: hyd_jueji :),
					"十三龙象袈裟" : (: ask_jiasha :),

					"大轮寺" : "这里便是大轮寺。",
					"天龙寺" : "天龙寺是大理段家武学的最高之地，传说的六脉神剑就在其中。",
					"营救段誉" : (: askduanyu :),
					"慕容复" : "江湖人称南慕容、北萧峰，听说慕容公子年级轻轻，却无所不精。",
					"慕容博" : "真乃姑苏慕容不出的杰才，可惜英年早逝。",
					"六脉神剑" : "传说的我天龙寺最高绝学，我一定要想办法此生得见。",
		]));
	    add_temp("apply/armor", 60);
        add_temp("apply/damage", 50);
        add_temp("apply/attack", 160);
        add_temp("apply/dodge", 50);
        setup();
        carry_object("/d/xueshan/npc/obj/longxiang-jiasha")->wear();
        add_money("gold",1);
}
string ask_jianpin()
{

	object me;
	int i;
	me=this_player();
	i = (int)me->query_skill("longxiang-boruo", 1);   
    if (me->query("quest/dls/longxiang/pass")==11)
    {
		 tell_object(me,HIW"龙象般若功十三层你现在修炼到第"HIR+me->query("lx/gree")+HIW"层。\n");
	     me->set("lx/gree",11);
		 return "哇！你居然解开龙象波若功第11层了，恭喜你了！\n";
    }
	if (me->query("quest/dls/longxiang/pass")==12)
    {
		 tell_object(me,HIW"龙象般若功十三层你现在修炼到第"HIR+me->query("lx/gree")+HIW"层。\n");
	     me->set("lx/gree",12);
		 return "哇！你居然解开龙象波若功第12层了，恭喜你了！\n";
    }
	if (me->query("quest/dls/longxiang/pass")==13)
    {
		 tell_object(me,HIW"龙象般若功十三层你现在修炼到第"HIR+me->query("lx/gree")+HIW"层。\n");
	     me->set("lx/gree",13);
		 return "哇！你居然解开龙象波若功第13层了，恭喜你了！\n";
    }
	if (me->query("lx/gree")>10)
	{
		 tell_object(me,HIW"龙象般若功十三层你现在修炼到第"HIR+me->query("lx/gree")+HIW"层。\n");
	     me->set("lx/gree",1);
		 return "恭喜你了！\n";
	}
	if (i < 100)
	{
		 tell_object(me,HIW"龙象般若功十三层你才刚刚起步。\n");
	     me->set("lx/gree",1);
		 
	}
	else if (i < 150)
	{
		//150
		 tell_object(me,HIW"龙象般若功十三层你已经修炼到了第一层了。\n");
	     me->set("lx/gree",1);
	}
	else if (i < 200)
	{
		//200
		tell_object(me,HIW"龙象般若功十三层你已经修炼到了第二层了。\n");
        me->set("lx/gree",2);
	}
	else if (i < 250) 
	{
		//250
		tell_object(me,HIW"龙象般若功十三层你已经修炼到了第三层了。\n");
	    me->set("lx/gree",3);
	}
	else if (i < 300)
	{
		//300
		tell_object(me,HIW"龙象般若功十三层你已经修炼到了第四层了。\n");
	    me->set("lx/gree",4);
	}
	else if (i < 350)
    {
		//350
		tell_object(me,HIW"龙象般若功十三层你已经修炼到了第五层了。\n");
	     me->set("lx/gree",5);
	}
	else if (i < 400)
	{
		//400
		tell_object(me,HIW"龙象般若功十三层你已经修炼到了第六层了。\n");
	    me->set("lx/gree",6);
	}
	else if (i < 450)
	{
		//450
		tell_object(me,HIW"龙象般若功十三层你已经修炼到了第七层了。\n");
	    me->set("lx/gree",7);
	}
	else if (i < 500)
    {
		//500
		tell_object(me,HIW"龙象般若功十三层你已经修炼到了第八层了。\n");
	     me->set("lx/gree",8);
	}
	else if (i < 550)
	{
		//550
		tell_object(me,HIW"龙象般若功十三层你已经修炼到了第九层了。\n");
	    me->set("lx/gree",9);
	}
	else if (i >= 550 )
	{
		tell_object(me,HIW"龙象般若功十三层你已经修炼到了第十层了，已经具备了十龙十象的大力。\n"
					+"以后修炼就靠你的毅力和悟性了,非大彻大悟者是难以达到这等境界的。\n\n");
	    me->set("lx/gree",10);
	}
	return "";

}


string askduanyu()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR2+"start" ))
  {
  	  command("?");
  		return "小僧不晓得段誉，不知道哪方高手。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query_temp(QUESTDIR2+"jiumozhi")&& !me->query(QUESTDIR2+"over"))
	{
  	  command("shrug "+me->query("id"));
  		return "小僧不晓得段誉，不知道哪方高手。";
  }
	if (me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"jiumozhi")&& !me->query_temp(QUESTDIR2+"kill_dizi")&& !me->query(QUESTDIR2+"over"))
	{
  	  command("flop "+me->query("id"));
  		return "我知道你知道剧情，但是好像还不应该临到我吧？去你的天龙寺看门去。";
  }
	if (me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"kill_dizi")&& !me->query_temp(QUESTDIR2+"caught")&& !me->query(QUESTDIR2+"over"))
	{
  	  command("flop");
  	  command("kick "+me->query("id"));
  		return "我知道你知道剧情，但是好像还不应该临到我吧？先去本因那里。";
  }
	if (me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"caught") && !me->query_temp(QUESTDIR2+"askzhi")&& !me->query(QUESTDIR2+"over"))
	{
  	  command("sneer "+me->query("id"));
  	  kill_ob(me); 
  	  set("quest/try_fight",1);
  	  set("quest/try_fight_id",me->query("id"));
  	  command("haha "+me->query("id"));	  
  	  power_condition(me,this_object(),200+random(100));  	  
		  return "不错，大理段公子正在我这里，你要带走还是拿点本事出来吧。\n";
  }
	if (me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"caught") && me->query_temp(QUESTDIR2+"askzhi")&& !me->query(QUESTDIR2+"over"))
	{
  	  command("sneer "+me->query("id"));
  	  kill_ob(me); 
  	  power_condition(me,this_object(),300+random(100));  	  
		  return "不错，大理段公子正在我这里，你要带走还是拿点本事出来吧。\n";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("sneer "+me->query("id"));
		  return "不错，大理段公子正在我这里逗留几天，不过现在早不在这里了。\n";
  }
	return "段誉正是大理镇南王之子。";
}
void attempt_apprentice(object ob)
{
        if( (string)ob->query("gender") == "无性" ) {
                command("say 施主身体残缺，虽说佛祖普渡众生，可是...\n");
                return;
        }
        if ((string)ob->query("family/family_name") != "大轮寺") {
                command("say"+ RANK_D->query_respect(ob) +
                        "不是本寺弟子，在这里捣什么乱？！");
                return;
        }
        if ((int)ob->query_skill("longxiang-boruo", 1) < 350) {
                command("say 我大轮寺各种武功均和龙象般若内功相辅相成。不小飞别来找我。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多钻研钻研本门的内功吧。");
                return;
        }
        if (((int)ob->query_con() < 50) || ((int)ob->query_str() < 60)){
                command("hmm");
                command("say 这位" + RANK_D->query_respect(ob) +
                	"臂力不足60，根骨不足50，体质似乎不适合学习我火焰刀神功，还是尽早想想别的出路吧。");
                return;
        }
	command("say 看你根骨精奇，确实是练武的好材料，好吧，就让我来好好调教调教你吧。");
	command("recruit " + ob->query("id"));
	ob->set("title",  "大轮寺掌门座下弟子");
}

int power_condition(object me,object ob,int p)
{
	int i;
	if(!me || !ob) return 0;
	if(environment(me)!=environment(ob)) return 0;
	//注意，小于15m则默认系统属性，大于15m后增强
 	i=me->query("max_pot");
	/*if(p<150) p=150;
	if(i<p) i=p;
	i=i-100;*/	
	//ob->set_skill("mizong-fofa", i+random(50));
	ob->set_skill("literate", i+random(50));
	ob->set_skill("force", i+random(50));
	ob->set_skill("longxiang-boruo",i+random(50));
	ob->set_skill("dodge", i+random(50));
	ob->set_skill("poison", 200);
	ob->set_skill("yuxue-dunxing", i+random(50));
	ob->set_skill("strike", i+random(50));
	ob->set_skill("huoyan-dao", i+random(50));
	ob->set_skill("parry", i+random(50));
	ob->set_skill("staff",i+random(50));
	ob->set_skill("wushang-dali",i+random(50));
	i=me->query("combat_exp");
	
	ob->set("combat_exp",i+random(1000000));
	i=me->query("neili");	  
	if(i<15000) i=15000;
	ob->set("neili", i);	  
	i=me->query("max_neili");	  
	if(i<8000) i=8000;
	ob->set("max_neili", i);	  
 	i=me->query("max_qi");	  
	ob->set("max_qi", i*2);	  
	ob->set("eff_qi", ob->query("max_qi"));	
	ob->set("qi", ob->query("max_qi"));	
	return 1;
}

void die()
{
	object me,ob=this_object();
	
	if(ob->query("quest/try_fight"))
	  if(ob->query("quest/try_fight_id"))
	  {
	  	me=find_player(ob->query("quest/try_fight_id"));
	  	if(!me) 
		{
			::die();
			return 0;
		}
	    if(environment(me)!=environment(ob))
		{
			::die();
			return 0;
		}
	    if (me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"caught") && !me->query_temp(QUESTDIR2+"askzhi")&& !me->query(QUESTDIR2+"over"))
	        me->set_temp(QUESTDIR2+"askzhi",1);
	    ob->delete("quest/try_fight");
	    ob->delete("quest/try_fight_id");
     }
	::die();
}

string ask_jueji()
{ 
	object me, ob;
	int i,time;

	ob = this_object();
	me = this_player();
    
	if (!me->query("family")
		|| me->query("family/family_name")!="大轮寺")
		//|| me->query("family/master_id")!="jiumo zhi"
		return "你非我弟子，来问此问题作甚？";
    if ((int)me->query("lx/gree")<10)
    {
		return "你的龙象般若神功连第十层都尚未修炼到，来此作甚？";
    }
	if( me->query_skill("longxiang-boruo", 1) < 450 )
		return RANK_D->query_respect(me) + "，你的龙象般若功力造诣不够450，还无法领悟我派火焰刀精要所在！";
	

	command("pat "+me->query("id"));
	command("say 我大轮寺乃是西部最强大的门派，寺中总共有三大绝技。");
	command("say 第一门绝技乃是我寺镇寺之宝，叫【龙象般若功】。");
	command("say 第二门绝技乃是我平生得意武学，乃是【火焰刀绝技】，凭此我曾横扫黑教。");
	command("say 第三门绝技乃是你师叔金轮法王的护教神技，【降伏轮绝技】。");
	command("say 你想学哪门神功？请用answer xx 回答。");
	me->set_temp("jueji/askjmz",1);
	add_action("do_answer","answer");
	return "鸠摩智坐在那里，甚是安详，堪称一代高僧大德。";
}
 
int do_answer(string arg)
{
   object key;
	object me=this_player();
	 if (!me->query_temp("jueji/askjmz"))
		return notify_fail("你想干什么？");
	if (!arg) return notify_fail("鸠摩智冷笑几声，沉默不语。");
  //龙象般若功
   
	
	if (arg=="龙象般若功")
	{
      command("say 好吧，既然你想参悟此门神功，那你就去吧。");
	  command("say 这门神功不仅仅靠的是悟性，更靠的是意志坚韧。");
	  command("say 好，我这里有一把钥匙，你去看看是否有这个机缘。");
	  if( me->query("quest/dls/longxiang/pass")>12 )
		return notify_fail( RANK_D->query_respect(me) + "，你不是已经解开了么？");
	  if (time()-me->query("quest/dls/longxiang/time")<86400)
		return notify_fail( RANK_D->query_respect(me) + "，你来的太勤快了？");
	  if (me->query_skill("longxiang-boruo",1)<500)
		return notify_fail( RANK_D->query_respect(me) + "，你的龙象般若功不足500，不用来！\n");
	  if (me->query_skill("longxiang-boruo",1)<500)
		return notify_fail( RANK_D->query_respect(me) + "，你的龙象般若功不足500，不用来！\n");
	  if (me->query("int")<40)
	  {
		return notify_fail("鸠摩智冷笑几声，这龙象般若功需要绝大悟性，先天悟性不足40别来找我！。");
	  }
	  if (this_object()->query("mishikey")>0)
	  {
		  key=new("d/xueshan/npc/obj/goldkey");
		  key->move(me);
		  command("say 你好好珍藏，不要弄丢了。");
		  
		  me->set_temp("lxbr/start",1);

		  this_object()->add("mishikey",-1);
		  me->move("d/xueshan/mishi");
		  command("rumor 据说"+me->query("name")+"得到一枚雪山派密室的金钥匙！\n");
	  }
	  else {
       command("say 今天我有点累了，你明天再来。");
	  }
	  
	   me->delte_temp("jueji/askjmz");
	  return 1;
	 }
	 //火焰刀
	 if (arg=="火焰刀绝技")
	 {
       if( me->query("quest/dls/hyd/pass")){
		   me->set("title",HIY"鸠摩智座下亲传弟子"+HIR"火焰刀传人"NOR);
		   me->set("mytitle/quest/dlshydtitle",HIY"鸠摩智座下亲传弟子"+HIR"火焰刀传人"NOR);
		   return notify_fail( RANK_D->query_respect(me) + "，你不是已经解开了么？\n");

	  }
	  if (me->query("family/master_id")!="jiumo zhi")
		 return notify_fail("鸠摩智冷笑几声，喝道，连我的弟子都不算，还想去天龙寺给我丢人现眼么？");
	  
	  command("laugh "+me->query("id"));
	  command("say 火焰刀绝技乃天下第一武技！");
	  command("say 这门绝技乃是我成名武技，既然你想学，那好我就交给你一件任务去完成。");
	  command("say 我曾答应慕容博替他弄到大理天龙寺的镇寺之宝六脉神剑剑谱。");
	  command("say 听慕容博讲，这门六脉神剑端的是奥妙无穷，我也很是好奇。");
	  command("say 你就替我跑一趟，去把那本秘籍给我抢回来，若抢回来我就传授你这门火焰刀绝技。");
	  command("say 若抢不回来，也不再来烦我！");
	  if( me->query("quest/dls/hyd/pass") )
		return notify_fail( RANK_D->query_respect(me) + "，你不是已经解开了么？");
	  if (time()-me->query("quest/dls/hyd/time")<86400)
		return notify_fail( RANK_D->query_respect(me) + "，你来的太勤快了？\n");
	  if (me->query_skill("longxiang-boruo",1)<500)
		return notify_fail( RANK_D->query_respect(me) + "，你的龙象般若功不足500，不用来！\n");
	  if (me->query_skill("huoyan-dao",1)<500)
		return notify_fail( RANK_D->query_respect(me) + "，你的火焰刀不足500，不用来！\n");
	  if (me->query("con")<40)
		return notify_fail( RANK_D->query_respect(me) + "，这火焰刀很看根骨，你根骨不足40，别来找我！\n");
	  me->set_temp("jueji/askhyd",1);
	  me->delete_temp("jueji/askjmz");
	  new("d/xueshan/npc/obj/goldletter")->move(me);
	  command("say 这是我写给大理天龙寺枯荣大师的拜帖，你拿此拜帖去吧！");
	  command("say 可不要让师傅我失望啊！");
	  command("chat 今天我派出我的亲传弟子"+me->query("name")+"为我出使大轮寺，还望各位掌门眷顾，鸠摩智不胜感激！");

	  return 1;
	 }
//降伏轮
	 if (arg=="降伏轮绝技")
	 {
		command("say 这门神功乃是你师叔金轮法王的独门绝技，你去找他试试吧。");
		if( me->query("quest/wulun/pass") )
			command( "say 这位你不是已经解开了么？");
		if (me->query("str")<32)
			return notify_fail( RANK_D->query_respect(me) + "，这降伏轮最看臂力，你先天臂力不足32，我看去也是白搭！\n");
		return 1;
	 }

}
string hyd_jueji()
{ 
	

	object me, ob;
	int i,j,x;
	
	ob = this_object();
	me = this_player();       
	if (!me->query("quest/dls/hyd/biyan/givebook"))
	{
		me->add_temp("hydjj/askjueji",1);
		command("say 你这么懒，连天龙寺都没去，再来烦我，小心我杀了你！");
		if ((int)me->query("hyd/askjueji")>3)
		{
			command("say 滚！");
			command("kick "+me->query("id"));
			me->move("d/xiangyang/damen");
		}
		return "";
	}
	if (!me->query("family")
		|| me->query("family/family_name")!="大轮寺"
		|| me->query("family/master_id")!="jiumo zhi")
		return "你非我弟子，来问此问题作甚？";

	
    if( me->query_skill("longxiang-boruo", 1) < 500 )
		return "你的龙象般若造诣不够，还无法领悟我派火焰刀精要所在！";
	if( me->query("quest/dls/hyd/pass")>12 )
		return "你已经解密了这个超级quest，又何故开此玩笑呢？";

    if( me->query_skill("huoyan-dao", 1) < 500 )
		return "你的火焰刀造诣不够450，还无法领悟我派五轮大转的精要所在！";
	if ((int)me->query("con")<40)
		return "这火焰刀很看根骨，你根骨不足40，别来找我！\n";
	
	
	if( time()- me->query("quest/dls/hyd/time")<86400)
		return "嗯？你不是刚来请教过我这门秘籍的奥秘吗？还是再努力段时间吧！";

   
	message_vision(HIY"$N严肃的看着$n，慢慢说道：“我派的火焰刀绝技讲究的是轻灵，千变万化，无一定之规，最终循环往复，\n"
						"你看好了，我给你演示一遍，看你自己的悟性了。\n"+
	  HIR"\n\n\n$N纵身而已，手掌翻飞，劲气汹涌，本来往复，疾驰如电，迅捷无比。看的$n眼花缭乱\n"NOR+
	  HBBLU"\n\n$N将火焰刀气动念既至的意境施展出来，数股劲力随着碧烟而去，看似缓慢，但却迅捷无比\n\n"NOR+
	  HBBLU+HIG"\n\n$N运起龙象般若功，右掌虚按，左掌斜斜劈出，掌上已蓄积真力，使出的正是「火焰刀」中的一招手刀绝技\n"NOR+
	  HBBLU+HIG"\n\n$N此刻双掌竖起，狠砍狠斫，全是少林派武功的路子。$N一刀劈落，「火焰刀」劲气翻涌，波的一轻响\n"NOR+
	  HBBLU+HIG"\n\n$N运使「火焰刀」绝技，奇妙无方，动念即至，刀气汹涌，两道碧烟忽然卷向$n的右臂\n"NOR+
	  HBBLU+HIG"\n\n$N双掌如抱圆球，内力运出，六道碧烟慢慢向外蜿蜒而去，遥遥指着击向$n的诸身大穴\n"NOR+
	  HBBLU+HIG"\n\n$N连运内功三次强劲，「火焰刀」绝技威力倍增，沛然莫能抵御，绿烟嗤嗤作响，向$n猛烈冲击而去\n"NOR+
	  HBBLU+HIG"\n\n$N运使火焰刀中一招“白虹贯日”，乃招式中精妙之作，一刀便要将向$n的左腿砍了下来\n"NOR, ob, me);
 
    i = 20;
	if(me->query("m-card-vip")) i =  18;
	if(me->query("y-card-vip")) i =  15;
	if(me->query("buyvip"))     i =  10;
	i=random(i);

	j=random(me->query("kar"));
	x=random(me->query("con"));

	command("say 本门五轮大法唯有和龙象般若刚猛之力相配合方能发挥最大威力，这一点你千万要记住。\n");
	command("pat "+me->query("id"));
	if( i<4 
		&& me->query("kar")<31
		&& x >= 35
		&& j >= 25 ) 
	{
		tell_object(me,HIY"\n你听了鸠摩智的指点，对碧烟纵横的奥妙颇有心得。\n"NOR);
		tell_object(me,HIG"\n你试图将内息冲到劳工穴中，突然只觉手三阳经上一股热气直通双手，手上经脉不禁豁然一轻。\n"
			             +"你下意识地顺手一挥，一阵破空声传来，波的一声，劲力强劲的很。\n"
						 +"你终于领悟了这门碧烟纵横绝技的运用法门。心中大喜之下，后续招式连绵不绝而出。\n"
						 +"这招式劲力运使法门第一次通行时甚是艰难，任督两脉既通，经脉熟悉后，势如破竹。\n"
						 +"顷刻之间，你手上经脉尽通，领悟了火焰刀碧烟纵横绝技。\n"NOR);
		me->set("quest/dls/hyd/pass",1);
		log_file("quest/hydjueji", sprintf("%8s(%8s) 失败%d次后，学到火焰刀碧烟纵横绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/dls/hyd/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));
		me->set("title",HIY"鸠摩智座下亲传弟子"+HIR"火焰刀传人"NOR);
		 me->set("mytitle/quest/dlshydtitle",HIY"鸠摩智座下亲传弟子"+HIR"火焰刀传人"NOR);
		me->delete_temp("hydjj/givejianpu");
		return "恭喜解密火焰刀碧烟纵横成功!\n";
		
	}	
   else
	{
		log_file("quest/hydjueji", sprintf("%8s(%8s) 解密碧烟纵横绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/dls/hyd/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了鸠摩智的指点，可是对碧烟纵横的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/dls/hyd/fail",1);
		me->set("quest/dls/hyd/time",time());
		me->start_busy(1+random(3));
		me->delete_temp("hydjj/givejianpu");
		return "非常遗憾解密火焰刀碧烟纵横失败"+me->query("quest/dls/hyd/fail")+"次。\n";
	}
}

int accept_object(object who, object obj)
{
	int i,j;
	i=2+random(10);
	j=1000+random(5000);
	if (obj->query("id")!="liumai jianpu")
	{
		command("kick "+who->query("id"));
		return notify_fail("我让你替我到天龙寺找的东西找到了么？");
	}
	if (who->query_temp("hydjj/tlsover")
		&& obj->query("id")=="liumai jianpu"
		&& obj->query("owner")==who->query("id")
		)
	{
		//who->set_temp("hydjj/givejianpu",1);
		write(HIY"你将"HIC"六脉剑谱"HIY"恭恭敬敬递给鸠摩智，说道，”师傅，幸不辱使命“。\n"NOR);
		command("say 好徒儿，好徒儿，你现在开始是我大轮寺的功臣啊！");
		command("chat 天龙寺好大名气，在我看来不若如此而已！我的弟子打的天龙寺满地找牙！");
		command("chat 天龙寺真是浪得虚名！");
		command("chat "+who->query("name")+"乃是我亲传弟子，各位掌门还请照顾一二！");
		write(HIG"鸠摩智拿起六脉神剑谱，一边放入怀中一边说道，乖徒儿，你下去休息去吧，为师要好好参详参详！”，\n"NOR);
		obj->move(this_object());
		destruct(obj);
		who->delete_temp("hydjj/tlsover");
		who->add("SJ_Credit",i);
		who->add("combat_exp",j);
		who->set("quest/dls/hyd/biyan/givebook",1);
		message_vision(HIC"你收到了鸠摩智大师给你的奖励，总共"HIR+chinese_number(i)+HIC"个通宝，以及"HIR+chinese_number(j)+HIC"点战斗经验。\n"NOR,who);
		return 1;
	}
}
