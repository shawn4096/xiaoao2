// sanyinshou暗劲.c

#include <ansi.h>
#include <condition.h>

inherit ILLNESS;

string name() { return "sys_anjin"; }

int min_qi_needed() { return 10; }

int update_condition(object me, int duration)
{
        if( duration < 1 ) return 0;

        message("vision", HIG + me->name() + "一道暗劲涌来剧痛无比"
		          "看来是所中的三阴手暗劲发作了！\n" NOR,
                environment(me), me);

        if( !living(me) && me->query("qi") < 1 ) {
                me->set_temp("last_damage_from", "三阴手暗劲发作而");
                me->die();
                return 0;
        }
        else
                tell_object(me, HIC "你浑身一阵抽搐，然后"
		                "又连续颤动了好一阵，看来是三阴手暗劲发作了！\n" NOR );

        me->receive_wound("qi", 1000);
        me->receive_damage("jingli", 1000);
        me->apply_condition(name(), duration - 1);

        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}
