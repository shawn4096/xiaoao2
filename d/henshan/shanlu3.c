inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣����һ������ǰ�ɽͤ�ˡ�
LONG );
        set("exits", ([ 
               "southup"    : __DIR__"chidifeng",
               "northwest"  : __DIR__"shanlu4",
        ]));

         set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

       // set("coor/x", -10);
	//set("coor/y", 20);
	//set("coor/z", 10);
	setup();
       // replace_program(ROOM);
}
 
