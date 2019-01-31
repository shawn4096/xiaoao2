// snake_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        me->receive_wound("qi", 160);
        me->receive_damage("qi", 160);
	me->set_temp("last_damage_from", "蝎子毒发作");
	me->apply_condition("xiezi_poison", duration - 1);
	if (living(me))
		message_vision(HIB "$N面色潮红，浑身不断长出一个个大脓包，向外涌出血脓！\n" NOR, me);
	else
		message_vision(HIB "$N哀嚎一声，将脓包抓破，脓血满身！\n" NOR, me);
	me->add_busy(2); 
	if( duration < 1 ) return 0;
	return 1;
}

string query_type(object me)
{
	return "poison";
}
