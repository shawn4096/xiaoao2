// Room: /d/chengdu/beidajie2.c
// By Jpei

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
���ǳɶ��ı���֡�����ͨ�򱱳��ţ��ϱ��Եúܷ�æ��
LONG
	);
        set("outdoors", "�ɶ�");

	set("exits", ([
		"north" : __DIR__"beidajie3",
		"south" : __DIR__"beidajie1",
		"west"	: __DIR__"yaodian",
		"east"	: __DIR__"yaochang",
	]));
	
	set("objects",([
		"/clone/zhiye/npc/caiyao-ren" : 1,
	]));
	
	set("incity",1);
	setup();
}

