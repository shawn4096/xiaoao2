#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{    
      tell_object(me, HIC "���Ȼ�е���Ȼһ�����Ե���Ķ�������͸����֫���࣬͸�������⡣��\n" NOR );
      message_vision(HIB"$NͻȻ���ȷ������ȫ��������������һ�㡣\n"NOR, me);

      me->receive_damage("jingli", 500+random(100));
      me->receive_wound("jing", 150+random(70));

      me->set_temp("last_damage_from", "�����������˷���");
      me->apply_condition("huanyin_poison", duration - 1);
	  me->add_busy(2+random(2));
     if( duration < 1 ) return 0;
     return CND_CONTINUE;
}

string query_type(object me)
{
	return "hurt";
}
