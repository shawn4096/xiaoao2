//huanxidong1.c
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�ϻ���");
        set("long", @LONG
����Ѫ�����ڵ��޻�ϲ��֮�أ����ڴ���һ���������֮����
��ʱ����Ů����ת�к͵����������˵İ���˻���������˲��ɵ�
Ѫ�����š�ǽ�ϻ����˺ܶั��Ů���ϵ�ͼ��(hua)��ÿһ�Ŷ���
�����룬˼����ǧ�����ߵ������ղ��ܡ�
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "east"   : __DIR__"huanxidong2",
			"south"   : __DIR__"kengdao4",
			"west"   : __DIR__"huanxidong3",
			"north"   : __DIR__"huanxidong4",
        ]));
        set("item_desc", ([
            "hua"   : "���Թ�ӡ�ȵĹ�����Ů˫��֮����Ϊ�޻�ϲ��֮�˵�������\n",
        ]));
        set("objects",([
                __DIR__"obj/bed" : 1,
        ]));
		create_door("south", "С��", "north", DOOR_CLOSED);

        setup();
}
void init()
{

	add_action("do_canchan","canchan");
}
//������ϲ���չ�ǰ������Ѫս��Ȼ��չ�
int do_canchan(string arg)
{
	object me;
	me=this_player();


}