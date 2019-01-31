// This program is a part of NITAN MudLIB
// jiejian.c 华山剑法「截剑式」
// edit by sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

#define JIE "「" HIB "截剑式" NOR "」"

int perform(object me, object target)
{
	object weapon;
    int level,skill;
	string msg;
	skill = me->query_skill("huashan-jianfa", 1);
	level=skill/250;
	if (! target) target = offensive_target(me);
	

	if (! target || ! me->is_fighting(target))
		return notify_fail(JIE "只能对战斗中的对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if (!me->query("quest/hs/hsjf/jiejian/pass"))
		return notify_fail("你只是听说过这招，尚未领悟贯通，你需向门中长老请教该招奥妙。\n");
	if (target->is_busy())
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
		
	if (skill < 350)
		return notify_fail("你的华山剑法不够娴熟，无法施展" JIE " 。\n");

    if (me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("你没有激发华山剑法，无法施展" JIE "。\n");

    if (me->query("neili") < 1000)
                return notify_fail("你现在真气不够，无法使用" JIE "。\n");
	if (me->query("jingli") < 600)
                return notify_fail("你现在真气不够，无法使用" JIE "。\n");
    if (!living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
	//message_vision();

    msg = HIW "\n但见$N" HIW "手中"+weapon->query("name")+HIW"一勒，使出华山剑法绝技之"
              "「" HIG "截剑式" HIW "」，转折之际天衣无缝，一"
              "\n剑既出，后着源源倾泻，如大浪跃滩，层层叠叠，迅"
              "然扑向$n" HIW "！\n" NOR;

    me->add("neili", -150);
	me->add("jingli", -100);
	if (random(skill) > (int)target->query_skill("parry", 1) / 2
		||random(me->query_int(1))>target->query_int(1)/2)
    {
		msg += HIR "结果$p" HIR "瘁不及防，连连倒退几步，一时间无法回手！\n" NOR;
		target->add_busy(level);
		
	} else {
                if (objectp(weapon = target->query_temp("weapon")))
        		msg += CYN "但是$p" CYN "识破了$P" CYN "的用意，"
                               "自顾将手中的" + weapon->query("name") +
                               CYN "\n舞成一团光花，$P"
                               CYN "一怔之下再也攻不进去。\n" NOR;
                else
                        msg += CYN "但是$p" CYN "双手戳点刺拍，将$P"
                               CYN "的来招一一架开。\n" NOR;

				me->add_busy(1);
	}
	message_vision(msg, me, target);
	
	return 1;
}

string perform_name() {return HBBLU+HIW"截剑式"NOR;}

int help(object me)
{
	write(WHT"\n华山剑法「"HIB"截剑式"WHT"」："NOR"\n");
	write(@HELP
    截剑式原本是华山普通的招式，但其中蕴含的剑意甚是奥妙
	风清扬曾在华山后山，指点令狐冲，将几招连起来一起使用
	直至截剑式而化为金玉满堂，将一代枭雄田伯光制服。招式
	倘若能明白华山剑法的奥义，此招将使得对手陷入绝境
	注意：此招命中和个人武技等级以及悟性有关。
	    
	指令：perform swrod.jiejian

要求：
	华山气功等级 350 级；
	或者紫霞神功 350 级
	基本剑法等级 350 级
	基本轻功等级 350 级，
	当前内力要求 1000 以上，
	当前精力要求 600  以上。
	激发剑法华山剑法；
	激发招架华山剑法
	手持剑类武器；
HELP
	);
	return 1;
}
