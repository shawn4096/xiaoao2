//By KinGSo 2006.12.25 �����ѪЧ��������
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{    
      tell_object(me,  HIR "�㱻���˵Ĳ�λ��������Ѫ��\n" NOR );
      message_vision( HIR"$N�����˵Ĳ�λ��������Ѫ��$N�������ģ��Ե���Щ������\n"NOR, me);

      me->receive_damage("qi", 150+random(200));
      me->receive_wound("qi", 150+random(200));
      me->add_busy(1);
      me->set_temp("last_damage_from", "ʧѪ����");
      me->apply_condition("liuxue", duration - 1);
      if( duration < 1 ) return 0;
     return CND_CONTINUE;
}

string query_type(object me)
{
	return "hurt";
}
