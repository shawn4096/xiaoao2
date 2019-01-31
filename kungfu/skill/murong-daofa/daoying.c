//    /kungfu/skill/xingyi-zhang/daoying.c pfm daoying
// by leontt /22/6/2000

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int j;
        object weapon = me->query_temp("weapon");
        j = me->query_skill("murong-daofa",1);
        if (me->query_temp("sy/shenyuan"))
			j=j+me->query_skill("shenyuan-gong")/6;
		
		//if (!userp(target)) j=j/4;
        //else j =j /8;
 
		j=j/4;
        
		if( !target ) target = offensive_target(me);

        if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))               
                return notify_fail("刀影掌只能对战斗中的对手使用。\n");                

        if( (int)me->query_skill("murong-daofa", 1) < 220 )
                return notify_fail("你的刀法还未练成，不能使用刀影掌！\n");        

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "murong-daofa")
                return notify_fail("你手里没有刀，无法使用刀影掌！\n");

        if((int)me->query_skill("xingyi-zhang", 1) < 220 )
                return notify_fail("你的掌法还未练成，不能使用刀影掌！\n");  
        if((int)me->query_skill("strike", 1) < 220 )
                return notify_fail("你的基本掌法还未练成，不能使用刀影掌！\n");  
        if((int)me->query_skill("blade", 1) < 220 )
                return notify_fail("你的基本刀法不够娴熟，不能在刀招中夹杂使用刀影掌。\n");

        if((int)me->query_skill("murong-daofa", 1) < 220 )
                return notify_fail("你的慕容刀法不够娴熟，不能在刀招中夹杂使用刀影掌。\n");     

       /* if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("你的内功不是神元功，无法使用刀影掌！\n");      */

        if(me->query_skill_mapped("strike") != "xingyi-zhang" 
         || me->query_skill_prepared("strike") != "xingyi-zhang")
                return notify_fail("你没有用掌，无法使用刀影掌！\n");

        if(me->query_skill_mapped("parry") != "xingyi-zhang")
		if(me->query_skill_mapped("parry") != "douzhuan-xingyi")

			if(me->query_skill_mapped("parry") != "murong-daofa")
                return notify_fail("你的招架功夫不对，无法使用刀影掌！\n");

        if((int)me->query("max_neili") < 3000 )
                return notify_fail("你现在内力修为不够，不能使用刀影掌！\n");      

        if((int)me->query("neili") < 500 )
                return notify_fail("你现在内力不足，不能使用刀影掌！\n");      


        message_vision(HIR"\n$N大吼一声使出慕容绝技「刀影掌」，只见$P掌随刀走，片片刀光中夹杂着阵阵掌风一起奔向$n！\n"NOR, me,target);
        
		
		me->add("neili", -200); 
        me->add("jingli", -150);
        
        me->add_temp("apply/attack", j); 
        me->add_temp("apply/blade",j);
        me->add_temp("apply/damage",j/2);
		me->set_temp("mr_daoying",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
		
if(objectp(target) && me->is_fighting(target))
        {
                weapon->unequip(); 
				me->add_temp("apply/strike",j*3/2);
				message_vision(HIR"\n$N忽然在漫天飞舞的刀光中突出一掌，印向$n！\n"NOR, me,target);
				target->add_busy(2);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				me->add_temp("apply/strike",-j*3/2);

				weapon->wield(); 
        }
        if(objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		
        if(objectp(target) && me->is_fighting(target) && random((int)me->query_str()) > 30)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

      
	    me->add_temp("apply/damage",-j/2);
        me->add_temp("apply/blade",-j);
        me->add_temp("apply/attack", -j);
		me->delete_temp("mr_daoying");
        me->start_busy(1+random(2));
		me->start_perform(4,"刀影掌");  
		return 1;
}
string perform_name(){ return HIR"刀影掌"NOR; }

int help(object me)
{
        write(HIC"\n慕容刀法之"+HIR+"「刀影掌」"NOR"\n\n");
        write(@HELP
	慕容刀法乃是慕容家族中传给家臣们的重要刀法武技，慕容氏
	早期乃是大燕国后裔，自慕容垂开始。崛起于军旅之间，刀法
	历经实战的演练，已经融合不少其他门派的刀法绝技，一刀既
	出，刀中夹掌。端的是厉害无比，防不胜防，因为是为家臣所
	用，所以内功不做特殊要求，若臂力越大，威力将增强。
	
指令：perform blade.daoying

要求：
	当前内力 500 以上；
	最大内力 3000 以上；
	当前精力 1000 以上；
	星移掌法等级 220 以上；
	慕容刀法等级 220 以上；
	基本掌法等级 220 以上；
	激发掌法为星移掌；
	激发招架为慕容刀法或斗转星移；
                
HELP
        );
        return 1;
}
