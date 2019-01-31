//diao.c
//钓鱼式
//by sohu
//为大理早期鞭子入门武技
//源自诸万里，刀白凤

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int i,damage,skill;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("渔叟钓法只能对战斗中的对手使用。\n");

	if(me->query_skill("qingxu-bian",1) < 140)
		return notify_fail("你的「渔叟钓法」还不够娴熟，不会使用渔叟钓法。\n");
	if(me->query_skill("whip",1) < 140)
		return notify_fail("你的「基本鞭法」还不够娴熟，不会使用渔叟钓法。\n");
	if( !weapon 
		|| weapon->query("skill_type") != "whip"
		|| me->query_skill_mapped("whip") != "qingxu-bian" 
		|| me->query_skill_mapped("parry") != "qingxu-bian" ) 
		return notify_fail("你现在无法使用渔叟钓法。\n");

	if( me->query("neili") < 600 )
		return notify_fail("你的内力不够500。\n");
	if( me->query("jingli") < 500 )
		return notify_fail("你的精力不够500。\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("你的最大内力不够1500。\n");
	if( me->query("max_jingli") < 1300 )
		return notify_fail("你的最大精力不够1300。\n");
	if( target->is_busy() )
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");
	
	if (me->query("gender")=="男性"&&me->query("quest/dl/qxb/diao/pass")) i=3;
	else i=2;
	skill=me->query_skill("qingxu-bianfa",1);
	damage=me->query_skill("qingxu-bianfa",1)+me->query_skill("whip",1);
	damage=damage*me->query_dex()/10;
	damage=damage+random(damage);
	
	if (damage>3000) damage=3000+random(500);
	if (me->query("quest/dl/qxb/diao/pass"))
	{
		if (damage>4000) damage=4000+random(1000);
	}
	message_vision(HIW "\n$N忽然将手中的"+weapon->query("name")+HIW"一甩，使出「清虚鞭法」的"HIR"渔叟钓法"HIW"的功夫，钓鱼钩瞬间刺向$n的咽喉！\n"NOR,me,target);

	if(random(me->query("combat_exp") )> target->query("combat_exp")/i
		||random(me->query_dex(1)) > target->query_dex(1)/i)
	{
		message_vision(HIY "\n结果$p被$P一卷，圈住脖子，顿时气血一滞。\n" NOR,me,target);
		target->add_busy(1);
		target->apply_condition("no_exert",1);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
        if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);
			
		if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);

		if (me->query("quest/dl/qxb/diao/pass") &&me->query("env/清虚鞭法")=="钓钩")
		{
			
			message_vision(RED "\n$n被这兵器上的钓钩直接刺穿咽喉！\n"NOR,me,target);
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/3,me);
			if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);
			
			if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);

			if (!target->query_temp("qxb/diao"))
			{	
				message_vision(HIW "\n$N将手中的鞭子套成圆圈，将$n笼罩在内，顺势一拉，将$n紧紧地束缚起来！\n"NOR,me,target);

				target->add_temp("apply/attack",-skill/5);
				target->add_temp("apply/parry",-skill/5);
				target->add_temp("apply/dodge",-skill/5);
				target->set_temp("qxb/diao",skill);
				call_out("remove_diao",20,target);
			}
			target->add_busy(2);
		}
		//target->
	}
	else {
		message_vision(HIW "可是$p看破了$P的渔叟钓法，身子一跃便躲开了。\n" NOR,me,target);
		me->start_perform(1,"渔叟钓法");
	}
	//message_vision(msg, me, target);
	//me->start_perform(1,"渔叟钓法");
	message_vision(HIW"$N钓钩一转，瞬间化作流星，刺向$n面部，防不胜防！\n"NOR,me,target);
	me->add_temp("apply/damage",skill/5);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (me->query("quest/dl/qxb/diao/pass")&&me->query("env/清虚鞭法")=="钓钩")
	{
		message_vision(HIW"长鞭乃是柔软之物，被$n拦截瞬间，灌注了真气的钓钩豁然反刺，直奔$n眼部，端的是阴险毒辣！\n"NOR,me,target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	}

	me->add_temp("apply/damage",-skill/5);
	me->add("jingli", -50);
	me->add("neili", -100);
    return 1;
}
int remove_diao(object target)
{
	int skill;
	if (!target) return 0;
	skill=target->query_temp("qxb/diao");
	target->add_temp("apply/attack",skill/5);
	target->add_temp("apply/parry",skill/5);
	target->add_temp("apply/dodge",skill/5);
	target->delete_temp("qxb/diao");
	message_vision(HIW "\n$N长舒一口气，身中清虚鞭所造成的虚弱缓缓被恢复了！\n"NOR,target);

	return;	
}
string perform_name(){ return HIR"渔叟钓法"NOR; }

int help(object me)
{
        write(HIG"\n清虚鞭法之「渔叟钓法」："NOR"\n\n");
        write(@HELP
	清虚鞭法是大理家臣诸万里的功夫，诸万里是水军都督，熟悉
	水性，所以将钓鱼的心得和诀窍融入到清虚鞭法中，利用鞭法
	的独特优势，令人防不胜防。伤害和命中都与身法有关。

	set 清虚鞭法 钓钩 解开点仓渔隐的小秘密后有额外伤害

	指令：perform whip.diao
		
要求：  
	当前内力需求 600 以上；
	最大内力需求 1500 以上；
	当前精力需求 500 以上；
	最大精力需求 1300 以上；
	当前精力需求 500 以上；
	清虚鞭法等级 140 以上；
	基本鞭法等级 140 以上:
	激发鞭法为清虚鞭法；
	激发招架为清虚鞭法；
	且手持鞭子类兵器。

HELP
        );
        return 1;
}
