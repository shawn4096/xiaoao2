//jinlong.c 金龙三式
//
//by sohu
//三招连击

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int skill;
	object weapon = me->query_temp("weapon");
	skill=me->query_skill("jinlong-bianfa",1);
	
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("「金龙三式」只能对战斗中的对手使用。\n");

	if(me->query_skill("jinlong-bianfa",1) < 150)
		return notify_fail("你的「金龙鞭法」还不够娴熟，不会使用「金龙三式」。\n");
	if(me->query_skill("whip",1) < 150)
		return notify_fail("你的「基本鞭法」还不够娴熟，不会使用「金龙三式」。\n");
	if( !weapon 
		|| weapon->query("skill_type") != "whip"
		|| me->query_skill_mapped("whip") != "jinlong-bianfa" 
		|| me->query_skill_mapped("parry") != "jinlong-bianfa" ) 
		return notify_fail("你现在无法使用「金龙三式」。\n");

	if( me->query("neili") < 500 )
		return notify_fail("你的内力不够500。\n");
	if( me->query("jingli") < 500 )
		return notify_fail("你的精力不够500。\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("你的最大内力不够1500。\n");
	if( me->query("max_jingli") < 1300 )
		return notify_fail("你的最大内力不够1300。\n");

	
	message_vision(HIG"\n$N大喝一声，宛如晴天霹雳，手中"+weapon->query("name")+HIW"连续甩动三个圆圈，层层套向$n！\n"NOR,me,target);
	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/5);
	me->add_temp("apply/whip",skill/5);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	
	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/5);
	me->add_temp("apply/whip",-skill/5);

	me->add("jingli", -100);
	me->add("neili", -200);
	me->start_perform(4,"金龙三式");
    return 1;
}

string perform_name(){ return HIY"金龙三式"NOR; }

int help(object me)
{
        write(HIG"\n金龙鞭法之「金龙三式」："NOR"\n\n");
        write(@HELP
	「金龙鞭法」是江南七怪韩宝驹的独门武技，韩宝驹一生
	爱马，所以将金龙鞭法往往化作套马索，既能套住烈马，
	也可以以此技伤人。「金龙三式」为连续攻击对方三招。
    
	指令：perform whip.jinlong
		
要求：  
	当前内力需求 500 以上；
	最大内力需求 1500 以上；
	当前精力需求 500 以上；
	最大精力需求 1300 以上；
	当前精力需求 500 以上；
	金龙鞭法等级 150 以上；
	基本鞭法等级 150 以上:
	激发鞭法为金龙鞭法；
	激发招架为金龙鞭法；
	且手持鞭子类兵器。

HELP
        );
        return 1;
}
