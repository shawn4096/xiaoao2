inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "��ɽͤ");
        set("long", @LONG
���ڵ��˰�ɽͤ�������뵽ף�ڷ����۸̻߳����г̣���ǡ����
һ��֮����·��Сͤ��Ȼ�Ѽ��žã�����Ϊ���������ڷ���ꡣ
LONG );

        set("exits", ([
               "southdown"  : __DIR__"shanlu4",
               "northwest"    : __DIR__"shanlu002",
        ]));

        //set("no_clean_up", 0);
        set("outdoors", "��ɽ");

       // set("coor/x", -20);
	//set("coor/y", 40);
	//set("coor/z", 20);
	setup();
       // replace_program(ROOM);
}

