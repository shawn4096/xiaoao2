inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "�ؾ���");
        set("long", @LONG
�ؾ������������£���Ϊ����̫����������ؾ���������ֻ��
�����ľ���죬����Ʈ���滨��ݣ����������ɫ���������ؾ�
��֮�㡹�Ǻ�ɽ���ľ�֮һ��
LONG );
        set("exits", ([
               "east"   : __DIR__"shanlu14",
               "south"  : __DIR__"shuzhuangtai",
        ]));

        //set("no_clean_up", 0);

     //   set("coor/x", -70);
	//set("coor/y", 80);
	//set("coor/z", 20);
	setup();
        //replace_program(ROOM);
}

