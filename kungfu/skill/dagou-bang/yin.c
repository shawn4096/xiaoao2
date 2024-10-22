// yin.c 打狗棒法--引字诀
// Creat by looklove@SJ 3/16/2001

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HBCYN"引字诀"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int mexp, texp, mlvl, tlvl, i, j, b, n;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("「引字诀」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");
	if( !weapon
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("stick") != "dagou-bang"
	 || me->query_skill_mapped("parry") != "dagou-bang" )
		return notify_fail("你现在无法使用「引字诀」。\n");

	mexp=me->query("combat_exp");
	texp=target->query("combat_exp");

	mlvl=me->query_skill("dagou-bang",1);
	tlvl=target->query_skill("dodge",1);

	i = me->query_int(1);
	j = target->query_int(1);
	b = me->query_skill("bangjue",1);

	tweapon = target->query_temp("weapon");

	if( mlvl < 450 )
		return notify_fail("你的打狗棒法还不够娴熟，不会使用［引字诀］。\n");

	if( b < 200 )
		return notify_fail("你的打狗棒诀不够娴熟，无法使出［引字诀］。\n");

	if( me->query_skill("huntian-qigong", 1) < 450 )
		return notify_fail("你的混天气功根基不足，无法使出［引字诀］。\n");

	if( me->query("neili") < 400 )
		return notify_fail("你的内力不够。\n");

	if( me->query("jingli") < 400 )
		return notify_fail("你的精力不足以让你使出此绝技。\n");

	if( me->query("max_neili") < 2000 )
		return notify_fail("你内力修为现在不够, 不能用「引字诀」！\n");

	if( target->query_condition("no_perform") )
		return notify_fail("对方已经被你的棒招所迷惑，大胆进攻吧！\n");

	n = b / 50 + random(b/50);
	if( mlvl > 350 ) n += random(n);
	if( n > 6 ) n = 6;
	if(wizardp(me)) write(sprintf(HIR"n=%d \n"NOR,n));

	i = mexp/10000 * (mlvl + i/2);
	j = texp/10000 * (tlvl + j);
	i += COMBAT_D->skill_power(me, "stick", SKILL_USAGE_ATTACK);
	j += COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);

	if( !tweapon ) msg = HBCYN"$N卖个破绽，手中"+weapon->name()+HBCYN"轻划，使出「引字诀」，好象要被$n夺住"+weapon->name()+HBCYN"。\n"NOR;
	else msg = HBCYN"$N运起「引字诀」，手中"+weapon->name()+HBCYN"疾翻，轻搭在"+tweapon->name()+HBCYN"寸许之处！\n"NOR;
	

	if( random(i + j ) > j 
		||random(me->query_int(1))>target->query_int()/2 ) {
		if( tweapon ) msg += HBCYN"\n$n身形连闪了数次，始终摆脱不了"+weapon->name()+HBCYN"的牵引之势。\n"NOR;
		else msg += HBCYN"\n$n一见有机可乘，迅速变势为爪，连抓了数次却都碰不到"+weapon->name()+HBCYN"分毫。\n"NOR;
		msg += HBCYN""+weapon->name()+HBCYN"看似破绽百出，无数虚招划出，$n却感觉处处受制，出手艰涩。\n"NOR;
		target->add_busy(2 + random(2));
		target->set_temp("dgb/yin", n);
		target->add_condition("no_perform",n);
    }
	else {
		msg += HBCYN "$n感觉不妙，顺着"+weapon->name()+HBCYN"的来势，跳了开去。\n" NOR;
		me->start_perform(2 + random(2), "引字诀");
	}
	message_vision(msg, me, target);
	if (me->query_skill("dagou-bang",1)<450)
		me->start_busy(1+random(2));

	if (me->query_skill("dagou-bang",1)<500 )
	{
		me->start_perform(3 + random(2), "引字诀");
	}
	me->add("neili",-300);
	me->add("jingli",-150);
	return 1;
}

int help(object me)
{
	write(HBCYN"\n打狗棒「引字诀」："NOR"\n");
	write(@HELP
	打狗棒在兵器类功夫里是属于轻巧一类的，其招数十分的灵活。
	八诀中的这「引字诀」，专门用来牵制吸引住对手的兵器。这棒
	引到东，对方兵器到东，棒引到西，对方兵器就到西，被牵制住
	的对手再也无力使出强力有效的攻击。命中与技能、经验和悟性
	有关。450后取消busy,500后且解开引字诀后威力释放。

	指令：perform stick.yin

要求：
	最大内力需求 2000 以上；
	当前内力需求 400 以上；
	打狗棒法等级 450 以上；
	混天气功等级 450 以上；
	打狗棒诀等级 200 以上：
	激发招架为打狗棒。
HELP
	);
	return 1;
}
