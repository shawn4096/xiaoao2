// zuijiu.c 醉酒 by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{                                  
      int i, lvl, addlvl,dk;
      object weapon;
      dk=me->query_conditions("drunk");
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target))
                return notify_fail("「八仙醉打」只能在战斗中对对手使用。\n");

      if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "club"
        || me->query_skill_mapped("club") != "zui-gun")
                return notify_fail("你现在无法使用「八仙醉打」。\n");
  
      if( (int)me->query_skill("zui-gun",1) < 150 )
                return notify_fail("你的醉棍不够娴熟，不会使用「八仙醉打」！\n");
      
      if( me->query_skill_mapped("force") != "yijin-jing" )
                return notify_fail("你现在所使的内功无法使出「八仙醉打」。\n");

      if( (int)me->query_skill("yijin-jing",1) < 150 )
                return notify_fail("你的易筋经等级不够，不能使用「八仙醉打」！\n");  
       
      if( (int)me->query_str() < 25 )
                return notify_fail("你的臂力不够强，不能使用「八仙醉打」！\n");
      
      if( (int)me->query("max_neili") < 2500 )
                return notify_fail("你的内力太弱，不能使用「八仙醉打」！\n");
            
        lvl = (int)me->query_skill("zui-gun", 1);
        addlvl = (int)me->query_skill("zui-gun", 1)+(int)me->query_skill("yijin-jing", 1)/2;
        addlvl=addlvl/2;
        if(lvl < 120) return notify_fail("你的等级太低，无法使用出「八仙醉打」！\n");

      	if( (int)me->query("neili") < 1500 )
                return notify_fail("你的内力太少了，无法使用出「八仙醉打」！\n");
      	lvl /= 20;
      	lvl--;
      	if(lvl > 8) lvl = 8; 
      	if(lvl < 1) return notify_fail("你的等级太低，无法使用出「八仙醉打」！\n");
        message_vision(GRN "只见$N喷出一口酒气，一式「八仙醉酒」，围着$n一摇一摆地走动着。\n" NOR, me, target);
		message_vision(HIY"\n$N将自己所领悟的“形醉意不醉，步醉心不醉”的醉棍真谛，步履踉跄，似醉非醉，使出「八仙醉打」，醉棍威力大增！\n"NOR,me);
        
		me->add_temp("apply/attack", addlvl);
		me->add_temp("apply/club", addlvl/2);
        me->add_temp("apply/parry", addlvl/2);
        me->add_temp("apply/dodge", addlvl/2);
       
		if (dk>0)
		{
		       me->add_temp("apply/damage", dk*addlvl/2);
			   me->set_temp("slzg/zuijiu1",1);
		}
		else  
		{
			me->add_temp("apply/damage", addlvl/2);
			me->set_temp("slzg/zuijiu2",1);
		}
      	me->set_temp("zuijiu", 1);
      	for(i=0; i < lvl; i++){
      	   	if(!me->is_killing(target->query("id")) 
      	   	&& !target->is_killing(me->query("id"))
      	   	&& !target->is_fighting(me))
      	   	break;
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
           	me->add_temp("zuijiu", 1);
                me->receive_damage("neili", 50);
                me->receive_damage("jingli", 10);
      	}
      	me->delete_temp("zuijiu");
        me->add_temp("apply/attack", -addlvl);
		me->add_temp("apply/club", -addlvl/2);
        me->add_temp("apply/parry", -addlvl/2);
        me->add_temp("apply/dodge", -addlvl/2);
        if (me->query_temp("slzg/zuijiu1"))
		{
		    me->add_temp("apply/damage", -dk*addlvl/2);
			me->delete_temp("slzg/zuijiu1");
		}
		if (me->query_temp("slzg/zuijiu2"))
		{
		    me->add_temp("apply/damage", -addlvl/2);
			me->delete_temp("slzg/zuijiu2");
		}	
        
		me->start_perform(5, "「八仙醉打」");
		me->delete_temp("slzg/zuijiu");

        tell_object(me, HIG"\n你心神一乱，再也无法维持似醉非醉的意境了。\n"NOR); 
        return 1;
}

int help(object me)
{
	write(HIC"\n醉棍之「醉酒」："NOR"\n");
	write(@HELP
	少林醉棍是少林棍法的中期棍法武技，这门武功和
	寻常棍法武技有所不同，需要处于似醉非醉状态下
	方可发挥最大威力。注意，攻击力和醉酒状态有关
	
	perform club.zuijiu

要求：
	最大内力 2500 以上；
	当前内力 1500 以上；
	醉棍等级 150 以上；
	易筋经等级 150 以上；
	激发招架为醉棍；
	激发棍法为醉棍；、
	后天身法大于25；
	注意：伤害和醉酒程度有关；
HELP
	);
	return 1;
}
