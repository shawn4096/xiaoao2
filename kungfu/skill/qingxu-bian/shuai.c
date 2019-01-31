//shuai.c 甩动
//by sohu
//钓叟招式

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int skill,damage;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);
	skill=me->query_skill("qingxu-bian",1);
	damage=skill*me->query_dex()+random(skill);
	if (damage>2000) damage=2000+random(1000);
	
	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("扫字诀只能对战斗中的对手使用。\n");

	if(me->query_skill("qingxu-bian",1) < 100)
		return notify_fail("你的「清虚鞭法」还不够娴熟，不会使用「甩字诀」。\n");

	if(me->query_skill("whip",1) < 100)
		return notify_fail("你的「基本鞭法」还不够娴熟，不会使用「甩字诀」。\n");
	if(me->query_skill("force",1) < 100)
		return notify_fail("你的「基本内功」还不够娴熟，不会使用「甩字诀」。\n");
	
	if( !weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "qingxu-bian" 
	|| me->query_skill_mapped("parry") != "qingxu-bian" ) 
		return notify_fail("你现在无法使用「甩字诀」。\n");

	if( me->query("neili") < 500 )
		return notify_fail("你的内力不够500。\n");
	if( me->query("jingli") < 500 )
		return notify_fail("你的精力不够500。\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("你的最大内力不够1500。\n");
	if((int)me->query("max_jingli") <1300)
	{
		write("max_jingli="+me->query("max_jingli"));
		return notify_fail("你的最大精力不够1300!\n");
	}
//	if( target->is_busy() )
//		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");
	
	message_vision(HIG "\n$N运使清虚鞭法「甩字诀」，将手中的"+weapon->query("name")+HIG"向$n的面部顺势甩出！\n"NOR,me,target);
	
	
	if(random(me->query("combat_exp") )> target->query("combat_exp")/2
		||random(me->query_dex(1)) > target->query_dex(1)/2)
	{
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
		message_vision(HIY "\n结果$p被$P抽中面部，一股大力传来，顿时$p眼冒金星！\n" NOR,me,target);

	    if(userp(me) && me->query("env/damage"))
        	tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage*4/3+ WHT"点攻击伤害。\n"NOR);
		
		if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage*4/3+ WHT"点伤害。\n"NOR);

	}
	else {
		message_vision(HIW "可是$p看破了$P的扫字诀，身子一跃便躲开了。\n" NOR,me,target);
	}
	//message_vision(msg, me, target);
	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/4);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/4);

	me->add("jingli", -100);
	me->add("neili", -60);
	me->start_perform(4,"甩字诀");
    return 1;
}

string perform_name(){ return HIG"甩字诀"NOR; }

int help(object me)
{
        write(HIG"\n清虚鞭法之「甩字诀」："NOR"\n\n");
        write(@HELP
	清虚鞭法是大理家臣诸万里的功夫，诸万里是水军都督，熟悉
	水性，所以将钓鱼的心得和诀窍融入到清虚鞭法中，利用鞭法
	的独特优势，令人防不胜防。伤害和命中都与身法有关。
    
	指令：perform whip.shuai
		
要求：  
	当前内力需求 500 以上；
	最大内力需求 1500 以上；
	当前精力需求 500 以上；
	最大精力需求 1300 以上；
	清虚鞭法等级 100 以上；
	基本鞭法等级 100 以上:
	基本内功等级 100 以上;
	激发鞭法为清虚鞭法；
	激发招架为清虚鞭法；
	且手持鞭子类兵器。

HELP
        );
        return 1;
}
