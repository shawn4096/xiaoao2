inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "�ּ���");
        set("long", @LONG
������һ���ּ����������������ѡ��������Ǻ������ڡ��ϱ�
�Ǳ���ϡ�
LONG );
         set("outdoors", "��ɽ");

        set("exits", ([
                "north"  : __DIR__"hsroad8",
                "south"  : __DIR__"hsroad6",
        ]));
       /* set("objects", ([
                "/clone/quarry/gou" : 1,
        ]));
*/
  //      set("coor/x", -40);
	//set("coor/y", -90);
	//set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

