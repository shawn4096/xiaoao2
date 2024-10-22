// 连环枪.c 
//Created by sohu

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return RED"连环枪"NOR; }
int perform(object me, object target)
{
	string msg;
	int extra;
	object weapon;
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);
	if( !target
		||	!target->is_character()
		||	!me->is_fighting(target) )
		return notify_fail("［连环枪］只能对战斗中的对手使用。\n");
	
	
	if(me->is_busy())
		return notify_fail("你现在手忙脚乱，无暇连环枪！！\n");
    if( (int)me->query_skill("huyan-qiang",1) < 100|| (int)me->query_skill("spear",1) < 100)
        return notify_fail("你目前功力还使不出「连环枪」。\n");
    if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "spear")
			return notify_fail("你使用的武器不对。\n");
	if( (int)me->query("neili") < 1500 )
         return notify_fail("你的内力不够。\n");
	if( (int)me->query("jingli") < 1000 )
         return notify_fail("你的精力不够。\n");
    if( me->query_skill_mapped("spear") != "huyan-qiang")
         return notify_fail("你现在激发不对，无法使用「连环枪」进行攻击。\n");


	extra = me->query_skill("huyan-qiang",1)/4 ;
	me->add_temp("apply/attack", extra);	
	me->add_temp("apply/damage", extra);
	message_vision(RED  "$N将手中"+ weapon->name() +"连续闪动三次，"+weapon->name() +"幻出三道枪影，向$n刺去！" NOR,me,target);
	COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
	COMBAT_D->do_attack(me,target, weapon, random(3)?1:3);
	COMBAT_D->do_attack(me,target, weapon, random(3)?1:3);
	me->add_temp("apply/attack", -extra);
	me->add_temp("apply/damage", -extra);
    me->start_perform(3+random(2), "「连环枪」");

	me->start_busy(2);
	return 1;
}

int help(object me)
{
   write(YEL"\n呼延枪「"HIG"连环枪"YEL"」："NOR"\n");
   write(@HELP
	呼延枪法是呼延家传绝技，源自战阵，实战性强，后传
	于江南七怪的闹市侠隐全金发，以秤杆运使此枪法，更
	为精妙。	
	连环枪是连续抖出三个枪花，刺向对方。

	指令：perform spear.lianhuan

要求：
	呼延枪法 100 级，
	基本枪法 100 级，
	当前内力 1500 以上，
	当前精力 1000 以上，
	激发枪法呼延枪法；
	手中装备枪类武器;

HELP
   );
   return 1;
}
