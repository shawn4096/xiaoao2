// by darken@SJ

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
		int ski=me->query_skill("liuye-daofa",1)/2+me->query_skill("tiezhang-zhangfa",1)/2;
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("一刀夹双掌只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("liuye-daofa", 1) < 100 )
                return notify_fail("你的柳叶刀法功力太浅，无法使用一刀夹双掌攻击。\n");

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 100 )
                return notify_fail("你的铁掌掌法功力太浅，无法使用一刀夹双掌攻击。\n");
      
        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("你的内力太浅，无法使用一刀夹双掌攻击。\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不足，无法使用一刀夹双掌攻击。\n");
        if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力不足，无法使用一刀夹双掌攻击。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "blade"
            || me->query_skill_mapped("blade") != "liuye-daofa" 
			|| me->query_skill_prepared("strike") != "tiezhang-zhangfa"
			|| me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("你的准备功夫不对。\n");

        me->add("neili", -200);
        me->add("jingli", -100);
		me->set_temp("lydf/daozhang",1);
        message_vision(BLU"$N呼呼呼连环三招，刀风中夹着两招铁掌掌法，迅速向$n砍去！\n" NOR,me,target);
        me->add_temp("apply/attack", ski/2);

		if (!userp(target))
        {
			me->add_temp("apply/attack", ski/3);
	        me->add_temp("apply/damage", ski/5);
			me->add_temp("apply/strike", ski/5);
			me->set_temp("lydf/daozhang",1);
        }
				
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        weapon->unequip();

        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        weapon->wield();
         if (me->query_temp("lydf/daozhang"))
        {
			me->add_temp("apply/attack", -ski/3);
	        me->add_temp("apply/damage", -ski/5);
			me->add_temp("apply/strike", -ski/5);
			me->delete_temp("lydf/daozhang");
        }
		me->add_temp("apply/attack", -ski/2);

		me->start_perform(4,"一刀挟双掌");
        me->start_busy(1);
		me->delete_temp("lydf/daozhang");
        return 1;
}

string perform_name(){ return HIY"一刀挟双掌"NOR; }

int help(object me)
{
        write(HIR"\n柳叶刀法之「一刀携双掌」："NOR"\n\n");
        write(@HELP 
	柳叶刀法乃是铁掌帮弟子入门的武技，是历代帮主
	和长老们数年抗敌后总结提炼的一套实用刀法。该
	刀法必须和铁掌配合会连续出一刀两掌的效果，到
	中藏掌，掌中带刀，可谓铁掌一绝技。
	
	指令：perform blade.daozhang
		
要求：  
	当前内力 500 以上；
	最大内力 1500 以上；
	当前精力 500 以上；
	铁掌掌法等级 100 以上；
	柳叶刀法等级 100 以上；
	基本内功等级 100 以上；
	基本掌法等级 100 以上；
	激发掌法为铁掌掌法，且备铁掌掌法；
	激发招架为柳叶刀法；
	激发刀法为柳叶刀法；
	激发内功为归元吐纳法。
	手持刀类武器；
HELP
        );
        return 1;
}