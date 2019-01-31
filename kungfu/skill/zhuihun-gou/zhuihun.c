// zhuihun.c 追魂 
//
// by sohu@xojh 2015

#include <ansi.h>

inherit F_SSERVER;
int remove_effect(object me,object target,object weapon,int conut);

int perform(object me, object target)
{
       object weapon = me->query_temp("weapon");  
       int skill;
    
       if( !target ) target = offensive_target(me);
       
       if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
           return notify_fail("「追魂绝技」只能在战斗中对对手使用。\n");
       if(!me->query("quest/xx/zhg/pass"))
           return notify_fail("你虽然听说过「追魂钩法」，但从并没有学会。\n");
       if ( (int)me->query_skill("huagong-dafa", 1) < 500 )
           return notify_fail("你的内功等级不够，不能使用「追魂绝技」。\n");
    
       if ( (int)me->query_skill("zhuihun-gou", 1) < 500 )
           return notify_fail("你的天山追魂钩不够娴熟，不能真正发挥「追魂绝技」。\n");
    
       if (!weapon 
        || weapon->query("skill_type") != "hook"
        || me->query_skill_mapped("hook") != "zhuihun-gou")
           return notify_fail("你现在无法使用「追魂绝技」来提高攻击力。\n");
    
       if ( (int)me->query("max_neili") < 15000 )
           return notify_fail("你的内力修为不够，不能使用「追魂绝技」。\n");

       if ( (int)me->query("max_jingli") < 1000 )
           return notify_fail("你的精力修为不够，不能使用「追魂绝技」。\n");

       if ( (int)me->query("neili") < 700 )
           return notify_fail("你现在内力太弱，不能使用「追魂绝技」。\n");
    
       if ( (int)me->query_temp("zhuihun/lpf") ) 
           return notify_fail("你正在使用天山追魂钩之「追魂绝技」。\n");
    
       if (me->query_skill_mapped("force") != "huagong-dafa")
           return notify_fail("你的内功有误，无法使用「追魂绝技」。\n");

       message_vision(HBBLU+HIW "\n$N忽然变得面目狰狞，大喝一声，追魂！手中"+weapon->name()+HBBLU+HIW"忽然间一阵舞动，幻起片片光芒！\n"NOR, me,target);  
	   if (me->query_skill_mapped("force")=="huagong-dafa")
	   {
		   message_vision(HBBLU+HIW "\n$N将自身的化功大法鼓荡，隐隐间有一层白雾向$n笼罩过去！\n"NOR, me,target);    
	   }	                

  
       me->set_temp("zhg/zhuihun",1);
         
       skill = me->query_skill("zhuihun-gou", 1);
    
      
       me->add_temp("apply/hook",   skill/5);
       me->add_temp("apply/attack",  skill/3);

       me->add_temp("apply/damage",  skill/5);
       
       
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       
	   me->add_temp("apply/hook",   -skill/5);
       me->add_temp("apply/attack",  -skill/3);

       me->add_temp("apply/damage",  -skill/5);
       me->delete_temp("zhg/zhuihun");
	   me->add("neili", -(me->query_skill("force",1)));
       me->add("jingli", - 100);
	   me->add_busy(2+random(1));
       me->start_perform(5, "追魂绝技");
       return 1;
}

string perform_name(){ return HBBLU+HIW"追魂绝技"NOR; }

int help(object me)
{
        write(HIB"\n追魂钩法之「追魂绝技」："NOR"\n");
        write(@HELP
	追魂钩法是星宿派的不传之秘，有追魂绝技之称
	若配合星宿派独门武功化功大法，则该武功的阴
	险、毒辣特点就发挥玲离尽致。
	追魂绝技是连击术，将浑身功力聚集，然后瞬间
	出招，招招狠毒夺命。
		
	指令：perform hook.zhuihun
		
要求：
	最大内力要求 15000 以上；      
	当前内力要求 1000 以上；
	当前精力要求 700 以上；
	化功大法等级 500 以上；
	追魂钩法等级 500 以上；
	基本钩法等级 500 以上；
	激发钩法和招架为追魂钩法；
	激发内功为化功大法；
	手持钩类兵器。
	            
                
HELP
        );
        return 1;
}
