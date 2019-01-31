// nroad6.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
#include "/d/suzhou/npc/lchj.h"

void create()
{
        set("short","山路");
        set("long",@LONG
你走在一山路上，四周有一座座小山丘。远处可以看见终年积雪
的山尖。周围的树草已经很难看得到了。
LONG );
        set("exits",([
                "north"   : __DIR__"nroad7",
                "southup" : __DIR__"nroad5",
        ]));
        set("objects",([
                __DIR__"npc/huatiegan" : 1,
        ]));
//	set("no_clean_up", 0);
        set("outdoors", "xuedao");
        setup();
//        replace_program(ROOM);
}

void init()
{
	object me = this_player();
	if (me->query_temp(QUESTDIR3+"tofindshui")) 
	{
		//me->delete_temp(QUESTDIR3+"tofindshui");
		call_out("clone_shui", 3+random(3), me);
	}
}

void clone_shui(object me)
{
	object shui;

	if( environment(me) != this_object()) return;

	if (!objectp(shui=present("shui sheng",environment(me))))
	{
		shui=new("d/xuedao/npc/shuisheng");
		shui->move(environment(me));
		message_vision(HIC"只听得叮玲玲，叮玲玲一阵铃声，一骑马自西至东，沿着江边驰来。\n"NOR, me);
		message_vision(HIC"一位皮肤略有微黑的俊俏姑娘疾驰而来，面上兀自气呼呼的模样。\n"NOR, me);

	}
	return;
}
