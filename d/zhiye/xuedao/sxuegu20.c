// xuegu.c 
// sohu 
inherit ROOM;
#include "sxuegu.h"

void create()
{
	set("short", HIW"ǳѩ��"NOR);
	set("long", @LONG
����һ���ǳ��ѩ�У�����ȫ�ǰ�ѩ����Ϊҫ�ۣ�����������
�κ�������Ҳ�������κ��ˣ����������ͨ������������΢��Щ��
�ơ������ְ��˰Ƿ����������������˵��ƺ���������������
LONG);
	set("exits", ([
		//"up" : __DIR__"xuegu1",
		//"down" : __DIR__"sxuegu20",
	]));
	set("xueceng", 2);
	set("zuan", 1);

	set("outdoors", "Ѫ����");

   setup();
}


