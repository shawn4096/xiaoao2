inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "�Ǹ�̨");
        set("long", @LONG
�����������ŵǸ���Զ�ĺ�ȥ������վ�����������壬����
�����衣ң���潭��ȥ������ű���ʱ��ʱ�֡���Χ��ϼ�����ޣ���
�ǣ�������廷����������ǧ��
LONG );
        set("exits", ([
               "northwest"  : __DIR__"nantian",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 4,
        ]));

        set("outdoors", "��ɽ");

        //set("no_clean_up", 0);

       // set("coor/x", -40);
	//set("coor/y", 60);
	//set("coor/z", 20);
	setup();
      //  replace_program(ROOM);
}

