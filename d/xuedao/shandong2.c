// shandong2.c
// Modified by Java Apr.27 1998
//�趨ΪѪ�������

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short",WHT"����"NOR);
        set("long",@LONG
ɽ�����ѩ��£�ɼ���ѩ�ѣ�����ʱ������ɨ����ѩ����ǰ�����
��������ԼԼ��һ��ɽ����
LONG );
        set("exits",([
                "enter" : __DIR__"shandong3",
                "west"  : __DIR__"sroad9",
        ]));
       set("objects", ([
                "/kungfu/class/xuedao/shengxiong" :1,
        ]));
        set("outdoors", "xuedao");
		set("valid_startroom", 1);

       
		setup();
       replace_program(ROOM); 
}

int valid_leave(object me, string dir)
{
	mapping fam;
	fam = (mapping)me->query("family");

	if (fam
		&&fam["family_name"] != "Ѫ����"
		&& dir == "enter"
		&& objectp(present("sheng xiong", environment(me))))
	    return notify_fail(CYN"ʤ��һ����ס�㣬˵����������Ѫ���ŵĵ��̣���Ҫ�����Ҵ���\n"NOR);
	  return ::valid_leave(me, dir);
}/**/

