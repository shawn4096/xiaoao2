inherit ROOM;

void create()
{
        set("short", "Ͽ��С��");
        set("long", @LONG
������ͨ����ɽɽ���һ����С����ƽʱ����û���˹�ˣ�����ɭɭ
���Ǻ��䣬·���Ա�ѩ������ɽ��Խ��Խ���ͣ��������ء�
LONG
        );
        set("exits", ([
          "southeast" : __DIR__"tsroad1",
          "northwest" : __DIR__"tsroad3",
        ]));

        set("outdoors", "tianshan");

        set("coor/x",-10);
		set("coor/y",50);
		set("coor/z",0);
		setup();
}
void init()
{
	object me=this_player();
	message_vision("һ��ɽ�紵�������̲�ס���˸�����\n",me);

	me->receive_damage("qi",200,"��������");
	me->receive_wound("qi",100,"��������");
}