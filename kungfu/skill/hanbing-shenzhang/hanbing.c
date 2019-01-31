// snowman
// Modified by Numa 2000.1.25

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

string perform_name() {return BLU"寒冰气"NOR;}

int perform(object me, object target)
{
	string msg, dodge_skill;
        int p;
        
        if( !target ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        ||  !living(target))
                return notify_fail("你不在战斗中。\n");
               
        if(me->query_temp("weapon"))
                return notify_fail("你必须空手才能使用的寒冰神掌。\n");
        if( (int)me->query_skill("hanbing-shenzhang", 1) < 350 )
                return notify_fail("你的寒冰神掌修为不够。\n");

        if( (int)me->query_skill("force", 1) < 350 )
                return notify_fail("你的基本内功修为不够。\n");
 
        if ( me->query_skill_mapped("force") != "hanbing-zhenqi")
                return notify_fail("你的内功不对！\n");
 
        if (me->query_skill_prepared("strike") != "hanbing-shenzhang"
        || me->query_skill_mapped("strike") != "hanbing-shenzhang")
                return notify_fail("你没有运用寒冰神掌！\n");
                
        if( me->query("max_neili") <= 5000 )
                return notify_fail("你的内力修为不够！\n");
                
        if( me->query("neili") <= 1500 )
                return notify_fail("你的真气不够！\n");

        if (me->query_skill("hanbing-shenzhang",1)<450)
            me->start_perform(3,"寒冰真气");
        message_vision(HBBLU+HIW "\n$N将已修练了十余年的“寒冰真气”注于食指之上，拚着大耗内力，手指一伸，飞点$n的胸口！\n\n" NOR, me,target);
        me->add("neili", -350);
       if ( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2
			||random(me->query_skill("strike",1))>target->query_skill("parry",1)/2)
        { 
//            me->add("max_neili", - (1+random(3)));
             	message_vision(HIB+HIW"结果$n促不及防，被$P一指点在胸前大穴上！\n", me, target);
             	if( me->query_skill("hanbing-shenzhang", 1) < target->query_skill("hanbing-shenzhang", 1) * 2)
             	{
                	tell_object(me, HIR "你一指点在" +target->query("name") +"胸口，不料此人竟然也练有寒冰神掌，看来你这指是无效了。\n"NOR);
                 	tell_object(target, HIY "你只觉一股寒气袭胸，立即全力运功，竟然抗住了寒气的侵袭！\n" NOR);
                 	return 1;
                }
             	else
             	{
                	tell_object(me, BLU "你一指点在" +target->query("name") +"胸口，待其运内力抵抗，将寒毒顺他“天池穴”直逼过去！" +target->query("name") +"体内。\n"NOR);
                 	tell_object(target, HIW "你只觉一股寒气袭胸，立即全力运功，不料一瞬之间，寒气已将你全身冻僵！\n"NOR);
                    target->receive_damage("qi", (me->query_skill("strike")+me->query_skill("force")),me);
                    target->receive_wound("qi", (me->query_skill("strike")+me->query_skill("force"))/3,me);
                 	target->receive_wound("jing", me->query_skill("hanbing-shenzhang",1),me);
                    if(!target->query_condition("cold_poison"))
                 	target->apply_condition("cold_poison", me->query_skill("hanbing-shenzhang", 1)*2);
                    if(!target->query_condition("no_force"))
                 	target->apply_condition("no_force", me->query_skill("hanbing-shenzhang", 1)/10);
                 	target->add_busy(2+random(2));
					p = (int)target->query("qi")*100/(int)target->query("max_qi");
                 	msg = damage_msg(me->query_skill("strike"), "内伤");
                 	msg += "( $n"+eff_status_msg(p)+" )\n";          
                 	message_vision(msg, me, target);
                    if(userp(me) && me->query("env/damage"))  
						tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+(me->query_skill("strike")+me->query_skill("force"))+ WHT"点攻击伤害。\n"NOR); 
					
if(userp(target)&& target->query("env/damage")) 
						tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+(me->query_skill("strike")+me->query_skill("force"))+ WHT"点伤害。\n"NOR);
					return 1;
               }
        }
        else
        {
        	dodge_skill = target->query_skill_mapped("dodge");
             	if( !dodge_skill )
             		//dodge_skill = "dodge";
             	message_vision(HIW "$n一个旱地拔葱，跃起数丈，堪堪避过。\n" NOR, me, target);
        }
        me->start_busy(1+random(3));
        return 1; 
}
int help(object me)
{
	write(HIW"\n寒冰神掌之"+BLU"「寒冰气」："NOR"\n\n");
        write(@HELP
	寒冰神掌乃是嵩山弟子高级武技，寒冰气乃是运使
	寒冰真气，以高深内力凝聚与一点，然后点向对方，
	对方一旦中招，立即寒气发作，动弹不得。同时寒
	冰真气发作，对方行动立即受制。
	
	指令；perform strike.hanbing

要求：
	最大内力  5000 以上；
	当前内力  1500  以上；
	寒冰真气  350  级以上；
	大嵩阳手  350  级以上；
HELP
        );
        return 1;
}