inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "�ּ���");
        set("long", @LONG
������һ���ּ����������Ǻ��Ͼ��ڡ��ϱ�ͨ�������һ��ɽ
�ڡ�·���������Կ���һ�ǳ�ǽ��������һ���Ͷ�ɽ�֡�
LONG );
        set("outdoors", "��ɽ");

        set("exits", ([
                //"west"     : "/d/motianya/mtroad1",
                "east"     : __DIR__"hsroad4",
                //"north"    : __DIR__"hsroad6",
                "southup"  : __DIR__"hsroad9",
        ]));

 //       set("coor/x", -40);
//	set("coor/y", -110);
//	set("coor/z", 0);
	setup();
  //      replace_program(ROOM);
}
