// nroad7.c
// Modified by Java Apr.27 1998

inherit ROOM;
void create()
{
        set("short","山路");
        set("long",@LONG
你走在一山路上，四周有一座座小山丘。
LONG );
        set("exits",([
                //"eastdown" : "/d/xueshan/shanjiao",
                "south"    : "/d/xuedao/nroad6",
        ]));
        set("objects",([
               "/d/xuedao/npc/wangxiaofeng" : 1,
			   "/d/xuedao/npc/shuisheng" : 1,

        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}

