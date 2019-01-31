// no_enable.c

#include <login.h>

int update_condition(object me, int duration)
{
	if (duration < 0) 
	{
		me->clear_condition("no_enable");
		me->delete_temp("no_enable");
		return 1;
	}
	me->apply_condition("no_enable", duration - 1);
	return 1;
}

string query_type(object me)
{
	return "busy";
}
