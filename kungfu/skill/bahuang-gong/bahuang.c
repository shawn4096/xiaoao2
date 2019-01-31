// bahuang.c by sohu@xojh 八荒六合 聚气功效

#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name(){ return HBYEL"八荒六合诀"NOR; }

int exert(object me, object target)
{
	int skill;

	if( me->query("neili") < 500 )
		return notify_fail("你的内力不够。\n");
    if( me->query("max_neili") < 1500 )
		return notify_fail("你的最大内力不够。\n");
	if( me->query_skill("bahuang-gong", 1) < 100 )
		return notify_fail("你的八荒六合唯我独尊功等级不够。\n");

	if( me->query_skill_mapped("force") != "bahuang-gong" )
		return notify_fail("你的内功不对。\n");

	if( me->query_temp("bhg/bahuang") )
		return notify_fail("你已经在运「八荒六合唯我独尊」了。\n");

	skill = me->query_skill("bahuang-gong",1);
	
    me->set_temp("bhg/bahuang",skill);
	
	me->receive_damage("neili", -300);
	
	message_vision(HBYEL+HIG "$N凝神息气，右手食指指天，左手食指指地，口中嘿的一声，鼻孔中喷出了两条淡淡白气！\n" NOR, me);
    message_vision(HBYEL+HIG "在$N八荒六合唯我独尊功运转之下，$N只觉四周精气不断向自己周身涌来，若隐若现，宛如一堵"+HIR"气墙！\n" NOR, me);
	
	me->add_temp("apply/parry", skill/6); 

	if (me->query("bhg/biguan")==1) 
    {
		message_vision(HIG "$N已经返老还童一次，感觉自身防御逐渐提升！\n" NOR, me);
        me->add_temp("apply/defense", skill/5); 
		me->add_temp("apply/armor", skill/5); 
    }
   if (me->query("bhg/biguan")==2) 
    {
		message_vision(HIY "$N已经返老还童二次，感觉自身防御大幅提升！\n" NOR, me);
        me->add_temp("apply/defense", skill/4); 
		me->add_temp("apply/armor", skill/4); 
        me->add_temp("apply/dodge", skill/4); 
    }
	if (me->query("bhg/biguan")==3) 
    {
		message_vision(HIR "$N已经返老还童三次，感觉自身防御已然大幅提升！\n" NOR, me);
        me->add_temp("apply/defense", skill/3); 
		me->add_temp("apply/armor", skill/3); 
        me->add_temp("apply/dodge", skill/3); 
        me->add_temp("apply/dexerity", skill/10);
		me->add_temp("apply/parry", skill/3);
    }
	call_out("remove_effect", 1, me, skill);
	//不能起手，可以用在独尊后组合
	me->start_exert(1, "八荒六合唯我独尊");
	if( me->is_fighting() && me->query_skill("bahuang-gong",1)<450)
		me->start_busy(1+random(1));
	return 1; 
}

void remove_effect(object me, int count)
{
	int skill;

	if (!objectp(me)||!me->query_temp("bhg/bahuang")) return;
	skill = me->query_skill("bahuang-gong",1);

	if( !me->is_fighting()
		||count < 0 ) {
		if (me->query("bhg/biguan")==1) 
	    {
			me->add_temp("apply/defense", -skill/5); 
			me->add_temp("apply/armor", -skill/5); 
		}
		if (me->query("bhg/biguan")==2) 
		{
		
			me->add_temp("apply/defense", -skill/4); 
			me->add_temp("apply/armor", -skill/4); 
			me->add_temp("apply/dodge", -skill/4); 
		}
		if (me->query("bhg/biguan")==3) 
		{		
			me->add_temp("apply/defense", -skill/3); 
			me->add_temp("apply/armor", -skill/3); 
			me->add_temp("apply/dodge", -skill/3); 
			me->add_temp("apply/dexerity", -skill/10);
			me->add_temp("apply/parry", -skill/3);
		}
        me->add_temp("apply/parry",-skill/6); 
		me->delete_temp("bhg/bahuang");
		tell_object(me, HBYEL"你的「八荒六合功」运行完毕，将内力缓缓收回丹田。\n"NOR);
		return;
	}
		call_out("remove_effect", 1, me, count--);
			   
	
}

int help(object me)
{
	write(HIW"\n八荒六合唯我独尊功之「八荒六合诀」："NOR"\n\n");
        write(@HELP
	八荒六合唯我独尊神功乃是逍遥派三大镇派绝技之一
	当初童姥修持此功和无崖子师兄的北冥神功、师妹李
	秋水修炼的小无相神功相抗衡。八荒六合唯我独尊原
	本是阳刚之气强劲的功法，每三十年需要闭关一次，
	返老还童一次，每一次返老还童闭关，功法的防御力
	都会大幅上升，大幅提升身法、轻功、防御等属性。
	注意：450级以前，有行动busy。
		
	指令：yun bahuang
	
要求：
	最大内力  1500 以上；
	当前内力  500  以上；
	八荒六合唯我独尊功  100  级以上；
HELP
        );
        return 1;
}