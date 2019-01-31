//liandao.c 
//by sohu@xojh 连续出刀
//王语嫣道：“是啊！他刚才使单刀圈住你，东砍那一刀，是少林寺的降魔刀法；西劈那一刀，是广西黎山洞黎老汉的柴刀十八路；
//回转而削的那一刀，又变作了江南史家的‘回风拂柳刀。’此后连使一十一刀，共是一十一种派别的刀法。后来反转刀背，在你肩头
//击上一记，这是宁波天童寺心观老和尚所创的‘慈悲刀’，只制敌而不杀人。他用刀架在你颈中，那是本朝金刀杨老令公上阵擒敌的招数，
//是‘后山三绝招’之一，本是长柄大砍刀的招数，他改而用于单刀。最后飞脚踢你一个斛斗，那是西夏回人的弹腿。”她一招一招道来，
//当真如数家珍，尽皆说明其源流派别，段誉听着却是一窍不通，瞠目以对，无置喙之余地。

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int j;
        object weapon = me->query_temp("weapon");
         j = me->query_skill("murong-daofa",1)/2+ me->query_skill("xingyi-zhang",1)/2;
        
		if (!userp(target)) j=j/2;
        else j =j /3;
 
		
		if(!userp(me)) j = j/ 3;
     
        if( !target ) target = offensive_target(me);

        if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))               
                return notify_fail("连刀绝技只能对战斗中的对手使用。\n");                

        if( (int)me->query_skill("murong-daofa", 1) < 350 )
                return notify_fail("你的刀法还未练成，不能使用连刀绝技！\n");        

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "murong-daofa")
                return notify_fail("你手里没有刀，无法使用连刀绝技！\n");

        if((int)me->query_skill("xingyi-zhang", 1) < 350 )
                return notify_fail("你的掌法还未练成，不能使用连刀绝技！\n");  

       /* if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("你的内功不是神元功，无法使用连刀绝技！\n");     
        if(me->query_skill_mapped("strike") != "xingyi-zhang" 
         || me->query_skill_prepared("strike") != "xingyi-zhang")
                return notify_fail("你没有用掌，无法使用连刀绝技！\n"); */


        if(me->query_skill_mapped("parry") != "xingyi-zhang")
		if(me->query_skill_mapped("parry") != "douzhuan-xingyi")

			if(me->query_skill_mapped("parry") != "murong-daofa")
                return notify_fail("你的招架功夫不对，无法使用连刀绝技！\n");

        if((int)me->query("max_neili") < 6000 )
                return notify_fail("你现在内力修为不够，不能使用连刀绝技！\n");      

        if((int)me->query("neili") < 1000 )
                return notify_fail("你现在内力不足，不能使用连刀绝技！\n");      

        if((int)me->query_skill("blade", 1) < 350 )
                return notify_fail("你的基本刀法不够娴熟，不能在刀招中夹杂使用连刀绝技。\n");

        if((int)me->query_skill("force", 1) < 350 )
                return notify_fail("你的基本内功不够娴熟，不能在刀招中夹杂使用连刀绝技。\n");     
        message_vision(HIG"\n$N拿起手中的"+weapon->query("name")+HIG"刹那间白光闪动，丈余圈子之内，全是刀影将$n裹将进来\n"+
			"$N每一刀都是完全不同的武功中的一招，似乎是拼凑起来的武技，但组合后却威力大增，正是慕容刀法的连刀绝技！\n"NOR, me,target);
        
		me->add("neili", -500); 
        me->add("jingli", -250);
        
        me->add_temp("apply/attack", j); 
        me->add_temp("apply/strength",j /10);
        me->add_temp("apply/blade",j);      
        me->add_temp("apply/damage",j/2);
		
		if (random(me->query_skill("blade",1))>target->query_skill("parry",1)/2)
		{
			message_vision(HIR"\n$n还没来得及跨步，便已给刀背上肩头重重敲了一下，“啊”的一声，脚步踉跄。$n脚步一乱，\n$N立时乘势直上，单刀的刃锋已劈向$n的后颈。\n"NOR,me,target);
			target->receive_damage("qi",1000+random(2000),me);
			target->add_busy(2);
			if (!userp(target)) target->add_busy(3);
			
		}
		me->set_temp("mrdf/liandao",7);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		
if(objectp(target) && me->is_fighting(target))
        {
              
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
				
        }
        if(objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
		
        if(objectp(target) && me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		if(objectp(target) && me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		if(objectp(target) && me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

		if(objectp(target) && me->is_fighting(target))
        {
               // weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				//weapon->wield();
        }
	    me->add_temp("apply/damage",-j/2);
        me->add_temp("apply/strength",-j /10);
        me->add_temp("apply/blade",-j);
        me->add_temp("apply/attack", -j);
		me->delete_temp("mrdf/liandao");
        //me->start_busy(1+random(2));
		me->start_perform(5,"连刀技");  
		return 1;
}
string perform_name(){ return HIY"连刀技"NOR; }

int help(object me)
{
        write(HIC"\n慕容刀法之"+HIB+"「连刀绝技」"NOR"\n\n");
        write(@HELP
	慕容刀法乃是慕容家族中传给家臣们的重要刀法武技，慕容氏
	早期乃是大燕国后裔，自慕容垂开始。崛起于军旅之间，刀法
	历经实战的演练，已经融合不少其他门派的刀法绝技，一刀既
	出，端的是厉害无比，防不胜防，因为是为家臣所用，所以内
	功不做特殊要求，若臂力越大，威力将增强。
	连刀绝技乃是将慕容氏家传武学融会贯通，形成强大的刀法集
	大成，或攻击犀利，或防御无隙，变化多端，极为厉害。
	
指令：perform blade.liandao
	
要求：
	当前内力需求 1000 以上；
	最大内力需求 6000 以上；
	当前精力需求 1000 以上；
	星移掌法等级 350 以上；
	慕容刀法等级 350 以上；
	基本掌法等级 350 以上；
	激发掌法为星移掌；
	激发刀法为慕容刀法
	激发招架为慕容刀法或斗转星移；
	手持刀类武器
                
HELP
        );
        return 1;
}
