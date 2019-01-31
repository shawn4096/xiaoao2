// qudu.c for hamagong
// Modified by snowman@SJ

#include <ansi.h>

int exert(object me)
{
	mapping poison;

	if( me->is_fighting() )
		return notify_fail("ս�����˹�������������\n");

	if ((int)me->query_skill("hamagong", 1) < 350)
		return notify_fail("��ĸ�󡹦����Ϊ��������\n");

	if ((int)me->query_skill("poison", 1) < 150)
		return notify_fail("��ԡ����������Ǻܾ�ͨ��\n");

        if( me->query("oyf/hamagong") < 1 ) 
                return notify_fail("��ĸ�󡹦����Ϊ��������\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("�������������\n");

	poison = me->query_conditions_by_type("poison");
	if (!mapp(poison)) 
		return notify_fail("���������˿��������С��������������ؽ��˼�����\n");
    		
	write( HIW"\n�㵹����Ϣ��ͷ�½��ϣ���Ѫ���У��������ӽ�������֮�����˳�ȥ��\n" NOR);
	message("vision", HIW+me->name()+"���ϰ���һ�ּ������ſں���һ����\n"NOR, environment(me), me);
	me->clear_conditions_by_type("poison");
	me->add("neili", -500);
	me->start_busy(6);
	return 1;
}

string exert_name(){ return HIC"����"NOR; }

int help(object me)
{
	write(WHT"\n��󡹦����������"NOR"\n");
	write(@HELP
	ŷ����Ķ��ž�����󡹦����������ѧ�еľ�������
	�Դ������������ɷ���ֶ�����µ�һ�ĳƺź���
	��󡹦������Ѱ���书�����ӹ������ס�����ת����
	֮�������ǵ�������������ľ�����
	�����������ǽ���󡹦������ת�������Ч��������
	������ʹ����������ת�󽫶������ԱƳ����⣬�ǰ�
	��ɽׯ�Ķ����ڹ��ķ���

	ָ�exert qudu

Ҫ��
	��ǰ���� 1000 ���ϣ�
	�����ڹ� 350 �����ϣ�
	�������� 150 �����ϣ�
	��󡹦�� 350 �����ϣ�
	��Ҫ��Ϊŷ�������ӣ�
HELP
);
	return 1;
}