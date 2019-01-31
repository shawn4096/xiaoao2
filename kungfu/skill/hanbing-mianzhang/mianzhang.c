// Created by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

string perform_name() {return HIY"寒冰阴柔劲"NOR;}

int perform(object me,object target)
{
        int damage,skill, p, win;
        int tmp;
        string msg;
         win=0;
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target))
                return notify_fail("寒冰绵掌「阴柔劲」绝技只能对战斗中的对手使用。\n");
        if (me->query_temp("weapon"))
                return notify_fail("寒冰绵掌「阴柔劲」绝技只能空手使用！\n");

        if( (int)me->query_skill("hanbing-mianzhang", 1) < 250 )
                return notify_fail("你的寒冰绵掌火候不够。\n");
 
        if( (int)me->query_skill("parry", 1) < 250 )
                return notify_fail("你的基本招架火候不够。\n");
        if( (int)me->query_skill("dodge", 1) < 250 )
                return notify_fail("你的基本轻功火候不够。\n");
        if( (int)me->query_skill("shenghuo-shengong", 1) < 250 )
                return notify_fail("你的圣火神功火候不够。\n");
                
        if( (int)me->query("max_neili") < 3500 )
                return notify_fail("你的内力修为不够。\n");

        if( (int)me->query("neili") < 800 )
                return notify_fail("你的真气不够。\n");

        if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力不够。\n");        

        if (me->query_skill_prepared("strike") != "hanbing-mianzhang"
         || me->query_skill_mapped("strike") != "hanbing-mianzhang")
                return notify_fail("你现在无法使用寒冰绵掌。\n");
       
        if( me->query_temp("hbmz/yinrou"))
               return notify_fail("你正在使用寒冰绵掌阴柔劲绝技。\n");
 
        me->add("neili", -200);
        me->add("jingli", -50);
        message_vision(HIR "\n$N忽然仰天喋喋怪笑，身形向后迅捷倒窜数尺，陡然回身双掌呈阴阳状按向$n的周身要害！\n" NOR,me, target);
		skill = me->query_skill("hanbing-mianzhang",1);     
       // me->add_temp("apply/attack", skill/3);
       // me->add_temp("apply/damage", skill/5);
      //  me->add_temp("apply/strike", skill/5);
		me->set_temp("hbmz/yinrou",skill);
	    me->add_temp("apply/attack", skill/3);               
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
		me->add_temp("apply/attack", -skill/3);    

        msg = HIB "\n$N左掌向前轻推，开声发力，右掌虚按所发出的阴力却先行着体，一股寒气直逼$n而去！\n" NOR;
        if (random(me->query("combat_exp")) > target->query("combat_exp")/2
			||random(me->query_dex(1)) > target->query_dex(1)/2 ){
                msg += HIC"$n刚要闪避，只觉一股寒气袭上身来，登时机伶伶打了个冷颤。\n"NOR;
                damage = (int)me->query_skill("force") + (int)me->query_skill("hanbing-mianzhang")*2;
				damage=damage*me->query_dex(1)/10; //需要高身法，福王武功特点
                damage = damage+random(damage);
                if (damage > 4000) damage = 4000 + (damage - 4000)/100;
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/4,me);
				target->apply_condition("hb_poison",1);
				target->start_busy(1+random(2));
                me->add("neili", -200);
                me->add("jingli", -50);
                if (wizardp(me)) tell_object(me,HIW"damage是"+damage + "。\n"NOR);
                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "内伤");
                msg += "( $n" + eff_status_msg(p) + " )\n";
				
				win=1;
        }
        else{ 
                msg += BLU"$n被这阴柔寒掌力打在身上，霎时间全身冰凉，似乎血液都要被冻僵了一般。\n"NOR;
                win = 0;
        }
        message_vision(msg, me, target);
	
     //第二掌
	  if (win == 1){  
          msg =HIW"就在$n周身冰冷之际，$N左掌蓄积的掌风又已然拍到！\n"NOR;
           if (random(me->query("combat_exp")) > target->query("combat_exp")/2
			  ||random(me->query_skill("strike",1)) > target->query_skill("parry",1)/2
		    ){
              msg += HIR"$n心知不妙，意欲闪避，却心有余而力不足，这一掌结结实实拍在$n的前胸！\n"NOR;
              damage=damage*me->query_str(1)/10;
			  damage=damage+random(damage);
             // if(!userp(me)&&damage > 6000) damage = 6000 + (damage - 6000)/100;
			 if(damage > 5000) damage = 5000 + (damage - 5000)/100;
              me->add("neili", -200);
              me->add("jingli", -50);
              target->receive_damage("qi", damage,me);
              target->receive_wound("qi", damage/3,me);
              if (wizardp(me)) tell_object(me,HIW"damage是"+damage + "。\n"NOR);
              p = (int)target->query("qi") * 100 / (int)target->query("max_qi"); 
              msg += damage_msg(damage, "内伤");
              msg += "( $n" + eff_status_msg(p) + " )\n";
			  me->add_temp("apply/attack", skill/3);
			  me->add_temp("apply/damage", skill/5);
			  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
			  me->add_temp("apply/attack", -skill/3);
			  me->add_temp("apply/damage", -skill/5);
           }
           else {
              msg +=HIY "$n被这股掌力打在身上，阴柔无比，引起全身内脏的巨震，痛彻入骨。\n"NOR;
           }
           message_vision(msg, me, target); 
		  // COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        }
       
        me->start_perform(4,"寒冰阴柔劲");
		me->delete_temp("hbmz/yinrou");
        me->start_busy(1+random(1));
        target->add_busy(1+random(2));
        return 1;
}

int help(object me)
{
        write(HIC"\n寒冰绵掌之「"+HIY"寒冰阴柔劲"NOR"」\n\n");
        write(@HELP
	寒冰绵掌阴柔劲乃是青翼蝠王独门武技，连续两招，一阴一阳
	陆续使出，厉害无比。青翼蝠王武功全凭轻功飘逸和掌法精妙
	所以，对于身法和掌法的要求较高。玩家在尝试此招时请注意。
	
	指令：perform strike.mianzhang

要求：
	当前内力 800  以上；
	当前精力 500  以上；
	最大内力 3500 以上；
	寒冰绵掌等级 250 以上；
	圣火神功等级 250 以上；
	基本轻功等级 250 以上；
	激发掌法为寒冰绵掌；
	激发招架为寒冰绵掌或乾坤大挪移。

HELP
        );
        return 1;
}
