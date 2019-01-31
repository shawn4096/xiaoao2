// cool 980310
// duan1.c
// Modify By River 98/11
//COOL@SJ,990828
// tangfeng@SJ 2004

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
#include "duan2.h"
#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"
#define QUESTDIR6 "quest/天龙八部/武功/"

string ask_join();
string ask_duan();
string strike();
string fenglu();
string ask_save();
string tianlonghelp();
string askxiaofeng();
string askjiumozhi();
string ask_juexue();
string askailao();
string ask_yyzjp();

string ask_helpwf();
string ask_helpmwq();
string ask_helpgbb();
string ask_helpqhm();
string ask_helpnhs();
void create()
{
	set_name("段正淳", ({ "duan zhengchun", "duan", "master" }) );
	set("title",HIC "镇南王"NOR);
	set("nickname","风流王爷");
	set("gender", "男性" );
	set("age", 44);
	set("str", 22);
	set("con", 23);
	set("dex", 23);
	set("int", 25);
	set("per", 28);
	set("attitude", "friendly");


	set("max_qi", 20000);
	set("max_jing", 4800);
	set("eff_jingli", 4800);
	set("neili", 8000);
	set("qi", 20000);
	set("jingli", 4800);
	set("max_neili", 8000);
	set("jiali", 150);
//	set("family/family","天龙寺");
	set("rank_info/respect", "风流王爷");
	create_family("天龙寺", 13, "镇南王");

	set("long",
	"段正淳是个相当高大的中年儒生，若不是跟随在他左右的铁甲卫士成群，\n"
	"你大概猜不到眼前这个温文儒雅的中年人竟是大理王爷。\n");

	set("combat_exp", 4500000);
	set("score", 50000);

	set("chat_chance_combat", 50);
	set("chat_msg_combat",({
		(: perform_action, "sword.fenglei" :),
		(: exert_function, "qi" :),
	}));

	set_skill("parry", 420);
	set_skill("dodge", 420);
	set_skill("force", 420);
	//set_skill("cuff", 420);
	set_skill("literate", 120);
	set_skill("sword", 420);
	set_skill("duanjia-jianfa", 420);
	set_skill("strike", 420);
	set_skill("qingyan-zhang", 420);
	set_skill("qiantian-yiyang", 420);
	//set_skill("duanjia-quan", 150);
	set_skill("tianlong-xiang", 420);
	set_skill("finger", 420);
	set_skill("yiyang-zhi", 420);
	set_skill("buddhism", 150);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "duanjia-jianfa");
	map_skill("sword", "duanjia-jianfa");
	//map_skill("cuff", "duanjia-quan");
	map_skill("force", "qiantian-yiyang");
	map_skill("strike", "qingyan-zhang");
	map_skill("finger", "yiyang-zhi");
	prepare_skill("strike","qingyan-zhang");
	set("inquiry", ([
		"段誉" : (: ask_duan :),
		//"name": "你问这干嘛，我就是段正淳，难道你又是我情人生的孩子？",
		//"here": "这里便是镇南王府。",
		//"天龙寺" : "天龙寺是我段家武学的最高之地，不过，想拜天龙寺可不是那么容易的.",
		"拜天龙" : (: ask_join :),
		"拜天龙寺" : (: ask_join :),
		"掌法诀要" : (: strike :),
		"掌法要诀" : (: strike :),
		"俸禄" :  (: fenglu :),
		"营救" : (: ask_save :),
		"一阳指鉴品" : (: ask_yyzjp :),
		"保护王妃" : (: ask_helpwf :),
		"保护木婉清" : (: ask_helpmwq :),
		"保护甘宝宝" : (: ask_helpgbb :),
		"保护秦红棉" : (: ask_helpqhm :),
		"保护拈花寺" : (: ask_helpnhs :),
		
		"一阳指绝学" : (: ask_juexue :),		
		//"大理" : "这里便是大理。",
		//"天龙寺" : "天龙寺是我段家武学的最高之地，不过，想拜天龙寺可不是那么容易的.",
		"天龙有难" : (: tianlonghelp :),
		//"萧峰" : "江湖人称南慕容、北萧峰，端得是一条好汉。",
		"营救段誉" : (: ask_save :),
		"救援萧峰" : (: askxiaofeng :),
		
		//"慕容复" : "江湖人称南慕容、北萧峰，听说慕容公子年级轻轻，却无所不精。",
		//"慕容博" : "姑苏慕容不出的杰才，可惜英年早逝。",
		"鸠摩智" : (: askjiumozhi :),
		"哀牢山剑意" : (: askailao :),
       // "六脉神剑" : "传说的我天龙寺最高绝学，我也未能得见。",          
	]));
	setup();
	carry_object("/d/dali/npc/obj/huangpao")->wear();
	carry_object("/clone/weapon/gangjian")->wield();
}

