// lihun.c 离魂斩

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HIG"离"HIY"魂"HIR"斩"NOR; }

int perform(object me, object target)
{
      int lvl;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl = (int)me->query_skill("lietian-fu", 1)+(int)me->query_skill("guiyuan-tunafa", 1)/2;
  
    if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
        return notify_fail("「离魂斩」只能在战斗中对对手使用。\n");

      if (!weapon || weapon->query("skill_type") != "axe"
       || me->query_skill_mapped("axe") != "lietian-fu")
        return notify_fail("你使用的兵刃不正确，无法使用「离魂斩」！\n");             

      if( (int)me->query_skill("lietian-fu",1) < 200 )
        return notify_fail("你的裂天斧法不够娴熟，不能使用「离魂斩」！\n");
      
      if( (int)me->query_skill("axe",1) < 200 )
        return notify_fail("你的基本斧法等级不够，不能使用「离魂斩」！\n");  
     
      if( (int)me->query_skill("guiyuan-tunafa", 1) < 200 )
        return notify_fail("你的归元吐纳法等级不够，不能使用「离魂斩」！\n");
      if( me->query_skill_mapped("force") !="guiyuan-tunafa" ||me->query_skill_mapped("parry")!="lietian-fu")
        return notify_fail("你的内功或招架不符，不能使用「离魂斩」！\n");

      if( (int)me->query("max_neili") < 2500 )
        return notify_fail("你的内力太弱，不能使用「离魂斩」！\n");
      
      if( (int)me->query("neili") < ( me->query_skill("force")+ lvl ))
        return notify_fail("你的内力太少了，无法使用出「离魂斩」！\n");   
                                                                                 
      message_vision(RED"\n$N使出「离魂斩」，每一式中都带着奇异的韵律，似乎时间都被这韵律所凝结，猛然间斧影如闪电似惊虹，如海浪般卷来。\n"NOR, me,target);
      me->add("neili", - 300);
      me->add("jingli", -50);      
      lvl = lvl /5;
      me->add_temp("apply/strength", lvl /2);
	  
me->add_temp("apply/attack", lvl );
	  me->add_temp("apply/damage", lvl  );

	  me->add_temp("apply/axe", lvl );

	  me->set_temp("lihun", 1);
	  if (!userp(target))
	  {
		  me->add_temp("apply/attack", lvl );
	      me->add_temp("apply/damage", lvl );
		  me->set_temp("ltf/npc",1);
	  }
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
      if (present(target,environment(me)) && me->is_fighting(target))
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
      if (present(target,environment(me)) && me->is_fighting(target))
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
      if (present(target,environment(me))
       && me->is_fighting(target)
       && me->query_skill("lietian-fu", 1) > 250)
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      me->add_temp("apply/strength", -lvl /2);

		  me->add_temp("apply/attack", -lvl );

		  me->add_temp("apply/axe", -lvl );

		  me->add_temp("apply/damage", -lvl );
     if (me->query_temp("ltf/npc"))
	  {
		  me->add_temp("apply/attack", -lvl );
	      me->add_temp("apply/damage", -lvl );
		  me->delete_temp("ltf/npc");
	  }
	  
me->delete_temp("lihun");
      me->start_busy(2);
      me->start_perform(4,"「离魂斩」");
      return 1;
}
int help(object me)
{
        write(HIY"\n裂天斧之「离魂斩」："NOR"\n\n");
        write(@HELP 
	裂天斧之绝技「离魂斩」，乃是当初外派的
	一位前辈高人，有感于抗金过程中短兵相接
	后，轻兵器不沾便宜的现状。总结提炼出一
	套近身搏杀的斧法，在战场中发挥了巨大的
	作用。
	
	指令：perform axe.lihun

要求：
	当前内力要求 500 以上；
	最大内力要求 2500 以上；
	当前精力要求 500 以上；
	基本斧法等级 200 以上；
	裂天斧法等级 200 以上；
	激发斧法为裂天斧法；
	激发招架为裂天斧法；
	激发内功为归元吐纳法。
	手持斧法类武器
HELP
        );
        return 1;
}