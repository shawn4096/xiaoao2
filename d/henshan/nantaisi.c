inherit ROOM;

void create()
{
        set("short", "��̨��");
        set("long", @LONG
��̨��Ϊ�������滳�õĵ���ʯͷϣǨ�ĵ������������Ʒ�����
ʯͷ����Ĺ����������е�������ͨ�ģ�Ȫ�����ˣ�����׷ɣ�ɽ��
����ʱ��ҶϤ�������ȥ����
LONG );
        set("exits", ([
                "northdown"  : __DIR__"shanlu9",
        ]));

        set("objects", ([
                __DIR__"npc/xiangke" : 4,
        ]));                    

               set("outdoors", "��ɽ");
       //set("no_clean_up", 0);

       // set("coor/x", -50);
	//set("coor/y", 0);
	//set("coor/z", 0);
	setup();
      //  replace_program(ROOM);
}

