inherit ROOM;

void create()
{
        set("short", "��ɽС·");
        set("long", @LONG
�����Ǻ�ɽ�ϵ�С·������С·�������˹������޳���
�ģ�Ҳ��ֻ����ǰ�Ĳ�ҩ�˲ȶ��ˣ��ֳ�����һ��С·����
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "west" : __DIR__"xiaolu2",
				"east" : __DIR__"pingdi",
                "enter" : __DIR__"shandong",
				"south" : __DIR__"huajing1",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
