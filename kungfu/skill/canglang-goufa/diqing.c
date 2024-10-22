// diqing.c 狄青降龙
// created by Olives@SJ
// Update By lsxk@hsbbs 2007/6/6

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIY"狄青降龙"NOR;}

void back(object target);

int perform(object me, object target)
{
        int skill,ap,pp,time;
        object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用。\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("「狄青降龙」只有拜了教主后才能用！\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 200 )
                return notify_fail("你的腾龙匕法不够娴熟，不会使用狄青降龙。\n");

        if( (int)me->query_skill("hook", 1) < 200 )
                return notify_fail("你的基本钩法不够娴熟，不会使用狄青降龙。\n");
		if(!weapon || weapon->query("skill_type")!="hook" )
                return notify_fail("你现在无法使用狄青降龙。\n");
        if( (int)me->query_skill("dulong-dafa", 1) < 200 )
                return notify_fail("你的毒龙大法不够娴熟，不会使用狄青降龙。\n");

    	if( (int)me->query("neili", 1) < 800 )
       		return notify_fail("你现在内力不足！\n");
       	if( (int)me->query("jingli", 1) < 500 )
       		return notify_fail("你现在精力不足！\n");

    	if( (int)me->query("max_neili", 1) < 1500 )
       		return notify_fail("你内力修为不足！\n");
        if( (int)me->query_str() < 50  )
                return notify_fail("你的臂力太低，不能使用狄青降龙。\n");
        if (me->query_skill_mapped("hook") != "canglang-goufa"
			||me->query_skill_mapped("parry") != "canglang-goufa")
                return notify_fail("你所使用的武技不对，现在无法使用狄青降龙。\n");
		if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你激发内功不对，现在无法使用狄青降龙。\n");

        if (!weapon
			||weapon->query("skill_type")!="hook")
                return notify_fail("你现在无法使用狄青降龙。\n");

        if(target->query_temp("clgf/diqing")
        || target->query_temp("block_msg/all"))
                return notify_fail("他的眼睛已经瞎了，不必再用狄青降龙了！\n");
        if (me->query_temp("clgf/diqing"))
				return notify_fail("他方才刚用过狄青降龙了！\n");
		skill = (int)me->query_skill("canglang-goufa", 1);

	    ap = COMBAT_D->skill_power(me,"dagger",SKILL_USAGE_ATTACK);
        pp = COMBAT_D->skill_power(me,"parry",SKILL_USAGE_ATTACK);
        if(target->is_busy())
        	pp /= 2;
        if (me->query("gender")=="男性")
           ap=ap+skill;
        me->add("neili", -350);
        me->add("jingli", -200);
        message_vision(HIY "\n$N左手握钩，右手使出一招「狄青降龙」，背脊后撞，十指向$n胸口虚抓，乘其避让之际，突然一个倒翻斛斗，\n"
							+"身子跃起，双腿一分，跨坐在$n肩头，同时双手拇指压住$n太阳穴，食指按眉，中指按眼。\n"NOR,me,target);

        message_vision(HIY"$n大吃一惊，匆忙中下意识地双臂回转，想护住双眼！\n"NOR, me, target);;

 	   if(random(ap+pp)>pp
		||random(me->query_str(1))>target->query_str(1)/2)
       {
                message_vision(HIR"\n只听$n惨叫一声，$N的两支手指已经插入$n的眼眶，只见$n的眼角鲜血直流！\n"NOR, me, target);
                if (!target->query_temp("clgf/diqing"))
                {
					target->add_temp("apply/attack", - skill/3);
					target->add_temp("apply/defense", -skill/3);
					target->add_temp("apply/parry", -skill/3);
					target->set_temp("block_msg/all",1);
					target->set_temp("clgf/diqing",skill);
					time = 3+skill/10;
					if(time>60) time = 60;
					call_out("back", time, target);

                }

                target->receive_damage("qi", skill*5,me);
                target->receive_wound("qi", skill*5/2,me);
                if(userp(me) && me->query("env/damage"))  
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ skill*5+ WHT"点攻击伤害。\n"NOR); 
                if(userp(target)&& target->query("env/damage"))  
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ skill*5+ WHT"点伤害。\n"NOR);
				COMBAT_D->report_status(target);
                target->kill_ob(me);
                me->start_perform(3,"狄青降龙");
        }
		 else {
                message_vision(HIY"$n抱头缩颈一个滚翻，总算躲开了$N这一招。\n"NOR, me, target);
                if((int)me->query_skill("canglang-goufa",1)>150){
                  message_vision(HIR"\n$N哪肯就此罢休？连忙飞身上前一阵强攻，$n顿觉几股劲风袭来!\n"NOR, me, target);
                  me->add_temp("apply/damage",skill/5);
                  me->set_temp("clgf/diqing",1);
                  COMBAT_D->do_attack(me,target,weapon,1);
                  COMBAT_D->do_attack(me,target,weapon,2);
                  COMBAT_D->do_attack(me,target,weapon,3);
                  me->delete_temp("clgf/diqing");
                  me->add_temp("apply/damage",-skill/5);
                }
                me->start_perform(2+random(3),"狄青降龙");
                me->start_busy(2);
                target->kill_ob(me);
        }

        return 1;
}

void back(object target)
{
        int lvl;
        if(!target) return;
        lvl = target->query_temp("clgf/diqing");
        target->add_temp("apply/attack", lvl/3);
        target->add_temp("apply/defense", lvl/3);
		target->add_temp("apply/parry", lvl/3);
        target->set_temp("block_msg/all", 0);
        if(living(target))
              tell_object(target, HIW "啊！总算双目没有被抓瞎，你又可以看见事物啦！\n" NOR);
        target->delete_temp("clgf/diqing");
}

int help(object me)
{
   write(WHT"\n沧浪钩法之「"HIY"狄青降龙"WHT"」："NOR"\n");
   write(@HELP
	沧浪钩法乃是神龙岛主晚年后整理自己的所学武技
	后总体提炼出的一套钩法武技，去繁就简，诡异犀
	利，防不胜防，尤其对于臂力较大男弟子而言，更
	是非常实战的功夫。其中狄青降龙乃是典型的偷袭
	武技，既可以刺瞎对方的双眼，若没刺中，又可以
	连攻三招。端的是厉害非常。
	  
	perform hook.diqing

要求：
	最大内力要求 1500 以上；
	当前内力要求 800 以上；
	当前精力要求 500 以上；
	沧浪钩法等级 200 以上；
	基本钩法等级 200 以上；
	毒龙大法等级 200 以上；
	当前臂力等级 50 以上；
	性别需求 男性。
HELP
   );
   return 1;
}
