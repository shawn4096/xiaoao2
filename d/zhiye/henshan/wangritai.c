inherit ROOM;

void create()
{
        set("short", "����̨");
        set("long", @LONG
����̨����ף�ڵ����ҹ�𣬵�̨������ң�����ţ���ˮ�Գ࣬
ٿ����ʣ����ֵ�����������������֮��ӿ���𣬹�ҫ��Ŀ��
LONG );
        set("exits", ([
                "southdown"  : __DIR__"shiziyan",
                "northup"    : __DIR__"zhurongdian",
        ]));

        set("objects", ([
                __DIR__"npc/youke"    : 2,
        ]));    

        set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

       // set("coor/x", -40);
	//set("coor/y", 90);
	//set("coor/z", 30);
	setup();
      //  replace_program(ROOM);
}

