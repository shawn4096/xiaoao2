inherit ROOM;
#include <ansi.h>
void create()
{
       set("short", "��·");	
        set("long", @LONG
������һ����������Ļ���·�ϣ�����������ɭɭ�����֡�����
��ͨ�����ݣ����Ͼͽ�����ϵؽ��ˡ�
LONG );
 
       set("outdoors", "��ɽ");
   
      set("exits", ([
		//"northdown" : "/d/wudang/wdroad4",	
                "southeast" : __DIR__"hsroad2",

	]));

	//set("coor/x", 20);
	//set("coor/y", -90);
	//set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}