void init()
{
	object ob,me,gold;
	ob =this_object();
	me = this_player();
	::init();
	if (interactive(me) && living(me)) { 
		
		if(!me->query_condition("killer")&& me->query_temp(QUESTDIR1+"see_duanyu1")&&!me->query(QUESTDIR1+"wuliangover"))
		{
			command("look "+me->query("id"));
			tell_object(me,HIY"\n你上前告诉"+ob->name()+"，说在无量山发现段誉，大可放心！\n"NOR);
			command("oh");
			command("jump "+me->query("id"));
			message_vision(HIC"$n向$N表示真诚的感谢。\n", me, this_object());
			command("touch "+me->query("id"));
			command("say 那我也完全放心了，想来这几天犬子就会回来的。"); 
			me->delete_temp("quest/busy");//任务系统冲突标志
			me->delete_temp("quest/天龙八部");   
			me->set(QUESTDIR1+"wuliangover",1);   
			//设定标志
			me->set(QUESTDIR+"time",time());
			me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		}
		
		if (me->query_temp("yyzhi/helpyuxu") )
		{
			command("congra "+me->query("id"));
			command("pat "+me->query("id"));
			command("say 真心不错，好好干！\n");
			if (!me->query("quest/tls/yyz/start/helpyuxuover"))
			{
				command("say 既然你把王妃替我请回来了，我非常高兴，这里有点小奖励你就拿去吧。\n");
				message_vision(HIY"段正淳随手给你"+chinese_number(5)+"两黄金，和"+chinese_number(5000)+"经验值！\n"NOR,me);
				gold=new("clone/money/gold");
				gold->set_amount(5);
				gold->move(me);
				me->add("combat_exp",5000);
				me->add("quest/tls/yyz/start/jiangli",1);
			}
			me->set("quest/tls/yyz/start/helpyuxuover",1);
			command("say 最近四大恶人市场出没我大理，不知道木婉清这娃娃是不是安全，我甚是不放心啊。\n");
			command("say 谁要是能替我保护好婉儿我将重重有赏!\n");
		}
		if (me->query_temp("yyzhi/helpmuover"))
		{
			command("congra "+me->query("id"));
			command("pat "+me->query("id"));
			command("say 真心不错，好好干！\n");
			if (!me->query("quest/tls/yyz/start/helpmuover"))
			{
			
				command("say 既然你把婉儿替我请回来了，我非常高兴，这里有点小奖励你就拿去吧。\n");
				message_vision(HIY"段正淳随手给你"+chinese_number(10)+"两黄金，和"+chinese_number(8000)+"经验值！\n"NOR,me);
				gold=new("clone/money/gold");
				gold->set_amount(10);
				gold->move(me);
				me->add("combat_exp",8000);
				me->add("quest/tls/yyz/start/jiangli",1);
			}
			me->set("quest/tls/yyz/start/helpmuover",1);

			command("say 最近四大恶人市场出没我大理，不知道宝宝是不是安全，我甚是不放心啊。\n");
			command("say 谁要是能替我保护好我的宝宝我将重重有赏!\n");
		}
		if (me->query_temp("yyzhi/helpgbbover"))
		{
			command("congra "+me->query("id"));
			command("pat "+me->query("id"));
			command("say 真心不错，好好干！\n");
			if (!me->query("quest/tls/yyz/start/helpgbbover"))
			{
			
				command("say 既然你保护了宝宝，我非常高兴，这里有点小奖励你就拿去吧。\n");
				message_vision(HIY"段正淳随手给你"+chinese_number(15)+"两黄金，和"+chinese_number(9000)+"经验值！\n"NOR,me);
				gold=new("clone/money/gold");
				gold->set_amount(15);
				gold->move(me);
				me->add("combat_exp",9000);
				me->add("quest/tls/yyz/start/jiangli",1);
			}
			me->set("quest/tls/yyz/start/helpgbbover",1);
			command("say 最近四大恶人市场出没我大理，不知道棉棉是不是安全，我甚是不放心啊。\n");
			command("say 谁要是能替我保护好我的棉棉我将重重有赏!\n");
		}
		if (me->query_temp("yyzhi/helpqhmover"))
		{
			command("congra "+me->query("id"));
			command("pat "+me->query("id"));
			command("say 真心不错，好好干！\n");
			if (!me->query("quest/tls/yyz/start/helpqhmover"))
			{
				command("say 既然你保护了棉棉，我非常高兴，这里有点小奖励你就拿去吧。\n");
				message_vision(HIY"段正淳随手给你"+chinese_number(20)+"两黄金，和"+chinese_number(10000)+"经验值！\n"NOR,me);
				gold=new("clone/money/gold");
				gold->set_amount(20);
				gold->move(me);
				me->add("combat_exp",10000);
				me->add("quest/tls/yyz/start/jiangli",1);
			}
			me->set("quest/tls/yyz/start/helpqhmover",1);
			command("say 最近四大恶人市场出没我大理，你若有意就去把大理东城区拈花寺的黄眉僧请来\n");
			command("say 谁要是能替我请来黄眉僧，对付四大恶人将大有胜算，我将重重有赏!\n");
		}
		if (me->query_temp("yyzhi/helpnhsover"))
		{
			command("congra "+me->query("id"));
			command("pat "+me->query("id"));
			command("say 真心不错，好好干！\n");
			if (!me->query("quest/tls/yyz/start/helpnhsover"))
			{
				command("say 既然你请来了黄眉和尚，我非常高兴，这里有点小奖励你就拿去吧。\n");
				message_vision(HIY"段正淳随手给你"+chinese_number(25)+"两黄金，和"+chinese_number(12000)+"经验值！\n"NOR,me);
				gold=new("clone/money/gold");
				gold->set_amount(25);
				gold->move(me);
				me->add("combat_exp",12000);
				me->add("quest/tls/yyz/start/jiangli",1);
			}
			me->set("quest/tls/yyz/start/helpnhsover",1);
			command("say 很好，经过考验，你为我天南大理付出极大的贡献!\n");
			command("say 此事体大，我也不知道该如何奖励你好，你最好去找我皇兄去吧!\n");
		}
	} 
}
 
