// fanpi.c 反身劈山
// cre by sohu@xojh
#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return RED"反身劈山"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「反身劈山」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");

	if( (int)me->query_skill("nanshan-dao", 1) < 100 )
		return notify_fail("你的南山刀法不够娴熟，无法使用反身劈山。\n");

	if ( me->query_skill_mapped("parry") != "nanshan-dao"
	|| me->query_skill_mapped("blade") != "nanshan-dao")
		return notify_fail("你现在无法使用反身劈山。\n");

	if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("你的基本内功不够高。\n");
	if( (int)me->query_skill("blade", 1) < 100 )
		return notify_fail("你的基本刀法不够高。\n");

	if((int)me->query("max_neili",1) < 1400 )
		return notify_fail("你的内力修为不够，无法使用「反身劈山」。\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("你现在内力太弱，不能使用「反身劈山」。\n");
	
	message_vision(RED "\n$N轻身一纵，向前半步，随后一个反身，一刀劈向$n的脑门，正是南山刀法精粹「反身劈山」的绝技！\n"NOR,me,target);

	ap = me->query("combat_exp", 1) / 10000 ;
	dp = target->query("combat_exp", 1)/ 10000 ;

	if ( random(ap + dp) > dp
		||random(me->query_skill("blade",1))>target->query_skill("parry",1)/2){
		damage = me->query_skill("blade",1) * 4;
		damage += me->query_skill("force",1) * 4;
		damage = damage + random(damage);
		
		if (damage > 2500) damage = 2500+random(damage-2500)/100;
		
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		if (wizardp(me)) write("damage="+damage);
		
		me->add("neili", -250);
		me->add("jingli", -80);
		msg = HIR"\n只见$N这招「反身劈山」，招式反常，$n一时不查，被一刀劈在额头，顿时鲜血狂喷！\n"NOR;
	
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
		message_vision(HIY"可是$p早有防备，笑道：“你在南山刀内暗藏杀机，难道就奈何的了我？\n"NOR, me,target);
		me->add("neili", -200);
		me->add_busy(1);
		//message_vision(msg, me, target);
		}	
	me->add_busy(1+random(2));
	me->start_perform(2, "反身劈山");
	
	return 1;
}
int help(object me)
{
        write(CYN"\n南山刀法之「反身劈山」："NOR"\n");
        write(@HELP
	南山刀是江南七怪南山樵子南希仁的绝技之一，
	反身劈山这招极为怪异，令对手防不胜防，一刀
	出后，顿时令对方见血，非常厉害。

	指令：perform blade.fanpi

要求：  
	最大内力需求 1400 以上；
	当前内力需求 500 以上；
	南山刀法等级 100 以上；
	基本内功等级 100 以上；
	基本刀法等级 100 以上；
	激发刀法南山刀法
	激发招架南山刀法

HELP
        );
        return 1;
}
                                                                                                                                                    