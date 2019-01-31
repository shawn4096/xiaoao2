// rouyun.c 柔云
//强调女性的阴柔之术

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{

	int damage;
	

    
	if( !target ) target = offensive_target(me);

	if( !target ||!living(target)|| !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「柔云绝技」只能在战斗中对对手使用。\n");

	if( objectp( me->query_temp("weapon")) )
		return notify_fail("只有空手才能施展「柔云绝技」。\n");
    if( me->query_skill_mapped("dodge")!="huanmo-wubu" )
		return notify_fail("需要激发幻魔舞步方能施展「柔云绝技」。\n");
	if( (int)me->query_skill("tianmo-shou", 1) < 250 )
		return notify_fail("你的天魔掌法并不娴熟，不会使用「柔云绝技」。\n");

	if( (int)me->query_skill("tianmo-gong", 1) < 250 )
		if( (int)me->query_skill("xixing-dafa", 1) < 250 )
		return notify_fail("你的特殊内功等级不够，不能使用「柔云绝技」。\n");
	
	if( (int)me->query_dex() < 25 )
		return notify_fail("你的身法不够强，不能使用「柔云绝技」。\n");



	if( (int)me->query("neili", 1) < 1200 )
		return notify_fail("你现在内力太弱，不能使用「柔云绝技」。\n");

	if( (int)me->query("neili", 1) < 50 )
		return notify_fail("你现在的内力施展不了那么多招。\n");

	if( me->query_temp("tms/rouyun"))
		return notify_fail("你的正在施展柔云绝技！\n");
	if(target->is_busy())
		return notify_fail("对方已经忙乱，赶紧进攻吧！\n");
    damage=me->query_skill("tianmo-shou",1)+me->query_skill("tianmo-gong",1)+me->query_skill("xixing-dafa",1);
	damage=damage*2+random(damage);
	me->set_temp("tms/rouyun",1);

	message_vision(HIG"$N忽然双手一变，出手似乎极其柔软，动作似缓实快，仿佛将一团棉花柔在一起，正是天魔手「柔云绝技」！\n"NOR, me, target);
	message_vision(HIG"$N的双手瞬间变白，宛如玉石，轻描淡写地向$n胸前诸穴拂去！\n"NOR, me, target);
	if( random(me->query("combat_exp")) > target->query("combat_exp")/2
		||random(me->query_skill("hand",1))>target->query_skill("parry",1)/2)
	{
		message_vision(HIB"$n只觉$N的手掌在$n身上轻抚了一下，原本不甚在意，但瞬间一股极为阴柔的劲力传来！\n"NOR, me, target);
		target->add_condition("neishang",1+random(2));
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/5,me);
		if (userp(target)) target->add_busy(1);
		else target->add_busy(3+random(1));
		call_out("rouyun_attack",1+random(1),me,target);
	}    
	
	call_out("remove_effect",2,me);
    
	 return 1;
}
int rouyun_attack(object me,object target)
{
	if (!me) return;
	if (!me->is_fighting()||!target) 
	{
		message_vision(BLU"$N所蓄积的后劲一下打空，劲气外泄！\n"NOR,me,target);
		return 1;
	}
	message_vision(BLU"$N所施展的柔云劲力此时方才发作，$n只觉这股劲力在自己经脉中乱窜不已！$N随后连攻两招！\n"NOR,me,target);
	target->set_temp("must_be_hit",1);
		me->add_temp("apply/damage",me->query_skill("tianmo-shou",1)/4);
		 COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
		  COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
		 me->add_temp("apply/damage",-me->query_skill("tianmo-shou",1)/4);
	target->delete_temp("must_be_hit");
	target->add_condition("neishang",2+random(2));
	return 1;
}
int remove_effect(object me)
{
	if (!me) return 0;
	me->delete_temp("tms/rouyun");
	message_vision(HIC"$N一口浊气吐出，将柔云劲缓缓收功。\n"NOR,me);
	return 1;
}
string perform_name(){ return HIY"柔云绝技"NOR; }

int help(object me)
{
	write(HIG"\n天魔手之「柔云绝技」：\n"NOR);
	write(@HELP
	天魔手乃是日月神教中女性高手所创的一门绝学，以阴柔绵劲
	见长，充分发挥女性柔韧的特点，在战斗中轻描淡写之间将阴
	柔之招式施展在对方身上，暗含杀机，令对手防不胜防。
	柔云绝技是通过不经意间的接触，将阴柔劲气拍入对方穴道之
	中导致对方中招的阴险招式。

	指令：perform hand.rouyun

要求：	
	天魔手法等级 250 以上；
	基本手法等级 250 以上；
	天魔功等级 250 以上（或吸星大法）
	最大内力 1200 以上； 
	最小身法需求 25；
HELP
      );
   return 1;
}