string ask_duan()
{
	object me;
	object *obj;
	int x;
	me = this_player();
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
           return "小儿和中原官府应该没有半点关系，"+RANK_D->query_respect(me) +"还是自我小心通缉！";
	}
  if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
  { 
      message_vision(HIC"$N脸上露出气愤的神色。\n", this_object());
  	  command("heng");
	  obj = users();
	  x = sizeof(obj);
	  while(x--) {
		  if ( (obj[x]->query_temp(QUESTDIR1+"jianying")
                          ||obj[x]->query_temp(QUESTDIR1+"start"))
			  && obj[x]!=me) 
			  return "不过，"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已经在帮我了，"+RANK_D->query_respect(me) +"不用那么着急！";		  
	  }
  	  //设定标志
  	  me->set(QUESTDIR+"time",time());
  	  me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
  	  me->set(QUESTDIR1+"start",1);
      me->set_temp(QUESTDIR1+"start",1);
	  me->set_temp("quest/busy",1);//与任务系统冲突标志
	  log_file("quest/TLBB", sprintf("%s(%s) 开始天龙八部第一部分。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	  return "小儿不爱学武，和我吵了几句就离家出走了，唉......家门不幸啊！";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
	  message_vision(HIC"$N脸上露出气愤的神色。\n", this_object());
  	  command("sigh");
  	  command("shrug "+me->query("id"));
	  return "前段时间有人说在无量山附近看到小儿，不知道现在身在何处。";
	}
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
 
  	  command("sigh");
  	  message_vision(HIC"$N脸上露出担心的神色。\n", this_object());
  	  //时间一天
  	  if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
	  {
		  if(random(2)) return "今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
		  else return "誉儿这几天就可能回来了，"+RANK_D->query_respect(me) +"先行休息去吧！";
	  }
	  me->set_temp(QUESTDIR1+"2_start",1);
	  return "小儿日前被四大恶人的南海鳄神掳走了，我们正在设法营救他，有来报目前就在无量山附近的一座石屋内。";
	}
	if (me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"2_start") && !me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  message_vision(HIC"$N脸上露出担心的神色。\n", this_object());
  	  command("shrug "+me->query("id"));
	  return "刚有探报，小儿确实就在无量山附近的一座石屋内，不得已只怕要走一次了。";
	}
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("look "+me->query("id"));
  	  command("nod "+me->query("id"));
  	  message_vision(HIC"$n向$N表示真诚的感谢。\n", me, this_object());
	  return "刚有探报，小儿确实就在无量山附近的一座石屋内，不过，有"+RANK_D->query_respect(me) +"相助，料无大碍。";
  }
  if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
  	  message_vision(HIC"$n向$N表示真诚的感谢。\n", me, this_object());
	  return "多谢"+RANK_D->query_respect(me) +"搭救小儿，只是这万劫谷之后，身体一直不调，才被送往天龙寺求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小儿自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
		  return "竟然惹出鸠摩智这等高手，但愿小儿吉人天相啊。";
  }
  command("nod "+me->query("id"));
	return "段誉正是犬子，不知道找他何事。";
}

