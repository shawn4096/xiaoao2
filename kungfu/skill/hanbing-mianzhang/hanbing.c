// HANBING.c 寒冰绵劲
// By sohu@xojh
#include <ansi.h>

inherit F_SSERVER;
void remove_effect(object me, int count);

int perform(object me,object target)
{
	string msg;
	int skill, i, ap, dp;
	skill = me->query_skill("hanbing-mianzhang",1);
	

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !me->is_fighting(target))
		return notify_fail("你只能对战斗中的对手使用「寒冰绵劲」。\n");

	if( me->query_temp("weapon"))
		return notify_fail("你拿着武器怎么能使用「寒冰绵劲」！\n");

	if( skill < 350 )
		return notify_fail("你的「寒冰绵掌」等级不够, 还不能使用「寒冰绵劲」！\n");

	if( me->query_skill_mapped("strike") != "hanbing-mianzhang")
		return notify_fail("你没有激发寒冰绵掌，现在无法使用「寒冰绵劲」！\n");

	if (me->query_skill_prepared("strike") != "hanbing-mianzhang")
		return notify_fail("你现在准备好寒冰绵掌，无法使用「寒冰绵劲」！\n");

	if ( me->query_skill_mapped("parry") != "qiankun-danuoyi"
	 && me->query_skill_mapped("parry") != "hanbing-mianzhang")
		return notify_fail("你现在无法使用「寒冰绵劲」！\n");

	if( me->query_skill("dodge", 1) < 350 )
		return notify_fail("你的轻功不够，无法熟练运用「寒冰绵劲」！\n");

	if( !me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 350)
		return notify_fail("你的圣火神功等级不够，无法使用「寒冰绵劲」！\n");

	if((int)me->query("neili") < 3000)
		return notify_fail("你的内力不够使用「寒冰绵劲」。\n");
    if(target->query_condition("hb_poison") )
		return notify_fail("对方已经身中寒冰绵掌毒，无需使用寒冰绵劲！\n");
    if( me->query_temp("hbmz/hb") )
		return notify_fail("你正在施展「寒冰绵劲」！\n");
	if((int)me->query("jingli") < 1200)
		return notify_fail("你的精力不够使用「寒冰绵劲」。\n");

	msg = HIW"\n$N用强大内力来激发寒冰绵掌功夫，周身腾起一层薄薄的寒气，手上的力道显然增强了不少。\n"NOR;
    me->set_temp("hbmz/hb",skill);
	ap = me->query("combat_exp") /10000;
	dp = target->query("combat_exp") /10000;
    me->add_temp("apply/attack",skill/3);
    me->add_temp("apply/damage",skill/6);
	me->add_temp("apply/strike",skill/5);
	if( (random(ap + dp) > dp 
		|| random(me->query_dex(1))>target->query_dex(1)/2)&& living(target) ) {
		msg += HIY"$n为$N掌上散发的寒气所迫，忍不住打了个寒颤，身形顿时为之一缓！\n"NOR;
		target->start_busy(1+random(2));
		if (!userp(target))
		   target->add_busy(2);
		if (!random(3))
		  target->apply_condition("hb_poison",1+random(3));
	} else msg += HIC"$n轻身闪过，避开了$N的这记狠招！\n"NOR;
	 
//	 call_out("remove_effect",0,me,(int)skill/20);
	 remove_effect(me,(int)skill/20);
	 if (skill<350) {
	     me->start_perform(2, "寒冰绵劲");
	     me->start_busy(random(2));	
	 }
	
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
	return 1;
}


void remove_effect(object me,int count)
{
	int amount;
	object weapon;
	if (!me) return;
//	if (!me->is_fighting()) count=0;
	weapon=me->query_temp("weapon");

	amount = me->query_temp("hbmz/hb");
	
	if( count < 0
		|| weapon
		||!me->is_fighting() 
		|| me->query_skill_prepared("strike")!="hanbing-mianzhang" 
		|| me->query_skill_mapped("strike")!="hanbing-mianzhang" )
	{
			
        me->add_temp("apply/attack",-amount/3);
        me->add_temp("apply/damage",-amount/6);
        me->add_temp("apply/strike",-amount/5);
        me->delete_temp("hbmz/hb");
		tell_object(me, HIW"你手上的寒冰绵掌劲气渐渐散去,力道明显弱了不少。\n"NOR);
		return;
		
	} 
	call_out("remove_effect",1,me,count--);
}


string perform_name(){ return HIW"寒冰绵劲"NOR; }

int help(object me)
{
        write(HIC"\n寒冰绵掌之"+HIW"「寒冰绵劲」"NOR"\n\n");
        write(@HELP
	寒冰绵劲乃是青翼蝠王独门武技，运使周身寒气聚集在手
	掌之上，使对手中毒。350级后大飞。为寒冰绵掌重要的
	辅助进攻武技功能。命中与战斗经验或身法有关
	
	指令：perform strike.hanbing
	注意：
		set 寒冰绵掌 寒气 主要效果是让对方中毒
		set 寒冰绵掌 吸血 主要效果是随机吸对方气和精
	
要求：  
	当前内力 3000 以上；
	当前精力 1200 以上；
	寒冰绵掌等级 350 以上；
	圣火神功等级 350 以上；
	基本轻功等级 350 以上；
	激发掌法为寒冰绵掌；
	激发招架为寒冰绵掌或乾坤大挪移。

HELP
        );
        return 1;
}
