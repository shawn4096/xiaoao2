#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me,int duration)
{
	if(!environment(me)) return CND_CONTINUE; 
	me->receive_wound("qi",200);
	me->receive_wound("jing",100);
	me->add_busy(2);
	me->set_temp("last_damage_from","��ħ���巢��");
	if( !living(me) ) message("vision",HIR+ me->name() + HIR"�����ӿ�ʼ��ý�Ӳ�����ϲ�������Ѫ������\n"NOR, environment(me), me);
	else 
		message_vision(HIR"$N˫ϥ������������������������������������Ȼ��ǰ������ħ��������Ԫ����\n"NOR,me);
	if(duration < 1) return 0;
	me->apply_condition("hmy_jieti",duration - 1);
	return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}