//fushedan.c
//���ߵ�
//���Ӿ���

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIY"��Ѫ���ߵ�"NOR, ({"jinxue shedan", "shedan","dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�Ž��ɫ�Ľ�Ѫ�ߵ���\n");
		set("value", 150000);
	}
	setup();
}

int do_eat(string arg)
{	
// int max;
	object me = this_player();

	if (!id(arg))
		return notify_fail("��Ҫ��ʲô��\n");
	if( !random(2) ) 
	{
		message_vision(HIM "$N�ſ�����һҧ���ߵ���Ƥ�㼴���ѣ��Ǿ����ڿ�֭���ȼ��༫�����$N���Լ��ԵĶ��������˳�����\n" NOR, me);
		this_player()->set("food",10);
		destruct(this_object());
		return 1;
	}
	if (me->query("max_neili")>(me->query_skill("force")-me->query_temp("apply/force")) * 8 + me->query("combat_exp") / 1000)
	{
		return notify_fail("�����������Ѿ����������ˣ��޷�ʹ�ã�\n");
	}
	 me->add("max_neili", 1);
//   me->set("jingli", max);
	message_vision(HIM "$N�ſ�����һҧ���ߵ���Ƥ�㼴���ѣ��Ǿ����ڿ�֭���ȼ��༫������ҪŻ��������\n" NOR, me);
	message_vision(HIM "���Թ�Ƭ�̣�$N�������棬��������õ�������\n" NOR, me);
	destruct(this_object());
	return 1;
}
