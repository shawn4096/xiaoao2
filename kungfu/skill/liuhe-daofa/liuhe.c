// sancai.c  六合刀

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIG"六合刀"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p,skill;
	string msg;
	skill=me->query_skill("liuhe-daofa",1);
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「六合刀」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");

	if( (int)me->query_skill("liuhe-daofa", 1) < 300 )
		return notify_fail("你的六合刀法不够娴熟，无法使用六合刀。\n");

	if ( me->query_skill_mapped("parry") != "liuhe-daofa"
	|| me->query_skill_mapped("blade") != "liuhe-daofa")
		return notify_fail("你现在无法使用六合刀。\n");

//	if( (int)me->query_skill("huntian-qigong", 1) < 300 )
//		return notify_fail("你的混天气功不够高。\n");

	if((int)me->query("max_neili",1) < 3500 )
		return notify_fail("你的内力修为不够，无法使用「六合刀」。\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("你现在内力太弱，不能使用「六合刀」。\n");
	if( (int)me->query("jingli", 1) < 500 )
		return notify_fail("你现在精力太弱，不能使用「六合刀」。\n");

	message_vision(HIG"\n$N围绕$n脚下奔走如飞，呈四象之意，$n觉得前后左右都是人影,$N施展手中刀，连续向外劈出数刀。\n"NOR,me,target);

	me->add_temp("apply/attack",skill/5);
	me->add_temp("apply/damage",skill/6);
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), random(3)?1:3);
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), random(3)?1:3);
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), random(3)?1:3);
	if (objectp(target)&&me->is_fighting())
	{
		weapon->unequip();
		if (me->query("gender")=="女性" && me->query_skill_prepared("strike")=="lianhua-zhang")
		{
		   message_vision(HIC"\n$N左手刀势回转，右手莲花掌花开并蒂顺势击出，冰彩纷呈。\n"NOR,me,target);				
		   COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="女性"?3:1);
		   COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="女性"?3:1);
		 }
		 if (me->query("gender")=="男性" && me->query_skill_prepared("hand")=="suohou-shou")
		{
		   message_vision(HIC"\n$N刀势中忽然夹杂锁喉手的一招锁喉擒拿，袭向$n的咽喉。\n"NOR,me,target);				
		   target->add_busy(2);
		   COMBAT_D->do_attack(me,target, me->query_temp("weapon"), random(2)?1:3);
		 }

	}
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="女性"?3:1);

	me->add_temp("apply/attack",-skill/5);
	me->add_temp("apply/damage",-skill/6);

	me->start_busy(1+random(2));
	me->start_perform(6, "六合刀");
	me->add("neili",-300);
	me->add("jingli",-200);
	return 1;
}
int help(object me)
{
        write(CYN"\n四象六合刀「六合刀」："NOR"\n");
        write(@HELP
	六合刀也是丐帮吴长老绝学，采用四象六合之意，将刀法以
	六合四象之意施展。该绝技施展开后，连出六招，刀中夹杂
	空手功夫，宛如狂风暴雨,刀势如虹，笼罩对方。
	女性如果备莲花掌会有连招优势，男性如果备锁喉手有牵制
	优势。

	指令: perform blade.liuhe

要求：  
	最大内力 3500 以上；
	当前内力 500 以上；
	当前精力 500 以上；
	基本刀法 300 级以上；
	六合刀法 300 级以上；
	内功不限；
	激发刀法六合刀法
	激发招架六合刀发
	手持刀类武器
HELP
        );
        return 1;
}
                                                                                                                                                    