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
		"west" : __DIR__"shulin4",
		"southwest" : __DIR__"shulin3",
		"northwest" : __DIR__"shulin5",
		"east" : __DIR__"huilang3",
	]));
        
	set("outdoors", "�Խ�ɽׯ");
	setup();
}

#include "sjsz_room.h";