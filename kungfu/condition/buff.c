#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{

        me->apply_condition("buff", duration - 1);
     /*   
        if(random(10)==1)
	{
		tell_room(environment(me), me->name() + "ͻȻ����ɢ����һ�ɱ��˵����ơ�\n", ({ me }));
		tell_object(me, HIW"��о��Լ��Ķ���������������������ƺ����ò����������\n"NOR);
	}*/

        if( duration < 1 ) 
        {
			//����buff������,Ҳ����ȡ��debuff��
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
			
        	tell_object(me, HIR"��Ȼ��������һ�ɣ������ƺ���ɢ�˼�һ�㡣\n"NOR);
        	return 0;
        }
        return CND_CONTINUE;
}

string query_type(object me)
{
	return "buff";
}
