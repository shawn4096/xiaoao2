// Room: zhengt.c
// Looklove y2k/4/26
// ��������ǰ�󣬴�����Ц LInuX@sj

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIG"������"NOR);
        set("long", @LONG
���ǹ������֮�ϣ���ſ���Ķ����������ɿ������µ�����������
���㲻��������û�����ܷ����㡣������Ҷ���ý��㸲��ס�������ᴵ
�������Ǿ��ס�
LONG
        );
/*
        set("exits", ([
                  "south" : __DIR__"tjing",
        ]));*/

       
	setup();
}
void init()
{
	object me=this_player();
	add_action("do_jump","jump");
	if (me->query_temp("bangjue/askfu"))
	{
		message_vision(HIC"$N�հ����Ӳغã���Ȼ����Զ������������\n"NOR,me);
		call_out("do_teach",1,me);
	}
}
int do_jump(string arg)
{

	object me=this_player();
	if (!arg || arg !="down")
	{
		return notify_fail("��Ҫ���Ķ�����\n");
	}
	message_vision("$N������£����¹�����\n",me);
	me->move("d/xiangyang/lzz/huayuan");
	return 1;

}

int do_teach(object me)
{
	object huang,huang1,lu1,lu;
	message_vision(HIG"$N��ʱһ��,����ʶ��ס��������ʱԶ������������˵������������Զ������$N���д󾪣���æ���������������С�\n"NOR,me);

	message_vision(HIC"\n\n\n����˵������³���ϣ�ǰһ���Ҵ�����Ĵ򹷰�������ϰ����ô���ˣ���\n"NOR,me);
	message_vision(HIY"\n\n³�н��ƺ���Щ���ȣ������ࡣ����˵����³����������ϰ�£������㿴����\n��ʱ�����غ�Ȼ�о����岻�ʣ���������������Ϣ��\n"NOR,me);
	message_vision(RED"\n\n���غ�Ȼ�����Ϻȵ���˭�����ϣ�����������\n"NOR,me);
	me->delete_temp("bangjue/askfu");
	me->delete_temp("bangjue/asklu");
	me->set_temp("bangjue/cang",1);
}
