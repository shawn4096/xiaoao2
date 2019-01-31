// zhuihun.c 追魂 
//
// by sohu@xojh 2015

#include <ansi.h>

inherit F_SSERVER;
//int remove_effect(object me,object target,object weapon,int conut);

int perform(object me, object target)
{
       object wep2;
       int skill,i,count;
       object *inv;
	   object weapon = me->query_temp("weapon");  

       if( !target ) target = offensive_target(me);
       
       if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
           return notify_fail("「追魂夺命」只能在战斗中对对手使用。\n");
       if(!me->query("quest/xx/tsz/zhuihun/pass"))
           return notify_fail("你虽然听说过「追魂夺命」，但从并没有学会。\n");
       if ( (int)me->query_skill("force", 1) < 500 )
           return notify_fail("你的内功等级不够，不能使用「追魂夺命」。\n");
    
       if ( (int)me->query_skill("tianshan-zhang", 1) < 500 )
           return notify_fail("你的天山追魂钩不够娴熟，不能真正发挥「追魂夺命」。\n");
    
       if (!weapon 
        || weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "tianshan-zhang")
           return notify_fail("你现在无法使用「追魂夺命」来攻击对方。\n");
    
       if ( (int)me->query("max_neili") < 15000 )
           return notify_fail("你的内力修为不够，不能使用「追魂夺命」。\n");

       if ( (int)me->query("max_jingli") < 1000 )
           return notify_fail("你的精力修为不够，不能使用「追魂夺命」。\n");

       if ( (int)me->query("neili") < 700 )
           return notify_fail("你现在内力太弱，不能使用「追魂夺命」。\n");
    
       if ( (int)me->query_temp("tsz/zhuihun") ) 
           return notify_fail("你正在使用天山追魂钩之「追魂夺命」。\n");
    
     //  if (me->query_skill_mapped("force") != "huagong-dafa")
       //    return notify_fail("你的内功有误，无法使用「追魂夺命」。\n");

       message_vision(HBBLU+HIW "\n$N忽然变得面目狰狞，大喝一声，追魂夺命！手中"+weapon->name()+HIW"转动宛如车轮，幻起片片光芒！\n"NOR, me,target);  
	   message_vision(HBBLU+HIW "\n全然不顾个人安危，招招只向$n的要害部分招呼，正是追魂夺命绝技！\n"NOR, me,target);  
       
	   skill = me->query_skill("tianshan-zhang", 1);

	   if (me->query_skill_mapped("force")=="huagong-dafa")
	   {
		   message_vision(HIW "\n$N将自身的化功大法劲气鼓荡，隐隐间有一层"HIB"毒雾"HIW"向$n笼罩过去！\n"NOR, me,target);
		   skill=skill+me->query_skill("huagong-dafa",1)/5;
	   }	                

  
       me->set_temp("tsz/zhuihun",skill);
         
    
      
       me->add_temp("apply/staff",   skill/5);
       me->add_temp("apply/attack",  skill/3);

       me->add_temp("apply/damage",  skill/5);
       
       
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		
		inv = all_inventory(me);
		for(count=0, i=0; i<sizeof(inv); i++) 
		{
         //  if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
           if( inv[i]->query("skill_type") == "hook" ) 
		   {
			   wep2 = inv[i];
			   break;
		   }
		}
	   if (objectp(wep2) && me->query_temp("tsz/lpf"))
       {
		   message_vision(HBWHT+HIB"$N此时施展出来的乱披风绝技已经出神入化，顺手抽出随身所带的"+wep2->query("name")+HBWHT+HIB"以杖法招式劈向$n！\n"NOR,me,target);
		   me->add_temp("apply/attack",skill/4);
		   me->add_temp("apply/damage",skill/4);
		   me->add_temp("apply/staff",skill/4);

		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		   me->add_temp("apply/attack",-skill/4);
		   me->add_temp("apply/damage",-skill/4);
		   me->add_temp("apply/staff",-skill/4);

       }

	   me->add_temp("apply/staff",   -skill/5);
       me->add_temp("apply/attack",  -skill/3);

       me->add_temp("apply/damage",  -skill/5);
       me->delete_temp("tsz/zhuihun");
	   me->add("neili", -(me->query_skill("force",1)));
       me->add("jingli", - 100);
	   me->add_busy(2+random(1));
       me->start_perform(5, "追魂夺命");
       return 1;
}

string perform_name(){ return HBBLU+HIW"追魂夺命"NOR; }

int help(object me)
{
        write(HIB"\n天山杖法之「追魂夺命」："NOR"\n");
        write(@HELP
	天山杖法是星宿派的不传之秘，有追魂夺命之称
	若配合星宿派独门武功化功大法，则该武功的阴
	险、毒辣特点就发挥玲离尽致。
	追魂夺命是连击术，将浑身功力聚集，然后瞬间
	出招，招招狠毒夺命。注意，若施展乱披风绝技
	且身带钩子类武器，会在乱披风状态下会随机施
	展一招较为犀利的招式。
		
	指令：perform staff.zhuihun
		
要求：
	最大内力要求 15000 以上；      
	当前内力要求 1000 以上；
	当前精力要求 700 以上；
	化功大法等级 500 以上；
	天山杖法等级 500 以上；
	基本杖法等级 500 以上；
	激发杖法和招架为天山杖法；
	不限制内功；
	手持杖类兵器。
	            
                
HELP
        );
        return 1;
}
