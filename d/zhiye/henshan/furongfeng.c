#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ܽ�ط�");
        set("long", @LONG
ܽ�ط��Ǻ�ɽ���֮һ����˵ܽ�ط����и�ɽ�������г�����ܽ
�ػ������겻л��ܽ�ط�Ҳ��˵����������˴��������ģ���ľ���̣�
���ﲻ��ף�ڷ�ߣ���ů���ˣ�ʵ���Ǹ��˼��ɾ���
LONG );

        set("exits", ([
                "southeast"   : __DIR__"shanlu13",
        ]));

        set("objects", ([
                //"/npc/liu" : 1,
               // "/d/hmy/npc/qu" : 1,
        ]));    

        //set("no_clean_up", 0);

    // set("coor/x", -70);
	//set("coor/y", 70);
	//set("coor/z", 20);
	setup();
        //replace_program(ROOM);
}

