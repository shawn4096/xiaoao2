// lianhuan
// By sohu@xojh
//连环出招

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,i,j;
	skill = (int)me->query_skill("jiuyin-shenzhua", 1);
	
	if (me->query_skill("jiuyin-zhengong",1)>180)
		skill = (int)me->query_skill("jiuyin-shenzhua", 1)+(int)me->query_skill("jiuyin-zhengong", 1);
	if (me->query_skill("poison",1)>=150)
		skill = (int)me->query_skill("jiuyin-shenzhua", 1)+(int)me->query_skill("poison", 1);

	if( !target ) target = offensive_target(me);

    if( !objectp(target) || !me->is_fighting(target) || !necessary(target) )
		return notify_fail("「九子连环爪」只能在战斗中使用。\n");

	if( me->query_temp("weapon"))
		return notify_fail("你拿着武器怎么能使用「九子连环爪」！\n");   

	if(me->query_skill("jiuyin-shenzhua", 1) < 500 )
		return notify_fail("你的九阴神爪还不够娴熟，使不出「九子连环爪」绝技。\n");
	if(me->query_skill("claw", 1) < 500)
		return notify_fail("你的基本爪法还不够娴熟，使不出「九子连环爪」绝技。\n");
	if(me->query_skill("force", 1) < 500)
		return notify_fail("你的基本内功还不够娴熟，使不出「九子连环爪」绝技。\n");
	if ( me->query_skill_mapped("claw") != "jiuyin-shenzhua"
		|| me->query_skill_prepared("claw") != "jiuyin-shenzhua")
		return notify_fail("你现在无法使用「九子连环爪」！\n");

	if( (int)me->query("max_neili") < 15000  )
		return notify_fail("你现在最大内力太弱，使不出「九子连环爪」。\n");      

	if( (int)me->query("neili") < 2000 )
		return notify_fail("你现在真气太弱，使不出「九子连环爪」。\n");
	if( (int)me->query("jingli") < 1000 )
		return notify_fail("你现在精力太弱，使不出「九子连环爪」。\n");

	message_vision(HBRED+HIY"\n$N纵身起伏，形如鬼魅，运起九阴神爪绝技，全身骨骼如爆豆般噼啪作响，手臂突然暴涨数尺！\n"NOR,me);
	message_vision(YEL"\n$N双爪挥舞如狂风暴雨，电闪雷鸣，瞬间挥出九式！\n"NOR,me);

	
	if (me->query_skill("jiuyin-zhengong",1)>500)
	{
		j=9;
		skill=skill+me->query_skill("jiuyin-zhengong",1)/5;
		me->add_temp("apply/claw", skill/3);

	}else j=5;
	me->add_temp("apply/attack", skill/3);
	me->add_temp("apply/damage", skill/4);

/*	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

*/
	for (i=0; i<=j ;i++ )
	{
		if(objectp(target) && me->is_fighting()) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	}
	me->add_temp("apply/attack", -skill/3);
	me->add_temp("apply/damage", -skill/4);
	if (me->query_skill("jiuyin-zhengong",1)>500)
	{
	
		me->add_temp("apply/claw", -skill/3);

	}
	me->start_perform(6, "九子连环爪");
	me->add("neili", -1200);
	me->add("jingli", -800);
	me->add_busy(random(1)+1);
	return 1;
}

string perform_name(){ return HBGRN+HIW"九子连环爪"NOR; }

int help(object me)
{
        write(RED"\n九阴神爪之「九子连环爪」："NOR"\n\n");
        write(@HELP
	九阴神爪乃是九阴真经上卷的功夫，为一代奇人黄裳
	所作，乃是集合天下爪法的大全和最高武技。九阴神
	爪施展后，爪法威力大增。因古墓中有重阳遗刻，所
	以古墓也有流传。
	
	九子连环爪，凝神发力，连续出九招神爪，威力惊人。
	
	perform claw.lianhuan

要求：  
	当前内力的需求 2000 以上；
	最大内力的需求 15000 以上；
	当前精力的需求 1000 以上；
	九阴神爪的等级 500 以上；
	基本爪法的等级 500 以上；
	基本内功的等级 500 以上；
	激发爪法为九阴神爪；                
	备爪法为九阴神爪；
	且手无兵器；	

HELP
        );
        return 1;
}
