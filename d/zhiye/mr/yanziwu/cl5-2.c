// /u/beyond/mr/cl5-2.c
// this is made by beyond
// update 1997.6.20
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
         set("short",HIW"����"NOR);
         set("long", @long
����һ�����ȣ����滭�Ž��������Ĺ��ʻ�����ɫ���������ɫ�������ߣ�
ʹ���㲻�ɵöԽ������������Ĵ��쾪̾���ѡ��ڳ������棬Ѿ�ߡ��Ҷ�����
����ȥ����æ���Լ������飬������һ�㵡������������������ի��
long);
	set("exits", ([
		"west" : __DIR__"shangyue",
		"north" : __DIR__"cl5-1",
	]));
	set("objects",([
		__DIR__"../npc/guanjia1" : 1,
	]));
	setup();
}