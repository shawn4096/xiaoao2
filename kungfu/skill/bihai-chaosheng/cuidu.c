// Modified by Darken@SJ
#include <ansi.h>

string exert_name() { return HIG"附骨钉催毒"NOR; }

int exert(object me, object target)
{
        int level = me->query_skill("bihai-chaosheng",1);
        int num;

        if( !objectp(target) )
                return notify_fail("你要催动谁的毒性？\n");
        if( environment(me)->query("no_fight") )
                return notify_fail("这里不能催毒。\n");
        if (me->query("thdjj/ronghe")!="pass")
			if( me->is_fighting() || target->is_fighting())
                return notify_fail("你的内功尚未融合贯通，战斗中催毒？找死啊？\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 350)
                return notify_fail("你的碧海潮生功修为还不够。\n");
        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力修为不够。\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你的真气不够。\n");
        if( me == target ) 
                return notify_fail("你有问题啊？\n");
        if(!target->query("thd/fugu"))
                return notify_fail("此人没有中附骨钉。\n");

        num = target->query("thd/fugu");        
        me->add("neili", -300);
        me->add("jing", -500);
        target->receive_wound("qi",random(level)*num,me);
        target->receive_wound("jing",random(level)*num,me);
        target->set_temp("last_damage_from", me);
        target->add("neili",-random(level));
        if (me->query("thdjj/ronghe")=="pass") 
        {
			target->receive_wound("qi",level*3*num,me);
            target->receive_wound("jing",level*num,me);
			target->add_busy(2+random(3));
        }
		else target->add_busy(2+random(3));
        message_vision(HIW"$N运起碧海潮生功，催动$n的附骨钉之毒！"NOR,me,target);
        message_vision(HIW"$n的"HIR"附骨钉"HIW"之毒发作了！\n"NOR,me,target);
        if(!target->is_killing(me)) me->kill_ob(target);
        me->add_busy(3+random(2));
        return 1;
}

int help(object me)
{
        write(HIG"\n「附骨钉---催字决」："NOR"\n");
        write(@HELP
	桃花岛落英掌绝技之催毒，使用碧海潮生功
	催动附骨钉的毒性，让目标的精气皆受到损
	伤，同时毒侵丹田，打散部分聚集的真气，
	催毒有辅助进攻效果。解开桃花岛的融合绝
	技后，该武技将飞跃。
	
	注意：在战斗中若提前给敌人按下几枚腐骨
		钉，手持萧类武器，则若解开融合谜题
		会出现奇效攻敌。
	设置：set 碧海潮生 催毒
	指令：yun cuidu

要求：
	碧海潮生等级 350 以上；
	最大内力 1000 以上；
	非战斗方能使用。
HELP
        );
        return 1;
}

