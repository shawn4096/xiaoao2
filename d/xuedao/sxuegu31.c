// xuegu.c 
// sohu 
inherit ROOM;
#include "sxuegu.h"

void create()
{
	set("short", CYN"��ѩ��"NOR);
	set("long", @LONG
����һ��Ϻ��ѩ�У�����ȫ�ǰ�ѩ��������Щ�ް���������
�����κ�������Ҳ�������κ��ˣ����������ͨ����������о���
Щ���ơ�
LONG);
	set("exits", ([
		//"up" : __DIR__"xuegu1",
		//"down" : __DIR__"sxuegu20",
	]));
	set("xueceng", 3);

	set("outdoors", "Ѫ����");

   setup();

}

