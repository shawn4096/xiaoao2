// Room: /d/huashan/shulin2.c
// Date: Look 99/03/25
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", WHT"灌木林"NOR);
        set("long", @LONG
你眼前骤然一黑，朦胧中，只见左右前后，到处都是铺天盖地的灌木林。
低矮的灌木林簇在一块，密实的树枝象一蓬蓬巨伞般覆盖这片低谷洼地，不见
丝毫阳光，地面阴寒至极。尺把厚的积雪积在地上，一脚踩下去，深没膝盖。
你似乎迷失了方向，象没头苍蝇般到处乱闯。
LONG);

        set("exits", ([
                "east" : __DIR__"shulin3",
                "south" : __FILE__,
                "west" : __DIR__"shulin1",
                "north" : __FILE__,
        ]));

        set("outdoors", "xuedao");
        set("coor/x",40);
		set("coor/y",100);
		set("coor/z",0);
		setup();
}

void init()
{
       set("exits/east", __DIR__"shulin"+(1+random(4)));
       set("exits/south", __DIR__"shulin"+(1+random(4)));
       set("exits/north",  __DIR__"shulin"+(1+random(4)));
       set("exits/west",  __DIR__"shulin"+(1+random(4)));
}

