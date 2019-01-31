// By River 2002.6.3

inherit ROOM;
#include <ansi.h>
int do_check(object me);

void create()
{
	set("short", "石梁尽头");
	set("long", @LONG
石梁凹凸不平，又加终年积雪，溜滑异常，在那石梁上，约有七八尺长的
一个缺口，奔一段，跃过一个缺口，接连过了七个断崖，眼见对面山上是一大
片平地。石梁已到尽头，可是尽头处却有一个极长缺口，看来总在一丈开外，
缺口彼端盘膝坐着一个书生，手中拿了一卷书，正自朗诵。那书生身后又有一
个短短的缺口。
LONG
	);
	set("outdoors", "桃源县");
	set("exits", ([
		"north" : __DIR__"hetang",
	]));

	set("objects", ([
		__DIR__"npc/duzi" : 1,
	]));

	setup();
}
/*
void init()
{
	
	object me=this_player();
   
	if (me->query_temp("nqg/askyingok"))
	{
		add_action("do_check","find");
	}


}
*/
int valid_leave(object me, string dir)
{
	if ( dir == "north"
	&& !me->query_temp("yideng/shusheng_pass")){
		if ( present("shu sheng", environment(me)))
			return notify_fail("书生端坐你面前，除了他所坐之处，别地无可容足。\n");
		else 
			return notify_fail("石梁尽头短短的缺口，使你感觉无法立足。\n");
	}
	return ::valid_leave(me, dir);
}
 /*
int do_check(object me)
{
	object duzi;
	me=this_player();
	duzi=present("shu sheng",environment(me));
    if (objectp(duzi))
    {
		
		message_vision(HIC"书生站在那儿，越瞅你越像奸细，看起来想杀死你。\n"NOR,me);

		return 1;
		
    }
	if (!objectp(me)) return 0;

    message_vision(HIC"$N仔细一看，发现一条小径，通向前方。\n"NOR,me);
	me->set_temp("yideng/shusheng_pass", 1);
	return 1;	

}*/