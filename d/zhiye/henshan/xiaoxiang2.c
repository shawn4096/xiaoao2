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
	        "south"  : __DIR__"baihuzhai",
	        "north"  : __DIR__"xiaoxiang1",
	]));

	//set("coor/x", 10);
	//set("coor/y", -130);
	//set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}

