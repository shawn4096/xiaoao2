#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
�������������������׵�֮�á����ṹΪ����Ъɽ������
���߲������������ʮ���ߣ������߼䣬��ʯ����ʮ��������������
ʮ����֮������������ʥ�۱���ׯ�ϡ�������֮��Ϊ��ɽС�ľ�֮һ��
 
LONG );
        set("exits", ([
                "south"  : __DIR__"yushulou",
                "north"  : __DIR__"houdian",
        ]));

        set("objects", ([
                __DIR__"npc/xiangke"  : 1,
                __DIR__"npc/youke"    : 1,
        ]));    

       //set("no_clean_up", 0);

       // set("coor/x", 0);
	//set("coor/y", -40);
	//set("coor/z", 0);
	setup();
       // replace_program(ROOM);
}

