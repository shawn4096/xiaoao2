// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"夺命铁爪"NOR; }

int perform(object me, object target)
{
        int skill,i;
        skill = (int)me->query_skill("tiezhang-zhangfa", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「夺命铁爪」只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「夺命铁爪」！\n");   
        if( skill < 200 )
                return notify_fail("你的铁掌掌法不够娴熟，使不出「夺命铁爪」。\n");
        if(me->query_skill("guiyuan-tunafa",1) < 200 )
                return notify_fail("你的归元吐呐法不够娴熟，使不出「夺命铁爪」。\n");
		 if(me->query_skill("strike",1) < 200 )
                return notify_fail("你的基本掌法不够娴熟，使不出「夺命铁爪」。\n");
        if(me->query_skill_mapped("strike") != "tiezhang-zhangfa" 
			||me->query_skill_prepared("strike") != "tiezhang-zhangfa" )
               return notify_fail("你现在无法使用「夺命铁爪」！\n");
        if( (int)me->query("max_neili") < 1500)
                return notify_fail("你现在内力太弱，使不出「夺命铁爪」。\n");      
        if( (int)me->query("neili") < 800 )
                return notify_fail("你现在真气太弱，使不出「夺命铁爪」。\n");
		if( (int)me->query("jingli") < 500 )
                return notify_fail("你现在精力不够，使不出「夺命铁爪」。\n");
        message_vision(HBBLU"\n$N左掌竖起向外拍出，右手成抓，同时袭到，两股强力排山倒海般压向$n！\n"NOR,me,target);
        
		if (!userp(target))
        {
			i=3;
			me->add_temp("apply/damage",skill/6);
			me->set_temp("tzzf/duoming",1);
        }
		else i=2;
		if (random(me->query_dex()) > target->query_dex()/i) {
           message_vision(HIR"$N右手成抓，劲气传来，结果$n被$N右手牢牢抓住！\n"NOR,me,target);
           target->add_busy(1);
        }
        message_vision(HBBLU"\n$N见$n有些慌乱，左掌一掌发出的劲气拍向$n！\n"NOR,me,target);
        me->add("neili", -random(500));
        me->add("jingli", -random(100));
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/damage",skill/5);
		if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/5);
		me->start_perform(3,"「夺命铁爪」");
		if (me->query_temp("tzzf/duoming"))
		{
			me->add_temp("apply/damage",-skill/6);
			me->delete_temp("tzzf/duoming");
		}
        return 1;
}


int help(object me)
{
        write(HIC"\n铁掌掌法之「夺命铁爪」："NOR"\n\n");
        write(@HELP 
	夺命铁爪是铁掌十三绝技之一，主要是利用铁掌
	掌法的特点，以硬功变掌为抓，牵引拉扯对方。
	同时换掌拍向对方胸口，端的是厉害无比。

	perform strike.duoming
		
要求：
	当前内力 800 以上；
	当前精力 500 以上；
	铁掌掌法等级 200 以上；
	基本内功等级 200 以上；
	基本掌法等级 200 以上；
	激发掌法为铁掌掌法；
	激发招架为铁掌掌法；
	激发内功归元吐纳法。
HELP
        );
        return 1;
}