// qixing.c for murong-jianfa
// by sohu

#include <ansi.h>
int check_xu(object me);
void remove_effect(object me);
inherit F_SSERVER;
int perform(object me,object target)
{
    object weapon;
    int i = me->query_skill("murong-jianfa",1);
    int d = me->query_skill("shenyuan-gong",1);
	int dz = me->query_skill("douzhuan-xingyi",1);
    
    if( !target ) target = offensive_target(me);
     
	if( !target 
	|| !me->is_fighting(target) 
	|| !living(target)
	|| environment(target)!=environment(me))
		return notify_fail("剑转七星只能对战斗中的对手使用。\n");

	if(me->query_skill_mapped("force") != "shenyuan-gong")
		return notify_fail("你的内功不是神元功，无法使用剑转七星！\n");
	if( (int)me->query_skill("shenyuan-gong", 1) < 300 )
		return notify_fail("你的神元功火候不到，不能使用剑转七星！\n");
	if( (int)me->query_skill("murong-jianfa", 1) < 300 )
		return notify_fail("你的慕容剑法还没有精进，不能使用剑转七星！\n");
	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "murong-jianfa")
		return notify_fail("你手里没有剑，无法使用剑转七星！\n");
                
	if(me->query_skill_mapped("parry") != "douzhuan-xingyi")
		return notify_fail("剑转七星必须激发斗转星移，否则无法使用剑转七星！\n");
	if((int)me->query("max_neili") < 5000 )
		return notify_fail("你的内力修为不够，不能使用剑转七星！\n");
	if((int)me->query("neili") < 1500 )
		return notify_fail("你现在真气不足，不能使用剑转七星！\n");
	if((int)me->query("jingli") < 1000 )
		return notify_fail("你现在精力不足，不能使用剑转七星！\n");
	if((int)me->query_temp("qixing"))
		return notify_fail("你正在使用剑转七星！\n");
	if((int)me->query_skill("sword", 1) < 300 )
		return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用剑转七星。\n");
                
    message_vision(HIB"\n$N"HIB"默运"HIY"斗转星移"HIB"使出慕容剑法之精髓"HIY"「剑转七星」"HIB"，但见手中"+weapon->name()+HIB"勾画北斗七星，团团剑光已经将$n"HIB"笼罩住！\n"NOR, me,target);
    message_vision(HIB"\n$N"HIB"顺着北斗七星的方位连连进攻，手中"+weapon->name()+HIB"越舞越快，威力大增！\n"NOR, me,target);
    if (me->query("mrqixing/super","pass"))
    {
		message_vision(HIC"\n$N对斗转星移已经融会贯通，忽然剑锋再转，只见七朵绚烂的"+HIG+"剑花"+HIC+"依次在$n面前绽开，分别袭向$n的七大要穴！\n"NOR,me,target);
		me->receive_damage("neili", 1500);
		me->receive_damage("jingli", 50);
		me->add_temp("apply/attack", i/2+dz/2);
		me->add_temp("apply/damage", i/3);    
		me->add_temp("apply/dodge", d/2);
		//第一剑
		me->add_temp("qixing1",1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->delete_temp("qixing1");
		me->add_temp("qixing2",1);
		//第二剑
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
		me->delete_temp("qixing2");
		me->add_temp("qixing3",1);
		//第三剑
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->delete_temp("qixing3");
		me->add_temp("qixing4",1);
		//第四剑
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);  
		me->delete_temp("qixing4");
		me->add_temp("qixing5",1); 
		//第五剑
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
		me->delete_temp("qixing5");
		me->add_temp("qixing6",1); 
		//第六剑
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);  
		me->delete_temp("qixing6");
		me->add_temp("qixing7",1);
		//第七剑
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/attack", -(i+dz)/2);
		me->add_temp("apply/damage", -i/3);        
		me->add_temp("apply/dodge", -d/2);  

		me->delete_temp("qixing7");         
		message_vision(HIB"\n$N缓缓收功，收剑挺立场中，南慕容的气势凛然！\n"NOR,me,target); 
		me->start_busy(3);
		me->start_perform(4, "「剑转七星」");
		return 1;
    }
	else {
		me->set_temp("qixing", 1+i/50);
		me->receive_damage("neili", 50);
		me->receive_damage("jingli", 50);
		me->add_temp("apply/attack", i/2+dz/2);
		me->add_temp("apply/damage", d/5);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		me->add_temp("apply/attack", -(i+dz)/2);
		me->add_temp("apply/damage", -d/5);  
		call_out("check_fight", 1+random(3), me, 1+i/30);
		return 1;
	}
}

void remove_effect(object me)
{
	if(!me) return;
		me->delete_temp("qixing");
	if(!living(me)) return;
	if(me->query("mrqixing/super","pass")) return;
	message_vision(RED"\n$N由于没有明白斗转星移的最终奥秘，不小心错踏七星，顿时血气翻涌，头晕目眩！\n"NOR, me);
	me->receive_damage("qi", 100);
	me->receive_damage("jing", 50);
	if(!me->is_busy()) me->start_busy(1+random(2));
}

void check_fight(object me, int i)
{
	object weapon, target;

	if (!me ) return;

	target = offensive_target(me);

	if( !living(me) 
	|| !target 
	|| !me->is_fighting(target) 
	|| !living(target)
	|| environment(target)!=environment(me)
	|| !me->query_temp("qixing"))
		return remove_effect(me);

	else if(me->query_skill_mapped("sword") != "murong-jianfa"){
		tell_object(me, HIR"你临时改换剑法，决定不再使用「剑转七星」绝技。\n");
		remove_effect(me);
	}
	else if(me->query_skill_mapped("force") != "shenyuan-gong"){
		tell_object(me, HIR"你临时改换内功，决定不再使用「剑转七星」绝技。\n");
		remove_effect(me);
	}
	else if(me->query_skill_mapped("parry") != "douzhuan-xingyi"){
		tell_object(me, HIR"你临时改换招架，决定不再使用「剑转七星」绝技。\n");
		remove_effect(me);
	}
	else if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"){
		tell_object(me, HIR"你临时改换武器，决定不再使用「剑转七星」绝技。\n");
		remove_effect(me);
	}
	else if(me->is_busy()) 
		call_out("check_fight", 1+random(1), me, i);
    
    else{
		me->receive_damage("neili", 30);
		me->receive_damage("jingli", 10);
		me->add_temp("apply/attack", me->query_skill("murong-jianfa",1)/2);
		me->add_temp("apply/damage", me->query_skill("shenyuan-gong",1)/4);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		me->add_temp("apply/attack", -me->query_skill("murong-jianfa",1)/2);
		me->add_temp("apply/damage", -me->query_skill("shenyuan-gong",1)/4);  
		i--;
		call_out("check_fight", 1, me, i);
	}
}
   

string perform_name(){ return HIB"剑转七星"NOR; }
int help(object me)
{
        write(HIG"\n慕容剑法之"+HIB"「剑转七星」"NOR"\n\n");
        write(@HELP
        要求：  当前内力 1500 以上；
                最大内力 5000 以上；
                当前精力 1000 以上；
                慕容剑法等级 300 以上；
                神元功等级 300 以上；
                基本剑法等级 300 以上；
                激发剑法为慕容剑法；
                必须激发招架为斗转星移；
                激发内功为神元功。
HELP
        );
        return 1;
}