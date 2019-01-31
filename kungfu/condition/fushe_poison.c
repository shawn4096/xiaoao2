// fushe_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        me->receive_wound("jing", 50);
        me->receive_damage("jingli", 300);
	me->set_temp("last_damage_from", "蝮蛇毒发作");
	me->apply_condition("fushe_poison", duration - 1);
	if (living(me))
		message_vision(BLU "$N两眼发直，身子瑟瑟抖了起来！\n" NOR, me);
	else
		message_vision(BLU "$N痛苦地哼了一声！\n" NOR, me);
	me->add_busy(2); 
	if( duration < 1 ) return 0;
	return 1;
}

string query_type(object me)
{
	return "poison";
}
