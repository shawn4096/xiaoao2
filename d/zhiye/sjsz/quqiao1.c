//quqiao.c ����

#include <ansi.h>
#include <room.h>

inherit ROOM;
void create()
{
	set("short",HIY"����"NOR);
	set("long", @LONG
һ��С�ɾ��Ƶ����ź���ڳ����ϣ�������������һ��Ϊ�����������ˮ
�����峺�����渡��Щʢ����˯����͸��˯���ķ�϶��Լ�ɼ���β��ɫ������
ˮ�����еػ����ζ���Զ����ǽ���µ�һ�԰Ž������Ļ��俪�������֣���
�������ĳ�����������������
LONG
	);

	set("exits", ([
		"west" : __DIR__"huilang3",
		"southeast" : __DIR__"quqiao2",
		"east" : __DIR__"jiashan",
		"northeast" : __DIR__"quqiao4",
	]));
        
	set("outdoors", "�Խ�ɽׯ");
	setup();
}

#include "sjsz_room.h";