// riyue 日月同辉
// by leontt
// Modify by leontt 1/05/2000
// By Spiderii fix bug

#include <ansi.h>
#include <combat.h>

string perform_name(){ return HIC"日月同辉"NOR; }

inherit F_SSERVER;
int perform(object me, object target)
{
        int i;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) ||!living(target))
                return notify_fail("「日月同辉」只能在战斗中使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("使用「日月同辉」时必须空手！\n");
        
        if( (int)me->query_skill("xingyi-zhang", 1) < 200 )
                return notify_fail("你的星移掌不够娴熟，使不出「日月同辉」绝技。\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 200 )
                return notify_fail("你的神元功等级不够，不能使用「日月同辉」。\n");

        //if (me->query_skill_mapped("force") != "shenyuan-gong")
                //return notify_fail("你目前的内功无法支持你使用「日月同辉」进行攻击。\n");  
                        
        if( (int)me->query_int() < 30 )
                return notify_fail("你的悟性还使不出「日月同辉」绝技。\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
         || me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("你现在无法使用「日月同辉」进行攻击。\n");  
        if (me->query_skill_mapped("parry") != "xingyi-zhang"
         && me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("你现在招架不对，无法使用「日月同辉」进行攻击。\n");                                                                                       
        if( (int)me->query("max_neili") < 2500 )
                return notify_fail("你现在内力修为太弱，不能使用「日月同辉」。\n");

        if( (int)me->query("neili") < 1000 )
                return notify_fail("你目前内力太少，不能使用「日月同辉」。\n");

        if( (int)me->query("jingli") < 200 )
                return notify_fail("你现在精力太少，不能使用「日月同辉」。\n");

        if( me->query_temp("mr_riyue"))
                return notify_fail("你刚使完「日月同辉」，真气运转不畅，无法再次使用！\n");
                
        tell_object(me,MAG"\n你双掌一搓，在双掌之间形成一个耀眼的「"HIW"气旋"MAG"」,状如星光漏斗！\n" NOR,me, target);
        message_vision(HIY"这股气旋在神元功加持下，越来越凝实，仿佛一股龙卷风一样罩向$n周身！\n"NOR,me,target);
        
		i = (int)me->query_skill("xingyi-zhang", 1);
		if (me->query_temp("sy/shenyuan"))
		{
			i=i+me->query_skill("shenyuan-gong",1)/5;
		}
        me->add_temp("apply/attack", i/3);
        me->add_temp("apply/strike", i/4);
        //me->add_temp("apply/strength",i/15);
		me->add_temp("apply/damage", i/5);
        me->set_temp("mr_riyue", 4);
        
        COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
        if (random(me->query_str())>target->query_dex()/2)
        {
			message_vision(HIC"$n感觉$N这掌力怪异，这股气旋带动自己身形不稳！\n"NOR,me,target);
			if (!userp(target))
				target->add_busy(3);
			else target->add_busy(1);
        }
		me->add("neili", -100);
        if(me->is_fighting(target)){
                COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
               // me->add("neili", -100);
        }
        if(me->is_fighting(target) && me->query_skill("xingyi-zhang", 1) >= 150){
                COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
              //  me->add("neili", -100);
        }
        if(me->is_fighting(target) && me->query_skill("xingyi-zhang", 1) >= 200){
                COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
                //me->add("neili", -100);
        }
                  
        message_vision(YEL "\n$N一式「日月同辉」发挥的淋漓尽致，双掌一分，气定神闲，信心倍增。\n" NOR,me, target);
        me->add_temp("apply/attack", -i/3);
        me->add_temp("apply/strike", -i/4);
        //me->add_temp("apply/strength",-i/15);
		me->add_temp("apply/damage", -i/5);
        me->delete_temp("mr_riyue");
        me->start_busy(1+random(2));
        me->start_perform( 4,"「日月同辉」");
        me->add("jingli", -100);
        me->add("neili", -200);
        if(me->query("neili") < 0) me->set("neili", 0);
        return 1;
}


int help(object me)
{
        write(HIC"\n星移掌法之"+HIM+"「日月同辉」"NOR"\n\n");
        write(@HELP
	当年慕容复在江湖历练时早期使用的招式，利用自身
	的优势在瞬间凝聚全身功力。以星光为引，以神元功
	为基，陡然间爆发一股强悍的掌力，毙敌于掌下。

	指令：perform strike.riyue

要求：  
	当前内力 1000 以上；
	最大内力 2500 以上；
	当前精力 500 以上；
	星移掌法等级 200 以上；
	神元功等级 200 以上；
	基本掌法等级 200 以上；
	激发掌法为星移掌；
	激发招架为星移掌或斗转星移；
	悟性要求 30 以上。
HELP
        );
        return 1;
}
