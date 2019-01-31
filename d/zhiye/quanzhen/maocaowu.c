inherit ROOM;

void create()
{
        set("short", "茅草屋");
        set("long", @LONG
这里是百花谷内靠阳处的一间茅草屋。一排三间组成，茅草崭新
显然为新搭建不久。屋外摆放了几个蜂箱，有不少白玉蜂在蜂房进出
这些白玉蜂甚是怪异，显然不是寻常品种。
LONG);
        //set("outdoors", "quanzhen");
        set("exits", ([
                "out" : __DIR__"baihuagu",
				      
        ]));
		set("objects", ([
              "kungfu/class/quanzhen/zhou" :1,
        ]) );

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}


