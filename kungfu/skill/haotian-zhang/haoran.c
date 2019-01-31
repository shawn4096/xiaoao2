// haoran.c 浩然一击
//sohu@xojh
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage, ap,dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("浩然一击只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("haotian-zhang", 1) < 200)
                return notify_fail("你的昊天掌不够娴熟，不会使用浩然一击。\n");

        if ((int)me->query_skill("force",1) < 200)
                return notify_fail("你的内功修为不够，难以施展浩然一击。\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你现在真气不够，无法使用浩然一击。\n");

        if (me->query_skill_mapped("strike") != "haotian-zhang")
                return notify_fail("你现在没有激发昊天掌法，无法使用浩然一击。\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必须空手才能够使用浩然一击。\n");

        message_vision(HIC "$N" HIC "大喝一声，合身向$n" HIC "扑上，双掌"
              "同时击出，正是昊天掌一招「浩然一击」绝技。\n" NOR,me);
  		message_vision(HIY "$p只觉一股浩荡的劲气扑面而来，甚是威猛！\n" NOR,me,target);

        if (living(target))
                dp = target->query_skill("force") / 2;
        else    dp = 0;
		ap=me->query_skill("haotian-zhang",1);
		if (me->query_temp("xtg/wuqi"))
		{
			ap=ap+me->query_skill("xiantian-gong",1)/2;
		}
        if (random(ap) > dp
			||random(me->query_str())>target->query_str()/2)
        {
               // me->start_busy(2);
                me->add("neili", -250);
                
				damage = 250*me->query("jiali");
              
				message_vision(HIR "结果$p" HIR "被$P" HIR "的气势所摄，慌忙后退，结果被$P" HIR "一掌击了个正中，吐血不止！！\n" NOR,me,target);

				target->receive_damage("qi",damage,me);
				target->receive_wound("qi",damage/3,me);

		} else
        {
                me->start_busy(1);
                me->add("neili", -60);
                message_vision(CYN "可是$p" CYN "识破了$P"CYN "这一招，斜斜一跃避开。\n" NOR,me,target);
        }
		me->start_perform(4,"浩然一击");
		
        return 1;
}

string perform_name(){ return HIC"浩然一击"NOR; }

int help(object me)
{
        write(HIC"\n昊天掌之「浩然一击」："NOR"\n");
        write(@HELP
	昊天掌是全真教前期武功之一，属于门中核心弟子所修武功
	全凭一口真气存在，绵绵不绝，运使劲气攻击对方。此门武
	功是全真高级武功的基础，全真弟子须认真修炼。
	浩然一击是将全真劲气凝聚，然后猛然推出攻击对方，让对
	方无法躲避，只能硬抗的招式，甚是威猛，但颇为消耗内力
	
	指令：perform strike.haoran

要求：
	先天功法的等级 200  以上；
	鸳鸯连环腿等级 200  以上；
	基本腿法的等级 200  以上；
	最大的内力要求 1500 以上；
	当前内力的要求 800  以上；
	激发且备掌法为昊天掌；
	激发先天功；
	空手且备掌法为昊天掌。
HELP
        );
        return 1;
}

