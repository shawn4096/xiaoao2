//caodi.c �ݵ� 

#include <ansi.h>
#include <room.h>

inherit ROOM;
void create()
{
	set("short",HIG"�ݵ�"NOR);
	set("long", @LONG
һƬ�����ĵĲ�ƺ�����ɵ������ˣ��޴���Ϊ���軺��Ũ�̿���������
�������������������ɫһ���£����Ӳ��������أ�����Զ�����ഺ����ӽ
�����졣
LONG
	);

	set("exits", ([
		"west" : __DIR__"huilang2",
		"southeast" : __DIR__"shulin8",
		"northeast" : __DIR__"shulin10",
		"east" : __DIR__"shulin9",
	]));
        
	set("outdoors", "�Խ�ɽׯ");
	setup();
}

#include "sjsz_room.h";