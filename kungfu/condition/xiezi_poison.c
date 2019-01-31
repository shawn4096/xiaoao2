// snake_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        me->receive_wound("qi", 160);
        me->receive_damage("qi", 160);
	me->set_temp("last_damage_from", "Ы�Ӷ�����");
	me->apply_condition("xiezi_poison", duration - 1);
	if (living(me))
		message_vision(HIB "$N��ɫ���죬�����ϳ���һ������ŧ��������ӿ��Ѫŧ��\n" NOR, me);
	else
		message_vision(HIB "$N����һ������ŧ��ץ�ƣ�ŧѪ����\n" NOR, me);
	me->add_busy(2); 
	if( duration < 1 ) return 0;
	return 1;
}

string query_type(object me)
{
	return "poison";
}
