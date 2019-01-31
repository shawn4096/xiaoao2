// 沙场破阵剑法 越女亲传
// by Jpei@NT 2009/05

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HIY"临阵六剑"NOR;}

int perform(object me,object target)
{
    object weapon;
    int skill;
	skill=me->query_skill("yuenu-jian",1);
	//if (me->query_skill("force",1)>=550)
		//skill=skill+me->query_skill("force",1)/10;
    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("临阵六剑只能对战斗中的对手使用。\n");
    if( (int)me->query_skill("yuenu-jian", 1) < 450 )
                return notify_fail("你的剑法还未练成，不能使用临阵六剑攻击！\n");
    if((int)me->query_skill("sword", 1) < 450 )
                return notify_fail("你的基本剑法不够娴熟，不能使用临阵六剑。\n");
    if (!objectp(weapon = me->query_temp("weapon")) 
		|| weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "yuenu-jian")
                return notify_fail("你手里无剑，如何使用临阵六剑？\n");
                
    if((int)me->query("max_neili") < 15000 )
                return notify_fail("你的内力修为不够，不能使用临阵六剑！\n");
    if((int)me->query("neili") < 1000 )
                return notify_fail("你现在真气不足，不能使用临阵六剑！\n");
    
	message_vision(HIY"\n$N剑招忽生惨烈悲壮之意，刺挑削、旋引撩，招招皆是剑法入门，威力却是极大，剑剑不离$n致命之处，正是越女亲授之“临阵六剑”"NOR"！\n"NOR, me,target);
    
	me->set_temp("ynj/6j",1);

    me->add_temp("apply/strength",  skill/20);
    me->add_temp("apply/attack",  skill/2);
    me->add_temp("apply/damage", skill/3);
    me->add_temp("apply/sword", skill/3);
    
	     COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    me->delete_temp("ynj/6j");
    me->add_temp("apply/strength",  -skill/20);
    me->add_temp("apply/attack",  -skill/2);
    me->add_temp("apply/damage", -skill/3);
    me->add_temp("apply/sword", -skill/3);
    target->start_busy(1);
    me->start_perform(5,"「临阵六剑」");
   
    me->add("neili", -500);
	return 1;
}

int help(object me)
{
   write(WHT"\n越女剑「"HIY"临阵六剑"WHT"」："NOR"\n");
   write(@HELP
	越女剑法相传是春秋战国时期一位越国叫做阿青的姑娘
	从白猿身上领悟的一套剑法，越王勾践卧薪尝胆要灭掉
	吴国，为了训练士兵，就在民间广征高手。有个女子来
	到军中，传了士兵一套剑法，传了以后，却不肯留下姓
	名。后来人们就以越女剑法来称呼这套剑法。
	临阵六剑，其道甚微而易，其意甚幽而深。道有门户，
	亦有阴阳。开门闭户，阴衰阳兴。凡手战之道，内实精
	神，外示安仪。见之似好妇，夺之似惧虎。
	越女亲授临阵六剑，刺挑削、旋引撩，招招皆是剑法入
	门，却招招指向致命之处，当者披靡。只有女性才能发
	挥出最大威力。

	perform sword.liujian

要求：
	最大内力需要 15000 以上；
	当前内力需要 1000 以上；
	基本剑法等级 450 以上；
	越女剑法等级 450 以上；
	激发剑法为越女剑法；
	手持剑类武器；
HELP
   );
   return 1;
}
