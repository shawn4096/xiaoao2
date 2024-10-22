// Created by LSXK@hsbbs 2007/5/10
// ci.c 苗家剑法之「绝命刺」.

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
string perform_name() {return HBBLU"绝命刺"NOR;}
int perform(object me, object target)
{
        object weapon;
        int damage,p;
        string msg,dodge_skill;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        ||  !living(target))
                return notify_fail("「绝命刺」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("miaojia-jianfa", 1) < 250 )
                return notify_fail("你的苗家剑法功力太浅，使不出苗家剑法之「绝命刺」的功夫!\n");

        if( (int)me->query_skill("sword", 1) < 250 )
                return notify_fail("你的基本剑法太差,使不出「绝命刺」的功夫!\n");

        if( (int)me->query("max_neili") < 3000 )
               return notify_fail("你的内力修为太浅，使不出「绝命刺」。\n");

        if( (int)me->query("neili") < 800 )
                return notify_fail("你的真气不够，使不出「绝命刺」功夫。\n");
        if( (int)me->query("jingli") < 800 )
                return notify_fail("你的精力不够，使不出「绝命刺」功夫。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "miaojia-jianfa")
                return notify_fail("你不使用苗家剑法,如何使得了「绝命刺」?\n");
                 
       if(me->query_temp("mjjf/lianhuan")
         &&!me->query("quest/雪山飞狐/武功/lengquanshengong_teach"))
           return notify_fail("你正在使用「连环夺命诀」！\n");

        me->set_temp("mjjf/ci", 1); 

        message_vision(HBBLU +HIW "\n$N突然运足内力，只听手中的"+weapon->name()+HBBLU+HIW"「嗡」的一声清响，便以雷霆万钧之势刺向$n。\n"NOR,me,target);

        if( random(target->query_skill("dodge"))<me->query_skill("dodge")/2
           || random(me->query("combat_exp"))>target->query("combat_exp")/3
           || random(me->query_skill("miaojia-jianfa")+me->query_skill("sword")) > target->query_skill("parry") ){
           damage = 3 * (int)me->query_skill("miaojia-jianfa", 1) + (int)me->query_skill("sword",1);
           damage = damage + random(damage) + 10 * (me->query("jiali")+(int)me->query_skill("miaojia-jianfa",1));
           if ( me->query("quest/雪山飞狐/武功/lengquanshengong_teach")
           && me->query_temp("lqsg/lq") ) {
               damage = damage*2;
               message_vision(HIW "$N更将「"HIB"冷泉"HIW"」内劲足足附于"+weapon->name()+HIW"上，顿时，"+weapon->name()+HIW"便如离弦之箭，只奔$n。\n"NOR,me,target);
           }
           if (wizardp(me))
               write(HIR"damage is; "+damage+" !\n"NOR);
           me->add("neili", -damage/10);
           me->add("jingli",-500);
           if(userp(target)&&damage >6000) damage=6000+random(1000);
           
		   target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage*2/3,me);
           if ( me->query("quest/雪山飞狐/武功/lengquanshengong_teach")
           && me->query_temp("lqsg/lq") ) 
               msg = HIB"但听$N一声清喝：「着！」，"+weapon->name()+HIB"已经在$n胸口对穿而过，殷红的鲜血瞬间从$n胸口喷了出来，眼见是活不成了。\n"NOR;
           else msg = HIR"但听$N一声清喝：「着！」，"+weapon->name()+HIR"已经在$n胸口对穿而过，殷红的鲜血瞬间从$n胸口喷了出来，眼见是活不成了。\n"NOR;
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           target->set_temp("last_damage_from", me);
           msg += damage_msg(damage, "刺伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           msg = replace_string( msg, "$l", "胸口" );
           msg = replace_string( msg, "$w", weapon->name());
		   message_vision(msg, me, target);
		   if(userp(me) && me->query("env/damage"))
			   tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR); 
		   
if(userp(target)&& target->query("env/damage"))
			   tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR); 
		   //by spiderii@ty 这个判断太...恐怖了。.auto call->die()...admire lsxk 
           if (random(target->query("kar")) < 2){
//                 if (wizardp(me))
                 message_vision(RED"$n哪里见过如此狠辣的招数，双眼惊恐地看着$N,一招穿心，倒地而亡。"NOR, me, target);
                 target->die();
           }
        } 
        else {
			  string tmp;
              msg = HIG"$n见这一剑来势如此之猛，哪敢正面接招，连忙运足轻功，往旁边一跃，远远的躲了开去。\n"NOR;
              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              if (stringp(tmp = SKILL_D(dodge_skill)->query_dodge_msg(target, 1)))
		      msg += tmp;
              me->add("neili", -100);
              me->start_busy(1); 
              target->add_busy(random(2)+1); 
                
			message_vision(msg, me, target);
        }
        me->delete_temp("mjjf/ci"); 

        me->start_perform(3, "「绝命刺」");
        return 1;
}

int help(object me)
{
   write(WHT"\n苗家剑法「"HBBLU+HIW"绝命刺"NOR+WHT"」："NOR"\n");
   write(@HELP
	「绝命刺」，光听这招名字，便让人感到心惊胆战。
	招式异常朴实，但对手若是被该招击中，哪怕便要
	真的应了这招的名字！另若，使用者会武林绝学冷
	泉神功之「冷泉」绝技，则相辅相成，威力更盛！

	指令：perform sword.ci
	
要求：
	当前内力需求 800 以上；
	最大内力需求 3000 以上；
	当前精力需求 800 以上；
	苗家剑法等级 250 以上；
	基本内功等级 250 以上；
	基本剑法等级 250 以上；
	激发剑法为苗家剑法；
	且手持兵器。

HELP
   );
   return 1;
}
