#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( !living(me) ) {
      message("vision", me->name() + "����һƬƬ����ɫ��״��ɢ����һ���ȳ�ζ��\n", environment(me), me);
   }
   else {
      tell_object(me, HIB "��Ȼð��һ�ɵ���ɫ�Ķ�����������ɴ��\n" NOR );
      tell_room(environment(me), HIB + me->name()+"ͻȻȫ��ð������ɫ�Ķ������ȳ����š�\n" NOR,
                ({ me }));      
   }
		me->receive_damage("qi", 200,"��ɰ������");

	    if(userp(me))
           me->receive_wound("jing",50,"��ɰ������");
	  
      else me->receive_wound("jing", 50,"��ɰ������");

		  me->apply_condition("hongsha_poison", duration - 1);
		  me->set_temp("last_damage_from", "��ɰ������");	  
   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}

string query_type(object me)
{
	return "poison";
}
