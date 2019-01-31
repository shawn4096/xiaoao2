// lianhuan.c  连环踢
// Modified by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HBGRN+HIW"鸳鸯连环踢"NOR; }

int perform(object me, object target)
{
        int i,lvl,damage;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("连环踢只能对战斗中的对手使用。\n");
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("你必须空手使用「连环踢」！\n");

		if( (int)me->query_skill("yuanyang-lianhuantui", 1) < 160 )
                return notify_fail("你的鸳鸯连环腿不够娴熟，无法施展出连环踢。\n");
        if ((int)me->query_skill("xiantian-gong", 1) < 160)
                return notify_fail("你的先天功火候不够，无法施展出连环踢。\n");
        if ( (int)me->query("max_neili") < 1500)
                return notify_fail("你的最大内力不够，无法施展出连环踢。\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("你的真气不够，无法施展出连环踢。\n");
        if (me->query_skill_prepared("leg") != "yuanyang-lianhuantui"
            || me->query_skill_mapped("leg") != "yuanyang-lianhuantui")
                return notify_fail("你现在无法使用连环踢进行攻击！\n");
        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("连环踢需要先天功激发攻击！\n");
        if (me->query_temp("yylht/yuanyang"))
                return notify_fail("你正在使用连环踢绝技！\n");
        
		lvl = me->query_skill("yuanyang-lianhuantui",1);
		damage=lvl+me->query_skill("xiantian-gong",1)/2;
		damage=damage*3+random(damage);

		message_vision(HBYEL+HIW "$N疾跑数步，轻身跃起，腾起空中，使出鸳鸯连环腿的「连环踢」绝技，宛如狂风暴雨，连续攻向$n！\n"NOR,me, target);
        me->set_temp("yylht/lianhuan",1);
		me->start_perform(6, "鸳鸯连环踢");


		me->add_temp("apply/attack",lvl/4);
		me->add_temp("apply/damage",lvl/5);
	
       for (i = 0; i < 4; i++)
	   {
			if (objectp(target)&& me->is_fighting())
				COMBAT_D->do_attack(me, target, 0, random(3)?1:3);
		}
		if (objectp(target)&& me->is_fighting()&&lvl>250)
			COMBAT_D->do_attack(me, target, 0, 3);
		if (objectp(target)&& me->is_fighting()&&lvl>300)
			COMBAT_D->do_attack(me, target, 0, 3);

		me->add_temp("apply/attack",-lvl/4);
		me->add_temp("apply/damage",-lvl/5);
		me->start_perform(5, "鸳鸯连环踢");
		me->add("neili",-250);
		me->add("jingli",-200);
		me->delete_temp("yylht/lianhuan");

		return 1;
}

int help(object me)
{
        write(HIG"\n鸳鸯连环腿之「鸳鸯连环踢」："NOR"\n");
        write(@HELP
	鸳鸯连环踢是全真教弟子入门武功之一，该脚法
	全凭一口真气悠长，凝神聚力，一股气连续踢向
	对方，令对方防不胜防。
	连环踢是身在空中，凭借一口真气，连续想对方
	攻击的招式，250级以前可以出四招，300级后，
	威力逐渐增加。

	指令：perform leg.yuanyang

要求：
	先天功法的等级 160  以上；
	鸳鸯连环腿等级 160  以上；
	基本腿法的等级 160  以上；
	最大的内力要求 1500 以上；
	当前内力的要求 500  以上；
	激发腿法和招架为连环鸳鸯腿；
	激发内功先天功；
	空手且备鸳鸯连环腿
HELP
        );
        return 1;
}


