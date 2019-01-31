// qingliang.c
// by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{                                  
      int i, lvl, addlvl,dk;
      object weapon;
      
	  if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target))
                return notify_fail("「清凉快打」只能在战斗中对对手使用。\n");
//笔法或刀法
      if (!objectp(weapon = me->query_temp("weapon")) 
        || (weapon->query("skill_type") != "brush"&&weapon->query("skill_type") != "blade"))
                return notify_fail("你的武器不对，现在无法使用「清凉快打」。\n");
      
	  if (me->query_skill_mapped("blade") != "qingliang-shan"
			||me->query_skill_mapped("parry") != "qingliang-shan"
			|| me->query_skill_mapped("brush") != "qingliang-shan")
                return notify_fail("你激发不对，现在无法使用「戳字诀」。\n");

      if( (int)me->query_skill("qingliang-shan",1) < 450 )
                return notify_fail("你的清凉扇不够娴熟，不会使用「清凉快打」！\n");      

      if( (int)me->query_skill("force",1) < 450 )
                return notify_fail("你的基本内功等级不够，不能使用「清凉快打」！\n");  
      if( (int)me->query_skill("blade",1) < 450 )
                return notify_fail("你的基本刀法等级不够，不能使用「清凉快打」！\n");  
      if( (int)me->query_skill("brush",1) < 450 )
                return notify_fail("你的基本笔法等级不够，不能使用「清凉快打」！\n");  
      
      
      if( (int)me->query_dex() < 70 )
                return notify_fail("你的身法不够强，不能使用「清凉快打」！\n");
      
      if( (int)me->query("max_neili") < 12500 )
                return notify_fail("你的内力太弱，不能使用「清凉快打」！\n");
            
      lvl = (int)me->query_skill("qingliang-shan", 1);
      addlvl = (int)me->query_skill("qingliang-shan", 1)+(int)me->query_skill("blade", 1)/2+(int)me->query_skill("brush", 1)/2+(int)me->query_skill("force", 1)/2;
         
	  addlvl=addlvl/2;
        
      	
	  if( (int)me->query("neili") < 1500 )
		      return notify_fail("你的内力太少了，无法使用出「清凉快打」！\n");
      	
	  dk=lvl / 80;
      	
	  if(dk > 8) dk = 8; 
      	
      message_vision(HBGRN+HIW "$N轻笑一声，长吸一口气，纵身而起，围着$n飞速地起纵辗转，一式"NOR+HIM"「清凉快打」"+HBGRN+HIW"，宛如蝴蝶穿花，疾风骤雨。\n" NOR, me, target);

		me->add_temp("apply/attack", addlvl/3);
		me->add_temp("apply/brush", addlvl/4);
        me->add_temp("apply/blade", addlvl/5);
        me->add_temp("apply/damage", addlvl/5);
       

      	me->set_temp("qls/kuaida", 1);
      	
		for(i=0; i < dk; i++)
		{
      	   
			if(!me->is_fighting() 
				&& !target->is_killing(me->query("id"))
				&& !target->is_fighting(me))
      	   	break;
			if (me->query("neili")<50
				||me->query("jingli")<50)
			break;
			
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
           	//me->add_temp("qls/kuaida", 1);
            me->receive_damage("neili", 50);
            me->receive_damage("jingli", 10);
      	}
      	me->delete_temp("qls/kuaida");

		me->add_temp("apply/attack", -addlvl/3);
		me->add_temp("apply/brush", -addlvl/4);
        me->add_temp("apply/blade", -addlvl/5);
        me->add_temp("apply/damage", -addlvl/5);

		me->start_perform(6, "「清凉快打」");
        tell_object(me, HIW"\n清凉快打招式迅捷无比，你将手中折扇一合缓缓收工。\n"NOR); 
        return 1;
}
string perform_name(){ return HIM"清凉快打"NOR; }

int help(object me)
{
	write(HIC"\n清凉扇之「清凉快打」："NOR"\n");
	write(@HELP
	清凉扇是昆仑派灵清居士外门绝技，以扇为兵器既可以
	化作短棍，又可以化作刀法攻击，俗话说一寸短，一寸
	险，靠近攻击威力极为犀利，对于不善用力的女性玩家
	这清凉扇也是门派的重要外家功夫。
	注意：
	
	perform brush.kuaida

要求：
	最大内力需求 12500 以上；
	当前内力需求 1500 以上；
	清凉扇的等级 450 以上；
	基本内功等级 450 以上；
	基本笔法等级 450 以上；
	基本刀法等级 450 以上；
	后天身法大于 70  以上；
	激发刀法为清凉扇
	激发笔法为清凉扇
	激发招架为清凉扇；、
	内功不限；
	手持刀或笔类武器
HELP
	);
	return 1;
}
