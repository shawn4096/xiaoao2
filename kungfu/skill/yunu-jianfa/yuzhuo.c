// yuzhuo.c 皓腕玉镯
//Created by sohu@xojh 2014/9

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIW"皓腕玉镯"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int ap, dp,damage;

	me->clean_up_enemy();
	target = me->select_opponent();

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「皓腕玉镯」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");
	tweapon = target->query_temp("weapon");
	damage=me->query_skill("yunu-jianfa",1)+me->query_skill("yunu-xinjing",1)+me->query_skill("suxin-jue",1);
	damage=damage*me->query_dex(1)/20+random(damage);

	if( !weapon
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("parry") != "yunu-jianfa" 
	 || me->query_skill_mapped("sword") != "yunu-jianfa" )
		return notify_fail("你现在无法使用「皓腕玉镯」。\n");

	if( !tweapon )
		return notify_fail("对方没有使用任何兵器，你无法使用「皓腕玉镯」。\n");

	if((int)me->query_skill("yunu-jianfa", 1) < 200 )
		return notify_fail("你的玉女剑法还不够娴熟，不会使用「皓腕玉镯」。\n");
	if((int)me->query_skill("yunu-xinjing", 1) < 200 )
		return notify_fail("你的玉女心法还不够娴熟，不会使用「皓腕玉镯」。\n");
	if((int)me->query("neili") < 2000 )
		return notify_fail("你的内力不够！\n");

	if( (int)me->query_dex() < 50 )
		return notify_fail("你的后天身法不足，无法使用「皓腕玉镯」。\n");

	if( me->query_skill_mapped("sword") != "yunu-jianfa"
		|| me->query_skill_mapped("parry") != "yunu-jianfa" )
                return notify_fail("你需要激发招架为玉女剑法，方能使用「皓腕玉镯」。\n");
	if( me->query_skill_mapped("force") != "yunu-xinjing")
                return notify_fail("你需要激发内功为玉女心经，方能使用「皓腕玉镯」。\n");
	message_vision(HIY"$N左手捏剑诀斜指，右手握住"+weapon->query("name")+NOR+HIY"在空中画了一个圆，一闪间却突然刺向$n的手腕。\n"NOR,me,target);

	//me->start_perform(3, "皓腕玉镯");

	ap = me->query("combat_exp")/100000;
	dp = target->query("combat_exp")/200000;

	if( random(ap)>dp
		||random(me->query_int(1))>target->query_int(1)/2
		|| random(me->query_dex(1))>target->query_dex(1)/2) 
	{				
		message_vision(HIR"$n只感手腕一痛，为$N刺中“寸关穴”，一个把握不住，手中兵器掉落地上。\n"NOR,me,target);
		target->add_busy(2+random(2));
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/4,me);
		if (tweapon)
		{
			tweapon->unequip();
			tweapon->move(environment(target));
		}
		
	}
	else {
		if (!objectp(tweapon) && objectp(target)) message_vision(CYN"$n急忙缩手，借力运功，身形随"+weapon->query("name")+CYN"而动，堪堪将$N的「皓腕玉镯」化于无形！\n"NOR,me,target);
		if (objectp(weapon) && objectp(tweapon))
			 message_vision(CYN"$n急忙缩手，借力运功，"+tweapon->query("name")+CYN"随"+weapon->query("name")+CYN"划出一道光环，将$N的「皓腕玉镯」化于无形！\n"NOR,me,target);
		me->add_busy(1);

	}
	if (me->query_skill("yunu-jianfa",1)<350)
	{
		me->start_perform(1,"皓腕玉镯");
	}
	me->add("neili",-300);
	me->add("jingli",-100);
	
	return 1;
}

int help(object me)
{
	write(WHT"\n玉女剑法之「皓腕玉镯」："NOR"\n");
	write(@HELP
	玉女剑法独特绝招，因古墓多为女子，所以玉女剑法
	不已力胜，而是靠剑招精妙凌厉，剑式轻柔灵动致胜
	身形清雅潇洒,姿态飘飘若仙,带著三分飘逸风姿，皓
	腕轻挥，以精妙剑招刺中对方手腕寸关穴。

	perform sword.yuzhuo
	
要求：
	当前内力要求 2000 以上；
	玉女剑法等级 200 以上；
	玉女心经等级 200 以上；
	有效身法等级 50  以上；
	激发剑法为玉女剑法；
	激发招架为玉女剑法；
	对手若手无兵器，则无效果。
HELP
	);
	return 1;
}