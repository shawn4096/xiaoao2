inherit ROOM;

void create()
{
        set("short", "��Ӧ��");
        set("long", @LONG
�����ǵط���ӭ�Ӿ�ʦ��ʷ�����������ĵط����������������
�����ˡ����ϵ���Ҳ�Ͼ�ϸЩ�����ʵ���ʱʱ���¡�
LONG );
        set("exits", ([ 
               "south"  : __DIR__"yubeiting",
               "north"  : __DIR__"yushulou",
        ]));

         set("outdoors", "��ɽ");

        //set("no_clean_up", 0);

      //  set("coor/x", 0);
	//set("coor/y", -60);
	//set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

