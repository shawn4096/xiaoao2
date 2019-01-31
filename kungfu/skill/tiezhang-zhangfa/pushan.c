// by darken@SJ
#include <ansi.h>
#include <combat.h>

 inherit F_SSERVER;
 string perform_name(){ return HBRED"铁蒲扇掌"NOR; }
 int perform(object me, object target)
 {
         int j;
         string msg;
         j = me->query_skill("tiezhang-zhangfa", 1);
		 j =j*me->query_str()/10;
         if( !target ) target = offensive_target(me);

         if( !target 
           || !me->is_fighting(target)
           || !living(target)
           || environment(target)!= environment(me))
                 return notify_fail("「铁蒲扇掌」只能在战斗中对对手使用。\n");

         if( objectp(me->query_temp("weapon")) )
                 return notify_fail("你必须空手才能使用「铁蒲扇掌」！\n");

         if( (int)me->query_skill("tiezhang-zhangfa", 1) < 250 )
                 return notify_fail("你的铁掌不够娴熟，使不出「铁蒲扇掌」绝技。\n");

         if( (int)me->query_skill("guiyuan-tunafa", 1) < 250 )
                 return notify_fail("你归元吐纳法不够，使不出「铁蒲扇掌」绝技。\n");

         if( (int)me->query("jiali") < 120 )
                 return notify_fail("你加力不够，使不出「铁蒲扇掌」绝技。\n");

         if (me->query_skill_mapped("force") != "guiyuan-tunafa")
                 return notify_fail("你所使用的内功不对。\n");

         if( (int)me->query_skill("force",1) < 250 )
                 return notify_fail("你的内功等级不够，不能使用「铁蒲扇掌」。\n");

         if( (int)me->query_str() < 55 )
                 return notify_fail("你的膂力还不够强劲，使不出「铁蒲扇掌」来。\n");

         if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
          || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
          || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                 return notify_fail("你现在无法使用「铁蒲扇掌」！\n");

         if( (int)me->query("max_neili") < 2000)
                 return notify_fail("你现在内力太弱，使不出「铁蒲扇掌」。\n");

         if( (int)me->query("neili") < 1000 )
                 return notify_fail("你现在真气太弱，使不出「铁蒲扇掌」。\n");
         if( (int)me->query("jingli") < 800 )
                 return notify_fail("你现在真气太弱，使不出「铁蒲扇掌」。\n");
         if( target->query_temp("pushan") )
                 return notify_fail("别那么残忍啦。\n");

         msg = HIR "\n$N你深吸一口气，大喝一声，伸出右手，五指张开，施出铁掌掌法中的"HIC"「铁蒲扇掌」"HIR"扇向$n太阳穴！\n"NOR;
         if ( target->query("combat_exp")/2 < random(me->query("combat_exp"))
			 ||random(me->query_str())>target->query_str()/2) 
		{
              msg += HIY"\n$n双掌一并，硬是接下了$N这一掌！\n"NOR;
              
			  if (target->query_str()/3 < random(me->query_str()))
			  {
                  target->add_temp("apply/strength",-me->query_str()/2);
                  target->set_temp("tzzf/pushan",me->query_str()/2);
                  target->receive_wound("qi",j/2,me);
                  target->receive_damage("qi",j*2,me);
				  if (objectp(target))
					call_out("remove_effect",(int)j/80,target);
                  msg += HIR"\n只听见喀啦一声，$n的腕骨居然被硬生生的震断了！\n"NOR;
                  
              } else {
                  msg += HIR"\n$n哇地喷出一口鲜血，似乎受了极重的内伤！\n"NOR;
                 
                  target->receive_wound("qi",j,me);
                  target->receive_damage("qi",j*2,me);
              }
              message_vision(msg, me, target);
              COMBAT_D->report_status(target);
         } else {
             msg += HIY"\n$n见来势凶猛，不敢硬挡，连忙转身避开！\n"NOR;
             msg += HIR"\n岂知$N已经埋伏下厉害后著，连出两掌重手！\n"NOR;
             message_vision(msg, me, target);
             me->set_temp("tzzf/pushan",1);
                 if(objectp(target)
             && me->is_fighting(target))
                     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             if(objectp(target)
             && me->is_fighting(target))
                     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             me->delete_temp("tzzf/pushan");
         }               

         me->add("neili", -1000);
         me->start_busy(random(2));
         
         me->start_perform(3,"「铁蒲扇掌」");
         return 1;
 }
int remove_effect(object target)
{
	int str;
	if (!target) return 0;
	str=(int)target->query_temp("tzzf/pushan");
	if (target->query_temp("tzzf/pushan"))
	{
		target->add_temp("apply/strength",str);
		message_vision(YEL"\n在$N强行运用内功不断冲击之下，受伤的手腕伤势大为好转,终于完好如初！\n"NOR,target);
		return 1;
	}


}

int help(object me)
{
        write(HIC"\n铁掌掌法之「铁蒲扇掌」："NOR"\n\n");
        write(@HELP 
	铁蒲扇掌是铁掌十三绝技之一，以雄浑的内力
	化入手掌中，五指张开，呈蒲扇状扇向对方太
	阳穴，若对方盲目举手抵挡，则会收到伤筋动
	骨的巨大伤害。命中和双方悟性与臂力有关

	perform strike.pushan
		
要求：
	当前内力 1000 以上；
	当前精力 800 以上；
	铁掌掌法等级 250 以上；
	基本内功等级 250 以上；
	基本掌法等级 250 以上；
	有效臂力要求 60  以上；
	必须加力要求 120 以上；
	激发掌法为铁掌掌法；
	激发招架为铁掌掌法；
	激发内功归元吐纳法。
HELP
        );
        return 1;
}