// jd.c 
// by emnil   98.10.4
//edit by sohu 2014
#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name() {return HIG"解毒"NOR;}

int exert(object me, object target)
{
        int skill;

        if(target != me && !present(target,environment(me)))
                return notify_fail("这里好象没有这个人？\n");

        if((int)me->query_skill("dulong-dafa",1) < 250  )
                return notify_fail("你的毒龙大法功力不够，无法解化骨绵掌毒。\n");
		if((int)me->query_skill("medicine",1) < 100  )
                return notify_fail("你的本草术理不够，无法解化骨绵掌毒。\n");
		if((int)me->query_skill("poison",1) < 150  )
                return notify_fail("你的毒计不够，无法解化骨绵掌毒。\n");
        if((int)me->query_skill("shenlong-yaoli",1) < 180  )
                return notify_fail("你对神龙药理学的领悟尚缺，无法解化骨绵掌毒。\n");

        if((int)me->query("neili") < 500
         || (int)me->query("max_neili")< 2500  )
                return notify_fail("你的内力不够。\n");

        skill= me->query_skill("dulong-dafa",1) + me->query_skill("shenlong-yaoli",1)+ me->query_skill("medicine",1);
         if((int)target->query("huagu") > skill)
            target->add("huagu",-skill);
        else
            target->delete("huagu");
        if( target != me)
          message_vision(HIW"\n$N伸手抵住$n的双掌，慢慢将$n身上的毒素逼出体外。\n\n"NOR,me,target);
        else 
          message_vision(HIW"\n$N满头大汗，用劲将身体内的毒素逼出体外。\n\n"NOR, me);
     
		target->clear_condition("huagu_poison");
        target->clear_condition("qianli_poison");
        target->clear_condition("7bug_poison");
        target->clear_condition("fugu_poison");
		target->clear_condition("snake_poison");
        target->clear_condition("sld_shexin");
        me->add("neili",-1000);
		if (!me->query("quest/sld/dldf/pass"))
			me->add("max_neili",-random(10));
		me->start_busy(5);
        if( target != me) target->start_busy(5);
        me->add("jingli",-400);
        return 1;
}
int help(object me)
{
        write(WHT"\n毒龙大法之"+HIG"「解毒」"WHT"：\n\n");
        write(@HELP
	毒龙大法乃是神龙岛内功绝技，乃是开山祖师
	洪教主根据门派独特心法所创立。既有其蛇毒
	的特性，又有其强悍的一面。
	「解毒」绝技乃是利用深厚的内功心法和独特
	的神龙药理知识相结合，对中了神龙岛一脉的
	各种毒素给与化解。
	注意：若没有解开毒龙大法谜题，会随机掉落
	使用者的最大内力。
	
	使用指令：yun jiedu
		
要求：
	当前内力要求 500 以上；
	最大内力要求 2500 以上；
	基本内功等级 250  以上；
	毒龙大法等级 250 以上；
	本草术理等级 100 以上；
	神龙药理等级 180 以上；
	毒计技能需求 150 以上；
	激发内功为毒龙大法；
	
HELP
        );
        return 1;
}
