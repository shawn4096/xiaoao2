#include <ansi.h>
inherit F_SSERVER;

string perform_name() {return HIW"总诀式"NOR;}

int perform(object me, object target)
{
	string msg, *skill;
	object weapon;
	mapping skills;
	int i,lvl;
	
	lvl=me->query_skill("dugu-jiujian",1);
	if( !target ) target = offensive_target(me);

    if( !objectp(target)
	||  !target->is_character()
	||  !me->is_fighting(target) )
		return notify_fail("「总诀式」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");

	if((int)me->query_skill("dugu-jiujian",1) < 550 )
		return notify_fail("你的独孤九剑还不够火候，无法实施由利反钝的境界。\n");
    if((int)me->query_skill("sword",1) < 550 )
		return notify_fail("你的基本剑法还不够火候，无法实施由利反钝的境界。\n");
	if((int)me->query_skill("force",1) < 550 )
		return notify_fail("你的基本内功还不够火候，无法实施由利反钝的境界。\n");
	if((int)me->query("max_neili")<20000)
		return notify_fail("你的最大内力不够！\n"); 
	if((int)me->query("jingli")<1500)
		return notify_fail("你的精力不够！\n"); 
	if((int)me->query("neili")<2500)
		return notify_fail("你的当前内力不够！\n"); 
	if((string)me->query_skill_mapped("sword") != "dugu-jiujian" && userp(me))
		  return notify_fail("你现在无法使用「总诀式」！\n");

	if((string)me->query_skill_mapped("parry") != "dugu-jiujian" && userp(me))
		  return notify_fail("总决式需要激发独孤九剑，你现在无法使用「总诀式」！\n");


	if(target->query_temp("dgjj/zongjue") )
	       return notify_fail("对手已经中了「总诀式」了。\n");
	
	//if(me->query_temp("dgjj/zongjue") )
	       //return notify_fail("你现在正在向对手使用「总诀式」了。\n");

	
	message_vision(HBYEL+HIG"\n$N独孤九剑已然大成，剑上完全不出内力，剑随意行，毫无章法，但却招招指向$n的破绽所在！\n"NOR,me,target);
	
	message_vision(HIC"\n$N谨遵独孤九剑总决式的口诀「归妹趋无妄，无妄趋同人，同人趋大有。甲转丙，丙转庚，庚转癸。\n"
						+"子丑之交，辰巳之交，午未之交。风雷是一变，山泽是一变，水火是一变。乾坤相激，震兑相激，\n"
						+"离巽相激。三增而成五，五增而成九」,在「总诀式」剑意激发下，剑气大增！\n"NOR,me,target);
	
	if (!me->query_temp("dgjj/zongjue"))
	{	
		me->add_temp("apply/attack",lvl/3);
		me->add_temp("apply/damage",lvl/5);
		me->add_temp("apply/sword",lvl/3);
		me->add_temp("apply/parry",lvl/3);
		me->add_temp("apply/defense",lvl/3);	
		me->set_temp("dgjj/zongjue",lvl);	
		call_out("zongjue_effect",1,me,(int)lvl/20);
	}
	me->add("jingli",-800);
	me->add("neili",-1000);

    if ( random(me->query_int(1)) > target->query_int(1)/2
	 ||random(me->query("combat_exp")) > target->query("combat_exp")/2)
 //原设计参数为target->query_int(),暂时加强一下,经验值压制+悟性
    {
		
		message_vision(HBGRN+HIW"\n$n只觉得自己周身处处受制，武功为独孤九剑所尽破，那些厉害之处完全无法发挥出来！\n"NOR,me,target);
		skills = target->query_skill_map();
		if (!skills) return notify_fail("他并没有激发特殊技能。\n");
			skill = keys(skills);
		i = sizeof(skill);
		while (i--)
			target->map_skill(skill[i]);
		target->delete("jiali");

		target->set_temp("no_enable",1);
		target->set_temp("dgjj/zongjue",1);
		
		me->start_perform(2,"总决式");
		me->add_busy(1);
		me->set("jiali",0);
		if (objectp(target))
			call_out("remove_effect",(int)me->query_skill("dugu-jiujian",1)/10,me,target);
	} 
	else {
		message_vision(HIG"\n$n灵机一动，身随剑走，果然$N的总决剑式再也无法达到随意出招的境界。\n"NOR,me,target);
		me->add_busy(2);
		me->start_perform(4,"总决式");
	}
	return 1;
}

void remove_effect(object me, object target)
{
	if (!objectp(target))return;
	
	//if (me) me->delete_temp("dgjj/zongjue");

	if (target) target->delete_temp("no_enable");
	if (target) target->delete_temp("dgjj/zongjue");
	return;
}

void zongjue_effect(object me, int count)
{
        int skill;
		object weapon;
        if (!me) return;
		weapon=me->query_temp("weapon");

		skill=me->query_temp("dgjj/zongjue");
		if (count<0
		    ||!me->is_fighting()
			||me->query_skill_mapped("sword")!="dugu-jiujian"
			||me->query_skill_mapped("parry")!="dugu-jiujian"
			||!weapon
			||weapon->query("skill_type")!="sword")
		{
			me->add_temp("apply/attack",-skill/3);
			me->add_temp("apply/damage",-skill/5);
			me->add_temp("apply/sword",-skill/3);
			me->add_temp("apply/parry",-skill/3);
			me->add_temp("apply/defense",-skill/3);
			me->delete_temp("dgjj/zongjue");
			message_vision(HBGRN+HIW"\n$N独孤九剑之「总诀式」缓缓收招，由动入静，弥漫的剑气逐渐消散。\n"NOR,me);
			return;
		}
		call_out("zongjue_effect",1,me,count--);
		return;
}

int help(object me)
{
	write(HIG"\n独孤九剑「总决式」："NOR"\n");
	write(@HELP
	独孤九剑招招进攻，无需防守，其中关键就是快捷和料敌机先，
	招招制敌。当然这其中运独孤九剑剑意非常重要，破敌之招数，
	以无招胜有招。独孤九剑号称破解天下武技，乃当世绝技。
	550级后融会贯通，招式连贯，由利反钝，返璞归真，任意施展。
	
	指令：perform sword.zongjue

要求：
	基本内功需求 550  以上；
	独孤九剑等级 550  以上；
	基本剑法等级 550  以上；
	当前精力需求 1500 以上；
	当前内力需求 2500 以上；
	最大内力需求 20000 以上；
	激发独孤九剑为剑法；
	激发独孤九剑为招架；
	在战斗中持剑使用。
HELP
        );	
        return 1;
}
