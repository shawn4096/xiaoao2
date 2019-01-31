// /d/xiangyang/xuanwumen.c

#include <ansi.h>
inherit ROOM;
string look_gaoshi();

void create()
{
        set("short", YEL"玄武门"NOR);
        set("long", @LONG
这里是军事重镇襄阳城的北门，不时地有顶盔贯甲的士兵走来走去。向北
可以进入陕西、河南境内，还能去参观著名的武当山。城门的墙上张贴着一纸
告示(gaoshi)。
LONG
        );
        set("outdoors", "襄阳");
        set("xyjob", 1);
        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));

        set("objects", ([
                CLASS_D("gaibang/guojing") : 1,
                NPC_D("guanfu/wujiang") : 1,
//                "d/xiangyang/npc/yangguo" : 1,
                NPC_D("guanfu/bing") : 2,
	]));
        set("exits", ([
                "north" : __DIR__"outnroad1",
                "south" : __DIR__"nroad1",
        ]));

	set("incity",1);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n襄阳安抚使\n吕文德\n";
}

 void init()
{
 object me = this_player();

me->set("env/brf_go",1);
 /*
 if(!me->query("cw_exp")) 
                          me->delete("relife/exp_ext");
if(me->query("combat_exp")<100000)
      me->apply_condition("db_exp", 1000);

me->set("relife/exp_ext",4);*/



}



