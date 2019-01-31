// jianzhang.c 剑掌五连环

#include <ansi.h>
  string perform_name() {return HIC"剑掌五连环"NOR;}

inherit F_SSERVER;

int perform(object me, object target)
{
      int lvl;
	  int a;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl = ( (int)me->query_skill("huashan-jianfa", 1) + (int)me->query_skill("hunyuan-zhang", 1) )/2;
      if( !target ) target = offensive_target(me);
     
      if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("剑掌五连环只能对战斗中的对手使用。\n");

     /* if( (string)me->query("gender") != "男性" )
      return notify_fail("只有男弟子才能用出剑掌五连环。\n");	*/

      if (!weapon || weapon->query("skill_type") != "sword"
       || me->query_skill_mapped("sword") != "huashan-jianfa"
       || me->query_skill_mapped("parry") != "huashan-jianfa")
          return notify_fail("你手里没有剑，无法使用剑掌五连环！\n");             
      if( (int)me->query_skill("sword",1) < 200 )
          return notify_fail("你的基本剑法等级不够，不能使用剑掌五连环！\n");  
      if( me->query_temp("hs/jianzhang"))
          return notify_fail("你正在使用剑掌五连环，不能连续使用！\n");  
      if( (int)me->query_skill("hunyuan-zhang", 1) < 200 )
           return notify_fail("你的混元掌法等级不够，不能使用剑掌五连环！\n");
      
      if( (int)me->query_skill("zixia-gong", 1) < 200 )
      
		  if( (int)me->query_skill("huashan-qigong", 1) < 200 )
      
		  return notify_fail("你的内功等级不够，不能使用剑掌五连环！\n");
      if( (int)me->query("max_neili") < 1500 )
          return notify_fail("你的内力太弱，不能使用剑掌五连环！\n");
      
      if( (int)me->query("neili") < 500 )
          return notify_fail("你的内力太少了，无法使用出剑掌五连环！\n");   
      if(me->query_temp("hs/jianzhang") )
          return notify_fail("你正在使用剑掌五连环！\n");                                                                   
      if (me->query_skill_prepared("strike") != "hunyuan-zhang"
          || me->query_skill_mapped("strike") != "hunyuan-zhang")
      return notify_fail("你现在无法使用剑掌五连环进行攻击。\n");             

      message_vision(HIG"\n$N突然招式一变，剑中夹掌，掌中藏剑，向$n奋力击出三剑两掌,正是华山气宗绝学「"HIR"剑掌五连环"HIG"」！\n"NOR, me,target);
      me->add("neili", -300-random(100)); 
      me->add("jingli", -100);      
      me->add_temp("apply/strength", lvl /20 );
      me->add_temp("apply/sword", lvl/6);
      me->add_temp("apply/damage", lvl /6 );
      me->add_temp("apply/attack", lvl /5);
      me->set_temp("hs/jianzhang",1);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(1)?3:1);
	 if (me->query("quest/huashan")=="气宗")
     {
        message_vision(MAG"\n$N暗运内劲，将辛苦修得的劲气附加在手臂之上，将这招的威力彻底发挥出来！\n"NOR, me,target);
		me->add_temp("apply/strength", lvl /20 );
		me->add_temp("apply/sword", lvl/10);
        me->add_temp("apply/damage", lvl /10 );
        me->add_temp("apply/attack", lvl /6);
		target->start_busy(2+random(2));
      }
     if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(1)?3:1);  
     if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
        weapon->unequip(); 
        me->add_temp("apply/strike", lvl/6);
     if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(1)?3:1); 
     if (me->is_fighting(target)) 
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(1)?3:1);  
         me->add_temp("apply/strike", -lvl/6);
         me->add_temp("apply/strength", -lvl /20 );
		 me->add_temp("apply/damage", -lvl /6);        
         me->add_temp("apply/sword", -lvl/6 );
		 me->add_temp("apply/attack", -lvl /5);
        
         weapon->wield();
      if (me->query("quest/huashan")=="气宗")
        {
       	me->add_temp("apply/strength", -lvl /20 );
		me->add_temp("apply/sword", -lvl/10);
        me->add_temp("apply/damage", -lvl /10 );
        me->add_temp("apply/attack", -lvl /6);
	    }
	  	 me->delete_temp("hs/jianzhang");
		 me->start_busy(1+random(2));
         me->start_perform(5, "「剑掌五连环」");
		 
return 1;
}


int help(object me)
{
    write(WHT"\n华山剑法「"HIC"剑掌五连环"WHT"」："NOR"\n");
    write(@HELP
	华山气宗绝学，将华山气功凝聚，在短时间内
	连续出三剑两掌，威力甚猛。若配合紫霞功威
	力更甚。

	指令： perform sword.jianzhang

要求：、
	紫霞神功/华山气功 200 级以上 
	华山剑法要求 200 级以上
	混元掌法要求 200 级以上
	最大内力要求 1500 以上
	当前内力要求 500  以上
	激发剑法华山剑法，
	激发招架华山剑法。
	激发掌法混元掌
	手持剑类武器
HELP
);
 return 1;
}


