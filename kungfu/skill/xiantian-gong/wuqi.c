// wuqi.c
// action@SJ 2009/1/17
// update sohu

#include <ansi.h>
inherit F_CLEAN_UP;
string exert_name(){ return HBMAG+HIW"五气朝元"NOR; }

int exert(object me, object target)
{
	int skill;

	if( me->query("neili") < 2000 )
		return notify_fail("你的内力不够。\n");
	if( me->query("jingli") < 1000 )
		return notify_fail("你的精力不够。\n");

	if( me->query_skill("xiantian-gong", 1) < 550 )
		return notify_fail("你的先天功等级不够。\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("你的内功不对。\n");

	if( me->query_temp("xtg/wuqi") )
		return notify_fail("你已经在运「五气朝元」了。\n");
	if(!me->query("quest/qz/xtg/wuqi/pass") )
		return notify_fail("你尚未得到门派师傅的传承，现在无法施展五气朝元。\n");
	skill =me->query_skill("xiantian-gong",1);
	
	me->add("neili", -500);
	me->add("jingli", -300);

	message_vision(
    HIC"$N默念“心藏神，肝藏魂，脾藏意，肾藏精，肺藏魄”的法诀，正合道家[五气朝元]之理，将自己辛苦修来的先天要诀\n"+

    "施展出来，心中默念“人之修道，必由五行归五老，三花而化三清，始能归原无极本体，而达圆通究竟”的法门。\n" NOR, me);
     if (me->query("quanzhen/force") =="pass")
     {
        me->add_temp("apply/defense", skill/3);
	    me->add_temp("apply/armor", skill/5);
		me->add_temp("apply/sword", skill/8);
		me->add_temp("apply/attack", skill/5);
		me->add_temp("apply/parry", skill/8);
		me->add_temp("apply/cuff", skill/5);
		me->add_temp("apply/strike", skill/5);

		me->set_temp("xtg/dywq",1);
		message_vision(HBYEL+HIW"\n\n$N先天功已然大成，先天功流转不息，在周身中形成一股若隐若现的先天罡气。\n"NOR,me);
	   //定阳开了后强化剑法
     }
     me->set_temp("xtg/wuqi", skill ); 
	 me->add_temp("apply/attack", skill/5);
     me->add_temp("apply/parry", skill/10);	
     me->add_temp("apply/sword", skill/5);
	 me->add_temp("apply/armor", skill/5);
	 me->add_temp("apply/dodge", skill/5);
		
	call_out("remove_effect", 1, me, skill/15);
	
	//me->start_exert(1, "五气朝元");
	//if( me->is_fighting() )
		//me->start_busy(random(2));
	return 1;
}

void remove_effect(object me, int count)
{
        int amount;
        if(!me)  return;
      	
		if( count-- > 0 ) 
		{
			call_out("remove_effect", 1, me, count);
			return;
		}
		amount = me->query_temp("xtg/wuqi"); 
		
		if (me->query("quanzhen/force") =="pass" )
        {
			me->add_temp("apply/defense", -amount/3);
			me->add_temp("apply/armor", -amount/5);
			me->add_temp("apply/sword",-amount/8);
			me->add_temp("apply/attack", -amount/5);
			me->add_temp("apply/parry",-amount/8);
			me->add_temp("apply/cuff",-amount/5);
			me->add_temp("apply/strike",-amount/5);

	   //定阳开了后强化剑法
        }
		
			me->add_temp("apply/attack" ,-amount/5);
			me->add_temp("apply/parry",-amount/10);
			me->add_temp("apply/sword",-amount/5);
			me->add_temp("apply/armor", -amount/5);
			me->add_temp("apply/dodge", -amount/5);
			me->delete_temp("xtg/wuqi");
       
		tell_object(me, HIW"你的["+HIR+"五气朝元"+HIW+"]运行完毕，将内力收回丹田。\n"NOR);
		return;
      
}

int help(object me)
{
	write(HIC"\n先天功之「五气朝元」："NOR"\n\n");
        write(@HELP
	先天功是全真教王重阳最为重要的内功心法，修到
	高深境界，可飞花摘叶伤人于无形，其中五气朝元
	乃是先天功高深境界的心法，运转后，可以起到有
	效的命中伤害和防御效果。其中解开定阳针绝技后
	先天功大威力方可真正体现。

	特效：set 先天功 先天罡气 

	效果：大幅增加防御效果，将辛苦修炼的先天罡气
	发挥极致。
	
	指令：exert wuqi

要求：
	当前内力  2000 以上；
	当前精力  1000 以上；
	先天功法  550  级以上；
	激发内功先天功；
	开了定阳绝技后本技能飞跃；

HELP
        );
        return 1;
}
