inherit ROOM;

void create()
{
        set("short", "正川门");
        set("long", @LONG
正川门是南岳大庙的第三进。院内则是玄德宗殿，关圣殿，观音
阁等楼宇。
LONG );
        set("exits", ([ 
               "south"  : __DIR__"kuixingge",
               "north"  : __DIR__"yubeiting",
        ]));

              set("outdoors", "衡山");

       //set("no_clean_up", 0);

        //set("coor/x", 0);
	//set("coor/y", -80);
	//set("coor/z", 0);
	setup();
     //   replace_program(ROOM);
}

