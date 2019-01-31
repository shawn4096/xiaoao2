// bibo.c 碧波掌
//桃花岛初期武功
//by sohu@xojh

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

string perform_name() { return HIC"碧波掌"NOR; }

int perform(object me, object target)
{
        int damage, p;
        string msg;
        
        if (!target) target = offensive_target(me);
        if (!objectp(target)) return notify_fail("你想劈谁？\n");
        if (wiz_level(me) < wiz_level(target))
                return notify_fail("你不能攻击巫师等级比你高的对手。\n");
        if (target == me)
                return notify_fail("用 suicide -f 指令会比较快些。\n");
         if( target->is_corpse() ) 
                return notify_fail("有个性，玩尸体。\n");
        if (!target || !target->is_character())
                return notify_fail("你想攻击谁？\n");
        if (me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用碧波掌！\n");   
        if (environment(me)->query("no_fight") )
                return notify_fail("这里不能战斗。\n");
        if ((int)me->query_dex() < 35)
                return notify_fail("你的身法不够，无法配合碧波掌。\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 100 )
                return notify_fail("你的碧海潮生功修为未到，无法打出碧波掌。\n");
        if ((int)me->query_skill("luoying-zhang",1) < 100 )
                return notify_fail("你的掌法修为不足，使不出碧波掌。\n");
        if ((int)me->query("max_neili") < 1500)
                return notify_fail("你现在内力太弱，不能打出碧波掌。\n");
       // if ((int)me->query("jiali") < 100)
                //return notify_fail("你现在加力太弱，不能打出碧波掌。\n");
        if (me->query_skill_prepared("strike") != "luoying-zhang" 
			|| me->query_skill_mapped("strike") != "luoying-zhang")
                return notify_fail("你准备的技巧不对！\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("你激发的内功不对！\n");
	

        msg = HIW "\n$N双手挥舞，宛如碧波万顷，其势极缓，但其劲气却甚是勇猛，是桃花岛"HIC"「碧波掌」"HIW"绝技！\n"NOR;
        if (random(me->query_dex()) > target->query_dex()/2
			||random(me->query_skill("luoying-zhang",1))>target->query_skill("parry",1)/3)
        {
                             
                damage = (int)me->query_skill("force",1) + (int)me->query_skill("strike",1) + me->query("jiali")*5;
                
				if (damage > 3500 + me->query("thd/is_fast")*3) damage = 3500 + me->query("thd/is_fast")*3;
			
                if (target->query("neili") < me->query("neili")) damage *= 2;
               // if (me->is_fighting()) damage *= 3/4;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                me->add("neili", -damage/10);
                if (me->query("neili") < 0) me->set("neili",0);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += HBCYN+HIB"$n一时不查，胸口为这一碧波掌暗劲打中，如中锤击！\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
				target->add_busy(1+random(1));
				//me->add_temp("apply/attack",me->query_skill("luoying-zhang",1)/3);
              //  me->add_temp("apply/damage",me->query_skill("luoying-zhang",1)/5);
			//	COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
			//	me->add_temp("apply/attack",-me->query_skill("luoying-zhang",1)/3);
             //   me->add_temp("apply/damage",-me->query_skill("luoying-zhang",1)/5);
				if (objectp(target)&&me->is_fighting())
				{
					call_out("do_pikong",1+random(3),me,target);
				}
				//me->start_busy(1);
               // me->kill_ob(target);
        }
        else {
                msg += CYN"$n见掌势猛烈，急忙向旁一让，$N这一掌便即落空。\n"NOR;
				me->start_busy(1);
        }
		
		me->start_perform(2,"碧波掌");
		me->add("neili",-150);
		me->add("jingli",-100);
        message_vision(msg, me, target);
        return 1;
}
int do_pikong(object me,object target)
{
	if (!me||!target) return 0;

	message_vision(HIC"$N一波未平一波又起，$n只觉两股暗劲陆续涌来，忍不住又倒退数步！\n"NOR,me,target);
	me->add_temp("apply/attack",me->query_skill("luoying-zhang",1)/3);
    me->add_temp("apply/damage",me->query_skill("luoying-zhang",1)/5);
	me->set_temp("lyz/bibo",1);
	COMBAT_D->do_attack(me, target, 0, random(3)?3:1);
	COMBAT_D->do_attack(me, target, 0, random(3)?3:1);
	me->delete_temp("lyz/bibo");
	me->add_temp("apply/attack",-me->query_skill("luoying-zhang",1)/3);
    me->add_temp("apply/damage",-me->query_skill("luoying-zhang",1)/5);
	return 1;
}
int help(object me)
{
        write(HIG"\n落英神剑掌之「碧波掌」："NOR"\n");
        write(@HELP

	碧波掌乃是桃花岛入门武功，掌法施展出
	来宛如碧波汪洋，绵绵不绝，桃花岛武功
	以阴柔见长，若配合高超的身法，则此招
	威力不容小觑。

	使用指令：perform strike.bibo

要求：
	碧海潮生功等级 100 以上；
	落英神剑掌等级 100 以上；
	后天身法要求为 35  以上；
	最大内力要求为 1500 以上；
	激发且备掌法落英神剑掌；
	激发内功碧海潮生；
	空手；
HELP
        );
        return 1;
}

