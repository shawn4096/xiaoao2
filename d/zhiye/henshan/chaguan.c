inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "�������");
        set("long", @LONG
��һ���������ŵ�һ�ɲ���������Ƣ������Ϊ֮һˬ�����Ű���
��һ���ſ������������˿��ˣ������̸Ц����ͷ�Ӷ�����Ҫ���
�������ƹʺ�ҥ�ԣ������Ǹ������ڡ�
LONG );
	set("resource/water", 1);

	set("exits", ([
	       "north" : __DIR__"hengyang",
	]));

	set("objects", ([
		__DIR__"npc/chaboshi" : 1,
	]));

	//set("coor/x", 0);
	//set("coor/y", -120);
	//set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}

