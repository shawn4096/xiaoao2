#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�������Ĵ����ң���������ܰݷ������ܣ�������������
����ƽʱ�ճ��Ѽ�����Ʒ����Ҫ������
LONG);
        set("exits", ([
                "east" : __DIR__"th",
        ]));
        set("objects", ([
                __DIR__"npc/obj/jieyao" : 1+random(3),
                __DIR__"npc/obj/jiudai" : 1+random(2),
                __DIR__"npc/obj/shefen" : 1+random(2),
				__DIR__"npc/obj/sheyao" : 1+random(2),
				__DIR__"npc/obj/shengzi" : 1+random(2),
				"kungfu/class/sld/pangtoutuo" : 1,
        ]));

        setup();
        replace_program(ROOM);
}
