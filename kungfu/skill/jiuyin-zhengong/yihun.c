// 我认为中了yihun应该100%打中自己。主要判断pfm是否命中。。 
#include <ansi.h>
inherit F_SSERVER;

int exert(object me, object target)
{       
	int skill, ap, dp;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
        || !me->is_fighting(target)
        || !necessary(target) )
		return notify_fail("移魂大法只能对战斗中的对手使用。\n");
    if ((int)me->query_skill("jiuyin-zhengong", 1) < 450)
		return notify_fail("你的九阴真功修为还不够。\n");
	if ((int)me->query_skill("force", 1) < 450)
		return notify_fail("你的基本内功修为还不够。\n");
    if (me->query_skill_mapped("force")!="jiuyin-zhengong")
		return notify_fail("你激发的内功不对。\n");
	if( (int)me->query("int") < 40 )
                return notify_fail("你的先天悟性不够。\n");

	if( (int)me->query("neili") < 2000 )
		return notify_fail("你的真气不够。\n");

	skill = me->query_skill("jiuyin-zhengong",1);

    ap = me->query_skill("force",1);
    dp = target->query_skill("force",1)/3;

	message_vision(HIW"$N脸上突然开始做出各样奇怪的表情，诡异的很，仿佛有一种魔力在吸引$n,$n下意识多看了一眼。\n"NOR, me, target);

    if (random(me->query_int()) > target->query("int")/2) 
    {
        int qi2 = target->query("qi");
        message_vision(HIW"$n正准备取笑$N，茫然间下意识间却不知不觉的学起$N的表情动作。\n"NOR, me, target);
		message_vision(HIR"$N猛然做出向自己攻击的动作，$n立刻向自己发疯似的攻击起来，出手越来越重！\n"NOR, me, target);
		target->add_temp("apply/attack",skill/3);
		target->add_temp("apply/damage",skill/3);
        target->set_temp("must_be_hit",1);

        COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 3);
        if( me->is_fighting(target)&& random(2))
			COMBAT_D->do_attack(target, target, target->query_temp("weapon"),3);
        if( me->is_fighting(target)) 
			COMBAT_D->do_attack(target, target, target->query_temp("weapon"),3);
        if(objectp(target))
          {
			target->add_temp("apply/attack",-skill/3);
			target->add_temp("apply/damage",-skill/3);
            target->delete_temp("must_be_hit");

			if(qi2 > target->query("qi")) target->set_temp("last_damage_from", me);
           }
	        me->add("neili", - 350);
	        me->add("jingli", -100);
	}
	else {
		    message_vision(HIW"不管$N怎么变化表情，$n心中冷哼一声，不为所动。\n"NOR, me, target); 
	        me->add("neili", - 150);
	        me->add("jingli", -50);
	}
    me->start_exert(3, "「移魂大法」");
	if ( !me->is_perform())
		me->start_perform(2, "「移魂大法」");
	return 1;
}

string exert_name(){ return HIG"移魂大法"NOR; }

int help(object me)
{
        write(HIG"\n九阴真功之「移魂大法」："NOR"\n\n");
        write(@HELP
		九阴真经乃是武林奇侠黄裳所著，他遍历道藏，深悟阴阳
		这部九阴真经博大精深，乃武林顶级绝学。其中移魂大法
		是将内功运使在目中，使得对方陷入茫然而不知觉。端的
		是阴险毒辣的狠招。
		要求：
			当前内力 2000 以上；
			先天悟性 40 以上；
			九阴真功等级 450 以上。
			基本内功等级 450 以上。

HELP
        );
        return 1;
}
