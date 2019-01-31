// flower_poison.c

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{
	if (me->is_ghost()) return 1;
	
	//if(me->query_temp("nopoison")) return 0;
	
	tell_object(me, HIG "你中的" HIR "断肠花毒" HIG "发作了！\n" NOR );
	me->receive_wound("jing", 60,"断肠花毒发作");
	me->receive_wound("qi",200,"断肠花毒发作");
	//if ((int)me->query("eff_jing")<0 || (int)me->query("eff_qi")<0) return 0;
	
	me->apply_condition("flower_poison", duration - 1);
	
	if( duration < 1 ) return 0;
	return CND_CONTINUE;;
}

string query_type(object me)
{
	return "poison";
}
