// Last Modified by winder on Aug. 25 2001
// 18pan.c 泰山十八盘 

#include <ansi.h>
inherit F_SSERVER;

int perform(object me,object target)
{
	string msg;
	object weapon;

	int skill;

	if( !objectp(target) ) target = offensive_target(me);
	
	if( !target || !target->is_character() || target == me ||	
	  	!me->is_fighting(target) ||
  	!living(target) || target->query_temp("noliving") )
		return notify_fail("此招只能对战斗中的对手使用。\n");
		
	if (!objectp(weapon = me->query_temp("weapon")) ||
		(string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");



	if( (int)me->query_skill("taishan-jianfa", 1) < 200 )
		return notify_fail("你的泰山剑法修为不够，使不出「泰山十八盘」。\n");

	if( (int)me->query_skill("force", 1) < 200 )
		return notify_fail("你的基本内功修为不够，使不出「泰山十八盘」。\n");

	if( me->query("neili") < 300 )
		return notify_fail("你的内力不够，无法运用泰山十八盘！\n");

	if( me->query("max_neili") < 400 )
		return notify_fail("你的内力修为不够，无法运用泰山十八盘！\n");

	if( target->is_busy() )
		return notify_fail(target->name()+"已经自顾不暇了，放胆攻击吧！\n");

	skill = me->query_skill("taishan-jianfa",1);
	msg = CYN "$N使出泰山十八盘剑法之缠剑式，一把剑闪出十八道剑影！\n";
	//me->start_busy(1);
	me->add("neili",-100);
	if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/3 )
	{
		msg += HIY"结果$n被缠个动弹不得！\n" NOR;
		target->add_busy(skill/150);
	} else
	{
		msg += HIC"可是$n看破了$N的剑招，一拧身跃出了剑影。\n" NOR;
		msg += HIY"$N却一下失去平衡，反陷入了被动。\n" NOR;
		me->start_busy(3);
	}
	 message_vision(msg, me, target);

        return 1;
}
string name() {return HIG"泰山十八盘"NOR; }

int help(object me)
{
        write(HIG"\n泰山剑法之"+HIW"「泰山十八盘」："NOR"\n\n");
        write(@HELP
	泰山派镇派之剑法绝技，乃是泰山派武术高手经年累月
	的凝练，最终而成为五岳之东岳泰山剑法大成。此剑法
	看似古拙朴素，但招式却凌厉刚猛，在不经意间出奇制
	胜。其中泰山十八盘乃是以剑法演绎登泰山之蜿蜒起伏
	之意，将对手困住。
	
	指令：perform sword.shibapan

要求：
	当前内力需求 500 以上；
	最大内力需求 1500 以上；
	当前精力需求 500 以上；
	泰山剑法等级 200 以上；
	泰山心法等级 200 以上；
	基本剑法等级 200 以上；
	基本轻功等级 200 以上；
	激发剑法为泰山剑法；
	激发招架为泰山剑法；
	激发内功为泰山心法。
	
HELP
        );
        return 1;
}
