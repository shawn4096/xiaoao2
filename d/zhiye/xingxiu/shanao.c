//shanao.c ɽ�꣬Ϊ׽���Ϻ�ϴ��Ȫ��׼��

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
����λ����ɽ��ɽ���Ѿ���Ͽ���������һƬ��ѩ���ǣ����Ϊһ��
С�͵���Ȫ���������ڣ������ɾ����Ҳ࿿��ɽ��һ����һ����ɭɭ��С��
����(cave)����ɭ�ֲ���
LONG
        );
        set("exits", ([
          "southeast" : __DIR__"tsroad3",
          //"northwest" : __DIR__"tsroad2",
			"west" : __DIR__"wenquan",
        ]));

        set("outdoors", "tianshan");

        set("coor/x",-10);
		set("coor/y",50);
		set("coor/z",0);
		setup();
}
void init()
{
	object me=this_player();
	add_action("do_enter","enter");
	me->receive_damage("qi",300,"��������");
	me->receive_wound("qi",100,"��������");
}
int do_enter(string arg)
{
	object me=this_player();
	if (!arg||(arg!="cave"&&arg!="����"))
	{
		return notify_fail("�㵽�����꣬��Ϊ�Լ���������ô��\n");
	}
	message_vision(HIC"$Nһ���������С������ȥ��һ�ɺ����������̲�ס���˸����䡣\n"NOR,me);
	me->receive_damage("qi",50,"��������");
	me->receive_wound("qi",300,"��������");
	me->move("/d/xingxiu/bingdong");
	return 1;
}