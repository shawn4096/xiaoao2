// 铁掌掌法 -- 阴阳合一
// Modified by snowman@SJ 19/12/2000
// By Spiderii 加入450 lv后必出tianlei
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string perform_name(){ return HBYEL+HIR"阴阳合一"NOR; }
int perform(object me, object target)
{
        int j;

        if( !target ) target = offensive_target(me);
        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)
          || environment(target)!= environment(me))
                return notify_fail("「阴阳合一」只能在战斗中对对手使用。\n");
        if( me->query_temp("weapon")) {
            return notify_fail("你必须空手才能使用「阴阳合一」！\n");
        }

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 300 )
                return notify_fail("你的铁掌掌法还不够娴熟，使不出「阴阳合一」绝技。\n");

        if( (int)me->query_skill("guiyuan-tunafa", 1) < 300 )
                return notify_fail("你的归元吐纳法等级不够，使不出「阴阳合一」绝技。\n");

        if (me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("你所使用的内功不对。\n");

        if( (int)me->query_skill("force",1) < 300 )
                return notify_fail("你的内功等级不够，不能使用「阴阳合一」。\n");

        if( (int)me->query_str() < 60 )
                return notify_fail("你的膂力还不够强劲，使不出「阴阳合一」来。\n");

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("你现在无法使用「阴阳合一」！\n");                                                                                 

      
        if( (int)me->query("max_neili") < 3500)
                return notify_fail("你现在内力太弱，使不出「阴阳合一」。\n");      

        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出「阴阳合一」。\n");

		if( (int)me->query("jingli") < 1000 )
                return notify_fail("你现在精力不足，使不出「阴阳合一」。\n");

		j = (int)me->query_skill("tiezhang-zhangfa", 1);
        
		message_vision(HIW"\n$N退了两步，突然身子微侧，紧跟着身形猛进直击$n！\n"NOR, me, target);

        if(me->query_temp("tzzf/zhangdao")) 
           j = j + random(j);
        me->add_temp("apply/strike", j);
        me->add_temp("apply/damage", j/2);
        me->add_temp("apply/attack", j);
        me->set_temp("tz/heyi", 1);
        if((int)me->query_temp("tzzf/zhangdao")) 
		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        else COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        
		me->set_temp("tz/heyi", 2);
        
		if(me->is_fighting(target)){
           if(random(me->query("combat_exp",1)) > target->query("combat_exp", 1)/2
           || me->query_temp("tzzf/zhangdao") )
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                else
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        }
        me->delete_temp("tz/heyi");
        me->add_temp("apply/strike", -j);
        me->add_temp("apply/damage", -j/2);
        me->add_temp("apply/attack", -j);
        if( me->query_skill("tiezhang-zhangfa",1) > 449 ){
                tell_object(me, HIY"\n紧接着你蓄积劲气后掌势一变，开始凝聚铁掌秘传掌法“天雷气”……！\n"NOR);
                me->start_call_out( (: call_other, __DIR__"tianlei", "tianlei_hit", me, 2 :), 1 );
        }
        me->add("neili", -500);
        me->add("jingli", -100);
        me->start_busy(random(2));
        me->start_perform(5,"「阴阳合一」");
        return 1;
}

int help(object me)
{
        write(WHT"\n铁掌掌法"+HBYEL+HIR"「阴阳合一」"NOR"\n");
        write(@HELP
	这是裘千仞铁掌功的十三绝招之一，叫作「阴阳合一」，
	最是猛恶无比。而且据帮中护法说，还看过帮主在此招之
	后出过一式杀招！令人防不胜防。
        
	perform strike.heyi

要求：
	当前内力要求 1000 以上；
	最大内力要求 3500 以上；
	当前精力要求 1000 以上；
	铁掌掌法等级 300 以上；
	基本内功等级 300 以上；
	有效臂力要求 60  以上；
	激发掌法为铁掌掌法；
	激发招架为铁掌掌法；
	备铁掌掌法且且手无兵器。
HELP
        );
        return 1;
}
