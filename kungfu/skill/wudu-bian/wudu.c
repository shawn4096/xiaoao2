 // wudu 五毒鞭

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	  int lv;
      object weapon;

      weapon = me->query_temp("weapon");
	  lv = me->query_skill("wudu-bian",1);
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
		  return notify_fail("「五毒鞭」只能在战斗中对对手使用。\n");

      if (!weapon || weapon->query("skill_type") != "whip"
       || me->query_skill_mapped("whip") != "wudu-bian")
		  return notify_fail("你手里没有鞭，无法使用「五毒鞭」！\n");             

      if( (int)me->query_skill("wudu-bian",1) < 220 )
	      return notify_fail("你的灵蛇鞭法不够娴熟，不能使用「五毒鞭」！\n");
      if( (int)me->query_skill("poison",1) < 100 )
	      return notify_fail("你的毒计不够娴熟，不能使用「五毒鞭」！\n");
      if( (int)me->query_skill("whip", 1) < 220 )
		  return notify_fail("你的基本鞭法等级不够，不能使用「五毒鞭」！\n");
      if( (int)me->query_skill("dodge", 1) < 220 )
		  return notify_fail("你的基本轻功等级不够，不能使用「五毒鞭」！\n");
	  if (me->query("gender")=="无性")
	 	  return notify_fail("五毒鞭需要阴阳二气，你无性不能使用「五毒鞭」！\n");

      if( (int)me->query("neili") < 300 )
		  return notify_fail("你的内力太少，不能使用「五毒鞭」！\n");
	  if( (int)me->query("jingli") < 500 )
		  return notify_fail("你的精力太少，不能使用「五毒鞭」！\n");
	  if (me->query_skill_mapped("whip")!="wudu-bian"
		 ||me->query_skill_mapped("parry")!="wudu-bian")
		  return notify_fail("你激发的鞭法不对，不能使用「五毒鞭」！\n");
	 
	  message_vision(HIB"\n$N将手中的"+weapon->query("name")+HIB+"连续抖动五下，每一招都极为怪异，依次循着诡异的途径向$n袭去！\n"NOR, me,target);
	  message_vision(HIB"\n$N运气成圆，将五毒教「五毒鞭」绝技施展出来！\n"NOR, me,target);

      me->add("neili", -200); 
      me->add("jingli", -50);

	  if (!userp(target)&&me->query("gender")=="女性") 
	  {
		  lv += lv+me->query_dex();
		 // lv=lv+
	  }

	  if (me->query("gender")=="女性"&& me->query_skill("poison",1)>100)
	  {
		  lv=lv+me->query_skill("poison",1);
	  }
	  //男人威力不足女人一半
	  if (me->query("gender")=="男性") 
		  lv=lv/3;

      me->set_temp("wdb/wudu",5);
      me->add_temp("apply/attack", lv/4);
	  me->add_temp("apply/whip", lv/5);
	  me->add_temp("apply/damage", lv/5);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	  //出手法天魔手
	  if (me->is_fighting(target)
		  &&me->query_skill_mapped("hand")=="tianmo-shou"
		  &&me->query_skill_prepared("hand")=="tianmo-shou")
      {
			message_vision(HIG"$N将手中的"+weapon->query("name")+HIG"收回腰间，顺手一击「天魔手」！点、戳、捏向对方周身大穴。\n"NOR,me,target);
			me->add_temp("apply/hand", lv/5);
			me->add_temp("apply/damage", lv/8);
			weapon->unequip();
			target->add_busy(1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
			me->add_temp("apply/damage", -lv/8);
			me->add_temp("apply/hand", -lv/5);
			weapon->wield();
      }
	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);  

      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  

	  me->add_temp("apply/attack", -lv/4);
      me->add_temp("apply/whip", -lv/5);
	  me->add_temp("apply/damage", -lv/5);
	  me->delete_temp("wdb/wudu");	
      me->start_perform(3,"「五毒鞭」");
      return 1;
}
string perform_name(){ return HIB"五毒鞭"NOR; }

int help(object me)
{
        write(HIC"\n五毒鞭法"+HIB"「五毒鞭」"NOR"\n");
        write(@HELP
	五毒鞭法乃是五毒教根据教中五种神物的研究而创立的一门
	武学，讲究灵动犀利、阴险毒辣，且带毒，舞动之际，宛如
	蛟龙出海，万毒喷发，厉害非常。若配合天魔手，则会产生
	意外的招式。
	注意：伤害与毒计和身法有关联，女性有优势
	
	指令：perform whip.wudu

要求：
	当前内力要求 500 以上；
	当前精力要求 300 以上；
	基本鞭法要求 220 以上；
	五毒鞭法要求 220 以上；
	基本身法等级 220 以上；
	毒计需求等级 100 以上；
	激发鞭法为五毒鞭法。
	激发招架为五毒鞭法。
	手持鞭类武器；

HELP
        );
        return 1;
}
