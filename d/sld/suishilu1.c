//suishilu1


#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "��ʯ·");
	set("long", @LONG
һ���ľ�����ʯ��·��һͷͨ�������һͷͨ�����֣�·�Է��ż�
�軨�ܣ����žջ���Ǿޱ�ȣ�ɷ���������������ں�ɽ�������ǻ�
�����Ӳݴ�������Ⱥ������û��
LONG
	);
	set("outdoors", "������");
	set("exits", ([
		"northup" : __DIR__"houshan",
		"west" : __DIR__"caoping",
		
	]));
	set("objects", ([
		//CLASS_D("shenlong")+"/zhong" : 1,
	]));
	setup();
	replace_program(ROOM);
}

