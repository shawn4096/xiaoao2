inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣�����Ѿ���������ף�ڷ��ˡ� 
LONG );
        set("exits", ([ 
                "eastdown" : __DIR__"shanlu003",
                "westup"   : __DIR__"zhurongfeng",         
        ]));

        set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

     //   set("coor/x", -60);
	//set("coor/y", 100);
	//set("coor/z", 60);
	setup();
       // replace_program(ROOM);
}

