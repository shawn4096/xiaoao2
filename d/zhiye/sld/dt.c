// dt.c
//
// 大厅
inherit ROOM;
void create()
{
	set("short","大厅");
	set("long",@long
这是一间硕大无朋的屋子，里面足可容千人之众。大厅彼端居中并排
放着两张竹椅，铺了锦缎垫子，显然是给教主夫妇坐的。此处是神龙教平
日议事之处。
long);
	set("exits",([
	    "north" : __DIR__"th",
         "south" : __DIR__"slj",
		 "west" : __DIR__"shenlongtang",     
]));
set("objects",([
	"/kungfu/class/sld/hongantong" : 1,
	//"/kungfu/class/sld/sq" : 1,
	//"/kungfu/class/sld/ptt" : 1,
	//"/kungfu/class/sld/stt" : 1,
	__DIR__"npc/cyjz" : 2,
]));
	set("coor/x",520);
  set("coor/y",440);
   set("coor/z",90);
   setup();
}
	    	
