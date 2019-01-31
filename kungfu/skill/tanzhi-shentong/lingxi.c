// lingxi.c 灵犀一指 by sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h"

int perform(object me, object target)
{
        string msg;
        object weapon;
        int damage, p;

        if( !target ) target = offensive_target(me);

        if( !target ||!living(target)|| !target->is_character() || !me->is_fighting(target) )
                return notify_fail("灵犀一指只能对战斗中的对手使用。\n");

      
		if (!me->query("thd/wuji/lingxi"))
		    return notify_fail("你虽然听说过“灵犀一指”这一招，可是却未获传授。\n");
        if( me->query_skill_mapped("finger") !="tanzhi-shentong" 
			|| me->query_skill_mapped("parry") !="tanzhi-shentong"
			|| me->query_skill_prepared("finger") !="tanzhi-shentong")
                return notify_fail("你的激发的武功不对，使不出来弹指神通。\n");
        if (me->query_skill_mapped("force")!="bihai-chaosheng")
                return notify_fail("你的激发的内功不对，使不出来弹指神通。\n");
		if( (int)me->query_skill("bihai-chaosheng", 1) < 250 )
                return notify_fail("你的弹指神通不够娴熟，无法使用灵犀一指。\n");
		if( (int)me->query_skill("tanzhi-shentong", 1) < 250 )
                return notify_fail("你的弹指神通不够娴熟，无法使用灵犀一指。\n");

        weapon = me->query_temp("weapon");
        if (weapon) return notify_fail("灵犀一指须空手使用。\n");

        if ( (int)me->query("neili") < 400)
                return notify_fail("你的内力不够，无法使用灵犀一指。\n");

        msg = HIC "$N双手一前一后，缓缓伸出，中指突地一弹，两道劲风汇成一股，“咝咝”有声，直袭$n前胸。\n";

        damage = (int)me->query_skill("tanzhi-shentong", 1) + (int)me->query_skill("bihai-chaosheng", 1)+(int)me->query_skill("qimen-bagua", 1) ;
        damage =damage*2+ random(damage);
        if (!userp(target))
           damage=damage*2;
		me->add_temp("apply/finger",(int)me->query_skill("tanzhi-shentong", 1)/3);
        if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 3
			||random(me->query_skill("finger",1)) > (int)target->query_skill("parry",1) / 3) {
                msg += HIR"$n躲闪不及，“噗”地一声，被指劲击中前胸【膻中穴】！\n"NOR;
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage / 3,me);
                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "刺伤");
                msg += "( $n" + eff_status_msg(p) + " )\n";
				target->apply_condition("no_exert",1);
				if (!userp(target))
				   target->set_temp("must_be_hit",1);
				me->add_temp("apply/damage",me->query_skill("tanzhi-shentong", 1)/4);
				COMBAT_D->do_attack(me, target, 0, 3);
				me->add_temp("apply/damage",-me->query_skill("tanzhi-shentong", 1)/4);
				if (!userp(target))
				    target->delete_temp("must_be_hit");
        } 
        else if (random(me->query("combat_exp")) > (int)target->query("combat_exp") * 2 / 3) {
                msg += HIY"$n向旁边一闪，让过了劲风，没想到这股指劲竟然有回力，从$n背后倒转回来，正刺中$p的后背。\n"NOR;
                target->receive_damage("qi", damage / 2,me);
                target->receive_wound("qi", damage / 4,me);
				target->add_busy(1+random(1));
                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "刺伤");
                msg += "( $n" + eff_status_msg(p) + " )\n";
        }
        else {
                msg += HIY"$n向旁边一闪，让过了劲风，却忽然发觉这股指劲竟然有回力，匆忙中只好一个前扑才堪堪躲过，模样狼狈之极。\n" NOR;
        }
		me->add_temp("apply/finger",-me->query_skill("tanzhi-shentong", 1)/3);
        message_vision(msg, me, target);
        me->add("neili", -300);
        me->start_busy(3);
        me->start_perform(3, "灵犀一指");
        return 1;
}
string perform_name(){ return BLU"灵犀一指"NOR; }
int help(object me)
{
        write(BLU"\n弹指神通之「灵犀一指」："NOR"\n");
        write(@HELP

	施展弹指神通的特强力一招，将碧海潮生功
	的内劲凝聚于一指，借助弹指神通的运气法
	门，施展出「灵犀一指」，这招宛如羚羊挂
	角，无迹可寻，不仅威力巨大，而且具有一
	定的破气功效。该武技为空手武技，所以和
	战斗经验以及基本指法的判断尤其重要。
	
	perform finger.lingxi

要求：
	碧海潮生等级 250 以上；
	弹指神通等级 250 以上；
	基本指法等级 250 以上；
	基本暗器等级 250 以上；
	最大内力要求 3000 以上；
	激发指法为弹指神通；
	备指法为弹指神通；
	激发招架为弹指神通；
	激发内功碧海潮生；
                
HELP
        );
        return 1;
}
