// /u/jpei/guiyun/zoulang3.c
#include <ansi.h>
inherit ROOM;
int do_jump(string arg);
int story1(object me);
int story2(object me);
void create()
{
	set("short","����");
	set("long",@LONG
����������������������ȡ������������ۣ����������˻�����
LONG
);
	/*  set("object",([
	__DIR__"obj/luchenfen.c" :     1,
	]));  */
	set("exits",([
		"east" : __DIR__"zoulang2",
		"south" : __DIR__"houting",
        "north" : __DIR__"wofang1",
	]) );
	set("no_clean_up",0);
	set("outdoors", "����ׯ");
	setup();
}
void init()
{
	//�����ж�
	
	add_action("do_jump","jump");
	add_action("do_jump","tiao");
	//add_action("do_pull","move");
	//add_action("do_pull","yi");
}

int do_jump(string arg)
{
	object me = this_player();

	if (me->is_busy() || me->is_fighting())	return notify_fail("����æ���أ�\n");
	if (arg == "liang"||arg == "��") {
		if (me->query_skill("dodge",1)<350)
		{
		   message_vision("$N��Ծ�������Ṧ��������Ծ����֮�ʣ���ƮȻ��ء�\n", me);
		   return 1;
		}
		else {
		   message_vision(HIC"$N�����Ṧ������Ծ��Ծ��������������ȣ��ԽŹ����������ϣ������ݿ�ȥ��\n"NOR, me);
           message_vision(HIC"ֻ�����й������ˣ�����Ů�ӣ�һ��ʮ�˾������òŮ�����ڵ��¿��飬��ؾ�����λ�̴�С���ˡ�\n"
		   +" �������˶���Ѿ�ߴ�磬����ȴ��ִ���У���װ�������������ȣ������������ա�\n"
		   +"$Nԭ��Ҫ�����ˣ�ȴ���˼������б����ϵ��м����б��飬���˾���һ�����ķ����ݶ������µȺ�ֻ����һ�����֡�\n"NOR, me);
           me->move("/d/thd/guiyun/menliang");
		   me->set_temp("slbw/tiaoliang",1);
		   return 1;
		}
	}

}
