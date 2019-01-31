#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	if( !living(me) ) {
		message("vision",HIB + me->name() + HIB"面上一层黑气，不时呻吟一声。\n"NOR, environment(me), me);
	}
	else {
		tell_object(me, HIB "忽然一股黑气自头顶向下蔓延，侵入心脉，你中的九阴白骨抓毒发作了！\n" NOR );
		message("vision", HIB + me->name() + HIB"一阵抽搐，脸色渐渐由白而黑，显然中毒了。\n"NOR,
				environment(me), me);
		me->receive_damage("qi", 150+random(100),"九阴白骨爪毒发作" );
		if(userp(me))
			me->receive_wound("jing", 80+random(50),"九阴白骨爪毒发作");
		else me->receive_wound("jing", 40+random(50),"九阴白骨爪毒发作");
	}
	
 	me->add_busy(1);
	 me->set_temp("last_damage_from", "九阴白骨爪毒发作");
	if( duration < 2 ) return 0;
	me->apply_condition("bgz_poison", duration - 1);
	return CND_CONTINUE;
}

string query_type(object me)
{
	return "poison";
}
