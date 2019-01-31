// chan.c 打狗棒法--缠字诀
// Modify by looklove@SJ 3/16/2001
// Update by lsxk@hsbbs 2007/7/2

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HBGRN"缠字诀"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int busy, mexp, texp, mlvl, tlvl, x, y, b;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「缠字诀」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");

	if( !objectp(weapon)
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("stick") != "dagou-bang" )
		return notify_fail("你现在无法使用「缠字诀」。\n");
	if( me->query_temp("dgb/zhuan") )
		return notify_fail("你正在使用「转字诀」。\n");

	if( me->query_temp("dgb/chan") )
		return notify_fail("你正在使用「缠字诀」。\n");

	mexp = (int)me->query("combat_exp");
	texp = (int)target->query("combat_exp");
	mlvl = (int)me->query_skill("dagou-bang",1);
	tlvl = (int)target->query_skill("dodge");

	x = me->query_int(1);
	y = target->query_int(1);
	b = me->query_skill("bangjue",1);

	tweapon = target->query_temp("weapon");

	if( mlvl < 100 )
		return notify_fail("你的打狗棒法还不够娴熟，不会使用「缠字诀」。\n");
	if( b < 100 )
		return notify_fail("你的打狗棒诀不够娴熟，无法使出「缠字诀」。\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 100 )
		return notify_fail("你的混天气功根基不足，无法使出「缠字诀」。\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("你的内力不够，无法使出「缠字诀」。\n");

	if( (int)me->query("jingli") < 100 )
		return notify_fail("你的精力不足以让你使出「缠字诀」。\n");
	if( (int)me->query_skill("bangjue",1) < 100 )
		return notify_fail("你的棒诀等级不足以让你使出「缠字诀」。\n");

	if( (int)me->query("max_neili") < 1000 )
		return notify_fail("你的内力不够支持你使用「缠字诀」。\n");

	if( target->is_busy()||target->query_temp("dgb/chan") )
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

	if( x >= y ) {
		busy = 4+(x-y)/2 + random(x-y);
       		busy += random(b/40);
	}
	else {
		busy = 3+(y-x)/5;
		busy += random(b/50);
	}

	if( mexp > texp ) busy += mexp/(texp+1);
	if( busy > 8 ) busy = 8;
	if( mlvl > 500 ) busy += (mlvl-500)/100;


	if( wizardp(me) ) write(sprintf(HIR"busy=%d\n"NOR,busy));
//1m以后打狗棒才飞 
	x = mexp/1000000*mlvl;
	y = texp/1000000*tlvl;
	x += COMBAT_D->skill_power(me, "stick", SKILL_USAGE_ATTACK);
	y += COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);
	
	message_vision(HIW"那"+weapon->query("name")+HIW"有如一根极坚韧的细藤，缠住了大树之后，任那树粗大数十倍，不论如何横挺直长，休想再能脱却束缚！\n"NOR,me,target);

	msg = HBGRN+HIW"$N信手使出「缠字诀」，手中"+weapon->query("name")+HBGRN+HIW"舞成一团棒影，直往$n罩了过去。\n"NOR;
	if( tweapon )
		msg += HBGRN+HIW"只见$n的"+tweapon->query("name")+HBGRN+HIW"挥到东，"+weapon->query("name")+HBGRN+HIW"就跟向东，"+tweapon->query("name")+HBGRN+HIW"打到西，"+weapon->query("name")+HBGRN+HIW"随到西。\n"NOR;
	else
		msg += HBGRN+HIW"只见"+weapon->query("name")+HBGRN+HIW"如影随形，招招不离$n周身大穴，当真精妙无比。\n"NOR;

	message("wizard", HIG"缠字诀：busy回合数"+busy+"，使用者EXP"+mexp+"，对手EXP"+texp+", "+x+","+y+"。\n"NOR, environment(me), me);
	
	me->set_temp("dgb/chan",1);

	if( random(x) > y/2 ||random(me->query_int())>target->query_int()/3 ){
		msg += HIM "$n左蹿右跳，始终逃不出棒影，无论闪向哪里，都有"+weapon->query("name")+HIM"随后跟到。\n" NOR;
		target->add_busy(busy);
		//target->set_temp("dgb/chan", 1);
		//call_out("check_fight", 1, me, target, weapon, busy);
	}
	else if( random(x+y) > y ){
		msg += HIM "结果$n顿时手忙脚乱，施展出浑身解数，也脱不开$N的棒影。\n" NOR;
		target->add_busy(busy);
		//target->set_temp("dgb/chan", 1);
		//call_out("check_fight", 1, me, target, weapon, busy);
	}
	else if( random(y) > x/2 ){
		msg += HIW "$n见势不好，大喝一声：“我打！”$N不由心神激荡，棒影随后落空。\n" NOR;
		me->start_perform(2, "缠字诀");
		me->add_busy(1+random(2));
	}
	else {
		msg += HIW "$n镇定自若，寻个破绽，信手在"+weapon->query("name")+HIW"上一点，漫天棒影顿时消失了。\n" NOR;
		me->start_perform(3, "缠字诀");
		me->start_busy(1+random(2));
	}
	me->add("neili", -260);
	me->add("jingli", -160);
	//350后小飞
	if (me->query_skill("dagou-bang",1)<350)
		me->start_perform(2, "缠字诀");

	if (!me->query("quest/gb/dgb/bangjue/pass"))
		me->start_perform(2, "缠字诀");
    
	//me->start_perform(5, "缠字诀");
	
	message_vision(msg, me, target);
	//me->delete_temp("dgb/chan");
	call_out("remove_effect",6-mlvl/100,me);
	return 1;
}

int remove_effect(object me)
{
	if (!me)
		return 0;
	me->delete_temp("dgb/chan");
	message_vision(HIW"$N的打狗棒缠字诀收功完毕！\n"NOR,me);	
	return 1;
	
	
}

int help(object me)
{
	write(HBGRN"\n打狗棒「缠字诀」："NOR"\n");
	write(@HELP
	昔年洪七公以打狗棒之轻灵奇巧，跻身当世五大高手。
	这打狗棒「缠字诀」，正是洪七公当年惯使的一招成
	名绝技。那施展出浑身解数，也脱不开的如梦幻般的
	棒影，令对手心惊肉跳。解开棒诀，本招将取消行动
	busy。命中与经验值和悟性有关。
	注意：缠字诀和转字诀不能混合使用。

	指令：perform stick.chan

要求：	
	最大内力需求 1000 以上；
	当前内力需求 500 以上；
	打狗棒法等级 100 以上；
	混天气功等级 100 以上；
	打狗棒诀等级 100 以上：
	激发招架为打狗棒。
HELP
	);
	return 1;
}
