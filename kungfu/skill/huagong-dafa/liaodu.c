// liaodu.c, 疗毒
// by snowman
// Modified by darken@SJ

#include <ansi.h>

string exert_name(){ return CYN"疗毒"NOR; }
int exert(object me)
{
		//加上个中毒判断
		if(!mapp(me->query_conditions_by_type("poison")))
				return notify_fail("你好象没有中毒吧。\n");
        if( me->is_fighting() )
                return notify_fail("战斗中运功？找死吗？\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 200)
                return notify_fail("你的化功大法修为还不够。\n");

        if ((int)me->query_skill("poison", 1) < 200)
                return notify_fail("你的基本毒技修为还不够。\n");

        if ((int)me->query_skill("medicine", 1) < 120)
                return notify_fail("你的本草术理修为还不够。\n");

        if ((int)me->query_skill("jingmai-xue", 1) < 120)
                return notify_fail("你的经脉学修为还不够。\n");

        if( (int)me->query("neili") < 5000 )
                return notify_fail("你的真气不够。\n");
      
		//这里是不是可以加个小小的飞跃
		if (!me->is_fighting() && (int)me->query_skill("huagong-dafa", 1) > 350)
		{
			message_vision(CYN"$N坐在地上，运行化功大法，体内毒素瞬间烟消云散。\n" NOR, me);
			me->clear_conditions_by_type("poison");
			me->add("neili", -300);
			me->start_busy(2);
		}
		else if  (!me->is_fighting() && (int)me->query_skill("huagong-dafa", 1) < 350)
		{
			message_vision(CYN"$N坐在地上，脸上青一阵白一阵，开始运功疗毒。\n" NOR, me);
			me->clear_conditions_by_type("poison");
			me->add("neili", -3000);
			me->add("max_neili", -random(2));
			me->start_busy(45-random(me->query("con")));
		}
        return 1;
}

int help(object me)
{
        write(BLU"\n化功大法"CYN"「疗毒」："NOR"\n");
        write(@HELP
	星宿派的功夫主要是在<毒>字上下功夫，深的阴损毒辣其中三味
	化功大法吸人内力，阴毒异常，江湖上人提起，无不谈虎色变。
	这疗毒是将自己所中毒性化解。

	指令：yun liaodu
	
要求:
	化功大法 200 级；
	毒技要求 200 级；
	本草术理 120 级；
	经脉学需 120 级；
	当前内力 5000 点；
	激发内功为化功大法；

        
HELP
        );
        return 1;
}

