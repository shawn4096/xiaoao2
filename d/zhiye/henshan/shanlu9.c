inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰错落，林壑幽深，溪泉飞瀑，云雾
缭绕，不觉心胸大快。南边是南台寺，北边通往福严寺。
LONG );
        set("exits", ([ 
               "southup"  : __DIR__"nantaisi",
               "northup"  : __DIR__"fuyansi",
        ]));

         set("outdoors", "衡山");

       //set("no_clean_up", 0);

        //set("coor/x", -50);
	//set("coor/y", 10);
	//set("coor/z", -10);
	setup();
        //replace_program(ROOM);
}

