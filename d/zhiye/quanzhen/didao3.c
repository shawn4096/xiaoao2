inherit ROOM;

void create()
{
        set("short", "ɽ�еص�");
        set("long", @LONG
�����Ǻ�ɽ�е�һ������С·������С·���˹������޳����ģ�
����һ�˴���������������Ǵ˵ص��ڿ������£������κβ��ʣ�Ӧ
���������ʿ�������˵أ��ص��������ϣ�����Խ��Խ���¡�
LONG);
      //  set("outdoors", "quanzhen");
        set("exits", ([
                "southdown" : __DIR__"didao2",
				"westup" : __DIR__"didao4",
              
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
