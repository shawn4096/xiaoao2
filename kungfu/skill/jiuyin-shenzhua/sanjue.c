#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
	int skill, j;

	skill = (int)me->query_skill("jiuyin-shenzhua", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("「九阴三绝爪」只能在战斗中使用。\n");

	if( me->query_temp("weapon"))
		return notify_fail("你拿着武器怎么能使用「九阴三绝爪」！\n");   

	if( skill < 160 )
		return notify_fail("你的九阴神爪不够娴熟，使不出九阴三绝爪。\n");

	if(me->query_skill("jiuyin-zhengong",1) < 160 )
		return notify_fail("你的九阴真功不够娴熟，使不出九阴三绝爪。\n");

	if(me->query_skill("jiuyin-shenfa",1) < 160 )
		return notify_fail("你的九阴身法不够娴熟，使不出九阴三绝爪。\n");

	if (me->query_skill_mapped("parry") != "jiuyin-shenzhua" 
	|| me->query_skill_prepared("claw") != "jiuyin-shenzhua" )
		return notify_fail("你现在无法使用「九阴三绝爪」！\n");

	if( (int)me->query("max_neili") < 2000)
		return notify_fail("你现在内力太弱，使不出「九阴三绝爪」。\n");      

	if( (int)me->query("neili") < 1500 )
		return notify_fail("你现在真气太弱，使不出「九阴三绝爪」。\n");

	message_vision(HIR"\n$N手臂突然伸长，向$n抓去！\n"NOR,me,target);
	message_vision(HIR"$N所使的似乎是江湖中驰名的九阴真经中阴毒功夫九阴白骨爪，只是招数光明正大，威力强极！\n"NOR,me,target);

	j = skill/3;
	if ( skill > 300)
		j = to_int(skill/300.0 * skill/4.0);

	me->add_temp("apply/attack", j);
	me->add_temp("apply/claw", j/2);
	me->add_temp("apply/damage", j/2);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(me->is_fighting(target)) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	me->add_temp("apply/attack", -j);
	me->add_temp("apply/claw", -j/2);
	me->add_temp("apply/damage", -j/2);

	me->add("neili", -400);
	me->add("jingli", -150);
	me->start_perform(3, "九阴三绝爪");
	me->start_busy(random(2));
	return 1;
}

string perform_name(){ return HIR"九阴三绝爪"NOR; }

int help(object me)
{
        write(HIR"\n九阴神爪之「九阴三绝爪」："NOR"\n\n");
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
	激发爪法为九阴神爪；                
	备爪法为九阴神爪；
	且手无兵器；	
HELP
        );
        return 1;
}
