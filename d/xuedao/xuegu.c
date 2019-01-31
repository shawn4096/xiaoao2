// xuegu.c 
// sohu 
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "大雪谷");
	set("long", @LONG
此地是一个巨大的雪谷。气候寒冷，导致积雪数年不化，雪层
上覆盖了一层厚厚的寒冰，极为光滑，因常年寒冷导致冰层不断叠
加，人在其上可以放心行走。向上看去，山坡处有一处岩石(yan)，
上面似乎有人影。
LONG);
	set("exits", ([
		"east" : __FILE__,
		"south" : __FILE__,
		"west" : __FILE__,
		"north" : __DIR__"xuegu1",
	]));
     set("item_desc", ([
                "yan": "上面有个突出的岩石。似乎可以(jump)跳上去。\n",
                "岩石":  "上面有个突出的岩石。似乎可以(jump)跳上去。\n",
        ]) );

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
    if( arg == "up")
    {
		if(me->query_skill("dodge")<150) 
		{
			message_vision(HIC"\n$N吸了一口气，尝试跳上雪谷，却突然发现风大山高，却退了回来。\n"NOR,me);
			return 1;
		}
		if (!(room = find_object("d/xueshan/xuegu2")))
			room = load_object("d/xueshan/xuegu2");
		if(!room)
		{ 
			tell_object(me,HIR"\n你无论怎么跳，发现都还在原地!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)缺少xuegu2.c文件。\n", me->name(1),me->query("id")) );	
		}
		else
		{
			message_vision(HIC"$N看准一块半空中突起的岩石，深吸一口气，高高跃起，顺势在岩石上微一借力，随即窜上雪谷。\n"NOR, me);
			me->move(room);
			me->delete_temp("quest/outxuegu");//
			me->start_busy(1);
            tell_room(environment(me),HIC"\n只见一个身影飞身而过，原来是"+me->name()+"从雪谷下跳上来。\n"NOR, ({me}));                       
		}
	
		return 1;
	}

	
}