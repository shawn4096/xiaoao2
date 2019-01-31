//Update By lsxk@hsbbs 2007/6/11

#include <ansi.h>
inherit F_SSERVER;
int check_fight(object me, object target);
string perform_name(){ return HIW"化字诀"NOR; }

int perform(object me, object target)
{
	int ap , dp;

	if(!target) target = offensive_target(me);

	if(!objectp(target) || !me->is_fighting(target))
		return notify_fail("你没在和对方战斗呢！\n");

	if( me->query_skill("qiankun-danuoyi", 1) < 400 )
		return notify_fail("你的乾坤大挪移还未练到第七层。\n");

	if (!me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 400 )
		return notify_fail("你的圣火神功等级不够。\n");

	if( me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("你没有使用乾坤大挪移作为招架！\n");

	//if( me->query("neili") > me->query("max_neili"))
	//	return notify_fail("你目前的内力太强，无法使用化字诀！\n");

	if( me->query("neili") < 4000 )
		return notify_fail("你的内力不够，无法使用化字诀！\n");

	
    if (!me->query("mjqkdny/pass"))
    {
		if( me->query("jiali") >= 20)
			return notify_fail("你目前的加力太大，无法使用化字诀！\n");
		if( me->query_temp("qkdny/yi") )
		    return notify_fail("你正在施展「移」字诀呢！\n");
	    if( me->query_temp("qkdny/xu") )
	    	return notify_fail("你正在施展「蓄」字诀呢！\n");
	    if( me->query_temp("qkdny/yin") )
		    return notify_fail("你正在施展「引」字诀呢！\n");
        me->start_perform(2, "「化」字诀");
    }
	if( me->query_temp("qkdny/hua") )
		return notify_fail("你正在施展「化」字诀呢！\n");

	    me->add("neili", -100-random(100));
	
        ap = me->query("combat_exp", 1) * me->query_int(1)/500;//防止数据溢出
        dp = target->query("combat_exp", 1) * target->query_int(1)/500;//防止数据溢出

	tell_object(me,HIW"\n你深深的吸了口气，口中默念「化」字诀，招数变的轻柔缓慢。\n"NOR);

	me->set_temp("qkdny/hua", 1);
//高悟性会增加对方no_pfm功能
	if ( random(ap + dp) > dp ) {
		tell_object(me, "你突然轻柔缓慢的出招，让"+target->name(1)+"一下子觉得很难适应。\n"NOR);
		tell_object(target, me->name(1)+"突然轻柔缓慢的出招，让你一下子觉得很难适应。\n"NOR);
		target->add_condition("no_perform",random(3)+1);
	}
	check_fight(me, target); 
        return 1;
}

int check_fight(object me, object target)
{
	if (!me || !me->query_temp("qkdny/hua")) return 0;

	if(me->is_ghost() || !living(me))
		me->delete_temp("qkdny/hua");

	if(!me->is_fighting()
	 || me->query("jiali") > 9
	 || me->query("jingli") < 500
	 || me->query("jing") < 500 
	 || !target ){
		tell_object(me, HIW"\n慢慢你的招数又恢复了平常。\n"NOR);
		me->delete_temp("qkdny/hua");
	}
	else call_out("check_fight", 1, me, target);
	return 1;
}

int help(object me)
{
        write(HIW"\n乾坤大挪移「化字诀」："NOR"\n");
        write(@HELP
	《倚天屠龙记》中张无忌的招牌武功，在中原明教的禁地中
	习得。功法源自波斯拜火教，乃镇教之宝，武学道理多元精
	妙，变化神奇，是西域武林最巅峰的武功。此功分七层境界
	悟性高者修习，第一层需七年，第二层加倍，如此愈发困难
	秘笈作者本人只练至第六层，习至第七层者实是古往今来第
	一人。主要有九大功能，包括激发最大潜力，集武功道理大
	成，制造对手破绽，积蓄劲力，粘住掌力，牵引挪移敌劲，
	反击对手，转换阴阳二气，借力打力等。
	特别注意：若解开乾坤大挪移的第七层神功时，乾坤大挪移
	可以自由使用各个绝技。
	
	使用指令：perform parry.hua
	
要求：
	当前内力的需求 4000 以上；
	未融合要加力需 20 以下；
	乾坤大挪移等级 400 以上；
	基本内功的等级 400 以上；
	激发招架为乾坤大挪移。
	解密融合后会产生飞跃。
HELP
        );
        return 1;
}
