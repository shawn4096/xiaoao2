//create by sohu@xojh


#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int i);
int next2(object me, object target, int i);

int perform(object me,object target)
{
        object weapon;
        string msg;
        int ap,dp,damage;
        int i = me->query_skill("tiezhang-zhangfa",1);

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("「铁掌绝技」只能对战斗中的对手使用。\n");
        //非解密不得开
        if(!me->query("tiezhang/pass"))
                return notify_fail("你虽然听说过「铁掌绝技」，但是一直没有领悟其中诀窍，还不会运用！\n");

        if( me->query_skill("tiezhang-zhangfa", 1) < 450 )
                return notify_fail("你的铁掌掌法还未练成，不能使用「铁掌绝技」！\n");

        if( me->query_skill("strike", 1) < 450 )
                return notify_fail("你的基本掌法还未练成，不能使用「铁掌绝技」！\n");

        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("你手里有兵器，无法使用铁掌绝技！\n");
   
        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa")
                return notify_fail("你现在无法使用「铁掌绝技」进行攻击。\n");  

        if(me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("你的招架功夫不对，无法使用「铁掌绝技」！\n");

        if(me->query("max_neili") < 9000 )
                return notify_fail("你的内力修为不够，不能使用「铁掌绝技」！\n");
        if(me->query("neili") < 2500 )
                return notify_fail("你现在真气不足，不能使用「铁掌绝技」！\n");
        if(me->query("jingli") <2500 )
                return notify_fail("你现在精力不足，不能使用「铁掌绝技」！\n");
         if(me->query_temp("tz/tiezhang"))
                return notify_fail("你正在使用「铁掌绝技」！\n");
         damage=me->query_skill("tiezhang-zhangfa",1)+me->query_skill("strike",1)+me->query_skill("force",1);
		 damage=damage*me->query_str()/10+random(damage);
      
         msg = HBBLU"\n$N使出「铁掌绝技」绝招，忽然双掌平分，将毕生功力聚集于掌上，丝毫无任何花巧，平平的向$n慢慢推去！\n"NOR;
         

         me->start_perform(2, "「铁掌绝技」");
         me->add_temp("apply/attack", me->query_skill("tiezhang-zhangfa") /3);

		 me->add_temp("apply/damage", me->query_skill("tiezhang-zhangfa") /4);
         me->set_temp("tz/tiezhang", i);
             
      //第一招攻击打断骨头
		 if (random(me->query("str")) > target->query("str")/2 
			 ||random(me->query("combat_exp")) > target->query("combat_exp")/2 
			 ||random(me->query_dex(1)) > target->query_dex(1)/2 )
           {
			  msg+= HBBLU "$n感觉全身四周已全被这掌力封住，两股强力排山倒海般压了过来,只得硬碰硬挡下这一招。\n"NOR;
			  target->receive_damage("qi", damage,me);
			  target->receive_wound("qi", damage/2,me);
			  msg += HBRED"$n被$N这一掌打在手腕处，上臂骨传来一阵断裂声！显然受伤不轻。\n"NOR;
			  target->apply_condition("no_exert",1);
			
		  }else msg +=HBYEL"$n手上劲力勃发，虽然将$N的这一招抵消，但却不由得惊出一身冷汗。\n"NOR;
        message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("apply/attack", -me->query_skill("tiezhang-zhangfa") /3);
		
me->add_temp("apply/damage", -me->query_skill("tiezhang-zhangfa") /4);

        me->add("neili", -350);

        if ( me->query_skill("tiezhang-zhangfa", 1) > 349)
                next1(me, target, i);
        else 
                me->delete_temp("tz/tiezhang");
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
                me->delete_temp("tz/tiezhang");
                return 0;
        }
        msg = HBRED"\n紧跟着$N欺身近前，左掌拍出，右手成抓，同时袭到，两股强力排山倒海般压了过来。\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_con(1)/10000;
        dp = target->query("combat_exp", 1) * target->query_con(1)/10000;
        if((userp(target)&& random(ap + dp) > dp )|| !userp(target)){
                msg += HIC"$n已经看出，$N右手这一抓虽然凶猛，但远不及左掌那么一触即能制人死命。\n"NOR;
                damage = me->query_skill("tiezhang-zhangfa",1)*3;

				damage += me->query_skill("strike")*3;
				
damage += random(damage);
        if ( damage > 5000 )
				damage = 5000 + (damage - 1000)/10;

		if(damage>= target->query("qi",1) && target->query("qi",1)>100 ) damage= target->query("qi",1)-1;

                target->add("neili",-(300+random(150)));
                target->receive_damage("qi", damage, me);
       // if(userp(me) && me->query("env/damage"))
       // 	tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
		
       // if(userp(target)&& target->query("env/damage"))
		//	tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
		
        target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "内伤");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("tiezhang-zhangfa") /3);

		me->add_temp("apply/damage", me->query_skill("tiezhang-zhangfa") /4);

        if(random(3))
			target->add_condition("no_perform", 1);
        //if(random(3))
			//target->add_condition("no_exert", 1);
        if(!userp(target))    target->add_busy(2);
        
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("tiezhang-zhangfa") /3);

		me->add_temp("apply/damage", -me->query_skill("tiezhang-zhangfa") /4);

                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "「铁掌绝技」");
        }
        else {
                msg  += CYN"\n$n急忙退后逃避，危急之中躲过这致命一击。\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
		//me->start_perform(1, "「铁掌绝技」");
        if (me->query_skill("tiezhang-zhangfa", 1) > 449)
                next2(me, target, i);
        else
                me->delete_temp("tz/tiezhang");
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
                me->delete_temp("tz/tiezhang");
                return 0;
        }
        msg = HBMAG"\n就在$n疲于防守之际，$N猛然大喊一声，宛如晴空打了个霹雳！\n"+HIW"左掌刚猛无铸，右掌却缓慢之极，招式端的是精妙无比\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1);
        dp = target->query("combat_exp", 1) * target->query_str(1);
       if((userp(target)&& random(ap + dp) > dp )|| !userp(target)){

                    damage = me->query_skill("tiezhang-zhangfa",1)*3;

					damage += me->query_skill("strike",1)*3;

					damage += random(damage);
                if ( damage > 8000 )
					damage = 8000 + (damage - 1000)/10;
				//if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;

                target->add_temp("apply/attack", -target->query_skill("tiezhang-zhangfa",1));
                target->add_temp("apply/dodge",  -target->query_skill("tiezhang-zhangfa",1));
                target->add_temp("apply/parry", -target->query_skill("tiezhang-zhangfa",1));
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "瘀伤");

                message_vision(msg, me, target);
      //  if(userp(me) && me->query("env/damage"))
		//	tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
		
