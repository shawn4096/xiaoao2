// snake_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        //me->receive_wound("jingli", 160);
        me->receive_damage("jingli", 300);
	me->set_temp("last_damage_from", "蜘蛛毒发作");
	me->apply_condition("zhizhu_poison", duration - 1);
	if (living(me))
		message_vision(HIB "$N满脸黑气缭绕，口吐白沫，不断抽搐！\n" NOR, me);
	else
		message_vision(HIB "$N黑气缭绕覆盖满脸，已经看不清面目了！\n" NOR, me);
	me->add_busy(2); 
	if( duration < 1 ) return 0;
	return 1;
}

string query_type(object me)
{
	return "poison";
}
