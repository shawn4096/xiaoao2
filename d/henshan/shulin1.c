#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","����");
        set("long", @LONG
�����Ǻ�ɽ��ɽ����һƬ���֣���˵���ﾭ����Ұ�޳�û��
LONG );

	set("objects",([
	   //   __DIR__"npc/hunter" : 1,	
		  __DIR__"npc/jian-ke" : 1,	
	]));

	set("exits", ([
		"east"  :  __DIR__"shanlu6",
	]));

	set("outdoors","��ɽ");
	//set("coor/x", -70);
	//set("coor/y", 50);
	//set("coor/z", 20);
	setup();
      //  replace_program(ROOM);
}
