#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{
 if( duration < 1 ) return 0;
 if( !living(me) ) {
     message("vision", me->name() + "痛苦地哼了一声。\n", environment(me), me);
 }
 else {
   tell_object(me, HIB "忽然一股阴柔之极的内力在你周身经脉盘旋上下，你的内息无法调顺！\n" NOR );
   if (me->query("quest/sl/yjj/powerup")) me->apply_condition("no_exert",1); 
   
   message("vision", me->name() + "功力被拈花指力所伤，内力混乱，不由地脚步踉跄，动弹不得。\n", environment(me), me);
   }
    me->add_busy(random(3)+2);
	me->receive_wound("jing",random(200));//增加负面效果
    me->apply_condition("fx_busy", duration - 1);
    if( duration < 1 ) return 0;
    return CND_CONTINUE;
}
