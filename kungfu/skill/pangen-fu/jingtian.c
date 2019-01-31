//  jingtian.c 惊天断云斧 
//  by Leontt 2000.6.11

#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
      int lvl,lvl1;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl = (int)me->query_skill("pangen-fu", 1);
      if( !target ) target = offensive_target(me);
     
     if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("盘根错节斧只能对战斗中的对手使用。\n");
    
      if (!weapon || weapon->query("skill_type") != "axe"
       || me->query_skill_mapped("axe") != "pangen-fu")
            return notify_fail("你使用的兵刃不对，无法使用「惊天断云斧」！\n");             

      if( (int)me->query_skill("pangen-fu",1) < 220 )
            return notify_fail("你的盘根斧法不够娴熟，不能使用「惊天断云斧」！\n"); 
      if ( me->query_skill_mapped("axe") != "pangen-fu"
            || me->query_skill_mapped("parry") != "pangen-fu")
            return notify_fail("你现在无法使用「盘根错节」斧法！\n");
     
      if( (int)me->query_skill("axe",1) < 220 )
        return notify_fail("你的基本斧法等级不够，不能使用「惊天断云斧」！\n");  
     
      if( (int)me->query_skill("qiantian-yiyang", 1) < 220 )
        return notify_fail("你的乾天一阳功等级不够，不能使用「惊天断云斧」！\n");
      if( me->query_str() < 40 )
            return notify_fail("你的膂力不够，无法使用「盘根错节」斧法！\n");

      if( (int)me->query("max_neili") < 2000 )
        return notify_fail("你的最大内力太弱，不能使用「惊天断云斧」！\n");
      if( (int)me->query("neili") <500 )
        return notify_fail("你的当前内力太弱，不能使用「惊天断云斧」！\n");     
      
      message_vision(HIY"\n$N突然大喝一声,运足内力，手中"+weapon->query("name") +HIY"轮圆了劈将下来，巨斧本已甚为\n"+
                          "深重，加上$N全力施展，力道何止千斤，直有惊天断云之威！\n"NOR, me,target);
      me->add("neili", - (200+random(200)));
      me->add("jingli", -80);      
      lvl1= lvl + me->query_dex() + me->query_str();
      me->add_temp("apply/axe", lvl/6);
      me->add_temp("apply/strength", lvl1 /20 );
      me->add_temp("apply/attack", lvl/4);
      me->add_temp("apply/damage", lvl/8);
      me->set_temp("pgf/jingtian", 1);
	  
	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
      if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);  
	  if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
      if (present(target,environment(me))
       && me->is_fighting(target)
       && me->query_skill("pangen-fu", 1) > 250){
       if(random(me->query("combat_exp")) > target->query("combat_exp")/3)     
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       else 
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
      }
      me->add_temp("apply/axe",- lvl/6);
      me->add_temp("apply/strength", -lvl1 /20 );
      me->add_temp("apply/attack",- lvl/4);
      me->add_temp("apply/damage",- lvl/8);
      me->delete_temp("pgf/jingtian");
      me->start_busy(random(2));
      me->start_perform(5,"「惊天断云斧」");
      return 1;
}
string perform_name() {return HIR"惊天断云"NOR;}

int help(object me)
{
   write(WHT"\n盘根错节斧法之「"HIR"惊天断云"WHT"」："NOR"\n\n");
   write(@HELP
	盘根错节斧乃是大理渔樵耕读四大护卫南山樵子古竺诚的独门武技，
	其斧法虽然招式平凡，但却在平凡的招式中蕴藏杀机。斧沉力猛，无
	论是上阵杀敌还是地下单打独斗都甚是威猛。惊天断云式乃是将斧头
	舞动开来，连续三招，将敌人翻在地，端的是厉害无比。攻击威力和
	招式、身法、臂力有关系。

	perform axe.jingtian

要求: 
	最大内力 4000 点；
	当前内力 1000 点；
	盘根斧法 220  以上；
	基本斧法 220 以上；
	乾天一阳 220 以上；
	后天臂力 40  以上
	激发斧法为盘根斧法；
	激发招架为盘根斧法；
	装备斧头。

          
HELP
   );
   return 1;
}