string ask_save()
{
	object me;
	object *obj;
	int i,j,x;
	i=random(5)+2;
	j=random(4)+3;
	me=this_player();

  if(!me->query(QUESTDIR1+"start" ))
  {
  	  command("?");
  		return "小儿向来只爱佛法已经，平易近人，援救之说何来之说？";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("shrug "+me->query("id"));
		  return "前段时间有人说在无量山附近看到小儿，这等贪玩，就让他去吧。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"wuliangover")&& !me->query_temp(QUESTDIR1+"2_start")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
		  return "小儿最近收了个莫名其妙的弟子，好像叫什么南海鳄鱼？我总是担心啊，千万不要出什么乱子。";
    }
	if (me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"2_start") && !me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
		if ( me->query("shen") < 0)
		           return ("我看" + RANK_D->query_respect(me) +"面带阴邪之气，恐怕是四大恶人一伙的奸细。");
    	if ( me->query("combat_exp") < 1500000)
		           return ("四大恶人都是绝顶高手,"+RANK_D->query_respect(me) +"似乎武功不够，和四大恶人相斗会有性命之忧。");
  		me->set_temp(QUESTDIR1+"step",i);
	  	me->set_temp(QUESTDIR1+"steps",j);
  	  command("look "+me->query("id"));
   	  //增加时间和经验间隔限制
  	  //时间一天
  	  if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
	  {
		  if(random(2)) return "今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
		  else return "誉儿被那四大恶人擒走，这件事还需从长计议，"+RANK_D->query_respect(me) +"千万不得鲁莽。";
	  }
	  //考虑很多限制，这里经验差距变得少一点
	  if(me->query(QUESTDIR+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<100000)
		  return "以"+RANK_D->query_respect(me) +"目前的经验就算目前有情况，也帮不上什么忙，还是抓紧练功吧！";

	  obj = users();
	  x = sizeof(obj);
	  while(x--) {
		  if ( obj[x]->query_temp(QUESTDIR1+"yingjiu")&& obj[x]!=me) 
			  return ""+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已经在帮我了，"+RANK_D->query_respect(me) +"还是抓紧练功吧！";		  
	  }

  	  //设定标志
  	  me->set(QUESTDIR+"time",time());
  	  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
  	  command("touch "+me->query("id"));
  	  me->set_temp(QUESTDIR1+"yingjiu",1);
	  me->set_temp("quest/busy",1);//与任务系统冲突标志
	  log_file("quest/TLBB", sprintf("%s(%s) 开始准备营救段誉（第一章）。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	  return ("既然"+ RANK_D->query_respect(me) +"有意相助，定会如虎添翼。居我得知，誉儿被四大恶人之首\n"+
			"段延庆囚在正在无量山附近的一座石屋内，只是路上十分险恶，之前为了探明路线，\n"+
			"我已损失好几名手下。你先去大理北面去无量山路上的一个小溪那里，向北行五里，\n"+
			"再向西行"+chinese_number(j)+"里，再向北行"+chinese_number(i)+"里，然后会到一座高山，再往后就要见机行事了。\n\n"+
			"段正淳说道：好了，准备一下，为了不惊动对方，切记要在晚上行动，路上小心。");
  }
  if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("look "+me->query("id"));
  	  command("touch "+me->query("id"));
                  return "有"+RANK_D->query_respect(me) +"相助，料无大碍。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多谢"+RANK_D->query_respect(me) +"搭救小儿，只是这万劫谷之后，身体一直不调，才被送往天龙寺求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小儿自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
  	  command("look "+me->query("id"));
		  return "竟然惹出鸠摩智这等高手，但愿小儿吉人天相啊。";
  }
  command("nod "+me->query("id"));
	return "小儿向来只爱佛法已经，平易近人，援救之说何来之说？";
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
		  return "这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧，所谓口生莲花，全是一派胡言。";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "鸠摩智妄为西域第一佛法高僧，所谓口生莲花，全是一派胡言。";
  }
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
		  return "听说这件事情，只是涉及到大辽与大宋之争，实在不好插手。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
                  return "萧峰，难不是你所迫出中原，今日所谓搭救不知何意。";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是涉及到大辽与大宋之争，实在不好插手。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "萧峰乃小儿之义兄，自然要救。这位"+RANK_D->query_respect(me) +"可先行一步，大理段家弟子随后援到。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "这一战真是痛快，"+me->query("name")+"更是威震武林，端得厉害啊。";
  }
	return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
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
		  return "这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧。";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
	  return "多谢"+RANK_D->query_respect(me) +"化解这场天龙危机，还将我侄子得以解救。";
  }
	  command("hoho");
	  return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
}
string strike()
{
	mapping fam = this_player()->query("family");
	object ob;
	if(!fam || fam["family_name"] != "天龙寺")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";
	if(this_player()->query_skill("strike",1) > 30)
		return "你的掌法已经有一定基础了，这本书对你没什么用，还是留给别的弟子吧";
	ob = unew("/d/dali/obj/book-strike");
	if(!clonep(ob))
		return "你来晚了，本派的「掌法诀要」不在此处。";
	if(clonep(ob) && ob->violate_unique()){
		destruct(ob);
		return "你来晚了，本派的「掌法诀要」不在此处。";
	}
	ob->move(this_player());
	return "好吧，这本「掌法诀要」你拿回去好好钻研。";
}

