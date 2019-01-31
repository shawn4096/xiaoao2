// xuegu.c 
// sohu 
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "大雪谷");
	set("long", @LONG
此地是一个巨大的雪谷。气候寒冷，导致积雪数年不化，雪层
上覆盖了一层薄薄的寒冰，极为光滑，因冰层厚度不匀，人在其上
行走极其容易掉入雪坑中，最终导致缺氧而死。
LONG);
	set("exits", ([
		"east" : __FILE__,
		"south" : __FILE__,
		"west" : __DIR__"xuegu",
		"north" : __DIR__"xuegu",
	]));

	set("outdoors", "血刀门");

   setup();
}
void init()
{
	object me = this_player();
	add_action("do_jump", ({"jump", "tiao","yue"}));
	
}

int do_jump(string arg)
{
	object room,me = this_player();
	//跃下大雪谷
    if( arg == "down")
    {
		if (!(room = find_object("/d/xuedao/sxuegu10")))
			room = load_object("/d/xuedao/sxuegu10");
		if(!room)
		{ 
			tell_object(me,HIR"\n你无论怎么跳，发现都还在原地!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)缺少sxuegu10.c文件。\n", me->name(1),me->query("id")) );	
			
		}
		message_vision(HIW"$N发现此处冰层甚薄，于是跃身纵起，头朝下，腿朝上，以入水姿势钻入雪中！\n"NOR, me);
		me->move(room);
		me->delete_temp("xd/xdzj");
		me->start_busy(1);
		me->add("neili",-800-random(300));
        tell_room(environment(me),HIC"\n只见一个身影飞起，跃入雪中，原来是"+me->name()+"钻入雪中!\n"NOR, ({me}));                       
	}

	return 1;
}