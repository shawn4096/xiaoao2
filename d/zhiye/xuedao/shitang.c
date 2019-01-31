// nroad6.c
// Modified by Java Apr.27 1998

#include <ansi.h>
inherit ROOM;
int do_dringk(string arg);
void create()
{
        set("short","ʳ��");
        set("long",@LONG
�˴���Ѫ����ɽ��������򣬴˴��ڷ��˹���ư�裬������һ��
����̨����һ�����ֵĺ����������ڷ���������еĳ��ˣ���������
����ڷ���һ���ŵ����ΰ�ʡ�
LONG );
        set("exits",([
                "south"   : __DIR__"cave",
                "north" : __DIR__"kengdao1",
        ]));
        set("objects",([
                __DIR__"obj/maoniurou" : 1,
				__DIR__"obj/niurou" : 1,
				__DIR__"obj/suyoucha" : 1,
				"d/xuedao/npc/food_lama" : 1,
        ]));
        setup();
        replace_program(ROOM);
}


void init()
{
	add_action("do_drink", "drink");
}
int do_drink(string arg)
{
	int current_water, max_water;
	object me;

	me = this_player();
        current_water = me->query("water");
	max_water = me->query("str")*10 + 100;

        if (current_water<max_water) {
		me->set("water", current_water+30);
		message("vision", me->name()+"�ò��״Ӳ�Ͱ��Ҩ��һ�ڲ�ˮ���ȡ�\n", environment(me), ({me}) );
		write("��Ҩ��һ��Ͱ�еĲ�ˮ���ȡ�\n");
        }
	else
	write("����Ҳ�Ȳ����ˡ�\n");
        return 1;
}
