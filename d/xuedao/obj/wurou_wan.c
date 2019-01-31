// wurou_wan.c ������

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIR"������"NOR, ({"wurou wan", "wan"}));
	set_weight(150);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("unique", 1);
		set("drug", 1);
		set("treasure", 1);
		set("long", "����һ�ź����Ѫ�������ӣ����Դ�ѩɽ���ֶ���Ѫ�����ƶ��ɣ�\n"+
			    "��Ѫ�����������ӣ��ȿ��Գ伢�ֿ�������������������\n");
		set("value", 5000);
	}
}

int do_eat(string arg)
{
	int force_limit, neili_limit, improve;
	object me = this_player();

	force_limit = me->query_skill("force")* 10 + 20* me->query("age") + me->query("combat_exp") /1000;
	neili_limit = me->query("max_neili");

	if (!id(arg))
		return notify_fail("��Ҫ��ʲô��\n");

	if(query("owner") != me->query("id"))
		return notify_fail("����������������õ��İɣ�\n");

	if (me->query("neili") < me->query("max_neili"))
		return notify_fail("��������δ��Ѫ��ӯ�����³��ܲ���������Ĳ�Ѫ��Ч��\n");
	
	if (me->query("max_neili")>(me->query_skill("force")-me->query_temp("apply/force")) * 8 + me->query("combat_exp") / 1000)
	{
		return notify_fail("�����������Ѿ����������ˣ��޷�ʳ��\n");
	}

	if (me->query_condition("medicine" ) > 0) {
		me->add("max_neili", -20);
		message_vision(HIR"$N����һ�������裬ֻ���øγ���ϣ��������ѣ�ԭ����ʳ̫��̫�࣬ҩЧ�ʵ��䷴��\n"NOR, me);
		log_file("quest/neili",sprintf("%-18s��ʳ%s��ȥ������ʮ�㡣\n",
			me->name(1)+"("+capitalize(me->query("id"))+")",name()), me);
	}
	else if (neili_limit < force_limit) {
		if (random(10) > 5) {
			improve = 10 + random(10);
			message_vision(HIY "$N����һ�������裬��Ȼ��ֻ��һ����Ѫ������ӯ����\n" NOR, me);
			me->unconcious();
			me->apply_condition("medicine", 180);
		}
		else {
			improve = 1;
			me->set("neili", 0);
			message_vision(HIY "$N����һ�������裬��Ȼ��ֻ��һ�ɺƵ�������ֱ�嶥�š���\n" NOR, me);
			me->apply_condition("medicine", 60);
		}
		me->add("max_neili", improve);
		log_file("quest/neili",sprintf("%-18s����%s��������%s�㡣\n",
			me->name(1)+"("+capitalize(me->query("id"))+")",name(), chinese_number(improve)), me);
	} else {
		message_vision(HIY "$N����������Ϊ�Ѿ����˼��ޣ�����һ�������衣\n" NOR, me);
		me->unconcious();
	}
	destruct(this_object());
	return 1;
}
