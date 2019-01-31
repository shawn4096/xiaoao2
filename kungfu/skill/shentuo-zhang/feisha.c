// This program is a part of NITAN MudLIB
// hama.c 蛤蟆功

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int damage, p, ap, dp;
        string msg, dodge_skill;

      //  if (userp(me) && ! me->query("can_perform/hamagong/hama"))
        //        return notify_fail("你还没有受过高人指点，无法施展「驼溅飞沙」。\n");

        if (! target) target = offensive_target(me);

        if (! target || !target->is_character() || 
            ! me->is_fighting(target) || 
            ! living(target))
                return notify_fail("驼溅飞沙绝招只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("hamagong", 1) < 250)
                return notify_fail("你的蛤蟆功还不够熟练，不能使用驼溅飞沙对敌！\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必须空手才能使用「驼溅飞沙」！\n");

        if (me->query_skill_mapped("force") != "hamagong")
                return notify_fail("你的内功中无此功夫。\n");

        if (me->query_skill_prepared("strike") != "shentuo-zhang" ||
            me->query_skill_mapped("strike") != "shentuo-zhang")
                return notify_fail("你必须先将神驼掌运用于掌法之中才行。\n");

        if ((int)me->query("max_neili") < 2500)
                return notify_fail("你现在最大内力不足，使不出神驼掌的绝招驼溅飞沙！\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("你现在真气不足，使不出神驼掌的绝招驼溅飞沙！\n");

        if ((int)me->query_skill("strike", 1) < 250)
                return notify_fail("你的掌法不够娴熟，使不出神驼掌的绝招驼溅飞沙！\n");

        if (me->query_str() < 30 )
                return notify_fail("你的力量太小，使不出用神驼掌绝招驼溅飞沙！\n");

        msg = YEL "\n$N"YEL"身子蹲下，左掌平推而出，劲气纵横，凛冽如风，使的正是$N生平最得意的「驼溅飞沙」绝招，掌风直逼$n而去！\n"NOR;

        ap = me->query_skill("shentuo-zhang",1);
        dp = target->query_skill("parry",1);

        if (ap / 2 + random(ap) > dp
			||random(me->query_str(1))>target->query_str(1)/2)
        {
                
                        
                me->add("neili", -200);
                
                damage = me->query_skill("shentuo-zhang",1)*me->query_str(1)/10;          
                
				if (me->query("neili") > random(target->query("neili")))
                        damage += random(damage);
                        
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                
                p = (int)target->query("eff_qi")*100/(int)target->query("max_qi");
                msg += COMBAT_D->damage_msg(damage, "内伤");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                call_out("perform2", 1, me, target, p, damage);    
        } else
        {
                                      
                me->add("neili", -100);
                tell_object(target, HIY"你但觉一股微风扑面而来，风势虽然不劲，然已逼得自己呼吸不畅，知道不妙，连忙跃开数尺。\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
		 me->add("jingli", -200);
		me->start_perform(4,"驼溅飞沙");
        return 1;
}


int perform2(object me, object target, int p, int damage)
{
        int ap, dp;
        string msg, dodge_skill;

        if( !target || !me || !living(me)
           || !me->is_fighting(target) 
           || environment(target)!=environment(me) || !living(target))
                return 0;

        if( (int)me->query("neili", 1) < 500 )
                return notify_fail("你待要再发一掌，却发现自己的内力不够了！\n");

        msg = HIR "\n$N左掌劲力未消，右掌也跟着推出，功力相叠，「驼溅飞沙」掌风排山倒海般涌向$n！\n"NOR;

        ap = me->query_skill("shentuo-zhang",1);
        dp = target->query_skill("parry",1);

     if (ap / 2 + random(ap) > dp
			||random(me->query_str(1))>target->query_str(1)/2)
        {
             
                me->add("neili", -300);
                damage = me->query_skill("shentuo-zhang",1)*me->query_str(1)/10;          

                if (me->query("neili") > random(target->query("neili")))
                        damage += random(damage);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += COMBAT_D->damage_msg(damage, "内伤");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";                
                call_out("perform3", 1, me, target, p, damage);  
        }
       else
        {
            
                me->add("neili", -200);
                tell_object(target, HIY"你喘息未定，又觉一股劲风扑面而来，连忙跃开数尺，狼狈地避开。\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
		me->add("jingli", -200);
		me->start_perform(4,"驼溅飞沙");
        return 1;
}

int perform3(object me, object target, int p, int damage)
{
        int ap, dp;
        string msg, dodge_skill;

        if(! target || ! me || environment(me) != environment(target)) return 1;
        if(!living(target))
              return notify_fail("对手已经不能再战斗了。\n");

        if( (int)me->query("neili", 1) < 700 )
                return notify_fail("你待要再发一掌，却发现自己的内力不够了！\n");

        msg = HBYEL+HIR "\n$N双腿一登，双掌相并向前猛力推出，$n连同身前方圆三丈全在「驼溅飞沙」劲力笼罩之下！\n"NOR;
       
		ap = me->query_skill("shentuo-zhang",1);
        dp = target->query_skill("parry",1);

		if (ap / 2 + random(ap) > dp
			||random(me->query_str(1))>target->query_str(1)/2)
        {
            
                me->add("neili", -400);
				damage = me->query_skill("shentuo-zhang",1)*me->query_str(1)/10;         
                if (me->query("neili") > random(target->query("neili")))
                        damage += random(damage) * 2;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p = (int)target->query("eff_qi")*100/(int)target->query("max_qi");
                msg += COMBAT_D->damage_msg(damage, "瘀伤");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";   
        } else
        {
         
                me->add("neili", -300);
                target->add("jingli", -100);
                tell_object(target, HIY"你用尽全身力量向右一纵一滚，摇摇欲倒地站了起来，但总算躲开了这致命的一击！\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }

        message_vision(msg, me, target);
		me->add("jingli", -200);
		me->start_perform(4,"驼溅飞沙");
        return 1;
}


string perform_name(){ return HIW"驼溅飞沙"NOR; }

int help(object me)
{
	write(HIC"\n神驼雪山掌之「驼溅飞沙」："NOR"\n");
	write(@HELP
	神陀雪山掌乃是白驼山庄主任欧阳锋的独门绝技，既有
	神陀的雄俊之态，又有雪山阴柔之气。施展过程中，刚
	猛异常。因白驼山庄以养蛇和蛤蟆，所以掌法中蕴含蛇
	毒与蛤蟆毒。
	驼溅飞沙是宛如群驼在沙漠中飞溅之态，连出数招攻敌
	
	指令：perform strike.shentuo

要求：
	当前精力的需求 1000 以上；
	当前内力的需求 1000 以上；
	神驼雪山掌等级 250 以上；
	蛤蟆功等级     250 以上；
	基本掌法的等级 250 以上；
	后天臂力大于   60  以上；
	激发掌法为神驼雪山掌；
	激发内功为蛤蟆功
	空手且备用；
HELP
	);
	return 1;
}

