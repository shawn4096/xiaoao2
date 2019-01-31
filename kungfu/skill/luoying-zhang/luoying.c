// luoying.c 落英剑

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      int lvl;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl =  (int)me->query_skill("luoying-zhang", 1);
      if( !target ) target = offensive_target(me);
    
      if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("落英剑只能对战斗中的对手使用。\n");

      if (!weapon || weapon->query("skill_type") != "sword")
          return notify_fail("你手里没有剑，无法使用落英剑！\n");             

      if (me->query_skill_mapped("sword") != "luoying-zhang"
       || me->query_skill_mapped("parry") != "luoying-zhang")
          return notify_fail("你需要激发剑法为落英剑，无法使用落英剑！\n");             
      if( (int)me->query_skill("sword",1) < 160 )
          return notify_fail("你的基本剑法等级不够，不能使用落英剑！\n");  
      if( (int)me->query_skill("strike",1) < 160 )
          return notify_fail("你的基本掌法等级不够，不能使用落英剑！\n");  

      if( (int)me->query_skill("luoying-zhang", 1) < 160 )
           return notify_fail("你的落英掌法等级不够，不能使用落英剑！\n");
      
      if( (int)me->query_skill("bihai-chaosheng", 1) < 160 )
      
		  return notify_fail("你的内功等级不够，不能使用落英剑！\n");
      if( (int)me->query("max_neili") < 1500 )
          return notify_fail("你的内力太弱，不能使用落英剑！\n");
      
      if( (int)me->query("neili") < 500 )
          return notify_fail("你的内力太少了，无法使用出落英剑！\n");   
      
	  if (me->query_skill_prepared("strike") != "luoying-zhang"
          || me->query_skill_mapped("strike") != "luoying-zhang")
		  return notify_fail("你现在无法使用落英剑进行攻击。\n");             

      message_vision(YEL"\n$N手中剑忽然化作落英冰纷，剑中夹掌，掌中藏剑，向$n奋力击出二剑一掌「"HIG"落英剑"YEL"」！\n"NOR, me,target);
      me->add("neili", -100-random(100)); 
      me->add("jingli", -100);      
      me->add_temp("apply/strength", lvl /20 );
      me->add_temp("apply/sword", lvl/5);
      me->add_temp("apply/damage", lvl /5 );
      me->add_temp("apply/attack", lvl /5);
    
	  me->set_temp("lyz/luoying",lvl);

	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(1)?3:1);
     
	 if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
        
		weapon->unequip(); 
        me->add_temp("apply/strike", lvl/4);
     if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);          
		 me->add_temp("apply/strike", -lvl/4);
         weapon->wield();
     
	 if (lvl>300 && objectp(target) && me->is_fighting(target))
	{
         message_vision(HIC"\n$N将手中剑顺势挥舞，施展出落英神剑的精髓剑招「"HIM"缤纷纷呈"HIC"」一招递出，绚烂无比！\n"NOR, me,target);

		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);          
	}
		 me->add_temp("apply/strength", -lvl /20 );
		 me->add_temp("apply/damage", -lvl /5);        
         me->add_temp("apply/sword", -lvl/5 );
		 me->add_temp("apply/attack", -lvl /5);
    
	me->delete_temp("lyz/luoying");
	
	me->start_busy(1+random(2));

    me->start_perform(4, "「落英剑」");
	
return 1;
}

string perform_name() {return HIM"落"HIC"英剑"NOR;}

int help(object me)
{
    write(WHT"\n落英掌之「"HIC"落英剑"WHT"」："NOR"\n");
    write(@HELP
	落英掌本来源自桃花岛的落英神剑掌绝技，乃是东邪
	黄药师观悟桃花落英并纷而得，只不过后来修习过程
	逐渐以剑化掌而成落英掌，落英绝技采自桃花落英并
	纷之意，快捷攻击对方两剑一掌。300级后落英剑小飞

	指令： perform sword.luoying

要求：、
	碧海潮生要求 160 级以上 
	基本剑法要求 160 级以上
	基本掌法要求 160 级以上
	落英掌法要求 160 级以上
	最大内力要求 1500 以上
	当前内力要求 500  以上
	激发剑法为落英神剑掌，
	激发掌法为落英神剑掌
	激发招架为落英神剑掌或弹指神通。
	备掌法为落英神剑掌
	手持剑类武器
HELP
        );
	return 1;
}


