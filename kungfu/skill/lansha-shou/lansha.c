 //lansha-shou.c 
//蓝砂手
//by sohu @xojh

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int lvl,damage;
		object weapon;
        lvl= me->query_skill("lansha-shou",1);
		weapon=me->query_temp("weapon");
        if (lvl<80)
                return notify_fail("你的蓝砂手还不够熟练\n");         
        
        if( !target ) target = offensive_target(me);
        if( !target
			||!target->is_character()
			||!me->is_fighting(target) )
                return notify_fail("［蓝砂漫天］只能对战斗中的对手使用。\n");
		if( (int)me->query("neili") < 600 )
			return notify_fail("你的内力不够。\n");

		if (!me->query_skill("lansha-shou",1)<250)
			return notify_fail("你的蓝砂手尚未领会贯通，不会使「蓝砂漫天」！\n");

		if( (int)me->query_skill("force", 1) < 250 )
			 return notify_fail("你的内功火候不够，不会使用「蓝砂漫天」！\n");
		if (me->query_temp("weapon"))
		{
			if( me->query_skill_mapped("throwing") != "lansha-shou")
			 return notify_fail("你必须激发throwing方可实施暗器突袭！\n");
			if( me->query_skill_mapped("throwing") != "lansha-shou")
			 return notify_fail("你必须激发throwing方可实施暗器突袭！\n");
		}
		if( me->query_skill_mapped("hand") != "lansha-shou"
			||me->query_skill_prepared("hand") != "lansha-shou")
			 return notify_fail("你没激发手法为「蓝砂手」！\n");
     
        
        damage= me->query_skill("lansha-shou",1)+me->query_skill("xuedao-jing",1)+me->query_skill("poison",1);
		damage=damage*2+random(damage);

        
		message_vision(HIB"$N突然扬起双掌，运气发力，双掌立即变得蓝汪汪一片，一招"HIC"［蓝砂手］"HIB"的招式拍向$n的胸口！\n" NOR,me);
        me->add_temp("apply/attack",lvl/4);
		me->add_temp("apply/damage",lvl/5);
		me->add_temp("apply/throwing",lvl/5);
		me->add_temp("apply/hand",lvl/5);

		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
        
        me->add("neili",-150);
		me->add("jingli",-100);
                 
        if (random(me->query_skill("lansha-shou",1))> target->query_skill("parry",1)/2
			||random(me->query_str())>target->query_con()/2)
		{
                target->receive_wound("qi",damage,me);
                message_vision(RED"$n"+RED"一声惨叫，被$N"+RED"拍得胸口发闷，忍不住狂喷鲜血。\n\n"NOR,me,target);
				target->add_busy(1);
				target->apply_condition("no_exert",1);
				target->apply_condition("lansha_poison",10+random(4));
	
        }               
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);

		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack",-lvl/4);
		me->add_temp("apply/damage",-lvl/5);
		me->add_temp("apply/throwing",-lvl/5);
		me->add_temp("apply/hand",-lvl/5);

		me->start_perform(4,"蓝砂漫天");
        return 1;
}  

string perform_name() {return HBBLU+HIG"蓝砂漫天"NOR;}

int help(object me)
{
	write(HBBLU+HIG"\n蓝砂手之「蓝砂漫天」："NOR"\n\n");
        write(@HELP
	蓝砂手是血刀门的外门武功，乃是一位高僧带入门
	中的家传武功，因为该武功既可以用修炼的手法攻
	击对方，又可以以此手法发送暗器，尤其是发出毒
	砂，令人防不胜防，十分歹毒阴险。
	
	perform throwing(hand).hongsha

要求：
	最大内力  1500 以上；
	当前内力  500  以上；
	血刀经    350  级以上；
	红砂掌法  350  级以上；
	激发掌法为蓝砂手；
	激发招架为蓝砂手；
	内功不限;
	空手或暗器均可使用；
HELP
        );
        return 1;
}