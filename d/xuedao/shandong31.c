// nroad6.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","������");
        set("long",@LONG
����һ��Ѫ���ŵ�˽�б����⣬�Ա�һ���еĻ�����
�ڷ��˺ܶ��������������Ҫ���Ե�Ϊ����
LONG );
        set("exits",([
                "west"   : __DIR__"shandong3",
                //"southup" : __DIR__"nroad5",
        ]));
        set("objects",([
                "/clone/weapon/miandao" : 2,
				"/clone/weapon/mudao" : 1,
				"/clone/weapon/xinyuedao" : 2,

        ]));
        //	set("no_clean_up", 0);
       // set("outdoors", "xuedao");
        setup();
       //        replace_program(ROOM);
}

