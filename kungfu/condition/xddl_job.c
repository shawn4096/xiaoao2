// xddl_job.c 

#include <login.h>

int update_condition(object me, int duration)
{
        if (duration < 0) {
              me->clear_condition("xddl_job");
                  }
        if (!duration) return 0;
        me->apply_condition("xddl_job", duration - 1);
        return 1;
}

string query_type(object me)
{
	return "job";
}
