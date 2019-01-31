// jingheal.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
/*
	if ((!target) || target->query("id")!=me->query("id"))
		return notify_fail("你要用真气为谁护精？\n");
*/
	int med;
	if ( userp(me) && (me->query("quest/szj/pass")!=3) && !me->query("quest/shenzhao/laozu"))
	   return notify_fail("你尚未解开神照经第三段要诀。\n");
	
		
	if (!target) target = me;
	med=me->query_skill("medicine",1);
	if( me->is_fighting() || target->is_fighting())
		return notify_fail("战斗中无法运功护精！\n");

	if( (int)me->query_skill("shenzhao-jing",1) < 500 )
		return notify_fail("你的神照经内功修为不够。\n");

	if( me->is_busy() )
		return notify_fail("你现在正忙着呢，哪有空运功？\n");

	if( target->is_busy())
		return notify_fail(target->name()+"现在正忙着呢！\n");

	if( (int)me->query("max_neili") < 15000)
		return notify_fail("你的内力修为不够。\n");

	if( (int)me->query("neili") < 2000)
		return notify_fail("你的真气不够。\n");

	if( (int)target->query("eff_jing") >= (int)target->query("max_jing"))
		return notify_fail("只有精气受损才需要护精。\n");

	if( (int)target->query("eff_jing") < (int)target->query("max_jing") / 10)
		return notify_fail("精气受损过重，经受不起真气震荡！\n");

	if ( me != target)
		message_combatd( HIC "$N坐了下来运起神照经内功，将左手掌贴在$n后背命门，右掌捂住$n丹田，缓缓地将运转真气....\n\n"HIY "过了不久，$n额头上冒出豆大的汗珠，脸上的疲惫模样也减轻多了。\n" NOR, me, target);
	else 
 		message_combatd( HIC "$N坐了下来运起神照经内功，将左手掌贴在后背命门，右掌捂住丹田，缓缓地将运转真气....\n\n"HIY "过了不久，$N额头上冒出豆大的汗珠，脸上的疲惫模样也减轻多了。\n" NOR, me);

	
	target->receive_curing("jing", med/10 + (int)me->query_skill("force")/2 );
	if( (int)target->query("jing") > (int)target->query("eff_jing") )
		target->set("jing", (int)me->query("eff_jing"));
	
	me->add("neili", -500);
	me->start_busy(3);
	target->start_busy(2);
	return 1;
}


string exert_name(){ return HIY"疗精"NOR; }

int help(object me)
{
        write(WHT"\n神照经「疗精」："NOR"\n");
        write(@HELP
	这是铁骨墨萼梅念笙老先生曾经教丁典的一套内功的秘经
	丁典习得此内功，后又传授狄云，狄云苦心多年，神照经
	已习得第三境界。巧遇机缘得到狄云指点，可更上一层楼
	为了体现神照经作为连城诀中的顶级武功特点，总共分为
	三个阶段，第一段由丁典指点，第二段由狄云指点。第三
	段将因机缘巧合为神照彻底大成，
	神照三后，神照经可以治疗自己精受伤状况，并且可以缓
	缓去除自己所中各种伤精类的毒素。
			
	指令：exert jingheal

要求:   
	当前的内力 2000  以上；
	最大的内力 15000 以上；
	神照经功等级 500 级以上；
	基本内功等级 500 级以上；
	激发内功神照经；
        
HELP
        );
        return 1;
}

