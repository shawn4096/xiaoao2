//sanxian 云龙三现
//by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
void next1(object me, object target);
void next2(object me, object target);

int perform(object me,object target)
{
	int i;
	string msg;
    object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("云龙三现只能对战斗中的对手使用。\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够使用云龙三现！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用云龙三现！\n");

        if (!weapon ||weapon->query("skill_type")!="blade")
                return notify_fail("你手中无刀怎能使用云龙三现？！\n");
		if (me->query_skill("blade",1)<300)
                return notify_fail("你的基本刀法不足300，怎能使用云龙三现？！\n");
		if (me->query_skill("force",1)<300)
                return notify_fail("你的基本内功不足300，怎能使用云龙三现？！\n");

		if (me->query_skill("hujia-daofa",1)<300)
                return notify_fail("你的胡家刀法不足300，怎能使用云龙三现？！\n");
       // if (!me->query_temp("hujia-daofa/luanren",1)||!me->query_temp("hujia-daofa/nizhuan",1))
               // return notify_fail("你不使用“阴阳(perform yinyang)倒乱(perform nizhuan)刃法”怎么能用云龙三现封住敌人行动！\n");

        if ( me->query_skill_mapped("blade") != "hujia-daofa" )
             	return notify_fail("你必须先激发刀法为胡家刀法。\n");
      //  if (me->query_temp("hjdf/yunlong"))
				// return notify_fail("你正在施展胡家刀法中的云龙三现。\n");
	
	message_vision( HIC"$N手中"+weapon->query("name")+HIC"一起，一招“大三拍”，刀光闪闪，已将$n上盘罩住，\n"+
		"随即$N所划刀光却笼罩住了$n的前后左右，令$n绝无闪避躲让之处。\n"NOR,me,target);
	
	me->start_perform(5,"「云龙三现」");
	//me->set_temp("hjdf/yunlong",1);
	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
	   || random(me->query_int())>target->query_int()/2)
	{
		
		msg = HIR "\n\n$n只得一招“横担铁门闩”，硬接了$N这招。\n" NOR;
		target->add_busy(2);
	}
	else {
		msg = HIW "可是$n看破了$N的企图，飞快的向后退去。\n" NOR;
		me->start_busy(1);
	}
	message_vision(msg, me, target);
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);

	if (objectp(target)&&me->is_fighting())
		next1(me, target);
	return 1;
}

void next1(object me, object target)
{
	string msg;
	int damage;
	object weapon;

	if (!me) return ;
		weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("hjdf/yunlong");
		return ;
	}

	msg = YEL"\n$N当下从东至西，自南趋北，依着“大四象方位”，斜行直冲，随手胡乱发招。\n"+
		"只要$n撞上了，不死也得重伤，便算不撞上，只要一架一闪，立时便会被陷入刀影中。\n"NOR;

	if(random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_skill("hujia-daofa",1))> target->query_skill("dodge",1)/2 )
	{
		msg = msg + HIR"$n双臂酸麻更甚，只要再给$N这般砍上几刀，$n手臂上的筋络也要给震伤。\n"NOR;
		damage = me->query_skill("hujia-daofa",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/20;
		damage += random(damage);
		
		target->add("neili",-(1000+random(500)));
		if (target->query("neili")<0) target->set("neili",10);
		
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		if (wizardp(me)) write("damage2="+damage);
	    
		msg += damage_msg(damage, "震伤");
		msg = replace_string(msg, "$w", weapon->query("name"));
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		msg  =  msg + CYN"$n凭借灵巧的身法躲开了这一招。\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1+random(2));
		target->start_busy(1+random(2));
	}
	me->start_perform(5,"云龙三现");

	if (objectp(target)&&me->is_fighting())
		next2(me, target);
	return;

}

void next2(object me, object target)
{
	string msg;
	int damage;
	object weapon;

	if( !me) return ;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("hjdf/yunlong");
		return ;
	}

	msg = WHT "\n$N并不跃起，反而抢前一步，直欺入怀，手起刀落，"+weapon->query("name")+WHT"已击中$n的左肩。\n"NOR;

	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		||random(me->query_str()) >target->query_dex()/3)
	{
		msg = msg + HIC "$n这"+weapon->query("name")+HIC"的一击自然伤他不着什么，但$n却面色大变！\n"NOR;
		damage = me->query_skill("hujia-daofa",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/20;
		damage += random(damage);
		
		//if (!target->is_busy()) target->start_busy(damage/500);
		target->add_temp("apply/attack", -200);
		target->add_temp("apply/dodge", -200);
		target->add_temp("apply/parry", -200);
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
				if (wizardp(me)) write("damage3="+damage);

		msg += damage_msg(damage, "砍伤");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-150);
		if (objectp(target))
			call_out("back", 5+random(5), target);
	} else {
		msg = msg + HIW "$n运起轻功，向前一跃，躲开一旁。\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
	me->delete_temp("hjdf/yunlong");
	me->start_perform(4,"云龙三现");
	return;
}

void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 200);
	target->add_temp("apply/dodge", 200);
	target->add_temp("apply/parry", 200);
}
string perform_name(){ return HIC"云龙三现"NOR; }

int help(object me)
{
   write(WHT"\n胡家刀法之「"HIG"云龙三现"WHT"」："NOR"\n");
   write(@HELP
	此「云龙三现」乃巧用内劲和身法配合，以胡家刀法中
	精奇的招式配合连砍三刀，攻敌一个措手不及。此招乃
	需要依靠丰富的战斗经验和相应的臂力与悟性。若对方
	为你所打中，则会出现一定程度的虚弱和忙碌状态。

	指令：perform blade.yunlong

要求：
	当前内力 1000 以上；
	当前精力 1000 以上；
	胡家刀法 300 以上；
	基本刀法 300 以上；
	基本内功 300 以上；
	激发刀法为胡家刀法；
	手中持刀；

HELP
   );
   return 1;
}
