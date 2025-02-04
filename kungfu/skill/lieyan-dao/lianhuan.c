//lianhuan
//连环三刀，源自范瑶招式
//by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
void next1(object me, object target);
void next2(object me, object target);
int perform(object me,object target)
{
		int i;
		string msg;
        object weapon;
		weapon= me->query_temp("weapon");  
		i=me->query_skill("lieyan-dao",1);
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("连环三击只能对战斗中的对手使用。\n");

        if( me->query("neili") <= 400 )
                return notify_fail("你的内力不够使用连环三击！\n");
        if( me->query("max_neili") <= 1400 )
                return notify_fail("你的内力不够使用连环三击！\n");

        if( me->query("jingli") <= 300 )
                return notify_fail("你的精力不够使用连环三击！\n");
        if( me->query_skill("lieyan-dao",1) <= 250 )
                return notify_fail("你烈焰刀不足250，不够使用连环三击！\n");
        if( me->query_skill("shenghuo-shengong",1) <= 250 )
                return notify_fail("你的,圣火神功不足250，不够使用连环三击！\n");

        if (!weapon||weapon->query("skill_type")!="blade")
                return notify_fail("你手中无刀怎能使用连环三击？！\n");
		
        if (me->query_skill_mapped("blade") != "lieyan-dao"
				&& userp(me))
             	return notify_fail("你必须先激发烈焰刀。\n");
		if (me->query_skill_mapped("parry") != "lieyan-dao"
			  && me->query_skill_mapped("parry") != "qiankun-danuoyi"
			  && userp(me))
             	return notify_fail("你需要激发烈焰刀或乾坤大挪移。\n");

	message_vision( RED"$N脚下发力，腾空而起，当头直砍，毫无花哨,力大如山。$n心中不以为然，似乎要向旁边闪避。\n"+
		"但$N的刀势临近$n头顶之际，竟然陡然变招，刀势削向了$n的双手。\n"NOR,me,target);
	
	me->start_perform(5,"「连环三击」");
	if(random(me->query_skill("lieyan-dao",1))  >target->query_skill("dodge",1)/3
		||random(me->query_str())>target->query_str()/2)
	{
		message_vision(CYN "$n心中无奈，只得一招“霸王卸甲”，硬接了$N这招。\n" NOR,me,target);
		target->add_busy(random(2) + 2);
		target->add_temp("apply/attack",i/4);
		target->add_temp("apply/damage",i/4);
		target->add_temp("apply/blade",i/4);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),2);
		target->add_temp("apply/attack",-i/4);
		target->add_temp("apply/damage",-i/4);
		target->add_temp("apply/blade",-i/4);
	}
	else {
		message_vision(HIW "可是$n看破了$N的企图，飞快的向后退去。\n" NOR,me,target);
		me->start_busy(1);
	}
 // 	message_vision(msg, me, target);
	if (objectp(target)&&me->is_fighting())
		next1(me, target);
	return 1;
}

void next1(object me, object target)
{
	string msg;
	int damage;
	object weapon;

	if (!me) return ;
	weapon = me->query_temp("weapon");
	damage = me->query_skill("lieyan-dao",1)+me->query_skill("shenghuo-shengong",1);
	damage += me->query_skill("blade",1)+me->query_skill("qiankun-danuoyi",1);
	damage=damage*3;
	damage += random(damage);
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		return ;
	}

	message_vision(CYN"\n$N第二刀连着又上，招法与第一刀一模一样,只是刀势竟然猛涨！\n"+
		"$n经验极其丰富，但竟无法破解$N这笨拙钝重的一招，除了同法硬架之外，更无善策。\n"NOR,me,target);

	if(random(me->query("max_neili"))> target->query("max_neili")/2
		||random(me->query_skill("force",1)) >target->query_skill("force",1)/3
	    ||target->is_busy())
	{
		msg = HIR"$N和$n二度相拼，$n双臂酸麻更甚，只要再给$N这般砍上几刀，$n手臂上的筋络也要给震伤。\n"NOR;
		if (!target->is_busy()) target->start_busy(damage/500);
		target->add("neili",-(500+random(150)));
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		msg += damage_msg(damage, "震伤");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		if (me->query("env/damage"))
		{
			tell_object(me,"你造成了"+damage+"的伤害！\n");
		}
		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		message_vision( CYN"$n内力深厚硬生生接下了这一招。\n"NOR,me,target);
		me->start_busy(1+random(2));
		
	}		
	//message_vision(msg, me, target);
	me->start_perform(4,"「连环三击」");

	if (objectp(target)&&me->is_fighting())
		next2(me, target);

}


void next2(object me, object target)
{
	string msg;
	int damage;
	object weapon;

	if( !me ) return ;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		return ;
	}

	message_vision(YEL "\n$n惊魂未定，$N第三刀顺势递出，刀势逐渐增强。刀光如火，宛如烈焰飞腾，刀光乍泄，向四周射出。\n"NOR,me,target);

	if(random(me->query("combat_exp")>target->query("combat_exp")/3 
		||random(me->query_str()) >target->query_str())/3)
   {
		msg=HIW "$n此时已给$N刀气所逼，眼见刀光来袭，忙伸手平掌一挡，刀尖刺中$n掌心！\n"NOR;
		damage = me->query_skill("lieyan-dao",1)+me->query_skill("shenghuo-shengong",1);
		damage += me->query_skill("blade",1)+me->query_skill("qiankun-danuoyi",1);
		damage=damage*4;
		damage += random(damage);
	    if (objectp(target)&&!target->query("lyd/lianhuan")) 
		{
			target->add_temp("apply/attack", 100);
			target->add_temp("apply/dodge", 100);
			target->add_temp("apply/parry", 100);
			target->set_temp("lyd/lianhuan",1);
		}
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		msg += damage_msg(damage, "刺伤");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "手心");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		if (me->query("env/damage"))
		{
			tell_object(me,"你造成了"+damage+"的伤害！\n");
		}

		me->add("neili",-300);
		me->add("jingli",-150);
		if (objectp(target))
			call_out("back", 5 + random(me->query("jiali") / 20), target);
	} else {
		message_vision(HIW "$n纵身躲过，心中大惊。\n" NOR,me,target);
		me->start_busy(1 + random(2));
		
	}
	me->start_perform(4,"「连环三击」");

}

void back(object target)
{
	if (!target||!target->query_temp("lyd/lianhuan")) return;
	target->add_temp("apply/attack", 100);
	target->add_temp("apply/dodge", 100);
	target->add_temp("apply/parry", 100);
	return;
}
string perform_name(){ return HIM"连环三刀"NOR; }

int help(object me)
{
        write(HIC"\n烈焰刀法"+HIR"「圣火烈焰」"NOR"\n");
        write(@HELP
	烈焰刀乃是明教入门级的武功，源自逍遥二仙中范瑶的传授
	范右使武功极为驳杂，当初毁容而打入敌人内部，就为查找
	陷害明教的对头，以哑巴头陀的形象示人与外，实乃明教的
	大功臣。
	连环三刀是源自范瑶和张无忌在相认时是施展武功精要所成
	一旦出手，全力以赴，向对方连续劈砍出三刀。

	指令：perform blade.lianhuan

要求：
	最大内力要求 1400 以上；
	当前内力要求 400 以上；
	当前精力要求 300 以上；
	烈焰刀法等级 250 以上；
	圣火神功等级 250 以上；
	激发刀法为烈焰刀法。
	激发招架为烈焰刀或乾坤大挪移
	手持刀类武器。

HELP
        );
        return 1;
}
