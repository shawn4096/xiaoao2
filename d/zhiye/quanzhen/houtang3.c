inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
������ȫ��̵��������书�ĵط���ȫ��̵����ڶ࣬��
��ÿ��ÿ�µ�ʮ�����죬���ټ����е����������д裬һ����
��������ǵ��书��������һ����ѡ���˲ŵ��ν��е���Ҫְ
�����ڻ�������������ӣ����п���һ�ˡ�
LONG);
        set("exits", ([
                "east" : __DIR__"jingxiushi",
                "west" : __DIR__"houtang2",
                "northeast" : __DIR__"xiaohuayuan1",
        ]));
        set("objects", ([
               "d/quanzhen/npc/wangzhitan" : 1,
        ]));

        setup();
        replace_program(ROOM);
}