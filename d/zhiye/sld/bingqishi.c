#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����������̵��Ӱڷű������������������ҵض���һЩ
�������е��Ѿ����ư߰��ˣ��еĻ��Ƿ���͸��������������
����ʱ�򣬾͵���������ѡ����,һ�Եı�����(jia)�Ϲ��˼�
����Ƥ��ס�
LONG);
        set("exits", ([
                "north" : __DIR__"road2",
        ]));
        set("objects", ([
                __DIR__"npc/obj/bian" : 2+random(3),
                __DIR__"npc/obj/shejia" : 1+random(2),
                "/clone/weapon/bishou" : 2+random(2),			
				__DIR__"npc/obj/hook" :  2+random(2),
				__DIR__"npc/obj/huxi" :  2+random(2),
        ]));

        setup();
        replace_program(ROOM);
}
