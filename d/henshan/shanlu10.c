inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣ɽ·��������ͨ�򷽹��¡������������塣
LONG );
        set("exits", ([ 
                "eastup"    : __DIR__"tianzhu",
                "westdown"  : __DIR__"fangguangsi",
        ]));

        set("objects", ([
                __DIR__"npc/xiangke" : 2,
                __DIR__"npc/youke"    : 3,
        ]));         

         set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

       // set("coor/x", -90);
	//set("coor/y", 40);
	//set("coor/z", 20);
	setup();
        //replace_program(ROOM);
}

