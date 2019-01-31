// By KinGSo@舞林 2006年4月25日 早上
//2006.12.29添加Help
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

#define PO "「" HIY "骄阳劈天" NOR "」"
string perform_name(){ return HBRED HIW"骄阳劈天"NOR; }


string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(PO "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对，难以施展" PO "。\n");

        if ((int)me->query_skill("jiuyang-gong", 1) < 260)
                return notify_fail("你的九阳神功不够娴熟，难以施展" PO "。\n");

        if ((int)me->query_skill("force", 1) < 260)
                return notify_fail("你的内功根基不够，难以施展" PO "。\n");

        if ((int)me->query_skill("blade", 1) < 260)
                return notify_fail("你的基本刀法火候不够，难以施展" PO "。\n");

        if ((int)me->query("max_neili") < 5500)
                return notify_fail("你的内力修为不足，难以施展" PO "。\n");

        if (me->query("neili") < 2000)
                return notify_fail("你现在真气不够，难以施展" PO "。\n");

        if (me->query_skill_mapped("blade") != "jiuyang-gong") 
                return notify_fail("你没有激发九阳神功为刀法，难以施展" PO "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        message_vision(HBRED HIW "\n$N猛然间飞身而起，半空中一声长啸，内力源源不绝地涌入" + weapon->name() + ""HBRED" "HIW",刹那间刀芒夺目，自天而下，劈向$n！\n"NOR, me,target);

        me->add("neili", -150);
        ap = me->query_skill("blade") + me->query_skill("force", 1);
        dp = target->query_skill("parry") + target->query_skill("force", 1);

        me->start_perform(5,"「骄阳劈天」");
    me->add("neili", -500);
        me->add_temp("apply/attack",  ap/8);
    //    me->add_temp("apply/damage",  ap/3);
        target->add_temp("apply/armor",  -ap/5);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    
        me->add_temp("apply/attack",  - ap/8);
    //    me->add_temp("apply/damage",  - ap/3);
        target->add_temp("apply/armor",  ap/5);

    me->start_busy(1);
    target->start_busy(1);
    return 1;
}

int help(object me)
{
	write(HBRED HIW"\n九阳神功「骄阳劈天」："NOR"\n");
        write(@HELP
       九阳神功作刀法使用时施展，凌
       厉的刀芒可贯穿敌人的防具直接
       伤其身体，给予沉重的打击。

	要求：  最大内力  5500 以上；
                当前内力  2000 以上；
                九阳神功等级 260 以上；
                基本刀法等级 260以上；
                激发内功为九阳神功。
                激发九阳神功为刀法。
               
HELP
        );
        return 1;
}


