// Room: /d/shaolin/banruo6.c
// Date: YZC 96/01/19

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "般若堂六部");
	set("long", @LONG
这是一间极为简陋的禅房。环视四周，除了几幅佛竭外，室内空荡荡地
别无他物。地上整齐的摆放着几个破烂且发黑的黄布蒲团，几位须发花白的
老僧正在坐在上面闭目入定。这里是本寺十八罗汉参禅修行的地方，不少绝
世武功便是在此悟出。
LONG
	);

	set("exits", ([
		"south" : __DIR__"banruo5",
		"north" : __DIR__"banruo7",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/cheng-xin2" : 1,
		"d/shaolin/obj/muchai" : 1,
	]));
	set("coor/x",110);
	set("coor/y",280);
	set("coor/z",110);
	setup();
}
void init()
{
	object me=this_player();
	add_action("do_pi","pi");

}

int do_pi(string arg)
{
	object muchai,weapon;
	int i,j;
	object me=this_player();
	weapon=me->query_temp("weapon");
	if (!arg||arg!="木柴")
		return notify_fail("此地空无，你要劈什么？\n");
	if (!me->query_temp("rmdf/askchengxin"))
	{
		return notify_fail("此地乃是少林寺般若堂刀法要地，你就不怕少林寺举寺追杀你么？\n");

	}
	if (!present("mu chai",environment(me)))
	{
		return notify_fail("此地没有木柴，你要劈什么？\n");
	}
	if (!weapon||weapon->query("id")!="mu dao")
	{
		return notify_fail("练习燃木刀法需要木刀方可修习！\n");
	}
	if( time()- me->query("quest/sl/rmdf/ranmu/time")<86400)
		return notify_fail("少林禅宗讲究的是顿悟，练功不宜太频繁！\n");

	message_vision(HIY"$N运功全身，大喝一声，挥舞手中的木刀，劈向地上的木柴！\n"NOR,me);
	
	i = 20;
	if(me->query("m-card-vip")) i =  18;
	if(me->query("y-card-vip")) i =  15;
	if(me->query("buyvip"))     i =  10;
	i=random(i);

	j=random(me->query("kar"));

	if( i<4 
		&& me->query("kar")<31
		&& j >=26 ) 
	{
		tell_object(me,HIY"\n你一刀劈出，顿觉手中木刀一阵炙热，对燃木刀法的奥妙颇有心得。\n"NOR);
		tell_object(me,HIG"\n顷刻之间，劲气贯通，你手上经脉尽通，领悟了燃木绝技的要旨。\n"NOR);
		tell_object(me,HIR"恭喜解密燃木绝技成功!\n"NOR);
		me->set("quest/sl/rmdf/ranmu/pass",1);
		log_file("quest/rmdfranmu", sprintf("%8s(%8s) 失败%d次后，学到燃木绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/sl/rmdf/ranmu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		me->delete_temp("rmdf");
		return 1;
		
	}	
   else
	{
		log_file("quest/rmdfranmu", sprintf("%8s(%8s) 解密燃木绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/sl/rmdf/ranmu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你体味澄信的指点，可是对燃木的奥妙全然不得要领。\n\n"NOR);
		me->add("quest/sl/rmdf/ranmu/fail",1);
		me->set("quest/sl/rmdf/ranmu/time",time());
		me->start_busy(1+random(3));
		me->delete_temp("ranmu");
		tell_object(me,"非常遗憾,解密燃木失败"+me->query("quest/sl/rmdf/ranmu/fail")+"次。\n");
		return 1;
	}

}


