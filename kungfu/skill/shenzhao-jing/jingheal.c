// jingheal.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
/*
	if ((!target) || target->query("id")!=me->query("id"))
		return notify_fail("��Ҫ������Ϊ˭������\n");
*/
	int med;
	if ( userp(me) && (me->query("quest/szj/pass")!=3) && !me->query("quest/shenzhao/laozu"))
	   return notify_fail("����δ�⿪���վ�������Ҫ����\n");
	
		
	if (!target) target = me;
	med=me->query_skill("medicine",1);
	if( me->is_fighting() || target->is_fighting())
		return notify_fail("ս�����޷��˹�������\n");

	if( (int)me->query_skill("shenzhao-jing",1) < 500 )
		return notify_fail("������վ��ڹ���Ϊ������\n");

	if( me->is_busy() )
		return notify_fail("��������æ���أ����п��˹���\n");

	if( target->is_busy())
		return notify_fail(target->name()+"������æ���أ�\n");

	if( (int)me->query("max_neili") < 15000)
		return notify_fail("���������Ϊ������\n");

	if( (int)me->query("neili") < 2000)
		return notify_fail("�������������\n");

	if( (int)target->query("eff_jing") >= (int)target->query("max_jing"))
		return notify_fail("ֻ�о����������Ҫ������\n");

	if( (int)target->query("eff_jing") < (int)target->query("max_jing") / 10)
		return notify_fail("����������أ����ܲ��������𵴣�\n");

	if ( me != target)
		message_combatd( HIC "$N���������������վ��ڹ���������������$n�����ţ�������ס$n��������ؽ���ת����....\n\n"HIY "���˲��ã�$n��ͷ��ð������ĺ��飬���ϵ�ƣ��ģ��Ҳ������ˡ�\n" NOR, me, target);
	else 
 		message_combatd( HIC "$N���������������վ��ڹ��������������ں����ţ�������ס��������ؽ���ת����....\n\n"HIY "���˲��ã�$N��ͷ��ð������ĺ��飬���ϵ�ƣ��ģ��Ҳ������ˡ�\n" NOR, me);

	
	target->receive_curing("jing", med/10 + (int)me->query_skill("force")/2 );
	if( (int)target->query("jing") > (int)target->query("eff_jing") )
		target->set("jing", (int)me->query("eff_jing"));
	
	me->add("neili", -500);
	me->start_busy(3);
	target->start_busy(2);
	return 1;
}


string exert_name(){ return HIY"�ƾ�"NOR; }

int help(object me)
{
        write(WHT"\n���վ����ƾ�����"NOR"\n");
        write(@HELP
	��������ī��÷���������������̶����һ���ڹ����ؾ�
	����ϰ�ô��ڹ������ִ��ڵ��ƣ����ƿ��Ķ��꣬���վ�
	��ϰ�õ������硣������Ե�õ�����ָ�㣬�ɸ���һ��¥
	Ϊ���������վ���Ϊ���Ǿ��еĶ����书�ص㣬�ܹ���Ϊ
	�����׶Σ���һ���ɶ���ָ�㣬�ڶ����ɵ���ָ�㡣����
	�ν����Ե�ɺ�Ϊ���ճ��״�ɣ�
	�����������վ����������Լ�������״�������ҿ��Ի�
	��ȥ���Լ����и����˾���Ķ��ء�
			
	ָ�exert jingheal

Ҫ��:   
	��ǰ������ 2000  ���ϣ�
	�������� 15000 ���ϣ�
	���վ����ȼ� 500 �����ϣ�
	�����ڹ��ȼ� 500 �����ϣ�
	�����ڹ����վ���
        
HELP
        );
        return 1;
}

