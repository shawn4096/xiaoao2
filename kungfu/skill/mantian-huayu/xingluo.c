//xingluo.c 星罗棋布  黑白子武功
//cre by sohu@xojh 2014/6
#include <ansi.h>
#include <combat.h>


inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i, p;
        int n,damage;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;
		skill = me->query_skill("mantian-huayu", 1)+me->query_skill("force", 1)/6;
		if (me->query_skill_mapped("force")=="tianmo-gong") skill = me->query_skill("mantian-huayu", 1)+me->query_skill("tianmo-gong", 1)/5;
		if (me->query_skill_mapped("force")=="xixing-dafa") skill = me->query_skill("mantian-huayu", 1)+me->query_skill("xixing-dafa", 1)/3;
        
        if (!target) target = offensive_target(me);

        if (userp(me) && !me->query("quest/hmy/mthy/xingluo/pass"))
                return notify_fail("你虽然听说过星罗棋布这项绝技，但尚未学会。\n");

        if (!target || !me->is_fighting(target))
                return notify_fail("星罗棋布绝技只能在战斗中对对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "throwing")
                return notify_fail("你现在手中并没有拿着暗器。无法施展星罗棋布\n");

        if (weapon->query_amount() < 20)
                return notify_fail("至少要有二十枚暗器才能施展，才能施展星罗棋布\n");

        if (skill < 350)
                return notify_fail("你的满天花雨技能不够娴熟，难以施展星罗棋布。\n");

        if ((int)me->query_skill("force",1) < 350)
                return notify_fail("你的内功火候不够，难以施展星罗棋布。\n");

        if ((int)me->query("neili") < 2000)
                return notify_fail("你现在真气不足，难以施展星罗棋布。\n");
        if (me->query_temp("mthy/xingluo"))
                return notify_fail("你正在施展星罗棋布绝技。\n");
        if (!living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg= RED "$N" RED "纵身跃起，陡然间十指猛张，竟将手中所有的"
             + weapon->name() + RED "打出，\n所有的暗器呈天圆地方之势，将$n" RED "笼罩其中！\n" NOR;

        my_exp = me->query("combat_exp")/1000;
        ob_exp = target->query("combat_exp")/1000;
        me->set_temp("mthy/xingluo",1);
        n = 5 + random(2);
        if (random(my_exp) > ob_exp) n += 6 + random(5);
        if (random(my_exp / 2) > ob_exp) n += 8 + random(6);
        if (random(my_exp / 3) > ob_exp) n += 10 + random(8);
        if (weapon->query_amount() < n) n = weapon->query_amount();

		if (random(my_exp) > ob_exp/2
			||random(me->query_skill("throwing",1))>target->query_skill("parry",1)/2)
        {

                msg += HBRED "结果$n" HBRED "躲闪不及，全身上下被$P" HBRED "射出"
                       HBRED + chinese_number(n) + HBRED "个血肉淋漓的窟窿，惨"
                       "不忍睹。\n" NOR;
			    damage=n*skill;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
				if (me->query("env/damage"))
				{
					tell_object(me, RED"这招威力巨大，你对"+target->query("name")+"造成了"+damage+RED"点伤害！\n"NOR);
				}
	            p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                message_vision(msg, me, target);
                
        } else
        {
                msg += CYN "$p" CYN "见得$P" CYN "招数奇特，不敢大意，当"
                       "即飞身躲开了所有暗器。\n" NOR;
                message_vision(msg, me, target);
        }

        //weapon->set_amount(0);
		me->add_temp("apply/attack",skill/2);
		me->add_temp("apply/damage",skill/4);
		me->add_temp("apply/throwing",skill/4);
		while (n--)
        {
          if (objectp(target)&&me->is_fighting(target))
    		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);			   
				 

         }
		me->add_temp("apply/attack",-skill/2);
		me->add_temp("apply/damage",-skill/4);
		me->add_temp("apply/throwing",-skill/4);

		me->delete_temp("mthy/xingluo");
        me->add("neili", -random(2000));
        me->start_busy(2);
        me->start_perform(4, "「星罗棋布」");
        return 1;
}
string perform_name(){ return HIC"星罗棋布"NOR; }
int help(object me)
{
        write(HIC"\n满天花雨之"HIC"「星罗棋布」："NOR"\n");
        write(@HELP
	满天花雨暗器手法乃是日月神教绝技之一，经历代高手千锤百炼后。
	暗器手法更是精湛，发出后宛如天女散花，属于大面积类攻击武技
	星罗棋布乃是梅庄四友之中老二黑白子的成名绝技，短时间内，将
	手中的棋子发射出去，专打对方穴道,防不胜防。
	学习此招需要向黑白子请教。
	
	指令;perform throwing.xingluo

要求：  
	基本内功等级 350 以上；
	漫天花雨等级 350 以上；
	当前内力 2000 以上；
	必须准备暗器。
HELP
        );
        return 1;
}
