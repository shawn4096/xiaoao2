//tiexian.c 铁拳成线
//by sohu
//张阿生

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIR"铁拳成线"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「铁拳成线」只能对战斗中的对手使用。\n");

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("你必须空手才能此招。\n");

	if( (int)me->query_skill("tiexian-quan", 1) < 100 )
		return notify_fail("你的铁线拳法不够娴熟，无法使用铁拳成线。\n");

	if ( me->query_skill_mapped("cuff") != "tiexian-quan"
	|| me->query_skill_mapped("parry") != "tiexian-quan")
		return notify_fail("你现在无法使用铁拳成线。\n");

	if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("你的基本内功不够高。\n");
	if( (int)me->query_skill("cuff", 1) < 100 )
		return notify_fail("你的基本拳法不够高。\n");

	if((int)me->query("max_neili") < 3000 )
		return notify_fail("你的最大内力修为不够，无法使用「铁拳成线」。\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("你当前内力太弱，不能使用「铁拳成线」。\n");
	
	msg = CYN "\n$N长长吸了一口气，猛然大喝道，“铁拳成线”，豁然一拳打出，宛如一条铁线！\n"NOR;

	ap = me->query("combat_exp", 1) / 1000 * me->query_skill("blade");
	dp = target->query("combat_exp", 1)/ 1000 * target->query_skill("parry");

	if ( random(ap + dp) > dp ){
		damage = me->query_skill("blade") * 4;
		damage += me->query_skill("force") * 4;
		damage = damage + random(damage);
		if (damage > 4500) damage = 4500+random(damage-3500)/10;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add("neili", -250);
		me->add("jingli", -80);
		msg += HIR"只见$N铁拳聚为一线，$n只觉一股气浪扑面而来，躲闪不及，一拳打中胸口，大口吐血！\n"NOR;
	
	   if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
	   	}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	   message_vision(msg, me, target);
			
	}
	else {
		msg += CYN"可是$p早有防备，笑道：“你在铁线拳法威力大是大，但又奈何的了我？\n"NOR;
		me->add("neili", -100);
		message_vision(msg, me, target);
		}	
	me->start_busy(1+random(2));
	me->start_perform(3, "铁拳成线");
	
	return 1;
}
int help(object me)
{
        write(CYN"\n铁线拳之「铁拳成线」："NOR"\n");
        write(@HELP
	铁线拳乃是江南奇怪老五张阿生的绝学，因其常年在屠宰
	场所和蛮牛角力，练就了一声横练功夫，铁线拳一方面是
	攻敌成线，颇为耗费内力，同时也具有一定铁布衫的功效

	指令：perform cuff.tiexian

要求：  
	最大内力需求  1400 以上；
	当前内力需求  500  以上；
	基本拳法等级 250 以上；
	基本内功等级 250 以上；
	铁线拳法等级 100 以上；
	激发拳法铁线拳；
	激发招架铁线拳；
	空手且备铁线拳；
HELP
        );
        return 1;
}
                                                                                                                                                    