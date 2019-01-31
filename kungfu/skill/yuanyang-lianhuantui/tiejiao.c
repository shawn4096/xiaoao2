// tiejiao.c  铁脚
// Modified by sohu@xojh
//铁脚仙谭处瑞绝技

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIR"铁脚仙"NOR; }

int perform(object me, object target)
{
        int lvl,damage;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("铁脚仙绝技只能对战斗中的对手使用。\n");
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("你必须空手使用「铁脚仙绝技」！\n");
        if( !me->query("quest/qz/yylht/tiejiao/pass") )
               return notify_fail("你只是听说过铁脚仙招式，目前无法使用「铁脚仙」绝技！\n");

		if( (int)me->query_skill("yuanyang-lianhuantui", 1) < 300 )
                return notify_fail("你的鸳鸯连环退不够娴熟，无法施展出铁脚仙绝技。\n");
        if ((int)me->query_skill("xiantian-gong", 1) < 300)
                return notify_fail("你的先天功火候不够，无法施展出铁脚仙绝技。\n");
		if ((int)me->query_skill("leg", 1) < 300)
                return notify_fail("你的基本腿法火候不够，无法施展出铁脚仙绝技。\n");
 
        if ( (int)me->query("max_neili") < 4000)
                return notify_fail("你的最大内力不够，无法施展出铁脚仙绝技。\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("你的真气不够，无法施展出铁脚仙绝技。\n");
        if (me->query_skill_prepared("leg") != "yuanyang-lianhuantui"
            || me->query_skill_mapped("leg") != "yuanyang-lianhuantui")
                return notify_fail("你现在无法使用铁脚仙绝技进行攻击！\n");
        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("铁脚仙绝技需要先天功激发攻击！\n");
        if (me->query_temp("yylht/tiejiao"))
                return notify_fail("你正在使用铁脚仙绝技！\n");
        
		lvl = me->query_skill("yuanyang-lianhuantui",1);
		damage=lvl+me->query_skill("xiantian-gong",1)/2;
		damage=damage*3+random(damage);

		message_vision(HBYEL+HIW "$N凝气下沉，先天功发动，双脚宛如两个铁钉一样钉入大地，正是「铁脚仙」绝技！\n"NOR,me, target);


		me->add_temp("apply/attack",lvl/4);
		me->add_temp("apply/damage",lvl/6);
		me->add_temp("apply/leg",lvl/5);

        me->set_temp("yylht/tiejiao",lvl);

		call_out("remove_attack", 1, me);
        return 1;
}

void remove_attack(object me)
{
        int lvl;
        if (!me) 
return;
		lvl=me->query_temp("yylht/tiejiao");

		if (!me->is_fighting()
			||me->query_skill_mapped("leg")!="yuanyang-lianhuantui"
			||me->query_skill_prepared("leg")!="yuanyang-lianhuantui")
		{
			me->add_temp("apply/attack",-lvl/4);
			me->add_temp("apply/damage",-lvl/6);
			me->add_temp("apply/leg",-lvl/5);

			me->delete_temp("yylht/tiejiao");
			message_vision(CYN"$N长长吐出一口浊气，铁脚仙绝技」缓缓收功！\n"NOR,me);
			return;
		}
		call_out("remove_attack",1,me);
}

int help(object me)
{
        write(HIG"\n鸳鸯连环腿之「铁脚仙」绝技："NOR"\n");
        write(@HELP
	鸳鸯连环腿是全真教弟子入门武功之一，该脚法
	全凭一口真气悠长，凝神聚力，一股气连续踢向
	对方，令对方防不胜防。
	铁脚仙绝技是全真七子谭处瑞的成名绝技，当初
	在悬崖边上单脚独立，虽然狂风呼啸，但依然纹
	丝不动，凭此一战成名。此招是鸳鸯连环脚的重
	要辅助进攻招式。

	指令：perform leg.tiejiao

要求：
	先天功法的等级 300  以上；
	鸳鸯连环腿等级 300  以上；
	基本腿法的等级 300  以上；
	最大的内力要求 4000 以上；
	当前内力的要求 500  以上；
	激发腿法和招架为连环鸳鸯腿；
	激发内功先天功；
	空手且备鸳鸯连环腿
HELP
        );
        return 1;
}


