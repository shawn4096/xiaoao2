// ѩ�ȱ��� xuegu_bieqi.c
// created by sohu@xojh
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
		
	//	if (environment(me)->query("xueceng")>2)
		//{
			me->receive_damage("qi",500);
			me->receive_damage("jing",200);
		//}
	     
		 if(!objectp(me->query_temp("last_damage_from")))
	     	me->set_temp("last_damage_from","����ѩ���б�����");
		 message_vision(WHT"�˵ؿ�����Ϊϡ����$N�о����Ǳ�����\n"NOR,me);
             me->apply_condition("xuegu_bieqi",duration-random(2));
       	     me->add_busy(1);
      
      if( duration < 1 ) return 0;
      return CND_CONTINUE;
}

string query_type(object me)
{
        return "wound";
}
