// fen.c 焚
// by iceland
// modefied by emnil@sj 2/3/2k
 
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
 
string perform_name(){ return HBRED+HIW"刀气"NOR; }
int check_fight(object me,int count);
int perform(object me,object target)
{
        
        int skill,damage;

        skill= me->query_skill("huoyan-dao",1);
		damage=skill+me->query_skill("longxiang-boruo",1);
        if( !target ) target = offensive_target(me);
        if( !target 
         || !me->is_fighting(target)
         || !objectp(target)
         || environment(target)!= environment(me))
		    return notify_fail("「火焰刀气」只能在战斗中对对手使用。\n");
       
        if (me->query_temp("hyd/power"))
                return notify_fail("你正在施展「火焰刀气」绝技。\n");          
         if (objectp(me->query_temp("weapon")))
                return notify_fail("你只能空手运用"HIR"「火焰刀气」"NOR"的绝技。\n");
        if( skill < 350)
                return notify_fail("你的「火焰刀」等级不够, 不能使出"HIR"「火焰刀气」"NOR"的绝技！\n");
        if( me->query_skill("longxiang-boruo",1) < 350)
                return notify_fail("你的「龙象般若功」功力不够, 不能使出"HIR"「火焰刀气」"NOR"的绝技！\n");
        if( me->query("neili") < 2500 )
                return notify_fail("你的内力无法支撑"HIR"「火焰刀气」"NOR"的施展了！\n");
        if( me->query("jingli") < 1500 )
                return notify_fail("你的精力无法支撑"HIR"「火焰刀气」"NOR"的施展了！\n");
        if( me->query("max_neili") < 5000 )
                return notify_fail("没有强大的内力支持如何施展"HIR"「火焰刀气」"NOR"绝技！\n");
        if( me->query_skill_mapped("strike") != "huoyan-dao"
         || me->query_skill_prepared("strike") != "huoyan-dao")
                return notify_fail("你必须使用「火焰刀」，才能使出"HIR"「火焰刀气」"NOR"的绝技！\n");
        if( me->query_skill_mapped("force") != "longxiang-boruo")
                return notify_fail("你现在所使用的内功同「龙象般若功」相抵触，不能使出「焚」的绝技！\n"); 
		message_vision(HBRED+HIY"\n$N左掌斜斜劈出，掌上已蓄积真力，刀气弥漫，宛如实质，\n这招使出的正是大轮寺「火焰刀」中的「刀气」绝技。\n"NOR, me, target);         
        
		if (me->query("quest/dls/longxiang/pass"))
        {
			skill=skill+me->query_skill("longxiang-boruo",1)/6;
        }
		
        me->add("jingli",-150);
		me->add("neili",-400);
		me->set_temp("hyd/power",skill);
		me->add_temp("apply/attack",skill/6);
	    me->add_temp("apply/damage",skill/6);
		me->add_temp("apply/strike",skill/6);
        if( random(me->query_skill("huoyan-dao",1)) > target->query_skill("parry",1)/3
         || random(me->query("combat_exp"))>target->query("combat_exp")/2
         || random(me->query("neili"))> target->query("neili")/2)
        {
        	message_vision(HIR "\n$n只觉得这招威力奇大，裹向自己周身，一不小心为刀气所伤！\n"NOR,me,target);			
			if (me->query("lx/gree")>10)
			{
				damage=damage*2;
			}else 
				damage+=damage+random(damage/2);			
			if (damage>4000) damage=4000+(damage-4000)/100;
			//if (target->query("qi")<damage)
			  // damage=target->query("qi")-100;
			target->receive_damage("qi",damage,me);
			target->start_busy(1+random(2));
			target->set_temp("hyd/power",1);
			if (me->is_fighting() && me->query_skill("huoyan-dao",1)>450)
				COMBAT_D->do_attack(me, target, 0, me->query_temp("xs/longxiang")?3:1);
			call_out("check_fight", 1, me);
        }
        else
        {
         	message_vision(HIB"\n$n一个闪身，运起自身内功迎向了$N，轻松将$N的攻势化解！\n"NOR,me,target);
        	me->start_busy(1);
        }
        if (me->query_skill("huoyan-dao",1)<450)
        {
			me->start_perform(2,"火焰刀气");
        }
        call_out("check_fight",1,me,skill);
        return 1;
}

int check_fight(object me,int count)
{
      int skill;
	  
      if ( !me || !me->query_temp("hyd/power")) return 0;
	  skill=me->query_temp("hyd/power");
/*
      if (me->query_skill_prepared("strike") !="huoyan-dao")
	  {
        me->delete_temp("hyd/power");
		me->add_temp("apply/attack",-skill/6);
	    me->add_temp("apply/damage",-skill/6);
		me->add_temp("apply/strike",-skill/6);
        tell_object(me, HIR"你招式一换，散去「火焰刀气」。\n"NOR);		
        return 0;
      }
	  */
      if ((!me->is_fighting())
          ||(me->query_skill_prepared("strike") !="huoyan-dao")	)  {
          me->delete_temp("hyd/power");
		  me->add_temp("apply/attack",-skill/6);
	      me->add_temp("apply/damage",-skill/6);
		  me->add_temp("apply/strike",-skill/6);
          tell_object(me, HIR"你将注于双掌之上的内力收回，散去了「火焰刀气」劲力。\n"NOR);
          return 0;
      }
    
       call_out("check_fight", 1, me,count -2);
       return 0; 
}
int help(object me)
{
	write(HIR"\n火焰刀秘技「刀气」："NOR"\n");
	write(@HELP
火焰刀秘技「刀气」：

	火焰刀乃是大轮寺绝技，依靠强大的龙象般若功的威力施展出来甚是强大
	想当初鸠摩智在崇明寺一战，以火焰刀尽败枯荣禅师等六僧，靠的就是这
	门神技。刀气乃是将劲力融于掌中，依靠强大的内功运使法门施展，为火
	焰刀绝技重要的辅助技能。450大飞。
	
	指令：perform strike.daoqi

要求：
	最大内力  5000 以上；
	内力要求  2500 以上；
	龙象般若功 350 以上；
	火焰刀等级 350 以上；
	基本内功   350 以上；    
HELP
	);
	return 1;
 }
