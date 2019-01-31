// tiao.c 挑字诀
//Created by Redhat@Sjmud 2009/4/7
//by sohu

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIY"挑字诀"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int ap, dp;

	int damage;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「挑字诀」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");
	tweapon = target->query_temp("weapon");

	if( !weapon
	 || weapon->query("skill_type") != "spear"
	 || me->query_skill_mapped("spear") != "huyan-qiang" )
		return notify_fail("你现在无法使用「挑字诀」。\n");


	if((int)me->query_skill("huyan-qiang", 1) < 200 )
		return notify_fail("你的呼延枪法还不够娴熟，不会使用「挑字诀」。\n");

	if((int)me->query("neili") < 2000 )
		return notify_fail("你的内力不够！\n");

	if( (int)me->query_str() < 35 )
		return notify_fail("你的先天臂力不足，无法使用「挑字诀」。\n");

	if( me->query_skill_mapped("spear") != "huyan-qiang")
        return notify_fail("你需要激发枪法为呼延枪法，方能使用「挑字诀」。\n");
	
	if( me->query_temp("hyq/tiao") )
        return notify_fail("你方才刚使用过「挑字诀」。\n");

	if (tweapon)	
		msg = HIG"$N双手握枪，将手中"+weapon->name()+HIR"搭上$n的"+tweapon->query("name")+HIR"，向空中猛然挑去。\n"NOR;
	else 
		msg = HIR"$N双手握枪，将手中"+weapon->name()+HIR"施展「挑字诀」，顺势扎向$n的前胸。\n"NOR;

	ap = me->query("combat_exp")/10000 * me->query_str(1);
	dp = target->query("combat_exp")/10000 * target->query_str(1);
	me->set_temp("hyq/tiao",1);

	me->add("neili",-200);
	me->add("jingli",-100);
	
	damage=me->query_skill("huyan-qiang",1)+me->query_skill("spear",1);
	damage=damage*me->query_str()/10+random(damage);
	
	if (damage>4000) damage=4000+random(1000);

	if( random(ap + dp) > dp )
	{
		if(tweapon)
		{
			msg += HIY"$n只感"+tweapon->name()+HIY"压力却越来越重，再也无法控制，一个把握不住，手中兵器被飞了出去。\n"NOR;
			target->add_busy(1+random(2));
			tweapon->unequip();
			tweapon->move(environment(me));
		}
		else {
			msg += HIY"$n一时不查，为$N手中的"+weapon->query("name")+HIY"所刺中，顿时扎了一个血窟窿！\n"NOR;
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/3,me);			
		}
		
	}
	else {
		
           msg += MAG"$n借力运功，向一旁躲避，将$N挑字诀化于无形！\n"NOR;

	}	
	message_vision(msg, me, target);
	call_out("remove_effect",2,me);

	return 1;
}
int remove_effect(object me)
{
	if (!me) return 0;
	me->delete_temp("hyq/tiao");
	return 1;
}

int help(object me)
{
	write(HBMAG"\n呼延枪法之「挑字诀」："NOR"\n");
	write(@HELP
	呼延枪法是呼延家传绝技，源自战阵，实战性强，后传
	于江南七怪的闹市侠隐全金发，以秤杆运使此枪法，更
	为精妙。
	对方若有兵器，则可能挑飞，若无兵器可能直接变为扎
	刺对方。此乃是全金发的独门绝技。

	指令：perform spear.tiao

要求：	
	当前内力需求 2000 以上；
	呼延枪法等级 200 以上；
	有效臂力需求 35 以上；
	激发枪法为呼延枪法；
	装备枪法。
HELP
	);
	return 1;
}