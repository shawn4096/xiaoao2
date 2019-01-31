#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",HIC"群玉院精舍"NOR);
        set("long", @LONG
此处是衡阳城大大有名的群玉院精舍，是为客人和姑娘们
专门设置的，屋内摆放了一张大大的床，上面铺满了厚厚的被
褥，雕龙画凤，极尽奢华，看起来就非常舒服。
LONG );
	set("objects", ([
		//__DIR__"npc/feiyan" : 1,
		//__DIR__"npc/qufeiyan" : 1,

	]));

	set("exits", ([
		"south" : __DIR__"lingyinge",
				//"south" : __DIR__"hengyang11",

	]));	

	//set("no_fight", 1);
	set("sleep_room", 1);

	setup();
		
}	
