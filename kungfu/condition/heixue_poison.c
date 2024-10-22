#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   
      tell_object(me, HIB "突然你感觉四肢麻麻的似乎不大灵便！\n" NOR );
      tell_room(environment(me), HIB + me->name()+"突然全身一颤，两张手掌心已全成黑色，黑气更顺着手臂向上攀升！\n" NOR,
                ({ me }));     
  
      me->receive_damage("qi", random(500));
      if(userp(me))
          me->receive_wound("jing", random(200));
      else me->receive_wound("jing", random(400));
		me->add_busy(2);
		me->set_temp("last_damage_from", "中黑血神针毒");
      if( duration < 2 ) return 0;
		me->apply_condition("heixue_poison", duration - 1);
      return CND_CONTINUE;
}

string query_type(object me)
{
	return "poison";
}
