// qzjob_jianxi.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        if (duration <= 1){
                return 0;
                }
		me->apply_condition("qzjx_job_busy",duration-1);
        return 1;
}

