// feizhang.c  螺旋飞杖

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return CYN"螺旋飞杖"NOR; }

int perform(object me, object target)
{
	object weapon;
	int ap, dp, damage, p;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("螺旋飞杖只能对战斗中的对手使用。\n");

	if( !objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "staff")
		return notify_fail("你使用的武器不对。\n");

	if( me->query_skill("fengmo-zhang", 1) < 160 )
		return notify_fail("你的疯魔杖法不够娴熟，不会使用「螺旋飞杖」。\n");

	if( me->query_skill_mapped("parry") != "fengmo-zhang"
	 || me->query_skill_mapped("staff") != "fengmo-zhang")
		return notify_fail("你现在不能使用飞杖伤敌。\n");

	if( me->query_skill("force", 1) < 160 )
		return notify_fail("你的基本内功不够高，不能使用飞杖伤敌。\n");

	if( me->query("max_neili", 1) < 1800 )
		return notify_fail("你的内力修为不够，不能使用「螺旋飞杖」。\n");

	if( me->query("neili",1) < 500 )
		return notify_fail("你的真气不够，无法使用飞杖。\n");

	msg = CYN"\n$N一声长啸，猛吸一口气,将手中"+weapon->query("name")+CYN"抡圆了竟然当成狼牙棒来使,砸向$n。\n"NOR;

	ap = COMBAT_D->skill_power(me, "staff", SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);
	ap += me->query("combat_exp", 1) / 10000 ;
	dp += target->query("combat_exp", 1) /10000 ;
	
	if (me->query("gender")=="男性" && me->query_temp("htqg/powerup"))
	{
		message_vision(RED"$N运起混天气功，激发出心中气血奔涌，浑然不顾，招式越发威猛。\n"NOR,me);
		//me->add_temp("apply/attack",me->query_skill("fengmo-zhang",1)/4);
		me->add_temp("apply/damage",(int)me->query_skill("fengmo-zhang",1)/6);
		me->set_temp("fmz/feizhang1",1);
	}
	if ( random(ap + dp ) > dp ||random( me->query_str(1))>target->query_con(1)/2) {
		damage = me->query_skill("staff") * 4;
		damage += me->query_skill("force") * 2;
		damage = damage + random(damage);
		if (userp(me))
		   damage =damage*5;
		if (damage > 5000) damage = 5000 + (damage-4000)/10;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add("neili", -250);
		me->add("jingli", -80);
		msg += HIR"只见$N手中"+ weapon->name()+HIR"螺旋飞出，倏的罩向$n。\n"+
			"$n只觉一股大力铺天盖地般压来，登时眼前一花，两耳轰鸣，哇的喷出一口鲜血！\n"NOR;
        if(userp(me) && me->query("env/damage")) 
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR);
        if( random(2) ) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 

		}
		msg +=	HIW"\n只见"+weapon->name()+HIW"撞到$n后，反弹回来又回到了$N手中。\n"NOR;
	}
	else{
		msg += CYN"可是$p见事不妙，猛地向前一跃，跳出了$P的攻击范围，$P大步向前接住空中的"+weapon->query("name")+CYN"。\n"NOR;
		me->add("neili", -100);
	}
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
	
	if (me->query("gender")=="男性" && me->query_temp("fmz/feizhang1") )
	{
		me->add_temp("apply/damage",-(int)me->query_skill("fengmo-zhang",1)/6);
		me->delete_temp("fmz/feizhang1");
	}
	me->start_busy(1+random(1));
	me->start_perform(3, "陀螺飞杖");
	message_vision(msg, me, target);
	return 1;
}

int help(object me)
{
	write(CYN"\n疯魔杖法之「螺旋飞杖」："NOR"\n");
        write(@HELP
	疯魔杖法乃是丐帮扬州分舵主马俱为的成名武技，该杖法原本源自少林。
	后来在江湖中流传，经历代高手去芙存精，使得疯魔杖法不断精炼，招式
	越加犀利。疯魔诀乃是凭借一口真气，奋不顾自己的安危，全力抢攻，瞬
	间施展出一百零八招攻击，另对方目不暇接。男性使用威力略高。
	
	指令:perform staff.feizhang

要求：  
	最大内力 1800 以上；
	当前内力 500 以上；
	疯魔杖法等级 160 以上；
	基本内功等级 160 以上；
	激发招架为疯魔杖法,。
	激发杖法为疯魔杖法
	装备杖法
HELP
        );
        return 1;
}
