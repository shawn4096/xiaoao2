// Created by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

string perform_name() {return HIG"仙鹤手"NOR;}

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
			return notify_fail("托塔手绝技只能对战斗中的对手使用。\n");

		if( (int)me->query_skill("songyang-shou", 1) < 220 )
			return notify_fail("你的大嵩阳手火候不够。\n");

		if( (int)me->query_skill("parry", 1) < 220 )
			return notify_fail("你的基本招架火候不够。\n");

		if( (int)me->query_skill("hanbing-zhenqi", 1) < 220 )
			return notify_fail("你的基本内功火候不够。\n");

		if( (int)me->query("max_neili") < 2500 )
			return notify_fail("你的内力修为不够。\n");

		if( (int)me->query("neili") < 500 )
			return notify_fail("你的真气不够。\n");

		if( (int)me->query("jingli") < 500 )
			return notify_fail("你的精力不够。\n");

		if (userp(me)&&!me->query("quest/ss/sys/xianhe/pass"))
			return notify_fail("你不会托塔手绝技。\n");

		if (me->query_skill_mapped("force") != "hanbing-zhenqi")
			if (me->query_skill_mapped("force") != "lengquan-shengong")
			return notify_fail("你用什么为基础来使托塔手绝技?\n");

		if (me->query_skill_prepared("hand") != "songyang-shou"
		|| me->query_skill_mapped("hand") != "songyang-shou")
			return notify_fail("你现在无法使用嵩阳手。\n");

		if (me->query_temp("weapon"))
			return notify_fail("托塔手绝技只能空手使用！\n");

		if( me->query_temp("ss/xianhe"))
			return notify_fail("你正在使用托塔手绝技。\n");

		me->add("neili", -200);
		me->add("jingli", -50);
		message_vision(HIY "\n$N纵身跃起，半空中宛如仙鹤展翅，施展出嵩阳手绝技「仙鹤手」，双手连续挥舞，击向$n！声势惊人\n" NOR,me, target);

		me->add_temp("apply/attack", skill/3);
		me->add_temp("apply/damage", skill/5);
		me->set_temp("ss/xianhe", skill);
		
		if (me->query("quest/ss/sys/xianhe/pass"))
		{		
			msg = HIB "\n$N双掌连续挥舞,伴随挥舞，两股雄浑的劲气一前一后压向$n，$n顿时感觉气息不顺！\n" NOR;

			if (random(me->query("combat_exp")) > target->query("combat_exp")/3
				|| random(me->query_skill("hand",1))>target->query_skill("parry",1)/3)
			{
				msg += HIW"$n躲闪不及，被仙鹤手巨大劲气压制，一口淤血顿时憋在胸口，极为难受，哇地一声吐出一口鲜血。\n"NOR;
				damage = (int)me->query_skill("hanbing-zhenqi") + (int)me->query_skill("songyang-shou")*2;
				damage = (random(damage) + damage) * (random(2)+2);
				if(userp(target)&&damage > 4000) damage = 4000 + (damage - 4000)/100;
				if (damage>5000) damage = 5000 + (damage - 5000)/10;
				if (me->query_skill_mapped("force") == "hanbing-zhenqi")
					target->add_condition("cold_poison",1);
				target->receive_damage("qi", damage,me);
				target->receive_wound("qi", damage/3,me);
				target->add_busy(2);
				target->apply_condition("no_exert",2);

				me->add("neili", -200);
				me->add("jingli", -50);
				if (wizardp(me)) tell_object(me,HIW"damage是"+damage + "。\n"NOR);
				p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
				msg += damage_msg(damage, "内伤");
				msg += "( $n" + eff_status_msg(p) + " )\n";
			}
			message_vision(msg, me, target);

		}	

		me->add_temp("apply/attack",me->query_skill("songyang-shou",1)/3);
		//me->add_temp("apply/damage",me->query_skill("songyang-shou",1)/6);
		COMBAT_D->do_attack(me, target, 0, random(2)?3:1);
		COMBAT_D->do_attack(me, target, 0, random(2)?3:1);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);

		me->add_temp("apply/attack",-me->query_skill("songyang-shou",1)/3);
		//me->add_temp("apply/damage",-me->query_skill("songyang-shou",1)/6);

		message_vision(HIY "\n$N缓缓落地，长吁一口浊气。\n" NOR,me, target);

		me->delete_temp("sys/xianhe");
		me->add_temp("apply/attack", -skill/3);
		me->add_temp("apply/damage", -skill/5);
		me->start_perform(5,"仙鹤手");
		me->start_busy(1);

        return 1;
}

int help(object me)
{
	write(HIW"\n大嵩阳手之"+HIY"「仙鹤手」："NOR"\n\n");
        write(@HELP
	大嵩阳手乃是嵩山弟子入门武技，但这门武功中蕴含
	的意境去不容小觑。这招的特点是依靠自己强大内力
	灌注于双手，所以若功力高深者，运用此招，再辅助
	以独门内劲寒冰真气，威力独具特色。
	仙鹤手是嵩山十三太保中的陆柏绝技，一手大嵩阳手
	运使既有仙鹤的雕琢招式，也有以气势压迫人的招式
	
	指令：perform hand.xianhe

要求：
	最大内力  2500 以上；
	当前内力  500  以上；
	当前精力  500  以上；
	寒冰真气  220  级以上；
	大嵩阳手  220  级以上；
	激发手法为嵩阳手；
	激发招架为嵩阳手
	激发内功为寒冰真气或阴性内功;
	备手法为嵩阳手；
	空手；
HELP
        );
        return 1;
}