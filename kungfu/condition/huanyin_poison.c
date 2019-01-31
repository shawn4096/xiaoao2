#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{    
      tell_object(me, HIC "你忽然感到忽然一阵寒气自丹田的而起，逐步渗透到四肢白赅，透出阵阵寒意。。\n" NOR );
      message_vision(HIB"$N突然两腿发软，冷的全身乏力，好象虚脱一般。\n"NOR, me);

      me->receive_damage("jingli", 500+random(100));
      me->receive_wound("jing", 150+random(70));

      me->set_temp("last_damage_from", "幻阴寒毒内伤发作");
      me->apply_condition("huanyin_poison", duration - 1);
	  me->add_busy(2+random(2));
     if( duration < 1 ) return 0;
     return CND_CONTINUE;
}

string query_type(object me)
{
	return "hurt";
}
