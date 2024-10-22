#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me,int duration)
{
	if(!environment(me)) return CND_CONTINUE; 
	me->receive_wound("qi",200);
	me->receive_wound("jing",100);
	me->add_busy(2);
	me->set_temp("last_damage_from","天魔解体发作");
	if( !living(me) ) message("vision",HIR+ me->name() + HIR"的身子开始变得僵硬，身上不断有鲜血流出。\n"NOR, environment(me), me);
	else 
		message_vision(HIR"$N双膝渐渐弯曲，身子软了下来，浑身无力，显然先前运用天魔解体伤了元气。\n"NOR,me);
	if(duration < 1) return 0;
	me->apply_condition("hmy_jieti",duration - 1);
	return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}