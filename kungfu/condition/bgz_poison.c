#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	if( !living(me) ) {
		message("vision",HIB + me->name() + HIB"����һ���������ʱ����һ����\n"NOR, environment(me), me);
	}
	else {
		tell_object(me, HIB "��Ȼһ�ɺ�����ͷ���������ӣ��������������еľ����׹�ץ�������ˣ�\n" NOR );
		message("vision", HIB + me->name() + HIB"һ��鴤����ɫ�����ɰ׶��ڣ���Ȼ�ж��ˡ�\n"NOR,
				environment(me), me);
		me->receive_damage("qi", 150+random(100),"�����׹�צ������" );
		if(userp(me))
			me->receive_wound("jing", 80+random(50),"�����׹�צ������");
		else me->receive_wound("jing", 40+random(50),"�����׹�צ������");
	}
	
 	me->add_busy(1);
	 me->set_temp("last_damage_from", "�����׹�צ������");
	if( duration < 2 ) return 0;
	me->apply_condition("bgz_poison", duration - 1);
	return CND_CONTINUE;
}

string query_type(object me)
{
	return "poison";
}
