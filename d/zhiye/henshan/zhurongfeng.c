#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "祝融峰");
        set("long", @LONG
祝融峰之高为衡山大四绝之首。在此俯瞰群峰，尽收眼底。东望
湘江，南及五岭，北瞰洞庭，西视雪山。唐朝杜甫望岳诗中有「祝融
五峰尊，峰峰次低昂」。著名诗人韩愈亦以「祝融万丈拔地起，欲见
不见轻烟里」极言其高。
LONG );
        set("exits", ([
                "eastdown"   : __DIR__"shanlu004",
        ]));

        /*set("objects", ([
                CLASS_D("henshan") + "/mo" : 1,
        ]));
      */		

        //set("no_clean_up", 0);

     //   set("coor/x", -70);
	//set("coor/y", 100);
	//set("coor/z", 70);
	setup();
      //  replace_program(ROOM);
}

