// shield.c
// changed by emnil@sj  2/2/2k
// changed by hunthu@sj 2/20/2001
#include <ansi.h>
inherit F_CLEAN_UP;

int exert(object me)
{
	int skill, skill1;
	
	if ((int)me->query_skill("longxiang-boruo", 1) < 250)
		return notify_fail("你的龙象般若功修为还不够。\n");

	if((int)me->query("max_neili") < 2500)
		return notify_fail("你的内力修为太差，多多打坐吧。\n");

	if( (int)me->query("neili") < 1000 ) 
		return notify_fail("龙象般若功需要强大内力支持，你的真气不够。\n");

	if (me->query_temp("xs/shield"))
		return notify_fail("你已经在运真气护体了。\n"); 
    if (!me->query("quest/dls/longxiang/pass"))
    {	
		if (me->query_temp("xs/longxiang"))
			me->add("max_neili",-1);

    }
    
	skill = me->query_skill("longxiang-boruo",1) / 8;
    //龙象绝世加成
	if (me->query("lx/gree")==11)
    {
		skill=skill+me->query_skill("force",1)/9;
    }
	else if (me->query("lx/gree")==12)
	{
		skill=skill+me->query_skill("force",1)/8;
	}
	else if (me->query("lx/gree")==13)
	{
		skill=skill+me->query_skill("force",1)/7;
	}

	if (me->query("quest/dls/longxiang/pass"))
	{
		message_vision(HBYEL+HIM "$N深深吸入一口气，体内真气流转不绝，身周仿佛凝结成一个气盾！\n" NOR, me);
		
	}else message_vision(CYN"$N深深吸入一口气，体内真气流转不绝，身周仿佛凝结成一个气盾！\n" NOR, me);

	

	me->add_temp("apply/dodge", skill);
	me->add_temp("apply/armor", skill);
	me->add_temp("apply/parry", skill);
    me->add_temp("apply/defense", skill);
	me->set_temp("xs/shield", skill);
	me->add("neili", -random(500));
	call_out("remove_effect",(int)skill*7/2,me);
	if( me->is_fighting() ) me->start_busy(random(2));
	if (!me->query("quest/dls/longxiang/pass")) me->start_exert(1, "气盾");
	return 1;
}

void remove_effect(object me)
{
        int amount;
        if (!me) return;
        amount = me->query_temp("xs/shield");

        if ( (int)me->query_temp("xs/shield") ) {
                me->add_temp("apply/dodge", - amount);
                me->add_temp("apply/armor", - amount);
				me->add_temp("apply/parry", - amount);
				me->add_temp("apply/defense", - amount);
                me->delete_temp("xs/shield");
                message_vision(RED "$N脸上红光一闪，骨节啪啪轻响几声，散去了护体真气。\n" NOR, me);
	}
	return;
}

string exert_name(){ return CYN"气盾"NOR; }

int help(object me)
{
        write(CYN"\n龙象般若功之「气盾」："NOR"\n\n");
        write(@HELP

	那「龙象般若掌」共分十三层，第一层功夫
	十分浅易，纵是下愚之人，只要得到传授，
	一二年中即能练成。第二层比第一层加深一
	倍，需时三四年。第三层又比第二层加深一
	倍，需时七八年。如此成倍递增，越往后越
	难进展。待到第五层后，欲再练深一层，往
	往便须三十年以上苦功。金刚宗一门，高僧
	奇士历代辈出，但这一十三层「龙象般若功」
	却从未有一人练到十层以上。这功夫循序渐
	进，本来绝无不能练成之理，若有人得享数		
	千岁高龄，最终必臻第十三层境界，只人寿
	有限，金刚宗中的高僧修士欲在天年终了之
	前练到第七层、第八层，便非得躁进不可，
	这一来，往往陷入了欲速不达的大危境。北
	宋年间，吐番曾有一位高僧练到了第九层，
	继续勇猛精进，待练到第十层时，心魔骤起，
	无法自制，终于狂舞七日七夜，自绝经脉而死。
	
	激发指令:yun shield

要求：

	当前内力 1000 以上；
	最大内力 2500 以上；
	龙象般若功等级 250 以上。
	解开龙象谜题，防御发生质变。

HELP
        );
        return 1;
}
