#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( !living(me) ) {
      message("vision", me->name() + "ȫ����ڣ�ɢ����һ�󽹺�ζ��\n", environment(me), me);
   }
   else {
      tell_object(me, HIR "��Ȼһ�ɻ���֮��Ϯ�����̵����ֽŷ�����\n" NOR );
      tell_room(environment(me), HIR + me->name()+"ͻȻȫ��ð��������̣��촽���ѣ�˫�ֺ��ҵػ����š�\n" NOR,
                ({ me }));      
   }
      me->receive_damage("qi", 30);

		  if(userp(me))
           me->receive_wound("jing", 10);
	  
      else me->receive_wound("jing", 1);

		  me->apply_condition("hot_poison", duration - 1);
		  me->set_temp("last_damage_from", "�ȶ�����");
   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}

string query_type(object me)
{
	return "poison";
}