// chuo.c 戳字诀
// by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
void remove_effect(object me,int count);

int perform(object me, object target)
{                                  
      int skill,damage;
      object weapon;
      
	  if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target))
                return notify_fail("「戳字诀」只能在战斗中对对手使用。\n");
//笔法或刀法
      if (!objectp(weapon = me->query_temp("weapon")) 
        || (weapon->query("skill_type") != "brush"&&weapon->query("skill_type") != "blade"))
                return notify_fail("你的武器不对，现在无法使用「戳字诀」。\n");
      
	  if (me->query_skill_mapped("blade") != "qingliang-shan"
			||me->query_skill_mapped("parry") != "qingliang-shan"
			|| me->query_skill_mapped("brush") != "qingliang-shan")
                return notify_fail("你激发不对，现在无法使用「戳字诀」。\n");

      if( (int)me->query_skill("qingliang-shan",1) < 150 )
                return notify_fail("你的清凉扇不够娴熟，不会使用「戳字诀」！\n");      

      if( (int)me->query_skill("force",1) < 250 )
                return notify_fail("你的基本内功等级不够，不能使用「戳字诀」！\n");  
      if( (int)me->query_skill("blade",1) < 250 )
                return notify_fail("你的基本刀法等级不够，不能使用「戳字诀」！\n");  
      if( (int)me->query_skill("brush",1) < 250 )
                return notify_fail("你的基本笔法等级不够，不能使用「戳字诀」！\n");  
      
      
      if( (int)me->query_dex() < 30 )
                return notify_fail("你的身法不够强，不能使用「戳字诀」！\n");
      if( (int)me->query("neili") < 1500 )
		      return notify_fail("你的内力太少了，无法使用出「戳字诀」！\n");
      if( (int)me->query("max_neili") < 2500 )
                return notify_fail("你的内力太弱，不能使用「戳字诀」！\n");
      if( target->query_temp("qls/chuo"))
                return notify_fail("对方已经中了「戳字诀」无需费劲，赶紧动手吧！\n");
      if(target->is_busy())
                return notify_fail("对方已经手忙脚乱，无需费劲，赶紧动手吧！\n");
           
      skill = (int)me->query_skill("qingliang-shan", 1);
      
	  damage = (int)me->query_skill("qingliang-shan", 1)+(int)me->query_skill("blade", 1)+(int)me->query_skill("brush", 1);
        
	  damage=damage*3+random(damage/3);   
      	
      message_vision(HIY"$N右手"NOR+weapon->query("name")+HIY"“刷”的一声将扇面合在一起，化扇为笔，施展出"+HIW"「戳字诀」"+HIY"，贴$n身而动，向$n戳了过去。\n" NOR, me, target);

	//  me->set_temp("qls/chuo", 1);
	  if (random(me->query_dex())>target->query_dex()/3
		  ||random(me->query_skill("qingliang-shan",1))>target->query_skill("parry",1)/2
		  ||random(me->query_int())>target->query_int()/2)
	  {
	     message_vision(HIR"$N一下戳中$n的软肋，$n顿时觉得自己半身酸麻，气血不通！\n"NOR, me, target);
		 target->receive_damge("qi",damage,me);
		 target->receive_wound("qi",damage/4,me);
		 target->add_busy(2);
		 target->apply_condition("no_jiali",1);
		 target->apply_condition("no_exert",2);
		 target->set_temp("qls/chuo",1);
		 
	  }else	{
		me->add_busy(1);	
		message_vision(HIY"$n纵声长啸，躲开了$N的这次攻击！\n"NOR,me,target);
	  }
     me->add("neili",-250);
	 me->add("jingli",-150);
     return 1;
}

string perform_name(){ return RED"戳字诀"NOR; }

int help(object me)
{
	write(HIC"\n清凉扇之「戳字诀」："NOR"\n");
	write(@HELP
	清凉扇是昆仑派灵清居士外门绝技，以扇为兵器既可以
	化作短棍，又可以化作刀法攻击，俗话说一寸短，一寸
	险，靠近攻击威力极为犀利，对于不善用力的女性玩家
	这清凉扇也是门派的重要外家功夫。
	戳字诀是将手中扇子类武器合在一处，状如短棍，贴身
	之际以笔法姿势戳中对方软肋，令对方丧失反抗。
	
	指令：perform brush.chuo

要求：
	最大内力需求 2500 以上；
	当前内力需求 1500 以上；
	清凉扇的等级 250 以上；
	基本内功等级 250 以上；
	基本刀法等级 250 以上；
	基本笔法等级 250 以上；
	后天身法大于 50  以上；
	激发刀法为清凉扇
	激发笔法为清凉扇
	激发招架为清凉扇
	内功不限；
	手持刀或笔类武器
HELP
	);
	return 1;
}
