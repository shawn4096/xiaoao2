#include <ansi.h>

int exert(object me)
{
	if( me->is_fighting() )
		return notify_fail("ս�����˹����ˣ�������\n");
	if ((int)me->query_skill("luohan-fumogong", 1) < 100)
		return notify_fail("����޺���ħ����Ϊ��������\n");
	if( (int)me->query("neili") < 200 )
		return notify_fail("�������������\n");
	if( (int)me->query("eff_jing") >= (int)me->query("max_jing"))
		return notify_fail("��ľ���״̬���á�\n");
      //�޸�Ϊ�������Ӻ���������õ�����
      if ((int)me->query_skill("dacheng-fofa", 1) > 100
           ||(int)me->query_skill("buddhism", 1) > 100
           || (int)me->query_skill("huanxi-chan", 1) > 100)
      {
	message_vision(HIC"$N��������˿�����һ�����ţ���"HIY"��"HIB"��"HIR"��"HIY"��"HIC"�������޺������������ö��ˡ�\n" NOR,me);

        me->receive_curing("jing", (int)me->query_skill("force")*2);
	me->add("neili", -100);
	me->start_exert(1);
	me->start_busy(2);
      }

      else
       {
        message_vision(HIM"$N��������˿�������ϥ������������������"HIY"���"HIM"����ׯ�ϣ������޺�����\n" NOR,me);
       me->receive_curing("jing", (int)me->query_skill("force")*2/3);
	me->add("neili", -100);
	me->start_exert(1);
	me->start_busy(2);
      }           
	return 1;
}

string exert_name(){ return HIC"�޺���"NOR; }

int help(object me)
{
        write(HIC"\n�޺���ħ����֮���޺�������"NOR"\n\n");
        write(@HELP
        Ҫ��   �ܹ��ƾ�
                ��ǰ���� 500 ���ϣ�
                �޺���ħ���ȼ� 100 ���ϡ�

HELP
        );
        return 1;
}
