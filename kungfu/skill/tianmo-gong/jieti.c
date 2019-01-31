// jieti.c 天魔解体
// action@SJ 2009/1/17

#include <ansi.h>
inherit F_CLEAN_UP;
string exert_name(){ return HBRED"天魔解体"NOR; }

int exert(object me, object target)
{
	int skill;

	if( me->query("max_neili") < 3500 )
		return notify_fail("你的功力不够。\n");
    if( me->query("neili") < 1500 )
		return notify_fail("你的内力不够。\n");
	if( me->query_skill("tianmo-gong", 1) < 250 )
		return notify_fail("你的天魔功等级不够。\n");

	if( me->query_skill_mapped("force") != "tianmo-gong" )
		return notify_fail("你的内功不对。\n");
    if (me->query_temp("tmg/tianmo"))
		return notify_fail("你已经在运使用「天魔解体大法」了。\n");
	if( me->query_temp("tmg/jieti") )
		return notify_fail("你已经在运「天魔解体大法」了。\n");

	skill = (int)me->query_skill("tianmo-gong")/100;
	if( skill < 2 ) skill = 2;

	me->receive_damage("neili", -500);
	message_vision(BRED"$N仰天长啸，运起天魔解体大法，双目变得赤红，脸色殷红，宛如滴血，势若疯狂！\n" NOR, me);

    me->set_temp("tmg/jieti",1); 
    me->add_temp("apply/strength", (int)me->query_skill("tianmo-gong", 1)/20); 
	me->add_temp("apply/armor", me->query_skill("tianmo-gong", 1)/6); 
   	me->add_temp("apply/damage", me->query_skill("tianmo-gong", 1)/4); 
	me->add_temp("apply/club", me->query_skill("tianmo-gong", 1)/5);
	me->add_temp("apply/axe", me->query_skill("tianmo-gong", 1)/5);
	me->add_temp("apply/blade", me->query_skill("tianmo-gong", 1)/5);
	me->add_temp("apply/strike", me->query_skill("tianmo-gong", 1)/5);
	me->add_temp("apply/throwing", me->query_skill("tianmo-gong", 1)/5);
	me->add_temp("apply/sword", me->query_skill("tianmo-gong", 1)/5);
	call_out("remove_effect", 1, me, skill);
	me->start_exert(1, "天魔解体");
	if( me->is_fighting() )
		me->start_busy(random(2));
	return 1;
}

void remove_effect(object me, int count)
{
	//int amount;
	//message_vision(HIR"$N身上鲜血不断飞溅，但全身气势却越来越强！\n"NOR);
	count=count-1;
	if( objectp(me) && me->query_temp("tmg/jieti") ) {
		if( count>0 )
		{
			
			if (!random(5))
			{
              message_vision(HIR"$N身上鲜血不断飞溅，但全身气势却越来越强！！\n"NOR,me);
			  me->receive_damage("qi",random(500),me);
			}
			call_out("remove_effect", 2, me, count);
			return;
		}
		//amount = me->query_temp("tmg/jieti");
		
        me->add_temp("apply/strength", -(int)me->query_skill("tianmo-gong", 1)/20); 
		me->add_temp("apply/armor", -me->query_skill("tianmo-gong", 1)/6); 
     	me->add_temp("apply/damage", -me->query_skill("tianmo-gong", 1)/4); 
		me->add_temp("apply/club", -me->query_skill("tianmo-gong", 1)/5);
	    me->add_temp("apply/axe", -me->query_skill("tianmo-gong", 1)/5);
		me->add_temp("apply/blade", -me->query_skill("tianmo-gong", 1)/5);
		me->add_temp("apply/strike", -me->query_skill("tianmo-gong", 1)/5);
		me->add_temp("apply/throwing", -me->query_skill("tianmo-gong", 1)/5);
		me->add_temp("apply/sword", -me->query_skill("tianmo-gong", 1)/5);
        me->add("max_neili",-2-random(3));
		me->receive_wound("qi",random(2000),"天魔解体透支而");
		me->delete_temp("tmg/jieti");
		me->add_condition("hmy_jieti",(int)count);
		tell_object(me, BRED"你的["+BRED+"天魔解体"+NOR+"]运行完毕，将内力收回丹田。精神立即萎靡不振，显然已经身体受到严重的伤害。\n"NOR);
	}
}


int help(object me)
{
	write(HBRED"\n天魔功之「天魔解体」："NOR"\n\n");
        write(@HELP
	天魔功乃是日月神教的入门内功，是门中长老
	长期总结和整理而成，适合入门弟子修炼，功
	力高深后，附着以日月神教的武技也有令人意
	料不到的威力。
	需要注意的是因天魔解体大法乃是历代长老经
	由秘法参悟而得，主要应用在短期内大幅提升
	攻击和防御的法门，使用者需注意，该大法会
	随机损失玩家的最大内力值。不到万不得已，
	不要轻易使用。
	
	指令：exert jieti

要求：  
	最大内力  2500 以上；
	当前内力  1500 以上；
	天魔功    250  以上；
			
HELP
        );
        return 1;
}