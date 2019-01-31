// shisan.c 武当长拳「长拳十三式」绝技
// sohu@xojh
#include <ansi.h>

inherit F_SSERVER;



string perform_name(){ return WHT"长拳十三式"NOR; }

int perform(object me, object target)
{
	int damage, p, m, force, ap ,dp;
	float at;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) )
		return notify_fail("「长拳十三式」只能对战斗中的对手使用。\n");

	if( me->query_skill("wudang-quan", 1) < 100 )
		return notify_fail("武当长拳的等级不够，又如何能使用「长拳十三式」？\n");
	if( me->query_skill("cuff", 1) < 100 )
		return notify_fail("基本拳法等级不够，又如何能使用「长拳十三式」？\n");
	if( me->query_skill("yinyun-ziqi", 1) < 100 )
		return notify_fail("氤氲紫气等级不够，又如何能使用「长拳十三式」？\n");

	if(me->query_skill_mapped("force") != "yinyun-ziqi"
	  ||me->query_skill_mapped("cuff") != "wudang-quan"
	  || me->query_skill_prepared("cuff") != "wudang-quan") 
		return notify_fail("你的内功或拳法不对，又如何能使用「长拳十三式」字诀？\n");

	if( (int)me->query("neili", 1) < 500 )
		return notify_fail("你现在真气不够，强迫使用「长拳十三式」字诀只会伤到你自己！\n");
	if( (int)me->query("jingli", 1) < 500 )
		return notify_fail("你现在精力不够，强迫使用「长拳十三式」字诀只会伤到你自己！\n");
	
	if( me->query_temp("weapon") )
		return notify_fail("你先放下手中的武器再说吧？！\n");

	msg = WHT"\n$N将这武当长拳中「长拳十三式」连贯使出，如行云流水！\n"NOR;


	ap = me->query_skill("wudang-quan",1);
	dp = target->query_skill("parry",1);

	if( random( ap + dp) > dp 
		|| random(me->query_str(1))>target->query_str(1)/2 )
	{
			
			msg += HIC"\n$N拳风凌冽，招式虽然简单却极为实用，逼迫$n连连后退！\n"NOR;
			target->add_busy(1);
			damage = (int)me->query_skill("wudang-quan",1) * me->query_str(1)/5;


			if( userp(target)&&damage>3000 ) damage = 3000;
			

			target->receive_damage("qi", damage, me);
			target->receive_wound("qi", damage/(2+random(2)), me);


			p = (int)target->query("eff_qi")*100/(int)target->query("max_qi");

			msg += COMBAT_D->damage_msg(damage, "内伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		

	}
	else{
		msg += HIY"$p纵身躲过这招！\n"NOR;
		me->start_busy(random(2));
		msg+=HIR"$N眼见这招没有打中，当即随手又是随身跟上，连击两招！\n"NOR;
		//message_vision(msg, me, target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		
	}
	message_vision(msg, me, target);
	me->start_perform(2, "「长拳十三式」");
	me->add("neili", -100);
	me->add("jingli", -50);

	return 1;
}

int help(object me)
{
	write(WHT"\n武当长拳之"HIC"「长拳十三式」："NOR"\n");
	write(@HELP
	武当长拳是创派祖师张三丰由少林基础武技
	演化而来，为武当派入门武技，后来经由张
	真人不断演化，形成典型的长拳十三式，既
	能将基本拳术要诀发挥出来，又能强身健体
	由此形成一门极具实战的拳术。
	
	指令：perform cuff.shisan

要求：	
	当前内力要求 500 以上；
	最大内力要求 1200 以上；
	当前精力要求 500 以上；
	武当长拳等级 100 以上；
	氤氲紫气等级 100 以上；
	基本拳法等级 100 以上；
	道学心法等级 100 级别；
	激发掌法为武当长拳；
	激发招架为武当长拳；
	激发内功为氤氲紫气。
	且空手
HELP
	);
	return 1;
}
