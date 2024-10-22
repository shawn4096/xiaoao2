// Room: /d/shaolin/guangchang1.c
// Date: YZC 96/01/19

#include <ansi.h>
#include <wanted.h>

inherit ROOM;

int init();
int do_open();
int xiao_ding1(object me);
int xiao_ding2(object me);
int xiao_ding3(object me);
int xiao_ding4(object me);
string look_gate();
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"

void create()
{
	set("short", "广场");
	set("long", @LONG
这里是少林寺前的广场，整个广场由大块的青石铺成，极为平坦。但因年
代久远，都有些破损。丛丛小草从石板的缝隙中长了出来。广场周围都是密密
的松树林，四角上各放了几块石碑，字迹都甚为模糊。正前方黄墙碧瓦，飞檐
翘檩，正中一道二丈来宽，三丈来高的朱红杉木包铜大门(gate)。上方一块大
匾，龙飞凤舞地书着『[1;33m少林寺[0;37;0m』三个大字。寺前三三两两的站着几个僧人。
LONG
    );

	set("exits", ([
		"east" : __DIR__"gchange",
		"south" : __DIR__"shifang",
		"west" : __DIR__"gchangw",
	]));

	set("outdoors", "shaolin");
	set("item_desc",([
		"gate"        :    (: look_gate :),
	]));

	set("objects",([
		CLASS_D("shaolin") + "/qing-fa" : 1,
	]));

	setup();
	"/clone/board/shaolin_b"->foo();
}

int init()
{
  object me;
 
  me = this_player();
  if(!me->query_condition("killer") && me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"dagouzhen"))
  {
   tell_object(me,HIC"\n你总算走出少林寺，来到山门殿广场。突然你又有一种不妙的预感。\n"NOR); 
   message_vision(WHT"山下匆匆走来一个人，向$N一拱手道：“嘿嘿，施主如此凶狠，还是留在少林潜修佛法得好阿。”\n"NOR,me);
   me->move("/d/gb/dagouzhen");
   tell_object(me,HIR"你疑惑了一下，却发现四周围上一圈人，似乎是丐帮打狗阵法。\n"NOR);
   log_file("quest/TLBB", sprintf("%s(%s)被关进打狗阵。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
   return 1;
  }
	add_action("do_knock", "knock");
   //增加萧峰大战丁春秋情节
   if (me->query_temp("xlz/askxiao1"))
   {
	   //me->delete_temp("xlz/askxiao1");
	   if (!present("ding chunqiu",environment(me)))
	   {
		   new("/d/xingxiu/npc/ding.c")->move("/d/shaolin/guangchang");
		}
       if (!present("xuanci dashi",environment(me)))
	   {
		   new("/kungfu/class/shaolin/xuan-ci.c")->move("/d/shaolin/guangchang");
		}
	  if (!present("xingxiu dizi",environment(me)))
      {
	   new("/d/xingxiu/npc/xxdizi.c")->move("/d/shaolin/guangchang");
       }
	  //me->start_busy(3);
	  call_out("xiao_ding1",2,me);
	  //me->delete_temp("xlz/askxiao1");
	 // return 1;
   }

}

int close_gate()
{
	object room;

	if(!( room = find_object(__DIR__"smdian")) )
		room = load_object(__DIR__"smdian");
	if(objectp(room)) {
	delete("exits/north");
	message("vision", "乒地一声，里面有人把大门关上了。\n", this_object());
	room->delete("exits/south");
	if (objectp(present("qingfa biqiu", room)))
		message("vision", "清法比丘上前把大门关了起来。\n", room);
	else
		message("vision", "壮年僧人上前把大门关了起来。\n", room);
	}
	else message("vision", "ERROR: gate not found(close).\n", room);
}

int do_knock(string arg)
{
	object room;

	if (query("exits/north"))
		return notify_fail("大门已经是开着了。\n");

	if (!arg || (arg != "gate" && arg != "north"))
		return notify_fail("你要敲什么？\n");

	if(!( room = find_object(__DIR__"smdian")) )
		room = load_object(__DIR__"smdian");

	if(objectp(room)) {
		set("exits/north", __DIR__"smdian");
		message_vision("$N轻轻地敲了敲门，只听吱地一声，一位壮年僧人应声打开大门，\n"
				"他用锐利的目光上上下下打量着$N。\n",this_player());
		room->set("exits/south", __FILE__);
		message("vision", "外面传来一阵敲门声，壮年僧人应声上前把大门开。\n", room);
		remove_call_out("close_gate");
		call_out("close_gate", 10);
	}
	return 1;
}

int valid_leave(object me, string dir)
{
	if (me->query_temp("xlz/askxiao1"))
	{
		notify_fail("你还有剧情没完成,不能离开！\n");
		return;
	}
	
	if ( dir != "north" )
	return ::valid_leave(me, dir);

	if (is_wanted(me))
		return 0;
	if ( me->query("family/family_name") == "少林派" ) {
		if ( me->query("guilty") == 0
		 && me->query("K_record") == ( me->query("PKS") + me->query("MKS"))) {
			message_vision("壮年僧人侧身让开，说道：师兄辛苦了，请进。\n", me);
			return 1;
		}
		else {
			if((int)me->query("guilty") == 0) {
				int shen = me->query("shen");
				if((int)me->query("shen_record") > shen)
					me->set("guilty", 1);
				else
					me->set("guilty", 2);
				me->set("K_record", me->query("PKS") + me->query("MKS"));
				if (shen > 0 && shen > me->query("combat_exp")) shen = me->query("combat_exp");
				if (shen < 0 && -shen > me->query("combat_exp")) shen = -me->query("combat_exp");
				if (shen < 0) shen += shen / 9;
				else shen -= shen / 9;
				me->set("shen_record", shen);
			}
			write("壮年僧人沉下脸来，说道：戒律院主持玄寂大师请师兄火速去戒律院陈述此行过犯。\n");
			return 1;
		}
	}
	else if( present("yingxiong ling", me)){
		message_vision("壮年僧人合十为礼，侧身让开，说道：原来是贵客驾到，请进请进！\n", me);
		return 1;
	}
	else if (me->query("luohan_winner")) {
		message_vision(HIY "壮年僧人对$N合十为礼，侧身让开，说道：原来是闯过罗汉阵的大英雄驾到，请进请进！\n" NOR, me);
		return 1;
	}
	if (me->query("shen") >= 0) {
		if (me->query("gender") == "女性") {
			return notify_fail("壮年僧人说道：这位女施主还是请回罢，本寺从不接待女客。\n");
		}
		else {
			return notify_fail("壮年僧人说道：这位施主请回罢，本寺不接待俗人。\n");
		}
	}
	return notify_fail("壮年僧人立时从身畔挚出一把雪亮的戒刀来，把明晃晃的\n"
			"刀尖对准你的胸口，横眉怒目地说道：你等邪魔外道，还不给我滚开！\n"
			"以后再敢走近少林一步，我立时就斩断你们的狗腿！\n");

	if(me->query("no_quest"))
		return notify_fail("\n");
}

string look_gate()
{
	return "一道三丈来高的朱红杉木包铜大门。\n";
}


int xiao_ding1(object me)
{
 
   message_vision(CYN"\n老衲当以本派大金刚掌接一接帮主的降龙十八掌，以降魔禅仗接一接帮主的打狗棒。唉，\n"
                      +"少林派和贵派世代交好，这几种武功，向来切磋琢磨则有之，从来没有用以敌对过招，\n"
					  +"老衲不德，却是愧对丐帮历代帮主和少林派历代掌门了。\n"NOR,me);
   message_vision(HIB"\n丁春秋好像甚是生气，忍不住哼了一声，将头看了身旁的阿紫一眼，深情甚是复杂，\n" NOR,me);
   message_vision(HIG"\n星宿派神功比丐帮降龙十八掌强得多，干么不使强的，反使差劲的？\n"NOR,me);
   message_vision(HIG"\n庄师兄，再上！当然要用恩师星宿老仙传给你的神功，去宰了老和尚！\n"NOR,me);  
   message_vision(HIG"\n星宿弟子纷纷说道：“星宿神功，天下第一，战无不胜，攻无不克。降龙臭掌，狗屁不值！”\n",me);
   message_vision(HIC"\n\n星宿弟子纷纷说道：“星宿神功，天下第一，战无不胜，攻无不克。降龙臭掌，狗屁不值！”\n",me);
   message_vision(HIB"\n\n星宿弟子纷纷说道：“星宿神功，天下第一，战无不胜，攻无不克。降龙臭掌，狗屁不值！”\n",me);
   message_vision(HIY"\n\n星宿弟子纷纷说道：“星宿神功，天下第一，战无不胜，攻无不克。降龙臭掌，狗屁不值！”\n",me);
   
   me->delete_temp("xlz/askxiao1");
   call_out("xiao_ding2",5,me);

   return 1;

}

int xiao_ding2(object me)
{
  
   message_vision(HIC"\n\n\n一片喧哗叫嚷之中，忽听得山下一个雄壮的声音说道：“谁说星宿派武功胜得了丐帮的降龙十八掌？”\n"NOR,me);
   call_out("xiao_ding3",5,me);
   return 1;

}
int xiao_ding3(object me)
{
  object ding,xf,xuan;
  //xuan=present("xuan ci",environment(me));
   
  if (!objectp(present("ding chunqiu",environment(me))))
  {
     new("/d/xingxiu/npc/ding.c")->move("/d/shaolin/guangchang");
  }
  ding=present("ding chunqiu",environment(me));

  // xx1=present("xingxiu dizi",environment(me));
   message_vision(HIY"\n这声音也不如此响亮，但清清楚楚的传入了从人耳中，众人一愕之间，都住了口。\n"NOR,me);
   message_vision(CYN"\n\n但听得蹄声如雷，十余乘马疾风般卷上山来。马上乘客一色都是玄色薄毡大氅，里面玄色布衣，\n"
                      +"但见人似虎，马如龙，人既矫捷，马亦雄骏，每一匹马都是高头长腿，通体黑毛，奔到近处，\n"
					  +"群雄眼前一亮，金光闪闪，却见每匹马的蹄铁竟然是黄金打就。来者一共是一十九骑，人数虽不甚多，\n"
					  +"气势之壮，却似有如千军万马一般，前面一十八骑奔到近处，拉马向两旁一分，最后一骑从中驰出。\n"
					  +"丐帮帮众之中，大群人猛地高声呼叫：“乔帮主，乔帮主！”数百名帮众从人丛中疾奔出来，在那人马前躬身参见。\n"NOR,me);
  if (!present("xiao feng",environment(me)))
  {
	  xf=new("/d/nanyang/npc/xiaofeng.c");
      xf->move(this_object());
	 /* xf->delete("chat_msg_combat");
	  xf->set("chat_msg_combat", ({
          (: exert_function, "huntian" :),
          (: perform_action, "strike.sanzhang" :),
			  }));*/
	  message_vision(HIR"\n\n萧峰快步走了过来，步入当场，英雄气势凛然,看向丁春秋喝道，“看掌！”。\n"NOR,me);
  }
  ding->kill_ob(xf);
  ding->kill_ob(me);
  //丁若被打晕

 
  call_out("xiao_ding4",30,me);
  //me->set_temp("xiaovsding",1);
  return 1; 
}

int xiao_ding4(object me)
{
    
	int i,j,g,t;
	object ding,xiao,xuanci,xxdizi;
	ding=present("ding chunqiu",environment(me));
	xiao=present("xiao feng",environment(me));
	xuanci=present("xuanci dashi",environment(me));
    xxdizi=present("xingxiu dizi",environment(me));
    if(file_name(environment(me))!="/d/shaolin/guangchang" ){
		message_vision(HIY"因为你已经离开少林广场，对于广场所发生的事情一无所知。\n"NOR,me);
        me->add("xlz/sanzhao/fail",1);
		me->set("xlz/sanzhao/time",time());
		me->delete_temp("xlz/askxiao1");
        return 1;
	}
	/*if (!objectp(ding))
	{
		mesage_vision(HIC"萧峰连续运使降龙十八掌的亢龙有悔绝技，三招之后将丁春秋打到在地。\n"NOR,me);
	    mesage_vision(HIY"一群少林弟子闪了出来，将丁春秋押了下去。一时间广场上变得冷冷清清。\n"NOR,me);
		//destruct(dcq);
		//destruct();
     }*/
	message_vision(CYN"\n\n你呆呆的看着眼前这一幕，尽管你已经领悟了全部的降龙十八掌，但这三招从萧风手中施展出来。\n"NOR, me);
	message_vision(CYN"\却宛如羚羊挂角，无迹可寻，却又似一阵电闪雷鸣，在你的脑海中激起千万丈的波涛汹涌。\n"
			           +"这些招式对你来说你已经了然若胸，一时之间竟然呆立当场..........................\n"
					   +"..............................................................................\n"NOR,me);

	j=random(me->query("kar"));
	g=random(me->query("relife/gifts/total"));
	//富源，随机参悟>=15点，且臂力>45
	t=20;
    if(me->query("m-card-vip")) t =  18;
    if(me->query("y-card-vip")) t =  15;
    if(me->query("buyvip"))     t =  10;
	i= random(t);
	
	if (me->query("kar")<31
		&& j>26
		&& i<3
		&& random(g)>=15
		&& random(me->query("str"))>40)
	{
       message_vision(HIC"$N恍然大悟，这降龙掌要想练成绝非一日之功，对于臂力要求是很高的。\n"NOR,me);
	   message_vision(HIC"$N同时融会贯通和熟能生巧也是武技达到巅峰的必由之路，原来这就是返璞归真的道理。\n"NOR,me);
	   message_vision(HIC"$N恭喜你，历经千难万险，终于领悟萧峰所传的三招连环降龙掌绝技。\n"NOR,me);
	   xiao->command("chat* haha"+me->query("id"));
	   
	   xiao->command("chat "+"丐帮降龙十八掌乃是武林中最霸道的掌法。");
	   xiao->command("chat* admire"+me->query("id"));
	   xiao->command("chat "+"降龙十八掌，天下第一掌法，恭喜恭喜！");
	   if (objectp(ding)) destruct(ding);
	   if (objectp(xiao)) destruct(xiao);	
	   if (objectp(xuanci)) destruct(xuanci);
	   if (objectp(xxdizi)) destruct(xxdizi);
	   //me->add("combat_exp",15000);
	   log_file("quest/xlzsanzhang",sprintf("%s(%s) 在少林广场，得到萧峰的亲自指点，打跑丁春秋。富源：%d。随机数：%d。失败：%d。经验值：%d。gift值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/sanzhao/fail"),me->query("combat_exp"),g,me));
	    me->set("title",HIC"南院大王"+HIY"萧峰挚友"NOR);
		me->set("mytitle/quest/xiaofengtitle",HIC"南院大王"+HIY"萧峰挚友"NOR);
	   me->set("xlz/sanzhao","pass");
	   me->delete_temp("xlz/askxiao1");
	   me->start_busy(-1);
	   return 1;
	}
	else
	{
		message_vision(HIY"\n$N虽然听萧峰降龙十八掌的终极奥义，但对于如何使用的劲力法门一时之间却是难以理解。降龙十八掌的\n"
		+"威力并没有发挥出来，看来你还是有待于重新跟萧峰领悟学习了。萧峰见你没有领悟，轻叹一声道，继续努力，终有一天你会明白的。\n"NOR,me);
		log_file("quest/xlzsanzhang",sprintf("%8s%-10s在少林广场，亢龙有悔三招并没有成功，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。gift值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/sanzhao/fail"),me->query("combat_exp"),g,me));
		me->add("xlz/sanzhao/fail",1);
		me->set("xlz/sanzhao/time",time());
		me->delete_temp("xlz/askxiao1");
		if (objectp(ding)) destruct(ding);
	    if (objectp(xiao)) destruct(xiao);	
	    if (objectp(xuanci)) destruct(xuanci);
	    if (objectp(xxdizi)) destruct(xxdizi);
		me->start_busy(-1);
        return 1;
	}
    
    
}