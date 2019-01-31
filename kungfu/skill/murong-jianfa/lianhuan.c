// lianhuan.c for murong-jianfa
// by snowman@SJ 01/05/1999.
// modify by leontt@SJ 26/09/2000.

#include <ansi.h>

inherit F_SSERVER;
int perform(object me,object target)
{
	object weapon;
	int i;
	int skill=me->query_skill("murong-jianfa",1);

	if( !target ) target = offensive_target(me);
	
	if( !target || !me->is_fighting(target) || !living(target)
	|| environment(target)!=environment(me))
		return notify_fail("七剑连环指只能对战斗中的对手使用。\n");

	if(me->query_skill_mapped("force") != "shenyuan-gong")
		return notify_fail("你的内功不是神元功，无法使用七剑连环指！\n");

	if( (int)me->query_skill("shenyuan-gong", 1) < 500 )
		return notify_fail("你的内功还未练成，不能使用七剑连环指！\n");

	if( (int)me->query_skill("murong-jianfa", 1) < 500 )
		return notify_fail("你的剑法还未练成，不能使用七剑连环指！\n");

	if(!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "murong-jianfa")
		return notify_fail("你手里没有剑，无法使用七剑连环指！\n");

    if((me->query_skill_mapped("parry") != "murong-jianfa")
        &&(me->query_skill_mapped("parry") != "douzhuan-xingyi"))
         return notify_fail("你的招架功夫不对，无法使用七剑连环指！\n");
	if( (int)me->query_skill("canhe-zhi", 1) < 500 )
		return notify_fail("你的参合指还未练成，不能使用七剑连环指！\n");
	if((int)me->query("max_neili") < 12000 )
		return notify_fail("你的内力修为不够，不能使用七剑连环指！\n");
	if((int)me->query("neili") < 1000 )
		return notify_fail("你现在真气不足，不能使用七剑连环指！\n");
	if((int)me->query("jingli") < 1000 )
		return notify_fail("你现在精力不足，不能使用七剑连环指！\n");
	if((int)me->query_temp("mrjf/lianhuan"))
		return notify_fail("你正在使用七剑连环指！\n");
	if(me->query_skill_mapped("finger") != "canhe-zhi"
	 || me->query_skill_prepared("finger") != "canhe-zhi")
		return notify_fail("你没有用指，无法使用七剑连环指！\n");
	if((int)me->query_skill("sword", 1) < 500 )
		return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用七剑连环指。\n");

	message_vision(MAG"\n$N"MAG"使出慕容剑法之精髓「七剑连环指」，但见$P右手食指在"+weapon->name()+MAG"上一弹，剑花朵朵相辉相映，直袭$n"MAG"！\n"NOR, me,target);
	me->set_temp("mrjf/lianhuan", 7);

	me->receive_damage("neili", 100);
	me->receive_damage("jingli", 100);
	
	me->add_temp("apply/attack", skill/3);
	me->add_temp("apply/damage", skill/4);

	//me->add_temp("apply/dodge",i/3);

	
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (me->query("quest/mr/dzxy/pass"))
	{
		message_vision(HIM"$N斗转星移神功威力大成,内功精湛，圆融汇通，内力转换间，已无凝滞！\n"NOR,me);
		me->start_perform(1, "「七剑连环指」");
		//i=14;
	}
	else {
		//i=7;
		me->start_perform(3, "「七剑连环指」");
	}
	i=7;
	call_out("check_fight", 1, me, i);
	return 1;
}


//退出程序
void remove_effect(object me)
{
	int skill;
	if(!me) return;
	skill=me->query_skill("murong-jianfa",1);

	me->delete_temp("mrjf/lianhuan");

    me->add_temp("apply/attack", -skill/3);
 
	me->add_temp("apply/damage", -skill/4);

	if (living(me))
		message_vision(HIY"\n$N"HIY"的「七剑连环指」绝技运行完毕，气回丹田，缓缓收功。\n"NOR, me);
	me->start_perform(5, "「七剑连环指」");
	return;
}
//检查状态
void check_fight(object me, int i)
{
	object weapon, target;

	if (!me ) return;

	target = offensive_target(me);

	if(i<0
	|| !living(me)
	|| !target
	|| !me->is_fighting(target)
	|| environment(target)!=environment(me)
	|| !me->query_temp("mrjf/lianhuan")
	|| me->query("neili") < 1000
	|| me->query("jingli") < 1000)
		return remove_effect(me);

	if(me->query_skill_mapped("sword") != "murong-jianfa") {
		tell_object(me, HIR"你临时改换剑法，决定不再使用「七剑连环指」绝技。\n");
		return remove_effect(me);
	
	}
    else if(me->query_skill_mapped("force") != "shenyuan-gong") {
		tell_object(me, HIR"你临时改换内功，决定不再使用「七剑连环指」绝技。\n");
		return remove_effect(me);
   } else if((me->query_skill_mapped("parry") != "murong-jianfa")
       &&(me->query_skill_mapped("parry") != "douzhuan-xingyi"))
   {
		tell_object(me, HIR"你临时改换招架，决定不再使用「七剑连环指」绝技。\n");
		return remove_effect(me);
	} 
    else if(!objectp(weapon = me->query_temp("weapon"))
		|| weapon->query("skill_type") != "sword")
	{
		tell_object(me, HIR"你临时改换武器，决定不再使用「七剑连环指」绝技。\n");
		return remove_effect(me);
	}
	else {
		me->receive_damage("neili", 50);
		me->receive_damage("jingli", 50);
		if (objectp(target) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		call_out("check_fight", 1, me, i--);
	}
}

string perform_name(){ return MAG"七剑连环指"NOR; }
int help(object me)
{
        write(HIG"\n慕容剑法之"+MAG"「七剑连环指」"NOR"\n\n");
        write(@HELP
	慕容剑法乃是南慕容武技中的精华招式，非核心弟子不传
	其剑法特点是兼容并包，融合天下剑法所长，但又别出心
	裁，与众不同。尤其是以慕容家传内功支持，则为例又更
	上一层楼。剑中夹杂指法，若解开斗转星移绝世武技，威
	力更上一层楼。

指令：perform sword.lianhuan

要求：
	当前内力需求 1000 以上；
	最大内力需求 12000 以上；
	当前精力需求 1000 以上；
	慕容剑法等级 500 以上；
	神元功法等级 500 以上；
	基本剑法等级 500 以上；
	激发剑法为慕容剑法；
	激发招架为慕容剑法或斗转星移；
	激发内功为神元功。
	激发指法为参合指
	手持剑类武技
HELP
        );
        return 1;
}