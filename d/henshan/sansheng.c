inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�������Ǹ����¿�ɽ��ʦ��˼��Ǵ�����˵��˼��ʦ����������
������ʳ�����������Զ���п����ӣ���˵���ܽ��ڻ�˼��ʦ����
��ǧ�꣬��ͤͤ���ǣ�������ԡ�
LONG );
        set("exits", ([ 
               "southup"   : __DIR__"jigaoming",
               "northdown"     : __DIR__"shanlu8",
               "eastdown"  : __DIR__"fuyansi",
        ]));

        set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

  //      set("coor/x", -60);
//	set("coor/y", 20);
	//set("coor/z", 10);
	setup();
        //replace_program(ROOM);
}

