// Room: /d/wizard/shandong.c
#include <ansi.h>
inherit ROOM; //�̳� ROOM ��
void create()
{
	set("short", HIB"ɽ��"NOR); 
	set("long", @LONG
�˴����±ڱ����ɽ����͸���±���һ˿˿�������˽������˵ؿռ䲻�󵫿���
��Ϊ���£���ûͷû�Եĵ���˴���������΢��Ӧ�˴˴������Ĺ���̧ͷһ��������
�ڰ���о�ȻƮ��һ���ˣ�
LONG );
	set("exits", ([
		//"south" : __DIR__"midao3",
		"out" : __DIR__"yabiqian",
		//"west" : __DIR__"midao2",
		//"north" : __DIR__"midao1",
	]));
	set("no_fight",1);
	set("objects", (["/d/xiaoyao/leigushan/npc/wuyazi" : 1 ]) );
	setup();
	replace_program(ROOM);
}

int init()
{
	object me=this_player();	
		message_vision(HIC"һ�����ϵ������ڰ���һ����̾��\n$N����һ�������ȵ�����˭����\n"NOR,me);		
}