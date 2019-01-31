// by sohu@xojh 2013

#include <ansi.h>

inherit F_SSERVER;
#include <combat_msg.h>
int perform(object me, object target)
{
        object weapon;
		int ski=me->query_skill("yanxing-daofa",1)+me->query_skill("sixiang-zhang",1);
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("「雁行乱刀」绝技只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("yanxing-daofa", 1) < 100 )
                return notify_fail("你的功力太浅，无法使用「雁行乱刀」绝技攻击。\n");

        if( (int)me->query_skill("sixiang-zhang", 1) < 100 )
                return notify_fail("你的四象掌法功力太浅，无法使用「雁行乱刀」绝技攻击。\n");
      
        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("你的内力太浅，无法使用一刀夹双掌攻击。\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不足，无法使用「雁行乱刀」绝技攻击。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "blade"
            || me->query_skill_mapped("blade") != "yanxing-daofa" 
			|| me->query_skill_prepared("strike") != "sixiang-zhang")
                return notify_fail("你的准备功夫不对。\n");

        me->add("neili", -200);
        me->add("jingli", -40);
        message_vision(HIY"$N运起临济庄，连环三招，正是峨眉「雁行乱刀」绝技，迅速向$n砍去！\n" NOR,me,target);
        me->add_temp("apply/attack", ski/2);
		if (userp(me) && me->query_skill("yanxing-daofa",1)<350)
        {
			me->add_temp("apply/damage", ski/6);
			me->add_temp("apply/strike", ski/5);
        }
				
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
        //COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        if (me->is_fighting(target)&&me->query_skill("yanxing-daofa",1)>150&&me->query("class")!="bonze")
        {
			weapon->unequip();
            message_vision(HIC"$N幻起漫天刀影，刀光霍霍，$n为$N的刀光所迷惑，不自觉陷入刀影之中。\n"NOR,me,target);
			target->add_busy(1);
            me->add_temp("apply/attack", ski/3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
			me->add_temp("apply/attack", -ski/3);
            weapon->wield();
        }
	   me->add_temp("apply/attack", -ski/2);
       if (userp(me)&&me->query_skill("yanxing-daofa",1)<350)
        {
			
	        me->add_temp("apply/damage", -ski/6);
			me->add_temp("apply/strike", -ski/5);
        }
		me->start_perform(4,"雁行乱刀");
        me->start_busy(1);
        return 1;
}

//string perform_name(){ return HIY"雁行乱刀"NOR; }
string perform_name(){ return HIY"雁行乱刀"NOR; }


int help(object me)
{
	    write(HIY"\n雁行刀法之「雁行乱刀」\n"NOR);
        write(@HELP 
	雁行刀法乃是峨嵋弟子入门的武技，经历代
	掌门以及长老总结提炼出来的一套实用刀法。
	该刀法必须和四象掌配合会连续出三刀一掌
	的效果，因为杀气较为浓厚，不为当代掌门，
	灭绝师太所喜欢，因此，这门武功可以向孤
	鸿子大师学习，俗家弟子有优势。
	
	指令：perform blade.luandao

要求：
	当前内力需求 500 以上；
	最大内力需求 1500 以上；
	当前精力需求 500 以上；
	四象掌法等级 100 以上；
	基本内功等级 100 以上；
	基本掌法等级 100 以上；
	激发掌法为四象掌法，且备四象掌法；
	激发招架为雁行刀法；
	激发不限。
	手持刀类武器
HELP
        );
        return 1;
}

