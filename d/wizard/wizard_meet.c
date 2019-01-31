// Room: /d/wizard/wizard_room.c

inherit ROOM;

void create()
{
	set("short", "��ʦ������");
	set("long", @LONG
�ڿ������Ĵ����������з���һ�ź�ľ��Բ������ʦͨ����������
����ͨ��һЩ��Ҫ������޸ĵ��᰸�����������԰��ܻ㣬�ϱ��Ͷ��ߵ�ͨ��
��ͨ��������̨�������ͨ��ͨ���Խ�ɽׯ�����ҡ�
LONG );
	set("exits", ([
		"west" : __DIR__"wizard_room",
		"tiandi" : "/d/xiangyang/leitai/lt",
		"fengyun" : "/d/xiangyang/leitai/lt1",
		"longhu" : "/d/xiangyang/leitai/lt2",
		"southdown" : "/d/foshan/dukou_tanbao",
		"down" : __DIR__"guest_room",
		"up" : "/d/sjsz/zongtai",
	]));
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("incity",1);
	setup();
	call_other("/clone/board/post_b", "???");
}

void init()
{
	object me = this_player();

	if (userp(me) && !wiz_level(me)) {
		me->move("/d/wizard/guest_room");
		message_vision("$N����ʦ��Ϣ�����ص�ˤ��������\n", me);
		me->unconcious();
	}
}
