// shuangjue.c It's a "pfm" .
// by Looklove@SJ 2001/2/14 ...情人节
// Modify by looklove 2001.4.4
// Mofify by looklove 2001.4.8
// Modify by looklove 2001.5.2

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIM"棒掌双绝"NOR; }
int perform(object me, object target)
{
	int b, z, j;
	object weapon;
	b = me->query_skill("dagou-bang", 1);
	b += me->query_skill("xianglong-zhang", 1);
	weapon = me->query_temp("weapon");

	//if (!target ) target = offensive_target(me);
	//|| !necessary(target)

	if (!objectp(target) || !me->is_fighting(target))
		return notify_fail("「棒掌双绝」只能在战斗中对对手使用。\n");

	if(!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "stick")
		return notify_fail("你手里没有棒，无法使用棒掌双绝！\n");
	if( !me->query("quest/gb/dgb/shuangjue/pass"))
		return notify_fail("你尚未受到洪七公的指点，无法使用棒掌双绝。\n");

	if( (int)me->query_int(1) < 50)
		return notify_fail("你后天悟性不足，无法使用棒掌双绝。\n");

	if( (int)me->query_skill("dagou-bang", 1) < 450 )
		return notify_fail("你的打狗棒法还不够娴熟，使不出「棒掌双绝」绝技。\n");

	if( (int)me->query_skill("xianglong-zhang", 1) < 450 )
		return notify_fail("你的降龙十八掌还未练成，不能使用棒掌双绝！\n");

	if( me->query_skill_mapped("force") != "huntian-qigong"
	|| (int)me->query_skill("huntian-qigong", 1) < 450 )
		return notify_fail("你的混天气功还没有学成，无法使用棒掌双绝！\n");

	if( me->query_skill_mapped("parry") != "dagou-bang")
		return notify_fail("你的招架功夫不是打狗棒，无法使用棒掌双绝！\n");

	if( me->query_skill_mapped("strike") != "xianglong-zhang"
	|| me->query_skill_prepared("strike") != "xianglong-zhang")
		return notify_fail("你没有用降龙十八掌，无法使用棒掌双绝！\n");

	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("你的内力根基太弱，使不出「棒掌双绝」。\n");

	if( (int)me->query("neili") < 2500 )
		return notify_fail("你现在真气太弱，使不出「棒掌双绝」。\n");

	if((int)me->query("jingli") < 1200 )
		return notify_fail("你的精力不足以让你使出此绝技。\n");

	z = b/2;
	//z=b;		
	j = to_int( z / 4.5);

	if( z >= 450 )
		j = to_int( z/3 * z/250.0 );
	else j = to_int( z/5 * z/250.0 );
/*	if( z < 350 )
		j = to_int( z/5 * z/250.0 );	
	else if( z > 450 )
		j = to_int( z/3 * z/450.0 );*/
	//write("j="+j);
	message_vision(HBGRN+HIW"\n$N大喝一声「棒掌双绝」，挥舞"+weapon->name()+HBGRN+HIW+"向$n击来，只见棒中藏掌，势不可挡，当者披靡。\n"NOR, me, target);

	me->add_temp("apply/attack", j);
	me->add_temp("apply/damage", j/2);

	me->set_temp("shuangjue/dgb", 3);

	me->add_temp("apply/stick", j);
	me->add_temp("apply/damage", j /3);
	if( me->is_fighting(target)) {

		message_vision(HIG"\n$N左手打狗棒密集性的点地，掀起一片棒影,"+weapon->name()+HIG+"向$n击来。\n"NOR, me, target);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	}
	me->add_temp("apply/stick", -j);
	me->add_temp("apply/damage", -j/3);
//降龙掌
	//message_vision(HIY"\n$n闪避这片棍影之际，$N右手抬起，凝重如山，正是降龙掌的招式。\n"NOR, me, target);

	me->set_temp("shuangjue/xlz", 2);

	weapon->unequip();
	me->add_temp("apply/strike", j);
	if( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/strike", -j);
	weapon->wield();
	//打狗棒招式
	//message_vision(HIG"\n$N紧跟一步，向$n左侧斜行，转身一招打狗棒法，信手而出。\n"NOR, me, target);

	me->add_temp("apply/stick", j);
	me->add_temp("apply/damage", j /2);
	if( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/stick", -j);
	me->add_temp("apply/damage", -j/2);
	//降龙掌
	//message_vision(HIY"\n$N将"+weapon->query("name")+HIY"交予右手，左手呈亢龙有悔之势，拍向$n的软肋。\n"NOR, me, target);

	weapon->unequip();
	me->add_temp("apply/strike", j);
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/strike", -j);
	weapon->wield();
	//打狗棒
	//message_vision(HIG"\n$N双手执"+weapon->query("name")+HIG"喝道，“棒打癞皮狗”！呈力劈华山之势，向$n劈了过去。\n"NOR, me, target);

	me->add_temp("apply/stick", j);
	me->add_temp("apply/damage", j /2);
	if( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/stick", -j);
	me->add_temp("apply/damage", -j/2);


	me->add_temp("apply/attack", -j);
	me->add_temp("apply/damage", -j/2);

	me->add("neili", -500-random(1000) );
	me->add("jingli", -300-random(200));
	me->delete_temp("shuangjue");
    me->start_perform(4+ random(2),"「棒掌双绝」");
	me->start_busy(random(2));
	return 1;
}

int help(object me)
{
	write(WHT"\n打狗棒法之「棒掌双绝」："NOR"\n");
	write(@HELP
	打狗棒的一门绝技，洪老帮主因打狗棒威力若没全部
	发挥出来之前，弟子施展打狗棒威力稍显不足，于是
	就将降龙十八掌的招式融入到棒法中，虽然有些杂驳
	但集打狗棒与降龙十八掌精华于一身，棒中藏掌，威
	力也自不同凡响，乃门中弟子中期重要过度武技。

	指令；peform stick.shuangjue

要求：
	后天悟性需求 50 以上；
	最大内力需求 5000 以上；
	当前内力需求 2500 以上；
	打狗棒法等级 450 以上；
	混天气功等级 450 以上；
	降龙掌法等级 450 以上；
	激发招架为打狗棒；
	空手武功为降龙十八掌。
HELP
	);
	return 1;
}
