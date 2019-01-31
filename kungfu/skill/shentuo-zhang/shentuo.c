// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <combat.h>

#define SUO "「" CYN "神驼骏足" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        int ap, dp, damage;
        string msg, pmsg;
        string *limbs, limb;



        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(SUO "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(SUO "只能空手施展。\n");

        if ((int)me->query_skill("shentuo-zhang", 1) < 100)
                return notify_fail("你神驼雪山掌火候不够，难以施展" SUO "。\n");
        if ((int)me->query_skill("hamagong", 1) < 100)
                return notify_fail("你蛤蟆功火候不够，难以施展" SUO "。\n");
        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你基本掌法火候不够，难以施展" SUO "。\n");
		if (me->query_skill_mapped("strike") != "shentuo-zhang"
			||me->query_skill_prepared("strike") != "shentuo-zhang")
                return notify_fail("你没有激发神驼雪山掌，难以施展" SUO "。\n");
       if (me->query_skill_mapped("force") != "hamagong")
                return notify_fail("你没有激发蛤蟆功，难以施展" SUO "。\n");

        if ((int)me->query("neili", 1) < 500)
                return notify_fail("你现在的真气不足，难以施展" SUO "。\n");
        if ((int)me->query("jingli", 1) < 500)
                return notify_fail("你现在的精力不足，难以施展" SUO "。\n");
		if ((int)me->query_str() < 50)
                return notify_fail("你的后天臂力不足50，难以施展" SUO "。\n");
        if (!living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "一声冷笑，双脚发力，一式"HIW"「神驼骏足」"HIR"，身形正对$n迎上，奋起神威。\n"
				HIY+"扬手拍出一掌，阳刚之气迸发如怒涛汹涌。\n" NOR;
        me->add("neili", -100);

        ap =  me->query_skill("strike",1);
        dp = target->query_skill("parry",1);

        if (ap / 2 + random(ap) > dp
			||random(me->query_str(1))>target->query_str(1)/2)
        {
                damage = me->query_skill("shentuo-zhang",1)*me->query_str(1)/10;               


				target->add("qi",-damage*2,me);
				target->add("eff_qi",-damage,me);
				target->apply_condition("snake_poison",2+random(1));
				target->apply_condition("chanchu_poison",2+random(4));

                msg +=RED "霎时只听「喀嚓」一声脆响，$n"RED "的"
                        "胸口肋骨竟然断了几根。\n" NOR;
                                                   
                //me->start_busy(1);
                me->add("neili", -50);
        } else 
        {
                msg += CYN "可是$n" CYN "看破了$P"
                       CYN "的企图，身形急动，躲开了这一掌。\n"NOR;
                me->start_busy(1);
                me->add("neili", -50);
        }
        message_vision(msg,me,target);
		me->start_busy(1);
		me->start_perfomr(3,"神驼骏足");
        return 1;
}

string perform_name(){ return CYN"神驼骏足"NOR; }

int help(object me)
{
	write(HIC"\n神驼雪山掌之「神驼骏足」："NOR"\n");
	write(@HELP
	神陀雪山掌乃是白驼山庄主任欧阳锋的独门绝技，既有
	神陀的雄俊之态，又有雪山阴柔之气。施展过程中，刚
	猛异常。因白驼山庄以养蛇和蛤蟆，所以掌法中蕴含蛇
	毒与蛤蟆毒。
	神驼骏足是宛如神驼奋起扬蹄，踢向对方的招式。一招
	制敌。
	
	指令：perform strike.shentuo

要求：
	当前精力的需求 500 以上；
	当前内力的需求 500 以上；
	神驼雪山掌等级 100 以上；
	蛤蟆功等级     100 以上；
	基本掌法的等级 100 以上；
	后天臂力大于   50  以上；
	激发掌法为神驼雪山掌；
	激发内功为蛤蟆功
	空手且备用；
HELP
	);
	return 1;
}

