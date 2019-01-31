// xixue.c 吸血青蝠
// By River
#include <ansi.h>

inherit F_SSERVER;
int perform(object me,object target)
{
	string msg;
	int skill, damage, p, ap, dp;
	skill = me->query_skill("hanbing-mianzhang",1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !me->is_fighting(target))
		return notify_fail("你只能对战斗中的对手使用「吸血青蝠」。\n");

	if( me->query_temp("weapon"))
		return notify_fail("你拿着武器怎么能使用「吸血青蝠」！\n");

	if( skill < 200 )
		return notify_fail("你的「寒冰绵掌」等级不够, 还不能使用「吸血青蝠」！\n");

	if( me->query_skill_mapped("strike") != "hanbing-mianzhang")
		return notify_fail("你现在无法使用「吸血青蝠」！\n");

	if (me->query_skill_prepared("strike") != "hanbing-mianzhang")
		return notify_fail("你现在无法使用「吸血青蝠」！\n");

	if ( me->query_skill_mapped("parry") != "qiankun-danuoyi"
	&& me->query_skill_mapped("parry") != "hanbing-mianzhang")
		return notify_fail("你现在无法使用「吸血青蝠」！\n");

	if( me->query_skill("dodge", 1) < 200 )
		return notify_fail("你的轻功不够，无法熟练运用「吸血青蝠」！\n");

	if( !me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 200)
		return notify_fail("你的圣火神功等级不够，无法使用「吸血青蝠」！\n");

	if((int)me->query("neili") < 400)
		return notify_fail("你的内力不够使用「吸血青蝠」。\n");

	if((int)me->query("jingli") < 200)
		return notify_fail("你的精力不够使用「吸血青蝠」。\n");

	msg = HIC"\n$N突然如同一只吸血青蝠，欺近$n的身前，张嘴便向$n的咽喉咬去。\n"NOR;

	ap = me->query("combat_exp") * me->query_str(1)/100;
	dp = target->query("combat_exp") * target->query_con(1)/100;

	if( random(ap + dp) > dp|| random(me->query_dex(1))>target->query_dex(1)/2 ) {
		msg += HIR"$n只觉得咽喉一阵剧痛，$N正咬在$n的脖子上狂吸$n的鲜血！\n"NOR;
		damage = skill*me->query_dex(1)/10;
		damage += me->query_skill("strike");
		damage += me->query_skill("force");
		if (me->query_temp("mj/shenghuo"))
		   damage += me->query_skill("shenghuo-shengong"); //圣火对吸血有加成
		damage += random(damage/2);

		me->add("neili",-250);
		me->add("jingli", -80);
        if (damage>3000) damage=3000+(damage-3000)/100;
       
		if(target->query("neili") >= skill*2)
			target->add("neili", - random(skill*2));
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/4,me);
		target->add_condition("hb_poison", skill / 15);
		target->add_busy(1+random(3));
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "啮伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "啮伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	}
	else {
		msg += CYN"只见$n不慌不忙，轻轻一闪，躲过了$N的利齿！\n"NOR;
		me->add("neili",-100);
		me->add("jingli",-50);
	}
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
	 me->start_perform(3, "吸血青蝠");
	 me->start_busy(random(2));	
	return 1;
}

string perform_name(){ return HIC"吸血青蝠"NOR; }

int help(object me)
{
        write(HIC"\n寒冰绵掌之「吸血青蝠」："NOR"\n\n");
        write(@HELP

        要求：  当前内力 400 以上；
                当前精力 200 以上；
                寒冰绵掌等级 200 以上；
                圣火神功等级 200 以上；
                基本轻功等级 200 以上；
                激发掌法为寒冰绵掌；
                激发招架为寒冰绵掌或乾坤大挪移。

HELP
        );
        return 1;
}
