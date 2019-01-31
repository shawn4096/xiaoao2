// pi.c 打狗棒法--劈字诀
// Creat by looklove@SJ 3/21/2001
// Mofify by looklove 2001.4.8
// Update by lsxk@hsbbs 2007/7/2

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HBRED"劈字诀"NOR; }
int perform(object me, object target)
{
	string msg;
	int mlvl, tlvl, damage, i, j, b, mexp, texp, p, ap, dp, m;
	object weapon, tweapon;

	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「劈字诀」只能在战斗中使用。\n");

	if (!objectp(weapon)
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("stick") != "dagou-bang"
	 || me->query_skill_mapped("parry") != "dagou-bang" )
		return notify_fail("你手中无棒，无法使用「劈字诀」！\n");

	mexp=me->query("combat_exp");
	texp=target->query("combat_exp");

	mlvl=me->query_skill("dagou-bang",1);
	tlvl=target->query_skill("dodge", 1);

	i = me->query_int(1);
	j = target->query_int(1);
	b = me->query_skill("bangjue",1);

	tweapon = target->query_temp("weapon");

	if( (int)me->query_con(1) < 60 )
		return notify_fail("你体质太弱,恐怕现在不能使用「劈字诀」。\n");

   if( (int)me->query_skill("huntian-qigong", 1) < 350 )
		return notify_fail("你的混天气功修为不够，使不出「劈字诀」绝技。\n");

	if( me->query_skill_mapped("force") != "huntian-qigong" )
		return notify_fail("没有混天气功作为根基，是无法使出「劈字诀」绝技的！\n");

   if( (int)me->query_skill("dagou-bang",1) < 350 )
		return notify_fail("你的打狗棒法修为不够,目前还不能使用「劈字诀」！\n");

   if( (int)me->query_skill("bangjue",1) < 150 )
		return notify_fail("「劈字诀」是以打狗棒诀为基础的，你棒决不熟如何使用？\n");

   if( (int)me->query("max_neili") < 2500 )
		return notify_fail("你内力修为现在不够, 不能用「劈字诀」！\n");

	if( (int)me->query("neili") < 800 )
		return notify_fail("你内力用尽, 不能用「劈字诀」！\n");

	if( (int)me->query("jingli") < 600 )
		return notify_fail("你现在没有足够的精力使用「劈字诀」。\n");


    msg = HBRED"\n$N使出打狗棒法「劈字诀」，挥舞起手中"+weapon->name()+HBRED"如狂风暴雨向$n劈头盖脸得打去！\n"NOR;

	ap = mexp/1000000 * (i + me->query_skill("stick",1)/10);
	dp = texp/1000000 * (j + target->query_skill("dodge",1)/10);
	//ap += COMBAT_D->skill_power(me, "stick", SKILL_USAGE_ATTACK);
	//dp += COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);

	if( dp < 1 ) dp = 1;

	if( random(ap + dp ) > dp
		||random(me->query_skill("stick",1))>target->query_skill("dodge",1)/2){
		msg += HBRED"\n$n只觉得眼花缭乱，一个不留神，被"+weapon->query("name")+HBRED"一招重重的劈中！\n"NOR;
		damage = mlvl*b + me->query_skill("huntian-qigong",1)*(2+random(i))/4;
/*
		if( me->query_skill("dagou-bang", 1) > 350 ) 
			m = 4000 + ( me->query_skill("dagou-bang", 1) - 350 ) * 10 + random(1500);
		else m = 4000;

		if( damage > m )
			damage = m + random(damage-m)/5;*/
	
		if(userp(target) && damage > 5000 )
			damage = 5000 + random(damage-5000)/100;		
		if (damage>8000) damage=8000+random(damage-8000)/100;
		if (!userp(me)) damage=damage/2;
		
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/4, me);
		target->receive_damage("jingli",damage/10,me);
        
		if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+damage+ WHT"点攻击伤害。\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR);

		if( random(2) ) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "棒伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "棒伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		me->add("neili", -400);
		if(me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		//if(me->is_fighting(target))
			//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	}
	else if( random(mlvl) > tlvl/2 ) {
		msg += HBRED"$n只感觉天旋地转，四处都是"+weapon->name()+HBRED"，避无可避，连连中招！\n"NOR;
		damage = mlvl*3+b*(2+random(i));

		if( me->query_skill("dagou-bang", 1) > 300 ) 
			m = 3000 + ( me->query_skill("dagou-bang", 1) - 300 ) * 10 + random(500);
		else m = 3000;

		if( damage > m )
			damage = m + random(damage-m)/5;
		if( damage > 6000 )
			damage = 6000 + random(damage-6000)/100;

		target->receive_damage("qi",damage, me);
		target->receive_wound("qi", random(damage)/2,me);
		target->receive_damage("jingli",damage/10, me);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "棒伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "棒伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		me->add("neili", -300);
		me->add("jingli", -100);
	}
       	else {
          	msg+=HIC"$n大惊失色，慌乱中一个就地十八滚，堪堪避过$N的"+weapon->name()+HIC"。\n"NOR;
          	me->add("neili", -200);
	}
	me->start_busy(random(2));
	me->add("jingli", -150);
	me->start_perform(3, "「劈字诀」");
	message_vision(msg, me, target);
	return 1;
}

int help(object me)
{
	write(HBRED"\n打狗棒「劈字诀」："NOR"\n");
	write(@HELP
	打狗棒中霸气十足的招数，当此莫属。此招出手，往往自己
	也无法控制威力，必杀一击。当者披靡。乃是打狗棒中招式
	比较爆烈的一招。命中与经验值武技等级以及悟性有关
	
	指令：perform stick.pi

要求：
	后天根骨大于 60 ；
	最大内力需求 2500 以上；
	当前内力需求 800 以上；
	当前精力需求 600 以上；
	打狗棒法等级 350 以上；
	混天气功等级 350 以上；
	打狗棒诀等级 150 以上：
	激发棒法打狗棒法	
	激发招架为打狗棒。
	激发内功混天气功
HELP
	);
	return 1;
}
