inherit ROOM;

void create()
{
        set("short", "���Ǹ�");
        set("long", @LONG
���Ǹ�����������ĵڶ�������Ϊһ������̨������Ϊ��ͤ����
����ͤ��������ڳ�Ϸ�������������ַǷ���
LONG );
        set("exits", ([
               "south"  : __DIR__"lingxingmen",
               "east"   : __DIR__"zhongting",
               "north"  : __DIR__"zhengchuan",
        ]));
              set("outdoors", "��ɽ");

        //set("no_clean_up", 0);

        //set("coor/x", 0);
	//set("coor/y", -90);
	//set("coor/z", 0);
	setup();
      //  replace_program(ROOM);
}

