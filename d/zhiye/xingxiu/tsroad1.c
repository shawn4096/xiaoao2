
#include <ansi.h>
inherit ROOM;


void create()
{
        set("short", "Ͽ��С��");
        set("long", @LONG
������ͨ����ɽɽ���һ����С����ƽʱ����û���˹�ˣ�����ɭɭ
���Ǻ��䣬·���Ա�ѩ������
LONG
        );
        set("exits", ([
          "southeast" : __DIR__"duchonggu-out",
          "northwest" : __DIR__"tsroad2",
        ]));

        set("outdoors", "tianshan");

      
		setup();
}
void init()
{
	object me=this_player();
	message_vision("һ��ɽ�紵�������̲�ס���˸�����\n",me);
	me->receive_damage("qi",100,"��������");
	me->receive_wound("qi",50,"��������");
}