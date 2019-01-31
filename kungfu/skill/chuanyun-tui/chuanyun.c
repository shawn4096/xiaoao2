inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
#include <combat.h> 

int perform(object me, object target)
{
	int damage,p;
	string msg,msg2;
        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「穿云」只能对战斗中的对手使用。\n");

	if( me->query_temp("weapon"))
		return notify_fail("你拿着武器无法使用「穿云」！\n");   

	if( (int)me->query_skill("chuanyun-tui",1) < 100 )
		return notify_fail("你的穿云腿法修为不足，使不出「穿云」。\n");
	
	if( (int)me->query("max_neili") < 1000 )
		return notify_fail("你功力太弱，不能使出「穿云」。\n");
	
	if( (int)me->query("neili") < 800 )
		return notify_fail("你现在内力太弱，不能使出「穿云」。\n");
	
	if( (int)me->query("jingli") < 500 )
		return notify_fail("你现在无精打采，不能使出「穿云」。\n");

	if (me->query_skill_prepared("leg") != "chuanyun-tui")
		return notify_fail("你没有使用穿云腿，现在无法使出「穿云」！\n");
    
	if(me->query_temp("klpfm/chuanyun"))
      return notify_fail("你暂时不能使用「穿云绝技」了。\n");  
                
		message_vision(HIW"\n$N突然滴溜溜的转身，轻身纵起！当空一脚踢出，状若「穿云」，电闪雷鸣，势如破竹。\n"NOR,me,target);
		damage  = (int)me->query_skill("leg");
		damage += (int)me->query_str()*10;
		damage += (int)me->query_dex()*10;
		damage += (int)me->query("jiali");
		damage  = damage*2+random(damage);
	if (damage>4000) damage=3000+random(1000);
	if (!userp(me)&&userp(target))
	{
		damage=damage/2;
	}
    if( random(me->query_skill("chuanyun-tui",1))> (int)target->query_skill("parry",1)/2
		  ||random(me->query_dex(1))>target->query_dex(1)/2) 
	{
		message_vision(HIY"$n一时不察，被$N的脚尖踢中胸口大穴，顿时气血凝阻不畅。\n"NOR, me,target);
		target->add_busy(1+random(2));
	//	damage *= 2;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/5, me);
		p = (int)target->query("qi")*100/(int)target->query("max_qi");
		msg = HIR"结果重重的踢在$n的胸口，$n登时鲜血狂喷，向后倒飞出去。\n"NOR;
		msg += "( $n"+eff_status_msg(p)+" )\n"; 
		message_vision(msg, me, target);
		if(userp(me) && me->query("env/damage")) 
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);
		if(userp(target)&& target->query("env/damage")) 
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
		//女性附加伤害
		if(me->query("gender")=="女性") {
			damage=damage/2+random(damage)/2;
			target->receive_damage("qi", damage, me);
			//target->receive_wound("qi", damage/2, me);
			p = (int)target->query("qi")*100/(int)target->query("max_qi");
			msg = HIW"$N见状紧随其后，瞬间裙底晃出一条大白腿，正是"HIY"「撩阴腿」"HIW"的招式，踢向了$n的要害之处！\n"NOR;
			msg += damage_msg(damage, "击伤");
			msg += "( $n"+eff_status_msg(p)+" )\n"; 
			message_vision(msg, me, target);
			if(userp(me) && me->query("env/damage")) 
				tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR); 
			if(userp(target)&& target->query("env/damage")) 
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
		}
	
	
	}
	else {
		message_vision(HIC"\n$n急中生智，突然瞅得一个空当脱离出去，惊出了一身冷汗。\n"NOR, me,target);	
		me->start_busy(random(2));		
	}
		
		me->add("neili", -150);
		me->add("jingli", -50);

		me->start_perform(3,"「穿云绝技」");
		return 1;
}

string perform_name(){ return HIW"穿 云"NOR; }

int help(object me)
{
        write(HIW"\n穿云腿之「穿云」："NOR"\n\n");
        write(@HELP
	穿云腿是昆仑派门下弟子入门武技，凭借在昆仑
	山上冰天雪地中练就的高超腿法驰誉江湖。穿云
	腿的最大特点是迅捷且力大腿猛。是昆仑威名遐
	迩的技能。该腿法和震天掌可以互备。
	命中与武技等级或身法有关，此招女性比男性有
	额外优势，伤害与臂力和身法有关。

	指令：perform leg.chuanyun

要求：
	当前内力   800 以上；
	最大内力  1000 以上；
	当前精力   500 以上；
	穿云腿等级 100 以上；
	激发腿法为穿云腿；
	备腿法为穿云腿；
	且手无兵器。

HELP
        );
        return 1;
}
