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
	set_name(WHT"��Ѫ�ߵ�"NOR, ({"yinxue shedan", "shedan","dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ������ɫɫ����Ѫ���ߵ���\n");
		set("value", 50000);
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
	if (me->query("max_jingli")>(me->query_skill("force")-me->query_temp("apply/force")) * 8)
	{
		return notify_fail("���������Ѿ����������ˣ��޷�ʳ��\n");
	}
	 //me->add("eff_jingli", 1+random(5));
	 me->add("max_jingli", 1+random(4));
	message_vision(HIM "$N�ſ�����һҧ���ߵ���Ƥ�㼴���ѣ��Ǿ����ڿ�֭���ȼ��༫������ҪŻ��������\n" NOR, me);
	message_vision(HIM "���Թ�Ƭ�̣�$N�������棬������õ�������\n" NOR, me);
	destruct(this_object());
	return 1;
}
