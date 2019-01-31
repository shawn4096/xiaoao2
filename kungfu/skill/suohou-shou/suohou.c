// suohou.c 锁喉 cre by sohu@xojhu 2014.1

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        string pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

    
	
		if (me->query_temp("weapon"))
			return notify_fail("「锁喉擒拿手」空手才能使用。\n");
        if (! target || ! me->is_fighting(target))
                return notify_fail("「锁喉」绝技只能在战斗中对对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能使用「锁喉」！\n");
                
        if ((int)me->query_skill("suohou-shou", 1) < 200)
                return notify_fail("你的锁喉功还不够娴熟，不能使用「锁喉」。\n");
       // if ((int)me->query_skill("huntian-qigong", 1) < 200)
                //return notify_fail("你的混天气功还不够娴熟，不能使用「锁喉」绝技。\n");  
		if ((int)me->query_skill("hand", 1) < 200)
                return notify_fail("你的基本手法还不够娴熟，不能使用「锁喉」绝技。\n"); 
		if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的基本内功还不够娴熟，不能使用「锁喉」绝技。\n"); 
        if ((int)me->query("neili", 1) < 200)
                return notify_fail("你现在内力太弱，不能使用「锁喉」。\n");
        if ((int)me->query("max_neili", 1) < 1500)
                return notify_fail("你现在最大内力太弱，不能使用「锁喉」。\n");
		if ((int)me->query("max_jingli", 1) < 1200)
                return notify_fail("你现在精力太弱，不能使用「锁喉」。\n");
		if (me->query_skill_mapped("hand")!="suohou-shou")
                return notify_fail("你现在没有激发锁喉手，不能使用「锁喉」。\n"); 
        msg = HIY "$N" HIY "冷笑一声，飞身一跃而起，眼露凶光，右手陡然抓"
              "向$n" HIY "的喉部。\n\n" NOR;
        me->add("neili", -200);

        //me->want_kill(target);
        ap = me->query_skill("hand",1)+me->query_skill("suohou-shou",1);
        dp = target->query_skill("dodge",1)+target->query_skill("parry",1);
        if (random(ap+dp) > dp || !living(target)||random(me->query_str(1))>target->query_dex(1)/2)
        {
                //me->start_busy(2);
                me->add("neili", -180);
                damage = 0;

                if (me->query("neili") > target->query("neili") * 2 && userp(target))
                {
                        msg += HIR "\n结果只听“喀喀”几声脆响，$N" HIR "五指已将$n"
                               HIR "喉结捏个粉碎，$n" HIR "一声哀嚎，软绵绵的瘫了下去。\n" NOR;
                        damage = -1;
						
                } else
                {
                        target->add_busy(1 + random(3));
       
                        damage = ap + (int)me->query_skill("force",1);
                        damage = damage + random(damage);
                        
                        if (arrayp(limbs = target->query("limbs")))
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "要害";
                        msg += HIC "\n$n连忙腾挪躲闪，只听“喀嚓”一声，$N"
                               HIC "五指正拿中$n" HIC "的" +HIR+ limb +NOR "，$n"
                               HIC "一声惨叫，鲜血飞溅而出。\n" NOR;
					    target->receive_damage("qi",damage,me);
						target->receive_wound("qi",damage/3,me);
						//target->recieve_wound("jing",damage/4,me);
                       // msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 66, pmsg);
                }
        } else 
        {
                me->start_busy(2);
                msg += CYN"可是$p看破了$P的企图，身形急动，躲开了这一抓。\n"NOR;
        }

        message_combatd(msg, me, target);
		//me->add_temp("apply/attack",);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
        if (damage < 0)
        {
                target->receive_wound("qi",(int)target->query("qi")*2/3,me);
                //target->die();
        }
		
        return 1;
}

string perform_name(){ return HIR"锁喉绝技"NOR; }

int help(object me)
{
        write(HIC"\n锁喉擒拿手法之「锁喉绝技」："NOR"\n\n");
        write(@HELP 
	锁喉擒拿手绝技，是丐帮马副帮主的成名绝技，是将锁喉
	与擒拿融合在一起的绝技。在双方对战过程中，既可以通
	过贴身擒拿术，点中对方的穴道，又可以通过锁喉绝技一
	招致敌。将对方咽喉要害之处拿捏住，一招毙命。乃丐帮
	初期绝技。
	
	指令：perform hand.suohou
			
要求：  
	最大内力 1500 以上；
	最大精力 1200 以上；
	锁喉擒拿等级 200 以上；
	基本内功等级 200 以上；
	基本手法等级 200 以上；
	激发手法为锁喉擒拿手；
	激发招架为锁喉擒拿手；
	且空手
HELP
        );
        return 1;
}