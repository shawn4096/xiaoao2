// wakeup.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{

	  if ( userp(me) && (me->query("quest/szj/pass")!=3) && !me->query("quest/shenzhao/laozu"))
	   return notify_fail("你尚未领悟第三段神照经，无法使用这种功能。");

	if ( !target || !target->is_character() )
		return notify_fail("你要用真气救醒谁？\n");

	if( me->is_fighting() || target->is_fighting())
		return notify_fail("战斗中无法运功救人！\n");

	if(target == me)
		return notify_fail("你不能为自己救醒自己！\n");

	if(!target->query_temp("noliving/unconcious") )
		return notify_fail("你只能救醒昏迷不醒的人！\n");

	if(!userp(target))
		return notify_fail("你只能救醒玩家！\n");

	if( (int)me->query_skill("shenzhao-jing", 1) < 500 )
		return notify_fail("你的神照经修为不够。\n");

	if( (int)me->query("max_neili") < 12000 )
		return notify_fail("你的最大内力修为不够。\n");

	if( (int)me->query("neili") < 5000 )
		return notify_fail("你的真气不够。\n");
	if( (int)me->query("jingli") < 2000 )
		return notify_fail("你的精力不够。\n");

	if( (int)target->query("eff_qi") < (int)target->query("max_qi") / 10 )
		return notify_fail( target->name() + "已经受伤过重，经受不起你的真气震荡！\n");

	message_combatd(HIW"$N坐了下来,扶起$n,然后将手掌贴在$n背心，缓缓地将神照经真气输入$n体内....\n\n过了不久，$n慢慢的苏醒过来。\n" NOR, me, target );

	target->receive_curing("qi", 10 + (int)me->query_skill("force",1)/3 );
	target->add("qi", 10 + (int)me->query_skill("force",1)/3 );
	if( (int)target->query("qi") > (int)target->query("eff_qi") )
		target->set("qi", (int)target->query("eff_qi"));

	//target->remove_call_out("revive");
	target->revive();
	target->reincarnate();
 
	me->add("neili", -5000);
	me->add("jingli",-2000);
	me->set("jiali", 0);
	me->start_busy(5);
	target->start_busy(5);
	return 1;
}

string exert_name() {return HBWHT"唤醒"NOR;}


int help(object me)
{
        write(WHT"\n神照经「唤醒」："NOR"\n");
        write(@HELP
	这是铁骨墨萼梅念笙老先生曾经教丁典的一套内功的秘经
	丁典习得此内功，后又传授狄云，狄云苦心多年，神照经
	已习得第三境界。巧遇机缘得到狄云指点，可更上一层楼
	为了体现神照经作为连城诀中的顶级武功特点，总共分为
	三个阶段，第一段由丁典指点，第二段由狄云指点。第三
	段将因机缘巧合为神照彻底大成，
	神照三后，神照经可以唤醒昏迷人类，无法自我唤醒。
			
	指令：exert wakeup

要求:   
	当前内力需求 5000  以上；
	最大内力需求 15000 以上；
	当前精力需求 2000  以上
	神照经功等级 500   级以上；
	基本内功等级 500   级以上；
	激发内功神照经；
        
HELP
        );
        return 1;
}

