//kunlun-zhang
//luoyan 昆仑落雁掌
// By sohu

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
#include <combat.h> 

string perform_name() { return HIG"落雁掌"NOR; }


int perform(object me, object target)
{
        int damage,skill;

        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("昆仑落雁掌劲力只能在战斗中使用。\n");       
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("先放下手中的武器再说吧！\n");
        if((int)me->query_skill("strike", 1) < 250 )
                return notify_fail("你的基本掌法太低，无法使用昆仑掌之昆仑落雁掌。\n");  
        if((int)me->query_skill("kunlun-zhang", 1) < 250 )
                return notify_fail("你的昆仑掌还不够娴熟，不能使出昆仑掌之昆仑落雁掌。\n");
        if (me->query_skill_prepared("strike") != "kunlun-zhang"
           || me->query_skill_mapped("strike") != "kunlun-zhang")
                return notify_fail("你不使用昆仑掌，又岂能使得化拳为掌？\n");   
        if( (int)me->query("max_neili", 1) < 2500 )
                return notify_fail("你内力修为太浅，无法运劲伤敌！\n");                
        if( (int)me->query("neili", 1) < 1500 )
                return notify_fail("你现在真气不够，发不出昆仑落雁掌的劲力。\n");
        if(userp(me) && (int)me->query_skill("xuantian-wuji", 1) < 250 )
                return notify_fail("你的玄天无极功等级不够，不能应用昆仑落雁掌的劲力。\n");
        if(userp(me) && me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("你的内功心法不对，发挥不出昆仑落雁掌劲力之威。\n"); 
        if( me->query_str(1) < 50 )
                return notify_fail("你的后天臂力不足50，无法使用昆仑叠掌之落雁掌。\n");  

		if(me->query_temp("klz/luoyan"))
                return notify_fail("你暂时不能使用"HIG"「昆仑落雁掌」"NOR"」了。\n");   
                                                                               
        damage=(int)me->query_skill("kunlun-zhang")+(int)me->query_skill("dodge")+(int)me->query_skill("force");
		damage=damage*2+random(damage);
		if (damage>4000) damage=4000+random(1000);
        
		skill=(int)me->query_skill("kunlun-zhang",1);
		
		if (me->query("gender")=="男性")
		{
			skill=skill+me->query_skill("xuantian-wuji",1)/6;
		}else
			skill=skill/3;

		me->add_temp("apply/damage", skill/5);
        me->add_temp("apply/attack",skill/4);
        me->add("neili", -200);
		me->add("jingli",-150);
        message_vision(HIY"$N纵身而起，施展"HIG"「昆仑落雁掌」"HIY"身形晃动间瞬间连出数招，迅如闪电，疾如奔雷，幻起一片掌印！\n"NOR,me, target);
		me->set_temp("klz/luoyan",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if (random(me->query_dex())>target->query_dex()/2
			||random(me->query_skill("strike",1))>target->query_skill("parry",1)/2)
		{
			message_vision(HIC"$N将昆仑派踏雪无痕的轻功发挥极致，幻起一片掌影，“啪”的一声打在$n的脸颊之上！\n$n不禁有些眩晕恍惚！\n"NOR,me, target);
			
			target->add_busy(1);
			target->apply_condition("no_exert",1);
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/3,me);

		}

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
		me->add_temp("apply/damage", -skill/5);
        me->add_temp("apply/attack",-skill/4);
		me->delete_temp("klz/luoyan");
        me->start_perform(4, "昆仑落雁掌");
		return 1; 
}

int help(object me)
{
	write(WHT"\n昆仑掌之「"HIG"落雁掌"WHT"」："NOR"\n");
	write(@HELP
	昆仑掌之落雁掌式源自鹿鼎记澄心大师
	点评昆仑派的章法招式，落雁掌和少林
	千叶手，武当派回风掌，崆峒派飞凤掌
	有异曲同工之妙。主要是招式快速无比
	配合昆仑派独特的身法优势，取自其快
	的要诀，迅速出招，令人防不胜防。
	注意：此招男性威力强于女性。
	
	指令：perform strike.luoyan
	
要求：
	当前内力 1500 以上，
	最大内力 2500 以上。
	基本掌法 250  以上。
	昆仑掌法 250  以上。
	玄天无极 250  以上。
	后天臂力 50   以上；
	激发掌法为昆仑掌；
	激发招架为昆仑掌；
	激发内功玄天无极功；
	空手且备掌法为昆仑掌

HELP
	);
	return 1;
}
