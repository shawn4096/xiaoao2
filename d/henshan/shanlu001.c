inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣һֱ������ͨ��ĥ��̨�������塣 
LONG );
        set("exits", ([ 
               "east"       : __DIR__"shanlu002",
               "west"       : __DIR__"shanlu5",         
        ]));

        set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

      //  set("coor/x", -40);
	//set("coor/y", 50);
	//set("coor/z", 20);
	setup();
      //  replace_program(ROOM);
}

