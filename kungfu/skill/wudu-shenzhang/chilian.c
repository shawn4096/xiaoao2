#include <ansi.h>
#include <combat.h>


int final(object me, object target);

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int damage;
        int ap, dp;

     //   if (userp(me) && ! me->query("can_perform/wudu-shenzhang/shi"))
      //          return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail( "「赤练神掌」只能对战斗中的对手使用。\n");

        if (me->query_skill("force",1) < 300)
                return notify_fail("你的基本内功不够火候，难以施展「赤练神掌」。\n");
		if (me->query_skill("strike",1) < 300)
                return notify_fail("你的基本掌法不够火候，难以施展「赤练神掌」。\n");
		if (me->query("max_neili") < 3500)
                return notify_fail("你的最大内力不足，难以施展「赤练神掌」。\n");
		if (me->query("neili") < 1000)
                return notify_fail("你的当前内力不足，难以施展「赤练神掌」。\n");
		if (me->query("jingli") < 1000)
                return notify_fail("你的当前精力不足，难以施展「赤练神掌」。\n");
        if ((int)me->query_skill("wudu-shenzhang", 1) < 300)
                return notify_fail("你的五毒神掌不够娴熟，难以施展「赤练神掌」。\n");

        if (me->query_skill_prepared("strike") != "wudu-shenzhang"
			||me->query_skill_mapped("strike") != "wudu-shenzhang")
                return notify_fail("你现在没有准备五毒神掌，难以施展「赤练神掌」。\n");

        if (me->query("neili") < 1500)
                return notify_fail("你的真气不够，难以施展「赤练神掌」。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HBRED+HIW "$N" HIW "身子一纵，双方一错之际，将体内真气运于双掌之间，只见双掌微微泛出隐晦的暗紫光，猛地拍向$n。\n" NOR;
		message_vision(msg,me,target);
        ap = me->query_skill("wudu-shenzhang",1);
        dp = target->query_skill("dodge",1);
        damage=ap*me->query_skill("poison",1)/10;
		me->set_temp("wdsz/chilian",3);
		if (random(ap) > dp/2
			||random(me->query("combat_exp"))>target->query("combat_exp")/2)
        {

			target->receive_damage("qi",damage,me);
			target->receive_damage("qi",damage/4,me);
			me->add_temp("apply/attack",me->query_skill("wudu-shenzhang",1)/2);
			me->add_temp("apply/damage",me->query_skill("wudu-shenzhang",1)/4);
			COMBAT_D->do_attack(me, target,0, 3);
			COMBAT_D->do_attack(me, target,0, 3);
			COMBAT_D->do_attack(me, target,0, 3);
			me->add_temp("apply/attack",-me->query_skill("wudu-shenzhang",1)/2);
			me->add_temp("apply/damage",-me->query_skill("wudu-shenzhang",1)/4);
			if (objectp(target))
			{
				message_vision(HIR "只见$n" HIR "被$N" HIR "一掌拍中，倒退几步，却见脸色已微微泛黑。\n" NOR,me,target);
			    target->apply_condition("chilian_poison",2);
			    target->receive_wound("jing", random(400), me);
				COMBAT_D->do_attack(me, target,0, 3);
				me->start_busy(1);
			}
				//call_out("final",1,me,target); 这里万一对方死了就没信息了，不如直接写一个描述 by renlai
			
        } else
        {
                msg = CYN "可是$p" CYN "眼明手快，侧身一跳$P"
                       CYN "已躲过$N这招。\n" NOR;
                message_vision(msg, me, target);
				me->start_busy(2);
                target->start_busy(1);
        }
		me->delete_temp("wdsz/chilian");
		me->start_perform(4,"赤练毒掌");
        return 1;
}

int final(object me, object target)
{
        if (!me||!target) return 1;
      
		if (objectp(target)&&me->is_fighting())
        {
			message_vision(HIR "只见$n" HIR "被$N" HIR "一掌拍中，倒退几步，却见脸色已微微泛黑。\n" NOR,me,target);
			target->apply_condition("chilian_poison",2);
			target->receive_wound("jing", random(400), me);

        }
		//else message_vision(HIR "只见$n" HIR "被$N" HIR "一掌拍中，倒退几步，却见脸色已微微泛黑。\n" NOR,me,target);


		me->add_temp("apply/attack",me->query_skill("wudu-shenzhang",1)/2);
		me->add_temp("apply/damage",me->query_skill("wudu-shenzhang",1)/4);
		COMBAT_D->do_attack(me, target,0, 3);
		me->add_temp("apply/attack",-me->query_skill("wudu-shenzhang",1)/2);
		me->add_temp("apply/damage",-me->query_skill("wudu-shenzhang",1)/4);       
		return 1;
}
string perform_name(){ return HBRED+HIW"赤练毒掌"NOR; }

int help(object me)
{
   write(WHT"\n五毒神掌之「"HBRED+HIW"赤练毒掌"WHT"」："NOR"\n");
   write(@HELP
	古墓派弟子李莫愁的武学，并非由古墓派所传
	而是由李莫愁在五毒秘传中独自悟出的掌法，
	该掌法需贴身而战，李莫愁绰号赤练仙子，非
	但因为行事心狠手辣，亦因这门掌法之威。这
	套掌法需近身施展，发掌时掌上含有剧毒，击
	中对手时其伤口会呈现朱砂般的指印，死时更
	是脸色发黑、剧痛奇痒。	
	注意：该掌法需向李莫愁单独请教,伤害和毒计
	有关系。
	注意：set 五毒神掌 五毒 会有特效
	perform strike.chilian
	
要求：
	最大内力要求 3500 以上；
	当前精力要求 1000 以上；
	当前内力要求 1000 以上；
	五毒神掌等级 300 以上；
	基本掌法等级 300 以上；
	激发且备掌法为五毒神掌；	
	
HELP
   );
   return 1;
}
