// ֯����
// zhibufang1.c
// augx@sj 19/9/2001

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short",HIY"֯����"NOR);
	set("long",
"���Ǽ䵽�����������ķ��䣬��֯Ů���������ŵ�������æµ�š�����
������������֯����������������֯Ů������ϸ����ָ���ŷ����ڱ�֯����
æµ����ӰҲ���������������������������ƥ���ͱ�֯�Լ��Ĳ�ƥ��
"); 

	set("objects",([
		"/clone/zhiye/npc/fangzhi-nu" : 1,
	]));
	
	set("exits",([
		"west" : __DIR__"northjie2",
	]));
	
	set("indoors", "������");
	set("incity",1);
	set("no_fight", 1);
	setup();
}
