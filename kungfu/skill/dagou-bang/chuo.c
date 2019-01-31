// chuo.c 打狗棒法--戳字诀
// Creat by Looklove@SJ 2001.4.9
// Modified by Looklove@SJ 2001.5.19
// update for condition limit by Lklv 2002.1.16

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int dgb_chuo(object me,object target,object weapon);

string perform_name(){ return HBWHT"戳字诀"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int mexp, texp, mlvl, tlvl, i, j, b, n;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「戳字诀」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");

	if( !weapon
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("stick") != "dagou-bang" )
		return notify_fail("你现在无法使用「戳字诀」。\n");

	mexp = me->query("combat_exp");
	texp = target->query("combat_exp");

	mlvl = me->query_skill("dagou-bang",1);
	tlvl = target->query_skill("dodge",1);

	i = me->query_int(1);
	j = target->query_int(1);
	b = me->query_skill("bangjue",1);

	tweapon = target->query_temp("weapon");

	if( mlvl < 200 )
		return notify_fail("你的打狗棒法还不够娴熟，不会使用「戳字诀」。\n");

	if( b < 120 )
		return notify_fail("你的打狗棒诀不够娴熟，无法使出「戳字诀」。\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 200 )
		return notify_fail("你的混天气功根基不足，无法使出「戳字诀」。\n");

	if( (int)me->query("neili") < 600 )
		return notify_fail("你的内力不够。\n");
	if( me->query_skill_mapped("force")!="huntian-qigong" )
		return notify_fail("你激发的内功不对。\n");
	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("你内力修为现在不够, 不能用「戳字诀」！\n");

	if ( target->query_condition("no_exert") || target->query_condition("no_force"))
		return notify_fail("对方已经被你的戳字诀点中，大胆进攻吧！\n");

	i = mexp/1000000*(mlvl+i);
	j = texp/1000000*(tlvl+j*2);
	i += COMBAT_D->skill_power(me, "stick", SKILL_USAGE_ATTACK);
	j += COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);

	n = b /100 + random(b/100) + mlvl/50;
	if( mlvl > 450 ) n += (mlvl-450)/50;
	if( n > 8 ) n = 8; // 击中目标最大busy 的condition数

	msg = HBWHT"$N使出打狗棒「戳字诀」，"+weapon->query("name")+HBWHT"连环不断，连点带戳直向$n周身招呼！\n"NOR;

	if( random(i+j) > j*5/4 ) {
		msg += HBWHT"$n身形闪了几闪，慌乱中一个措手不急，被"+weapon->query("name")+HBWHT"猛的戳中要穴。\n"NOR;
		msg += HBCYN+HIW"结果$n顿时面色苍白，感觉浑身内息大乱，头重脚轻。\n"NOR;
		target->add_busy(1+random(2));
		target->set_temp("dgb/chuo", n);
		target->apply_condition("no_force",n);
		target->add_busy(1);
		target->add("neili",-2000-random(1000));		
		//打掉对方部分内力
		if (target->query("neili")<0)
			target->set("neili",0);
		//戳中对方气
		target->receive_damage("qi",2000+random(1000),me);
		target->receive_wound("qi",500+random(500),me);
		message("wizard", HIG"戳字诀：时效"+n*20+"秒，使用者EXP"+mexp+"，对手EXP"+texp+"。\n"NOR, environment(me), me);
	}
	else {
		if (tweapon) msg += HBWHT"$n大吃一惊，连忙奋力用"+tweapon->query("name")+HBWHT"在"+weapon->query("name")+HBWHT"上一拨。\n"NOR;
		else msg += HBWHT "$n心中暗叫不好，用力提气纵身，跳后数步，避过了"+weapon->query("name")+HBWHT"的来势。\n" NOR;
		
		if ( random(mexp) > texp/2 ){
			msg += WHT "不料$N早已料到$n有此一招，手中"+weapon->query("name")+WHT"一转，改戳$n的脚踝。\n" NOR;
			msg += WHT ""+weapon->query("name")+WHT"来势甚急，$n已经避无可避，扑通一身，应声而倒。\n" NOR;
			target->apply_condition("no_exert",(int)n/2);
			target->add_busy(3+random(2));
			message("wizard", HIG"戳字诀：时效"+n*20/3+"秒，使用者EXP"+mexp+"，对手EXP"+texp+"。\n"NOR, environment(me), me);
		}
		
	}
	if (objectp(target))
		call_out("dgb_chuo",1,me,target,weapon);
	message_vision(msg, me, target);
	
	me->start_perform(3, "戳字诀");

	me->start_busy(1+random(2));
	me->add("neili",-500);
	me->add("jingli",-200);
	return 1;
}

int dgb_chuo(object me,object target,object weapon)
{
	
	if (!me || !target) return 0;
	
	message_vision(HIC"$N趁$n不注意，悄然转到$n身后，手中"+weapon->query("name")+HIC"疾送，使出打狗棒法中第四招“戳”字诀，忽地向$n臀上戳去。\n"NOR,me,target);

	if (random(me->query_int())>target->query_int()/3)
	{
			message_vision(HIY"\n以$n的武功修为，背后有人突施暗算，岂有不知之理？可是打狗棒法端的神奇奥妙，$n虽惊觉，急闪之际终究还是差了这么几寸，\n"+
					"噗的一下，正中臀部。饶是$n内功深厚，臀部又是多肉之处，可是这一下却也甚是疼痛，兼之出其不意，他只道定可避过，偏偏竟又戳中，\n"+
					"不由得“啊”的一声叫了出来。\n"NOR,me,target);
			target->receive_damage("qi",2000+random(1000),me);
			target->receive_wound("qi",500+random(500),me);
			target->receive_damage("jingli",100+random(500),me);

	}else {
		message_vision(HIC"$n识破了$N的意图，向前一纵身躲了开去。\n"NOR,me,target);

	}
	target->set_temp("must_be_hit",1);
	me->add_temp("apply/damage",(int)me->query_skill("dagou-bang",1)/4);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/damage",-(int)me->query_skill("dagou-bang",1)/4);
	target->delete_temp("must_be_hit");
	return 1;

}
int help(object me)
{
	write(HBWHT"\n打狗棒「戳字诀」："NOR"\n");
	write(@HELP
	打狗棒招式异常灵活，可横扫竖打，此「戳字诀」便是连点
	带戳，招招不离对手内息相关之要穴，一旦戳中，将封住对
	手之内息脉路，一定时间内使对手内息大乱而不能自行调整。
	命中与经验值和武技等级有关
	
	指令：perform stick.chuo

要求：
	最大内力需求 2000 以上；
	当前内力需求 600 以上；
	打狗棒法等级 200 以上；
	混天气功等级 200 以上；
	打狗棒诀等级 120 以上：
	激发棒法为打狗棒
	激发招架为打狗棒。
	激发内功为混天气功
	手持棒类武器
HELP
	);
	return 1;
}
