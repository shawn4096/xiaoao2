// bingcan.c 冰蚕毒掌招式
// Created by sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        
        int j, lvl = me->query_skill("chousui-zhang", 1);
        
		j=lvl;

		if (!me->query("quest/xx/csz/bingcan/over"))
			 return notify_fail("你尚未打通神足经，无法使用「冰蚕毒掌」。\n");
		
		if (!me->query("quest/xx/csz/bingcan/pass"))
			 return notify_fail("你虽然打通了神足经，但对于运转并不了解，无法使用「冰蚕毒掌」。\n");

		if (me->query("quest/hgdf/powerup"))
			j = me->query_skill("chousui-zhang", 1)+me->query_skill("huagong-dafa", 1)/5;
        
		if (me->query("quest/xx/csz/bingcan/pass"))
		{
			j = j+me->query_skill("huagong-dafa", 1)/5;

		}

		if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target)
         || !living(target) )
                return notify_fail("「冰蚕毒掌」只能对战斗中的对手使用。\n");

        
        if( (int)me->query_skill("chousui-zhang", 1) < 500 )
                return notify_fail("你的抽髓掌功力太浅，别做梦了。\n");

        if( (int)me->query_skill("strike", 1) < 500 )
                return notify_fail("你的基本掌法功力太浅，别做梦了。\n");

        
        if( (int)me->query_skill("force", 1) < 500 )
                return notify_fail("你的内功功力太浅，别做梦了。\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 500 )
                return notify_fail("你的化功大法太浅，别做梦了。\n");

        if( (int)me->query("max_neili") < 15000 )
                return notify_fail("你的最大内力太浅，别做梦了。\n");

        if( (int)me->query("neili") < 3000 )
                return notify_fail("你的真气不够，别做梦了。\n");
        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang")
                tell_object(me,"你必须用抽髓掌才能使用「冰蚕毒掌」进行攻击。\n"); 
                                                                                         
        if(me->query_skill_mapped("force") != "huagong-dafa")
                tell_object(me,"你发现自己所用的内功无法进行「冰蚕毒掌」攻击。\n");                
        
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「冰蚕毒掌」！\n");           
        
		
		j = j/3;

        if ( lvl > 350 )
                j = to_int(lvl/3.0 * lvl/350.0);

		message_vision(HBWHT+HIG"\n$N"HIG"双脚呈丁字步站定，猛喝一声，竖起双掌，夹裹一股阴寒之气裹向$n周身！\n"NOR, me,target);
		message_vision(HBWHT+HIB"抽髓掌在天蚕毒的夹裹下，威力顿时大的出奇！\n"NOR, me,target);
		
        me->set_temp("csz/bingcan", 5);

        me->add_temp("apply/strike", j);
        me->add_temp("apply/attack", j);
        me->add_temp("apply/damage", j/2);
       
		if (wizardp(me)) write("j="+j);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);

        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
		if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		//if( me->is_fighting(target) )
               // COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
		if( me->is_fighting(target)&&me->query("hgdf/powerup") )
	    {
			message_vision(HIB"$N将星宿老仙所领悟的化功大法精髓施展出来，乌黑的手掌忽然开始变大，随之毒气逐渐四散开来。\n"NOR,me,target);
			target->add_busy(1+random(1));
			target->set_temp("must_be_hit",1);
			message_vision(BLU"$n一不小心吸入毒雾，心中暗叫一声不好，手脚似乎有些麻木。\n"NOR,me,target);
			target->apply_condition("no_perform",1+random(2));
			target->apply_condition("no_exert",1+random(2));
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			target->delete_temp("must_be_hit");
		}

        me->add_temp("apply/strike", -j);
        me->add_temp("apply/attack", -j);
        me->add_temp("apply/damage", -j/2);

        

        me->delete_temp("csz/bingcan");

        me->start_busy(random(2));
        me->add("neili", -300);
        me->add("jingli", -150);
        me->start_perform(3, "「冰蚕毒掌」");
        return 1;
}

string perform_name(){ return HBWHT+HIB"冰蚕毒掌"NOR; }

int help(object me)
{
        write(HBBLU"\n抽髓掌之「冰蚕毒掌」："NOR"\n\n");
        write(@HELP
	星宿派的功夫主要是在<毒>字上下功夫，深的阴损毒辣其中三味
	抽髓掌乃是在战斗中，凭借深厚内功把体内存毒逼出借以伤敌的
	一门功夫。「冰蚕毒掌」一式讲究以快打慢，一出手就是连环六
	式，招式平平，但威力奇大，加上有天山奇物冰蚕的辅助功效，
	这招属于抽髓掌的终极招式，需要解密方可使用！
	
	指令：perform strike.bingcan

要求：
	当前内力需求 3000 以上;
	最大内力需求 15000 以上；
	抽髓掌法等级 500 以上；
	化功大法等级 500 以上；
	基本掌法等级 500 以上；
	基本内功等级 500 以上;
	激发内功化功大法
	激发掌法抽髓掌
	激发招架为抽髓掌
	且手中无兵器。

        
HELP
        );
        return 1;
}

