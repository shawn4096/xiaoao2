//By KinGSo 2006.12.25 添加流血效果常规型
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{    
      tell_object(me,  HIR "你被割伤的部位正淌着鲜血。\n" NOR );
      message_vision( HIR"$N被割伤的部位正淌着鲜血，$N昏昏沉沉的，显得有些虚弱。\n"NOR, me);

      me->receive_damage("qi", 150+random(200));
      me->receive_wound("qi", 150+random(200));
      me->add_busy(1);
      me->set_temp("last_damage_from", "失血过多");
      me->apply_condition("liuxue", duration - 1);
      if( duration < 1 ) return 0;
     return CND_CONTINUE;
}

string query_type(object me)
{
	return "hurt";
}