string ask_join()
{
	object me;
	object ob;
	ob=this_player();
	me=this_object();
	if (ob->query("tls"))
		return "你已经是天龙寺出家弟子了，何故还要问此事？";

//	if (ob->query("combat_exp") > 100000)
//		return "大理段氏在大理还需要你这样的人才，就不要去天龙寺出家吧。";

	if(ob->query_temp("tls_app"))
		return "我不是已经推荐你去天龙寺了吗？怎么还不去啊？";

	if((string)ob->query("gender") == "女性" )
		return "天龙寺武功需要纯阳之体，小姑娘可不收啊! ";

	if((int)ob->query_skill("qiantian-yiyang",1) < 450 )
		return RANK_D->query_respect(ob) +"，你乾天一阳功不足450,不能学习高等级的功夫!";

	if ( ob->query("job_time/大理") + ob->query("job_time/送信")  < 5000)
		return "我看你为镇南王府做事做的还不够啊，努力做吧！";

	if ( ob->query_int() < 30 )
		return "天龙寺武学深奥，我看你的悟性似乎不够，恐怕无法领会这么高的功夫!";

	if( ob->query("marry"))
		return "你都已经结婚了，要去出家，叫你夫人怎么办？";

	ob->set_temp("tls_app",1);
	command ("say 哈哈！好样的！这位兄弟既然为我大理段氏做了这么多事,今天就推荐你去天龙寺！");
	return "我即刻修书一封，快马送到天龙寺了惑禅师那里，你速速赶去吧!";
}

