// ci.c canhe-zhi perform 刺字诀
// by leontt 1/5/2000
// modified by darken to reduce busy time

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
	string msg;
	int improve, ap, dp, skill, i,c;

	if( !target ) target = offensive_target(me);

         if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
		return notify_fail("「刺字诀」只能在战斗中对对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手使用「刺字诀」！\n");

	if( (int)me->query_skill("canhe-zhi",1) < 450 )
		return notify_fail("你的参合指不够娴熟，不会使用「刺字诀」！\n");

	if( (int)me->query_skill("shenyuan-gong",1) < 450 )
		return notify_fail("你的神元功等级不够，不能使用「刺字诀」！\n");

	if( (int)me->query_str(1) < 60 )
		return notify_fail("你的臂力不够强，不能使用「刺字诀」！\n");

	if( (int)me->query("max_neili") < 3000 )
		return notify_fail("你的内力太弱，不能使用「刺字诀」！\n");	
	
	if( (int)me->query("neili") < 1000 )
		return notify_fail("你的内力太少了，无法使用出「刺字诀」！\n");

	if (me->query_skill_prepared("finger") != "canhe-zhi"
	|| me->query_skill_mapped("finger") != "canhe-zhi")
		return notify_fail("你现在无法使用「刺字诀」进行攻击。\n");

    if ( me->query_skill_mapped("force") != "shenyuan-gong")
        return notify_fail("没有神元功支持如何使用「刺字诀」！\n");
	if ( me->query_skill_mapped("parry") != "canhe-zhi"
	&& me->query_skill_mapped("parry") != "douzhuan-xingyi")
		return notify_fail("你现在无法使用「刺字诀」进行攻击。\n");
	
	
	if( target->query_temp("chz/ci"))
	       return notify_fail("对方已经中了你的刺字诀,你正在使用参合指的特殊攻击「刺字诀」！\n");
	
	msg = HIC"\n$N突然一掌拍在自己的丹田上激荡全身的内力形成一股「"HIR"剑气"HIC"」，从右手拇指激射而出，刺向$n的肩部。\n" NOR;
	message_vision(msg, me, target);

//	pfm ci 中不出 aut pfm 的标记 by lane
//	me->set_temp("chz/ci", 1);


	ap = me->query_skill("finger",1);
	dp = me->query_skill("parry",1);

	if ( target->is_busy())
		dp -= dp/3;

	skill = me->query_skill("canhe-zhi", 1);

	i = skill/3+me->query_skill("shenyuan-gong",1)/3;
	if ( skill > 275 )
		i = to_int( skill/3 * skill/275);
	//意味着550级后威力翻翻
	
	
	
	if(	random(ap + dp) > dp 
		||random(me->query_str(1))>target->query_str(1)/2)
	{
		
		msg = HIR"$n的肩关节一酸，双臂立时失去知觉，动弹不得。\n"NOR;
		message_vision(msg, me, target);
		target->add_condition("no_perform", 1);
		target->add_condition("neishang", 2);
		target->add_busy(random(1)+1);   
		
		
		
		if (!userp(target)) c=i*2;
		else c=i;
        
		me->add_temp("apply/damage", c/6);
		
	
		if (present(target,environment(me)) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		
		me->add_temp("apply/damage",-c/6);
		
		if (objectp(target)&&!target->query_temp("chz/ci"))
		{
			improve = me->query_str(); //由先天改为后天，变相提高威力				
			target->add_temp("apply/strength", -improve/2);
			target->set_temp("chz/ci", improve/2);

			call_out("remove_effect", 5, target ,improve/2,);//(int)me->query_skill("finger",1)/30  这里时间太久容易出bug
		}

		if (random(me->query_str())>target->query_str()/2)
		{
			target->receive_damage("qi", 2000, me);
			target->receive_wound("qi", 1000, me);
			message_vision(HIR "只听“噗嗤”一声，指力竟在$n胸前穿了一个血肉模糊的大洞，透体而入。\n" NOR,me,target);
		}		
		
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	else {
		msg = CYN"$n纵身一跃，敏捷地躲过了$N的这一招！\n"NOR;
		message_vision(msg, me, target);
		me->add_busy(1);
	}

	me->start_busy(random(1));
	me->add("neili", -500);
	me->add("jingli", -280);

	//me->start_perform(4, "「刺字诀」");  //这些不能去掉，不然就成机关枪了
	return 1;
}

void remove_effect(object target, int improve)
{
	if(!target) return;
	target->add_temp("apply/strength", improve);
	target->delete_temp("chz/ci");
	tell_object(target, HIR"\n你运气一周脸色好了许多，只觉得双臂已经恢复了原状。\n"NOR);
}

string perform_name(){ return HIC"刺字诀"NOR; }

int help(object me)
{
        write(HIC"\n参合指之「刺字诀」"NOR"\n\n");
        write(@HELP
	参合指是南慕容氏的绝学，参商相隔，斗转星移，是南慕容
	家传的绝世武技，参合指以强大的内力将内力激发出来，和
	对方搏斗，若习得参合指的绝世秘籍，并不弱与天下其他门
	派的指法绝技。
	刺字诀乃是以斗转星移之术演习少林金刚指力之意，一招刺
	或刺穿对方的身体要害，或一招刺中对方臂膀，虚弱对方。

指令：perform finger.ci

要求：
	当前内力 1000 以上；
	最大内力 3000 以上；
	参合指等级 450 以上；
	神元功等级 450 以上；
	激发指法为参合指；
	备指法为参合指；
	臂力不小于60。
	且手无兵器,

HELP
        );
        return 1;
}
                                
