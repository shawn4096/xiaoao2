// nroad6.c
// Modified by Java Apr.27 1998

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","��Ϣ��");
        set("long",@LONG
���Ŵ�����������ǽ�ǣ��İ��ĵƹ��£���λ����������Ϣ
�������˲������Σ��������ס�����һ�Ŵ��Ͼ�Ȼ��һλ��������
��Ů�����ڽ�Ц�ź�һλ����˵��ʲô����������������
LONG );
        set("exits",([
                "east"   : __DIR__"cave",
                //"southup" : __DIR__"nroad5",
        ]));
        set("objects",([
             /*  "/clone/weapon/miandao" : 1,
				
				"/clone/weapon/xinyuedao" : 1,*/
				//"/clone/weapon/blade" : 1,

        ]));
        //	set("no_clean_up", 0);
        set("sleep_room", 1);
        set("no_fight", 1);
		setup();
        replace_program(ROOM);
}

