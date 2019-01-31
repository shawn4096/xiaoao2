// fushe_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        me->receive_wound("qi", 200);
        me->receive_wound("jing", 100);
	me->set_temp("last_damage_from", "银血蛇毒发作");
	me->apply_condition("yinxueshe_poison", duration - 1);
	if (living(me))
		message_vision(BLU "$N两眼发银灰色光，身子泛起一层银色雾气！\n" NOR, me);
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
