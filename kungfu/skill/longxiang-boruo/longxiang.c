// longxiang.c
// modefied by emnil@sj 2/2/00

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me,int count);

int exert(object me, object target)
{
    int i,skill;
    i=(int)me->query("lx/gree");
	if ( !me->is_fighting())
		return notify_fail("你只有在战斗中，才能运真气增加攻击力。\n");

	if ( me->query_skill("longxiang-boruo", 1) < 350 || i<7)
		return notify_fail("只有修炼到龙象般若功第七层之后，才能增强自己的攻击力。\n");

	if ( me->query("max_neili") < 2500)
		return notify_fail("你的内力修为太差，多多打坐吧。\n");

	if ( me->query("neili") < 1000 ) 
		return notify_fail("你的真气不够。\n"); 

	if ( me->query_temp("xs/longxiang"))
		return notify_fail("你已经在运真气增加攻击力。\n"); 

	 skill = me->query_skill("longxiang-boruo",1) /8;

	if ( me->query_temp("xs/shield")&& !me->query("quest/dls/longxiang/pass"))
		me->add("max_neili",-1);
//绝世龙象威力增加
	if (me->query("lx/gree")==11)
    {
		skill=skill+me->query_skill("force",1)/8;
    }
	else if (me->query("lx/gree")==12)
	{
		skill=skill+me->query_skill("force",1)/7;
	}
	else if (me->query("lx/gree")==13)
	{
		skill=skill+me->query_skill("force",1)/6;
	}

	if(wizardp(me)) tell_object(me,sprintf("add attack: %d\n",skill));
	
	if (me->query("quest/dls/longxiang/pass")){
		message_vision(HBMAG+HIW"\n$N潜运龙象般若功，周身衣袍无风而起，脸上"+CHINESE_D->chinese_number(i)+"次紫气闪动，举手投足间具有大威力！\n" NOR, me);
		skill=skill*2;
	}
	else message_vision(MAG"\n$N潜运龙象般若功，真气流转，脸上连泛"+CHINESE_D->chinese_number(i)+"次紫气后恢复如常，但神色间隐约透出一种自信！\n" NOR, me);
	

	me->add_temp("apply/attack", skill);
	//防御类都统一调整到shield内
	if (me->query("quest/dls/longxiang/pass"))
	{
		
		me->add_temp("apply/attack",skill/2);
        me->add_temp("apply/damage",skill/4);
		me->add_temp("apply/hammer",skill/2);
		me->add_temp("apply/strike",skill/2);
		me->add_temp("apply/strength",skill/15);
	}
	me->set_temp("xs/longxiang", skill);
	me->add("neili", -350);

	call_out("remove_effect", 1, me, skill/10);

//	me->start_busy(random(2));
	if (!me->query("quest/dls/longxiang/pass"))
		me->start_exert(1, "龙象");
	return 1; 
}

void remove_effect(object me,int count)
{
	int skill;
	if ( !me || !me->query_temp("xs/longxiang"))
		return;
    skill=me->query_temp("xs/longxiang");
	if ( count < 1 || !me->is_fighting()) {
		me->add_temp("apply/attack", -skill);
		if (me->query("quest/dls/longxiang/pass"))
	     {
	    	me->add_temp("apply/attack",-skill/2);
            me->add_temp("apply/damage",-skill/4);
		    me->add_temp("apply/hammer",-skill/2);
			me->add_temp("apply/strike",-skill/2);
			me->add_temp("apply/strength",-skill/15);
	     }
		me->delete_temp("xs/longxiang");
		message_vision(MAG"$N长吐一口浊气，脸上紫气一闪，又恢复如常。\n" NOR, me);
		return;
	}
	call_out("remove_effect", 1, me,count - 1);
}

string exert_name(){ return MAG"龙象"NOR; }

int help(object me)
{
        write(MAG"\n龙象般若功之「龙象」："NOR"\n\n");
        write(@HELP
龙象般若功之「龙象」：

	那「龙象般若掌」共分十三层，第一层功夫十分浅易，纵是下愚之人，只要得到传授，
	一二年中即能练成。第二层比第一层加深一倍，需时三四年。第三层又比第二层加深
	一倍，需时七八年。如此成倍递增，越往后越难进展。待到第五层后，欲再练深一层，
	往往便须三十年以上苦功。金刚宗一门，高僧奇士历代辈出，但这一十三层「龙象般
	若功」，却从未有一人练到十层以上。这功夫循序渐进，本来绝无不能练成之理，若
	有人得享数千岁高龄，最终必臻第十三层境界，只人寿有限，金刚宗中的高僧修士欲
	在天年终了之前练到第七层、第八层，便非得躁进不可，这一来，往往陷入了欲速不
	达的大危境。北宋年间，吐番曾有一位高僧练到了第九层，继续勇猛精进，待练到第
	十层时，心魔骤起，无法自制，终于狂舞七日七夜，自绝经脉而死。
		
	那金轮国师实是个不世出的奇才，潜修苦学，进境奇速，竟尔冲破第九层难关，此时
	已到第十层的境界，当真是震古烁今，虽不能说后无来者，却确已前无古人。据那
	《龙象般若经》言道，此时每一掌击出，均具十龙十象的大力，他自知再求进境，此
	生已属无望，但既已自信天下无敌手，即令练到第十一层，也已多余。倘若解开大轮
	寺最大的秘密，龙象波若功将真正的名震江湖。

	指令;exert longxiang

要求：	
	当前内力的需求 1000 以上；
	最大内力的需求 2500 以上；
	龙象般若功等级 350 以上,
	修炼到第七重后方能发挥龙象的威力。

HELP
        );
        return 1;
}
