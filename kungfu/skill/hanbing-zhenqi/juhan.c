// by darken@SJ
// Lklv add help at 2001.10.06
// ��Ҫ��juhan����д������һ��superquest�����ֳ�����������ţ���� �ۺ�
#include <ansi.h>
inherit F_SSERVER;
string exert_name(){ return HBGRN+HIW"�ۺ���"NOR; }

int exert(object me)
{
	string msg;
	//int i;
	int lv = me->query_skill("hanbing-zhenqi",1);
    
	if (!me->is_fighting())
		return notify_fail("��ֻ����ս����ʹ�á��ۺ�������\n");

	if (lv < 350)
		return notify_fail("����Ŀǰ�ĺ�����������Ϊ���޷�ʹ�á��ۺ�������\n");

	if (me->query("neili") < 300)
		return notify_fail("����������㡣\n");
		
	if ( me->query_temp("ss/focus")>15)	
		return notify_fail("���Ѿ������ۺ��������ӵ����쾡�£�����ʩչ�����湦�ˡ�\n");

	msg = HBBLU+HIW"$N�����������Ķ�����Ϣ�����䣬�����¶ȶ�Ȼ���ͣ���Ȼ���˱���һ�㺮˪��\n"NOR;

	if (!me->query_temp("ss/focus")) {
		call_out("remove_effect", lv/5 + random(10), me);
	}  
	
	me->add("neili",-(200+random(50)));
    
	me->add_temp("ss/focus", (int)lv/200+1);
    
	if ( me->query_temp("ss/focus") > 15 )
		me->set_temp("ss/focus", 15);

	message_vision(msg, me);
	if (!me->query("quest/ss/hbzq/pass"))
		me->start_exert(1, "���ۺ�����");
	return 1;
}

void remove_effect(object me)
{
	if (!me || !me->query_temp("ss/focus") ) return;
	message_vision(HIW"$N����������ĺ���������ɢȥ�ˡ�\n"NOR,me);
	me->delete_temp("ss/focus");
}

int help(object me)
{
	write(HIW"\n��������֮���ۺ�������"NOR"\n\n");
        write(@HELP
	������������������ɽ���ɵ������似���뵱����������������
	��������̽���������һս���Ժ������������������еĽ�����
	��ɧһʱ������������ɽ�ɵ��似��Ч�����ѡ�ս����ʹ�ã���
	��������,�ж����˺����⿪��������������ɡ�
	
	ָ�exert juhan
	
Ҫ��  
	��������  350  ���ϣ�
	�������  2000 ���ϣ�
	��ǰ����  500  ���ϣ�
	��ǰ������������� 1/3 ���ϡ�

HELP
        );
        return 1;
}
