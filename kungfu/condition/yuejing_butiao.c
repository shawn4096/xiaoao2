// /kungfu/condition/yuejing_butiao.c
// by akuma 1:30 PM 1/22/2002

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{
	string msg;
	switch( random(3) ) {
	case 0 :
		msg = HIR"$N突然觉得下腹不适，说不出的难受。\n"NOR;
		break;
	case 1 : 
		msg = HIR"$N突然觉得下腹不适，说不出的难受。\n"NOR;
		me->receive_damage("qi", 2);
		me->receive_wound("qi", 1);
		break;
	case 2 :
		msg = HIR"$N突然觉得下腹不适，说不出的难受。\n"NOR;
		me->receive_damage("jing", 1);
		me->receive_wound("jing", 2);
		break;
	}
	message_vision(msg, me); 
    me->set_temp("last_damage_from", "月经不调发作");	  	
	me->apply_condition("yuejing_butiao", duration - 1);
	if( duration < 1 ) return 0;
	return CND_CONTINUE;
}

string query_type(object me)
{
	return "hurt";
}

