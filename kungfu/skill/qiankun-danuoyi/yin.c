#include <ansi.h>
inherit F_SSERVER;
int check_fight(object me);
string perform_name(){ return HIG"引字诀"NOR; }

int perform(object me,object target,string arg)
{
	//int ski;
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「引」字诀只能对战斗中的对手使用。\n");

	if(!me->is_fighting())
		return notify_fail("你没在战斗中呢！\n");

	if(me->query_skill("qiankun-danuoyi", 1) < 400 )
		return notify_fail("你的乾坤大挪移还未练到第七层。\n");

	if (!me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 400 )
		return notify_fail("你的圣火神功等级不够。\n");

	if(me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("你没有使用乾坤大挪移作为招架！\n");

	if((int)me->query("neili") < 5000)
		return notify_fail("你目前的内力不够。\n");
    if (!me->query("mjqkdny/pass"))  //融合后乾坤大挪移将发生飞跃
    {
		if((int)me->query_temp("qkdny/yi") )
		    return notify_fail("你正在施展「移」字诀呢！\n");
	    if((int)me->query_temp("qkdny/xu") )
		    return notify_fail("你正在施展「蓄」字诀呢！\n");
    	if((int)me->query_temp("qkdny/hua") )
	    	return notify_fail("你正在施展「化」字诀呢！\n");
        me->start_perform(1, "引字诀");
		//ski=150;
    }
	
	if((int)me->query_temp("qkdny/yin") )
		return notify_fail("你正在施展「引」字诀呢！\n");

	if(target->query_temp("qkdny/yin"))
		return notify_fail( target->query("name") +"正在使用「引」字诀呢。\n");

	me->add("neili", -400);
	tell_object(me,HIG"\n你运起乾坤大挪移心法，缓下了攻击，使用「引」字诀，凝神专注牵引。\n"NOR);
	me->set_temp("qkdny/yin", 1);
	//me->set_temp("lost_attack", 1);
	//if (me->query_skill("qiankun-danuoyi",1)<450)
	  // me->start_perform(2, "引字诀");
	me->add_temp("apply/dodge", -150);
	me->add_temp("apply/parry", -150);
	check_fight(me);
	return 1;
}

int check_fight(object me)
{
	if (!me || !me->query_temp("qkdny/yin")) return 0;

	if(me->is_ghost() 
	 || !living(me)
	 || !me->is_fighting()
	 || (me->query("jingli") < 500)
	 || (me->query("neili") < 500)
	 || (me->query("jing") < 500))
	 {
		tell_object(me, HIG"\n你将乾坤大挪移引字诀的招数缓缓收功。\n"NOR);		
		me->add_temp("apply/dodge", 150);
		me->add_temp("apply/parry", 150);
		me->delete_temp("qkdny/yin");
	 }
	else {
		//me->set_temp("lost_attack", 1);
		call_out("check_fight", 1, me);
	}
	return 1;
}

int help(object me)
{
        write(HIG"\n乾坤大挪移「引字诀」"NOR"\n");
        write(@HELP
	《倚天屠龙记》中张无忌的招牌武功，在中原明教的禁地中习得。
	功法源自波斯拜火教，乃镇教之宝，武学道理多元精妙，变化神
	奇，是西域武林最巅峰的武功。此功分七层境界，悟性高者修习，
	第一层需七年，第二层加倍，如此愈发困难，秘笈作者本人只练
	至第六层，习至第七层者实是古往今来第一人。主要有九大功能，
	包括激发最大潜力，集武功道理大成，制造对手破绽，积蓄劲力，
	粘住掌力，牵引挪移敌劲，反击对手，转换阴阳二气，借力打力
	等。
	特别注意：若解开乾坤大挪移的第七层神功时，乾坤大挪移可以
	自由使用各个绝技,
	
	perform parry.yin

要求：
	当前内力 5000 以上；
	乾坤大挪移等级 400 以上；
	基本内功等级 400 以上；
	圣火神功等级 400 以上；
	激发招架为乾坤大挪移。
	解密融合后会产生飞跃。
HELP
        );
        return 1;
}
