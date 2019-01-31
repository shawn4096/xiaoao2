#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{

        me->apply_condition("dhd_cd", duration - 1);       
    
        if( duration < 1 ) 
        {
        	tell_object(me, HIR"大还丹的药性已过，你又可以使用了。\n"NOR);
        	return 0;
        }
        return CND_CONTINUE;
}

string query_type(object me)
{
	return "dhd_cd";
}