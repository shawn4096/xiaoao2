// by darken@SJ

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;
string perform_name(){ return HIC"燃字诀"NOR; }

int perform(object me)
{
        string msg;
        object target;
        int hs, ls,hit_qi,p,damage,damaged;

       
        hs = me->query_skill("huoyan-dao",1);
        ls = me->query_skill("longxiang-boruo",1);
        if( !target ) target = offensive_target(me);

        if( !target 
         || !me->is_fighting(target)
         || !objectp(target)
         || environment(target)!= environment(me))
		 return notify_fail("「燃」只能在战斗中对对手使用。\n");
     
        if (objectp(me->query_temp("weapon")))
                return notify_fail("你只能空手运用「燃」的绝技。\n");
        if( hs < 350)
                return notify_fail("你的「火焰刀」等级不够, 不能使出「燃」的绝技！\n");
        if( ls < 350)
                return notify_fail("你的「龙象般若功」功力不够, 不能使出「燃」的绝技！\n");
        if( me->query("neili") < 1000 )
                return notify_fail("你的内力即将用尽，发不出「燃」了！\n");
        if( me->query("jingli") < 1000 )
                return notify_fail("你的精力即将用尽，发不出「燃」了！\n");
        if( me->query("max_neili") < 4500 )
                return notify_fail("你的内力不够，不能催动内力发出「燃」绝技！\n");
        if( me->query_skill_mapped("strike") != "huoyan-dao"
         || me->query_skill_prepared("strike") != "huoyan-dao")
                return notify_fail("你必须使用「火焰刀」，才能使出「燃」的绝技！\n");
        if( me->query_skill_mapped("force") != "longxiang-boruo")
                return notify_fail("你现在所使用的内功同「龙象般若功」向抵触，不能使出「燃」的绝技！\n");
 
        msg = HIR "\n$N双掌急速搓动，猛然间轻喝一声，丹田气涌动，双掌分使间挟著二股热气向$n击出！\n"NOR;
       // if (me->query_temp("honglian/lianxu") && me->query("neili")>target->query("neili")*2/3)
		if (random(me->query("neili"))>target->query("neili")/2
			||random(me->query_skill("strike",1))>target->query_skill("parry",1)/2)
        { 
           msg += RED "$N暴喝一声，聚集的真气汹涌而出，带着热浪的真气如排山倒海般冲击$n\n"+
           HIW "$n不停的痛苦挣扎着，但是$N已臻大成的"HIY"龙象般若功"HIW"一阵接着一阵，一个不慎，内息大乱！\n"NOR;
           damage =  8 * ((int)me->query_skill("huoyan-dao", 1)+(int)me->query_skill("longxiang-boruo", 1));
           damage = damage  + random(damage);
		   if (me->query_temp("hyd/power"))
		   {
			   if (damage>6000) damage=6000+(damage-6000)/10;
		   }
		   else if (damage>4000) damage=4000+(damage-4000)/100;
		   if(userp(me) && me->query("env/damage")) 
	             tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
           me->add("neili", -300);
           me->add("jingli",-100);
		   if (target->query("qi")<damage)
			   damage=target->query("qi")-100;
		    
           target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage/2,me);
           msg += "( $n"+eff_status_msg(p)+" )\n";
           target->set_temp("last_damage_from", "被"+me->query("name")+"杀");
           
		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
           //me->delete_temp("honglian/lianxu");
        }
        else if(random(me->query_skill("force",1)) >  target->query_skill("force",1)*2/5){
                msg+= RED "$n为$N强大的内功所迫，当即中招，只觉得全身燥热，内息顿时乱冲！\n"NOR;
                target->add("qi", -target->query("qi")*(ls+hs)/2000);
                //target->set("eff_qi", target->query("eff_qi")*(ls+hs)/2000);
                target->add("neili", -target->query("neili")*(ls+hs)/2000);
				target->apply_condition("no_exert",(me->query_skill("huoyan-dao,1")/100+random(5)));
			    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                target->start_busy(2);
                me->add("neili",-400);
        } 
        else {
                msg += HIY "$n内功亦是极为了得，运起全身功力，硬是将此股热气反击回来。\n" NOR;
                msg+= HIR "$N只觉得全身燥热，内息乱冲！"NOR;
                me->set("qi", target->query("qi")*(ls+hs)/1000);
                me->set("eff_qi", target->query("eff_qi")*(ls+hs)/1000);
                me->add("neili",-400);
                target->add("neili",-800);
                target->start_busy(2);
        }

        if (me->query_skill("huoyan-dao",1)<449
			|| me->query_skill("longxiang-boruo",1)<449) 
		{
			me->start_perform(4, "燃字诀");
		}
        else 
        {
        	me->start_perform(3,"燃字诀");
		}       //设置个小飞跃，450以后pfmbusy略减
        
        message_vision(msg, me, target);
        return 1;
}

int help(object me)
{
	write(HIY"\n火焰刀秘技「燃字诀」："NOR"\n");
	write(@HELP
	火焰刀燃字诀是大轮寺成名绝技，是将火焰刀之真气攻击敌人之法，
	燃字诀乃是以深厚的功力夹带掌风中施展，非功力深厚者无法施展，
	一旦打中大方，可令对方内力或气血受到不同程度的损伤，注意若
	配合火焰刀另外一门绝技使用，则威力更甚。
	
	指令：perform strike.ran

要求：
	最大内力的需求 4500 以上；
	当前内力的需求 1000 以上；
	龙象般若功等级 350 以上；
	火焰刀等级需求 350 以上；
	基本内功的等级 350 以上；    
HELP
	);
	return 1;
 }
