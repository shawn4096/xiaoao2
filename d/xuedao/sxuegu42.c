// xuegu.c 
// sohu 
inherit ROOM;
#include "sxuegu.h"

void create()
{
	set("short", HIC"��ѩ��"NOR);
	set("long", @LONG
����һ������ѩ���У�����ȫ�ǰ�ѩ������ģ��������������
�κ�������Ҳ�������κ��ˣ������һ�㶼����ͨ����������о���
�����ơ�
LONG);
	set("exits", ([
		//"up" : __DIR__"xuegu1",
		//"down" : __DIR__"sxuegu20",
	]));
	set("xueceng", 4);

	set("outdoors", "Ѫ����");

   setup();
}


