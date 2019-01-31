//zixu.c 子胥举鼎
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIC"子胥举鼎"NOR;}

int perform(object me, object target)
{
		object weapon;
        int i; 
		i=(int)me->query_skill("canglang-goufa",1)/100;
        if( !target ) target = offensive_target(me);
		weapon=me->query_temp("weapon");

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("【子胥举鼎】只能在战斗时使用！\n");

		if (me->query_skill_prepared("strike") != "huagu-mianzhang"
            || me->query_skill_mapped("strike") != "huagu-mianzhang"
			|| me->query_skill_mapped("hook") != "canglang-goufa"
			|| me->query_skill_mapped("parry") != "canglang-goufa" )
                return notify_fail("你现在无法使用【子胥举鼎】进行攻击。\n");  

		 if( !weapon || weapon->query("skill_type")!="hook") 		  
                return notify_fail("你必须拿着钩才能用【子胥举鼎】！\n");     
    

		if( (int)me->query_skill("huagu-mianzhang", 1) < 350 )
                return notify_fail("你的化骨绵掌还不够熟练，不能使用【子胥举鼎】！\n");
     
        if( (int)me->query_skill("canglang-goufa", 1) < 350 )
                return notify_fail("你的沧浪钩法还不够熟练，不能使用【子胥举鼎】！\n");
        
        if( (int)me->query_skill("dulong-dafa", 1) < 350 )
                return notify_fail("你的毒龙大法功力不足，不能用【子胥举鼎】。\n");
      
        if( (int)me->query_skill("hook", 1) < 350 )
                return notify_fail("你的基本钩法还不够熟练，不能使用【子胥举鼎】！\n");

        if((int)me->query("max_neili") < 5000) 
                return notify_fail("你现在内力修为尚低，不能使用【子胥举鼎】！\n"); 

        if((int)me->query("jingli") < 1000) 
                return notify_fail("你现在精力修为不足，不能使用【子胥举鼎】！\n"); 

        if((int)me->query("max_jingli") < 2500)
                return notify_fail("你现在最大精力不足，不能使用【子胥举鼎】！\n");       

        if((int)me->query("neili") < 1000) 
                return notify_fail("你现在当前内力不足，不能使用【子胥举鼎】！\n");  

	    if( target->is_busy() )
		        return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        if( (int)me->query_str() < 70  )
                return notify_fail("你的膂力太低，不能使用【子胥举鼎】。\n");

		me->add("jingli",-100);
        me->add("neili",-200);

		message_vision(HIC"$N双脚丁字步站好，将"+weapon->query("name")+HIC"交与左手，直削$n面门,然后右手单膀发力，冲$n大喝一声。\n"+
			"猛然使出洪教主真传绝技"+HIR+"「子胥举鼎」"+HIC+"，右手顺势拎住$n的上肢，试图将$n举起来！\n"NOR,me,target);
		if (random(me->query("combat_exp"))>target->query("combat_exp")/2
			||random(me->query_str())>target->query_dex()/2)
		{
			message_vision(HIR"$N左掌突然变掌为抓，出其不意抓向$n颈后【大椎穴】，$N要穴被擒全身真气立即涣散，\n"NOR,me,target);
			message_vision(HIR"$N挫步向前右肩顺势一沉，尽然生生将$n扛了起来，$n心中大骇顿时手忙脚乱。\n"NOR,me,target);
			
			if (userp(target))
			{
				if (random(2))
					target->apply_condition("no_perform",1);
				target->start_busy(2);
			}
			else {
				if (random(2))
					target->apply_condition("no_perform",3);
				target->start_busy(i);
			}

		}else {					
			message_vision(HIW"$n急中生智，低头缩肩，堪堪避过了这招。\n"NOR,me,target);
			me->start_busy(1);							
		}
		me->add("neili",-random(300));
		me->add("jingli",-random(100));
		
        return 1;

}
int help(object me)
{
   write(WHT"\n沧浪钩法「"HIC"子胥举鼎"+WHT"」：\n");
   write(@HELP
	沧浪钩法乃是神龙岛主晚年后整理自己的所学武技
	后总体提炼出的一套钩法武技，去繁就简，诡异犀
	利，防不胜防，尤其对于臂力较大男弟子而言，更
	是非常实战的功夫。其中子胥举鼎乃是典型的困敌
	武技，利用自己高的臂力和丰富的战斗经验，将对
	方举起来的招式。
	
	perform hook.zixu

要求：
	最大内力要求 5000 以上；
	当前内力要求 1000 以上；
	最大精力要求 2500 以上；
	当前精力要求 1000 以上；
	化骨绵掌等级 350 以上；
	基本掌法等级 350 以上；
	沧浪钩法等级 350 以上；
	毒龙大法等级 350 以上；
	基本钩法等级 350 以上；
	有效臂力要求 70  以上；
	激发且备掌法为化骨绵掌；
	激发钩法为沧浪钩法；
	激发招架为沧浪钩法；
	装备钩型武器；

HELP
   );
   return 1;
}