string fenglu()
{
	object ob=this_player();
	mapping fam = ob->query("family");
	int gold = 0, fenglu;

	if (!fam || fam["family_name"] != "天龙寺")
		return "这位"+ RANK_D->query_respect(ob) +"不是我大理国的臣民，难道也想来拿大理的俸禄？";

	if( ob->query("tls"))
		return "这位"+ RANK_D->query_respect(ob) +"已经出家了，还要这俸禄做甚？";

	switch (fam["generation"]) {
		case 13:
			gold += 500;
		case 14:
			gold += 800;
			break;
		default:
			return "这位"+ RANK_D->query_respect(ob) +"在大理时间还太短，等过段时间才来拿吧。";
	}
	fenglu = ob->query("age") * 12 + ob->query("month");
	if (ob->query("fenglu") >= fenglu)
		return "这位"+RANK_D->query_respect(ob) +"本月不是已经拿过俸禄了，怎么还想来拿？";
	gold *= ob->query_skill("qiantian-yiyang", 1);
        if (ob->query_skill("force", 1) < 216)  return "你这个月没有俸禄。";
	ob->set("fenglu", fenglu);
	command ("pat " + ob->query("id"));
	message_vision("$N给了$n"+MONEY_D->money_str(gold)+"。\n", this_object(), ob);
	MONEY_D->pay_player(ob, gold);
	return "这是你本月的俸禄，这位"+ RANK_D->query_respect(ob) +"好好干啊！";
}

void attempt_apprentice(object ob)
{
	object me=this_object();
	mapping fam = ob->query("family");
	if( (string)ob->query("gender") == "女性" ){
		command ("say 我天龙寺武功需要纯阳之体，小姑娘我可不收啊!");
		return;
	}
	if (ob->query("tls")){
		command ("say 你已经是天龙寺出家弟子了，我不能再收你了！\n");
		return;
	}
	if( (int)ob->query_skill("qiantian-yiyang",1) < 350  ){
		command ("hmm");
		command ("say 你乾天一阳功居然不足350，如此之差我可不收你?");
		return;
	}
	if(ob->query_int() < 50){
		command("say 学一阳指之人必须悟性奇高，依我看" + RANK_D->query_respect(ob) + "的悟性似乎不够50？");
		return;
	}
	if(fam["master_name"] == "段正明"){
		command("haha");
		command("say "+RANK_D->query_respect(ob)+"已是兄长身前的侍卫，"+RANK_D->query_self(me)+"怎能再收你为徒？");
		return;
	}
	if ((int)ob->query("shen") < 500000){
		command ("say  我大理段氏乃堂堂正派，依我看" + RANK_D->query_respect(ob) +"正神不足500k，不适合入我大理段氏。");
		return;
	}
	command("smile");
	command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
	command("recruit " + ob->query("id") );
	if (!ob->query("qinwang")) {
		this_player()->set("title","大理国镇南王府家将");
	}
	else {
		this_player()->set("title", HIW "大理国"+ ob->query("qinwang")+NOR);
	}
}

