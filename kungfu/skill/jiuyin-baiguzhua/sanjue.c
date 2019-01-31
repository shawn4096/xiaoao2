// SANJUE 白骨三绝爪
// By Spiderii 适当提高
#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,skill1, i;
	skill = (int)me->query_skill("jiuyin-baiguzhua", 1);
	
	if (me->query_skill("jiuyin-zhengong",1)>180)
		skill = (int)me->query_skill("jiuyin-baiguzhua", 1)+(int)me->query_skill("jiuyin-zhengong", 1);
	if (me->query_skill("poison",1)>=150)
		skill = (int)me->query_skill("jiuyin-baiguzhua", 1)+(int)me->query_skill("poison", 1);

	if( !target ) target = offensive_target(me);

    if( !objectp(target) || !me->is_fighting(target) || !necessary(target) )
		return notify_fail("「白骨三绝爪」只能在战斗中使用。\n");

	if( me->query_temp("weapon"))
		return notify_fail("你拿着武器怎么能使用「白骨三绝爪」！\n");   

	if(me->query_skill("jiuyin-baiguzhua", 1) < 350 )
		return notify_fail("你的九阴白骨爪还不够娴熟，使不出「白骨三绝爪」绝技。\n");
	if(me->query_skill("claw", 1) < 350)
		return notify_fail("你的基本爪法还不够娴熟，使不出「白骨三绝爪」绝技。\n");
	if(me->query_skill("force", 1) < 350)
		return notify_fail("你的基本内功还不够娴熟，使不出「白骨三绝爪」绝技。\n");
	if ( me->query_skill_mapped("claw") != "jiuyin-baiguzhua"
		|| me->query_skill_prepared("claw") != "jiuyin-baiguzhua")
		return notify_fail("你现在无法使用「白骨三绝爪」！\n");

	if( (int)me->query("max_neili") < 5000  )
		return notify_fail("你现在最大内力太弱，使不出「白骨三绝爪」。\n");      

	if( (int)me->query("neili") < 1500 )
		return notify_fail("你现在真气太弱，使不出「白骨三绝爪」。\n");
	if( (int)me->query("jingli") < 800 )
		return notify_fail("你现在精力太弱，使不出「白骨三绝爪」。\n");
	if (me->query_skill_mapped("claw")!="jiuyin-baiguzhua"
		||me->query_skill_prepared("claw")!="jiuyin-baiguzhua")
                return notify_fail("你尚未激发九阴白骨爪。\n");
/*
    if( me->query("shen") > -1000000 && me->query("PKS") < 10 )
 
		if( me->query("GKS") < me->query("BKS") && !me->query("no_pk") )
			return notify_fail("你不够狠毒，无法使出「白骨三绝爪」的绝技。\n");*/

	message_vision(RED"\n$N突然怪叫一声，运起九阴白骨爪绝技，全身骨骼如爆豆般噼啪作响，手臂突然暴涨三尺！\n"NOR,me);
	message_vision(BLU"\n$N手上阴森森腾起一股劲气，向$n挥出三招，招招插向$n的头骨！\n"NOR,me);

	
	if(wizardp(me)) tell_object(me,sprintf("Jiuyin Debug:i=%d \n",i));					
	
	me->add_temp("apply/attack", skill/3);
	me->add_temp("apply/damage", skill/5);
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

    if(me->is_fighting(target)) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);

    if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	me->add_temp("apply/attack", -skill/3);
	me->add_temp("apply/damage", -skill/5);

	me->start_perform(4, "白骨三绝爪");
	me->add("neili", -400);
	me->add("jingli", -150);
	me->start_busy(random(2));
	return 1;
}

string perform_name(){ return HBWHT+RED"白骨三绝爪"NOR; }

int help(object me)
{
        write(RED"\n九阴白骨爪之「白骨三绝爪」："NOR"\n\n");
        write(@HELP
	九阴白骨爪乃是九阴真经下卷的功夫，为一代奇人
	黄裳搜集敌人武功所归纳，放在卷首，并标明了破
	解之法。陈玄风梅超风二人不明白上卷武功，只凭
	个人揣摩，把 “五指发劲，无坚不破，摧敌首脑，
	如穿腐土 ”理解成用人头骨练习这门功夫。但此功
	法威力不俗，加上伤人无数，也成就了这白骨爪的
	赫赫威名。
	
	白骨爪连续三招，招招直指对方的头脑部位，端的
	是无坚不摧，爪爪入骨！
	
	perform claw.sanjue

要求：  
	当前内力的需求 1500 以上；
	最大内力的需求 5000 以上；
	当前精力的需求 800 以上；
	九阴白骨爪等级 350 以上；
	基本爪法的等级 350 以上；
	基本内功的等级 350 以上；
	激发爪法为九阴白骨爪；                
	备爪法为九阴白骨爪；
	且手无兵器；	

HELP
        );
        return 1;
}
