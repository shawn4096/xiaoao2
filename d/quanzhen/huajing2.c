inherit ROOM;

void create()
{
        set("short", "����С·");
        set("long", @LONG
�����Ǻ�ɽ�ϵ�С·������С·�������˹������޳���
�ģ�Ҳ��ֻ����ǰ�Ĳ�ҩ�˲ȶ��ˣ��ֳ�����һ��С·��������
�����˸���Ұ�����������󣬷��ͻ��㣬��Ϊ�ľ���		
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "southeast" : __DIR__"huajing3",
				"northwest" : __DIR__"huajing1",               
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
