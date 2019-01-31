// tianmo.c 天魔大法
// action@SJ 2009/1/17

#include <ansi.h>
inherit F_CLEAN_UP;
string exert_name(){ return HIR"天魔大法"NOR; }

int exert(object me, object target)
{
	int skill;

	if( me->query("neili") < 1000 )
		return notify_fail("你的内力不够。\n");

	if( me->query_skill("tianmo-gong", 1) < 150 )
		return notify_fail("你的天魔功等级不够。\n");

	if( me->query_skill_mapped("force") != "tianmo-gong" )
		return notify_fail("你的内功不对。\n");

	if( me->query_temp("tmg/tianmo") )
		return notify_fail("你已经在运「天魔大法」了。\n");

	skill = me->query_skill("force")/3;
	if( skill > 150 ) skill = 150;

	me->receive_damage("neili", -300);
	message_vision(HIR"$N一声怪啸，双目变得赤红，双足一点，身子腾空而起，四周顿时热浪翻涌，灸热难当！。\n" NOR, me);

    me->set_temp("tmg/tianmo",1); 
    me->add_temp("apply/armor", me->query_skill("tianmo-gong", 1)/6); 
    me->add_temp("apply/attack", me->query_skill("tianmo-gong", 1)/5);
    me->add_temp("apply/blade", me->query_skill("tianmo-gong", 1)/6); 
	//me->add_temp("apply/armor", me->query_skill("tianmo-gong", 1)/3); 
	call_out("remove_effect", 1, me, skill);
	
	me->start_exert(1, "天魔大法");
	if( me->is_fighting()&&me->query_skill("tianmo-gong")<450 )
		me->start_busy(random(2));
	return 1;
}

void remove_effect(object me, int count)
{
	int amount;
	if( objectp(me) && me->query_temp("tmg/tianmo") ) {
		if( count-- > 0 ) {
			call_out("remove_effect", 1, me, count);
			return;
		}
		amount = me->query_temp("tmg/tianmo");
		me->add_temp("apply/armor", -me->query_skill("tianmo-gong", 1)/6);
		me->add_temp("apply/attack",-me->query_skill("tianmo-gong", 1)/5);
        me->add_temp("apply/blade", -me->query_skill("tianmo-gong", 1)/6); 
        me->delete_temp("tmg/tianmo");
		tell_object(me, HIW"你的["+HIR+"天魔大法"+HIW+"]运行完毕，将内力收回丹田。\n"NOR);
	}
}

int help(object me)
{
	write(HIR"\n天魔功之「天魔大法」："NOR"\n\n");
        write(@HELP
	天魔功乃是日月神教的入门内功，是门中长老
	长期总结和整理而成，适合入门弟子修炼，功
	力高深后，附着以日月神教的武技也有令人意
	料不到的威力。
	天魔大法运转之后，会有效提升命中和防御，
	尤其对于刀法有额外的辅助作用。
	要求：  
		最大内力  2000 以上；
		当前内力  1000 以上；
		天魔功    150  以上；
HELP
        );
        return 1;
}