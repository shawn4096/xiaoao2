inherit ROOM;

void create()
{
	set("short", "�ӻ���");
        set("long", @LONG
����һ��СС���ӻ��̣�ƽʱ����Щ�ճ���Ʒ��ֻ�������Ϸ���
��ʽ�����Ļ���ϰ���æ���к����ˣ����Ŵ�����һ������(zhaop
ai)������д��Щ��С�֡�
LONG );
	set("item_desc", ([
		"zhaopai": "���� \"list\" �г������\"buy\" ���ϰ幺�\n",
	]));
	set("exits", ([
		"south"    : __DIR__"hengyang2",
	]));
	set("objects", ([
		__DIR__"npc/qiang": 1,
	]));

	//set("coor/x", 10);
	//set("coor/y", -100);
	//set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}

