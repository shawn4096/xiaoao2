// mtroad1.c  ����

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIG"�������"NOR);
        set("long", @LONG
������Ħ���¸����ĸ�����ޣ���ɳ�Ѿ�ͣϢ�ˣ����޸�����΢�紵������˿˿���⡣
�㷢��ԭ�����޸����������þ������ߵ�ɳʯС������������ƺ��л�ȥ�Ľݾ���
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "east"  : "/d/changan/northroad10", //���ӳ���
            "west"  : __DIR__"mtroad",
            
        ]));
        setup();       
}
