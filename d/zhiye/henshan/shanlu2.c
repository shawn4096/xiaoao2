inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣
LONG );
        set("exits", ([ 
               "southeast"  : __DIR__"shanlu1",
               "northup"    : __DIR__"chidifeng",
        ]));

        set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

    //    set("coor/x", -10);
//	set("coor/y", 0);
	//set("coor/z", 10);
	setup();
        //replace_program(ROOM);
}

