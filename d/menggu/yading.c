// Room: /d/menggu/yading
inherit ROOM;
#include <ansi.h>
int do_canwu(string arg);
int do_climb(string arg);
void create()
{
  set ("short", "山崖顶");
  set ("long", @LONG
崖顶是个巨大的平台，积满了皑皑白雪。几块巨大的石头半卧在一边,
形状千奇百怪,上面有许多洞穿的小孔,风过处,如泣如诉.四边的山崖平平
如削,几棵矮树就斜长于崖边.
LONG);

	set("outdoors", "menggu");
    set("exits", ([ /* sizeof() == 1 */
	//	"down" : __DIR__"xuanya4",
]	));

  setup();
  replace_program(ROOM);
}

void init()
{
	add_action("do_climb", "climb");
	add_action("do_canwu", "canwu");
}


int do_climb(string arg)
{
	object me = this_player();
	int gain,cost;

	if(me->is_busy())
		return notify_fail("你还在忙着呢。\n");


	cost = ( 300-me->query_dex()*me->query_skill("dodge")/20 )/10;
	
	if ( cost<10 )cost = 10;
	cost *= 2;

	if( me->query("jing") < 30)
		return notify_fail("你累的实在爬不动了。\n");
	if (!arg||arg!="down")
	{
		return notify_fail("此处已经是崖顶，你要往哪儿去？\n");
	}
	if(arg == "down" )
	{
		message_vision( HIY"\n$N在悬崖上攀藤附葛，小心谨慎的爬下去。\n"NOR, me);
		me->move(__DIR__"xuanya4");
		message_vision( HIY"\n$N爬了下来。\n"NOR, me);
		return 1;
	}
	return 1;
}
//参悟

int do_canwu(string arg)
{
	object me;
	int i,j;
	me=this_player();
	if (!arg||arg!="上天梯")
	{
		return notify_fail("你要参悟什么武技？\n");
	}
		if (me->query("family/family_name")!="全真教") 
		{
			return notify_fail("此地空旷，你非全真教弟子，没有受到马钰道长的指点，要参悟什么？\n");
		}

		if (!me->query_temp("jyg/start")) 
		{
			return notify_fail("你没有在崖底准备好，根本没有任何领悟！\n");
		}

		if(me->is_busy())
			return notify_fail("你还在忙着呢。\n");

		message_vision(HIC"$N盘膝而坐，仔细回味方才爬崖的经过，心中略有所悟！\n"NOR,me);
		

	   if (!me->query("quest/qz/dichuan"))
	   {
		      return notify_fail("say 你非全真嫡传弟子，来此作甚？");
             

	   }
	   if (!me->query_dex(1))
	   {
		      return notify_fail("say 你的后天身法低于60，领悟不了任何东西？");
             

	   }

	   if (me->query_skill("xiantian-gong",1) < 200) {
              return notify_fail("say 我全真教一身功夫全在先天功，你先天功不足200，来此作甚？。");
              
       }
	   if (me->query_skill("yuanyang-lianhuantui",1) < 200) {
               return notify_fail("say 我鸳鸯连环腿不足200，来此作甚？。");
             
       }
	   	if (me->query("quest/qz/jyg/shangtianti/pass"))
		{
			return notify_fail("你的连环鸳鸯腿的铁脚绝技已经解开了”！\n");
		}
		if (time()-me->query("quest/qz/jyg/shangtianti/time")<86400)
		{
			return notify_fail("你来的太频繁了，明天再来！\n");
		}
	   if (me->is_busy())
	   {
		  return notify_fail("你正在手忙脚乱中!\n");
	   }
		me->start_busy(10);
		if (me->query("party/gongji")<100)
		{
			return notify_fail("你的门派贡献值不够100点，请继续努力去为门派奋斗吧\n");
		}
		me->add("party/gongji",-100);


		i = 20;
		  if(me->query("m-card-vip")) i =  18;
		  if(me->query("y-card-vip")) i =  15;
		  if(me->query("buyvip"))     i =  12;
		  i=random(i);
		j=random(me->query("kar"));
		if( i<3
			&& random(me->query_dex())>50
			&& me->query("kar")<31
			&& j > 27 ) 
		{
			tell_object(me,HIC"\n你听了的马钰道长的亲自指点，联想起早期自己所用金雁功的种种心得，两下印照。\n"NOR);
			tell_object(me,HIR"\n忽然脚底涌泉穴一股大力传来，你顿时感觉身轻如燕，腿部力量大增，瞬间领悟了这上天梯绝技的运气法门。\n"
						NOR);
			me->set("quest/qz/jyg/shangtianti/pass",1);
			log_file("quest/qzshangtt", sprintf("%8s(%8s) 失败%d次后，学到上天梯绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/qz/jyg/shangtianti/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			command("haha"+me->query("id"));		
			
			tell_object(me, "恭喜解密上天梯绝技绝技成功!\n");/**/
			
		}	
	   else
		{
			log_file("quest/qzshangtt", sprintf("%8s(%8s) 解密上天梯绝技绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/qz/jyg/shangtianti/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"你结合马钰道长的指点，可是对上天梯绝技的奥妙全然不得要领。\n\n"NOR);
	
			me->add("quest/qz/jyg/shangtianti/fail",1);
			me->set("quest/qz/jyg/shangtianti/time",time());
			me->start_busy(1+random(3));
			
			return notify_fail("非常遗憾解密连金雁功之上天梯绝技失败"+me->query("quest/qz/jyg/shangtianti/fail")+"次。\n");
		}
		me->add_busy(1);

	
	return 1;
}



