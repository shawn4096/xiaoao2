// this condition used by dugu-jiujian's perform poqi��

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{
   	if (duration < 1) {
          	message_vision(HIC"$N�˹����˺󣬳���һ�������о���Ѩ�������𽥻ָ��ˡ�\n" NOR, me);
          	//me->add_temp("apply/dodge",(int)me->query_temp("dgb/ban"));
          	//me->delete_temp("dgb/ban");
          	return 0;
    	}
   	if (!duration) return 0;
   	
   	if( !living(me) ) {
          	message_vision(HIC"$N������ʹ����Ȼ�䵤�ﲿλһ���ʹ�����������ƺ�һ�������ζ�ʱ�鴤��\n" NOR, me); 
       	}
   	
   	else {
          	message_vision(HIR"$Nȫ������һƬ���ң������ʹ���������޷���ת��\n" NOR, me); 
       	}
		me->receive_damage("qi",random(1000),"���¾Ž�����ʽ���˶�");
		me->receive_damage("neili",200+random(1000));
		me->set_temp("last_damage_from", "���¾Ž�����ʽ����");
		if (me->query("neili")<0) me->set("neili",0);
		
   		me->add_busy(random(2)+1);
   		me->apply_condition("dgjj_poqi", duration - 1);
   		return CND_CONTINUE;
}

string query_type(object me)
{
        return "wound";
}
