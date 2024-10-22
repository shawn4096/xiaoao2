// paishui.c
// modify by sohu@xojh
//卜沉等人武技设计

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>


inherit F_SSERVER;
int get_current_day_phase();
nosave mapping *day_phase = NATURE_D->query_day_phase(); 

int perform(object me, object target)
{
	object weapon, ob;
	string msg; 
	int skill;
	skill=me->query_skill("fenshui-daofa",1);
	
	 if( !target ) target = offensive_target(me);
         if( !target || !target->is_character() || !me->is_fighting(target) )
 	      return notify_fail("「分水三刀」只能对战斗中的对手使用。\n");
        
 	
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
           
         
	if( (int)me->query("max_neili") < 1600 )
		return notify_fail("你的最大内力不够了！\n");

	if( (int)me->query_skill("blade",1) < 140 ||
	    me->query_skill_mapped("blade") != "fenshui-daofa")
		return notify_fail("你的「基本刀法」还不到家，无法使用「分水三刀」！\n");
        
    if( (int)me->query_skill("fenshui-daofa",1) < 140 )
            return notify_fail("你的「分水刀法」还不到家，无法使用「分水三刀」！\n");
	if( (int)me->query("neili") < 800 )
            return notify_fail("你的当前内力不足800，还不到家，无法使用「分水三刀」！\n");
	if( (int)me->query("jingli") < 500 )
            return notify_fail("你的当前内力不足500，还不到家，无法使用「分水三刀」！\n");
        msg = HIW "$N猛然将刀身一横纵横三竖三横，连续化作三刀,状若分水式，劈向$n的面门！\n" NOR;
        message_vision(msg, me, target);
     if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 )	
	 {  
		msg = HIW "$N只觉刀光闪烁，快捷无比，$n见状大喜连续三刀，从三个不同的方向砍来！\n" NOR;	
	    message_vision(msg, target,me);
	   
	    target->add_busy(1);
		if (!userp(target)) target->add_busy(1);
		
	  }
	me->add_temp("apply/attack",skill/4);
	me->add_temp("apply/attack",skill/5);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	me->add_temp("apply/attack",-skill/4);
	me->add_temp("apply/attack",-skill/5);

	me->add("neili", -150);
	me->add("jingli",-80);
	me->start_busy(random(1));
    me->start_perform(3,"分水三刀");
	return 1;
}


string perform_name(){ return HIW"分水三刀"NOR; }

int help(object me)
{
        write(HIB"\n分水刀法之「分水三刀」："NOR"\n\n");
        write(@HELP
	分水刀法是嵩山邀请的外门客卿武功，其中卜沉、沙天翁
	长期生活在水上，修炼成一门独特的分水刀法武技。分水
	三刀就是瞬间爆发三招。

	指令：perform blade.fenshui

要求：
	当前内力需求 800 以上；
	最大内力需求 1600 以上；
	当前精力需求 500 以上；
	分水刀法等级 140 以上；
	基本刀法等级 140 以上；
	激发刀法为分水刀法；
	内功不限；
	且手持刀类兵器。

HELP
        );
        return 1;
}
