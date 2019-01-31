#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{

        me->apply_condition("buff", duration - 1);
     /*   
        if(random(10)==1)
	{
		tell_room(environment(me), me->name() + "突然浑身散发出一股逼人的气势。\n", ({ me }));
		tell_object(me, HIW"你感觉自己的动作变得随心所欲，而且似乎有用不完的力量。\n"NOR);
	}*/

        if( duration < 1 ) 
        {
			//消除buff的威力,也可能取消debuff。
			me->delete_temp("apply/attack");
			me->delete_temp("apply/damage");
            me->delete_temp("apply/strength");
			me->delete_temp("apply/cuff");
			me->delete_temp("apply/strike");
			me->delete_temp("apply/hand");
		    me->delete_temp("apply/leg");
			me->delete_temp("apply/sword");
			me->delete_temp("apply/blade");
			me->delete_temp("apply/dodge");
			me->delete_temp("apply/parry");
			me->delete_temp("apply/dex");		    
			
        	tell_object(me, HIR"忽然，你气势一松，浑身似乎像散了架一般。\n"NOR);
        	return 0;
        }
        return CND_CONTINUE;
}

string query_type(object me)
{
	return "buff";
}
