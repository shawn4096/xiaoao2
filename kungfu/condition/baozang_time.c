// baozang_time.c  寻宝有效时间计时
// Create By renlai

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
       int i;

       if (duration <= 1){
           tell_object(me,BLINK + HIC"突然从墓道上方传来隆隆响声，你暗道一声不好，连滚带爬的从一处洞穴爬出。\n"NOR);
           me->move("/d/city/guangchang");
		   me->unconcious();
           return 0;
       }
       me->apply_condition("baozang_time", duration - 1);
       tell_object(me,BLINK + HIC"你感觉墓道似乎有崩塌的迹象，看来要抓紧时间寻宝了。\n"NOR);	   
	return 1;
}

string query_type(object me)
{
       return "quest";
}
