// �÷���
// caifengpu1.c
// augx@sj 10/9/2001

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short",HIC"�÷���"NOR);
	set("long",
"���Ǽ�װ諺����Ĳ÷��̣������ﵽ�������˸ո����õ��·���ñ�ӡ�Ь
�ӵȵ��������Ҳ÷��̵����ﳤ���ǣ���ٹ������ﲻ����ʮ������������
�ǻ������źܴ�Ĳ÷�������������Ĳ÷��������ӱ�æµ�š�
");

	set("objects",([
		"/clone/zhiye/npc/caifeng" : 1,
		"/clone/zhiye/caifengzhuo" : 1,
	]));

	
	set("exits",([
		"east" : __DIR__"northjie2",
	]));
	
	set("indoors", "������");
	set("incity",1);
	set("no_fight", 1);
	setup();
}