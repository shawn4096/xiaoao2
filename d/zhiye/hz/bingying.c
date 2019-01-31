// Room: /d/suzhou/bingying.c
// Date: May 31, 98  Java
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "����ָ����");
	set("long", @LONG
�����Ǳ�Ӫ���������鵽�����ǹٱ����е����佫��ָ�����жӲ�
�����еĶ������������е����š�����������Ϣ����ǽ��������˧����
����ɫ��Ѱ�������ܡ����������������ȫ�������Χ�˹��������ƿ�
����̫�
LONG );
	set("outdoors", "����");
	set("exits", ([
		"north"  : __DIR__"bingyinggate",

	]));
	set("objects", ([
		"/d/city/npc/wujiang": 1,
		"/d/hz/npc/duantiande": 1,
		"/d/city/npc/bing": 4,
	]));
	setup();
	//replace_program(ROOM);
}

int init()
{
	add_action("do_zhua",({"zhuazhu","zhua","catch","sha"}));
	
}

int do_zhua(string arg)
{
	object me,duan;
	me=this_player();
	if (me->is_fighting())
	{
		return notify_fail("������ս���У��������ɱ����£�\n");
	}
	if (present("jinguo gaoshou",this_object()))
	{
		return notify_fail("����������ں���ս���У��������ɱ����£�\n");
	}
	if (!objectp(duan=present("duan tiande",this_object())))
	{
		return notify_fail("����²��ڴ˵أ��������ɱ����£�\n");
	}
	if ((arg=="duan"||arg=="duan tiande"||arg=="tiande")
		&&me->query_temp("quest/���Ӣ�۴�/�����߹�/findduan"))	
	{
		message_vision(HIY"��������д󾪣���æץ����Χ��ʿ������$N����ͼ�赲Ƭ�̣�\n"NOR,me);
		message_vision(HIC"\n$N��ϸ���ϣ�����������ȥ�ķ����ƺ��Ǻ��ݾ����µķ���\n"NOR,me);
		me->delete_temp("quest/���Ӣ�۴�/�����߹�");
		
		me->set_temp("quest/���Ӣ�۴�/�����߹�/jingcisi",1);
		destruct(duan);
	}
	
    return 1;
}
