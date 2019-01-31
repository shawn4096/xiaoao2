// 狂风
//kuangfeng.c 
//狂风招式

#include <ansi.h>
inherit F_SSERVER;
    
      
int perform(object me,object target)
{
       object weapon;
		int i,j;
      
       if( !target ) target = offensive_target(me);
       
       if( !objectp (target) || !me->is_fighting(target) || !living(target)
          || environment(target)!=environment(me))
                   return notify_fail("狂风疾攻只能对战斗中的对手使用。\n");
  
    
       if( (int)me->query_skill("kuangfeng-xunlei", 1) < 250 ) 
                   return notify_fail("你的狂风迅雷还未练成，不能使用狂风疾攻！\n");

                 
       if((int)me->query_skill("brush", 1) < 250 )
                   return notify_fail("你的基本笔法不够娴熟，不能在使用狂风疾攻。\n");
       if((int)me->query_skill("hand", 1) < 250 )
                   return notify_fail("你的基本手法不够娴熟，不能在使用狂风疾攻。\n"); 
	   if((int)me->query_skill("force", 1) < 250 )
                   return notify_fail("你的基本内功不够娴熟，不能在使用狂风疾攻。\n");
	   if((int)me->query_skill("dodge", 1) < 250 )
                   return notify_fail("你的基本内功不够娴熟，不能在使用狂风疾攻。\n");
	   if((int)me->query_dex(1) < 50 )
                   return notify_fail("你的后天身法不足50，不能在使用狂风疾攻。\n");
//必须左手扇子，右手空手
	   if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "brush"
           || me->query_skill_mapped("brush") != "kuangfeng-xunlei"
           || me->query_skill_mapped("parry") != "kuangfeng-xunlei")
                   return notify_fail("你现在激发不对使得了狂风疾攻么？\n");
                    
       if((int)me->query("max_neili") < 6000 )
                  return notify_fail("你的最大内力修为不够，不能使用狂风疾攻！\n");
       if((int)me->query("neili") < 2000 )
                 return notify_fail("你现在真气不足，不能使用狂风疾攻！\n");
       if((int)me->query("jingli") < 1000 )
                 return notify_fail("你现在精力不足，不能使用狂风疾攻！\n");
        message_vision(WHT"\n$N轻轻一笑，左手"+weapon->query("name")+WHT"甚是潇洒地挥了挥，脸上紫气闪了闪，身法突地加快!\n"NOR,me,target);
        message_vision(MAG"这正是狂风迅雷的绝招「狂风疾攻」,瞬间数招迭出，$N夹杂着右手犀利的点穴招式，$n目不暇接，防不胜防！\n"NOR,me,target);
		
		i = (int)me->query_skill("kuangfeng-xunlei",1);

        j=5;
		
		if (target->query_temp("kfxl/xlg"))
		{
			j=j-1;
			message_vision(RED"$N知晓$n为自己迅雷呵功所扰，心中暗笑，出手更不留情！\n"NOR,me,target);

		}
		me->set_temp("kfxl/kfjg",1);
     
		me->add("neili", -300);
		me->add("jingli", -200);
        me->add_temp("apply/attack",  i);
        me->add_temp("apply/damage",  i/j);

        me->add_temp("apply/hand",  i/j);
        me->add_temp("apply/brush",  i/j);

		if (me->is_fighting(target))

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
		weapon->unequip();
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
		weapon->wield();
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
		weapon->unequip();

		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
		weapon->wield();
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

      	weapon->unequip();

		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		weapon->wield();
        
           
	    me->add_temp("apply/attack",  -i);
        me->add_temp("apply/damage",  -i/j);

        me->add_temp("apply/hand",  -i/j);
        me->add_temp("apply/brush",  -i/j);
	
		me->delete_temp("kfxl/kfjg");
		message_vision(YEL"$N一番疾攻后，长吁一口气浊气，又恢复原来状态！\n"NOR,me,target);

		me->start_perform(5,"「狂风疾攻」");

		me->start_busy(random(3));

		return 1;
 }

string perform_name() {return HBCYN+HIB"狂风疾攻"NOR;}

int help(object me)
{
	write(WHT"\n狂风迅雷「"HIR"狂风疾攻"WHT"」："NOR"\n");
	write(@HELP
    狂风迅雷是霍都的招式，当初霍都随同金轮法王和达尔巴
	在大胜关和中原群豪一战，受法王指点施展出狂风迅雷功
	甚是惊艳。
	注意：此功法需带武器施展，和迅雷功组合后效果更佳。

	指令：perform brush.kuangfeng

要求：
	基本内功等级 350 级；
	基本笔法等级 350 级
	狂风迅雷等级 350 级
	基本轻功等级 350 级，
	当前内力要求 2000 以上，
	最大内力要求 6000 以上，
	当前精力要求 1000  以上。
	激发手法为狂风迅雷功；
	激发笔法为狂风迅雷功；
	手持笔类武器；
HELP
	);
	return 1;
}
