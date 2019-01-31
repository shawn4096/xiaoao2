// throw.c 灵蛇杖法喷毒
// By Yzuo 97.04

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage;
		damage=me->query_skill("lingshe-zhangfa",1)+me->query_skill("hamagong",1);
		damage=damage+random(damage/2);
        if( !target ) target = offensive_target(me);

        if( environment(me)->query("no_fight") )
                return notify_fail("这里不能攻击别人! \n");

        if( !target || !target->is_character() )
                return notify_fail("喷毒只能对对手使用。\n");

        if( (int)me->query_skill("hamagong", 1) < 350 )
                return notify_fail("你的蛤蟆功不够娴熟，不能喷毒。\n");

        if( (int)me->query_skill("lingshe-zhangfa", 1) < 350 )
                return notify_fail("你的灵蛇杖法不够娴熟，不能喷毒。\n");

        if( (int)me->query("neili", 1) < 2000 )
                return notify_fail("你的内力不够，不能喷毒。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
            return notify_fail("你使用的武器不对。\n");

        if( (string)weapon->query("id") != "guaishe zhang" )
                return notify_fail("你手中没有蛇杖，不能喷毒。\n");

        me->add("neili", -200);

        msg = MAG "$N喉间发出刺耳的格格声响，蛇杖前头的小蛇猛地扬头，一阵粉红毒雾带着甜香喷向$n。\n";

        me->start_busy(1);
        if( random( (int)me->query_skill("lingshe-zhangfa",1))
          > target->query_skill("dodge",1)/3 )
        {
                msg += MAG "结果$p被$P杖头小蛇一口喷中！\n" NOR;
                if (target->query("neili")/4 < random(me->query("neili")))
                {
                   msg += MAG "$p只闻到一阵甜香，眼前就模糊起来。\n" NOR;
                   target->receive_damage("qi",damage,me);
                   target->receive_wound("qi",damage/3,me);
                   target->receive_wound("jing", damage/5,me);
                   target->apply_condition("snake_poison", random(me->query_skill("lingshe-zhangfa",1)/10) + 1 +target->query_condition("bt_poison")); 
                   target->apply_condition("snake_poison", random(me->query_skill("lingshe-zhangfa",1)/10) + 1 +target->query_condition("bt_poison"));
                   if (userp(target)) target->add_busy(1+random(1));
                   else target->add_busy(2 + random(5));
                   message_vision(msg, me, target);
                   COMBAT_D->report_status(target);
                }
                else
                {
                   msg += CYN "$p急运内力，一口真气向蛇毒喷去，顿时蛇毒反向$P飘了回去。\n" NOR;
                   msg += MAG "$P只闻到一阵甜香，眼前就模糊起来。\n" NOR;
                   me->receive_damage("qi",damage/3,me);
                   me->receive_wound("qi",damage/5,me);
                   me->receive_wound("jing", damage/10,me);
                   me->apply_condition("snake_poison", random(me->query_skill("lingshe-zhangfa",1)/10) + 1 +me->query_condition("snake_poison"));
                   me->start_busy(1 + random(2));
                   message_vision(msg, me, target);
                   COMBAT_D->report_status(me);
                }

        } else {
                msg += CYN"可是$p急忙闪在一旁，躲了开去。\n" NOR;
                me->start_busy(3);
                message_vision(msg, me, target);
        }
        if( !target->is_killing(me) ) target->kill_ob(me);
        return 1;
}

string perform_name(){ return MAG"喷毒"NOR; }

int help(object me)
{
        write(HIC"\n灵蛇杖法之"+HIB"「喷毒」"NOR"\n\n");
        write(@HELP
	灵蛇杖法乃是白驼山武学精髓所在，欧阳锋一生以驱蛇和蛤蟆功名扬江湖，凭借此两
	大神技得意获得五绝称呼，并创立白驼山一脉武学。白驼山武学以狠辣、阴险、剧毒
	诡异为特色。灵蛇杖法的起名就与灵蛇有关，所以凭借白驼山的怪蛇杖发出此招后，
	会使得对方在防不胜防之际为蛇毒所侵染。
	注意：需装备怪蛇杖方有此功效。
	要求：当前内力 2000  以上；
		灵蛇杖法等级 350 以上；
		基本杖法等级 350 以上；
		蛤蟆功的等级 350 以上；		
		激发拳法为灵蛇拳法；
		激发招架为灵蛇杖法。

HELP
        );
        return 1;
}