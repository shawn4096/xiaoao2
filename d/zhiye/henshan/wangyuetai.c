#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "����̨");
        set("long", @LONG
����̨��ף�ڵ��һ���ʾ�ʯ��ÿ��ҹ������µ��գ���������
���֣�����������ԣ�������ɫ����ӳ�Ͱ���Ⱥ�塣��ʱ��Ȼ���
����ʮ���壬����������У�ʼ���·��޴���Ҳ��ǰ�������ʫ����
�˼������ѽԾ����˵������δ�͡�
LONG );
        set("exits", ([
               "southup"    : __DIR__"zhurongdian",
               //"up"    : "/d/reborn/jitan3",
        ]));

        set("objects", ([
                __DIR__"npc/youke"    : 3,
        ]));    

         set("outdoors", "��ɽ");

        //set("no_clean_up", 0);

      //  set("coor/x", -40);
	//set("coor/y", 110);
	//set("coor/z", 30);
	setup();
}


