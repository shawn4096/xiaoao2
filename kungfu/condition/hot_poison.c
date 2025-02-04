#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( !living(me) ) {
      message("vision", me->name() + "全身变黑，散发出一阵焦糊味。\n", environment(me), me);
   }
   else {
      tell_object(me, HIR "忽然一股火热之气袭来，烫得你手脚发颤！\n" NOR );
      tell_room(environment(me), HIR + me->name()+"突然全身冒出阵阵红烟，嘴唇干裂，双手胡乱地挥舞着。\n" NOR,
                ({ me }));      
   }
      me->receive_damage("qi", 30);

		  if(userp(me))
           me->receive_wound("jing", 10);
	  
      else me->receive_wound("jing", 1);

		  me->apply_condition("hot_poison", duration - 1);
		  me->set_temp("last_damage_from", "热毒发作");
   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}

string query_type(object me)
{
	return "poison";
}
