// ningxue.c  凝血神爪之「凝血诀」
// Create By lsxk@hsbbs 2007/5/13 
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string *xue_name = ({"大锥穴","百会穴","志室穴","肩井穴","劳宫穴","内关穴","外关穴","会宗穴",
                     "曲池穴","冲阳穴","臂儒穴","白海穴","灵台穴","风府穴","神风穴","玉书穴",
                     "青门穴","商阳穴","丝空竹穴","气海穴","冲门穴","大椎穴","百里穴","槐阳穴", });

string perform_name() {return RED"凝血诀"NOR;}
int remove_effect(object me,int count);

 int perform(object me, object target)
 {
         int j;
         string msg,xuedao;
         j = me->query_skill("ningxue-shenzhua", 1);

         if( !target ) target = offensive_target(me);

         if( !target 
           || !me->is_fighting(target)
           || !living(target)
           || environment(target)!= environment(me))
                 return notify_fail("「凝血诀」只能在战斗中对对手使用。\n");

         if( objectp(me->query_temp("weapon")) )
                 return notify_fail("你必须空手才能使用「凝血诀」！\n");

         if( (int)me->query_skill("ningxue-shenzhua", 1) < 150 )
                 return notify_fail("你的凝血神爪不够娴熟，使不出「凝血诀」绝技。\n");

         if( (int)me->query_skill("force", 1) < 200 )
                 return notify_fail("你基本内功不够，使不出「凝血诀」绝技。\n");

         if( (int)me->query_dex() < 30 )
                return notify_fail("你在身法不足，无法使用「凝血诀」绝技!\n");

         if (me->query_skill_prepared("claw") != "ningxue-shenzhua"
          || me->query_skill_mapped("claw") != "ningxue-shenzhua"
          || me->query_skill_mapped("parry") != "ningxue-shenzhua")
                 return notify_fail("你要全面运用凝血神爪功夫才能使出「凝血诀」绝技！\n");

         if( (int)me->query("max_neili") < 2000)
                 return notify_fail("你内力修为太差，无法使用「凝血诀」绝技。\n");

         if( (int)me->query("neili") < 1500 )
                 return notify_fail("你现在真气太弱，无法使用「凝血诀」绝技。\n");
         if( me->query_temp("nxsz/ningxue"))
                 return notify_fail("你现在正在使用「凝血诀」绝技。\n");

        // if( (int)me->query("combat_exp",1)*2/3 > (int)target->query("combat_exp",1) && userp(target))
          //       return notify_fail("世界如此美好，你却如此暴躁，这样不好，不好。。。。。。\n");

         xuedao = xue_name[random(sizeof(xue_name))];

        message_vision(HBWHT+HIR"$N暗运凝血劲，全身真气流转，凝聚于$N双手,掌心颜色由白变红连转数次，冒出一缕缕热气！\n"NOR,me);
		message_vision(HIR "\n$N把左掌缓缓抬起，无声无息之际，手掌向$n的「"+HIY+xuedao+HIR+"」抓过去！\n"NOR,me,target);
		
		me->add_temp("apply/attack",j/3);
		me->add_temp("apply/damage",j/4);
		me->add_temp("apply/claw",j/4);
		me->set_temp("nxsz/ningxue",j);
		call_out("remove_effect",1,me,j/20);


        if (random(j) > (int)target->query_skill("parry",1)/3
			||random(me->query("combat_exp"))>target->query("combat_exp")/2)
		{
             message_vision(HIR"眼看$N的抓风离$n已经咫尺之遥，$n无法躲避，「"+HIY+xuedao+HIR+"」被你抓个正着。\n"NOR,me,target);
                 
                   target->receive_wound("qi",j*3,me);
                  target->receive_damage("qi",j*6,me);
                  target->apply_condition("nxsz_hurt",j/8);
				  target->add_busy(2);
                 // message_vision(msg, me, target);
                  COMBAT_D->report_status(target);

         } else {
             message_vision(CYN"\n$n早有防备，一个鹞子翻身侧身躲过$N的抓风，但$N毫不留情，趁前冲之势，向$n继续攻击！\n"NOR,me,target);
                // message_vision(msg, me, target);
                 me->set_temp("nxsz_pfm",1);
                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                 me->delete_temp("nxsz_pfm");
         }               

         me->add("neili", -500);
        // me->start_busy(2+random(2));
         
       //  me->start_perform(2+random(4),"「凝血诀」");
         return 1;
 }
 


int remove_effect(object me,int count)
{
	int j;
	if (!me) return 0;
	j=me->query_temp("nxsz/ningxue");
	
	if (count<0
		||!me->is_fighting()
		||me->query_skill_mapped("claw")!="ningxue-shenzhua"
		||me->query_skill_prepared("claw")!="ningxue-shenzhua")
	{

		me->add_temp("apply/attack",-j/3);
		me->add_temp("apply/damage",-j/4);
		me->add_temp("apply/claw",-j/4);
		me->delete_temp("nxsz/ningxue");
		message_vision(HBWHT+HIR"$N双手凝血劲一松，双脸瞬间由红转变为煞白！\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me,count--);
}

int help(object me)
{
   write(WHT"\n凝血神爪「"RED"凝血诀"WHT"」："NOR"\n");
   write(@HELP
	「凝血神爪」是天地会总舵主陈近南最得意的成名武艺。传言中，
	凡中此神爪之人，三天后全身血液会慢慢凝结变成浆糊一般，无药
	可治。凝血诀最大的功效是提升自身凝血神爪的攻击威力，且让对
	方受暗伤。
	
	指令：perform claw.ningxue

要求：
	当前内力 1500 以上；
	最大内力 2000 以上； 
	后天身法 30 以上； 
	凝血神爪等级 150 以上；
	有效内功等级 200 以上；
	激发爪法为凝血神爪；
	激发招架为凝血神爪；
	备爪法且手无兵器。

HELP
   );
   return 1;
}
