// baozang_time.c  Ѱ����Чʱ���ʱ
// Create By renlai

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
       int i;

       if (duration <= 1){
           tell_object(me,BLINK + HIC"ͻȻ��Ĺ���Ϸ�����¡¡�������㰵��һ�����ã����������Ĵ�һ����Ѩ������\n"NOR);
           me->move("/d/city/guangchang");
		   me->unconcious();
           return 0;
       }
       me->apply_condition("baozang_time", duration - 1);
       tell_object(me,BLINK + HIC"��о�Ĺ���ƺ��б����ļ��󣬿���Ҫץ��ʱ��Ѱ���ˡ�\n"NOR);	   
	return 1;
}

string query_type(object me)
{
       return "quest";
}
