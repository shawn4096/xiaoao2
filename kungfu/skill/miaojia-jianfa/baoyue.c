// baoyue.c 怀中抱月
// Created by sohu@xojh 2015 

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
int baoyue_back(object me);

void remove_effect(object me);

int perform(object me, object target)
{
	object weapon;
	int focus;
	int j,ap,dp,damage,p;
	string msg;
	if (me->query_skill_mapped("force") == "lengquan-shengong")
		focus =me->query_skill("force",1)+ me->query_skill("lengquan-shengong",1);
	else focus =me->query_skill("force",1);
	
	        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("「洗剑怀中抱月」只能在战斗中使用。\n");
        
	if( (int)me->query_skill("miaojia-jianfa", 1) < 350 )
		return notify_fail("你的嵩山剑法还不够娴熟，无法使出「洗剑怀中抱月」。\n");

	if( (int)me->query_skill("force", 1) < 350 )
		return notify_fail("你的基本内功等级还不够，无法使出「洗剑怀中抱月」。\n");
	if( (int)me->query_skill("sword", 1) < 350 )
		return notify_fail("你的基本剑法等级还不够，无法使出「洗剑怀中抱月」。\n");
	

	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	//|| me->query_skill_mapped("parry") != "miaojia-jianfa"
	|| me->query_skill_mapped("sword") != "miaojia-jianfa" )
		return notify_fail("你无法使出「洗剑怀中抱月」。\n");

	if (me->query_temp("mjjf/baoyue"))
		return notify_fail("你正在使用「洗剑怀中抱月」，休息一下吧。\n"); 
    if (target->is_busy())
		return notify_fail("对方已经手忙脚乱了，无需使用这招「洗剑怀中抱月」。\n"); 
           
	if( (int)me->query("max_neili") < 5000)
		return notify_fail("你的内力修为太差，无法使出「洗剑怀中抱月」。\n");
                
	if( (int)me->query("neili") < 1000)
		return notify_fail("你现在真气太弱，使不出「洗剑怀中抱月」。\n");
	if( (int)me->query("jingli") < 1000)
		return notify_fail("你现在精力太弱，使不出「洗剑怀中抱月」。\n");

	j = me->query_skill("miaojia-jianfa", 1);
			
	me->set_temp("mjjf/baoyue",1);

	me->add_temp("apply/attack",j/2);
	me->add_temp("apply/damage", j/2);
	
	target->set_temp("combat_msg/dodge",HIY"突然之间，身形一晃，$n向后滑出丈余，立时宛如弹簧一样回到了原地。\n"NOR );
			
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER );
	
	target->delete_temp("combat_msg/dodge");
	
	me->add_temp("apply/damage", -j / 2);
	me->add_temp("apply/attack",-j/2 );
	
		
	message_vision(RED"\n$n哪知$N的武功，当真练到出神入化，就在这危急之间，$N双臂一曲，剑尖陡然刺向自己的胸口。\n"
	                  +"$n大吃一惊，只道$N还剑自戕,哪里料到$N胸口一运气，那剑刺在身上，竟然反弹出来。剑柄正好点在$n胸口‘神藏穴’上\n"NOR,me,target);

	ap = me->query("combat_exp", 1) / 1000;
	dp = target->query("combat_exp",1 ) / 1000 ;
	
	if ( target->is_busy())
		dp -= dp/3;

	if( random( ap + dp) > dp 
		||random(me->query_skill("sword",1))>target->query_skill("parry",1)/2)
	{
		message_vision(HIR"\n$n被这招「洗剑怀中抱月」的反击当胸一撞，身形顿时受制，同时口中鲜血狂喷而出！\n"NOR,me,target);
		damage = me->query_skill("sword",1) + focus;
		damage = damage * (int)me->query_str()/20;
		damage += random(damage);

		if( damage > 4500) 
			damage = 4500 + (damage- 4500)/5;

		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2 + random(damage/2), me);
		
		target->add_busy(2);
		if (!userp(target))
			target->add_busy(2+random(2));
		
		if (random(2))
			target->apply_condition("no_exert",2);
		else target->apply_condition("no_perform",2);

		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg = COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg = COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->query("name"));
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		me->add("neili", -350);
		me->add("jingli", -150);
	} 
      else {
		message_vision(CYN"突然之间，白影急晃，$n向后滑出丈余，立时又回到了原地。\n"NOR,me,target);
		me->add_busy(1);
		me->add("neili", -100);
		me->add("jingli", -80);
	}
	//message_vision(msg, me, target);
	call_out("baoyue_back",2,me);
	me->add("neili", -100);
	me->add("jingli", -80);
	if (me->query_skill("miaojia-jianfa",1)<350)
		me->start_perform(3, "洗剑怀中抱月");
	else if (me->query_skill("miaojia-jianfa",1)<450)
		me->start_perform(1, "洗剑怀中抱月");
	//me->start_busy(random(2));
    return 1; 
}
int baoyue_back(object me)
{
	if (!me) return 1;
	
	if (me->query_temp("mjjf/baoyue"))
	{
		me->delete_temp("mjjf/baoyue");
		message_vision(CYN"$N双臂张开，将「洗剑怀中抱月」缓缓收招。\n"NOR,me);
		return 1;

	}

}

string perform_name(){ return RED"洗剑怀中抱月"NOR; }

int help(object me)
{
        write(YEL"\n苗家剑法之「洗剑怀中抱月」："NOR"\n\n");
        write(@HELP
	苗家剑法乃是打遍天下无敌手的苗人凤家传绝技
	该剑法胜在灵活多变，狠辣异常，几乎没有破绽
	实乃武林中不可多得的一门武技。
	「洗剑怀中抱月」是利用归自己深厚的内功，利
	用强悍的内劲将剑蜷曲在怀中，宛如自戕，随后
	利用内功反震，以剑柄点中对方穴道，然后顺手
	攻击。
	
	指令:perform sword.baoyue

要求：
	当前内力需求 1000 以上；
	最大内力需求 5000 以上；
	当前精力需求 1000 以上；
	苗家剑法等级 350 以上；
	基本内功等级 350 以上；
	基本剑法等级 350 以上；
	激发剑法为苗家剑法；
	且手持兵器。

HELP
        );
        return 1;
}
