// modified by darken@SJ

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	int focus, i, j;
	string str;

	focus = me->query_temp("ss/focus");

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) 
	|| !living(target))
		return notify_fail("剑光飞舞只能对战斗中的对手使用。\n");

	if( me->query_skill("songshan-jian", 1) < 250 )
		return notify_fail("你的嵩山剑法功力太浅，无法使用飞舞攻击。\n");

	if( me->query_skill("sword", 1) < 250 )
		return notify_fail("你的基本剑法功力太浅，无法使用飞舞攻击。\n");

	if( me->query_skill("hanbing-zhenqi", 1) < 250 )
		return notify_fail("你的内功功力太浅，无法使用飞舞攻击。\n");
                
	if( me->query("max_neili") < 2000 )
		return notify_fail("你的内力太浅，无法使用飞舞攻击。\n");

	if( me->query("neili") < 800 )
		return notify_fail("你的真气不足，无法使用飞舞攻击。\n");

	if (me->query_skill_mapped("force") != "hanbing-zhenqi")
		return notify_fail("你用什么为基础来使嵩山剑绝技么?\n");

	if (!objectp(weapon = me->query_temp("weapon")) 
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "songshan-jian"
	|| me->query_skill_mapped("parry") != "songshan-jian" )
		return notify_fail("你使得了嵩山剑绝技么?\n");

	i = me->query_skill("songshan-jian", 1);

	message_vision(HIB"\n$N长啸一声，举剑挺刺，在半空中划出道道剑光，空中气劲激荡，阵阵寒气向$n奔袭而去！\n" NOR,me,target);
  if(me->query_temp("ss/hb"))
	message_vision(HIB"\n$N更将「寒冰诀」发挥得淋漓尽致，身周寒光大盛！\n" NOR,me);
 
	j = i / 4;
        if ( i > 200 )
	j = to_int(i/ 4.0 * i/ 200.0);

	if ( focus > 20 ) focus = 20;
	j += 5 * focus;
	
	//削弱NPC威力
    if(!userp(me)) j = j /4;

		
		me->add_temp("apply/attack", j/2);
	    
		me->add_temp("apply/sword",  j/4);
        //me->add_temp("apply/hand",  j );
	    me->add_temp("apply/damage", j/4 );
	if(me->query_temp("ss/hb"))
	{
       	me->add_temp("apply/damage", j/4);
		me->set_temp("ssj/fwhanbing",1);
	}
    if (me->query("quest/ss/ssjf/feiwu/pass"))
    {
		message_vision(HIG"\n$N更将自己所领悟的「松涛飞舞」绝技发挥出来，飞舞绝技施展出来更是出神入化，威力倍增！\n" NOR,me,target);
		if (!userp(target))
			target->add_busy(2+random(1));
		else target->add_busy(1);
		me->add_temp("apply/damage", j/5);
		me->add_temp("apply/sword", j/5);
    }
	me->set_temp("ss/feiwu",j);
	
	if (wizardp(me)) write("damage="+j);
	//1
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	//2
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
    //3
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	//4,,,,250后再出一招
    if(me->is_fighting(target) && (int)me->query_skill("songshan-jian", 1) > 250 )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    //5,,,300后再出一招嵩阳手
	if( me->is_fighting()&& objectp(target)
		&&me->query_skill("songyang-shou", 1) > 300 
		&&me->query_skill_mapped("hand")=="songyang-shou" 
		&&me->query_skill_mapped("hand")=="songyang-shou" )  
		{
		  target->add_busy(1+random(1));
	      weapon->unequip();
		  message_vision(HIC"\n$N长啸一声，剑法突变，手中剑向后一背，电石火光间猛然施展出大嵩阳手的招数！\n" NOR, me);
		  me->add_temp("apply/hand",j/3);
		  COMBAT_D->do_attack(me, target,0, userp(me)?3:1);
		  me->add_temp("apply/hand",-j/3);
          weapon->wield();
		}
/*
	
if(me->is_fighting(target)&&me->query_skill("songshan-jian",1)>300)
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	*/
	if(me->query_temp("ssj/fwhanbing"))
	{
		me->add_temp("apply/damage", -j/4);	
		me->delete_temp("ssj/fwhanbing");
    }
	if (me->query("quest/ss/ssjf/feiwu/pass"))
    {
		me->add_temp("apply/damage", -j/5);
		me->add_temp("apply/sword", -j/5);
    }
	me->add_temp("apply/attack",-j/2);
	me->add_temp("apply/sword",  -j /4);
       // me->add_temp("apply/hand",  -j );
	me->add_temp("apply/damage", -j/4 );
    me->delete_temp("ss/feiwu");
	me->add("neili", -350);
	me->add("jingli", -150);
	me->start_busy(1+random(2));
	me->start_perform(3+random(2), HIB"飞舞"NOR);
	message_vision(HIB"\n$N这几招星矢如电，如万松飞舞，施展完后，长吁一口气，缓缓收功！\n" NOR,me);

	return 1;
}

string perform_name(){ return HBBLU+HIW"寒光飞舞"NOR; }

int help(object me)
{
        write(HIB"\n嵩山剑法之「飞舞」："NOR"\n\n");
        write(@HELP
	嵩山剑法有“内八路，外九路”之称，总共十七路长短快慢的剑法
	应有尽有。当年五岳剑派与魔教十长老两度会战华山，五岳剑派
	的好手死伤殆尽，五派剑法的许多惊世绝招随五派高手而消逝。
	嵩山派掌门左冷禅会集本派残存的耆老，将各人所记得的剑招不
	论粗精，尽数录了下来，汇成一部剑谱。
	剑光飞舞招式是嵩山派的绝技之一，乃是凭借一口真气在短时间
	内连续出招，若再配合嵩山派独特内功寒冰真气，则此招威力更
	甚。需注意的是飞舞每200级威力飞跃一次。
	
	指令：perform sword.feiwu

要求：
	当前内力需求 800 以上；
	最大内力需求 2000 以上；
	当前精力需求 500 以上；
	嵩山剑法等级 250 以上；
	寒冰真气等级 250 以上；
	基本剑法等级 250 以上；
	激发手法为大嵩阳手：
	激发剑法为嵩山剑法；
	激发招架为嵩山剑法；
	激发内功为寒冰真气；
	且手持兵器。

HELP
        );
        return 1;
}
