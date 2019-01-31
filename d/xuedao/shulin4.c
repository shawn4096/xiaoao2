// Room: /d/huashan/shulin2.c
// Date: Look 99/03/25
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", WHT"��ľ��"NOR);
        set("long", @LONG
����ǰ��Ȼһ�ڣ������У�ֻ������ǰ�󣬵�����������ǵصĹ�ľ�֡�
�Ͱ��Ĺ�ľ�ִ���һ�飬��ʵ����֦��һ�����ɡ�㸲����Ƭ�͹��ݵأ�����
˿�����⣬���������������߰Ѻ�Ļ�ѩ���ڵ��ϣ�һ�Ų���ȥ����ûϥ�ǡ�
���ƺ���ʧ�˷�����ûͷ��Ӭ�㵽���Ҵ���
LONG);

        set("exits", ([
                "east" : __DIR__"shulin3",
                "south" : __FILE__,
                "west" : __DIR__"shulin1",
                "north" : __FILE__,
        ]));

        set("outdoors", "xuedao");
        set("coor/x",40);
		set("coor/y",100);
		set("coor/z",0);
		setup();
}

void init()
{
       set("exits/east", __DIR__"shulin"+(1+random(4)));
       set("exits/south", __DIR__"shulin"+(1+random(4)));
       set("exits/north",  __DIR__"shulin"+(1+random(4)));
       set("exits/west",  __DIR__"shulin"+(1+random(4)));
}