void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	 ob->set("class", "officer");
}

string ask_juexue()
{
	object me;
	me = this_player();
	
	//mapping fam;
	//fam = me->query("family");
	

	if (!me->query("family") || me->query("family/family_name") != "天龙寺")
		return "这位"+ RANK_D->query_respect(me) +"不是我大理国的臣民，难道也想来拿大理的俸禄？";
	if (me->query("tls/yideng/ronghe")=="pass" )
	{
  	      command("heng "+me->query("id"));
		  command("consider "+me->query("id"));
		  return "你已经知晓了大理一阳指绝学，还在这里调戏本王么？\n";		  
    }
	if (me->query_temp("yyzjx"))
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
	  return "你老年痴呆了？我不是告诉过你么？\n";
     }	
	command("nod "+me->query("id"));
	me->set_temp("yyzjx",1);
	return "大理段氏一阳指乃是武林第一绝学，这门功夫我是学不了了，你若真的感兴趣，你可以去找一灯大师看看是否有此机缘。\n";
    	
}

int prevent_learn(object ob, string skill)
{
	if (skill == "yiyang-zhi"){
		command("一阳指乃是我大理国镇国之宝，非做出巨大贡献者不得而传。\n");
		return 1;
	}
	return 0;
}


/*
void die()
{
	object ob;
	if (!query_temp("living"))
	{
		if (!objectp(preset("duan zhengchun","d/dali/wangfu/nuange")))
		{		
		 ob = new("/d/dali/wangfu/npc/dzc");
		 ob->move("/d/dali/wangfu/nuange");
		}
	}
	::die();
}*/

