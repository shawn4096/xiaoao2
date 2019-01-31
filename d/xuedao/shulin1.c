// shulin1，灌木林
// 产生动物之地
//采血，采肉
// by sohu@xojh
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", WHT"灌木林"NOR);
	set("long", @LONG
这是一片灌木林。低矮的灌木林簇在一块，密实的树枝象一蓬蓬巨伞
般覆盖这片低谷洼地，不见阳光。尺把厚的积雪积在地上，一脚踩下去，深
没膝盖。
LONG);

	set("exits", ([
		"south" : __FILE__,
		"east" : __DIR__"caodi",
		"west" : __FILE__,
		"north" : __DIR__"shulin2",
	]));

	set("outdoors", "xuedao");

	set("coor/x",40);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}


