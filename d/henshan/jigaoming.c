#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������̨");
        set("long", @LONG
�����Ǹ�������ߴ����������������顸�����������������ڴˣ�
�⼴���༫��(���޼�����)����⼫��(����������)��������������
�ģ���Ի������̨��
LONG );
        set("exits", ([ 
               "northdown"  : __DIR__"sansheng",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 4,
        ]));    

        set("outdoors", "��ɽ");

        //set("no_clean_up", 0);

     //   set("coor/x", -60);
	//set("coor/y", 10);
	//set("coor/z", 20);
	setup();
      //  replace_program(ROOM);
}

