// By River 2002.6.3

inherit ROOM;
#include <ansi.h>
int check_yideng(object me);

void create()
{
	set("short", "石屋正房");
	set("long", @LONG
室中小几上点着一炉檀香，几旁蒲团上坐一个僧人。只见他身穿粗布僧袍，
两道长长的白眉从眼角垂了下来，面目慈祥，眉间虽隐含愁苦，但一番雍容高
华的神色，却是一望而知。
LONG
	);
	set("exits", ([
		"east" : __DIR__"xiangfang",
		"south" : __DIR__"zhulin",
	]));

	set("objects", ([
		__DIR__"npc/yideng" : 1,
	]));

	setup();
}

void init()
{
	object me=this_player();
	if (me->query_temp("nqg/askyingok"))
    {
		tell_object(me,HIY"\n\n\n你刚刚到达门口，却听到身后有四个人喊道，“师傅！危险！\n"NOR);
		tell_object(me,HIY"\n\n\n屋内一个老和尚盘膝做在哪儿，口诵佛号，”阿弥托福“！\n"NOR);
       // call_out("check_yideng",1,me);
		return;
	}

}
/*
int check_yideng(object me)
{

	
	object yideng;
	yideng=present("yideng dashi",environment(me));
    if (!objectp(yideng)) 
    {
		return notify_fail("非常遗憾，一灯大师为人所暗杀！\n");
    }
	
	if (!objectp(me)) return 0;
	
	if (me->query_temp("yideng/kill_yideng", 1)&& !objectp(yideng))
	{
		me->add("shen",-random(2000000));
		me->set("tls/killyideng",1);

		message_vision(HIC"\n\n$N哼了一声道，再厉害的秃驴我照样是我手下败将。\n"NOR, me);

		message_vision(HIC"\n\n$N想起瑛姑说的要人头之事，看来是该到了回去给瑛姑交差的时间了。\n"NOR, me);
        return 1;
	}
	
	return 1;

}*/