//kuangdao.c 田伯光的狂风快刀作为大招 
//cre by sohu@xojh
#include <ansi.h>
inherit F_SSERVER;
    
   string perform_name(){ return HIW"狂风快刀"NOR; }
    
   int perform(object me,object target)
 {
       object weapon;
       int i;
      
       if( !target ) target = offensive_target(me);
       
       if( !objectp (target) || !me->is_fighting(target) || !living(target)
          || environment(target)!=environment(me))
                   return notify_fail("狂风快刀只能对战斗中的对手使用。\n");  
       if( !me->query("quest/hmy/tmd/kuaidao/pass")) 
                   return notify_fail("你只是听说过狂风快刀绝技，但还未练成，不能使用狂风快刀！\n");
       if( (int)me->query_skill("tianmo-dao", 1) < 450 ) 
                   return notify_fail("你的狂风快刀还未练成，不能使用狂风快刀！\n");

                 
       if((int)me->query_skill("blade", 1) < 450 )
                   return notify_fail("你的基本刀法不够娴熟，不能在使用狂风快刀。\n");
	    if((int)me->query_skill("force", 1) < 450 )
                   return notify_fail("你的基本内功不够娴熟，不能在使用狂风快刀。\n");
      
	   if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "blade"
           || me->query_skill_mapped("blade") != "tianmo-dao"
           || me->query_skill_mapped("parry") != "tianmo-dao")
                   return notify_fail("你现在使得了狂风快刀么？\n");
                   
       if((int)me->query("max_neili") < 9000 )
                  return notify_fail("你的最大内力修为不够，不能使用狂风快刀！\n");
       if((int)me->query("neili") < 2000 )
                 return notify_fail("你现在真气不足，不能使用狂风快刀！\n");
  
       message_vision(HIW"\n$N身法突地加快，使出快刀，所谓「天下武功，无坚不摧，唯快不破」\n",me);
       message_vision(HIM"$N身形变化，瞬间连出数刀，电闪雷鸣，这正是天魔刀法的绝招「狂风快刀」!\n",me);
		i = (int)me->query_skill("tianmo-dao",1)/4;
		target->receive_damage("qi",i*(2+random(4)),me);
        me->set_temp("tmd/kf1",1);
		
		//me->start_perform(2,"「狂风快刀」");
      
		me->add("neili", -300);
		me->add_temp("apply/attack",  i);
        me->add_temp("apply/damage",  i/4);
        me->add_temp("apply/blade",  i/4);
      
	  if (me->is_fighting(target))
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
     
     // if (me->is_fighting(target))
         //COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
      
      if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
	  if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);

	  if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
     me->delete_temp("tmd/kf1");
           
	  if(me->query("quest/hmy/tmd/kuaidao/pass")&&objectp(target))
	 {
			message_vision(HBYEL+RED"$N已然将狂风快刀的绝技融会贯通,猛吸一口真气，劲力流转，手中的刀法顿时一变。\n"NOR,me);
			message_vision(HBYEL+RED"招式已经电闪雷鸣，暇不及发，宛如狂风暴雨一般，刀光将$n笼罩过来。\n"NOR,me,target);


			if (userp(target))
				target->add_busy(2);

			else target->add_busy(4);
			me->add_temp("apply/attack",  i/4);
			me->add_temp("apply/damage",  i/5);
			me->set_temp("tmd/kf2",1);
			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
            if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);                 
            if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
/*
			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
*/
			//target->receive_damage("qi",i*2,me);

			me->delete_temp("tmd/kf2");

			me->add_temp("apply/attack",  -i/4);
			me->add_temp("apply/damage",  -i/5);
		}
		
		me->add_temp("apply/attack",  -i);
        me->add_temp("apply/damage",  -i/4);
	    me->add_temp("apply/blade",  -i/4);

			me->delete_temp("tmd/kfdf");

			me->start_perform(6,"「狂风快刀」");

			me->start_busy(2+random(2));

			return 1;
 }

int help(object me)
{
        write(HIB"\n天魔刀之「狂风快刀」："NOR"\n\n");
        write(@HELP
	狂风快刀源自江湖奇人田伯光的绝学，想当初在回雁楼与
	令狐冲一战，使得狂风快刀名震江湖。寻常快刀威力并不
	彰显，若机缘巧合获得田伯光的真传，则该快刀的威力将
	彻底释放。
	
指令:perform blade.kuangdao

要求：
	当前内力需求 9000 以上；
	最大内力需求 3000 以上；
	天魔刀法等级 450 以上；
	基本刀法等级 450 以上；
	基本内功等级 450 以上；
	激发刀法为天魔刀；
	激发招架为天魔刀；
	激发内功不限；
	且手持刀类兵器。
HELP
        );
        return 1;
}
