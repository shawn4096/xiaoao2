inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣ɽ·ת��ܽ�ط壬����ԶԶ�����ؾ��󣬶���
����ͨ�������š�
LONG );
        set("exits", ([ 
               "west"       : __DIR__"cangjingdian",
               "southeast"  : __DIR__"nantian",
        ]));

         set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

       // set("coor/x", -60);
	//set("coor/y", 80);
	//set("coor/z", 20);
	setup();
       // replace_program(ROOM);
}

