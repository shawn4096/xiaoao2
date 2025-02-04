#include <ansi.h>
#include <combat.h>

#define HUAN "「" HIG "千幻神诀" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

   //  if (userp(me) && ! me->query("can_perform/wudu-shenzhang/huan"))
              //  return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUAN "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");
		if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("你基本掌法不够娴熟，难以施展" HUAN "。\n");
        if ((int)me->query_skill("wudu-shenzhang", 1) < 200)
                return notify_fail("你五毒神掌不够娴熟，难以施展" HUAN "。\n");
		if (me->query("max_neili") < 1500)
                return notify_fail("你的最大内力不足，难以施展「赤练神掌」。\n");
		if (me->query("neili") < 500)
                return notify_fail("你的当前内力不足，难以施展「赤练神掌」。\n");
		if (me->query("jingli") < 500)
                return notify_fail("你的当前精力不足，难以施展「赤练神掌」。\n");
		if (me->query_dex(1) < 50)
                return notify_fail("你的当前身法不足，难以施展「赤练神掌」。\n");
        if (me->query_skill_prepared("strike") != "wudu-shenzhang"
			||me->query_skill_mapped("strike") != "wudu-shenzhang")
                return notify_fail("你没有准备五毒神掌，难以施展" HUAN "。\n");

        if (me->query_skill("dodge",1) < 200)
                return notify_fail("你的轻功修为不够，难以施展" HUAN "。\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("你现在的真气不够，难以施展" HUAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = me->query_skill("wudu-shenzhang", 1) + me->query_skill("dodge", 1) / 2;

        dp = target->query_skill("dodge",1);

        msg = HIC "\n$N" HIC "身法陡然变快，使出绝招「" HIG "千幻神诀" HIC "」，"
              "双掌不断拍出，\n招式如影如幻，虚实难测，试图扰乱$n" HIC "的攻"
              "势。\n" NOR;

        message_vision(msg, me, target);

        if (random(ap) > dp / 2)
        {
				msg = HIY "$n" HIY "只见$N" HIY "双掌飘忽不定，毫"
                      "无破绽，竟被困在$N" HIY "的掌风之中。\n" NOR;
				message_vision(msg, me, target);

                target->start_busy(2+random(4));
               	me->start_busy(1);
                me->add("neili", -80);
        } else
        {
                msg = CYN "$n" CYN "看破$N" CYN "毫无攻击之意，于"
                      "是大胆反攻，将$N" CYN "这招尽数化解。\n" NOR;
				message_vision(msg, me, target);

                me->start_busy(2);
                me->add("neili", -30);
        }
		me->start_perform(2,"千幻神诀");
        return 1;
}
string perform_name(){ return HIG"千幻神诀"NOR; }

int help(object me)
{
   write(WHT"\n五毒神掌之「"HIG"千幻神诀"WHT"」："NOR"\n");
   write(@HELP
	古墓派弟子李莫愁的武学，并非由古墓派所传
	而是由李莫愁在五毒秘传中独自悟出的掌法，
	该掌法需贴身而战，李莫愁绰号赤练仙子，非
	但因为行事心狠手辣，亦因这门掌法之威。这
	套掌法需近身施展，发掌时掌上含有剧毒，击
	中对手时其伤口会呈现朱砂般的指印，死时更
	是脸色发黑、剧痛奇痒。	
	千幻神诀是将古墓派身法优势发挥到极致，围
	绕对手快速奔跑，以期将对方困住。

	perform strike.huan
	
要求：
	最大内力要求 1500 以上；
	当前精力要求 500 以上；
	当前内力要求 500 以上；
	五毒神掌等级 200 以上；
	基本掌法等级 200 以上；
	有效身法等级 50  以上；
	激发且备掌法为五毒神掌；	
	
HELP
   );
   return 1;
}
