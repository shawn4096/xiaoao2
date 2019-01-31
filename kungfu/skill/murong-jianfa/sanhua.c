// cred by sohu@sojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int i);
int next2(object me, object target, int i);

int perform(object me,object target)
{
        object weapon;
        string msg;
        int i = me->query_skill("murong-jianfa",1) / 4;
        int ap,dp;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("天女散花只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("你的内功不是神元功，无法使用天女散花！\n");

        if( me->query_skill("shenyuan-gong", 1) < 150 )
                return notify_fail("你的内功还未练成，不能使用天女散花！\n");

        if( me->query_skill("murong-jianfa", 1) < 150 )
                return notify_fail("你的剑法还未练成，不能使用天女散花！\n");

        if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "murong-jianfa")
                return notify_fail("你手里没有剑，无法使用天女散花！\n");

        if(me->query_skill_mapped("parry") != "murong-jianfa"
        && me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("你的招架功夫不对，无法使用天女散花！\n");
        if(me->query("max_neili") < 1500 )
                return notify_fail("你的内力修为不够，不能使用天女散花！\n");
        if(me->query("neili") < 500 )
                return notify_fail("你现在真气不足，不能使用天女散花！\n");
        if(me->query("jingli") < 600 )
                return notify_fail("你现在精力不足，不能使用天女散花！\n");
        if(me->query_temp("sanhua"))
                return notify_fail("你正在使用天女散花！\n");

        if(me->query_skill("sword", 1) < 150 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用天女散花。\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        message_vision(HIG"\n$N使出慕容剑法之「天女散花」，神元功力运转于"+weapon->query("name")+HIG"之上，剑尖幻出点点剑光直飞$n全身各大要穴。\n"NOR,me,target);
		//message_vision();
        
		me->start_perform(3, "「天女散花」");
        ap = me->query("combat_exp", 1)/100000;
        dp = target->query("combat_exp", 1)/100000; 
        i = random(i/8) + 3;
        if ( i > 5 ) i = 5;
        if( random(ap + dp ) > dp 
			||random(me->query_int(1))>target->query_int(1)/2 ) 
		{
                message_vision(MAG "$n忽然觉得有些眼花缭乱，一时不查结果被$N攻了个措手不及。\n" NOR,me,target);
                target->add_busy(i);
                me->set_temp("sanhua", 1);
                me->add("neili", -150);
        }
        else {
                me->add("neili", -80);
                message_vision(MAG "可是$n看破了$N的企图，并没有上当。\n" NOR,me,target);
                me->start_busy(random(2));
        }
       // message_vision(msg, me, target);
        if ( me->query_skill("murong-jianfa", 1) > 150)
                next1(me, target, i);
        else 
                me->delete_temp("sanhua");
        return 1;
}
int next1(object me, object target, int i)
{
        string msg;
        int damage, ap,dp;
        object weapon;

        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("sanhua");
                return 0;
        }
        msg = HIR"\n紧跟着$N剑锋一转，欺身近前，从不可思议的角度刺向$n的" + HIY"「命门穴」"HIR + "。\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1);
        dp = target->query("combat_exp", 1) * target->query_con(1);
        if( random(ap + dp) > dp ){
                msg += CYN"$n只觉全身真气由「命门穴」狂泻而出。\n"NOR;
                damage = me->query_skill("murong-jianfa",1);
                damage += me->query_skill("sword")* 3;
                damage += random(damage);
                if ( damage > 5000 )
                        damage = 5000 + (damage - 5000)/10;
                target->add("neili",-(300+random(150)));
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "刺伤");
                msg = replace_string(msg, "$w", weapon->name());
                msg = replace_string(msg, "$l", "「命门穴」");
                message_vision(msg, me, target);
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+damage+ WHT"点攻击伤害。\n"NOR);
				
if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+damage+ WHT"点伤害。\n"NOR);

				COMBAT_D->report_status(target, random(2));
                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "「天女散花」");
        }
        else {
                msg  += CYN"$n一个懒驴打滚，危急之中躲过致命一击。\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
        if (me->query_skill("murong-jianfa", 1) > 200)
                next2(me, target, i);
        else
                me->delete_temp("sanhua");
        return 1;
}
int next2(object me, object target, int i)
{
        string msg;
        int damage, ap, dp;
        object weapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
        if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("sanhua");
                return 0;
        }
        msg = HIC"\n就在$n疲于防守之际，$N又运起神元功，风驰电掣地刺出第三剑。\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1);
        dp = target->query("combat_exp", 1) * target->query_dex(1);
        if( random(ap + dp) > dp ) {
                msg += HIW "结果一剑正刺中$n的" + HIR"「檀中穴」"HIW + "。\n"NOR;
                damage = me->query_skill("murong-jianfa",1);
                damage += me->query_skill("sword",1);
				damage *=3;
                damage += random(damage);
                if ( damage > 8000 )
                        damage = 8000 + (damage - 8000)/100;
                target->add_temp("apply/attack", 80);
                target->add_temp("apply/dodge", 80);
                target->add_temp("apply/parry", 80);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "刺伤");
                msg = replace_string(msg, "$w", weapon->name());
                msg = replace_string(msg, "$l", "「檀中穴」");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));
                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"「天女散花」");
                call_out("back", 5 + random(me->query("jiali") / 20), target);
        } 
        else {
                msg = msg + HIW "$n一个旱地拔葱，跃起数丈，堪堪避过。\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("sanhua");
        return 1;
}

void back(object target)
{
        if (!target) return;
        target->add_temp("apply/attack", -80);
        target->add_temp("apply/dodge", -80);
        target->add_temp("apply/parry", -80);
}

string perform_name(){ return HIG"天女散花"NOR; }
int help(object me)
{
        write(HIG"\n慕容剑法之"+HIR"「天女散花」"NOR"\n\n");
        write(@HELP
	慕容剑法乃是南慕容武技中的精华招式，非核心弟子不传
	其剑法特点是兼容并包，融合天下剑法所长，但又别出心
	裁，与众不同。尤其是以慕容家传内功支持，则为例又更
	上一层楼。剑中夹杂指法，若解开斗转星移绝世武技，威
	力更上一层楼。

指令：perform sword.sanhua

要求：  
	当前内力需求 500 以上；
	最大内力需求 1500 以上；
	当前精力需求 600 以上；
	慕容剑法等级 150 以上；
	神元功法等级 150 以上；
	基本剑法等级 150 以上；
	激发剑法为慕容剑法；
	激发招架为慕容剑法或斗转星移；
	激发内功为神元功。
HELP
        );
        return 1;
}
