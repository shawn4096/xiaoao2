// lgf.c
// ������
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short","������");
	set("long",@long
�˴�����̳����ƽʱ����ϰ��ĵط������п�ǽ�и������ܣ������
�Ų��ٱ������Ա߷��ż���ʯ��(suo)�������м���һ��÷��׮(zhuang)��
���ӵĴ���������ż���ɳ��(dai)��
long);
	set("exits",([
	    "south" : __DIR__"road2",
	]));
	set("item_desc",([
	    "dai" : "һ�����ŵ�ɳ���������е�����ϰ�Ʒ��ĵ��ߣ�����Դ�(da)���ԡ�\n",
		"zhuang" : "÷��׮�������е�����ϰ�Ṧ�ĵط����������(tiao)���ԡ�\n",
	]));
	set("objects",([
	
	
		//__DIR__"obj/yaoli3" : 1,
	]));	
	set("coor/x",500);
	set("coor/y",440);
	set("coor/z",90);
	setup();
}
int init()
{
	add_action("do_da","da");
	add_action("do_tiao","tiao");
}
	   	
int do_da(string arg)
{
		object me=this_player();

		if (!arg || arg!="dai")
			return notify_fail("��Ҫ��ʲô����\n");
		
        if (me->is_busy())
			 return notify_fail("������æµ�С�\n");
		if (me->query_skill("strike",1)>100)
			return notify_fail("һ����ȥ����ɳ����ɣ�\n");
		
		message_vision(YEL"$N���������ƣ�����һ�ƴ���ɳ����\n"NOR,me);
		me->add_busy(1+random(1));
		
		if (random(me->query("jingli"))<30) return notify_fail("�㾫������\n");
		
		
		me->add("jingli",-20-random(10));
		
		
		if (me->query_skill("strike",1)<100)
		{			
			me->improve_skill("strike",(int)me->query_skill("strike",1));
		}
		return 1;
}

int do_tiao(string arg)
{
		object me=this_player();

		if (!arg || arg!="zhuang")
			return notify_fail("��Ҫ��ʲô����\n");
		
        if (me->is_busy())
			 return notify_fail("������æµ�С�\n");
		if (me->query_skill("dodge",1)>100)
			return notify_fail("��÷��׮��������ɣ��������磡\n");
		
		message_vision(HIG"$NԾ��÷��׮��շת��Ų���Ṧ���������治ǳ��\n"NOR,me);
		me->add_busy(1+random(1));
		
		if (random(me->query("jingli"))<30) return notify_fail("�㾫������\n");
		
		
		me->add("jingli",-20-random(10));
		
		
		if (me->query_skill("dodge",1)<100)
		{			
			me->improve_skill("dodge",(int)me->query_skill("dodge",1));
		}
		return 1;
}