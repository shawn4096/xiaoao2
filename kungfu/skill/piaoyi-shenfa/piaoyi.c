// piaoyi.c 青翼诀
// cre by sohu 飘移身法绝技

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,damage;
	string msg;
    int ap, dp;

    if (! target)
    {
	        me->clean_up_enemy();
	        target = me->select_opponent();
    }
	if (! target || ! me->is_fighting(target))
		return notify_fail("「」只能对战斗中的对手使用。\n");

	if (!me->query("quest/mj/pysf/pass") )
		return notify_fail("你只是听说过韦蝠王的飘移身法，但尚未习得。\n");

	if ((int)me->query_skill("force", 1) < 350)
		return notify_fail("你的基本内功不够娴熟，现在还无法使用「青翼诀」。\n");
	if ((int)me->query_skill("dodge", 1) < 350)
		return notify_fail("你的基本轻功不够娴熟，现在还无法使用「青翼诀」。\n");
	if (me->query_dex(1) < 60)
		return notify_fail("你的基本身法不够娴熟，现在还无法使用「青翼诀」。\n");
	
	if ((int)me->query_skill("piaoyi-shenfa", 1) < 350)
		return notify_fail("你的飘移身法不够娴熟，现在还无法使用「青翼诀」。\n");
	                        
	if ((int)me->query("neili") < 200)
		return notify_fail("你现在真气不够，无法运用「青翼诀」。\n");
	if ((int)me->query("jingli") < 200)
		return notify_fail("你现在精力不够，无法运用「青翼诀」。\n");
	if (me->query_temp("pysf/piaoyi"))
		return notify_fail("你现在正在施展「青翼诀」。\n");
		
	message_vision(HIG "$N" HIG "忽然间如一只大蝙蝠似得，化作一道幻影，身子猛然贴地向后滑出丈余，来去如电，趋退若神。\n"
          HIG "好似有人用绳缚住以快迅无纶的手法向后扯动一般宛如有一根绳子生拉硬拽，进退间似鬼似魅！\n"NOR,me);

        ap = me->query_skill("piaoyi-shenfa",1);
        dp = target->query_skill("dodge",1);
    
	skill=me->query_skill("piaoyi-shenfa",1);
	
	me->add_temp("apply/dodge",skill/4);
	me->add_temp("apply/parry",skill/4);
	me->add_temp("apply/dexerity",skill/5);	
	me->set_temp("pysf/piaoyi",skill);
	call_out("remove_effect",1,me);
	if (me->query_skill_mapped("strike")=="hanbing-mianzhang"
		||me->query_skill_prepared("strike")=="hanbing-mianzhang")
	    if (ap / 2 + random(ap) > dp || !userp(target))
		{
			target->add_busy(2);
			damage = (int)me->query_skill("force") + (int)me->query_skill("piaoyi-shenfa");
					damage = damage / 3;
					damage += random(damage);

			me->add("neili", -100);
			message_vision( HIR "只见$n" HIR "大吃一惊，仓皇之下不及闪躲，被$N附身在其后，咬住$n颈动脉疯狂地吸起血来！\n" NOR,me,target);
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/2,me);
			target->apply_condition("hb_poison",5+random(3));

		} 

	return 1;
}


int remove_effect(object me)
{
	int skill;
	if (!me) return 0;
	skill=me->query_temp("pysf/piaoyi");
	
	if (!me->is_fighting()
		||me->query_skill_mapped("dodge")!="piaoyi-shenfa"
		||!me->query_temp("pysf/piaoyi"))
	{
		me->add_temp("apply/dodge",-skill/4);
		me->add_temp("apply/parry",-skill/4);
		me->add_temp("apply/dexerity",-skill/5);	
		me->delete_temp("pysf/piaoyi");
		message_vision(HIG"$N感觉浑身寒气渐重，急忙停止青翼诀的运转！\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me);

}

string perform_name(){ return HIW"青翼诀"NOR; }

int help(object me)
{
        write(HIW"\n飘移身法之"HIG"「青翼诀」："NOR"\n");
        write(@HELP
	飘移身法是明教四大法王之青翼蝠王的独门轻功身法
	该武功在整个倚天体系中独步武林，独占鳌头，即便
	是身负九阳神功的张无忌也对福王的身法叹服。其在
	光明顶斗灭绝、万安寺气赵敏、援救武当山等诸多战
	役中表现极为出色。武学泰斗张三丰也曾称道青翼蝠
	王轻功绝顶，世所罕有，今日一见，果是名不虚传！
	青翼诀是韦蝠王以蝙蝠飞行的仿生学原理而创造的独
	步武林的绝学。一旦施展身法和招架将大幅度提升，
	且如果备用寒冰绵掌，则有概率趁机施展「吸血诀」
	来偷袭对方。
	该招需要向韦蝠王请教方可修习。为明教独享的身法
	绝技。
	注意：set 飘移身法 青翼 解密后躲避效果大幅增加

	指令：perform dodge.piaoyi
	
要求：
	飘移身法等级 350 级以上；
	基本内功等级 350 级以上；
	基本轻功等级 350 级以上；
	后天身法至少 60  以上；
	当前内力要求 200 以上；      
	当前内力要求 200  以上；
			    
                
HELP
        );
        return 1;
}