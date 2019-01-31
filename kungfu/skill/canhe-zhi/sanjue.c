//三绝指 cre by sohu@xojh
//第一招 金刚指力
//第二招 多罗叶指
//第三招 拈花指

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int i);
int next2(object me, object target, int i);

int perform(object me,object target)
{
        object weapon;
        string msg;
        int ap,dp;
        int i = me->query_skill("finger",1) / 2 + me->query_skill("canhe-zhi",1) /2 ;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("「三绝指」只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("你的内功不是先天功，无法使用「三绝指」！\n");

        if(!me->query("quest/mr/canhe/sanjue/pass"))
                return notify_fail("你虽然听说过「三绝指」绝技，但是一直没有领悟其中诀窍，还不会运用！\n");

        if( me->query_skill("shenyuan-gong", 1) < 500 )
                return notify_fail("你的内功还未练成，不能使用「三绝指」！\n");

        if( me->query_skill("canhe-zhi", 1) < 500 )
                return notify_fail("你的指法还未练成，不能使用「三绝指」！\n");

        if (me->query_temp("weapon"))
                return notify_fail("你手里有武器，无法使用「三绝指」！\n");
   
        if (me->query_skill_prepared("finger") != "canhe-zhi"
            || me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("你没有激发并使用参合指法，现在无法使用「「三绝指」」进行攻击。\n");  

        if(me->query_skill_mapped("parry") != "canhe-zhi"
        && me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("你的招架功夫不对，无法使用「三绝指」！\n");

        if(me->query("max_neili") < 3500 )
                return notify_fail("你的内力修为不够，不能使用「三绝指」！\n");
        if(me->query("neili") < 1000 )
                return notify_fail("你现在真气不足，不能使用「三绝指」！\n");
        if(me->query("jingli") < 600 )
                return notify_fail("你现在精力不足，不能使用「三绝指」！\n");
        if(me->query_temp("chz/sanjue"))
                return notify_fail("你正在使用「三绝指」！\n");

        if(me->query_skill("finger", 1) < 500 )
                return notify_fail("你的基本指法不够娴熟，不能在剑招中使用「三绝指」。\n");


        msg = HBRED"\n$N使出慕容氏家传武技参合指，连续施展出三招不同指法绝技，各自不同，正是参合指绝技「三绝指」！\n"NOR;
		msg+=HIR"$N不偏不倚，抬指便刺，内力激发下“嗤”的一声，正是少林绝技"+HIW+"「金刚指」"+HIR+"力！\n"NOR;
              message_vision(msg, me, target);
		
        me->start_perform(3, "「三绝指」");
        
		me->add_temp("apply/attack", me->query_skill("canhe-zhi") /4);

		me->add_temp("apply/damage", me->query_skill("canhe-zhi") /4);
        me->set_temp("chz/sanjue", 1);
             
        //第一招攻击金刚指
        if (me->is_fighting(target))
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("canhe-zhi") /4);
		
me->add_temp("apply/damage", -me->query_skill("canhe-zhi") /4);

        me->add("neili", -150);

        if ( me->query_skill("canhe-zhi", 1) > 500)
                next1(me, target, i);
        else 
                me->delete_temp("chz/sanjue");
        return 1;
}

int next1(object me, object target, int i)

{
        string msg;
        int damage, ap,dp;
        object weapon;

        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("chz/sanjue");
                return 0;
        }
        msg = HIR"\n紧跟着$N双手合十，微微一笑，颇得拈花之意，轻轻一指，一缕罡气电射而出，袭向$n胸前。\n"NOR;
		msg+=HIC"正是少林七十二绝技中极为阴柔的功夫"+HIR+"「拈花指」！\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_con(1)/100000;
        dp = target->query("combat_exp", 1) * target->query_con(1)/100000;
        
		if((userp(target)&& random(ap + dp) > dp )|| !userp(target)){
                msg += HIB"$n只觉一股阴柔的柔劲进入自己的经脉，东窜西突。\n"NOR;
                damage = me->query_skill("canhe-zhi",1)*3;

				damage += me->query_skill("finger")*3;
				
damage += random(damage);
        if ( damage > 2000 )
				damage = 2000 + (damage - 2000)/100;

		if(damage>= target->query("qi")) damage= target->query("qi")-1;

           target->add("neili",-(300+random(150)));
           target->receive_damage("qi", damage, me);
        if(userp(me) && me->query("env/damage"))
        	tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
		
        
			target->receive_wound("qi", damage/3, me);
            msg += damage_msg(damage, "内伤");
            message_vision(msg, me, target);
            COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("canhe-zhi") /4);

		me->add_temp("apply/damage", me->query_skill("canhe-zhi") /4);

        if(!random(3))
			target->add_condition("no_perform", 1);
        if(!random(3))
			target->add_condition("no_exert", 1);
        if(!userp(target))    target->add_busy(2);
        if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack", -me->query_skill("canhe-zhi") /4);

		me->add_temp("apply/damage", -me->query_skill("canhe-zhi") /4);

                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "「三绝指」");
        }
        else {
                msg  += CYN"\n$n一个横向纵跃，危急之中躲过致命一击。\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
        if (me->query_skill("canhe-zhi", 1) > 450 && objectp(target))
                next2(me, target, i);
        else
                me->delete_temp("chz/sanjue");
        return 1;
}

