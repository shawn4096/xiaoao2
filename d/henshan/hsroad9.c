inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "����ɽ��");
        set("long", @LONG
�����������һ��ɽ�ڡ����������ϵĴ����ɽ�������Ǻ��ϵ�
�ؽ硣���Ϲ㶫������ʢ�����к���֮ʿ��
LONG );
         set("outdoors", "��ɽ");

        set("exits", ([
                "northdown" : __DIR__"hsroad5",
                "southeast" : "/d/foshan/xiaolu3",
        ]));
 //       set("coor/x", -40);
//	set("coor/y", -120);
//	set("coor/z", 10);
	setup();
       //replace_program(ROOM);
}
