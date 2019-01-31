// cuogu.c 挫骨手 
// Modified by sohu@xojh
// 点穴，伤经脉

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIG"分筋挫骨诀"NOR; }

int perform(object me, object target)
{
        int lvl,damage;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「分筋挫骨诀」只能对战斗中的对手使用。\n");
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("你必须空手使用「「分筋挫骨诀」」！\n");

		if( (int)me->query_skill("cuogu-shou", 1) < 100 )
                return notify_fail("你的分筋错骨手不够娴熟，无法施展出「分筋挫骨诀」。\n");
        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候不够，无法施展出「分筋挫骨诀」。\n");
        if ( (int)me->query("max_neili") < 1000)
                return notify_fail("你的最大内力不够，无法施展出「分筋挫骨诀」。\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("你的真气不够，无法施展出「分筋挫骨诀」。\n");
		if (me->query_dex() < 35)
                return notify_fail("你的后天身法不够，无法施展出「分筋挫骨诀」。\n");
        if (me->query_skill_prepared("hand") != "cuogu-shou"
		    || me->query_skill_mapped("parry") != "cuogu-shou"
            || me->query_skill_mapped("hand") != "cuogu-shou")
                return notify_fail("你现在激发不对，无法使用「分筋挫骨诀」进行攻击！\n");
        if (me->query_temp("cgs/cuogu"))
                return notify_fail("你正在使用「分筋挫骨诀」绝技！\n");
        
		lvl = me->query_skill("cuogu-shou",1);
		damage=lvl+me->query_skill("force",1);
		
	
		//message_vision(HBYEL+HIW "$N疾跑数步，轻身跃起，腾起空中，使出全真教「「分筋挫骨诀」」连续两腿攻向$n！\n"NOR,me, target);
      //  me->set_temp("yylht/yuanyang",1);
		me->start_perform(2, "「分筋挫骨诀」");

		message_vision(CYN "$N揉身而上，挥出一片手影，点、拿、戳、卸，如雨点般攻向$n,正是"RED"「分筋挫骨」"CYN"的招式！\n"NOR,me, target);
		if (random(me->query_skill("cuogu-shou",1))>target->query_skill("parry",1)/2)
		{
			message_vision(YEL"$n身形一顿，为$N拿住要穴，不由地身形一滞！\n"NOR,me, target);
			if (userp(target))
				target->add_busy(2);
			else target->add_busy(4);
		}
		if (random(me->query_dex())>target->query_dex()/3)
		{
			message_vision(HBGRN+HIW"$N身形如鬼魅，围绕$n转了一圈，双手分合之间使出「分筋式」，顿时捏住$n的筋骨要害！\n"NOR,me, target);
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
		me->add_temp("apply/hand",lvl/5);
		
		me->set_temp("cgs/fenjin",1);
		COMBAT_D->do_attack(me, target, 0, me->query("gender")=="男性"?3:1);
		me->delete_temp("cgs/fenjin");

		me->add_temp("apply/hand",-lvl/5);
		me->add_temp("apply/attack",-lvl/4);
		me->add_temp("apply/damage",-lvl/5);
		if (objectp(me)
			&&objectp(target)
			&&me->is_fighting())
			call_out("cuogu_attack", 1, me, target);
        return 1;
}

void cuogu_attack(object me, object target)
{
        int i,lvl,damage;
        if (!me||!target) 
return;
		lvl = me->query_skill("cuogu-shou",1);
		
		damage=me->query_skill("cuogu-shou",1)+me->query_skill("force",1);
		damage=damage*2+random(damage);
		message_vision(WHT"$N双手捏住$n的筋骨，向外一拽，真是"HIY"「挫骨式」"RED"的招式！\n"NOR,me, target);
 
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
		me->set_temp("cgs/cuogu",1);
        me->add_temp("apply/attack",lvl/4);
        me->add_temp("apply/damage",lvl/4);
               for (i = 0; i < 2; i++){
					if (objectp(target)&& me->is_fighting())
						COMBAT_D->do_attack(me, target, 0, userp(me)?1:3);
				}
        me->add_temp("apply/attack",-lvl/4);
        me->add_temp("apply/damage",-lvl/4);
		me->delete_temp("cgs/cuogu");				
      

		me->start_perform(3, "「分筋挫骨诀」");
		me->add("neili",-150);
		me->add("jingli",-100);
		return;
}
int help(object me)
{
        write(HIG"\n分筋挫骨手之「分筋挫骨诀」："NOR"\n");
        write(@HELP
	分筋错骨手是江南七怪之二圣手书生朱聪的绝技。朱聪
	手法精妙，以分筋挫骨将对方点穴或拿捏重要经脉，瞬
	间将对方拿住并给与重创。

	指令：perform hand.cuogu
要求：
	基本内功的等级 100  以上；
	分筋错骨手等级 100  以上；
	基本手法的等级 100  以上；
	最大的内力要求 1000 以上；
	当前内力的要求 200  以上；
	后天身法的要求 35   以上；
	激发且备手法为分筋错骨手；
	空手且备手法为分筋错骨手；
	内功不限。
HELP
        );
        return 1;
}


