inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
��������������ĵ�һ���ţ��ɺ����񣬻���ʯ��͵�ʯ�Ʒ���
������ɽ��ף����Ϣ֮�أ����̷�Ϊ����С���졣�ڴ�Զ����ɽ��ɽ
����ɣ�����������յĴ���
LONG );
        set("exits", ([
                "north"  : __DIR__"kuixingge",
                "south"  : __DIR__"hengyang",
        ]));

        set("outdoors", "��ɽ");

        //set("no_clean_up", 0);

        //set("coor/x", 0);
	//set("coor/y", -100);
	//set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

