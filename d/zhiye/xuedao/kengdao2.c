// hollow.c

inherit ROOM;

void create()
{
        set("short", "�ӵ�");
        set("long", @LONG
����Ѫ�����ڵĹ����Կӵ���Ϊ�����Ӹ�����Ҫɽ�����ã�����
������һ���ŵ���ľ�����죬��������Զ��������������Ϣ��
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south"   : __DIR__"kengdao1",
			"west"   : __DIR__"kengdao3",
        ]));
        set("item_desc", ([
           // "dong"   : "һ�������İ��Ķ�Ѩ��\n",
        ]));
        set("objects",([
             //   __DIR__"npc/zhizhu" : 1,
        ]));
        setup();
}
