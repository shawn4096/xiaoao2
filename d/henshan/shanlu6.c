inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣�ϱ�ɽ·���� ĥ��̨ �� �����塣
LONG );
        set("exits", ([
                "southdown"  : __DIR__"mojingtai",
                "east"       : __DIR__"shanlu5",
	 	"west"       : __DIR__"shulin1",
        ]));

        set("objects", ([
                __DIR__"npc/xiangke"  : 4,
                __DIR__"npc/youke"    : 2,
        ]));    

         set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

        //set("coor/x", -60);
	//set("coor/y", 50);
	//set("coor/z", 20);
	setup();
       // replace_program(ROOM);
}

