// xuejian.c 飞雪四溅
//sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return CYN"飞雪四溅"NOR; }

int perform(object me, object target)
{
	string msg, *limbs, limb;
	object weapon;
    int damage, num, lvl, p,skill,i;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character() 
	 || !me->is_fighting(target))
		return notify_fail("飞雪四溅只能对战斗中的对手使用。\n");

	if (!me->query("quest/kl/sys/xuejian/pass"))
		return notify_fail("你虽然听说过“飞雪四溅”这一招，可是却因不懂真正奥秘。\n");

	lvl = me->query_skill("sanyin-shou", 1);
    skill=lvl+me->query_skill("xuantian-wuji", 1)/5;
	if (lvl < 250)
		return notify_fail("你的三阴手不够娴熟，无法使用飞雪四溅。\n");

	if (me->query_skill("throwing", 1) < 300)
		return notify_fail("你的基本暗器不够娴熟，无法使用飞雪四溅。\n");

    if ( me->query_skill_mapped("throwing") != "sanyin-shou")
		return notify_fail("你现在的情况，无法使用飞雪四溅。\n");
	if ( me->query_skill("hand", 1) < 300 )
		return notify_fail("你的基本手法等级不够，无法使用飞雪四溅。\n");
	if ( me->query_skill("sanyin-shou", 1) < 300 )
		return notify_fail("你的三阴手等级不够，无法使用飞雪四溅。\n");

	if ( me->query_skill("force", 1) < 300 )
		return notify_fail("你的基本内功等级不够，无法使用飞雪四溅。\n");

	weapon = me->query_temp("weapon");

	if (!weapon
		||weapon->query("skill_type")!="throwing")
		return notify_fail("飞雪四溅必须装备暗器才能使用。\n");

	if ((num = weapon->query_amount()) <= 2)
		return notify_fail("你掏了掏背囊，发现里面的暗器已经不够使用飞雪四溅的要求了！\n");

	if (me->query("neili") < 1000)
		return notify_fail("你的内力不够，无法使用飞雪四溅。\n");

	if (me->query("jingli") < 1000)
		return notify_fail("你的精力不够，无法使用飞雪四溅。\n");
	i=lvl/100;

	message_vision(HIW"\n$N从皮囊中抓出" + CHINESE_D->chinese_number(i) + weapon->query("base_unit") + weapon->query("name") + HIW"来，向四周撒去宛如飞雪四溅！\n"NOR,me,target);
    
	weapon->add_amount(-i);
    
	damage = (int)me->query_skill("sanyin-shou",1) + (int)me->query_skill("force",1) + (int)me->query_skill("throwing",1) ;
    
	if (random(me->query_dex()) > (int)target->query_dex() / 2
		||random(me->query_skill("throwing",1))>target->query_skill("parry",1)/2)
	{
		limbs = target->query("limbs");
		limb = limbs[random(sizeof(limbs))];
		//中了三阴手暗劲，伤害增大
		if (objectp(target) && target->query_temp("sys/sanyin"))
		{
			message_vision(HBYEL"$N见$n已中三阴手暗劲，手中的"NOR+weapon->query("name")+HBYEL"以飞雪四溅之势发出，威力倍增。\n"NOR,me,target);
			damage=2*damage;
		}
		message_vision(HIR"$n躲闪不及，“噗噗”地几声，被"+chinese_number(i)+HIR"道暗器击中！\n"NOR,me,target);
		damage=damage*2+random(damage);
		
		if (!userp(target)) damage=damage*2;
		if (damage>6000) damage=damage+(damage-6000)/100;
		
		target->receive_damage("qi", damage, me);
        target->receive_wound("qi", damage/3, me);
		me->add("neili", -400);
		me->add("jingli", -100);
		
		p = (int)target->query("eff_qi") * 100 / (int)target->query("max_qi");
		msg = COMBAT_D->damage_msg(damage, "刺伤");
		msg = replace_string( msg, "$l", limb);
		msg = replace_string( msg, "$w", weapon->name());
		msg += "( $n" + COMBAT_D->eff_status_msg(p) + " )\n";
        message_vision(msg, me, target);

		if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR); 
		

	}
	else {
			me->add("neili", -150);
			me->add("jingli", -50);
			message_vision(HIY"$n吓得赶忙抱头团身，万分狼狈地向旁边一滚，方才堪堪地躲了过去。\n" NOR,me,target);					
			//target->add_busy(2+random(2));

	}

	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/4);
	me->add_temp("apply/throwing",skill/4);
	me->set_temp("sys/xuejian",1);
    if (objectp(target)&&me->is_fighting(target)&&me->query_skill("sanyin-shou",1)>200)
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
    if (objectp(target)&&me->is_fighting(target)&&me->query_skill("sanyin-shou",1)>250)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("sanyin-shou",1)>300)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("sanyin-shou",1)>350)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("sanyin-shou",1)>450)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->delete_temp("sys/xuejian");

	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/4);
	me->add_temp("apply/throwing",-skill/4);
	me->start_perform(4, "「飞雪四溅」");
	me->start_busy(1+random(2));
	if (num <= (int)lvl / 50)
	{
		weapon->unequip();
		tell_object(me, "\n你的" + weapon->query("name") + "快用完了！\n");
	}
	me->add("neili", -350);
	me->add("jingli", -200);
	return 1;
}

int help(object me)
{
        write(HIC"\n三阴手之「飞雪四溅」："NOR"\n");
        write(@HELP
	乃是灵清居士在观悟昆仑雪山飞溅而悟，以三阴手法
	一次同时弹出许多的暗器，让对手防不胜防，避无可
	避。同时，由於使用暗器数量极多，若是连续使用必
	须注意，以免战中发现暗器不够了。此招式在使用过
	程中随技能提升而不断强大，请玩家自己尝试。
	注意，若和三阴手的三阴暗劲配合，威力大增，需向
	门中长老请教。

	perform hand.xuejian
	
要求：  
	基本内功等级 300 以上；
	基本暗器等级 300 以上
	三阴手法等级 300 以上
	基本手法等级 300 以上；
	当前内力要求 1000 以上；
	当前精力要求 1000 以上
	激发手法三阴手；
	激发暗器三阴手；
	备手法为三阴手
	配合三阴手暗劲使用攻击伤害增加；
	必须准备暗器。
HELP
        );
        return 1;
}
