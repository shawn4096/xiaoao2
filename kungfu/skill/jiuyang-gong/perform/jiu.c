// By KinGSo@舞林 2006年4月25日 早上

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

#define JIU "「" HIR "九曦混阳" NOR "」"
string perform_name(){ return HBRED "九曦混阳"NOR; }

 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if( !target ) target = offensive_target(me);

        if( !objectp(target) 
        || !target->is_character() 
        || !me->is_fighting(target) 
        || !living(target))
                return notify_fail(JIU "只能对战斗中的对手使用。\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(JIU "只能空手施展。\n");
                
        if (me->query("max_neili") < 6000)
                return notify_fail("你的内力的修为不够，现在无法使用" JIU "。\n");

        if (me->query_skill("jiuyang-gong", 1) < 350)
                return notify_fail("你的九阳神功还不够娴熟，难以施展" JIU "。\n");

        if (me->query_skill_mapped("cuff") != "jiuyang-gong")
                return notify_fail("你现在没有激发九阳神功为拳脚，难以施展" JIU "。\n");

        if (me->query_skill_mapped("force") != "jiuyang-gong")
                return notify_fail("你现在没有激发九阳神功为内功，难以施展" JIU "。\n");

        if (me->query_skill_prepared("cuff") != "jiuyang-gong")
                return notify_fail("你现在没有准备使用九阳神功，难以施展" JIU "。\n");

        if ((int)me->query("neili") < 2000)
                return notify_fail("你的真气不够，无法运用" JIU "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "大喝一声，顿时一股浩荡无比的真气至体内迸发，双掌"
              "猛然翻滚，朝$n" HIR "闪电般拍去。\n" NOR;

        ap = me->query_skill("cuff") + (me->query("con") * 10);
        dp = target->query_skill("parry") + (target->query("con") * 10);

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 15;
                msg += HIR "$n" HIR "只觉周围空气炽热无比，又见无数气团向"
                       "自己袭来，顿感头晕目眩，不知该如何抵挡。\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "只见$N" HIY "无数气团向自己袭来，连"
                       "忙强振精神，勉强抵挡。\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/damage", count);
        me->add_temp("apply/attack", count);

        me->add("neili", -2000);

        for (i = 0; i < 9; i++)
        {
                if (!target) break;
                if ( !me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 3);
        }

        me->start_busy(1 + random(2));
        me->add_temp("apply/damage", -count);
        me->add_temp("apply/attack", -count);     
        me->start_perform(5,"「九曦混阳」");
        return 1;
}
int help(object me)
{
	write(HBRED"\n九阳神功「九曦混阳」："NOR"\n");
        write(@HELP
       混沌一阳的升级招数，只有先练
       成了混沌一阳之后才能施展。战
       斗中同时激射出数个威力超凡的
       旋涡气团，伤敌于无形。

	要求：  最大内力  6000 以上；
                当前内力  2000 以上；
                九阳神功等级 350 以上；
                激发内功为九阳神功。
                激发九阳神功为拳法。
                准备使用九阳神功。
HELP
        );
        return 1;
}

