//tiexian.c 铁布衫绝技
//by sohu
//张阿生

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIW"铁布衫绝技"NOR; }

int perform(object me, object target)
{
	object weapon;
	int skill;


	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「铁布衫绝技」只能对战斗中的对手使用。\n");

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("你必须空手才能此招。\n");

	if( (int)me->query_skill("tiexian-quan", 1) < 100 )
		return notify_fail("你的铁线拳法不够娴熟，无法使用铁布衫绝技。\n");

	if ( me->query_skill_mapped("cuff") != "tiexian-quan"
	|| me->query_skill_mapped("parry") != "tiexian-quan")
		return notify_fail("你现在无法使用铁布衫绝技。\n");

	if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("你的基本内功不够高。\n");
	if( (int)me->query_skill("cuff", 1) < 100 )
		return notify_fail("你的基本拳法不够高。\n");

	if((int)me->query("max_neili") < 3000 )
		return notify_fail("你的最大内力修为不够，无法使用「铁布衫绝技」。\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("你当前内力太弱，不能使用「铁布衫绝技」。\n");
	if( me->query_temp("txq/tiebushan") )
		return notify_fail("你正在使用「铁布衫绝技」。\n");
	message_vision(WHT "\n$N暗自运功，运转不绝，劲气布慢周身，施展出铁线拳的「铁布衫」绝技！\n"NOR,me);
	me->add_temp("apply/armor",skill/6);
	me->add_temp("apply/defense",skill/5);
	me->add_temp("apply/constitution",skill/30);
	me->set_temp("txq/tiebushan",skill);

	call_out("remove_effect",1,me,(int)skill/50);

	
	return 1;
}
int remove_effect(object me,int count)
{
	int skill;
	if (!me) return 0;
	skill=me->query_temp("txq/tiebushan");
	if (!me->is_fighting()
		||count<0)
	{
		me->add_temp("apply/armor",-skill/6);
		me->add_temp("apply/defense",-skill/5);
		me->add_temp("apply/constitution",-skill/30);
		me->delete_temp("txq/tiebushan");
		message_vision(WHT "\n$N突出一口浊气，「铁布衫」绝技缓缓收功！\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me,count--);
	
}
int help(object me)
{
        write(CYN"\n铁线拳之「铁布衫绝技」："NOR"\n");
        write(@HELP
	铁线拳乃是江南奇怪老五张阿生的绝学，因其常年在屠宰
	场所和蛮牛角力，练就了一声横练功夫，铁线拳一方面是
	攻敌成线，颇为耗费内力，同时也具有一定铁布衫的功效

	指令：perform cuff.tiebushan

要求：  
	最大内力需求  1400 以上；
	当前内力需求  500  以上；
	基本拳法等级 250 以上；
	基本内功等级 250 以上；
	铁线拳法等级 100 以上；
	激发拳法铁线拳；
	激发招架铁线拳；
	空手且备铁线拳；
HELP
        );
        return 1;
}
                                                                                                                                                    