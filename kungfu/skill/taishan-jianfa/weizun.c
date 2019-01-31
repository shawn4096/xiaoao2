// weizun.c  五岳为尊
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "「五岳为尊」"
int perform(object me,object target)
{
	string msg;
	object weapon;
	
	int skill,i,attack_time;

	if( !objectp(target) ) target = offensive_target(me);
	
	if( !target || !target->is_character() || target == me ||	
	  	!me->is_fighting(target) ||
  	!living(target) || target->query_temp("noliving") )
		return notify_fail("此招只能对战斗中的对手使用。\n");
		
	if (!objectp(weapon = me->query_temp("weapon")) ||
		(string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");



	if( (int)me->query_skill("taishan-jianfa", 1) < 400 )
		return notify_fail("你的泰山剑法修为不够，使不出「五岳为尊」。\n");

	if( (int)me->query_skill("force", 1) < 400 )
		return notify_fail("你的基本内功修为不够，使不出「五岳为尊」。\n");

	if( me->query("neili") < 1300 )
		return notify_fail("你的内力不够，无法运用五岳为尊！\n");

	if( me->query("max_neili") < 4000 )
		return notify_fail("你的内力修为不够，无法运用五岳为尊！\n");


	skill = me->query_skill("taishan-jianfa",1);
	message_vision(HIW"$N使出泰山剑法的「五岳为尊」，身法陡然加快，剑锋一转，从五个方向连出数剑！\n" NOR, me);

	me->add("neili", -100);
	attack_time = 5 + random(3);
	
	me->add_temp("apply/attack",skill/4);
	me->add_temp("apply/damage",skill/5);

	for(i = 0; i < attack_time; i++)
	{
		if (!objectp(target)) break;
		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),3);
	}
	me->add_temp("apply/attack",-skill/4);
	me->add_temp("apply/damage",-skill/5);

	return 1;
}
string name() {return HIR"五岳为尊"NOR; }

int help(object me)
{
        write(HIG"\n泰山剑法之"+HIW"「五岳为尊」："NOR"\n\n");
        write(@HELP
	泰山派镇派之剑法绝技，乃是泰山派武术高手经年累月
	的凝练，最终而成为五岳之东岳泰山剑法大成。此剑法
	看似古拙朴素，但招式却凌厉刚猛，在不经意间出奇制
	胜。其中五岳为尊是从五个不同方向连出五招，迅捷无
	比。为泰山剑法精华招式。
	
	指令：perform sword.weizun

要求：
	当前内力需求 500 以上；
	最大内力需求 1500 以上；
	当前精力需求 500 以上；
	泰山剑法等级 400 以上；
	泰山心法等级 400 以上；
	激发剑法为泰山剑法；
	激发招架为泰山剑法；
	激发内功为泰山心法。
	
HELP
        );
        return 1;
}
