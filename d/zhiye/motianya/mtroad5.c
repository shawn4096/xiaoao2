inherit ROOM;
#include <ansi.h>
int do_climb(string arg);

void create()
{
        set("short",YEL "Ħ���°�ɽ�ͱ�"NOR);
        set("long", @TEXT
������Ħ���µİ�ɽ�ͱڣ���̧ͷ���˿��������ֱ��ɽ��(lian)�����˿�����
�㻷�����ܣ����������ͱڣ��ƺ�ֻ��һֱ������(climb)�ˡ�
TEXT );
        set("outdoors", "motianya");
        set("exits", ([
               
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
        n = me->query_skill("dodge", 1)/10;
        message_vision(HIC"$N������һ����������������������������\n"NOR, me);
        if (random(n)*2 > n)
        {
                message_vision(HIY"$N���˰��죬����������ȥ��$N���˵�"
                               "Ĩ��Ĩ����\n"NOR, me);
                me->receive_damage("jingli", 500);
                me->move(__DIR__"mtdating");
                me->start_busy(3);
        } else
        {
                message_vision(HIW"$N����һ�ᣬһ��С��ˤ��������\n"NOR, me);
                me->receive_damage("qi", 2500 +random(2500));
                me->receive_wound("qi", 2500);
                me->move(__DIR__"mtyadi");  
                me->start_busy(3);
        }

        return 1;
}

