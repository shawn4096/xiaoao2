//改编自snowman的sanhuan
//改编者:caiji
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int i = me->query_skill("zhuihun-gou", 1)/5;
        int j = me->query("jiali")/4 + 10;
        
        if( !target ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("「神形俱灭」只能对战斗中的对手使用。\n");
        if(me->query_temp("zhuihun/lpf"))
        return notify_fail("你正在使用「乱披风」。\n");
		if(me->query("xx/zhg/pass"))
           return notify_fail("你虽然听说过「追魂钩法」，但从并没有学会。\n");
        if( (int)me->query_skill("zhuihun-gou", 1) < 200 )
                return notify_fail("你的追魂钩功力太浅，别做梦了。\n");

        if( (int)me->query_skill("hook", 1) < 200 )
                return notify_fail("你的基本钩法功力太浅，别做梦了。\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 200 )
                return notify_fail("你的内功功力太浅，别做梦了。\n");
                
        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力太浅，别做梦了。\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够，别做梦了。\n");
        if (me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你用什么为内功基础来使「神形俱灭」?\n");
        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "hook"
            || me->query_skill_mapped("hook") != "zhuihun-gou")
                return notify_fail("你使得了「神形俱灭」么?\n");
                 
        me->add("neili", -150);
        me->add("jingli", -100);
        me->set_temp("zhuihun/jumie", 4); 
        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", j);
        message_vision(GRN "\n$N大喝一声「绝命」，身形贴近$n身侧，浑然不顾$N的招式伤害，一招递出.\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        if(me->is_fighting(target)){
        message_vision(YEL "\n$N神情萧索宛如丧子，反手一钩，双钩并举，紧跟着发出第二招「落魄」！\n"NOR,me);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        }
        if(me->is_fighting(target)&&(int)me->query_skill("zhuihun-gou", 1) >= 140){
        message_vision(RED "\n$N双手挥舞兵器，凌空一劈，第三式「夺魂」随后而至，令$n"RED"措手不及！\n"NOR,me,target);
        me->add("neili", -50);
		target->add_busy(1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);        
        }
        if(me->is_fighting(target)&&random(me->query("combat_exp"))>target->query("combat_exp")/2
        && (int)me->query_skill("zhuihun-gou", 1) >= 180){
        message_vision(MAG "\n$N身行晃动，最后一式「屠灵」劲道凌厉非常！\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);   
        me->add("neili", -80);
        }
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/damage", -j);   
        me->start_busy(1);
        me->delete_temp("zhuihun/jumie"); 
        me->start_perform(4, "「神形俱灭」");
        return 1;
}

string perform_name(){ return HIG"神形俱灭"NOR; }

int help(object me)
{
        write(HIM"\n追魂钩法之「神形俱灭」："NOR"\n");
        write(@HELP
	追魂钩法是星宿派的不传之秘，有追魂夺命之称
	若配合星宿派独门武功化功大法，则该武功的阴
	险、毒辣特点就发挥玲离尽致。
	神形俱灭是不要命的打法，利用摘星功的轻便优
	势，瞬间出四招，招招狠毒夺命。
		
	指令：perform hook.jumie
		
要求：
	最大内力要求 1000 以上；      
	当前内力要求 500 以上；
	化功大法等级 200 以上；
	追魂钩法等级 200 以上；
	基本钩法等级 200 以上；
	激发钩法和招架为追魂钩法；
	激发内功为化功大法；
	手持钩类兵器。
	            
                
HELP
        );
        return 1;
}
