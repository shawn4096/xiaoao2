// no_force.c

#include <login.h>

int update_condition(object me, int duration)
{
	if (duration < 0) return 0;
	me->apply_condition("no_jiali", duration - 1);
	return 1;
}

string query_type(object me)
{
	return "busy";
}
