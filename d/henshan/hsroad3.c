inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "��·");
        set("long", @LONG
������һ����������Ļ���·�ϣ�����������ɭɭ�����֡�����
��Զ���Ǻ����س��ˡ�
LONG );
         set("outdoors", "��ɽ");

        set("exits", ([
                "northeast": __DIR__"hsroad2",
                "west"     : __DIR__"hengyang2",
        ]));

  //      set("coor/x", 20);
	//set("coor/y", -110);
	//set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}
