inherit ROOM;

void create()
{
        set("short", "ĥ��̨");
        set("long", @LONG
ĥ��̨λ���������£����ɽͤһ�����ڡ�̨ǰ���·ת��̨��
���ɲԴ䣬�������ġ��ഫ�������ڻ����ڴ���������š�����
̨��ɮ����������ĥ�����Ƿ����ڵ�һ����̨�����������ĥ��̨֮
�ġ��Ǻ�ɽ���ľ�֮һ��
LONG );
        set("exits", ([
                "southdown"  : __DIR__"shanlu8",
                "westup"     : __DIR__"shanlu7",
                "northup"    : __DIR__"shanlu6",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 2,
        ]));               
 
              set("outdoors", "��ɽ");

       //set("no_clean_up", 0);

      //  set("coor/x", -60);
	//set("coor/y", 40);
	//set("coor/z", 10);
	setup();
      //  replace_program(ROOM);
}
