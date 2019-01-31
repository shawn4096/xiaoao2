//Created by Redhat@Sjmud 2009/4/7
//updated by Zhuifeng@SJFY 2010/7/27

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/射雕英雄传/"
#define QUESTDIR1 "quest/射雕英雄传/风雪惊变/"
void create()
{
	set("short", "杨家小屋");
	set("long", @LONG
这是一座十分清爽的民房，家具摆设一应俱全，只是都附着一层灰土。屋
子中间是一张小桌，桌上的杯碗还都没有撤去，看来主人去的很匆忙。墙上挂
着一杆短柄生了锈的铁枪(Tieqiang)。
LONG
	);

	set("item_desc", ([
		"tieqiang" : "一杆用旧了的铁枪，看起来原来应该有一对的，不知为何只剩了一杆。\n",
	]) );

	set("exits", ([
		"north" : __DIR__"houyuan.c",
		"south" : __DIR__"qianyuan.c",
	]));
    set("objects",([
               __DIR__"npc/yang": 1,
            //   __DIR__"npc/bao": 1,
     ]));

	setup();
}
//丘处机走后，如果愿意保护，正线,包惜弱会救完颜洪烈
//如果选择去保护完颜洪烈，就是邪线，和丘处机等人大战。


void init()
{
  object me,obj,yang,guo,qiu;
  me = this_player();
  add_action("do_jiejiao","jiejiao");

  //痛饮

  if (me->query(QUESTDIR1+"start") 
	 &&objectp(present("yang tiexin",this_object()))
	 &&!me->query_condition("killer")
	 &&!me->query(QUESTDIR1+"over")
	 && me->query_temp(QUESTDIR1+"xiangzhi"))
  {
		
	  message_vision(HIC"杨铁心眼见你进来，哈哈大笑，对$N说道，“等您好久了，多谢这位英雄的美酒，来，请上座！”\n"NOR,me);
	  if (!objectp(guo=present("guo xiaotian",this_object())))
	  {
			guo=new("d/thd/niujia/npc/guo");
			guo->move("d/thd/niujia/yangjia");
	  }
	  if (!objectp(qiu=present("qiu chuji",this_object())))
	  {
			guo=new("d/thd/niujia/npc/qiuchuji");
			guo->move("d/thd/niujia/yangjia");
	  }
	  call_out("say_baby",3+random(4),me);
	  me->delete_temp(QUESTDIR1+"xiangzhi");
	  me->set_temp(QUESTDIR1+"saybaby",1);
	  return;
  }
//帮助杨铁心杀敌
  if (me->query(QUESTDIR+"start")
 	 &&!me->query_condition("killer")
	 &&!me->query(QUESTDIR1+"over")
	 && me->query(QUESTDIR+"tongyin")
	 && me->query_temp(QUESTDIR1+"helpyangtiexin") )
  {
     tell_object(me,HIC"杨铁心怒气填膺，开门走出，大声喝道：“我就是杨铁心！你们干甚么？”两名兵丁吓了一跳，丢下火把转身退开。”\n" 
                       "火光中一名武官拍马走近，叫道：“好，你是杨铁心，跟我见官去。拿下了！”四五名兵丁一拥而上。杨铁心倒转枪来，\n"NOR+
                    RED"一招“白虹经天”，把三名兵丁扫倒在地，又是一招“春雷震怒”，枪柄跳起一兵，惯入了人堆，喝道：“要拿人，先得说说我犯了甚么罪。”\n"NOR); 
     message_vision(HIR"\n金兵突然看见$N你冲进来，全体一愣，突然一个金兵甲说道：“敢挡大爷捉拿要犯，给我杀了。”\n"NOR, me);
     me->delete_temp(QUESTDIR1+"helpyangtiexin");
     me->set_temp(QUESTDIR1+"fightjinbing",1);
/*	 
	 obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));	 
     obj->move(environment(me));  
	 obj->kill_ob(me);
	 obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));	 
     obj->move(environment(me));  
	 obj->kill_ob(me);
*/
	 obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));	 
     obj->move(environment(me));  
	 obj->kill_ob(me);
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
	 obj->kill_ob(me);
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
	 obj->kill_ob(me);
  //   remove_call_out("killme");
     call_out("check_kill", 5, me);        
  }      
}
int check_kill(object me)
{
	object bing;
	if (!me) return 0;
	
	if (file_name(this_object())!="/d/thd/niujia/yangjia")
	{
		me->set("quest/射雕英雄传/time",time());
		me->add("quest/射雕英雄传/fail",1);
		me->delete_temp("quest/射雕英雄传");
		message_vision(HIY"你擅自离开战斗场所，临阵脱逃，任务失败！明天再继续!\n"NOR,me);
		return 1;
	}
	if (!me->is_fighting()
		&& present("yang tiexin",this_object())
		&& !present("jin bing",this_object()))
	{
		me->set("quest/射雕英雄传/风雪惊变/成功保护杨铁心",1);
	    return 1;
	}
	call_out("check_kill",1,me);
}
//叙话，
int say_baby(object me)
{
	
	message_vision(HIY"\n众人喝着酒，彼此性情相投，不知不觉间都喝的差不都了！\n"NOR, me);
	message_vision(CYN"\n杨铁心此时说道：“我和郭大哥的浑家都已怀孕，丘道长文采斐然，要不替我们倆孩子起个名字如何”？\n"NOR, me);
	message_vision(CYN"\n丘处机沉吟了下说道：“靖康耻，犹未雪，臣子恨何时灭，我看就叫杨康和郭靖如何”？\n"NOR, me);
	message_vision(CYN"\n杨铁心说道：“若是两男孩，就结拜为兄弟，若是女孩为姐妹，男女就是夫妻”？\n"NOR, me);
	message_vision(CYN"\n丘处机说道：“正好我近日得到两柄匕首，作为二位兄弟子嗣的纪念物，也是老道我的一番心意”？\n"NOR, me);
	message_vision(YEL"\n丘处机从口袋里掏出两柄匕首，运功在剑上刻下“郭靖”和“杨康”字样，分赠给杨铁心和郭啸天？\n"NOR, me);

	message_vision(CYN"\n这一提议，众人都是觉得兴奋，朦胧间对未来充满了期待！\n"NOR, me);
	message_vision(HIG"\n杨铁心提议道，“今日大雪纷纷，我们借此美景何不痛饮一番，也不枉了这大好的时光”！\n"NOR, me);
	message_vision(HIR"\n你愿意接受杨铁心的痛饮（tongyin yes||no）建议么?请注意，只有一次选择机会!\n"NOR, me);

	add_action("do_tongyin","tongyin");
	
}
//tongyin
int do_tongyin(string arg)
{
	object me,yang,guo,qiu;
	int i;
	
	me=this_player();
	i=me->query_temp("quest/射雕英雄传/风雪惊变/hejiutime");
	message_vision(HIY"\n杨铁心喊道，“惜弱！上酒！”\n在此期间，$N发现杨铁心的夫人包惜弱上酒的时间有点久！\n"NOR, me);
	message_vision(HIC"\n到目前为止已经喝了"+chinese_number(i)+"碗酒，彼此间越聊越是投机，大有相见恨晚之意！\n"NOR, me);
	
	if (me->query("quest/射雕英雄传/tongyin"))
	{
		return notify_fail("你已经选择了痛饮并一醉方休！\n");
	}
	if (me->query("quest/射雕英雄传/风雪惊变/notongyin"))
	{
		return notify_fail("你没有选择和一群山野村夫痛饮，自己有新的选择！\n");
	}
	if (time()-me->query("quest/射雕英雄传/time")<86400)
	{
		return notify_fail("今天已经喝过酒了，还没消化，明天继续！\n");
	}
	if (arg=="yes")
	{
		message_vision(HIG"\n在此提议下，众人一番痛饮，$N心细如发，不经意间发现杨铁心夫人包惜弱期间离开很长一段时间，\n而且她回来时脸色稍微有些慌乱！\n"NOR, me);
		message_vision(HIC"\n几杯酒下肚后，$N酒量很浅，嘴里说着“干！干！”，逐渐昏睡过去！\n"NOR, me);
		//me->apply_condition("drunk",100);
		message_vision(HIR"\n在迷迷糊糊中似乎听见远处西面村口处传来阵阵马蹄的声音！\n"NOR, me);

		me->unconcious();
		me->set_temp("quest/射雕英雄传/风雪惊变/yestongyin",1);
		me->set("quest/射雕英雄传/风雪惊变/yestongyin",1);
		me->set("quest/射雕英雄传/tongyin",1);
		
	}
	if (arg=="no")
	{
		message_vision(HIG"\n你决定不再喝了，说道，“时光匆匆，既然大家都喝得尽兴，我看就到此为止，好吧？”\n"NOR, me);
		message_vision(HIG"\n杨铁心和郭啸天以及丘处机彼此看了看，纷纷点头，结束了这次喝酒。\n"NOR, me);
		me->set("quest/射雕英雄传/风雪惊变/notongyin",1);
		me->set("quest/射雕英雄传/bad",1);

		me->set_temp("quest/射雕英雄传/风雪惊变/notongyin",1);
		//me->set("quest/射雕英雄传/风雪惊变/yestongyin",1);
	}
	if (objectp(qiu=present("qiu chuji",this_object())))
	{
		destruct(qiu);
	}
	if (objectp(guo=present("guo xiaotian",this_object())))
	{
		destruct(guo);
	}
	me->add_temp("quest/射雕英雄传/风雪惊变/hejiutime",1);
	return 1;

}	


int valid_leave(object me, string dir)
{
       if (me->is_fighting())
                return notify_fail(RED"\n金兵大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
       if (present("jin bing",this_object()))

		   return notify_fail(RED"\n金兵大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
   		if(me->query_condition("killer")) 
   		          return notify_fail(RED"\n怎么进来的？？这里等wiz吧。\n"NOR);
        return ::valid_leave(me, dir);
}

