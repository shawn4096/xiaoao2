// chou.c  五毒鞭 甩抽

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return RED"大甩抽"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「甩抽」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "whip")
		return notify_fail("你使用的武器不对。\n");

	if( (int)me->query_skill("wudu-bian", 1) < 100 )
		return notify_fail("你的五毒鞭不够娴熟，无法使用甩抽。\n");

	if ( me->query_skill_mapped("parry") != "wudu-bian"
	|| me->query_skill_mapped("whip") != "wudu-bian")
		return notify_fail("你现在无法使用甩抽。\n");

	if( (int)me->query_skill("tianmo-gong", 1) < 100 )
		if( (int)me->query_skill("xixing-dafa", 1) < 100 )
		return notify_fail("你的特殊内功不够高。\n");

	if((int)me->query("max_neili",1) < 1400 )
		return notify_fail("你的内力修为不够，无法使用「甩抽」。\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("你现在内力太弱，不能使用「甩抽」。\n");
	
	msg = CYN "\n$N面色忽变，步法飘忽不定，手腕疾抖，手中"+weapon->query("name")+CYN"一个大甩抽抽向$n的面颊。\n"NOR;

	ap = me->query("combat_exp", 1) / 10000 ;
	dp = target->query("combat_exp", 1)/ 10000 ;
	if (me->query("gender")=="女性")
	{
		ap+=ap/2;
	}else ap=ap/2;
	if ( random(ap + dp) > dp
		||random(me->query_skill("whip",1))>target->query_skill("parry",1)/2)
	{
		damage = me->query_skill("whip",1)*2;
		damage += me->query_skill("force",1)*2;
		damage = damage*3 + random(damage);
		if (damage > 2500) damage = 2500+random(damage-2500)/100;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add("neili", -250);
		me->add("jingli", -80);
		msg += HIR"\n只见$N闪烁不定，甩动长鞭“啪”的一声山响，$n躲闪不及，为$N一鞭抽的满脸桃花开！\n"NOR;
	
	   if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
	   	}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	   message_vision(msg, me, target);
	   if (me->query("gender")=="女性")
	   {
			
			target->add_busy(1);
		}
	}
	else {
		msg = WHT"可是$p早有防备，笑道：“你这五毒鞭能奈何的了我？\n"NOR;
		me->add("neili", -100);
		message_vision(msg, me, target);
		}	
	me->start_busy(1+random(2));
	me->start_perform(3, "大甩抽");
	
	return 1;
}
int help(object me)
{
        write(CYN"\n五毒鞭法「大甩抽」："NOR"\n");
        write(@HELP
	五毒鞭法乃是五毒教根据教中五种神物的研究而创立的一门
	武学，讲究灵动犀利、阴险毒辣，且带毒，舞动之际，宛如
	蛟龙出海，万毒喷发，厉害非常。若配合天魔手，则会产生
	意外的招式。
	注意：命中与经验值和招式等级有关联，女性有优势
	
	指令：perform whip.shuaichou

要求：
	当前内力要求 500 以上；
	当前精力要求 300 以上；
	基本鞭法要求 100 以上；
	灵蛇鞭法要求 100 以上；
	基本身法等级 100 以上；
	激发鞭法为灵蛇鞭法。
	激发招架为灵蛇鞭法。
	手持鞭类武器；

HELP
        );
        return 1;
}
                                                                                                                                                    