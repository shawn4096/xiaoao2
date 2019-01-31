// zhuona.c 天罗地网技
// cre by sohu@xojh
#include <ansi.h>

inherit F_SSERVER;
void dohit(object me,object target); 

string perform_name(){ return HIC"天罗地网"NOR; }

int perform(object me, object target)
{
	int skill,hits;
	string msg,shou;
	
	if(!me->is_fighting())
		return notify_fail("你没在战斗中呢！\n");
	
	hits=(int)me->query_skill("tianluo-diwang",1)/100;
	
	if(!target) target = offensive_target(me);

	if( (skill=(int)me->query_skill("tianluo-diwang", 1)) < 150 )
		return notify_fail("你的天罗地网势还不够纯熟，无法施展「天罗地网」绝技。\n");
	if( (int)me->query_skill("yunu-xinjing", 1) < 150 )
		return notify_fail("你的玉女心经还不够纯熟，无法施展「天罗地网」绝技。\n");
	if( (int)me->query_skill("hand", 1) < 150 )
		return notify_fail("你的基本手法还不够纯熟，无法施展「天罗地网」绝技。\n");
	if(//me->query_skill_mapped("parry") != "tianluo-diwang"
		me->query_skill_prepared("hand") != "tianluo-diwang"
		||me->query_skill_mapped("hand") != "tianluo-diwang")
		return notify_fail("你没有激发天罗地网势！\n");
	
	if ( me->query_temp("weapon"))
		return notify_fail("你手持武器，如何使用「天罗地网」绝技？\n");
	if (target->query_temp("tldw/zhuona"))
		return notify_fail("你正在使用「天罗地网」绝技？\n");
	if(me->query("gender")=="无性")
		return notify_fail("面对无性对手，你如何施展「天罗地网」绝技？\n");
	if(me->query("gender")=="男性") shou="修长的手掌";
	else shou="纤纤玉手";
	if(me->query("max_neili")<1500)
		return notify_fail("你最大内力不够，无法使用「天罗地网」绝技。\n");
	if(me->query("neili")<500)
		return notify_fail("你内力不够，无法使用「天罗地网」绝技。\n");
	if(me->query("jingli")<500)
		return notify_fail("你当前精力不够，无法使用「天罗地网」绝技。\n");
	msg = HIC"\n$N一双"+shou+"挥出，东边一收，西边一拍，将$n挡了回来，这边挡，那边拍，瞬间拍出八十一掌\n"+
			HIC"$N将掌风控制在三尺之内，出手挡击，回臂反扑，但见$N双臂飞舞，两只手掌宛似化成了千手千掌，\n"NOR;
	message_vision(msg,me,target);
	//me->set_temp("tldw/zhuona",1);
	if (random(me->query_dex(1))>target->query_dex(1)/3)
	{
		msg = HIY"\n任凭$n如何飞滚翻扑腾挪，始终辗转不出$N所围作的三尺圈子。\n"NOR; 
		message_vision(msg, me, target);
		target->start_busy(hits);
		target->set_temp("tldw/zhuona",1);
		call_out("dohit",1,me,target);

	}else {  
		msg = HIW"\n$n轻轻一纵，对$N微微一笑，躲开了这招「天罗地网势」绝技。\n"NOR; 
		message_vision(msg, me, target);
		me->add_busy(1);		
	}
	me->add("neili",-random(200));
	me->add("jingli",-random(100));
	if (objectp(target))
		call_out("do_effect",hits,me,target);
	me->start_perform(1,"天罗地网势");
	return 1;
}


void dohit(object me,object target) 
{
	int damage;
	if (!objectp(target)) return;

	damage = (me->query("neili")-target->query("neili"))*me->query("jiali");
	if (damage<1) damage=1;
	if (damage>2000) damage=2000;
	
	message_vision(HIR"\n$n眼见双手要抱住$N的脖子，那知就在两臂将合未合之际，$N斜刺里向後一滑，脱出了他臂圈。\n"+
		"$n忙回臂去捉，这一下急冲疾缩，自己势道用逆了，再也立足不稳，仰天一交，跌得背脊隐隐生痛。！\n"NOR, me, target);
	target->apply_condition("no_exert",1);
	target->receive_damage("qi",damage,me);
	target->receive_wound("qi",damage/4,me);
	me->add_temp("apply/attack",me->query_skill("tianluo-diwang",1)/2);
	me->add_temp("apply/damage",me->query_skill("tianluo-diwang",1)/5);

	COMBAT_D->do_attack(me, target,0, 3);
	me->add_temp("apply/attack",-me->query_skill("tianluo-diwang",1)/2);
	me->add_temp("apply/damage",-me->query_skill("tianluo-diwang",1)/5);
	return;
	
}
void do_effect(object me,object target)
{
	if (!target) return;
	target->delete_temp("tldw/zhuona");
	tell_object(me,target->name(1)+HIC"终于摆脱了所中的天罗地网势，不禁长吁一口气。\n"NOR);
	tell_object(target,HIC"你终于摆脱了所中的天罗地网势，不禁长吁一口气。\n"NOR);
	return;
}

int help(object me)
{
   write(WHT"\n天罗地网势「"HIC"天罗地网"WHT"」："NOR"\n");
   write(@HELP
	古墓派入门武学，由古墓派师祖林朝英所创，
	为绵密无比的掌法。为杨过拜小龙女为师后，
	由其传授。更于其中修习绝顶轻功，飘逸轻
	灵，变化万方。修习到最高境界，能以双掌
	困住九九八十一只麻雀。
	注意：若身带白金手套，有自动打掉对方兵
	器的概率。悟性大于40可以和美女拳法互备


	perform hand.tianluo
	
要求：
	最大内力要求 1500 以上；
	当前精力要求 500 以上；
	当前内力要求 500 以上；
	天罗地网等级 150 以上；
	基本手法等级 150 以上；
	玉女心经等级 150 以上；
	激发且备手法为天罗地网势；
	
	
HELP
   );
   return 1;
}
