// chousui.c 三阴抽髓
// Created and Modified by spiderii

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        
        int j, lvl = me->query_skill("chousui-zhang", 1);
        if (me->query("quest/hgdf/powerup"))
            lvl = me->query_skill("chousui-zhang", 1)+me->query_skill("huagong-dafa", 1);
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target)
         || !living(target) )
                return notify_fail("「三阴抽髓」只能对战斗中的对手使用。\n");

        
        if( (int)me->query_skill("chousui-zhang", 1) < 400 )
                return notify_fail("你的抽髓掌功力太浅，别做梦了。\n");

        if( (int)me->query_skill("strike", 1) < 400 )
                return notify_fail("你的基本掌法功力太浅，别做梦了。\n");

        
        if( (int)me->query_skill("force", 1) < 400 )
                return notify_fail("你的内功功力太浅，别做梦了。\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 400 )
                return notify_fail("你的化功大法太浅，别做梦了。\n");

        if( (int)me->query("max_neili") < 9000 )
                return notify_fail("你的内力太浅，别做梦了。\n");

        if( (int)me->query("neili") < 3000 )
                return notify_fail("你的真气不够，别做梦了。\n");
        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang")
                return notify_fail("你必须用抽髓掌才能使用「三阴抽髓」进行攻击。\n"); 
                                                                                         
        if(me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你发现自己所用的内功无法进行「三阴抽髓」攻击。\n");                
        
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「三阴抽髓」！\n");           
        
		j = lvl/3;

        if ( lvl > 350 )
                j = to_int(lvl/3.0 * lvl/275.0);
        message_vision(BLU"\n$N"BLU"绕着$n快速的转了几圈，暴喝一声，掌爪互逆，几道冷风从掌端射出，袭向$n！ "BLU"！\n"NOR, me,target);

        me->set_temp("csz/chousui", 3);
		if (wizardp(me))
		{
			write("j="+j);
		}
        me->add_temp("apply/strike", j);
        me->add_temp("apply/attack", j);
        me->add_temp("apply/damage", j/2);
        //激发且备sanyin-zhua >450后出绝招
        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		
        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		
        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
		if (me->query_skill("sanyin-zhua",1)>450
			&&me->query_skill_mapped("claw")=="sanyin-zhua"
			&&me->query_skill_prepared("claw")=="sanyin-zhua"
			&&objectp(target)&&me->is_fighting())
        {
			me->prepare_skill("claw","sanyin-zhua");
			message_vision(HBWHT+HIB"$N阴阴一笑，变掌为抓，试图抓住$n的手腕！\n"NOR,me,target);
			if (random(me->query_str())>target->query_str()/2||random(me->query("combat_exp"))>target->query("combat_exp")/2)
			{
				target->add_busy(2);
				message_vision(CYN"$n一不小心为$N的三阴抓所抓住，顿时身形不稳。\n"NOR,me,target);
			}
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);

			me->prepare_skill("strike","chousui-zhang");
        }
		/*
		if( me->is_fighting(target)&&me->query("hgdf/powerup") )
	    {
			message_vision(HIB"$N将星宿老仙所领悟的化功大法精髓施展出来，乌黑的手掌忽然开始变大，随之毒气逐渐四散开来。\n"NOR,me,target);
			target->add_busy(1+random(1));
			target->set_temp("must_be_hit",1);
			message_vision(BLU"$n一不小心吸入毒雾，心中暗叫一声不好，手脚似乎有些麻木。\n"NOR,me,target);
			target->apply_condition("no_perform",1);
			target->apply_condition("no_exert",1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			target->delete_temp("must_be_hit");
		}*/
        me->add_temp("apply/strike", -j);
        me->add_temp("apply/attack", -j);
        me->add_temp("apply/damage", -j/2);

        

        me->delete_temp("csz/chousui");

        me->start_busy(random(2));
        me->add("neili", -300);
        me->add("jingli", -150);
        me->start_perform(3, "「三阴抽髓」");
        return 1;
}

string perform_name(){ return HBBLU"三阴抽髓"NOR; }

int help(object me)
{
        write(HBBLU"\n抽髓掌之「三阴抽髓」："NOR"\n\n");
        write(@HELP
	星宿派的功夫主要是在<毒>字上下功夫，深的阴损毒辣其中三味
	抽髓掌乃是在战斗中，凭借深厚内功把体内存毒逼出借以伤敌的
	一门功夫。「三阴抽髓」一式讲究以快打慢，一出手就是连环三
	式。如对方不解其中奥妙，甚难防御,若解开化功大法谜题，威力
	将再上一台阶！
	注意：抽髓掌和三阴抓可以互备，所以有效的组合有意想不到的
		杀伤力
	
	perform strike.chousui

要求：
	当前内力需求 3000 以上;
	最大内力需求 9000 以上；
	抽髓掌法等级 400 以上；
	化功大法等级 400 以上；
	基本掌法等级 400 以上；
	基本内功等级 400 以上;
	且手中无兵器。

        
HELP
        );
        return 1;
}

