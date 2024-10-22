//songfeng.c 松风如潮

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	int j;


	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) 
	|| !living(target))
		return notify_fail("松风如潮只能对战斗中的对手使用。\n");

	if( me->query_skill("songfeng-jian", 1) < 100 )
		return notify_fail("你的青城派绝技松风如潮法功力太浅，无法使用松风如潮攻击。\n");

	if( me->query_skill("sword", 1) < 100 )
		return notify_fail("你的基本剑法功力太浅，无法使用松风如潮攻击。\n");

	if( me->query_skill("force", 1) < 100 )
		return notify_fail("你的基本内功功力太浅，无法使用松风如潮攻击。\n");
                
	if( me->query("max_neili") < 1000 )
		return notify_fail("你的内力太浅，无法使用松风如潮攻击。\n");

	if( me->query("neili") < 800 )
		return notify_fail("你的真气不足，无法使用松风如潮攻击。\n");


	if (!objectp(weapon = me->query_temp("weapon")) 
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "songfeng-jian"
	|| me->query_skill_mapped("parry") != "songfeng-jian" )
		return notify_fail("你使得了青城派绝技松风如潮绝技么?\n");

	j = me->query_skill("songfeng-jian", 1);

	message_vision(HIG"\n$N剑光一阵晃动，宛如风过松林，一阵澎湃的剑气伴随着剑招如潮般的攻来！\n" NOR,me,target);
	
	//削弱NPC威力
		
		me->add_temp("apply/attack", j/4);
	    
		me->add_temp("apply/sword",  j/5);
	    me->add_temp("apply/damage", j/5);

	me->set_temp("sfj/songfeng",j);
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	//2
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
    //3
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	//4,,,,250后再出一招
    if(me->is_fighting(target) && (int)me->query_skill("songfeng-jian", 1) > 250 )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    //5,,,300后再出一招嵩阳手
	
if(me->is_fighting(target)&&me->query_skill("songfeng-jian",1)>300)
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-j/4);
	me->add_temp("apply/sword",  -j /5);
	me->add_temp("apply/damage", -j/5 );
    me->delete_temp("sfj/songfeng");
	me->add("neili", -350);
	me->add("jingli", -150);
	me->start_busy(1+random(2));
	me->start_perform(3+random(2), HIB"松风如潮"NOR);
	message_vision(HIG"\n$N这几招耗力巨大，如万松松风如潮，施展完后，长吁一口气，缓缓收功！\n" NOR,me);

	return 1;
}

string perform_name(){ return HIG"松风如潮"NOR; }
