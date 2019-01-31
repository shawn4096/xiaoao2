#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ʯ�޷�");
        set("long", @LONG
ܽ�ط��Ǻ�ɽ���֮һ��ÿ�������ʱ����ˮ���ڷ��е���ʯ
�ϣ������޴�Ļ���������������������Ժ�еĶ����������Ը÷���
�˶�������ɽ�ɵ�ʯ�޽���Ҳ�ɴ˶���
LONG );

        set("exits", ([
                "westdown"   : __DIR__"liuyunping",
        ]));

        set("objects", ([
		__DIR__"npc/dizi1" : 2,
        ]));

       //set("no_clean_up", 0);

      //  set("coor/x", -30);
	//set("coor/y", 70);
	//set("coor/z", 40);
	setup();
}

void init()
{       
        add_action("do_think", "think");
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
                return notify_fail("��Ļ���������򲻹����޷�����ʯ�޽�����\n");

        if ((int)me->query_skill("shilin-jian", 1) > 120)
                return notify_fail("�㷢���Ѿ����ܴ�������������ߵ�ʯ�޽�����\n");

        if ((int)me->query("jing") < 25)
                return notify_fail("�����ھ��񲻼ã�����ƣ�룬������Ϣ"
                                   "һ��ɡ�\n");

        me->receive_damage("jing", 20);

        if (me->can_improve_skill("shilin-jian"))
                me->improve_skill("shilin-jian", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "�۾�����Ĳ���ʯ�޷壬"
                       "��������\n" NOR, me);
        write(HIC "��ԡ�ʯ�޽����������µ�����\n" NOR);
        return 1;
}
