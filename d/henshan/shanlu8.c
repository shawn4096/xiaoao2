inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣�ϱ߾��Ǹ����¡�
LONG );
        set("exits", ([ 
               "southup"  : __DIR__"sansheng",
               "northup"  : __DIR__"mojingtai",
        ]));

        set("objects", ([
                __DIR__"npc/xiangke"  : 2,
                __DIR__"npc/youke"    : 3,
        ]));    

         set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

        //set("coor/x", -60);
	//set("coor/y", 30);
	//set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

