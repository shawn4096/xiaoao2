inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣�����������������ˣ��߸ߴ������������ľ�
�Ǻ�ɽ���֮һ��ܽ�ط塣
LONG );
        set("exits", ([ 
                "northeast"  : __DIR__"nantian",
                "southeast"  : __DIR__"shanlu5",
                "northwest"  : __DIR__"furongfeng",
        ]));

         set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

     //   set("coor/x", -60);
	//set("coor/y", 60);
	//set("coor/z", 20);
	setup();
      //  replace_program(ROOM);
}

