// jue.c 绝命针
//做成pxj的起手式，增加伤害和命中

#include <ansi.h>
string perform_name(){ return HBRED+HIY"绝命针"NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("pixie-jian", 1) < 400 )
                return notify_fail("你的辟邪剑法不够娴熟，不会使用绝命针。\n");
		if( (int)me->query_skill("sword", 1) < 400 )
                return notify_fail("你的基本剑法不够娴熟，不会使用绝命针。\n");
		if( (int)me->query_skill("dodge", 1) < 400 )
                return notify_fail("你的基本轻功不够娴熟，不会使用绝命针。\n");
        if( (int)me->query_dex() < 65  )
                return notify_fail("你的身法太低，不能使用绝命针。\n");
 
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你现在内力不足！\n");     
		if( (int)me->query("jingli", 1) < 500 )
                return notify_fail("你现在精力不足！\n");  

        if (!weapon || !(weapon->id("needle"))
			|| me->query_skill_mapped("dodge") != "pixie-jian"
			|| me->query_skill_mapped("parry") != "pixie-jian"
			|| me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("你现在无法使用绝命针。\n");
        if( me->query("gender")!="无性")
                return notify_fail("你是有根之人，如何能懂得辟邪剑法真意？\n");

        message_vision(RED"\n$N一声尖叫,猛地纵起，向$n扑去，手指一弹，数枚细针飞了出去，插向$n的右目！\n\n"NOR, me, target);
  
        me->add("neili", -random(1000));
        me->add("jingli", -random(500));
      
      if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 
		  || random(me->query_dex(1)) >(int)target->query_dex(1)/2)
	  {
        message_vision(HIR"\n$n猝不及防，大叫一声，右眼中针！\n"NOR, me, target);
        tell_object(target, HIY "你感觉细针正插在自己的瞳仁之中，如果这针直贯入脑，便有性命之忧！\n" NOR);
        
		if (!me->query("quest/pixie/super") || !QUEST_D->queryquest(me,"kuihua/book"))
        {
					me->start_busy(2);
        }
                target->start_busy(2);
                me->add("neili", -300);
                damage = (int)target->query("max_qi");
                damage = damage/2;
				if (me->query("quest/pixie/super") || QUEST_D->queryquest(me,"kuihua/book"))
					damage=damage+random(damage);

                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
				target->apply_condition("no_perform",1);
                if(userp(me) && me->query("env/damage"))
		           tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR); 
	            
if(userp(target)&& target->query("env/damage"))
		           tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
	  
          me->query_temp("weapon")->move(target);
                if (userp(target))
					target->kill_ob(me);
               }
               else 
               {
                target->start_busy(2);
                me->query_temp("weapon")->move(environment(target));
                target->kill_ob(me);
                message_vision(HIY"\n可是$n看破了$N的企图，飞身闪了开去。\n"NOR, me, target);
                me->add("neili", -random(300));
               }

        return 1;
}


int help(object me)
{
   write(WHT"\n辟邪剑法「"HBRED+HIY"绝命针"WHT"」："NOR"\n");
   write(@HELP
	日月神教乃江湖中重要的一大邪派组织，做事全凭个人好恶
	教中长老武技各有所长，这辟邪剑法乃是现任教主东方不败
	的绝技，后来江湖流传各种版本，但正宗辟邪剑法以轻巧、
	灵活、多变而著称。
	「绝命针」乃是运功与针，直插对方头部，若中后，对方则
	会遭受极大的创伤，乃是一招出其不意的狠招！
    
	指令：perform sword.jue

要求：
	当前内力 1000 以上；
	当前精力 500 以上；
	辟邪剑法 400 以上；
	基本剑法 400 以上；
	基本轻功 400 以上；
	后天身法 65  以上；
	激发轻功辟邪剑法
	激发招架辟邪剑法；
	激发剑法辟邪剑法；
	需手持针状武器;

HELP
   );
   return 1;
}
