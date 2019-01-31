// leiting 雷霆万钧
// edited by sohu 2013

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
	object weapon;
	string msg;
	int damage, p, ap, dp;
	//int focus = me->query_temp("ss/focus");
	int j;
	        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) ||!living(target)|| !me->is_fighting(target) )
		return notify_fail("「雷霆万钧」只能在战斗中使用。\n");
        
	if( (int)me->query_skill("dali-shenmofu", 1) < 250 )
		return notify_fail("你的大力神魔斧还不够娴熟，无法使出「雷霆万钧」。\n");

	if (me->query_skill_mapped("force") != "tianmo-gong" )
       if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("你所使用的特殊内功不对。\n"); 

    if(me->query_skill("xixing-dafa", 1)<250)
       if(me->query_skill("tianmo-gong", 1) < 250)
                return notify_fail("以你现在的内功修为不够，还使不出「雷霆万钧」。\n");  

	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "axe"
	|| me->query_skill_mapped("axe") != "dali-shenmofu"
	|| me->query_skill_mapped("parry") != "dali-shenmofu" )
		return notify_fail("你无法使出大力神魔斧头的「雷霆万钧」。\n");

	if (me->query_temp("dlf/leiting"))
		return notify_fail("你正在使用「雷霆万钧」，休息一下吧。\n"); 
                
	if( (int)me->query("max_neili") < 2000)
		return notify_fail("你的内力修为太差，无法使出「雷霆万钧」。\n");
                
	if( (int)me->query("neili") < 1000)
		return notify_fail("你现在真气太弱，使不出「雷霆万钧」。\n");
	
	j = me->query_skill("dali-shenmofu", 1);
	
	if ( me->query_skill("dali-shenmofu", 1) > 350 )
		j = to_int( j/3* j/ 275.0);

	//j += focus * 5;
			
	me->set_temp("dlf/leiting",1);
	me->add_temp("apply/attack",j/2 );
	me->add_temp("apply/damage", j/2);
	
	//target->set_temp("combat_msg/dodge",HIY"忽然间，一道身影闪烁，$n瞬间向后滑出丈余，旋即又回到了原地。\n"NOR );
			
	//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER );
	
	//target->delete_temp("combat_msg/dodge");
	me->add_temp("apply/damage", -j / 2);
	me->add_temp("apply/attack",-j / 2 );
	
		
	msg = HBRED"\n$N大喝一声，全身劲力都集中到了右臂之上，将手中的"+weapon->query("name")+HBRED"抡圆了宛如车轮，全力向着$n劈了出去！\n"
	+"这一招力大斧沉，但却迅疾无比，宛如电闪雷鸣，雷霆万钧！试图一招定生死!\n"NOR;

	ap = me->query("combat_exp", 1) / 1000 * me->query_skill("axe",1);
	dp = target->query("combat_exp",1 ) / 1000 * target->query_skill("dodge",1);

	if ( target->is_busy()||!userp(target))
		dp -= dp/2;

	if( random( ap + dp) > dp ) {
		msg += HIR"\n$n被这招大力神魔斧的雷霆万钧招式所逼，当胸一撞，立时口中鲜血狂喷而出！\n"NOR;
		damage = me->query_skill("axe",1) + me->query_skill("force",1)+ me->query_skill("dali-shenmofu",1);
		damage = damage * 5;
		damage += random(damage);

		if( damage > 6000) 
			damage = 6000 + (damage- 6000)/10;
       
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2, me);

		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "砍伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "砍伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		me->add("neili", -350);
		me->add("jingli", -150);
	} 
     else {
		msg += HIW"突然之间，白影急晃，$n向后滑出丈余，立时又回到了原地。\n"NOR;
		me->add("neili", -100);
		me->add("jingli", -80);
	}
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add("neili", -100);
	me->add("jingli", -80);
	me->delete_temp("dlf/leiting");
	me->start_perform(3, "雷霆万钧");
	me->start_busy(random(2));
        return 1;
}

string perform_name(){ return HBYEL+RED"雷霆万钧"NOR; }

int help(object me)
{
        write(HBYEL+RED"\n大力神魔斧之「雷霆万钧」："NOR"\n\n");
        write(@HELP
		
        要求：  当前内力 1000 以上；
                最大内力 2500 以上；
                当前精力 1000 以上；
                大力神魔斧等级 250 以上；
                有效内功等级 250 以上；
                激发斧法为大力神魔斧；
                激发招架为大力神魔斧；
                激发内功为天魔功或吸星大法；
                且手持兵器。

HELP
        );
        return 1;
}
