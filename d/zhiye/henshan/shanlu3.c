inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰错落，林壑幽深，溪泉飞瀑，云雾
缭绕，不觉心胸大快。再走一会儿就是半山亭了。
LONG );
        set("exits", ([ 
               "southup"    : __DIR__"chidifeng",
               "northwest"  : __DIR__"shanlu4",
        ]));

         set("outdoors", "衡山");

       //set("no_clean_up", 0);

       // set("coor/x", -10);
	//set("coor/y", 20);
	//set("coor/z", 10);
	setup();
       // replace_program(ROOM);
}
 
