// lianhuan.c 鸳鸯连环腿
// by sohu@xojh

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int perform(object me, object target)
{

	int i,damage,p;
	string msg;
	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("「鸳鸯连环腿」只能在战斗中对对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("使用「鸳鸯连环腿」时双手必须空着！\n");

	if( (int)me->query_skill("shaolin-tantui", 1) < 250 )
		return notify_fail("你的鸳鸯连环腿腿不够娴熟，不会使用「鸳鸯连环腿」。\n");

	if( (int)me->query_skill("yijin-jing", 1) < 250 )
		return notify_fail("你的易筋经等级不够，不能使用「鸳鸯连环腿」。\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		return notify_fail("你目前的内功无法支持你使用「鸳鸯连环腿」进行攻击。\n");  
	if (me->query_skill("leg",1)<250)
		return notify_fail("你目前的基本腿法不足100，不支持你使用「鸳鸯连环腿」进行攻击。\n");  
		
	if( (int)me->query_dex() < 50 )
		return notify_fail("你的身法不够50，不能使用「鸳鸯连环腿」。\n");

	if (me->query_skill_prepared("leg") != "shaolin-tantui"
	|| me->query_skill_mapped("leg") != "shaolin-tantui")
		return notify_fail("你现在无法使用「鸳鸯连环腿」进行攻击。\n");  
											       
	if( (int)me->query("max_neili") < 2500 )
		return notify_fail("你现在最大内力太弱，不能使用「鸳鸯连环腿」。\n");
	if( (int)me->query("neili") < 500 )
		return notify_fail("你目前内力太少，不能使用「鸳鸯连环腿」。\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("你现在精力太少，不能使用「鸳鸯连环腿」。\n");


	message_vision(RED"\n$N一鼓作气将十二路弹腿发挥极致，喝道，「鸳鸯连环腿」！，身子在空中，双腿连续发力，向$n连环踢出三腿！\n" NOR,me, target);
	
		
	me->set_temp("sltt/lianhuan", 1);
	me->add("neili", -180);
	if (target->is_busy())
	{
		i = (int)me->query_skill("ruying-suixingtui", 1)+(int)me->query_skill("yijin-jing", 1)/3;
	}else 	i = (int)me->query_skill("ruying-suixingtui", 1)+(int)me->query_skill("yijin-jing", 1)/5;

	me->add_temp("apply/attack",i);
    me->add_temp("apply/damage",i/4);
    me->add_temp("apply/dodge", i);


	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
	if (me->query_skill_mapped("hand")=="fengyun-shou"
		&&me->query_skill_prepared("hand")=="fengyun-shou"
		&&me->query_skill_mapped("leg")=="shaolin-tantui"
		&&me->query_skill_prepared("leg")=="shaolin-tantui")
	{
		message_vision(HIY"$N眼见$n不防，趁机伸出手腕，施展出风云手绝技，夹杂着腿法袭向$n的胸口！\n"NOR,me,target);
		me->add_temp("apply/attack",i/4);
		me->add_temp("apply/damage",i/6);
		me->add_temp("apply/hand",i/4);
		//me->prepared_skill("");
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		me->add_temp("apply/attack",-i/4);
		me->add_temp("apply/damage",-i/6);
		me->add_temp("apply/hand",-i/4);

	}
//	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
	

	
	me->add_temp("apply/attack",- i);
    me->add_temp("apply/damage",- i/4);
    me->add_temp("apply/dodge", -i);

		message_vision(HIC "\n$N一口气踢完，空中借势回旋，轻飘飘落在地上。\n" NOR,me);

		me->delete_temp("sltt/lianhuan");

		me->start_perform(4,"「鸳鸯连环腿」");

		return 1;
}


string perform_name(){ return HIY"鸳鸯连环腿"NOR; }
int help(object me)
{
        write(HIC"\n少林弹腿之「鸳鸯连环腿」绝技："NOR"\n");
        write(@HELP
	少林弹腿为少林入门腿法，利用坚实的腿功和强大的内力，身
	子纵起空中，趁对方不备向对方踢出一脚绝命杀招，令对手防
	不胜防，躲无可躲，端的是厉害非常。鸳鸯连环意思是双腿相
	随，连续踢出。
		
	注意：「少林弹腿」是腿法基本功，乃后期如影随形腿的必修
		功夫。少林鸳鸯连环腿命中依靠身法和腿法，切记！

	指令：perform leg.tantui

要求：  
	最大内力需求 2500 以上；      
	当前内力需求 500  以上
	当前精力需求 500  以上；  
	少林弹退等级 250 以上；
	易筋经功等级 250 以上；
	基本腿法等级 250 以上；	
	激发腿法为少林鸳鸯连环腿；
	激发招架为少林鸳鸯连环腿；
	且手无兵器；
	有效身法不得小于50。
                
HELP
        );
        return 1;
}
