inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "������");
        set("long", @LONG
������Ǻ����سǡ������ش�ƫԶ���Լ�Զ������ԭ�����ˡ�
LONG );
               set("outdoors", "��ɽ");

	set("exits", ([
	       "east"   : __DIR__"hengyang2",
	       "west"   : __DIR__"hengyang1",
	       "south"  : __DIR__"chaguan",
	       "north"  : __DIR__"lingxingmen",
	]));

       /* set("objects", ([
                "/d/henshan/npc/lu" : 1,
        ]));*/
	//set("coor/x", 0);
	//set("coor/y", -110);
	//set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}

