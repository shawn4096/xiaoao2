// xuegu.c 
// sohu 
#include <ansi.h>

inherit ROOM;
#include "sxuegu.h"

void create()
{
	set("short", WHT"ǳѩ��"NOR);
	set("long", @LONG
����һ���ǳ��ѩ�У�����ȫ�ǰ�ѩ����Ϊҫ�ۣ�����������
�κ�������Ҳ�������κ��ˣ���ѩ��ϱ���͸���Ժã���Ȼ������
��ͨ�����Ǵ������ﲢ�����ơ�����ϸһ�����ִ˵��ƺ����������
LONG);
	set("exits", ([
		//"up" : __DIR__"xuegu1",
		//"down" : __DIR__"sxuegu20",
	]));
	set("xueceng", 1);
	set("zuan", 1);

	set("outdoors", "Ѫ����");

   setup();
}


