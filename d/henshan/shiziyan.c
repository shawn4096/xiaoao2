inherit ROOM;

void create()
{
        set("short", "ʨ����");
        set("long", @LONG
ʨ���Ҳ������ι�״����ʯ��ϸ�������ʨ�ӣ���Ծ���𣬸�Ф
���ࡣ��ʨ���ң�ף�ڷ��Ѿ������ˡ�
LONG );
        set("exits", ([ 
               "southwest"  : __DIR__"nantian",
               "northup"    : __DIR__"wangritai",
        ]));

         set("outdoors", "��ɽ");
       //set("no_clean_up", 0);

       // set("coor/x", -40);
	//set("coor/y", 80);
	//set("coor/z", 20);
	setup();
        //replace_program(ROOM);
}

