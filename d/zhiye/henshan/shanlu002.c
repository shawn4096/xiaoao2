inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰错落，林壑幽深，溪泉飞瀑，云雾
缭绕，不觉心胸大快。一直往西可通往磨镜台和天柱峰。 
LONG );
        set("exits", ([ 
                "southeast"  : __DIR__"banshan",
                "west"       : __DIR__"shanlu001",    
        ]));

         set("outdoors", "衡山");

       //set("no_clean_up", 0);

      //  set("coor/x", -30);
	//set("coor/y", 50);
	//set("coor/z", 20);
	setup();
       // replace_program(ROOM);
}

