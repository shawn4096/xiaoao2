// By KinGSo@舞林 2006年4月25日 早上
//2006.12.29添加Help
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

#define PO "「" HIY "金阳破岭" NOR "」"
string perform_name(){ return HIY"金阳破岭"NOR; }


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
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" PO "。\n");

        if ((int)me->query_skill("jiuyang-gong", 1) < 200)
                return notify_fail("你的九阳神功不够娴熟，难以施展" PO "。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的内功根基不够，难以施展" PO "。\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("你的基本剑法火候不够，难以施展" PO "。\n");

        if ((int)me->query("max_neili") < 3500)
                return notify_fail("你的内力修为不足，难以施展" PO "。\n");

        if (me->query("neili") < 1000)
                return notify_fail("你现在真气不够，难以施展" PO "。\n");

        if (me->query_skill_mapped("sword") != "jiuyang-gong") 
                return notify_fail("你没有激发九阳神功为剑法，难以施展" PO "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        message_vision(HBRED  HIY "\n$N一声长吟，内力瀑涨，全身真气贯与剑柄。手中" + weapon->name() + "光芒四射，刹那间一股强劲的剑气已涌向$n" HIY "！\n"NOR, me,target);

        me->add("neili", -150);
        ap = me->query_skill("sword") + me->query_skill("force", 1);
        dp = target->query_skill("parry") + target->query_skill("force", 1);

       me->add("neili", -150);
        ap = me->query_skill("blade") + me->query_skill("force", 1);
        dp = target->query_skill("parry") + target->query_skill("force", 1);

        me->start_perform(5,"「金阳破岭」");
        me->add("neili", -800);
         target->add_temp("apply/armor",  -ap/10);
        me->add_temp("apply/attack",  ap/8);
    //    me->add_temp("apply/damage",  ap/3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    
        me->add_temp("apply/attack",  - ap/8);
      //  me->add_temp("apply/damage",  - ap/3);
         target->add_temp("apply/armor",  ap/10);


    me->start_busy(1);
    target->start_busy(1);
    return 1;
}

int help(object me)
{
	write(HBRED HIY"\n九阳神功「金阳破岭」："NOR"\n");
        write(@HELP
       九阳神功作剑法使用时施展，强
       韧的剑气从剑尖射出，可穿破敌
       人的护体真气，给予沉重的打击。


	要求：  最大内力  3500 以上；
                当前内力  1000 以上；
                九阳神功等级 200 以上；
                基本剑法等级 200以上；
                激发内功为九阳神功。
                激发九阳神功为剑法。
               
HELP
        );
        return 1;
}
