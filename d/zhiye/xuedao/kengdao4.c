// hollow.c
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "��ӵ�");
        set("long", @LONG
����Ѫ�����ڵ�һ���Ƚϴ�Ŀӵ���Ϊ�����Ӹ�����Ҫɽ�����ã�
����������һ���ŵ���ľ�����죬��������Զ��������������Ϣ��
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "east"   : __DIR__"midong",
			"south"   : __DIR__"kengdao3",
				"north"   : __DIR__"huanxidong1",
        ]));
        set("item_desc", ([
           // "dong"   : "һ�������İ��Ķ�Ѩ��\n",
        ]));
        set("objects",([
             //   __DIR__"npc/zhizhu" : 1,
        ]));
		create_door("north", "С��", "south", DOOR_CLOSED);

        setup();
}
