inherit ROOM;

void create()
{
        set("short", "��ͤ");
        set("long", @LONG
��ͤ��������һ�ڣ��ؾ�ǧ�ÿ��ɽ�鱩����������飬����
ʾ�������Ŷ�ʮ���⡣ 
LONG );
        set("exits", ([
               "west"   : __DIR__"kuixingge",
        ]));

        //set("no_clean_up", 0);

       // set("coor/x", 10);
	//set("coor/y", -90);
	//set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

