inherit ROOM;

void create()
{
        set("short", "狮子岩");
        set("long", @LONG
狮子岩布满奇形怪状的岩石，细究则绝类狮子，腾跃伏吼，各肖
其类。到狮子岩，祝融峰已经在望了。
LONG );
        set("exits", ([ 
               "southwest"  : __DIR__"nantian",
               "northup"    : __DIR__"wangritai",
        ]));

         set("outdoors", "衡山");
       //set("no_clean_up", 0);

       // set("coor/x", -40);
	//set("coor/y", 80);
	//set("coor/z", 20);
	setup();
        //replace_program(ROOM);
}

