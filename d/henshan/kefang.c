#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "��ɽ�ɿͷ�");
        set("long", @LONG
����һ��ܴ�Ŀͷ����Ǻ�ɽ�ɹ�ǰ��������ο���ס�ķ����
��ʮ�ּ�ª�� ��ǽ����ʮ����Сľ���� ��Ȼ��ª�˵㵫���ܱ��ڻ�
ɽ��¶��ǿ�ö��ˡ�
LONG );
	set("sleep_room", 1);
	set("no_fight", 1);
	set("exits", ([
	       "south" : __DIR__"changlang",
	]));
	//set("coor/x", -30);
	//set("coor/y", 110);
	//set("coor/z", 40);
	setup();
      //  replace_program(ROOM);
}


