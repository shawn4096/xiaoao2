inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "��������");
        set("long", @LONG
�����Ǻ��������֣����·�˴Ҵ��򶫶��У��ϱ�����һ����ǣ�
������һ��װ�κܵ��ŵĵ��̣��������Ŵ������˷��塣
LONG );
               set("outdoors", "��ɽ");

	set("exits", ([
	        "east"   : __DIR__"hengyang1",
	        "west"   : __DIR__"hsroad4",
	        "north"  : __DIR__"lingyinge",
	]));

//	set("coor/x", -20);
//	set("coor/y", -110);
//	set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}

