// 夺命金花 - 满天花雨
// By River@SJ 

inherit F_SSERVER;
#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int num,p,damage,skill;
        string msg;
        object weapon = me->query_temp("weapon");
        damage = me->query_skill("duoming-jinhua", 1);
		skill = me->query_skill("duoming-jinhua", 1);
        
		if( !target ) target = offensive_target(me);
        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
              return notify_fail("你只能对战斗中的对手使用。\n");
        if((int)me->query_skill("duoming-jinhua", 1) < 250 )
              return notify_fail("你的夺命金花不够娴熟，还不能使用满天花雨。\n");
        if((int)me->query_skill("shenghuo-shengong", 1) < 250 )
              return notify_fail("你的圣火神功等级不够，不能使用满天花雨。\n");
        if((int)me->query("neili", 1) < 500 
         ||(int)me->query("jingli", 1) < 1200 )
              return notify_fail("你现在内力和体力不能施展满天花雨的绝技！\n");
        if( (int)me->query_dex() < 35 )
			  return notify_fail("你的身法太低，无法施展满天花雨的绝技。\n");
        if ( !weapon
         || weapon->query("skill_type") != "throwing"
         || me->query_skill_mapped("throwing") != "duoming-jinhua")
              return notify_fail("你现在无法使用满天花雨。\n");
        num = me->query_skill("duoming-jinhua", 1) / 100;
       
        if ((weapon->query_amount()) < num)
             return notify_fail("你身上的暗器不够，无法使出满天花雨。\n");         
        me->add("neili", -100);
        me->add("jingli", -50);
        if (me->query_skill("duoming-jinhua",1)<300)
        {
			me->start_busy(1);
        }
        msg = HIY"\n$N清叱一声，长袖飘飘，只见"+chinese_number(num)+"道寒光呈满天花雨之势，从四面八方向$n飞射而去。\n"NOR;
        if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/2
          || (int)me->query_dex(1) > random(target->query_dex(1))){
          weapon->add_amount(-num);
          msg += HIR"只见$n躲闪不及，痛苦的大叫一声，"+weapon->name()+HIR"已全部击中其全身要穴。\n"NOR;
          me->add("neili", -200);          
          damage +=me->query_skill("throwing", 1);
          damage = damage *num*me->query_str()/20;
          damage = damage + random(damage);
          if (damage >3000) damage=3000+(damage-3000)/10; //发挥圣火的威力
          if (me->query("gender") =="女性"&&!userp(target)) damage=damage*2;
		  if (damage>target->query("qi"))
		  {
			  damage=target->query("qi");
		  }
		  target->receive_damage("qi", damage,me);
          target->receive_wound("qi", damage/4,me);
          target->start_busy(1+random(2));
          if(!target->is_killing(me->query("id"))) target->kill_ob(me);
          p = (int)target->query("qi")*100/(int)target->query("max_qi");
          msg += "( $n"+eff_status_msg(p)+" )\n";
         }
         else {
          msg += CYN"$n抱头缩颈一个滚翻，堪堪然躲开了"+weapon->name()+CYN"的攻击。\n"NOR;
          weapon->add_amount(-num);
          me->start_busy(1);
          me->add("neili",-100);
         }
         message_vision(msg, me, target);
		 me->add_temp("apply/attack",skill/3);
		 if (me->query("gender")=="女性"){
			 me->add_temp("apply/damage",skill/5);
			 me->add_temp("apply/throwing",skill/5);
		 }
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		 me->add_temp("apply/attack",-skill/3);
		 if (me->query("gender")=="女性"){
			 me->add_temp("apply/damage",-skill/5);
			 me->add_temp("apply/throwing",-skill/5);
		 }
         me->start_perform(4,"满天花雨");
		 me->start_busy(random(1));
         return 1;
}
string perform_name(){ return HIR"「漫天花雨」"NOR; }

int help(object me)
{
	write(YEL"\n夺命金花之"+HIR"「漫天花雨」"NOR"\n\n");
	write(@HELP
	夺命金花乃是金华婆婆（紫衫龙王）的独门武功，女性
	使用有额外威力。金华一出，绚烂无比。紫衫龙王容颜
	娇媚，乃天下第一美人，手持金华，漫天花雨，攻击极
	为犀利。女性运用此招比男性有优势。300级小飞
	注意：命中与身法有关，伤害与臂力有关。
	
	指令：perform throwing.huayu

要求：
	当前内力 500 以上；
	当前精力 1200 以上；
	圣火神功 250 级;
	夺命金花等级 250 以上；
	激发暗器为夺命金花；
	且手持暗器。


HELP
        );
        return 1;
}
