// snake_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        me->receive_wound("jing", 60);
        me->receive_damage("jing", 60);
	me->set_temp("last_damage_from", "蟾蜍毒发作");
	me->apply_condition("hama_poison", duration - 1);
	if (living(me))
		message_vision(HIB "$N面色惨白，不住的翻滚，哀嚎！\n" NOR, me);
	else
		message_vision(HIB "$N状如一只蟾蜍，向空中一纵，随即摔在地上，一动不动！\n" NOR, me);
	me->add_busy(2); 
	if( duration < 1 ) return 0;
	return 1;
}

string query_type(object me)
{
	return "poison";
}
