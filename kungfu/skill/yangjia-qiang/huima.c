//  huima.c 回马枪 
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HBRED"回马枪"NOR;}

int perform(object me,object target)
{
    object weapon;
    int i;
    i = me->query_skill("yangjia-qiang", 1);
    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「回马枪」只能对战斗中的对手使用。\n");

    if((int)me->query_skill("force", 1) < 350 )
                return notify_fail("你的基本内功不够娴熟，无法支持「回马枪」。\n");

    if( (int)me->query_skill("yangjia-qiang", 1) < 350 ) 
                return notify_fail("你的枪法还未练成，不能使用「回马枪」！\n");

    if((int)me->query_skill("spear", 1) < 350 )
                return notify_fail("你的基本枪法不够娴熟，不能在剑招中使用「回马枪」。\n");

    if((int)me->query_skill("dodge", 1) < 350 )
                return notify_fail("你的基本轻功不够娴熟，不能使用「回马枪」。\n");

    if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "spear"
        || me->query_skill_mapped("spear") != "yangjia-qiang")
        //|| me->query_skill_mapped("parry") != "yangjia-qiang"
                return notify_fail("你手里无枪，如何使用「回马枪」？\n");
                
    if((int)me->query("max_neili") < 8000 )
                return notify_fail("你的内力修为不够，不能使用「回马枪」！\n");

    if((int)me->query("neili") < 3000 )
                return notify_fail("你现在真气不足，不能使用「回马枪」！\n");

    if((int)me->query("jingli") < 1000 )
                return notify_fail("你现在太累了，不能使用「回马枪」！\n");
    if((int)me->query("yjq/huima")  )
                return notify_fail("你正在使用「回马枪」！\n");
      
    message_vision(HIB"\n$N忽然纵身跃起，将手中的"+weapon->query("name")+HIB"倒拖在身后，转身扬长而去！"NOR, me,target);
	message_vision(HIG"\n$N微微扭头一看，见$n在后面紧紧跟随，不由地冷笑一声，忽地施展出杨家枪之"YEL"「回马枪」"HIG"绝技!\n"NOR, me,target);
        
    me->add("neili", -800);
    me->add("jingli",-500);
    me->set_temp("yjq/huima",1);

  
    if (random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_str())>target->query_dex()/2)
    {  
	
	    message_vision(HIY"$n却见$N陡然反身，手中的"+weapon->query("name")+HIY"宛如一条巨蟒，抖出数朵枪花，直刺自己要害,不由大惊失色！"NOR,me,target);
		target->set_temp("must_be_hit",1);
		target->receive_damage("qi",random(3000),me);
		target->receive_wound("qi",random(500),me);
		target->add_busy(2+random(2));
        
        me->add_temp("apply/spear",i/5);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),4);
        target->delete_temp("must_be_hit");
		me->add_temp("apply/spear", -i/5);
    	
    }else
	{
		message_vision(HIC"$n当即一个铁板桥躲过此招，但却吓了一声冷汗。\n"NOR,me,target);
		target->apply_condition("no_exert",1);
		target->add_busy(1);
		me->add_busy(2);
		
	}
   
    me->delete_temp("yjq/huima");
    me->start_busy(1);
	me->start_perform(3,"「回马枪」");
    target->start_busy(1);
    return 1;
}

int help(object me)
{
   write(YEL"\n杨家枪「"HIG"回马枪"YEL"」："NOR"\n");
   write(@HELP
   指令：perform huima
	杨家枪乃是传自北宋年间杨家将的枪法，无论马上还是
	马下都极为实战，其中回马枪是必杀绝技招式，乃佯装
	败北，趁敌人匆忙追赶过程中，陡然一枪刺出，将对方
	刺与马下的招式。
	要求：
		杨家枪法 350 级，
		基本枪法 350 级，
		最大内力 8000 以上，
		当前内力 3000 以上，
		当前精力 1000 以上，
		激发枪法为杨家枪。
HELP
   );
   return 1;
}