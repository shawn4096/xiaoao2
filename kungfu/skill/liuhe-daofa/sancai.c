// sancai.c  奇门三才刀

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return CYN"奇门三才刀"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「奇门三才刀」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");

	if( (int)me->query_skill("liuhe-daofa", 1) < 100 )
		return notify_fail("你的六合刀法不够娴熟，无法使用奇门三才刀。\n");

	if ( me->query_skill_mapped("parry") != "liuhe-daofa"
	|| me->query_skill_mapped("blade") != "liuhe-daofa")
		return notify_fail("你现在无法使用奇门三才刀。\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 100 )
		return notify_fail("你的混天气功不够高。\n");

	if((int)me->query("max_neili",1) < 1400 )
		return notify_fail("你的内力修为不够，无法使用「奇门三才刀」。\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("你现在内力太弱，不能使用「奇门三才刀」。\n");
	
	msg = CYN "\n$N面色忽变，步法飘忽不定，手腕疾抖，千万个刀花如漫天飘雪，铺天盖地飞向$n。\n"NOR;

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
		msg += HIR"只见$N足踏天地人奇门三才刀光聚为一线，$n只觉一股热流扑面而来，躲闪不及，连中数刀鲜血狂喷而出！\n"NOR;
	
	   if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
	   	}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	   message_vision(msg, me, target);
	   if (me->is_fighting()&&random(me->query("combat_exp")) > target->query("combat_exp")/2||random(me->query_int())>target->query_int()/3)
		{
              message_vision(HIY "$N多年拼杀经验非常丰富，见到$n中了此招，当即潜运混天气功，趁$n防备不周又连攻两招！\n" NOR, me,target);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="女性"?3:1);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="女性"?3:1);
	     } else  message_vision(HIY "$n战斗经验异常丰富，看破了$N的企图，当即躲开$N的凌厉杀气！\n" NOR, me,target);
		
	}
	else {
		msg += CYN"可是$p早有防备，笑道：“你在六合刀法内暗藏奇门三才，难道就奈何的了我？\n"NOR;
		me->add("neili", -100);
		message_vision(msg, me, target);
		}	
	me->start_busy(1+random(2));
	me->start_perform(2, "三才刀");
	
	return 1;
}
int help(object me)
{
        write(CYN"\n四象六合刀「奇门三才刀」："NOR"\n");
        write(@HELP
	奇门三才刀乃是丐帮吴长老绝学，采用四象六合之意，将
	犀利的刀法蕴含其中。该绝技需要较高的经验和悟性配合
	方显威力。女性玩家有略为优势。
	
	指令：perform blade.sancai

要求：  
	最大内力  1400 以上；
	当前内力  500 以上；
	四象六合刀等级 100 以上；
	混天气功等级 100 以上；
HELP
        );
        return 1;
}
                                                                                                                                                    