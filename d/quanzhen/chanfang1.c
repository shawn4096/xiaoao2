#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������ȫ��̵��Ӱڷű������������������ҵض���һЩ
�����е��Ѿ����ư߰��ˣ��еĻ��Ƿ���͸����ȫ���������
��ʱ�򣬾͵���������ѡ���С�
LONG);
        set("exits", ([
                "east" : __DIR__"chanfang2",
        ]));
        set("objects", ([
                __DIR__"npc/obj/gangjian" : 1+random(3),
                __DIR__"npc/obj/gangdao" : 1+random(2),
                __DIR__"npc/obj/tiejia" : 1+random(2),
				"clone/weapon/fuchen" : 1+random(2),
        ]));

        setup();
        replace_program(ROOM);
}