int next2(object me, object target, int i)
{
        string msg;
        int damage, ap, dp;
        object weapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("chz/sanjue");
                return 0;
        }

        msg = HIY"\n$n急运内功摆脱之际，$N指力又化为多罗叶指之势，指力弥漫，招招指向$n的周身大穴！\n"NOR;
        ap = me->query("combat_exp") * me->query_str(1)/100000;
        dp = target->query("combat_exp") * target->query_str(1)/100000;
		//100000降低ap,dp，以防溢出 by sohu@xojh
       if(objectp(target)&&((userp(target)&& random(ap + dp) > dp) || !userp(target))){

                    damage = me->query_skill("canhe-zhi",1)*3;

					damage += me->query_skill("finger",1)*3;

					damage += random(damage);
                if ( damage > 3000 )
					damage = 3000 + (damage - 3000)/100;
				//if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;

            
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                
				msg += damage_msg(damage, "瘀伤");
                message_vision(msg, me, target);

        if(objectp(target) && me->query("env/damage"))
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
		//
if(userp(target)&& target->query("env/damage"))
			//tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
		
COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", (int)me->query_skill("shenyuan-gong") /4);

		me->add_temp("apply/damage", (int)me->query_skill("shenyuan-gong") /4);
        if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -(int)me->query_skill("shenyuan-gong") /4);

	    me->add_temp("apply/damage", -(int)me->query_skill("shenyuan-gong") /4);
                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"「三绝指」");
				
        } 
        else {
                msg = msg + HIW "$n一个铁板桥，反身仰倒，堪堪避过。\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("chz/sanjue");
        return 1;
}



string perform_name(){ return HIG"三绝指"NOR; }
int help(object me)
{
        write(HIG"\n参合指法之"+RED"「三绝指」："NOR"\n\n");
        write(@HELP
	参合指是南慕容氏的绝学，参商相隔，斗转星移，是南慕容
	家传的绝世武技，参合指以强大的内力将内力激发出来，和
	对方搏斗，若习得参合指的绝世秘籍，并不弱与天下其他门
	派的指法绝技。
	三绝指是连续出三指，均为少林指法之精华，第一招为大力
	金刚指，第二招为拈花指，第三招为多罗叶指。乃是慕容氏
	演习天下武功的精粹招式。

指令：perform finger.sanjue

要求：
	当前内力 1000 以上；
	最大内力 8000 以上；
	参合指等级 500 以上；
	神元功等级 500 以上；
	激发指法为参合指；
	招架为参合指或斗转星移
	备指法为参合指；
	且手无兵器,

HELP
        );
        return 1;
}
