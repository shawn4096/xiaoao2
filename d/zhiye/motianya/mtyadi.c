// mtyadi.c �µ�

inherit ROOM;
#include <ansi.h>
int do_climb(string arg);

void create()
{
        set("short",YEL "Ħ���µ�"NOR);
        set("long", @TEXT
�����ǰ��һ����ֱ��ɽ�壬����ǧ�ɣ��嶥����������Լ�ɼ���
ɽ���ͺͺ�ģ����������㴦��ɽ�崹��һ������(lian)����ϸһ����
���������⼣���ƺ�����������(climb)�����¡�
TEXT );
        set("outdoors", "motianya");
        set("exits", ([
                "north" : __DIR__"mtroad",
        ]));
        setup();
}

void init()
{
        add_action("do_climb","climb");
}

int do_climb(string arg)
{
        int n;
        object me;

        if (arg != "lian")
        {
                write("��Ҫ��ʲôѽ? \n");
                return 1;
        }

        me = this_player();
       // n = me->query_skill("dodge", 1) /10;
        n=me->query_dex();
		message_vision(HIC"$N������һ����������������������������\n"NOR, me);
        if (me->query("quest/������/������/givexieling"))
        {
           message_vision(HIC"$N�õ�Ħ���ʿл�̿͵�ָ�㣬������ɽ�Ʒǳ���Ϥ���������ݼ�͵����¶���\n"NOR, me);
		   me->move("d/motianya/mtdating");
		   return 1;
        }
		if (random(n) > 20&& me->query("neili")>500)
        {
                message_vision(HIY"$N���˰��죬����������ȥ��$N���˵�"
                               "Ĩ��Ĩ����\n"NOR, me);
                me->receive_damage("jingli", 300);
                me->start_busy(3);
				me->add("neili",-random(500));
                me->move(__DIR__"mtroad2");
        } else
        {
                message_vision(HIW"$N����һ�ᣬһ��С��ˤ��������\n"NOR, me);
                me->receive_damage("qi", 300 +random(300));
                me->receive_wound("qi", 300);
                me->start_busy(3);
        }

        return 1;
}
