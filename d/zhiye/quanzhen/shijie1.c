inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����һ�������ʯ��·����ɽ����������ɽ�Ƶ���������
���ۡ�����ɽ�ƶ��ˣ������޽�����ʯ��ʱ�϶����˲�С�Ĺ�
���ߵ�����Ѿ����Կ���ȫ��������۵��ܽ��ˡ�
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "northup"   : __DIR__"shijie2",
                "southdown" : "/d/quanzhen/shanjiao",
        ]));

        set("objects",([
                __DIR__"npc/youke" : 1,
                __DIR__"npc/xiangke" : 2,
        ]));

        setup();       
}