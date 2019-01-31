// Room:jpei����֮��
// Date: Zhuifeng 2010

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",  HIW "����ɽ��" NOR);
	set("long", @LONG
������һ�����ɸߵ�ɽ�£���̧ͷһ������Ȼ����ɽ����������һ���������
���ɵ����п�ϲ���㲻ס�����Ͽ�����Ȼûע�⵽����û���κγ�·��
LONG
	);

	set("no_clean_up", 0);
	set("exits", ([
		"down" : "d/city/dangpu",
	]));

	set("objects", ([ 
		//"zhang" : 1 
	]));

	set("no_death",1);
	setup();
}

void init()
{
	add_action("do_tiao", "walk");
	add_action("do_kao", "kao");
	add_action("do_cai", "cai");
}
int do_kao(string arg)
{
	object ob;
	object me = this_player();
	if (arg != "shanji" )
		return notify_fail("��Ҫ��ʲô��\n");
	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");
	/*
	if( me->query("id") !="jpei"|| me->query("id") !="zhuifeng" )
	return notify_fail("����Ҫ��ʲô��\n");
	*/
	if ( (int)me->query("jingli")<400)
	{
		write("������̫���ˣ���Ϣһ�°ɣ�\n");
		return 1;
	} 

	if(random(10) > 5)
	{
		me->add("jingli",-random(300));
		return notify_fail("���������˰��죬���������ɽ��������ץ��������\n"); 
	}

	message_vision("��Ȼ�ݴ���һֻ��ʰ�쵵�"HIY"��"HIG"��"NOR"��$N���������������ɡ�\n"NOR, me);
	message_vision("$N�ۼ��ֿ죬һ�Ѱ�"HIY"��"HIG"��"NOR"ץ�����\n"NOR, me);
	message_vision("$N����ʳָ�󶯣�׼�������տ�Ұζ��\n"NOR, me);
	message_vision("$N����һ��"HIY"���档\n"NOR, me);
	message_vision("��һ��һֻ�������"HIY"�л���"NOR"�Ϳ����ˡ���\n"NOR, me);
	ob = new("/kungfu/class/gaibang/obj/jiaohuaji");
	ob->move(me);
	me->start_busy(10);
	//ob->move(environment(me));
	return 1;
}

int do_cai(string arg)
{
	object ob;
	object me = this_player();

	if (arg != "zhuguo")
		return notify_fail("��Ҫ��ʲô��\n");
	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");

	if( me->query("id") !="jpei" )
		return notify_fail("һ�������Կ������𣬡��������������������滨���֮���ԣ���һ�鷲������ν����ģ�����\n");

	if ( (int)me->query("jingli")<400)
	{
		write("������̫���ˣ���Ϣһ�°ɣ�\n");
		return 1;
	}
	if(random(20) == 3)
	{
		me->add("jingli",-random(300));
		return notify_fail("���������˰��죬ʲôҲû�ҵ���\n"); 
	}

	if (present("zhuguo", me))
	return notify_fail("�������Ѿ���һö"HIR"�������"NOR"�ˣ�ĪҪ̰�����ᣡ\n");
	message_vision("$N���ѵ���Ե��֮�ϣ����ֲ�����һö"HIR"�������"NOR"��\n���Ȼ�����Ա߻��г���һ��"HIG"�ݻ���"NOR"���Ͻ�����������\n"NOR, me);
	ob = new("/u/jpei/zhuguo");
	ob->move(me);
	ob = new("/u/jpei/huandan");
	//ob->move(me)
	return 1;
}

int do_tiao(string arg)
{
	object me = this_player();
	if (arg != "down")
		return notify_fail("��Ҫ��ô�Ĵ��\n");
	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");
	message_vision("$N������һ���¹ڣ�ʩʩȻ���߽�����ʦ����ҡ�\n", me);
	tell_object(me, "��������һ���¹ڣ�ʩʩȻ���߽�����ʦ����ҡ�\n");

	me->receive_damage("jing", 30);
	me->move("/d/wizard/guest_room");
	message_vision("$N����Ӱ��ͻȻ������һ�������С�\n", me);

	me->start_busy(random(2));
	return 1;
}

