//By Kingso 2006.12.29修正完成

#include <ansi.h>
string exert_name(){ return HBRED HIR"九阳神功"NOR; }

int exert(object me, object target)
{
	string msg, force;
       mapping poison;

	if( !target )
		return notify_fail("你要用真气为谁疗伤？\n");

	if( ! present(target,environment(me)))
		return notify_fail("这里有这个人吗？\n");

	

	if( me->is_fighting() || target->is_fighting())
		return notify_fail("战斗中无法运功疗伤！\n");

	if( target->is_busy())
		return notify_fail( target->name()+ "正忙着呢！\n");

	if( target->query("env/no_lifeheal"))
		return notify_fail( target->name()+"拒绝你帮其疗伤。\n");

	if( !living(target) || !target->query("can_speak"))
		return notify_fail("它不是活物，给它疗伤干什么？\n");

	if(!(force = me->query_skill_mapped("force")))
		return notify_fail("你还没有选择你要使用的内功。\n");

	if(me->query("max_neili") < 3500 )
		return notify_fail("你的内力修为不够。\n");

	if(me->query("neili") < 500 )
		return notify_fail("你的真气不够。\n");

	if( me->query_skill("force") < 200 ) 
		return notify_fail("你的内功等级还太低，不能运功疗伤。\n");

	if( me->query_skill("medicine", 1) < 110 )
		return notify_fail("你本草术理的等级不够，无法为他人疗伤。\n");

	poison = target->query_conditions_by_type("poison");


	

	msg = HBMAG HIR"$N坐了下来运起"HIR""+to_chinese(force)+""HBMAG"，将手掌贴于丹田处，缓缓地将真气运转大小周天……\n\n"NOR;
	msg +=HBMAG HIR"$n只觉一股暧阳阳的真气源源不绝的输入体内，只见$N头顶上丝丝白气冒出。\n\n"NOR;
	msg +=HBMAG HIR"$n吐出一口瘀血，脸色看起来红润多了，伤势有了很大的好转，全身真气无比充沛。\n\n"NOR;

	message_vision(msg ,me ,target);			     

	target->receive_curing("qi", 600 + me->query_skill("force")/2 );
	target->receive_heal("qi", 600 + me->query_skill("force")/2 );
       target->receive_curing("jing", 200 + me->query_skill("force")/2 );
	target->receive_heal("jing", 200 + me->query_skill("force")/2 );
       target->clear_conditions_by_type("poison");
       target->clear_conditions_by_type("hurt");
       target->clear_conditions_by_type("wound");
	me->add("neili", -500);
	me->set("jiali", 0);
	me->start_busy(4);
	target->start_busy(4);
	return 1;
}

int help(object me)
{
	write(HBRED HIR"\n九阳神功「九阳神功」："NOR"\n");
        write(@HELP
       运用雄厚的九阳神功内力治疗,
       效果非凡,并对所有毒、内伤、
       状态等的化解有着特殊的效果,
       尤其是寒毒。
       可为自己或者别人治疗。



	要求：  最大内力  3500 以上；
                当前内力  500 以上；
                九阳神功等级 200 以上；
                本草术理等级 110以上；
                

               
HELP
        );
        return 1;
}

