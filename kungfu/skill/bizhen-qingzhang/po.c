// po.c 碧针清掌绝招：凝碧破
// By sohu

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    object weapon;
    int damage, dp;
    string msg;

    if( !target ) target = offensive_target(me);

    if( !target || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("「凝碧破」只能对战斗中的对手使用。\n");

    if( (int)me->query_skill("bizhen-qingzhang", 1) < 200 )
        return notify_fail("你的碧针清掌不够娴熟，不会使用「凝碧破」。\n");

    if( (int)me->query_skill("strike", 1) < 200 )
        return notify_fail("你的基本掌法等级不够，无法使出「凝碧破」。\n");
    if( (int)me->query_skill("force", 1) < 200 )
        return notify_fail("你的基本内功等级不够，无法使出「凝碧破」。\n");
    if( me->query_skill_mapped("strike")!="bizhen-qingzhang" 
		||me->query_skill_prepared("strike")!="bizhen-qingzhang" )
        return notify_fail("你激发的掌法不对，无法使出「凝碧破」。\n");

    if( (int)me->query("neili", 1) < 1000 )
        return notify_fail("你现在内力太弱，强使凝碧破有损无益！\n");

    message_vision( HIG "$N双掌盘旋翻飞「凝碧破」幻化作一团绿影，突然间掌力疾吐，形成一股气旋，呈陀螺状，直奔$n各处要害！\n"NOR,me,target);

    if (living(target))
           dp = target->query_skill("force",1)/2;
    else    dp = target->query_skill("force",1)/4;

    if (random(me->query_skill("force",1)) > dp
		||random(me->query_str(1))>target->query_str(1)/2)
    {

        damage = (int)me->query_skill("bizhen-qingzhang", 1) + (int)me->query_skill("force",1);
		damage=me->query("str")*damage/10;
        damage = damage + random(damage) ;
		
        target->receive_damage("qi", damage,me);
		target->apply_condition("neishang",2);
        target->start_busy(4);
        message_vision(HIR"$N只觉全身大穴宛遭针刺，喉头一甜，口中鲜血如雨般喷出！\n"NOR,me);
    }
    else
    {
        me->start_busy(1);
        message_vision(CYN"$N见势不妙，连忙着地一滚，狼狈万状的避了开去。\n"NOR,target);
    }
	me->start_perform(3,"凝碧破");
	me->add("neili", -300);
    me->add("jingli", -100);

    return 1;
}
string perform_name() {return HIC"凝碧破"NOR;}

int help(object me)
{
   write(HIC"\n碧针清掌之「" HIG"凝碧破"HIC"」："NOR"\n\n");
   write(@HELP
	碧针清掌是摩天居士谢烟客的独门秘籍，一旦施展
	宛如巨浪排空，劲气极为汹涌，属于掌法中异常独
	特的一种功法。凝碧破是凝力于一点，然后瞬间爆
	破，将对方造成内伤的一门招式。
	
	指令：perform strike.po

要求: 
	当前内力需求 1000 以上；
	当前精力需求 1000 以上；
	碧针清掌等级 200 以上；
    基本内功等级 200 以上；
	基本掌法等级 200 以上；
	激发掌法为碧针清掌；
	内功不限；
	空手，备碧针清掌。

HELP
   );
   return 1;
}



