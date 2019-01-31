// nroad6.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
#include "/d/suzhou/npc/lchj.h"

void create()
{
        set("short","ɽ·");
        set("long",@LONG
������һɽ·�ϣ�������һ����Сɽ��Զ�����Կ��������ѩ
��ɽ�⡣��Χ�������Ѿ����ѿ��õ��ˡ�
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
		message_vision(HIC"ֻ���ö����ᣬ������һ��������һ�����������������Ž��߳�����\n"NOR, me);
		message_vision(HIC"һλƤ������΢�ڵĿ��ι��Ｒ�۶���������أ����������ģ����\n"NOR, me);

	}
	return;
}