string askailao()
{
	object me;
	int j,i;
	me = this_player();
	if (!me->query("family")||me->query("family/family_name")!="天龙寺")
	{
  	      command("heng "+me->query("id"));
		  return "你不是我大理弟子，所为何来，难道是奸细不成？\n";
    }
	if (me->query_skill("qiantian-yiyang",1)<200)
	{
  		  command("sigh");
  	      command("? "+me->query("id"));
		  return "你的乾天一阳功力不足200，如何施展出这哀牢山剑意，赶紧努力去吧。";
    }
	if (me->query_skill("duanjia-jianfa",1)<200)
	{
  		  command("sigh");
  		  command("? "+me->query("id"));
		  return "你的段家剑法功力不足200，如何施展出这哀牢山剑意，赶紧努力去吧。。";
    }
	if (me->query("quest/tls/ailao/pass"))
	{
  		  command("nod "+me->query("id"));
		  return "你已经彻底领悟了这门绝学，在这里啰嗦什么？";
    }
	if (time()-me->query("quest/tls/ailao/time")<86400)
	{
  		  command("nod "+me->query("id"));
		  return "你来的也太勤快了，烦不烦！";
    }
	
	j=random(me->query("kar"));
	i=random(10);

	if (me->query("kar")<31
		&&j>22
		&&i>5)
	{
       message_vision(HIC"\n\n$N终于将这段家剑法融会贯通，彻底领悟哀牢山剑意，段家剑法威力大增。\n"NOR,me);
	 
	   log_file("quest/djjfailao",sprintf("%s(%s) 从段正淳处领悟段家剑法之哀牢山剑意。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("quest/tls/ailao/fail"),me->query("combat_exp"),me));
	   me->set("quest/tls/ailao/pass",1);
	   command("congra "+me->query("id"));
	   return "恭喜你完成了哀牢山剑意谜题。\n";
	}
	else
	{
		message_vision(HIY"\n\n$N虽然听段正淳说了这段家剑法的哀牢山剑意，但对于如何使用的劲力法门一时之间却是难以理解。\n"NOR,me);
		log_file("quest/djjfailao",sprintf("%8s%-10s请教段家剑法的哀牢山剑意，但并没有成功，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("quest/tls/ailao/fail"),me->query("combat_exp"),me));
		me->add("quest/tls/ailao/fail",1);
		me->set("quest/tls/ailao/time",time());
		return "解密段家剑法的哀牢山剑意失败。\n";

	}     
  
}

string ask_yyzjp()
{
	object me;
	int j,i;
	me = this_player();
	if (!me->query("family")||me->query("family/family_name")!="天龙寺")
	{
  	      command("heng "+me->query("id"));
		  return "你不是我大理弟子，所为何来，难道是奸细不成？\n";
    }
	if (100>(int)me->query_skill("yiyang-zhi",1))
	{
  	  command("sigh");
  	  command("hammer "+me->query("id"));
		  return "你的一阳指功力不足100，如何鉴定，赶紧努力去吧。";
    }
	if (99<(int)me->query_skill("yiyang-zhi",1)&&(int)me->query_skill("yiyang-zhi",1)<200)
	{
  	  command("sigh");
  	  command("hammer "+me->query("id"));
	  me->set("yyz/degree",9);
		  return "你的一阳指功力不过九品起步而已，赶紧努力去吧。";
    }
	if (199<(int)me->query_skill("yiyang-zhi",1)&&(int)me->query_skill("yiyang-zhi",1)<300)
	{
  	  command("sigh");
  	  command("hammer "+me->query("id"));
	  me->set("yyz/degree",8);
		  return "你的一阳指功力不过八品而已，赶紧努力去吧。";
    }
	if (299<(int)me->query_skill("yiyang-zhi",1)&&(int)me->query_skill("yiyang-zhi",1)<350)
	{
  	  command("sigh");
  	  command("hammer "+me->query("id"));
	  me->set("yyz/degree",7);
		  return "你的一阳指功力不过七品而已，赶紧努力去吧。";
    }
	if (349<(int)me->query_skill("yiyang-zhi",1)&&(int)me->query_skill("yiyang-zhi",1)<400)
	{
  	  command("sigh");
  	  command("smile "+me->query("id"));
	  me->set("yyz/degree",6);
		  return "你的一阳指功力不过六品而已，赶紧努力去吧。";
    }
   if (399<(int)me->query_skill("yiyang-zhi",1)&&(int)me->query_skill("yiyang-zhi",1)<450)
	{
  	  command("sigh");
  	  command("smile "+me->query("id"));
	  me->set("yyz/degree",5);
		  return "你的一阳指功力不过五品而已，赶紧努力去吧。";
    }
	if (449<(int)me->query_skill("yiyang-zhi",1)&&(int)me->query_skill("yiyang-zhi",1)<500)
	{
  	 // command("sigh");
  	  command("smile "+me->query("id"));
	  me->set("yyz/degree",4);
		  return "恭喜你，你的一阳指功力已经修炼到四品，我大理段氏四品后方可修习六脉神剑。";
    }
	if (499<(int)me->query_skill("yiyang-zhi",1)&&(int)me->query_skill("yiyang-zhi",1)<550)
	{
  	  //command("sigh");
  	  command("smile "+me->query("id"));
	  me->set("yyz/degree",3);
		  return "恭喜你，你的一阳指功力已达三品，品级越高威力越大。";
    }
	if (549<(int)me->query_skill("yiyang-zhi",1)&&(int)me->query_skill("yiyang-zhi",1)<600)
	{
  	  //command("sigh");
  	  command("smile "+me->query("id"));
	  me->set("yyz/degree",2);
		  return "恭喜你，你的一阳指功力已达二品，品级越高威力越大。";
    }
	if (559<(int)me->query_skill("yiyang-zhi",1))
	{
  	  command("laugh");
  	  command("congra "+me->query("id"));
	  me->set("yyz/degree",1);
		  return "恭喜你，你的一阳指功力已达一品，天下虽大，尽可去的！";
    }
}

//救王妃

