inherit ROOM;

void create()
{
	set("short", "С��");
        set("long", @LONG
���Ǻ�������һ��ƫƧ��С�ƽʱ������������ֻ������С��
����������֪��ͨ��δ���
LONG );
               set("outdoors", "��ɽ");

	set("exits", ([
	        "south"  : __DIR__"xiaoxiang2",
	        "north"  : __DIR__"hengyang2",
	]));

	//set("coor/x", 10);
	//set("coor/y", -120);
	//set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}

