// yuanyang.c  鸳鸯脚
// Modified by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIY"鸳"HIR"鸯"HIG"脚"NOR; }

int perform(object me, object target)
{
        int lvl,damage;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("鸳鸯脚只能对战斗中的对手使用。\n");
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("你必须空手使用「鸳鸯脚」！\n");

		if( (int)me->query_skill("yuanyang-lianhuantui", 1) < 100 )
                return notify_fail("你的鸳鸯连环退不够娴熟，无法施展出鸳鸯脚。\n");
        if ((int)me->query_skill("xiantian-gong", 1) < 100)
                return notify_fail("你的先天功火候不够，无法施展出鸳鸯脚。\n");
        if ( (int)me->query("max_neili") < 1000)
                return notify_fail("你的最大内力不够，无法施展出鸳鸯脚。\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("你的真气不够，无法施展出鸳鸯脚。\n");
		if (me->query_dex() < 35)
                return notify_fail("你的后天身法不够，无法施展出鸳鸯脚。\n");
        if (me->query_skill_prepared("leg") != "yuanyang-lianhuantui"
            || me->query_skill_mapped("leg") != "yuanyang-lianhuantui")
                return notify_fail("你现在无法使用鸳鸯脚进行攻击！\n");
        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("鸳鸯脚需要先天功激发攻击！\n");
        if (me->query_temp("yylht/yuanyang"))
                return notify_fail("你正在使用鸳鸯脚绝技！\n");
        
		lvl = me->query_skill("yuanyang-lianhuantui",1);
		damage=lvl+me->query_skill("xiantian-gong",1);
		
		if (me->query("gender")=="男性")
		{
			damage=damage*me->query_dex()/4+random(damage);
			if (damage>5000) damage=damage+random(500);
		}else {

			damage=damage*me->query_dex()/8+random(damage);
			if (damage>4000) damage=damage+random(500);
		}
		
		
		//message_vision(HBYEL+HIW "$N疾跑数步，轻身跃起，腾起空中，使出全真教「鸳鸯脚」连续两腿攻向$n！\n"NOR,me, target);
      //  me->set_temp("yylht/yuanyang",1);
		me->start_perform(2, "鸳鸯脚");

		message_vision(CYN "$N清喝一声，看招！右腿蓄势，左腿虚晃，抡起一道腿影，戳向$n,正是"RED"「鸳脚」"CYN"的招式！\n"NOR,me, target);
		if (random(me->query_skill("yuanyang-lianhuantui",1))>target->query_skill("parry",1)/2)
		{
			message_vision(YEL"$n身形一顿，为$N脚法所惑，顿时出现破绽，不由地身形一滞！\n"NOR,me, target);
			if (userp(target))
				target->add_busy(2);
			else target->add_busy(4);

		}
		if (random(me->query_dex())>target->query_dex()/3)
		{
			message_vision(HBRED"$N这一脚神出鬼没，正好踹在$n的软肋！\n"NOR,me, target);
			target->receive_damage("qi",damage,me);
			if (me->query("gender")=="男性")
				target->receive_wound("qi",damage/2,me);
			else target->receive_wound("qi",damage/3,me);
			if(userp(me) && me->query("env/damage"))
        		tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
		
			if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);

		}
		me->add_temp("apply/attack",lvl/4);
		me->add_temp("apply/damage",lvl/5);
		me->add_temp("apply/leg",lvl/5);
		
		me->set_temp("yylht/yuan",1);
		COMBAT_D->do_attack(me, target, 0, me->query("gender")=="男性"?3:1);
		me->delete_temp("yylht/yuan");

		me->add_temp("apply/leg",-lvl/5);
		me->add_temp("apply/attack",-lvl/4);
		me->add_temp("apply/damage",-lvl/5);
		if (objectp(me)
			&&objectp(target)
			&&me->is_fighting())
			call_out("yang_attack", 1, me, target);
        return 1;
}

void yang_attack(object me, object target)
{
        int i,lvl,damage;
        if (!me||!target) 
return;
		lvl = me->query_skill("yuanyang-lianhuantui",1);
		
		damage=me->query_skill("yuanyang-lianhuantui",1)+me->query_skill("xiantian-gong",1);
		damage=damage*2+random(damage);
		message_vision(RED "$N右腿顺势舒展，借助左腿之势，一式"HIY"「鸯脚」"RED"的招式使出！\n"NOR,me, target);
 
		if (target->is_busy())
		{
			message_vision(WHT"$N身在空中，眼见$n为鸳腿虚招所惑，蓄势待发的右腿瞬间踢出，击中$n胸口！\n"NOR,me, target);
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage,me);
			if(userp(me) && me->query("env/damage"))
        		tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage*2+ WHT"点攻击伤害。\n"NOR);
		
			if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage*2+ WHT"点伤害。\n"NOR);

		}
		me->set_temp("yylht/yang",1);
        me->add_temp("apply/attack",lvl/4);
        me->add_temp("apply/damage",lvl/4);
               for (i = 0; i < 2; i++){
					if (objectp(target)&& me->is_fighting())
						COMBAT_D->do_attack(me, target, 0, userp(me)?1:3);
				}
        me->add_temp("apply/attack",-lvl/4);
        me->add_temp("apply/damage",-lvl/4);
		me->delete_temp("yylht/yang");				
      

		me->start_perform(3, "鸳鸯脚");
		me->add("neili",-150);
		me->add("jingli",-100);
		return;
}
int help(object me)
{
        write(HIG"\n鸳鸯连环腿之「鸳鸯脚」："NOR"\n");
        write(@HELP
	鸳鸯连环腿是全真教弟子入门武功之一，该脚法
	全凭一口真气悠长，凝神聚力，一股气连续踢向
	对方，令对方防不胜防。
	鸳鸯脚是分别踢出3招，第一招为鸳脚姿势，主要
	是虚招，迷惑对方，若对方中招，则随后的鸯腿威
	力巨大。身法对于对方伤害至关重要。男性略有优
	势。

	指令：perform leg.yuanyang

要求：
	先天功法的等级 100  以上；
	鸳鸯连环腿等级 100  以上；
	基本腿法的等级 100  以上；
	最大的内力要求 1000 以上；
	当前内力的要求 200  以上；
	后天身法的要求 35   以上；
	激发且备腿法为连环鸳鸯腿；
	激发先天功；
	空手且备鸳鸯连环腿
HELP
        );
        return 1;
}


