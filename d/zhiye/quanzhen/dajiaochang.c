// Code of ShenZhou
// road: /zhongnan/dajiaochang.c

#include <ansi.h>
inherit ROOM;
#include "/kungfu/class/quanzhen/beidou.h" 

void create()
{
        set("short", HIY"大校场"NOR);

        set("long", @LONG
这是一个位於终南山山腰的圆坪，四周群山环抱。山脚下有一座大池。每年
腊月，全真派便於此地举行大校，以考察门下弟子在这一年间的进境。往南是一
条崎岖的山道。往西是一条通往峰顶的山路。往北行便是重阳宫。只见远处十馀
幢道观屋宇疏疏落落的散处山间。
LONG );

        set("exits",([ 
			"north" : "/d/quanzhen/jiaobei",
        ]));

        set("objects", ([
                CLASS_D("quanzhen") + "/zhaozhijing" : 1,
				/*"/d/quanzhen/npc/chenzhiyi":1,
				"/d/quanzhen/npc/cuizhifang":1,
				"/d/quanzhen/npc/qizhicheng":1,
				"/d/quanzhen/npc/shenzhifan":1,
				"/d/quanzhen/npc/fangzhiqi":1,
			    */
        ]));

        set("cost",1);
        set("outdoors", "quanzhen");
        setup();
}

