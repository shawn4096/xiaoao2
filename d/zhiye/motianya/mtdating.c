//room: mtdating.c

inherit ROOM;
#include <ansi.h>
#define XKX_QUEST1 "quest/������/Ħ����/"

void create()
{
        set("short", YEL"Ħ���¶�"NOR);
        set("long", @LONG
�����Ħ�����ˡ������ͺͺ�ģ���һ��С��Ҳû�У��嶥��Ҳ
ʮ�ֿ������������������ƣ������������ƶ�֮�У�ʹ���ľ�������
������һ��Сľ�ݡ�
LONG );
        set("outdoors", "motianya");
        set("exits",([
                "east" : __DIR__"mtxiaowu",
                "down" : __DIR__"mtyadi",
        ]));
        set("objects",([
                __DIR__"npc/xieyan" : 1,
        ]));

        set("outdoors", "Ħ���¶�");
        setup();
}

void init()
{
	object me,ob;
	me=this_player();
	ob=present("xie yanke",environment(me));
	if (me->query_temp(XKX_QUEST1+"agree"))
	{
		message_vision(HIY"��յ���Ħ���¶���������Զ��һ����������������������\n"NOR,me);
		if (ob)
		{
			message_vision(HIC"л�̿ͺȵ�����˭��װ��Ū������˵���׷�˳�ȥ��\n"NOR,me);
			destruct(ob);
		}
	}
}


int valid_leave(object me, string dir)
{
        object ob;

        if (dir == "east" &&
            objectp(ob = present("xie yanke", this_object())) &&
            living(ob))
                return notify_fail("л�̿Ͱ���һ�����ȵ��������һ�������\n");

        return ::valid_leave(me, dir);
}

