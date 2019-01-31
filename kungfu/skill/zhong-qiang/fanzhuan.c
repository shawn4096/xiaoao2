#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	int extra;
	object weapon;
	extra = me->query_skill("zhong-qiang",1);
    	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "club")
			return notify_fail("你使用的武器不对。\n");
	if( !target ) target = offensive_target(me);
	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("［反转流星］只能对战斗中的对手使用。\n");
	weapon = me->query_temp("weapon");
	message_vision(HIY  "$N使出中平枪法中的［反转流星］，假意抽身急退，蓦地反身抖手一枪刺向$n！" NOR,me,target);
	
	me->add_temp("apply/attack",extra/4);
	me->add_temp("apply/damage",extra/6);

		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
	me->add_temp("apply/attack",-extra/4);
	me->add_temp("apply/damage",-extra/6);

	me->start_busy(2);
	return 1;
}