//if(userp(target)&& target->query("env/damage"))
			//tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
		
COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("tiezhang-zhangfa") /3);

		me->add_temp("apply/damage", me->query_skill("tiezhang-zhangfa") /4);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("tiezhang-zhangfa") /3);

	    me->add_temp("apply/damage", -me->query_skill("tiezhang-zhangfa") /4);
                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"「铁掌绝技」");
                call_out("back", 5 + random(me->query("jiali") / 20), target);
        } 
        else {
                msg = msg + HIW "$n一个旱地拔葱，跃起数丈，堪堪避过。\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("tz/tiezhang");
		 me->start_perform(4, "「铁掌绝技」");
        return 1;
}

void back(object target)
{
        if (!target) return;
        target->add_temp("apply/attack", target->query_skill("tiezhang-zhangfa",1));
        target->add_temp("apply/dodge", target->query_skill("tiezhang-zhangfa",1));
        target->add_temp("apply/parry", target->query_skill("tiezhang-zhangfa",1));
}

string perform_name(){ return HBRED+HIY"铁掌绝技"NOR; }
int help(object me)
{
        write(HIR"\n铁掌掌法之「铁掌绝技」："NOR"\n\n");
        write(@HELP 
	铁掌绝技乃该帮不传之秘，经由上代帮主上官剑南和当代帮主
	裘千仞的精雕细琢，已然大成。铁掌掌法继承了以往刚猛无铸
	的特点，同时又精妙绝伦，虽然霸道刚猛不及降龙十八掌，但
	招式却更加精妙。若配合水上漂或者特殊内功，那么铁掌的威
	力将彻底发挥出来。
	
	perform strike.tiezhang

要求：  
	当前内力需求 2500 以上；
	最大内力需求 9000 以上;
	当前精力需求 2500 以上；
	铁掌掌法等级 450 以上；
	基本内功等级 450 以上；
	基本掌法等级 450 以上；
	激发掌法为铁掌掌法；
	激发招架为铁掌掌法；
	激发内功不限。
HELP
        );
        return 1;
}
