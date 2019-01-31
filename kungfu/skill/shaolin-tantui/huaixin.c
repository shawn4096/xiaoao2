// huaixin.c 怀心腿
// by sohu@xojh

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int perform(object me, object target)
{

	int skill;
	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("「怀心腿」只能在战斗中对对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("使用「怀心腿」时双手必须空着！\n");

	if( (int)me->query_skill("shaolin-tantui", 1) < 200 )
		return notify_fail("你的怀心腿腿不够娴熟，不会使用「怀心腿」。\n");

	if( (int)me->query_skill("yijin-jing", 1) < 200 )
		if( (int)me->query_skill("hunyuan-yiqi", 1) < 200 )
		return notify_fail("你的易筋经或混元一气等级不够，不能使用「怀心腿」。\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		return notify_fail("你目前的内功无法支持你使用「怀心腿」进行攻击。\n");  
	if (me->query_skill("leg",1)<200)
		return notify_fail("你目前的基本腿法不足100，不支持你使用「怀心腿」进行攻击。\n");  
		
	if( (int)me->query_dex() < 40 )
		return notify_fail("你的身法不够40，不能使用「怀心腿」。\n");

	if (me->query_skill_prepared("leg") != "shaolin-tantui"
		|| me->query_skill_mapped("leg") != "shaolin-tantui")
		return notify_fail("你现在无法使用「怀心腿」进行攻击。\n");  
											       
	if( (int)me->query("max_neili") < 2400 )
		return notify_fail("你现在最大内力太弱，不能使用「怀心腿」。\n");
	if( (int)me->query("neili") < 600 )
		return notify_fail("你目前内力太少，不能使用「怀心腿」。\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("你现在精力太少，不能使用「怀心腿」。\n");
	if (me->query_temp("sltt/hxt"))
		return notify_fail("你现在正在使用「怀心腿」进行攻击。\n");  

	skill=me->query_skill("shaolin-tantui",1);

	message_vision(HIR"\n$N身形半蹲，将自己的一条腿略微弯曲，藏了起来，似乎是一条腿站立在当地，正式少林弹腿最为正宗的「怀心腿」绝技！\n" NOR,me, target);
	
		
	me->set_temp("sltt/hxt", 1);
	me->add("neili", -380);
	me->add("jingli", -180);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);

	message_vision(RED "\n$N向$n踢出一腿后，后招源源不断，这怀心腿好像随时会踢出去一般。\n" NOR,me,target);
	me->start_perform(3,"「怀心腿」");
	call_out("remove_hxt",1,me,(int)skill/50);
	return 1;
}
int remove_hxt(object me,int count)
{
	if (!me||!me->query_temp("sltt/hxt")) return 0;
	if (!me->is_fighting()
		||me->query_skill_mapped("leg")!="shaolin-tantui"
		||me->query_skill_prepared("leg")!="shaolin-tantui"
		||count--<0)
	{
		me->delete_temp("sltt/hxt");
		message_vision(RED"$N长吁一口气，呼出一口浊气，泄掉「怀心腿」绝技！\n"NOR,me);
		return 1;
	}

	call_out("remove_hxt",1,me,count--);

}

string perform_name(){ return HBRED+HIW"怀心腿"NOR; }
int help(object me)
{
        write(HIC"\n少林弹腿之「怀心腿」绝技："NOR"\n");
        write(@HELP
	少林弹腿为少林入门腿法，利用坚实的腿功和强大的内力，身
	子纵起空中，趁对方不备向对方踢出一脚绝命杀招，令对手防
	不胜防，躲无可躲，端的是厉害非常。
		
	注意：「少林弹腿」是腿法基本功，乃后期如影随形腿的必修
		功夫。少林怀心腿命中依靠身法和腿法，切记！

	指令：perform leg.huaixin

要求：  
	最大内力需求 2400 以上；      
	当前内力需求 600  以上
	当前精力需求 500  以上；  
	少林弹退等级 200 以上；
	易筋经功等级 200 以上；
	基本腿法等级 200 以上；	
	激发腿法为少林弹腿；
	激发招架为少林弹腿；
	且手无兵器；
	有效身法不得小于40。
                
HELP
        );
        return 1;
}
