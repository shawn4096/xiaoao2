#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��ɳ̶");
        set("long", @LONG
��ɳ̶�ֳƺ���̶������ף�ˮɫ�Ժڣ��ٲ�������ˮ�к���
����ĭ���࣬���Ŀɲ���ʯ���ϡ��������С����־���Ϊ���λ�����
٥�������ݽ����壬һ��������
LONG );
        set("exits", ([ 
               "up"  : __DIR__"shanjian",
        ]));

         set("outdoors", "��ɽ");

        //set("no_clean_up", 0);
       // set("coor/x", -100);
	//set("coor/y", 30);
	//set("coor/z", -10);
	setup();
}

int valid_leave(object me, string dir)
{
    if ((random((int)me->query_skill("dodge")) <= 30) && dir=="up")    
    {
        return notify_fail("��ʹ����һ�ģ����ٲ�����������Զ�͵���������ˤ�ı������ס�\n");
    }
    if ((random((int)me->query_skill("dodge")) <= 35) && dir=="up")    
    {
        return notify_fail("�����һԾ��ȴ���ٲ�������һ�ɶ�Զ�������ǰ׷�������\n");
    }
    if ((random((int)me->query_skill("dodge")) <= 40) && dir=="up")    
    {
        return notify_fail("������������ٲ���ֻ��һ����ˣ��ټӰѾ���\n");
    }

    return ::valid_leave(me, dir);
}

