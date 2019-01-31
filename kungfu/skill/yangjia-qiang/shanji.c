// pi.c 打狗枪法--闪击
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return RED"闪击"NOR; }
int perform(object me, object target)
{
	string msg;
	int extra;
	object weapon;
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);
	if(me->is_busy())
		return notify_fail("你现在手忙脚乱，无暇闪击！！\n");
    if( (int)me->query_skill("yangjia-qiang",1) < 100|| (int)me->query_skill("spear",1) < 100)
        return notify_fail("你目前功力还使不出「闪击」。\n");
    if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "spear")
			return notify_fail("你使用的武器不对。\n");
	if( (int)me->query("neili") < 1500 )
         return notify_fail("你的内力不够。\n");
	if( (int)me->query("jingli") < 1000 )
         return notify_fail("你的精力不够。\n");
    if( me->query_skill_mapped("spear") != "yangjia-qiang"
        || me->query_skill_mapped("parry") != "yangjia-qiang")
         return notify_fail("你现在无法使用「闪击」进行攻击。\n");

	if( !target
		||	!target->is_character()
		||	!me->is_fighting(target) )
		return notify_fail("［闪击］只能对战斗中的对手使用。\n");
	
	extra = me->query_skill("yangjia-qiang",1)/4 ;
	me->add_temp("apply/attack", extra);	
	me->add_temp("apply/damage", extra);
	message_vision(RED  "$N手中的"+ weapon->name() +"幻出一环枪影，"+weapon->name() +"划破长空，突然向$n疯狂划去！" NOR,me,target);
	COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
	COMBAT_D->do_attack(me,target, weapon, random(3)?1:3);
	COMBAT_D->do_attack(me,target, weapon, random(3)?1:3);
	me->add_temp("apply/attack", -extra);
	me->add_temp("apply/damage", -extra);
    me->start_perform(3+random(2), "「闪击」");

	me->start_busy(2);
	return 1;
}

int help(object me)
{
   write(YEL"\n杨家枪「"HIG"闪击"YEL"」："NOR"\n");
   write(@HELP
	杨家枪乃是传自北宋年间杨家将的枪法，无论马上还是
	马下都极为实战，其中【闪击枪】是在战斗中忽然出招
	令对手防不胜防，杀伤力颇大。但若不中，自己也将深
	受羁绊，当慎用。

	指令：perform spear.shanji

要求：
	杨家枪法 100 级，
	基本枪法 100 级，
	当前内力 1500 以上，
	当前精力 1000 以上，
HELP
   );
   return 1;
}
