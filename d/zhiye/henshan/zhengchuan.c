inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����������������ĵ�������Ժ�����������ڵ��ʥ�����
���¥�
LONG );
        set("exits", ([ 
               "south"  : __DIR__"kuixingge",
               "north"  : __DIR__"yubeiting",
        ]));

              set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

        //set("coor/x", 0);
	//set("coor/y", -80);
	//set("coor/z", 0);
	setup();
     //   replace_program(ROOM);
}

