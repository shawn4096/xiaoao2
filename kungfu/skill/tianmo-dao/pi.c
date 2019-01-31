// pi.c 刀劈华山，表达对五岳剑派的愤怒和不满
// cre by sohu@xojh
#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return RED"刀劈华山"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「刀劈华山」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");

	if( (int)me->query_skill("tianmo-dao", 1) < 100 )
		return notify_fail("你的天魔刀不够娴熟，无法使用刀劈华山。\n");

	if ( me->query_skill_mapped("parry") != "tianmo-dao"
	|| me->query_skill_mapped("blade") != "tianmo-dao")
		return notify_fail("你现在无法使用刀劈华山。\n");

	if( (int)me->query_skill("tianmo-gong", 1) < 100 )
		return notify_fail("你的天魔功不够高。\n");

	if((int)me->query("max_neili",1) < 1400 )
		return notify_fail("你的内力修为不够，无法使用「刀劈华山」。\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("你现在内力太弱，不能使用「刀劈华山」。\n");
	
	message_vision(RED "\n$N将刀缓缓抽出，凝气运劲，脚下步伐不断加快，形成一股气势如虹的刀气，然后猛然间劈向$n！\n"NOR,me,target);

	ap = me->query("combat_exp", 1) / 10000 ;
	dp = target->query("combat_exp", 1)/ 10000 ;

	if ( random(ap + dp) > dp
		||random(me->query_skill("blade",1))>target->query_skill("parry",1)/2){
		damage = me->query_skill("blade",1) * 4;
		damage += me->query_skill("force",1) * 4;
		damage +=me->query_skill("tianmo-gong",1)*4;
		damage = damage + random(damage);
		
		if (damage > 4500) damage = 4500+random(damage-4500)/100;
		
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		if (wizardp(me)) write("damage="+damage);
		
		me->add("neili", -250);
		me->add("jingli", -80);
		msg = HIR"\n只见$N忽然间跃起半空，施展一招「刀劈华山」，$n只觉一股凶猛至极的刀气扑面而来，一刀劈在胸口，顿时鲜血狂喷！\n"NOR;
	
	   if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
	   	}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	   message_vision(msg, me, target);
	 
	   if (me->is_fighting()
		   &&random(me->query("combat_exp")) > target->query("combat_exp")/2
		   ||random(me->query_int())>target->query_int()/3)
		{
              message_vision(CYN "$N见到$n中了此招，当即潜运天魔功，刀气霍霍，反手刀瞬间而出招！\n" NOR, me,target);
             // COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="女性"?3:1);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3);
	     } else  message_vision(YEL "$n战斗经验异常丰富，看破了$N的企图，当即躲开$N的凌厉杀气！\n" NOR, me,target);
		
	}
	else {
		message_vision(HIY"可是$p早有防备，笑道：“你在天魔刀内暗藏杀机，难道就奈何的了我？\n"NOR, me,target);
		me->add("neili", -200);
		me->add_busy(1);
		//message_vision(msg, me, target);
		}	
	me->add_busy(1+random(2));
	me->start_perform(2, "刀劈华山");
	
	return 1;
}
int help(object me)
{
        write(CYN"\n天魔刀法之「刀劈华山」："NOR"\n");
        write(@HELP
	天魔刀是日月神教的绝技之一，刀势凶猛异常，刀劈华山
	乃是教中一位长老独创的招式，再加上和五岳剑派的不世
	之仇，所以命名为到劈华山。
	注意：命中与经验值和技能有关,悟性高者会再出一招
	
	指令：perform blade.pi

要求：  
	最大内力需求 1400 以上；
	当前内力需求 500 以上；
	天魔刀法等级 100 以上；
	天魔功法等级 100 以上；
	激发刀法天魔刀法
	激发招架天魔刀法

HELP
        );
        return 1;
}
                                                                                                                                                    