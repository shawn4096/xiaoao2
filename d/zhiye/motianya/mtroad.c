// mtroad.c  ɽ·

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIG"����ɽ·"NOR);
        set("long", @LONG
����һ��ɽ·������������������������ľ����һ��Ů�����������ϱ߷�
�����ϱ߾���Ħ�����ˣ�һ����ɭ�ֲ���������֮�������㲻������
�Լ������ǿ��߰ɡ�
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "south" : __DIR__"mtyadi",
            "east"  : __DIR__"mtroad1",
        ]));
        set("objects",([
            __DIR__"npc/dingdang" : 1,
        ]));
        setup();       
}
