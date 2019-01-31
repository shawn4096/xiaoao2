// tiannu.c  天女散花
//cre by sohu@xojh 2014
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「天女散花」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
		
	if( (int)me->query_skill("tianyu-qijian", 1) < 150 )
		return notify_fail("你的天羽奇剑不够娴熟，不会使用。\n");
	if( me->query_skill_mapped("sword")!="tianyu-qijian"
		||me->query_skill_mapped("parry")!="tianyu-qijian")
		return notify_fail("你没有激发天羽奇剑，不会使用。\n");                        
	if( (int)me->query_skill("bahuang-gong", 1) < 150 )
		return notify_fail("你的八荒六合唯我独尊功不够高。\n");
			
	if( (int)me->query("neili", 1) < 600 )
		return notify_fail("你现在内力太弱，不能使用「天女散花」。\n");
			
	msg = CYN "$N凝神息气，手腕疾抖，"+weapon->query("name")+CYN"在手中挽出千万个剑花，铺天盖地飞向$n。\n"NOR;

	if (random(me->query_skill("sword",1)) > target->query_skill("parry",1)/2
		||random(me->query_skill("combat_exp"))>target->query("combat_exp")/2)
	{
		if (me->query("gender")=="女性"&& me->query("per")>28)
		{
				msg += HIG "$N风姿卓著，玉骨冰肌，宛如云中仙子，$n神情不由地一呆。\n"NOR;
				target->add_busy(2);
		}
		if (!userp(target)) target->add_busy(2);
			//target->start_busy( (int)me->query_skill("tianyu-qijian") / 20 + 1);
		
		damage = (int)me->query_skill("bahuang-gong", 1);
		damage = damage +  (int)me->query_skill("tianyu-qijian", 1);
		damage = damage +  (int)me->query_skill("sword", 1);
		damage=damage*me->query("per")/5;
		if (damage>5000) damage=5000+random(1000);
		
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		me->add("neili", -100);
		msg += HIR"只见$N剑花聚为一线，穿向$n,\n$n只觉一股热流穿心而过，喉头一甜，鲜血狂喷而出！\n"NOR;
		me->start_busy(random(2));
	} else 
	{
		msg += CYN"可是$p猛地向前一跃,跳出了$P的攻击范围。\n"NOR;
		me->add("neili", -100);
		me->start_busy(2);
	}
	message_vision(msg, me, target);
	me->start_perform(3,"「天女散花」");
	return 1;
}
string perform_name(){ return CYN"天女散花"NOR; }

int help(object me)
{
        write(WHT"\n天羽奇剑之「天女散花」："NOR"\n\n");
        write(@HELP
	天羽奇剑乃是天山童姥绝学之一，因天山派
	渊源和逍遥派休戚相关，乃三大分支之一，
	所以天羽奇剑的意境含有天然的虚幻飘渺之
	意，看似风轻云淡，但其中却蕴藏无限杀机
	「天女散花」此招乃模仿天女之态，以剑化
	花，零落散下，形成一片密集的剑网，将对
	方置于其中，形成疾风暴雨式的攻击。
	注意：此招漂亮女性略有优势。
		
	perform sword.tiannu

要求：
	当前内力要求 600 以上;
	天羽奇剑等级 150 以上；
	基本剑法等级 150 以上；
	八荒功法等级 150 以上；
	激发剑法为天羽奇剑；
	激发招架为天羽奇剑；
	需手持剑类兵器。


HELP
        );
        return 1;
}
