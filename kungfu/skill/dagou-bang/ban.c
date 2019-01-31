// ban.c 打狗棒法--绊字诀
// Creat by Looklove@SJ 3/16/2001
// modified by Looklove 2001.5.10
// Modified by Lane@SJ 2005.7.29

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HBBLU"绊字诀"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int ap ,dp ,p, n;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「绊字诀」只能对战斗中的对手使用。\n");
	if (!userp(me)) return 1;
	
	weapon = me->query_temp("weapon");

	if( !weapon
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("stick") != "dagou-bang" 
	 || me->query_skill_mapped("parry") != "dagou-bang" )
		return notify_fail("你现在无法使用「绊字诀」。\n");

	ap = me->query("combat_exp");
	dp = target->query("combat_exp");

	tweapon = target->query_temp("weapon");

	if( me->query_skill("dagou-bang", 1) < 400 )
		return notify_fail("你的打狗棒法还不够娴熟，不会使用「绊字诀」。\n");

	if( me->query_skill("bangjue",1) < 200 )
		return notify_fail("你的打狗棒诀不够娴熟，无法使出「绊字诀」。\n");

	if( (int)me->query_skill("huntian-qigong",1) < 400 )
		return notify_fail("你的混天气功根基不足，无法使出「绊字诀」。\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("你的内力不够，无法使出「绊字诀」。\n");

	if( (int)me->query("jingli") < 1000 )
		return notify_fail("你的精力不足以让你使出「绊字诀」。\n");

	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("你内力修为现在不够，不能用「绊字诀」！\n");

	if( target->query_temp("dgb/ban") )
		return notify_fail("对方已经被拌中了，放手攻击吧。\n");

	n = me->query_skill("bangjue", 1);

	if( me->query_skill("dagou-bang", 1) > 450 )
		n += random(me->query_skill("bangjue", 1)/2);

	ap = COMBAT_D->skill_power(me, "stick", SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);

	ap += ap /100000 * me->query_skill("stick") * me->query_int(1)/3;
	dp += dp /100000 * target->query_skill("dodge") * target->query_int(1)/3;

	msg=HBBLU"$N"+weapon->name()+HBBLU"挥出，以「绊字诀」着地扫去，一绊不中，二绊续至，连环钩盘，棒影如山，如长江大河绵绵而不绝。\n"NOR;

	if( ( ap = random(ap+dp) ) > dp/2 )
	{
		msg+=HBBLU"$N决不容敌人有丝毫喘息时机，$n纵身稍慢，转身不见有人，便知中计，被"+weapon->name()+HBBLU"在左胫上一拨，右踝上一钩，扑地倒了。\n"NOR;
		target->add_busy(2+random(3));
		target->recieve_damage("qi", n*3, me);
		target->recieve_wound("qi", n*3, me);
		if (random(2))
		{
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		target->set_temp("dgb/ban", n*2);
		target->add_temp("apply/dodge",-n*2);
		target->apply_condition("dgb_ban_wound", n/30);
		me->add("neili", -400);
		me->add("jingli", -200);
		me->start_busy(random(2));
		me->set_temp("dgb/ban",1);
		call_out("check_perform", 1,me, target,weapon, n);
	}
	else if( ap > dp ) {
		msg+=HBBLU"$n脚下慌乱，抬脚想去踏住"+weapon->name()+HBBLU"，却被"+weapon->name()+HBBLU"在脚踝上一绊，扑通倒地。\n"NOR;
		target->add_busy(1+random(2));
		target->recieve_damage("qi", n*2, me);
		target->recieve_wound("qi", n*2, me);
		if( random(2) ) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		target->set_temp("dgb/ban", n);
		target->add_temp("apply/dodge",-n);
		target->apply_condition("dgb_ban_wound",n/40);
		me->add("neili", -300);
		me->add("jingli", -100);
		me->start_busy(random(2));
		me->set_temp("dgb/ban",1);
		call_out("check_perform", 1, me,target,weapon, n/2);
	}
	else {
		msg += HIG"$n下盘功夫十分扎实，闪展腾挪间躲开"+weapon->name()+HIG"的绊绕，顺势一脚踢中$N的屁股。\n"NOR;
		me->start_busy(1+random(2));
		me->add("neili", -150);
		me->add("jingli", -50);
	}
	if( wizardp(me) ) tell_object(me, HIY"打狗棒法「绊字诀」命中率对比 "+ap+" ："+dp+"。\n"NOR);
	if (!me->query("quest/gb/dgb/bangjue/pass") || me->query_skill("dagou-bang",1)<450)
		me->start_perform(2,"绊字诀");
	message_vision(msg, me, target);
	return 1;
}

void check_perform(object me,object target, object weapon,int bonus)
{
	
	if (!me) return;
	
	
	if (!me->is_fighting()
		||!target
		||!me->query_temp("dgb/ban")
		|| bonus<1) 
	{
		me->delete_temp("dgb/ban");
		message_vision(HBBLU"$N眼见对方已经认输，将手中的"+weapon->query("name")+HBBLU"一收，吸了一口气，停止「绊字诀」！\n"NOR,me);
		return;
	}
	if (random(10)>5)
	{	
		switch (random(3))
		{
			case 0:
				message_vision(CYN"$N一绊不中，二绊续至，连环钩盘，虽只一个「绊字诀」中间却蕴藏着千变万化，防不胜防。\n"+
							"$n越跃越快，但见地下一片棒影化成的碧光盘旋飞舞。“绊”到十七八下，$n纵身稍慢，被\n"+
							weapon->query("name")+CYN"在左胫上一拨，右踝上一钩，扑倒在地，\n"NOR,me,target);
				target->receive_damage("qi",1000+random(2000),me);
				target->receive_damage("qi",500+random(1000),me);
				target->add_busy(2);
				break;
			case 1:
				message_vision(YEL"$n纵身上跃，但那「绊字诀」棒法乃是一棒快似一棒，第一棒若能避过，立时躲开，方能设法\n"+
								"挡架第二棒，现下一棒即被绊倒，爬起身来想要挡过第二棒，真是谈何容易？但觉得脚下犹如\n"+
								"陷入了泥沼，又似缠在无数藤枝之中，一交摔倒，爬起来又是一交摔倒。\n"NOR,me,target);
				target->add_busy(2+random(2));
				target->receive_damage("jing",random(800),me);
				target->recieve_wound("jing",random(500),me);
				break;
			case 2:
				message_vision(WHT"$n转身不见有人，便知中计，微感劲风袭向下盘，急忙涌身跃起，总算躲过了一招，但那「绊字诀」\n"+
								"有如长江大河，绵绵而至，决不容敌人有丝毫喘息时机，一绊不中，二绊续至，连环钩盘，虽只一个\n"+  
								"招式，但却变化万千，无穷无尽。\n"NOR,me,target);
				target->add_busy(2+random(2));
				target->receive_damage("jingli",random(1000),me);
			//target->recieve_wound("jingli",random(1000),me);

				break;
		}
	 }
	call_out("check_perform", 1, me,target,weapon,bonus-3);
	return;
}

int help(object me)
{
        write(HBBLU"\n打狗棒「绊字诀」："NOR"\n");
        write(@HELP
	打狗棒以轻、巧、灵诸称，舞将起来是四处只见棒影不见人影。
	这「绊字诀」，却是专攻敌人下盘的招数。对于下盘不稳的对手
	极是有效，一旦绊中，对手身形变慢，必处处受制。
	注意：解开「绊字诀」秘密后，「绊字诀」大飞。
	
	指令：perform stick.ban
	
要求：
	最大内力需求 2000 以上；
	当前内力需求 600 以上；
	打狗棒法等级 400 以上；
	混天气功等级 400 以上；
	打狗棒诀等级 200 以上：
	激发招架为打狗棒。
HELP
        );
        return 1;
}
