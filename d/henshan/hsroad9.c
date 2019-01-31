inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "南岭山口");
        set("long", @LONG
这里是南岭的一个山口。南面是岭南的大镇佛山，北面是湖南的
地界。岭南广东富庶繁盛，颇有豪侠之士。
LONG );
         set("outdoors", "衡山");

        set("exits", ([
                "northdown" : __DIR__"hsroad5",
                "southeast" : "/d/foshan/xiaolu3",
        ]));
 //       set("coor/x", -40);
//	set("coor/y", -120);
//	set("coor/z", 10);
	setup();
       //replace_program(ROOM);
}
