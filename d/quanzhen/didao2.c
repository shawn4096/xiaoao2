inherit ROOM;

void create()
{
        set("short", "ɽ�еص�");
        set("long", @LONG
�����Ǻ�ɽ�е�һ������С·������С·���˹������޳����ģ�
����һ�˴���������������Ǵ˵ص��ڿ������£������κβ��ʣ�Ӧ
���������ʿ�������˵أ��ص��������ϣ�����Խ��Խ���¡�
LONG);
       // set("outdoors", "quanzhen");
        set("exits", ([
                "northup" : __DIR__"didao3",
				"westdown" : __DIR__"didao1",
              
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
