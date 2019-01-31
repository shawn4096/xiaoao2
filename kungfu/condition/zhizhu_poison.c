// snake_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        //me->receive_wound("jingli", 160);
        me->receive_damage("jingli", 300);
	me->set_temp("last_damage_from", "֩�붾����");
	me->apply_condition("zhizhu_poison", duration - 1);
	if (living(me))
		message_vision(HIB "$N�����������ƣ����°�ĭ�����ϳ鴤��\n" NOR, me);
	else
		message_vision(HIB "$N�������Ƹ����������Ѿ���������Ŀ�ˣ�\n" NOR, me);
	me->add_busy(2); 
	if( duration < 1 ) return 0;
	return 1;
}

string query_type(object me)
{
	return "poison";
}
