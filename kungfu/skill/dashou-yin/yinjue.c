//yinjue.c 密宗大手印之手印诀
//By sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return MAG"手印总诀"NOR; }
int remove_effect(object me,int count);

int perform(object me, object target)
{
	int skill;
	string msg;

		if( !target ) target = offensive_target(me);

		if( !target || !target->is_character() || !me->is_fighting(target) )
			return notify_fail("「手印总决」诀只能对战斗中的对手使用。\n");


		if( objectp(me->query_temp("weapon")) )
			return notify_fail("你必须空手才能使用「手印总决」诀！\n");		
		if((int)me->query_skill("longxiang-boruo",1)<450)
            return notify_fail("你的龙象般若功修为不够。\n");	
        if( (int)me->query_skill("dashou-yin", 1) < 450 )
			return notify_fail("你的密宗大手印修为不够，不能使用「手印总决」诀。\n");
        if((int)me->query("max_neili",1)<5000)
            return notify_fail("你的内力修为太差无法使用本势。\n");                        
        if( (int)me->query("neili", 1) < 1500 )
			return notify_fail("你现在内力太弱，不能使用「手印总决」诀。\n");
		if( (int)me->query("jingli", 1) < 1500 )
			return notify_fail("你现在精力太弱，不能使用「手印总决」诀。\n");
		if( me->query_temp("dsy/yinjue"))
			return notify_fail("你正在使用「手印总决」。\n");
		if( !me->query("quest/dls/dsy/yinjue/pass"))
			return notify_fail("你听说过「手印总决」但并未学会。\n");
		if (me->query_skill_mapped("hand")!="dashou-yin"
			||me->query_skill_mapped("parry")!="dashou-yin"
			||me->query_skill_prepared("hand")!="dashou-yin")
			return notify_fail("你没有激发，不能使用「手印总决」诀。\n");
		
		
		skill=me->query_skill("dashou-yin",1);

		message_vision( MAG"$N" MAG "猛喝一声，口中默念三十六路天印诀，手上各种手势不断变换，施展出密宗绝学「"HIY"手印总决"NOR"」!\n" NOR,me,target);

		me->add("neili", -150);
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/hand",skill/4);
		me->add_temp("apply/strength",skill/20);
		me->add_temp("apply/defense",skill/4);
		remove_effect(me,(int)skill/30);
		me->set_temp("dsy/yinjue",skill);
		return 1;
}
int remove_effect(object me,int count)
{
	int skill;
	if (!me||!me->query_temp("dsy/yinjue")) return 0;
	skill=me->query_temp("dsy/yinjue");
	if (!me->is_fighting()
		||me->query_skill_mapped("hand")!="dashou-yin"
		||me->query_skill_prepared("hand")!="dashou-yin"
		||me->query_skill_mapped("parry")!="dashou-yin"
		||count--<0	)
	{
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/hand",-skill/4);
		me->add_temp("apply/defense",-skill/4);
		me->add_temp("apply/strength",-skill/20);

		me->delete_temp("dsy/yinjue");
		message_vision(MAG"$N猛然间喷出一口浊气，缓缓泄了手印诀的功力！\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me,count);
}
int help(object me)
{
        write(HIY"\n密宗大手印「手印总诀」："NOR"\n");
        write(@HELP
	密宗大手印绝技「手印总诀」,是密宗大手印集大成的招式
	各种手势纷繁复杂，变换多端，功效不同，后来宗门中高人
	总结各种招式归纳为三十六式，一气呵成，威力巨大。
	注意：
		set 印诀 大势至诀 增加臂力	
		set 印诀 金刚诀   增加防御
		set 印诀 宝瓶诀	  增加根骨
		set 印诀 光明诀   增加身法
		set 印诀 总决	  综合增加
	指令：perform hand.yinjue

要求：  
	当前内力 1500 以上；      
	最大内力 5000 以上；
	当前精力 1500 以上；  
	密宗大手印等级 450 以上；
	龙象波若功等级 450 以上；
	激发手法为密宗大手印;
	激发招架为密宗大手印；
	激发内功龙象波若功功;
	备手法大手印；
	
HELP
        );
        return 1;
}

