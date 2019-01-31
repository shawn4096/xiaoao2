//pikan.c by sohu@xojh
//裂天斧

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
		string msg;
		int p,damage;
		int ski=me->query_skill("lietian-fu",1);
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("「劈砍诀」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("lietian-fu", 1) < 140 )
                return notify_fail("你的裂天斧法功力太浅，无法使用「劈砍」攻击。\n");
        if( (int)me->query_skill("axe", 1) < 140 )
                return notify_fail("你的基本斧法功力太浅，无法使用「劈砍」攻击。\n");


      
        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("你的内力太浅，无法使用「劈砍」攻击。\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不足，无法使用「劈砍」攻击。\n");
        if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力不足，无法使用「劈砍」攻击。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "axe"
            || me->query_skill_mapped("axe") != "lietian-fu" 
			|| me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("你的准备功夫不对。\n");

        message_vision(HIR"$N大喝一声，奋起全身劲气，气势如虹，力大斧沉，一斧向$n砍去！\n" NOR,me,target);
        
		if (random(me->query_skill("axe",1))>target->query_skill("parry",1)/2
			||random(me->query_str(1))>target->query_str(1)/2)
		{
		
			damage = me->query_skill("axe",1) +me->query_skill("lietian-fu",1);
			damage += me->query_skill("force",1);
			damage = damage*me->query_str()+ random(damage);
			if (damage > 3500) damage = 3500+random(damage-3500)/100;
			
			target->receive_damage("qi", damage, me);
			target->receive_wound("qi", damage/3, me);

			msg = RED"$N斧沉力大，招式简单，$n躲闪不及，被一斧头劈中！\n"NOR;
	
			if (random(2)) {
				p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
				msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			}else {
				p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
				msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
			}
	   		message_vision(msg, me, target);		
		}
		else {
			msg = CYN"可是$p轻功卓越，当即躲闪一旁。\n"NOR;
			//me->add("neili", -100);
			message_vision(msg, me, target);
		}
		me->add("neili", -100);
		me->add("jingli", -50);

		me->start_perform(2, "劈砍诀");
	
        return 1;
}

string perform_name(){ return HBRED+HIW"劈砍诀"NOR; }

int help(object me)
{
        write(HIR"\n裂天斧之「劈砍诀」："NOR"\n\n");
        write(@HELP 
	裂天斧之绝技「劈砍诀」，乃是当初外派的
	一位前辈高人，有感于抗金过程中短兵相接
	后，轻兵器不沾便宜的现状。总结提炼出一
	套近身搏杀的斧法，在战场中发挥了巨大的
	作用。将斧头的直接效果发挥出来。
	
	指令：perform axe.pikan

要求：
	当前内力要求 500 以上；
	最大内力要求 1500 以上；
	当前精力要求 500 以上；
	基本斧法等级 140 以上；
	裂天斧法等级 140 以上；
	激发斧法为裂天斧法；
	激发招架为裂天斧法；
	激发内功为归元吐纳法。
	手持斧类武器；
HELP
        );
        return 1;
}