// fushe_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
	if (me->query("neili")<400) me->set("neili",0);
	else  me->add("neili", -400);
        
	me->receive_wound("jing", 150);
	
	me->set_temp("last_damage_from", "五步蛇毒发作");
	me->apply_condition("wubushe_poison", duration - 1);
	if (living(me))
		message_vision(BLU "$N两眼泛起灰色雾气，瑟瑟发抖！\n" NOR, me);
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
