// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <combat.h>

#define SUO "「" HBWHT+HIR "雪锁千山" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
      //  string *limbs, limb;



        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(SUO "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(SUO "只能空手施展。\n");

        if ((int)me->query_skill("shentuo-zhang", 1) < 350)
                return notify_fail("你神驼雪山掌火候不够，难以施展" SUO "。\n");
        if ((int)me->query_skill("hamagong", 1) < 350)
                return notify_fail("你蛤蟆功火候不够，难以施展" SUO "。\n");
        if ((int)me->query_skill("strike", 1) < 350)
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
		if ((int)me->query_str() < 60)
                return notify_fail("你的后天臂力不足60，难以施展" SUO "。\n");
        if (!living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
		if (!me->query("quest/bt/stxsz/hubei/pass"))
				return notify_fail("你尚未受到领悟这神驼雪山掌的精髓，难以施展" SUO "。\n");
		if (target->is_busy())
		{
			return notify_fail("对方已经手忙脚乱之中，无需那么费劲了！\n");
		}
        msg = HIW "$N" HIW "身形闪动，在行进间连续拍出数掌，阴风汹涌，形成一个阴劲旋涡，试图将$n"HIW"陷在当地。\n" NOR;
        me->add("neili", -100);

        ap =  me->query_skill("force",1);
        dp = target->query_skill("dodge",1);

        if (ap / 2 + random(ap) > dp
			||random(me->query_skill("strike",1))>target->query_skill("parry",1)/2)
        {
              msg +=HIR "霎时$n" HIR "被这股汹涌的阴风所罩住，身形不稳，跌跌撞撞。\n" NOR;
                                                   
               target->add_busy((int)me->query_skill("shentuo-zhang",1)/10);
               me->add("neili", -150);
				if (me->query_temp("hmg/powerup"))
				{				
					msg+=HIR "$N气起丹田，突然发出一声声青蛙的鸣叫，声音怪异，宛如破裂之音！\n" NOR;

				}
				if ((int) me->query("combat_exp",1)/2 >=  random((int) target->query("combat_exp",1)))
				{
					damage = me->query_skill("shentuo-zhang",1)*me->query_str(1)/10;          

					if (damage >=1200) damage=1200;
					target->receive_damage("jing",-random(damage),me);
					target->apply_condition("no_exert",1);
					target->add_busy(2);

					msg+=HIB"$n觉得$N这声青蛙鸣叫难听至极，头痛欲裂，差点儿晕了过去。\n"NOR;
				}

        } else	
        {
                msg += CYN "可是$n" CYN "看破了$P"
                       CYN "的企图，向旁躲开。\n"NOR;
                me->start_busy(1);
                me->add("neili", -50);
        }
        message_vision(msg,me,target);
		  
        return 1;
}

string perform_name(){ return HBWHT+HIB"雪锁千山"NOR; }

int help(object me)
{
	write(HIC"\n神驼雪山掌之「雪锁千山」："NOR"\n");
	write(@HELP
	神陀雪山掌乃是白驼山庄主任欧阳锋的独门绝技，既有
	神陀的雄俊之态，又有雪山阴柔之气。施展过程中，可
	以通过此招陷敌于雪旋涡中。
	
	指令：perform strike.xuesuo

要求：
	当前精力的需求 500 以上；
	当前内力的需求 500 以上；
	神驼雪山掌等级 350 以上；
	蛤蟆功等级     350 以上；
	基本掌法的等级 350 以上；
	后天臂力大于   50  以上；
	激发掌法为神驼雪山掌；
	激发内功为蛤蟆功
	空手且备用；
HELP
	);
	return 1;
}

/**/