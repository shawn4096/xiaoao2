// leiting 雷霆一击
// edited by sohu 2013

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
	object weapon;
	string msg;
	int damage, p, ap, dp;
	int focus = me->query_temp("ss/focus");
	int j;
	        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("「雷霆一击」只能在战斗中使用。\n");
        
	if( (int)me->query_skill("songshan-jian", 1) < 220 )
		return notify_fail("你的嵩山剑法还不够娴熟，无法使出「雷霆一击」。\n");
	
	if( (int)me->query_skill("force", 1) < 220 )
		return notify_fail("你的基本内功还不够娴熟，无法使出「雷霆一击」。\n");

	if( (int)me->query_skill("hanbing-zhenqi", 1) < 220 )
		return notify_fail("你的寒冰真气等级还不够，无法使出「雷霆一击」。\n");

	if (me->query_skill_mapped("force") != "hanbing-zhenqi")
		return notify_fail("你目前的内功无法使出「雷霆一击」。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "songshan-jian"
	|| me->query_skill_mapped("parry") != "songshan-jian" )
		return notify_fail("你无法使出「雷霆一击」。\n");

	if (me->query_temp("ss/leiting"))
		return notify_fail("你刚使用完「雷霆一击」，休息一下吧。\n"); 
                
	if( (int)me->query("max_neili") < 2500)
		return notify_fail("你的内力修为太差，无法使出「雷霆一击」。\n");
                
	if( (int)me->query("neili") < 1000)
		return notify_fail("你现在真气太弱，使不出「雷霆一击」。\n");
	
	j = me->query_skill("songshan-jian", 1);
	
	if ( j > 350 )
		j = to_int( j/4* j/ 350.0);

	j += focus * 5;
			
	me->set_temp("ssj/leiting",1);
	me->add_temp("apply/attack",focus * 10 );
	me->add_temp("apply/damage", (int)j/3);
	target->set_temp("combat_msg/dodge",CYN"突然之间，白影急晃，$n向后滑出丈余，立时又回到了原地。\n"NOR );
			
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER );
	
	target->delete_temp("combat_msg/dodge");
	me->add_temp("apply/damage", -(int)j/3);
	me->add_temp("apply/attack",-focus * 10 );
	
	me->delete_temp("ssj/leiting");
		
	msg = YEL"\n$N右手衣袖鼓了起来，犹似吃饱了风的帆篷一般，全身劲力都集中到了右臂之上，全力向着$n刺出。\n"NOR;

	ap = me->query("combat_exp", 1) / 100000+ focus * 10;
	dp = target->query("combat_exp",1 ) / 100000 ;

	if ( target->is_busy()||!userp(target))
		dp -= dp/3;

	if( random( ap + dp) > dp 
		||random(me->query_skill("sword",1))>target->query_skill("dodge",1)/3) {
		msg += HIR"$n被这招雷霆一击的猛击当胸一撞，立时口中鲜血狂喷而出！\n"NOR;
		damage = me->query_skill("sword",1) + me->query_skill("force",1);
		damage = damage * (focus+1);
		damage += random(damage);

		if( damage > 4500) 
			damage = 4500 + (damage- 4500)/100;

		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2, me);

		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->query("name"));
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		me->add("neili", -350);
		me->add("jingli", -150);
	} 
       else {
		msg += CYN"突然之间，白影急晃，$n向后滑出丈余，立时又回到了原地。\n"NOR;
		me->add("neili", -100);
		me->add("jingli", -80);
	}
	message_vision(msg, me, target);
	//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add("neili", -500);
	me->add("jingli", -350);
	me->start_perform(3, "雷霆一击");
	me->start_busy(random(2));
    return 1;
}

string perform_name(){ return HBWHT+HIG"雷霆一击"NOR; }

int help(object me)
{
        write(HBYEL+RED"\n嵩山剑法之「雷霆一击」："NOR"\n\n");
        write(@HELP
	嵩山剑法有“内八路，外九路”之称，总共十七路长短快慢的剑法
	应有尽有。当年五岳剑派与魔教十长老两度会战华山，五岳剑派
	的好手死伤殆尽，五派剑法的许多惊世绝招随五派高手而消逝。
	嵩山派掌门左冷禅会集本派残存的耆老，将各人所记得的剑招不
	论粗精，尽数录了下来，汇成一部剑谱。
	雷霆一击招式是嵩山派的绝技之一，乃是将自己的内力集中于一
	点，宛如山洪爆发，一招毙敌，此招需要强大的内力支持。
	
	指令：perform sword.leiting
		
要求：
	当前内力需求 1000 以上；
	最大内力需求 2500 以上；
	当前精力需求 1000 以上；
	嵩山剑法等级 220 以上；
	寒冰真气等级 220 以上；
	有效内功等级 220 以上；
	激发剑法为嵩山剑法；
	激发招架为嵩山剑法；
	激发内功为寒冰真气；
	且手持兵器。

HELP
        );
        return 1;
}
