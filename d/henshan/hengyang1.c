inherit ROOM;
//#include <ansi.h>
void create()
{
	set("short", "��������");
        set("long", @LONG
��������ʯ�̾͵���С�ֵ��ϡ�ֻ������ʱ�����˳ֽ����У���
���������ɶ���ˡ��ϱ���һ��С�꣬����һ������Ρ�룬���ܵ��ߣ�
 �ſڲʵƸ������ܼҼҶ��������������ˡ�
LONG );
               set("outdoors", "��ɽ");
	set("exits", ([
	       "east"   : __DIR__"hengyang",
	       "west"   : __DIR__"hengyang11",
	       "south"  : __DIR__"shop",
	       "north"  : __DIR__"liufugate",
	]));

        //set("no_clean_up", 0);

	//set("coor/x", -10);
	//set("coor/y", -110);
	//set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}

