// This program is a part of NITAN MudLIB
// qinna.c 擒拿

#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me,object target)
{
        string msg;
        object weapon;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("风云手「擒拿」只能在战斗中对对手使用。\n");

        skill = me->query_skill("fengyun-shou", 1);

        if (skill < 140)
                return notify_fail("你的风云手等级不够，不会使用「擒拿」！\n");
		if (me->query_skill("yijin-jing", 1) < 140)
                return notify_fail("你的易筋经等级不够，不会使用「擒拿」！\n");
		if (me->query_skill("hand", 1) < 140)
                return notify_fail("你的基本手法等级不够，不会使用「擒拿」！\n");

        if (me->query("neili") < 500)
                return notify_fail("你的真气不够，无法运用「擒拿」！\n");
         if (me->query("jingli") < 500)
                return notify_fail("你的当前精力不够，无法运用「擒拿」！\n");

        if (me->query_skill_mapped("hand") != "fengyun-shou"
			||me->query_skill_prepared("hand") != "fengyun-shou") 
                return notify_fail("你没有激发风云手，无法使用「擒拿」！\n");
       if (target->is_busy())
              return notify_fail("对方已经手忙脚乱了，用不着这么费力吧？\n");

       if (!living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "贴上前来，和$n" HIC "近身搏击，只见$P"
              "的手忽折忽扭，或抓或甩，令人眼花缭乱！\n" NOR;
 
		ap = me->query("combat_exp")/1000;
		dp = target->query("combat_exp")/1000;
	
        if (random(ap) > dp/2
			||random(me->query_skill("hand",1))>target->query_skill("parry",1)/2)
        {
                me->add("neili", -80);
                damage =me->query_skill("hand",1)+me->query_skill("fengyun-shou",1) ;
                message_vision(HIR "$p" HIR "奋力抵抗，终究不敌$P"HIR "，连中数招后还是被压制得无法反击！\n" NOR,me,target);
				target->receive_damage("qi",damage,me);
				target->receive_damage("qi",damage/3,me);
				if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);

                target->add_busy(1);
                
        } else
        {
                message_vision(CYN "可是$p" CYN "的看破了$P" CYN
                       "的招式，巧妙的一一拆解，没露半点破绽！\n" NOR,me,target);
                me->add("neili",-20);
                me->start_busy(2);
        }
        return 1;
}

string perform_name(){ return HIY"擒拿术"NOR; }

int help(object me)
{
        write(HIC"\n风云手之「擒拿术」绝技："NOR"\n");
        write(@HELP
	风云手是一门少林手法入门武技，是以后高级手法千叶手
	的基础武技。乃是少林弟子初入江湖所习用武技。
	其特点是将少林的擒拿术融合到实战中，贴身而战，趁对
	方不防备拿住对方的要害部位，从而一招制敌。
	
	指令：perform hand.qinna
		
要求：  
	最大内力需求 1500 以上；      
	当前内力需求 500  以上
	当前精力需求 500  以上；  
	风云手法等级 150 以上；
	易筋经功等级 150 以上；
	基本手法等级 150 以上；	
	激发手法为风云手；
	且手无兵器；
                
HELP
        );
        return 1;
}