// 雪谷憋气 xuegu_bieqi.c
// created by sohu@xojh
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
		
	//	if (environment(me)->query("xueceng")>2)
		//{
			me->receive_damage("qi",500);
			me->receive_damage("jing",200);
		//}
	     
		 if(!objectp(me->query_temp("last_damage_from")))
	     	me->set_temp("last_damage_from","深入雪谷中憋死了");
		 message_vision(WHT"此地空气极为稀薄，$N感觉甚是憋气。\n"NOR,me);
             me->apply_condition("xuegu_bieqi",duration-random(2));
       	     me->add_busy(1);
      
      if( duration < 1 ) return 0;
      return CND_CONTINUE;
}

string query_type(object me)
{
        return "wound";
}
