// sanhua.c 三花聚顶掌
// sohu@xojh

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage,skill,wap,wdp;
	string *limb, type, result, str,msg;

	type = "内伤";

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("三花聚顶只能对战斗中的对手使用。\n");

	if( me->query_temp("sanhua") )
		return notify_fail("你已在使用三花聚顶了！\n");

	if( me->query_temp("kongming") )
		return notify_fail("你已在使用灵台空明了！\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("空手才能施展三花聚顶！\n");

	if( me->query_skill_mapped("strike") != "haotian-zhang" )
		return notify_fail("你所用的并非重阳神掌，不能施展三花聚顶！\n");

	if( me->query_skill_prepared("strike") != "haotian-zhang" )
                return notify_fail("你所备的并非重阳神掌，不能施展三花聚顶！\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("你所用的并非先天功，施展不出三花聚顶！\n");

	if( me->query_skill("force") < 150 )
		return notify_fail("你的先天功火候未到，无法施展三花聚顶！\n");

	if( me->query_skill("strike") < 150 )
		return notify_fail("三花聚顶需要精湛的重阳神掌方能有效施展！\n");

	if( me->query("neili") <= 300 )
		return notify_fail("你的内力不够使用三花聚顶！\n");

	if( me->query("jing") <= 200 )
		return notify_fail("你的精不够使用三花聚顶！\n");


	msg = HIM"$N运起玄门先天功，内力遍布全身，头顶冒出丝丝热气，竟然呈现三朵莲花，紧跟劈出一掌，一股气劲似浪潮一般向$n袭来！\n\n"NOR;
	message_vision(msg, me, target);

	me->set_temp("sanhua", 1);

	skill =  ( me->query_skill("strike")
		+ me->query_skill("force") ) / 3;

	me->add_temp("apply/attack", skill/2);
	me->add_temp("apply/damage",  skill/6);
	me->add_temp("apply/dodge",  skill/2);
	me->add_temp("apply/parry",  skill/2);
	me->add_temp("apply/defense",  skill/2);
//如果对方带武器
	weapon = target->query_temp("weapon");

    if( objectp(weapon) )
	{
		wap =   me->query("force")/5
		+ (int)me->query("haotian-zhang")/5
		+ (int)me->query_str()
		+ (int)me->query("jiali");

		wdp = (int)weapon->weight() / 500
		+ (int)target->query_str()
		+ (int)target->query("jiali")
		+ (int)target->query_skill("parry")/3;

		wap = wap/2 + random(wap/2);

		if( wap > 3 * wdp ) {
			message_vision(HIY"只见$N身上的$n"+HIY+"已被一掌震断。\n"NOR, target, weapon);
			weapon->unequip();
			weapon->move(environment(target));
			weapon->set("name", "断掉的" + weapon->query("name"));
			weapon->set("value", 0);
			weapon->set("weapon_prop", 0);
			target->reset_action();
			me->add("neili", -150); // to break weapon takes more neili
		} else if( wap > 2 * wdp ) {
			message_vision(HIW"$N只觉得手中" + weapon->name() + "被一掌震得把持不定，脱手飞出！\n" NOR, target);
			weapon->unequip();
			weapon->move(environment(target));
			target->reset_action();
			me->add("neili", -120); // to break weapon takes more neili
		} else if( wap > wdp ) {
			message_vision("$N只觉得手中" + weapon->name() + "一震，险些脱手！\n", target);
			me->add("neili", -100); // to break weapon takes more neili
		}
	}
	else{
		me->add_temp("apply/attack", skill/2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
		me->add_temp("apply/attack", -skill/2);
	}
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

	me->add("neili", -skill/2);
	me->add("jingli", -100);
	me->add("jing", -100);
	me->start_busy(random(2));

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/2 :), skill/15);

	return 1;
}

void remove_effect(object me, int amount)
{
	me->add_temp("apply/attack", -amount);
	me->add_temp("apply/damage", -amount/3);
	me->add_temp("apply/parry", -amount);
	me->add_temp("apply/dodge", -amount);
	me->add_temp("apply/defense", -amount);
	me->delete_temp("sanhua");
	message_vision(
	HIY "\n$N吸了一口气，将内力收回丹田！\n\n" NOR, me);

	return;
}

int help(object me)
{
        write(HIW"\n昊天掌之「三花聚顶」："NOR"\n");
        write(@HELP
	昊天掌是全真教前期武功之一，属于门中核心弟子所修武功
	全凭一口真气存在，绵绵不绝，运使劲气攻击对方。此门武
	功是全真高级武功的基础，全真弟子须认真修炼。
	三化聚顶掌是全真门派昊天掌的高深掌法，将先天功威力叠
	加在掌法中，短时间内提升掌法威力，同时瞬间连出三招，
	威力巨大，若功力深厚并设置得当可以将对方兵器打断。
	
	注意：set 昊天掌 断 其功效为打断对方兵器
		
	指令：perform strike.sanhua

要求：
	先天功法的等级 200  以上；
	鸳鸯连环腿等级 200  以上；
	基本腿法的等级 200  以上；
	最大的内力要求 1500 以上；
	当前内力的要求 800  以上；
	激发且备掌法为昊天掌；
	激发先天功；
	空手且备掌法为昊天掌。
HELP
        );
        return 1;
}

