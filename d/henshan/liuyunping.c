inherit ROOM;

void create()
{
        set("short", "����ƺ");
        set("long", @LONG
ÿ���������ں�ɽ������������������ɽ����ӿ��������ɽ��
��ǰɽ��к��ֱ�����ӷ�к��εΪ׳�ۣ�����������ŵ������澰��
LONG );
        set("exits", ([ 
               "westdown"  : __DIR__"nantian",
               "eastup"    : __DIR__"shilinfeng",
        ]));

         set("outdoors", "��ɽ");

        //set("no_clean_up", 0);

      //  set("coor/x", -40);
	//set("coor/y", 70);
	//set("coor/z", 30);
	setup();
        //replace_program(ROOM);
}

