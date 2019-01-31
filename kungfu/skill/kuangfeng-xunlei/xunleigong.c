// 迅雷呵功
//xunleigong.c 
//呵斥类武技，降低对方防御，失神

#include <ansi.h>
inherit F_SSERVER;
    
    
   int perform(object me,object target)
 {
       object weapon;
		int i;
      
       if( !target ) target = offensive_target(me);
       
       if( !objectp (target) || !me->is_fighting(target) || !living(target)
          || environment(target)!=environment(me))
                   return notify_fail("迅雷呵功只能对战斗中的对手使用。\n");
  
      
       if( (int)me->query_skill("kuangfeng-xunlei", 1) < 250 ) 
                   return notify_fail("你的狂风迅雷还未练成，不能使用迅雷呵功！\n");
		if( (int)me->query_skill("mizong-fofa", 1) < 200 ) 
                   return notify_fail("你的密宗佛法还未练成，不能使用迅雷呵功！\n");
                 
       if((int)me->query_skill("brush", 1) < 250 )
                   return notify_fail("你的基本笔法不够娴熟，不能在使用迅雷呵功。\n");
       if((int)me->query_skill("hand", 1) < 250 )
                   return notify_fail("你的基本手法不够娴熟，不能在使用迅雷呵功。\n"); 
	   if((int)me->query_skill("force", 1) < 250 )
                   return notify_fail("你的基本内功不够娴熟，不能在使用迅雷呵功。\n");
	   if((int)me->query_skill("dodge", 1) < 250 )
                   return notify_fail("你的基本内功不够娴熟，不能在使用迅雷呵功。\n");
	   if((int)me->query_dex(1) < 50 )
                   return notify_fail("你的后天身法不足50，不能在使用迅雷呵功。\n");
//必须左手扇子，右手空手
	   if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "brush"
           || me->query_skill_mapped("brush") != "kuangfeng-xunlei"
           || me->query_skill_mapped("parry") != "kuangfeng-xunlei")
                   return notify_fail("你现在激发不对使得了迅雷呵功么？\n");
                   
       if((int)me->query("max_neili") < 6000 )
                  return notify_fail("你的最大内力修为不够，不能使用迅雷呵功！\n");
       if((int)me->query("neili") < 2000 )
                 return notify_fail("你现在真气不足，不能使用迅雷呵功！\n");
       if((int)me->query("jingli") < 1000 )
                 return notify_fail("你现在精力不足，不能使用迅雷呵功！\n");
       if (me->query_temp("kfxl/xlg"))
				return notify_fail("你正在施展使用迅雷呵功！\n");
	   if (target->query_temp("kfxl/xlg"))
		        return notify_fail("对方已中了你的迅雷呵功！\n");
		message_vision(WHT"\n$N左手"+weapon->query("name")+WHT"对$n连挥三下，脸上紫气闪了闪，在疾攻的同时对$n不断大声呵斥，宛如迅雷!\n"NOR,me,target);
    
		i = (int)me->query_skill("kuangfeng-xunlei",1)/4;

		
		if (!target->query_temp("kfxl/xlg")
			&&(random(me->query_skill("force",1))>target->query_skill("force",1)/2)||random(me->query_int())>target->query_int()/2)
		{
			message_vision(HIM"\n$N对$n发出一连串的梵语，大声呵斥，$n一时不查，顿时为这迅雷呵功所吓住，手法一滞!\n"NOR,me,target);
			target->add_busy(2);
			target->add_temp("apply/attack",-i/5);
			target->add_temp("apply/parry",-i/5);
			target->add_temp("apply/dodge",-i/5);
			target->set_temp("kfxl/xlg",i);
			call_out("remove_effect",1,target);
		}
        
		me->set_temp("kfxl/xlg",1);      
		me->add("neili", -350);
		me->add("jingli", -250);
 
		call_out("me_effect",1,me);
		return 1;
 }

 int me_effect(object me)
 {
	if (!me) return 0;
	me->delete_temp("kfxl/xlg");
	message_vision(HIM"\n$N平心静气，缓缓将迅雷呵功停止运使!\n"NOR,me);

	return 1;
} 
 int remove_effect(object target)
 {
	int i;
	if (!target||!target->query_temp("kfxl/xlg")) return 0;
	i=target->query_temp("kfxl/xlg");
	target->add_temp("apply/attack",i/5);
	target->add_temp("apply/parry",i/5);
	target->add_temp("apply/dodge",i/5);
	target->delete_temp("kfxl/xlg");
	message_vision(HIM"\n$n劲气瞬间通达，将迅雷功带来的虚弱消除殆尽!\n"NOR,target);

	return 1;

 }
string perform_name() {return HIR"迅雷呵功"NOR;}

int help(object me)
{
	write(WHT"\n狂风迅雷「"HIR"迅雷呵功"WHT"」："NOR"\n");
	write(@HELP
    狂风迅雷是霍都的招式，当初霍都随同金轮法王和达尔巴
	在大胜关和中原群豪一战，受法王指点施展出狂风迅雷呵
	功甚是惊艳。命中和悟性、基本内功等级挂钩
	注意：此功法需带武器施展，和迅雷呵功组合后效果更佳。

	指令：perform brush.kuangfeng

要求：
	基本内功等级 350 级；
	基本笔法等级 350 级
	狂风迅雷等级 350 级
	基本轻功等级 350 级，
	当前内力要求 2000 以上，
	最大内力要求 6000 以上，
	当前精力要求 1000  以上。
	激发手法为狂风迅雷呵功；
	激发笔法为狂风迅雷呵功；
	手持笔类武器；
HELP
	);
	return 1;
}
