// cf.c
// ����
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@long
�����������̽��ڳԷ���ˮ�ĵط�����̨�Ϸ��Ų��ٰ��ӡ��ƴ���
long);
	set("exits",([
		"west" : __DIR__"th",
	]));
	set("objects",([
		__DIR__"npc/chuzi" : 1,
		__DIR__"obj/shegeng" : 4,
		FOOD_D("baozi") : 3,
		FOOD_D("jiudai") : 3,
	]));
	set("resource/water",1);
	setup();
}

