// jinzhen.c 金针渡劫
// by sohu@xojh 2014

#include <ansi.h>
#include <combat.h>
int strike_attack(object me,object target);

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage,skill;
        string msg;
		object weapon;
		skill=me->query_skill("liangyi-jian",1);
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
			return notify_fail("「金针渡劫」只能对战斗中的对手使用。\n");
		if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "sword")
            return notify_fail("开什么玩笑，没装备剑就想使「金针渡劫」？\n");
                
		if( (int)me->query_skill("liangyi-jian",1)<200)
			return notify_fail("你的正两仪剑法不够娴熟，不会使用「金针渡劫」。\n");
		if( me->query_skill_mapped("sword")!="liangyi-jian"
			||me->query_skill_mapped("sword")!="liangyi-jian")
			return notify_fail("你没有激发正两仪剑法，不会使用「金针渡劫」。\n");

		if( (int)me->query_skill("xuantian-wuji",1)<200)
			return notify_fail("你的玄天无极功不够深厚，不会使用「金针渡劫」。\n"); 
		if( (int)me->query_skill("sword",1)<200)
			return notify_fail("你的基本剑法不够深厚，不会使用「金针渡劫」。\n"); 
        if( (int)me->query("max_neili",1)<1500)
			return notify_fail("你现在最大内力太弱，不能使用「金针渡劫」。\n");                
		if( (int)me->query("neili",1)<400)
			return notify_fail("你现在当前内力太弱，不能使用「金针渡劫」。\n");
		if( (int)me->query("jingli",1)<300)
			return notify_fail("你现在当前精力太弱，不能使用「金针渡劫」。\n");
		if( (int)me->query_dex(1)<50)
			return notify_fail("你现在有效身法太弱，不能使用「金针渡劫」。\n");	
	                        
		message_vision(HIW "$N双手举起手中"+weapon->query("name")+HIW"，凝神聚力,使出昆仑派两仪剑法中的起手式"HIR"「金针渡劫」。\n" NOR,me);
				
		
        if (random(me->query("neili")) > target->query("neili")/3 
			||random(me->query_dex())>target->query_dex()/2 )
		{
			               
			message_vision(HIR "$N这招「金针渡劫」招式简单，但配合两仪决施展，威力奇大，$n只觉躲无所躲，被一剑刺中。\n" NOR,me,target);
			damage= skill+(int)me->query_skill("dodge",1)+(int)me->query_skill("xuantian-wuji",1);
			damage = damage*2 + random(damage);                
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/2,me);

			//msg=HIY"这招由正互变为反，正招反施，顿时威力大增！\n"NOR;
			if( damage < 2000 ) 
				msg = HIY"结果$n被$N刺中了一剑，闷哼一声，顿时鲜血如注。\n"NOR;
			else if( damage < 3000 ) msg = HIY"结果$n被$N连刺两剑，「啊」地一声退了两步。\n"NOR;
			else if( damage < 5000 ) msg = RED"结果$n被$N重重的连砍数剑，有如受到数记雷击一般，连退了五六步！\n"NOR;
			else msg = HIR"结果$n被$N的「金针渡劫」剑透前心，眼前一黑，身子向后飞出丈许！！\n"NOR;
			message_vision(msg, me, target);
			if (objectp(me)&&me->is_fighting())
				call_out("strike_attack",1,me,target);
		}
		else
		{
			me->start_busy(1);
            msg = CYN"可是$p看破了$P的企图，并没有上当。\n"NOR;
			message_vision(msg, me, target);
		}
		me->add("neili",-100);
		me->add("neili",-80);
		me->start_perform(3,"金针渡劫");
		return 1;
}

int strike_attack(object me,object target)
{
	if (!me||!target) return 0;
	
	if (me->is_fighting()
		&&me->query("gender")=="女性"
		&&me->query_skill_mapped("leg")=="chuanyun-tui"
		&&me->query_skill_prepared("leg")=="chuanyun-tui")
	{
			message_vision(HIR "$N身子轻盈，基本轻功修炼的极为扎实，轻身飞纵，顺势一脚踹向$n。\n" NOR,me,target);
			me->add_temp("apply/attack",me->query_skill("chuanyun-tui",1)/4);
			me->add_temp("apply/damage",me->query_skill("chuanyun-tui",1)/5);
			me->add_temp("apply/leg",me->query_skill("chuanyun-tui",1)/5);
			COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			me->add_temp("apply/attack",me->query_skill("chuanyun-tui",1)/4);
			me->add_temp("apply/damage",me->query_skill("chuanyun-tui",1)/5);
			me->add_temp("apply/leg",me->query_skill("chuanyun-tui",1)/5);

	}
	if (me->is_fighting()
		&&me->query("gender")=="男性"
		&&me->query_skill_mapped("cuff")=="zhentian-quan"
		&&me->query_skill_prepared("cuff")=="zhentian-quan")
	{
			message_vision(HIY "$N辛苦修炼的震天拳此时发挥威力，顺势一拳击向$n的前胸！\n" NOR,me,target);
			me->add_temp("apply/attack",me->query_skill("zhentian-quan",1)/4);
			me->add_temp("apply/damage",me->query_skill("zhentian-quan",1)/5);
			me->add_temp("apply/cuff",me->query_skill("zhentian-quan",1)/5);
			COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			me->add_temp("apply/attack",me->query_skill("zhentian-quan",1)/4);
			me->add_temp("apply/damage",me->query_skill("zhentian-quan",1)/5);
			me->add_temp("apply/cuff",me->query_skill("zhentian-quan",1)/5);

	}
	return 1;
}

string perform_name() {return RED"金针渡劫"NOR;}

int help(object me)
{
    write(WHT"\n两仪剑法「"RED"金针渡劫"WHT"」："NOR"\n");
    write(@HELP
	两仪剑法乃是昆仑派绝技，当初昆仑三圣何足道以此剑法横扫
	西域诸雄。后来在少林大战中一战成名，凭借的就是此剑法。
	两仪剑乃是正宗的正两仪剑法，剑法轻灵迅捷，不以力胜，但
	却将剑法灵动多变发挥到极致。倘若身法轻功好，则两仪剑法
	的威力更上一层楼。
	金针渡劫是两仪剑法的起手式，招式简单，但配合踏雪无痕的
	招式，以剑化针，直刺对方，变化多端，令对手烦不胜防。

	指令：perform sword.jinzhen
	
要求：
	玄天无极等级 200 级以上；
	两仪剑法等级 200 级以上；
	基本剑法等级 200 级以上，
	最大内力要求 1500 以上，
	当前内力要求 400 以上，
	当前精力要求 300 以上，
	激发剑法两仪剑，
	激发招架两仪剑，
	需手持剑类武器。    

HELP
	);
	return 1;
}
