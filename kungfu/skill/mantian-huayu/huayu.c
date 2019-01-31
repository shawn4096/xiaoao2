// huayu.c 漫天花雨

#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return HIG"漫天花雨"NOR; }

int perform(object me, object target)
{
	string msg, *limbs, limb;
	object weapon;
        int damage, num, lvl, p;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character() 
	 || !me->is_fighting(target))
		return notify_fail("漫天花雨只能对战斗中的对手使用。\n");

	if (me->query("quest/hmy/mthy/huayu/pass")!="pass")
		return notify_fail("你虽然听说过“漫天花雨”这一招，可是却未获传授。\n");

	lvl = me->query_skill("mantian-huayu", 1);

	if (lvl < 250)
		return notify_fail("你的漫天花雨不够娴熟，无法使用漫天花雨。\n");

	if (me->query_skill("throwing", 1) < 250)
		return notify_fail("你的基本暗器不够娴熟，无法使用漫天花雨。\n");

    if ( me->query_skill_mapped("throwing") != "mantian-huayu")
		return notify_fail("你现在的情况，无法使用漫天花雨。\n");

	if ( me->query_skill("tianmo-gong", 1) < 250 )
		if ( me->query_skill("xixing-dafa", 1) < 250 )
		return notify_fail("你的特殊内功等级不够，无法使用漫天花雨。\n");

	weapon = me->query_temp("weapon");
    
	if (!weapon)
		return notify_fail("漫天花雨必须装备暗器才能使用。\n");

	//if ((num = weapon->query_amount()) < lvl / 20)
	if (weapon->query_amount()< 2)
		return notify_fail("你掏了掏背囊，发现里面的暗器已经不够使用漫天花雨的要求了！\n");
	
	if (weapon->query_amount() < lvl / 80) {
		weapon->unequip();
		tell_object(me, "\n你的" + weapon->query("name") + "用完了！\n");
		return notify_fail("你囊中没有暗器可用！\n");
	}

	if (me->query("neili") < 1000)
		return notify_fail("你的内力不够，无法使用漫天花雨。\n");

	if (me->query("jingli") < 900)
		return notify_fail("你的精力不够，无法使用漫天花雨。\n");
	
	num=lvl/80;
	msg = HIY"\n$N身子向外飞出去，跟着一口鲜血急喷而出，回手抓出" + CHINESE_D->chinese_number(lvl / 80) + weapon->query("base_unit") + weapon->query("name") + HIY"来，如雨般散出!\n"
	+"$n"HIY"见到这丛黑针，久闻魔教黑血神针的大名，无不惊心，闪避间乱成一团，$n只觉眼前似乎在下一场暗器雨！\n"NOR;
	
		weapon->add_amount(-(lvl/80));

       damage = (int)me->query_skill("mantian-huayu",1) + (int)me->query_skill("force",1) + (int)me->query_skill("hand",1) ;
       if (random(me->query_dex()) > (int)target->query_dex() / 2
		   ||random(me->query("combat_exp"))>target->query("combat_exp")/2) {
		limbs = target->query("limbs");
		limb = limbs[random(sizeof(limbs))];
		msg += HIB"$n躲闪不及，“噗噗”地几声，被几道神针暗器击中！\n"NOR;
		if (objectp(target)&&target->query_temp("hmy/shenzhen"))
		{
			message_vision(HBYEL"$N见$n已经身中神针，手中的"NOR+weapon->query("name")+HBYEL"以漫天花雨之势发出，威力倍增。\n"NOR,me,target);
			damage=2*damage;
		}
		damage=damage*2+random(damage);
		if (!userp(target)) damage=damage*2;
		if (damage>5000) damage=damage+(damage-5000)/100;
		
		target->receive_damage("qi", damage, me);
        target->receive_wound("qi", damage/3, me);
		me->add("neili", -400);
		me->add("jingli", -100);
		p = (int)target->query("eff_qi") * 100 / (int)target->query("max_qi");
		msg += COMBAT_D->damage_msg(damage, "刺伤");
		msg = replace_string( msg, "$l", limb);
		msg = replace_string( msg, "$w", weapon->name());
		msg += "( $n" + COMBAT_D->eff_status_msg(p) + " )\n";
        if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR); ;
	}
	    else {
		me->add("neili", -150);
		me->add("jingli", -50);
		msg += HIW"$n吓得赶忙抱头团身，万分狼狈地向旁边一滚，方才堪堪地躲了过去。\n" NOR;
		target->add_busy(1+random(2));
	}
	message_vision(msg, me, target);
	if (weapon->query("skill_type")=="throwing"&&!me->query_temp("anqi/damage"))
	{
		me->add_temp("apply/damage",lvl/4);
		message_vision(HIC"$N手中的"+weapon->query("name")+HIC"在内力激发下，闪耀着森森的寒光！\n"NOR,me);
		me->set_temp("anqi/damage",lvl);
	}
    me->add_temp("apply/throwing",lvl/2);
	me->add_temp("apply/damage",lvl/3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("mantian-huayu",1)>150)
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
    if (objectp(target)&&me->is_fighting(target)&&me->query_skill("mantian-huayu",1)>200)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("mantian-huayu",1)>250)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("mantian-huayu",1)>300)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("mantian-huayu",1)>350)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/throwing",-lvl/2);
	me->add_temp("apply/damage",-lvl/3);
	if (me->query_temp("anqi/damage"))
	{
		me->add_temp("apply/damage",-lvl/4);
		me->delete_temp("anqi/damage");
		//message_vision(HIC"$N手中的"+weapon->query("name")+HIC"在内力激发下，闪耀着森森的寒光！\n"NOR,me);
	}
	me->start_perform(4, "「漫天花雨」");
	me->start_busy(1+random(2));
	
	
	return 1;
}

int help(object me)
{
        write(HIC"\n漫天花雨之"HIG"「漫天花雨」："NOR"\n");
        write(@HELP
	一次同时弹出许多的暗器，让对手防不胜防，避无可避。同时，由於使用暗
	器数量极多，若是连续使用必须注意，以免战中发现暗器不够了。此招式在
	使用过程中随技能提升而不断强大，250飞跃一次，300，350,450各自飞跃。

	指令;perform throwing.huayu

要求：  
	天魔功或吸星大法等级 250 以上；
	漫天花雨等级 250 以上；
	当前内力 1000 以上；
	配合幻魔舞步使用攻击伤害增加；
	必须准备暗器。
HELP
        );
        return 1;
}
