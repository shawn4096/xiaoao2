inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������ȫ������֮��̷���˵ľ��ң���䷿����ʰ�ĺ���
ͨ�����ûʲô����ֻ��һ����Ⱦ��ǽ��б����һ�ѱ�����
LONG);
        set("exits", ([
                "north" : __DIR__"xianzhentang",
        ]));
        set("objects",([
                CLASS_D("quanzhen") + "/tanchuduan" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
