inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣
LONG );
        set("exits", ([ 
               "southdown"  : __DIR__"beimen",
               "northwest"  : __DIR__"shanlu2",
        ]));

        set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

       // set("coor/x", 0);
	//set("coor/y", -10);
	//set("coor/z", 10);
	setup();
        //replace_program(ROOM);
}

