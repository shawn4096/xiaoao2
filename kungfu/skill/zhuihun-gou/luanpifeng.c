// luanpifeng.c 乱披风 
// by snowman@SJ 30/09/1999
// by sohu@xojh 2013

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
           return notify_fail("「乱披风」只能在战斗中对对手使用。\n");
       if(me->query("xx/zhg/pass"))
           return notify_fail("你虽然听说过「追魂钩法」，但从并没有学会。\n");
       if ( (int)me->query_skill("huagong-dafa", 1) < 350 )
           return notify_fail("你的内功等级不够，不能使用「乱披风」。\n");
    
       if ( (int)me->query_skill("zhuihun-gou", 1) < 350 )
           return notify_fail("你的天山追魂钩不够娴熟，不能真正发挥「乱披风」。\n");
    
       if (!weapon 
        || weapon->query("skill_type") != "hook"
        || me->query_skill_mapped("hook") != "zhuihun-gou")
           return notify_fail("你现在无法使用「乱披风」来提高攻击力。\n");
    
       if ( (int)me->query("max_neili") < 2500 )
           return notify_fail("你的内力修为不够，不能使用「乱披风」。\n");

       if ( (int)me->query("max_jingli") < 1000 )
           return notify_fail("你的精力修为不够，不能使用「乱披风」。\n");

       if ( (int)me->query("neili") < 700 )
           return notify_fail("你现在内力太弱，不能使用「乱披风」。\n");
    
       if ( (int)me->query_temp("zhuihun/lpf") ) 
           return notify_fail("你正在使用天山追魂钩之「乱披风」。\n");
    
       if (me->query_skill_mapped("force") != "huagong-dafa")
           return notify_fail("你的内功有误，无法使用「乱披风」。\n");

       message_vision(HBBLU "\n$N将发结解开，披头散发，脸色惨白，突然狂嚎一声，手中的"+weapon->name()+HBBLU"胡乱挥舞着，全然不按章法，间杂着抽髓掌狂乱使出！\n"NOR, me);                 
  
       me->set_temp("zhuihun/lpf",1);
         
       skill = me->query_skill("zhuihun-gou", 1);
    
       me->add_temp("apply/parry",  -skill/5);
       me->add_temp("apply/dodge",  -skill/5);
       me->add_temp("apply/attack",  skill/2);

       me->add_temp("apply/damage",  skill/2);
       
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       
       me->add("neili", -(me->query_skill("force")));
       me->add("jingli", - 100);
       me->start_perform(4, "乱披风");
       call_out("remove_effect", 1, me, target, weapon,5);
       return 1;
}

int remove_effect(object me,object target,object weapon,int count)
{
        if(!me) return 0;
        if(!me->query_temp("zhuihun/lpf")) return 0;
        if( !target 
         || !me->is_fighting(target)
         || weapon != me->query_temp("weapon")
         || me->query_skill_mapped("hook") != "zhuihun-gou"
         || count < 0){
           me->add_temp("apply/attack", -me->query_skill("zhuihun-gou", 1)/2);
		   me->add_temp("apply/damage", -me->query_skill("zhuihun-gou", 1)/2);
 
		   me->add_temp("apply/parry", me->query_skill("zhuihun-gou", 1)/5); 
		   
me->add_temp("apply/dodge", me->query_skill("zhuihun-gou", 1)/5);
           me->delete_temp("zhuihun/lpf");
           if(living(me))
             message_vision(HIG "\n$N大口大口地喘气，招数也渐渐恢复正常，看来是消耗了不少的气力！\n\n" NOR, me);
           return 0;
         }
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3); 
         call_out("remove_effect", 1 ,me ,target, weapon, count -1);
}
string perform_name(){ return HIW"乱披风"NOR; }

int help(object me)
{
        write(HIM"\n追魂钩法之「乱披风」："NOR"\n");
        write(@HELP
	追魂钩法是星宿派的不传之秘，有追魂夺命之称
	若配合星宿派独门武功化功大法，则该武功的阴
	险、毒辣特点就发挥玲离尽致。
	乱披风也是不要命的打法，欲伤敌先伤己，在牺
	牲自己防御的前提条件下换取命中和伤害。瞬间
	出招，招招狠毒夺命。
		
	指令：perform hook.luanpifeng
		
要求：
	最大内力要求 2500 以上；      
	当前内力要求 1000 以上；
	当前精力要求 700 以上；
	化功大法等级 350 以上；
	追魂钩法等级 350 以上；
	基本钩法等级 350 以上；
	激发钩法和招架为追魂钩法；
	激发内功为化功大法；
	手持钩类兵器。
	            
                
HELP
        );
        return 1;
}
