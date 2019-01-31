// luanhuanjue.c  乱环诀

#include <ansi.h>
#include <combat.h>
inherit SKILL;
inherit F_SSERVER;
void check_fight(object me, object target,int j);
private void remove_effect(object me); 
int perform(object me, object target)
{
      string msg;
	  int dm,i,j;	  	
      object weapon = me->query_temp("weapon");  
	  i=me->query_skill("xuanxu-daofa",1);
	  j=2;
      //int j = (int)me->query_skill("xuanxu-daofa", 1)/5;
   
	  if( !target ) target = offensive_target(me);
      if (!objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "blade")                
        return notify_fail("玄虚刀法需要手中拿刀方可施展。\n");
      if( me->is_busy() )
        return notify_fail("你正忙着呢。\n");
      if( !target || !me->is_fighting(target) )
        return notify_fail("乱环诀只能在战斗中对对手使用。\n");
             
      if( (int)me->query_skill("xuanxu-daofa", 1) < 100 )
        return notify_fail("你的玄虚刀法不够娴熟，不能使乱环诀！\n");
      
      if( (int)me->query_skill("force", 1) < 100 )
        return notify_fail("你的基本内功等级不够，不能使用乱环诀！\n");

      if( (int)me->query_skill("blade", 1) < 100 )
        return notify_fail("你的基本刀法等级不够，不能使用乱环诀！\n");  
      
      if( (int)me->query_skill("taoism", 1) < 100 )
        return notify_fail("你对道家心法领悟不够精深，无法使用出乱环诀！\n");
      
      if( (int)me->query("max_neili") < 1500 )
        return notify_fail("你的内力太弱，不能使用乱环诀！\n");
      
      if( (int)me->query("neili") < 500 )
        return notify_fail("你的内力太少了，无法使用出乱环诀！\n");   

      if (!weapon || weapon->query("skill_type") != "blade"
		  || me->query_skill_mapped("parry") != "xuanxu-daofa"
          || me->query_skill_mapped("blade") != "xuanxu-daofa")
        return notify_fail("你没有激发玄虚刀法。\n");
                                                                                 
      if( me->query_temp("blade_lh") )
          return notify_fail("你正在使用玄虚刀法的乱环诀！\n");
   
	  if (i<350)
       {
			dm=i+me->query_skill("blade",1);
            dm/=3;
			j=4;
	   } 
	  else dm=i/5;
      msg = HIY"$N使出玄虚刀法中的绝技"+HIC"[乱环刀决]"+HIY"，刀出成环，一圈一圈的划出，绞的$n眼前一片刀影光环。\n"NOR;
	 
      me->add("neili", -100);
      me->set_temp("blade_lh", dm);
  	  me->add_temp("apply/attack",dm);
	  me->add_temp("apply/damage",dm/4);
      if (random(me->query("combat_exp"))>target->query("combat_exp")/3)
      {

		   msg += HIR"$N趁$n疏忽之际幻起一片刀影，看似缓慢，实则迅捷无比。攻向$n的前胸。\n"NOR;           
		   if (!userp(target))
		      target->start_busy(1+random(2));
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
       }
	  message_vision(msg, me, target);
	  if (objectp(target)&&me->is_fighting(target)&&me->query_skill_mapped("strike")=="zhenshan-mianzhang"&&me->query_skill("xuanxu-daofa",1)>150)
	  {
		 switch (random(4))
	      {
                     case 0:                             
                              message_vision(HIG"$N闪电般地劈出一刀,幻起一片刀影，迅捷无比。\n"NOR,me);
					          if (me->is_fighting(target))
			                   {
                                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
                                target->add_busy(1+random(2));
								}
                               break;        
                     case 1:
                                            
                              message_vision(HIC"$N闪电般地劈出两刀。一刀为阴，一刀呈阳。双刀瞬间齐至。\n"NOR,me);
							  if (me->query_skill_mapped("force")=="yinyun-ziqi")
							    message_vision(HIB"$N运起内功，一股柔韧力道使出，刀势形成的刀气刮的$n脸上疼痛不已。\n"NOR,me,target);
                            
			                  if (me->is_fighting(target))
			                   {
							     //target->receive_damage("qi",dm*2);
							     //target->receive_wound("qi",dm);
                                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
                                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);  
								 //j=j-1;
							   }
                              break;                              
                      case 2:                                                 
                              message_vision(HIB"$N闪电般地劈出三刀。错落有致，刀法严谨，滴水不漏。\n"NOR,me);
							   if (me->is_fighting(target))
			                   {
							     me->add_temp("apply/parry",dm/3);
                                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
                                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
                                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
							     me->add_temp("apply/parry",-dm/3);
								 //j=j-1;
							   }
                             
                              break;                              
                      case 3:                                      
                              message_vision(HIR"$N闪电般地劈出四刀。纵横捭阖，刀气弥漫，显然将深厚的内功融合到刀法之中。\n"NOR,me);
							  if (me->is_fighting(target))
			                  {
							   me->add_temp("apply/blade",dm/4);
                               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
                               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
                               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
                               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
							   me->add_temp("apply/blade",-dm/4);
							  // j=j-1;
							  }
                              break;                                 
                     }
	  }
	  me->add_temp("apply/attack",-dm);
      me->add_temp("apply/damage",-dm/4); 
      message_vision(HIY"你觉得精力略有衰竭，手中刀光渐缓。\n"NOR,me);
	  me->delete_temp("blade_lh");
      me->start_perform(4,"玄虚乱环");		
     
      return 1;
}


string perform_name(){ return HIY"乱环刀诀"NOR; }
int help(object me)
{
         write(HIB"\n玄虚刀法之"+HIY"「乱环刀诀」"NOR"\n");
        write(@HELP
	玄虚刀法乃是武当入门弟子的武技，该刀法乃是开山祖师
	张三丰早期闯荡江湖时所使用的武功。总共十七招，后来
	俞岱岩凭借此武功追杀盗贼，在第八招上那汪洋巨盗给斩
	杀。以此享誉江湖。
	玄虚刀法乱环刀诀，乃是融合张三丰异常丰富的战斗经验
	所汇集，具有很强的实战效果。
	
	指令：perform blade.luanhuan

要求：
	氤氲紫气：100
	玄虚刀法：100
	基本刀法：100
	道学心法：100
	最大内力：1500
	当前内力：500
	道学心法：100
	激发刀法玄虚刀法；
	激发招架玄虚刀法；
	内功不限；
	备震山绵掌。
	手持刀类武器；
HELP
        );
        return 1;
}
