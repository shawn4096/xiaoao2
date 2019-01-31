// kuangfeng.c  狂风绝技
// Modified by Darken@SJ

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIG"狂风绝技"NOR; }

int perform(object me, object target)
{
        int lvl;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("狂风绝技只能对战斗中的对手使用。\n");
        //if (!(me->query("thd/perform") & 4))
		if (!me->query("thd/wuji/kuangfeng"))
                return notify_fail("你虽然听说过“狂风绝技”是桃花岛看门神技，可是却未获黄岛主传授。\n");
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("你必须空手使用「狂风绝技」！\n");
        if( (int)me->query_skill("luoying-zhang", 1) < 100 )
                return notify_fail("你的落英神剑掌不够娴熟，无法施展出狂风绝技。\n");
        if( (int)me->query_skill("xuanfeng-tui", 1) < 100 )
                return notify_fail("你的旋风扫叶腿不够娴熟，无法施展出狂风绝技。\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 100)
                return notify_fail("你的碧海潮生功火候不够，无法施展出狂风绝技。\n");
        if ( (int)me->query("max_neili") < 1000)
                return notify_fail("你的内力不够，无法施展出狂风绝技。\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("你的真气不够，无法施展出狂风绝技。\n");
        if (me->query_skill_prepared("leg") != "xuanfeng-tui"
            || me->query_skill_mapped("leg") != "xuanfeng-tui"
			//|| me->query_skill_prepared("strike") != "luoying-zhang"
            || me->query_skill_mapped("strike") != "luoying-zhang" )
                return notify_fail("你现在无法使用狂风绝技进行攻击！\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("你的碧海潮生功修为不够，无法使用狂风绝技进行攻击！\n");
        if (me->query_temp("thd/kuangfeng"))
                return notify_fail("你正在使用桃花岛狂风绝技！\n");
        if (me->query_temp("thd/is_fast")) lvl += 100;
        lvl = me->query_skill("xuanfeng-tui",1);
		if (!userp(target)&& me->query_skill("xuanfeng-tui",1)<250)
            lvl=lvl*1.2;

	    message_vision(HBGRN "$N一声清啸，拳脚齐施，使出桃花「狂风绝技」迅捷无伦地攻向$n！\n"NOR,me, target);
        me->set_temp("thd/kuangfeng",1);
		me->start_perform(6, "狂风绝技");
		call_out("kuangfeng_attack", 1, me, target, "leg", lvl);
        return 1;
}

void kuangfeng_attack(object me, object target, string skill, int lvl)
{
        int i,lvl1;
        if (!me) 
return;
		
if(me)

			me->receive_damage("neili", 50+random(50));
       // lvl1=me->query_skill("xuanfeng-tui",1)+me->query_skill("bihai-chaosheng",1)/4;
		
		if (!objectp(target) || !me->is_fighting(target) || lvl <= 0 || me->query("neili") <= 100) {
                message_vision(HIG"$N身形渐缓，停止了狂风绝技。\n"NOR, me);
                //me->prepare_skill("cuff");
				//me->prepare_skill("claw");
				//me->prepare_skill("finger");
				//me->prepare_skill("hand");
				//me->prepare_skill("strike");
				//me->prepare_skill("strike","luoying-zhang");
                me->prepare_skill("leg", "xuanfeng-tui");				
				me->delete_temp("thd/kuangfeng");
				me->start_perform(5, "狂风绝技");
                return;
        } else {
                if (skill == "strike") {
                        me->prepare_skill("leg");
                        me->prepare_skill("strike", "luoying-zhang");
                        message_vision(HIG"$N变腿为掌，掌影翻飞，宛如桃花飞舞，迅捷无比地向$n攻去。\n"NOR, me, target);
                        //remove_call_out("kuangfeng_attack");
						call_out("kuangfeng_attack", 2, me, target, "leg", lvl-50);
                } else {
                        me->prepare_skill("strike");
                        me->prepare_skill("leg", "xuanfeng-tui");
                        message_vision(HIY"$N变掌为腿，带动劲气汹涌，在地上掀起一阵狂风，迅捷无比地向$n攻去。\n"NOR, me, target);
                        //remove_call_out("kuangfeng_attack");
						call_out("kuangfeng_attack", 2, me, target, "strike", lvl-50);
                }
                me->add_temp("apply/attack",lvl/5);
                me->add_temp("apply/damage",lvl/5);
                for (i = 0; i < 5; i++){
					if (objectp(target)&& me->is_fighting())
						COMBAT_D->do_attack(me, target, 0, random(3)?1:3);
				}
                me->add_temp("apply/attack",-lvl/5);
                me->add_temp("apply/damage",-lvl/5);
				return;
       }
}

int help(object me)
{
        write(HIG"\n「狂风绝技」："NOR"\n");
        write(@HELP
	旋风腿为桃花岛绝技之一，东邪黄药师当日因
	陈玄风和梅超风偷走九阴真经下卷，一怒之下
	将所有的弟子打断脚筋并逐出门派，后来见到
	曲灵风的悲惨遭遇后，黄药师心神大动，重新
	创造一门腿法，留给弟子。这门功夫以落英神
	剑掌配合旋风扫业腿向对手快速攻击，为黄药
	师极得意的独门绝技。六招落英神剑掌，六招
	旋风扫叶腿，循环不止。注意：攻击力，命中
	率每回合逐渐下降，若配合奇门五转可提升持
	续时限。

	perform leg.kuangfeng

要求：
	碧海潮声功等级 100  以上；
	落英神剑掌等级 100  以上；
	旋风扫叶腿等级 100  以上；
	最大的内力要求 1000 以上；
	激发且备腿法为旋风腿；
	每回合消耗内力、精力；
HELP
        );
        return 1;
}


