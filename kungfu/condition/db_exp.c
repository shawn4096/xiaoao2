#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{

        me->apply_condition("db_exp", duration - 1);
        
        if(random(10)==1)
	{
		tell_room(environment(me), me->name() + "看起来神采飞扬精神充沛。\n", ({ me }));
		tell_object(me, HIG"在双倍exp奖励期间，你感觉做任何事都是事半功倍。\n"NOR);
	}

        if( duration < 1 ) 
        {
        	tell_object(me, HIR"双倍经验奖励期已经结束，你的成长速度又慢了下来。\n"NOR);
        	return 0;
        }
        return CND_CONTINUE;
}

string query_type(object me)
{
	return "db_exp";
}
