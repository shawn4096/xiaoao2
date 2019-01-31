// luanpifeng.c 乱披风 
// by snowman@SJ 30/09/1999
// by sohu@xojh 2013
// 移植到杖法，星宿钩子取消
#include <ansi.h>

inherit F_SSERVER;
int remove_effect(object me,int conut);

int perform(object me, object target)
{
       object weapon;
       int skill;
		weapon = me->query_temp("weapon");  
       if( !target ) target = offensive_target(me);
       
       if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
           return notify_fail("「乱披风」只能在战斗中对对手使用。\n");
       if(!me->query("quest/xx/tsz/luanpifeng/pass"))
           return notify_fail("你虽然听说过「乱披风绝技」，但从并没有学会。\n");
       
	   if ( (int)me->query_skill("huagong-dafa", 1) < 350 )
           return notify_fail("你的内功等级不够，不能使用「乱披风」。\n");
    
       if (me->query_skill("tianshan-zhang", 1) < 350 )
           return notify_fail("你的天山杖法不够娴熟，不能真正发挥「乱披风」。\n");
       if (me->query_skill_mapped("dodge")!="zhaixingshu" )
           return notify_fail("你的激发身法不是摘星术，不能真正发挥「乱披风」。\n");

       if (!weapon 
        || weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "tianshan-zhang"
		|| me->query_skill_mapped("parry") != "tianshan-zhang")
           return notify_fail("你的激发武功不对，现在无法使用「乱披风」来提高攻击力。\n");
    
       if ( (int)me->query("max_neili") < 5000 )
           return notify_fail("你的内力修为不够，不能使用「乱披风」。\n");

       if ( (int)me->query("max_jingli") < 1000 )
           return notify_fail("你的精力修为不够，不能使用「乱披风」。\n");

       if ( (int)me->query("neili") < 700 )
           return notify_fail("你现在内力太弱，不能使用「乱披风」。\n");
    
       if ( (int)me->query_temp("tsz/lpf") ) 
           return notify_fail("你正在使用天山杖法之「乱披风」。\n");
    
       if (me->query_skill_mapped("force") != "huagong-dafa")
           return notify_fail("你的内功有误，无法使用「乱披风」。\n");

       message_vision(HBBLU "\n$N将发结解开，披头散发，脸色惨白，突然狂嚎一声，手中的"+weapon->name()+HBBLU"胡乱挥舞着，全然不按章法！\n"NOR, me);                 
       message_vision(HBGRN+HIW "\n$N虽然杖法散乱，但脚下"HIR"「摘星术」"HIW"运转间落脚处却显得错落有致！全是从不可能的角度挥出!\n"NOR, me);                 

         
       skill = me->query_skill("tianshan-zhang", 1);
           

       me->add_temp("apply/parry",  -skill/2);
       me->add_temp("apply/dodge",  -skill/2);
       me->add_temp("apply/attack",  skill/3);

       me->add_temp("apply/damage",  skill/5);

       me->add_temp("apply/staff",  skill/2);

		   
       me->set_temp("tsz/lpf",skill);

	   me->add("neili", -300);
       me->add("jingli", - 200);
       if (me->query_skill("tianshan-zhang",1)<350)
			me->start_perform(1, "乱披风");
       
	   call_out("remove_effect", 1, me, (int)skill/10);
       return 1;
}

int remove_effect(object me,int count)
{
        int skill;
		object weapon;
		if(!me) return 0;

        if(!me->query_temp("tsz/lpf")) return 0;
        
		skill=me->query_temp("tsz/lpf");
		weapon=me->query_temp("weapon");
		if( !me->is_fighting()
         || me->query_skill_mapped("staff") != "tianshan-zhang"
		 ||!weapon
		 || weapon->query("skill_type")!="staff"
         || count < 0)
		{
           me->add_temp("apply/staff",  -skill/2);
		   me->add_temp("apply/attack", -skill/3);
		   me->add_temp("apply/damage", -skill/5);
 
		   me->add_temp("apply/parry", skill/2); 
		   
me->add_temp("apply/dodge", skill/2);
           me->delete_temp("tsz/lpf");
           if(living(me))
             message_vision(HBGRN+HIW "\n$N大口大口地喘气，招数也渐渐恢复正常，看来是消耗了不少的气力！\n\n" NOR, me);
           return 1;
         }
         
		 call_out("remove_effect", 1 ,me , count -1);
}
string perform_name(){ return HIW"乱披风绝技"NOR; }

int help(object me)
{
        write(HIB"\n天山杖法之「乱披风」："NOR"\n");
        write(@HELP
	天山杖法是星宿派的重要武技，有追魂夺命之称
	若配合星宿派独门武功化功大法，则该武功的阴
	险、毒辣特点就发挥玲离尽致。
	乱披风也是不要命的打法，欲伤敌先伤己，在牺
	牲自己防御的前提条件下换取命中和伤害。瞬间
	出招，招招狠毒夺命。
		
	指令：perform staff.luanpifeng
		
要求：
	最大内力要求 5000 以上；      
	当前内力要求 1000 以上；
	当前精力要求 700 以上；
	化功大法等级 350 以上；
	天山杖法等级 350 以上；
	基本杖法等级 350 以上；
	激发杖法和招架为天山杖法；
	激发内功为化功大法；
	手持杖类兵器。
	            
                
HELP
        );
        return 1;
}
