#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( !living(me) ) {
      message("vision", me->name() + "泛起一片片红砂状，散发出一阵腥臭味。\n", environment(me), me);
   }
   else {
      tell_object(me, HIR "忽然冒出一股淡红色的毒气，如雾如纱！\n" NOR );
      tell_room(environment(me), HIR + me->name()+"突然全身冒出淡红色的毒气，腥臭难闻。\n" NOR,
                ({ me }));      
   }
		me->receive_damage("qi", 300,"红砂毒发而");

	    if(userp(me))
           me->receive_wound("jing",150,"红砂毒发而");
	  
      else me->receive_wound("jing", 50,"红砂毒发而");

		  me->apply_condition("hongsha_poison", duration - 1);
		  me->set_temp("last_damage_from", "红砂毒发作");	 
   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}

string query_type(object me)
{
	return "poison";
}
