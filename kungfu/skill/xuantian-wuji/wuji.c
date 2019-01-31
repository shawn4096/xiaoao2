//wuji.c

#include <ansi.h>
void remove_effect(object me,int skill);


string exert_name() {return HIW"日月无极"NOR;}

int exert(object me)
{      
    int skill;
    skill = me->query_skill("xuantian-wuji", 1)/10;
       
	if ( !me->is_fighting())
		return notify_fail("你只能在战斗中使用「无极」！\n");

	if( (int)me->query_skill("xuantian-wuji", 1) < 180 )
		return notify_fail("你的玄天无极功修为不够，无法使用「无极」！\n");

	if (me->query_skill_mapped("force") != "xuantian-wuji")
		return notify_fail("其它内功有「日月无极」吗？\n");

	if( (int)me->query("neili") < 300 )
		return notify_fail("你目前的内力太少了，无法使用「日月无极」！\n");

	if( (int)me->query("max_neili") < 1500 )
		return notify_fail("你的内力修为这么差，还想使用「日月无极」？\n");

    if(me->query_temp("xtwj/riyue"))
		return notify_fail("你正在运用「日月无极」心法！\n");   
	

	message_vision(HIC "$N运起玄天无极心法，只见$N全身被一团若隐若现的真气包裹起来，飘然若仙。\n" NOR, me);
    me->add_temp("apply/parry", me->query_skill("xuantian-wuji", 1)/2);
    me->add_temp("apply/armor", me->query_skill("xuantian-wuji", 1)/2);
	
	me->add("neili", -300);
    
	me->set_temp("xtwj/riyue",skill);
	
	
	if (me->query_skill("xuantian-wuji",1)<450)
    {
		me->start_exert(2, "「无极」");
    }
	call_out("remove_effect", 1, me, skill);
	return 1;
}

void remove_effect(object me, int count)
{
	
	 if (objectp(me)) {
        if  ( !me->is_fighting() || count < 0 ) {
			
        
			me->delete_temp("xtwj/riyue");
			me->add_temp("apply/parry", -me->query_skill("xuantian-wuji", 1)/2);
			me->add_temp("apply/armor", -me->query_skill("xuantian-wuji", 1)/2);
			message_vision(HIC"\n$N的玄天无极功运行完毕，将内力收回丹田。\n"NOR, me);
			return;
		}
		call_out("remove_effect", 2, me, count -1);
        return;

	}
}


int help(object me)
{
        write(WHT"\n玄天无极功「日月无极」："NOR"\n");
        write(@HELP
	此「无极」一式，乃是以昆仑派内功心法玄天无极功作为基础，
	以无上玄功化日月精华为无极气盾，提高自身防御的同时，有
	几率使对方攻击无效！
	
	exert wuji

要求:
	玄天无极功 180 级以上；
	最大内力 1500 点；
	当前内力 300 点；
              
HELP
        );
        return 1;
}


