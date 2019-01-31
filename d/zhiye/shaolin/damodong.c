// Room: /d/shaolin/damodong.c
// Date: YZC 96/01/19

inherit ROOM;
#include <ansi.h>

int do_canwu(string arg);

void create()
{
	set("short", "达摩洞");
	set("long", @LONG
这里是达摩古洞。五百年前南天竺僧人菩提达摩来到少林寺，见此风水
宝地，就住下来广罗弟子，传授禅宗，开创少林寺佛教禅宗千年不败之基。
达摩祖师常在此面壁悟道，一坐十年，壁间隐隐似仍可看到他面壁时的打坐
姿态。除地上的几块竹片外，洞中空无一物。
LONG
	);

	set("exits", ([
		"out" : __DIR__"bamboo1",
	]));

	set("coor/x",40);
	set("coor/y",520);
	set("coor/z",150);
	setup();
}

void init()
{
	object me = this_player();

	if ((int)me->query_temp("bamboo/count") == 14 
	&&  (int)me->query_skill("dodge", 1) >= 30 
	&&  (int)me->query_skill("dodge", 1) <= 100 
	&&  present("bamboo", me) )
	{
		me->receive_damage("jing", 20);
		me->improve_skill("dodge", me->query("int"));
	}
	if (me->query_temp("yzc/askxuancheng"))
	{
		add_action("do_canwu","canwu");	
	}
	add_action("do_mianbi","mianbi");	
}

int do_mianbi()
{
	int i,j,x,y;
	object me = this_player();
	i = (int)me->query("shen");
	j = me->query("combat_exp");
	y = me->query_skill("yijin-jing",1);
	x = me->query_skill("buddhism",1);

	if ( me->is_busy() ) return notify_fail("你正忙着呢,心情静不下来。\n");

	me->start_busy(random(2));
	if (me->query("jing") < 100)
		return notify_fail("你精神恍惚，需要休息了。\n");
	me->receive_damage("jing", 50+random(50));
	if (x >= 200)
		if (i < 0) {
			me->add("shen",1000+random(5000));
			message_vision("$N面对着达摩洞后半边的石壁跌坐静思，良久，似有所悟。\n", me);
			me->set_temp("sl_mianbi",1);
			return 1;
		} else if ( i > 0) {
			me->add("shen",-1000-random(5000));
			me->set_temp("sl_mianbi",2);
			message_vision("$N面对着达摩洞后半边的石壁静坐沉思良久，似有所悟。\n", me);
			return 1;
		}
	message_vision("$N面对着达摩洞后半边的石壁沉思了一会，结果心情越想越乱，不由地站了起来。\n", me);
	return 1;
}

int do_canwu(string arg)
{
	object me=this_player();
	int i;
	i=random(me->query("kar"));
	if (!me->query_temp("yzc/askxuancheng"))
	{
		return notify_fail("你无缘无故，来此参悟什么？\n");
	}
	if (!arg||arg!="一指禅")
	{
		return notify_fail("你要参悟什么？\n");
	}
	if (time()-me->query("quest/sl/yzc/time")<86400)
	{
		return notify_fail("你来的也太勤快点了！\n");
	}
	if (me->query("quest/sl/yzc/pass"))
	{
		return notify_fail("你已经通过观摩达摩图像，领悟了一指禅的奥妙！\n");
	}
	if(i>=25)
	{
		tell_object(me,HIG"\n你平心静气，按照玄澄大师的指点，对一指禅的真正奥妙似乎有些心得。\n"NOR);
		tell_object(me,HIC"\n你把玄澄大师告诉你的要诀在心中不断演练，运转不绝。\n"NOR);       
		tell_object(me,HIW"\n渐渐你的思路逐渐和石壁上的画像彼此呼应，好像逐渐要融合为一的趋势。\n"NOR); 
		tell_object(me,HIC"\n你参悟良久，若有所悟，一指禅内劲骤然提到极限，一股沛然莫能御内劲流\n"+
							"遍你的七筋八脉。你感觉到平时功力运转艰涩之处全然不见，圆转如意之间\n"+
							"不禁轻声吟道:西来大意谁能穷，五乳峰头九载功。若道真诠尘内了，达摩洞内自圆通。\n"NOR);
		tell_object(me,HIR"\n恭喜你，你已经将一指禅的奥秘和达摩图像融合，融会贯通。\n"NOR); 
		me->set("quest/sl/yzc/pass",1);
		log_file("quest/yizhichan", sprintf("%8s(%8s) 失败%d次后，彻底领悟一指禅的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/sl/yzc/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/sl/yzc/fail",1);
		me->set("quest/sl/yzc/time",time());
		
		tell_object(me,HIY"你参悟半天，心烦意乱，很难静下心来，对一指禅的真正奥妙全然不得要领。\n\n"NOR);
		
		log_file("quest/yizhichan", sprintf("%8s(%8s) 彻底领悟一指禅解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/sl/yzc/fail"),i,me->query("combat_exp")) );
	}
	me->start_busy(2);
	return 1;

}