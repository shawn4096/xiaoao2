inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "��·");
        set("long", @LONG
������һ����������Ļ���·�ϣ�����������ɭɭ�����֡�
LONG );

         set("outdoors", "��ɽ");

        set("exits", ([
                //"northwest" : __DIR__"hsroad1",  //������ȥ�䵱�ˣ���ͼ��ֲ���
                "southwest" : __DIR__"hsroad3",
                "southeast" : "/d/fuzhou/wroad4",
        ]));

       // set("coor/x", 30);
	//set("coor/y", -100);
	//set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}
