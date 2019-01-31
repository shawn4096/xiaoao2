// By KinGSo@舞林 2006年4月26日 早上
//By KingSo 2006.12.31 修正添加help
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
#define HUN "「" HIR "混沌一阳" NOR "」"
string perform_name(){ return HIR"混沌一阳"NOR; }
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, p;


       

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUN "只能对战斗中的对手使用。\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUN "只能空手施展。\n");

        if (me->query_skill("jiuyang-gong", 1) < 200)
                return notify_fail("你的九阳神功还不够娴熟，难以施展" HUN "。\n");

        if (me->query_skill_mapped("cuff") != "jiuyang-gong")
                return notify_fail("你现在没有激发九阳神功为拳脚，难以施展" HUN "。\n");

        if (me->query_skill_mapped("force") != "jiuyang-gong")
                return notify_fail("你现在没有激发九阳神功为内功，难以施展" HUN "。\n");

        if (me->query_skill_prepared("cuff") != "jiuyang-gong")
                return notify_fail("你现在没有准备使用九阳神功，难以施展" HUN "。\n");

        if (me->query("neili") < 2000)
                return notify_fail("你的内力不够，难以施展" HUN "。\n");
 
        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "跨前一步，双手回圈，颇得太极之意。掌心顿时闪"
              "出一个气团，向$n" HIR "电射而去。\n" NOR;
 
        ap = me->query_skill("jiuyang-gong", 1) * 2 + me->query("con") * 20 +
             me->query_skill("force", 1);
        dp = target->query_skill("force") + target->query("con") * 10 +
             target->query_skill("force", 1);

        me->add("neili", -800);

        if (ap / 2 + random(ap) < dp)
        {
                msg += HIY "然而$n" HIY "全力抵挡，终于将$N" HIY
                       "发出的气团拨开。\n" NOR;
	        me->start_busy(3);
        } else
        {
               
                damage = ap * 5 + random(ap * 10);
                me->add("neili", -150);
              if(target->query("neili") > me->query("neili")) damage /= 2;

                if (damage > 8000) damage = 8000 + random(7000);  

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                me->add("neili", -500);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");

                msg +=HIR "$n" HIR "急忙抽身后退，可是气团射得更快，只听$p" HIR "一声惨叫，鲜血飞溅！\n" NOR;
        msg += "( $n"+eff_status_msg(p)+" )\n"; 
             me->start_busy(2);

        }
        message_vision(msg, me, target);
         me->start_perform(5,"「混沌一阳」");

        return 1;
}
int help(object me)
{
	write(HIR"\n九阳神功「混沌一阳」："NOR"\n");
        write(@HELP
       用自身雄厚的内劲逼运气流，形
       成一个旋涡伤人，威力不算很强
       大，但命中率很高。

	要求：  最大内力  2000 以上；
                当前内力  2000 以上；
                九阳神功等级 200 以上；
                激发内功为九阳神功。
                激发九阳神功为拳法。
                准备使用九阳神功。
HELP
        );
        return 1;
}

