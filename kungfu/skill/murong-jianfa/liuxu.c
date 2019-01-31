// liuxu.c 柳絮剑法

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	string msg, dodge_skill;
	object weapon;
	int ap, dp,i,skill;
    
	if( !target ) target = offensive_target(me);

	//if( !me->query("quest/mr/mrjf/liuxu/pass") )
		//return notify_fail("你未得传授「柳絮剑法」。\n");

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target)
	|| !living(target) )
		return notify_fail("「柳絮剑法」只能对战斗中的对手使用。\n");


	if( (int)me->query_skill("murong-jianfa", 1) < 200 )
		return notify_fail("你的慕容剑法功力太浅了。\n");

	if( (int)me->query_skill("sword", 1) < 200 )
		return notify_fail("你的基本剑法功力太浅了。\n");

	if( (int)me->query_skill("shenyuan-gong", 1) < 200 )
		return notify_fail("你的内功功力太浅了。\n");

	if( (int)me->query("max_neili") < 3000 )
		return notify_fail("你的内力太浅了。\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("你的真气不够。\n");

	if( me->query_skill_mapped("force") != "shenyuan-gong" )
		return notify_fail("慕容剑法乃慕容家传武功，需要神元功支持「柳絮剑法」？\n");
	if( me->query_temp("mrjf/liuxu") )
		return notify_fail("你正在使用「柳絮剑法」\n");
	if( target->query_temp("mrjf/liuxu") )
		return notify_fail("对方已经身中你的「柳絮剑法」\n");

	if( !objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "murong-jianfa")
	 
		return notify_fail("你激发不对使得了「柳絮剑法」么?\n");
	
	//if( target->is_busy() )
		//return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");
	//For npc Chan+liuxu 流氓至极
      
	ap = me->query("combat_exp")/100000;
	dp = target->query("combat_exp")/100000;
	//550级后增加命中
	if( me->query_skill("murong-jianfa", 1) > 549 )
	{
		ap += random(ap/2);
       // me->set_temp("apply/armor",me->query("shenyuan-gong",1)/3);
	}	      

	message_vision(HIW"\n$N施展出慕容剑法中的柳絮剑法，手中"+weapon->query("name")+HIW"立即变成无声无息，宛如柳絮飞扬,但剑气却极其凌厉！\n"NOR,me,target);
	
	skill=(int)me->query_skill("murong-jianfa",1);
	
	if (me->query("quest/mr/syg/pass"))
	{
		skill=skill+me->query_skill("shenyuan-gong",1)/2;
	}
	
	if ( random( ap + dp ) > dp 
		||random(me->query_int())>target->query_int()/2) 
	{
		message_vision(HIC"\n$n忽觉$N攻势诡异，剑招突兀难制，防不胜防，立时中招！\n"NOR,me,target);		
		
		if (userp(target)) target->add_busy(2);
		else target->add_busy(4);
		
		if( target->query_temp("lost_attack") < 1 )
			target->add_temp("lost_attack", 2+random(3));
		me->add("neili", -300);
		me->add("jingli", -100);
		//降低对方防御
		me->set_temp("mrjf/liuxu",skill);
		if (!target->query_temp("mrjf/liuxu"))
		{
			target->add_temp("apply/dodge",-skill/6);
			target->add_temp("apply/attack",-skill/6);
			target->add_temp("apply/parry",-skill/6);
			
			target->set_temp("mrjf/liuxu",skill);
	//调用target
			call_out("target_liuxu",(int)skill/50,target);

		}
		//调用自己判断
		call_out("liuxu_effect",1,me,(int)skill/20);		
		
	}
	else {
		
		message_vision(HIY"$n轻轻一纵身，躲开了$N这招攻击！\n"NOR, me, target);

		me->add("neili", -100);
		me->add("jingli", -50);
		me->start_busy(1);
		me->start_perform(1+random(2), "「柳絮剑法」");
	}	
	return 1;
}

int liuxu_effect(object me,int count)
{

        object weapon;
		int skill;
		if (!me) return 0;
		
		weapon=me->query_temp("weapon");

		if (!me->is_fighting()
			|| me->query_skill_mapped("sword")!="murong-jianfa"
			|| !weapon
			|| !me->query_temp("mrjf/liuxu")
			|| count < 0
			|| weapon->query("skill_type")!="sword")
		{				
			
			me->delete_temp("mrjf/liuxu");			
			message_vision(HIB"$N将手中的剑舞个花，柳絮剑法缓缓收功。\n"NOR,me);			
			return 1;
		}
		call_out("liuxu_effect",1,me,count--);
		
	  
}
int target_liuxu(object target)
{
	int skill;
	if (!target) return 0;
	if (!target->query_temp("mrjf/liuxu")) return 0;

	skill=target->query_temp("mrjf/liuxu");
	
	tell_object(target, HIW"你逐渐恢复了身中「柳絮剑法」所带来的衰弱状态。\n"NOR);
	target->add_temp("apply/attack", skill/6);
	target->add_temp("apply/dodge", skill/6);
	target->add_temp("apply/parry", skill/6);
	target->delete_temp("mrjf/liuxu");
	return 1;
	
	
}

string perform_name(){ return HIC"柳絮剑法"NOR; }

int help(object me)
{
        write(MAG"\n慕容剑法之「柳絮剑法」："NOR"\n\n");
        write(@HELP
	柳絮剑法是南慕容家传慕容剑法的精妙武技，
	凭借其深厚的内功修为，将内力灌注与剑招
	之中，无声无息，快速出招，在短时间内对
	敌人形成潜在的威胁，为慕容氏初期武技
	
	指令：perform sword.liuxu

要求：  
	当前内力要求 1000 以上;
	最大内力要求 3000 以上；
	慕容剑法等级 200 以上；
	神元功法等级 200 以上；
	基本剑法等级 200 以上；
	激发剑法为慕容剑法；
	激发内功为神元功；

HELP
        );
        return 1;
}
