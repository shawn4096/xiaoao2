//shedan.c
//�ߵ�
//�����ڹ�β��

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name("�ߵ�", ({"she dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�ŵ���ɫ���ߵ�,���������Ŀ����΢����������\n");
		set("value", 10000);
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
// max = (int)me->query("eff_jingli");
	 if (me->query("neili")<me->query("max_neili"))
	 {
		 me->set("neili",me->query("max_neili")-1);
	 }
	
	message_vision(HIG "$N�ſ�����һҧ���ߵ���Ƥ�㼴���ѣ��Ǿ����ڿ�֭���ȼ��༫������ҪŻ��������\n" NOR, me);
	message_vision(HIG "���Թ�Ƭ�̣�$Nֻ������˳��������������\n" NOR, me);
	destruct(this_object());
	return 1;
}

