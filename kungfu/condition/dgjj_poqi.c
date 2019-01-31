// this condition used by dugu-jiujian's perform poqi。

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{
   	if (duration < 1) {
          	message_vision(HIC"$N运功疗伤后，长出一口气，感觉气穴处伤势逐渐恢复了。\n" NOR, me);
          	//me->add_temp("apply/dodge",(int)me->query_temp("dgb/ban"));
          	//me->delete_temp("dgb/ban");
          	return 0;
    	}
   	if (!duration) return 0;
   	
   	if( !living(me) ) {
          	message_vision(HIC"$N功力运使，忽然间丹田部位一阵剧痛传来，不由闷哼一声，身形顿时抽搐。\n" NOR, me); 
       	}
   	
   	else {
          	message_vision(HIR"$N全身气机一片混乱，丹田剧痛，浑身功力无法运转。\n" NOR, me); 
       	}
		me->receive_damage("qi",random(1000),"独孤九剑破气式所伤而");
		me->receive_damage("neili",200+random(1000));
		me->set_temp("last_damage_from", "独孤九剑破气式发作");
		if (me->query("neili")<0) me->set("neili",0);
		
   		me->add_busy(random(2)+1);
   		me->apply_condition("dgjj_poqi", duration - 1);
   		return CND_CONTINUE;
}

string query_type(object me)
{
        return "wound";
}
