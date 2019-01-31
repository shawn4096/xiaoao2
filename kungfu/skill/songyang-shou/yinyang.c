// Created by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

string perform_name() {return HIY"大阴阳手"NOR;}

int perform(object me, object target)
{
		int i, j, damage, num, p, win=0;
		int tmp,focus,skill;
		string msg;
		focus = me->query_temp("ss/focus");
		skill = me->query_skill("songyang-shou", 1);
		if( !target ) target = offensive_target(me);
		
		if( !target
		|| !target->is_character()
		|| !me->is_fighting(target) 
		|| !living(target))
			return notify_fail("大阴阳手绝技只能对战斗中的对手使用。\n");

		if( (int)me->query_skill("songyang-shou", 1) < 300 )
			return notify_fail("你的嵩阳手火候不够。\n");

		if( (int)me->query_skill("parry", 1) < 300 )
			return notify_fail("你的基本招架火候不够。\n");

		if( (int)me->query_skill("hanbing-zhenqi", 1) < 300 )
			return notify_fail("你的基本内功火候不够。\n");

		if( (int)me->query("max_neili") < 1500 )
			return notify_fail("你的内力修为不够。\n");

		if( (int)me->query("neili") < 1000 )
			return notify_fail("你的真气不够。\n");

		if( (int)me->query("jingli") < 600 )
			return notify_fail("你的精力不够。\n");

		if (userp(me)&&!me->query("quest/ss/sys/yinyang/pass"))
			return notify_fail("你不会大阴阳手绝技。\n");

		if (me->query_skill_mapped("force") != "hanbing-zhenqi")
			return notify_fail("你用什么为基础来使大阴阳手绝技?\n");

		if (me->query_skill_prepared("hand") != "songyang-shou"
		|| me->query_skill_mapped("hand") != "songyang-shou")
			return notify_fail("你现在无法使用嵩阳手。\n");

		if (me->query_temp("weapon"))
			return notify_fail("大阴阳手绝技只能空手使用！\n");

		if( me->query_temp("sys/yinyang"))
			return notify_fail("你正在使用大阴阳手绝技。\n");

		me->add("neili", -200);
		me->add("jingli", -50);
		message_vision(HIY "\n$N正在和$n对战之际，突然向后倒窜，但双掌却先后向着$n发力遥击！\n" NOR,me, target);

		me->add_temp("apply/attack", skill/3);
		me->add_temp("apply/damage", skill/5);
		me->set_temp("sys/yinyang", skill);

		msg = HIB "\n$N双掌一阴一阳，阳掌先出，阴力却先行着体，一股寒气直逼$n而去！\n" NOR;

		if (random(me->query("combat_exp")) > target->query("combat_exp")/3
		|| random(me->query_skill("hand",1))>target->query_skill("parry",1)/3) {
			msg += HIW"$n刚要闪避，只觉一股寒气袭上身来，登时机伶伶打了个冷战。\n"NOR;
			damage = (int)me->query_skill("hanbing-zhenqi") + (int)me->query_skill("songyang-shou")*2;
			damage = (random(damage) + damage) * (random(2)+2);
			if(userp(target)&&damage > 4000) damage = 4000 + (damage - 4000)/100;
			if (damage>5000) damage = 5000 + (damage - 5000)/10;
			if (me->query_skill_mapped("force") == "hanbing-zhenqi")
				target->add_condition("cold_poison",1);
			target->receive_damage("qi", damage,me);
			target->receive_wound("qi", damage/3,me);
			me->add("neili", -200);
			me->add("jingli", -50);
			if (wizardp(me)) tell_object(me,HIW"damage是"+damage + "。\n"NOR);
			p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
			msg += damage_msg(damage, "内伤");
			msg += "( $n" + eff_status_msg(p) + " )\n";
		}
		else{ 
			msg += HIC"$n被这阴寒掌力打在身上，霎时间全身剧震，说不出的难受。\n"NOR;
			win = 1;
		}
		message_vision(msg, me, target);
		me->add_temp("apply/attack",me->query_skill("songyang-shou",1)/3);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
		me->add_temp("apply/attack",-me->query_skill("songyang-shou",1)/3);

		//第二掌，阳掌
		if (win == 1){
			me->start_busy(1+random(1));
			call_out("remove_effect", 1, me, target, 2, skill); //打不中，延迟3秒
			return 1;
		}
		else {
			msg = HIR"$n只一呆，一股炙热的掌风跟着扑到！\n"NOR;
			if (random(me->query("combat_exp")) > target->query("combat_exp")/2
			||random(me->query_int())>target->query_int()/2) {
				msg += RED"$n意欲闪避，已是不能，身体立似火烧火燎般痛楚！\n"NOR;
				damage = (int)me->query_skill("hanbing-zhenqi") + (int)me->query_skill("songyang-shou")*2;
				damage = (random(damage) + damage) * (focus+1);
				if(damage > 2000) damage = 2000 + (damage - 2000)/100;
				me->add("neili", -200);
				me->add("jingli", -50);
				target->receive_damage("qi", damage,me);
				target->receive_wound("qi", damage/3,me);
				if (wizardp(me)) tell_object(me,HIW"damage是"+damage + "。\n"NOR);
				p = (int)target->query("qi") * 100 / (int)target->query("max_qi"); 
				msg += damage_msg(damage, "内伤");
				msg += "( $n" + eff_status_msg(p) + " )\n";
			}
			else {
				msg += "$n被这炙热掌力打在身上，霎时间全身剧震，说不出的难受。\n";
			}
			message_vision(msg, me, target);
			me->add_temp("apply/hand",skill/4);
			COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
			COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);

			me->add_temp("apply/hand",-skill/4);
		}

		me->delete_temp("sys/yinyang");
		me->add_temp("apply/attack", -skill/3);
		me->add_temp("apply/damage", -skill/5);
		me->start_perform(3,"大阴阳手");
		me->start_busy(1);

        return 1;
}


void remove_effect(object me, object target, int count, int skill)
{
		if (!me) return;
		if(!target
		|| !me->is_fighting(target)
		|| me->query_temp("weapon")
		|| me->query_skill_prepared("hand") != "songyang-shou"
		|| count < 1 ){
			me->add_temp("apply/attack", -skill/3);
			me->add_temp("apply/damage", -skill/5);
			me->delete_temp("sys/yinyang");
			return;
		}
		call_out("remove_effect", 1, me, target, count - 1, skill);
}

int help(object me)
{
	write(HIW"\n大嵩阳手之"+HIY"「大阴阳手」："NOR"\n\n");
        write(@HELP
	大嵩阳手乃是嵩山弟子入门武技，峻极乃是取嵩山峻
	极峰之意，但这门武功中蕴含的意境去不容小觑。这
	招的特点是依靠自己强大内力以及臂力和对方以掌对
	掌抗衡，所以若功力高深者，运用此招，再辅助以独
	门内劲寒冰真气，则会使得对方防不胜防，当然，若
	比对方功力低，则会为对方内力反震，嵩山弟子需谨
	慎使用。注意，160级后会有后招变化。
	注意：此招需要向乐厚请教。
	
	指令：perform hand.yinyang

要求：
	最大内力  1500 以上；
	当前内力  1000  以上；
	当前精力  600  以上；
	寒冰真气  300  级以上；
	大l嵩阳手  300  级以上；
	激发手法为嵩阳手；
	激发招架为嵩阳手
	激发内功为寒冰真气或阴性内功;
	备手法为嵩阳手；
	空手；
HELP
        );
        return 1;
}