// wakeup.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{

	  if ( userp(me) && (me->query("quest/szj/pass")!=3) && !me->query("quest/shenzhao/laozu"))
	   return notify_fail("����δ������������վ����޷�ʹ�����ֹ��ܡ�");

	if ( !target || !target->is_character() )
		return notify_fail("��Ҫ����������˭��\n");

	if( me->is_fighting() || target->is_fighting())
		return notify_fail("ս�����޷��˹����ˣ�\n");

	if(target == me)
		return notify_fail("�㲻��Ϊ�Լ������Լ���\n");

	if(!target->query_temp("noliving/unconcious") )
		return notify_fail("��ֻ�ܾ��ѻ��Բ��ѵ��ˣ�\n");

	if(!userp(target))
		return notify_fail("��ֻ�ܾ�����ң�\n");

	if( (int)me->query_skill("shenzhao-jing", 1) < 500 )
		return notify_fail("������վ���Ϊ������\n");

	if( (int)me->query("max_neili") < 12000 )
		return notify_fail("������������Ϊ������\n");

	if( (int)me->query("neili") < 5000 )
		return notify_fail("�������������\n");
	if( (int)me->query("jingli") < 2000 )
		return notify_fail("��ľ���������\n");

	if( (int)target->query("eff_qi") < (int)target->query("max_qi") / 10 )
		return notify_fail( target->name() + "�Ѿ����˹��أ����ܲ�����������𵴣�\n");

	message_combatd(HIW"$N��������,����$n,Ȼ����������$n���ģ������ؽ����վ���������$n����....\n\n���˲��ã�$n���������ѹ�����\n" NOR, me, target );

	target->receive_curing("qi", 10 + (int)me->query_skill("force",1)/3 );
	target->add("qi", 10 + (int)me->query_skill("force",1)/3 );
	if( (int)target->query("qi") > (int)target->query("eff_qi") )
		target->set("qi", (int)target->query("eff_qi"));

	//target->remove_call_out("revive");
	target->revive();
	target->reincarnate();
 
	me->add("neili", -5000);
	me->add("jingli",-2000);
	me->set("jiali", 0);
	me->start_busy(5);
	target->start_busy(5);
	return 1;
}

string exert_name() {return HBWHT"����"NOR;}


int help(object me)
{
        write(WHT"\n���վ������ѡ���"NOR"\n");
        write(@HELP
	��������ī��÷���������������̶����һ���ڹ����ؾ�
	����ϰ�ô��ڹ������ִ��ڵ��ƣ����ƿ��Ķ��꣬���վ�
	��ϰ�õ������硣������Ե�õ�����ָ�㣬�ɸ���һ��¥
	Ϊ���������վ���Ϊ���Ǿ��еĶ����书�ص㣬�ܹ���Ϊ
	�����׶Σ���һ���ɶ���ָ�㣬�ڶ����ɵ���ָ�㡣����
	�ν����Ե�ɺ�Ϊ���ճ��״�ɣ�
	�����������վ����Ի��ѻ������࣬�޷����һ��ѡ�
			
	ָ�exert wakeup

Ҫ��:   
	��ǰ�������� 5000  ���ϣ�
	����������� 15000 ���ϣ�
	��ǰ�������� 2000  ����
	���վ����ȼ� 500   �����ϣ�
	�����ڹ��ȼ� 500   �����ϣ�
	�����ڹ����վ���
        
HELP
        );
        return 1;
}

