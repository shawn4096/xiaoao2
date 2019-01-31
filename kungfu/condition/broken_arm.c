#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( !living(me) ) {
      message("vision", me->name() + "������Ѫ����������\n", environment(me), me);
   }
   else {
      tell_object(me, HIR "�������Ѫ�����������������ϵļ��١�\n" NOR );
      message("vision", me->name() + "������Ѫ����������\n",
            environment(me), me);
   }
      me->receive_wound("qi", 50);
      me->add_temp("apply/strength",-1);
      if (me->query_str() <0)
              me->add_temp("apply/strength",1);
	me->add_busy(2); 
	me->set_temp("last_damage_from", "������Ѫ����");
      me->apply_condition("broken_arm", duration-1);
   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}

string query_type(object me)
{
        return "wound";
}
