// fushe_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        me->receive_wound("qi", 150);
        me->receive_wound("jing", 200);
	me->set_temp("last_damage_from", "��Ѫ�߶�����");
	me->apply_condition("jinxueshe_poison", duration - 1);
	if (living(me))
		message_vision(HIY "$N����ð��⣬���ӷ���һ���ɫ��������\n" NOR, me);
	else
		message_vision(HIY "$Nʹ��غ���һ����\n" NOR, me);
	me->add_busy(2); 
	if( duration < 1 ) return 0;
	return 1;
}

string query_type(object me)
{
	return "poison";
}
