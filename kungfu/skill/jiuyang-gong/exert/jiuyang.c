//By Kingso 2006.12.29�������

#include <ansi.h>
string exert_name(){ return HBRED HIR"������"NOR; }

int exert(object me, object target)
{
	string msg, force;
       mapping poison;

	if( !target )
		return notify_fail("��Ҫ������Ϊ˭���ˣ�\n");

	if( ! present(target,environment(me)))
		return notify_fail("�������������\n");

	

	if( me->is_fighting() || target->is_fighting())
		return notify_fail("ս�����޷��˹����ˣ�\n");

	if( target->is_busy())
		return notify_fail( target->name()+ "��æ���أ�\n");

	if( target->query("env/no_lifeheal"))
		return notify_fail( target->name()+"�ܾ���������ˡ�\n");

	if( !living(target) || !target->query("can_speak"))
		return notify_fail("�����ǻ���������˸�ʲô��\n");

	if(!(force = me->query_skill_mapped("force")))
		return notify_fail("�㻹û��ѡ����Ҫʹ�õ��ڹ���\n");

	if(me->query("max_neili") < 3500 )
		return notify_fail("���������Ϊ������\n");

	if(me->query("neili") < 500 )
		return notify_fail("�������������\n");

	if( me->query_skill("force") < 200 ) 
		return notify_fail("����ڹ��ȼ���̫�ͣ������˹����ˡ�\n");

	if( me->query_skill("medicine", 1) < 110 )
		return notify_fail("�㱾������ĵȼ��������޷�Ϊ�������ˡ�\n");

	poison = target->query_conditions_by_type("poison");


	

	msg = HBMAG HIR"$N������������"HIR""+to_chinese(force)+""HBMAG"�����������ڵ��ﴦ�������ؽ�������ת��С���졭��\n\n"NOR;
	msg +=HBMAG HIR"$nֻ��һ��������������ԴԴ�������������ڣ�ֻ��$Nͷ����˿˿����ð����\n\n"NOR;
	msg +=HBMAG HIR"$n�³�һ����Ѫ����ɫ������������ˣ��������˺ܴ�ĺ�ת��ȫ�������ޱȳ��档\n\n"NOR;

	message_vision(msg ,me ,target);			     

	target->receive_curing("qi", 600 + me->query_skill("force")/2 );
	target->receive_heal("qi", 600 + me->query_skill("force")/2 );
       target->receive_curing("jing", 200 + me->query_skill("force")/2 );
	target->receive_heal("jing", 200 + me->query_skill("force")/2 );
       target->clear_conditions_by_type("poison");
       target->clear_conditions_by_type("hurt");
       target->clear_conditions_by_type("wound");
	me->add("neili", -500);
	me->set("jiali", 0);
	me->start_busy(4);
	target->start_busy(4);
	return 1;
}

int help(object me)
{
	write(HBRED HIR"\n�����񹦡������񹦡���"NOR"\n");
        write(@HELP
       �����ۺ�ľ�������������,
       Ч���Ƿ�,�������ж������ˡ�
       ״̬�ȵĻ������������Ч��,
       �����Ǻ�����
       ��Ϊ�Լ����߱������ơ�



	Ҫ��  �������  3500 ���ϣ�
                ��ǰ����  500 ���ϣ�
                �����񹦵ȼ� 200 ���ϣ�
                ��������ȼ� 110���ϣ�
                

               
HELP
        );
        return 1;
}

