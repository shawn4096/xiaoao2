#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ϻ�ɽ���֮һ�������壬����Ⱥɽ��������У�ÿÿ����
��ʪʱ������������������������ˡ���ɽ�ɾ�ѧ�����������Ǵ�
����������ġ�
LONG );
        set("exits", ([ 
                "westdown"   : __DIR__"shanlu10",
                "eastdown"   : __DIR__"shanlu7",
        ]));
/*
        set("objects", ([
                CLASS_D("henshan") + "/lu" : 1,
        ]));    
*/
       //set("no_clean_up", 0);

   //     set("coor/x", -80);
//	set("coor/y", 40);
	//set("coor/z", 30);
	setup();
}

void init()
{       
        //add_action("do_think", "think");
}

int do_think(string arg)
{
        object here, me = this_player();
        int add;

        if (me->query("special_skill/clever"))
                add = me->query_int() * 4;
        else
                add = me->query_int() * 3;

        if (! living(me) || arg != "feng")
                return notify_fail("��Ҫ����ʲô��\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("��������æ���ء�\n");

        if ((int)me->query_skill("sword", 1) < 30)
                return notify_fail("��Ļ���������򲻹����޷���������������\n");

        if ((int)me->query_skill("tianzhu-jian", 1) > 120)
                return notify_fail("�㷢���Ѿ����ܴ�������������ߵ�����������\n");

        if ((int)me->query("jing") < 25)
                return notify_fail("�����ھ��񲻼ã�����ƣ�룬������Ϣ"
                                   "һ��ɡ�\n");

        me->receive_damage("jing", 20);

        if (me->can_improve_skill("tianzhu-jian"))
                me->improve_skill("tianzhu-jian", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "�۾�����Ĳ��������壬"
                       "��������\n" NOR, me);
        write(HIC "��ԡ����������������µ�����\n" NOR);
        return 1;
}
