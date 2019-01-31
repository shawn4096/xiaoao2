// huaixin.c ������
// by sohu@xojh

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int perform(object me, object target)
{

	int skill;
	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("�������ȡ�ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("ʹ�á������ȡ�ʱ˫�ֱ�����ţ�\n");

	if( (int)me->query_skill("shaolin-tantui", 1) < 200 )
		return notify_fail("��Ļ������Ȳ�����죬����ʹ�á������ȡ���\n");

	if( (int)me->query_skill("yijin-jing", 1) < 200 )
		if( (int)me->query_skill("hunyuan-yiqi", 1) < 200 )
		return notify_fail("����׽���Ԫһ���ȼ�����������ʹ�á������ȡ���\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		return notify_fail("��Ŀǰ���ڹ��޷�֧����ʹ�á������ȡ����й�����\n");  
	if (me->query_skill("leg",1)<200)
		return notify_fail("��Ŀǰ�Ļ����ȷ�����100����֧����ʹ�á������ȡ����й�����\n");  
		
	if( (int)me->query_dex() < 40 )
		return notify_fail("���������40������ʹ�á������ȡ���\n");

	if (me->query_skill_prepared("leg") != "shaolin-tantui"
		|| me->query_skill_mapped("leg") != "shaolin-tantui")
		return notify_fail("�������޷�ʹ�á������ȡ����й�����\n");  
											       
	if( (int)me->query("max_neili") < 2400 )
		return notify_fail("�������������̫��������ʹ�á������ȡ���\n");
	if( (int)me->query("neili") < 600 )
		return notify_fail("��Ŀǰ����̫�٣�����ʹ�á������ȡ���\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("�����ھ���̫�٣�����ʹ�á������ȡ���\n");
	if (me->query_temp("sltt/hxt"))
		return notify_fail("����������ʹ�á������ȡ����й�����\n");  

	skill=me->query_skill("shaolin-tantui",1);

	message_vision(HIR"\n$N���ΰ�ף����Լ���һ������΢�����������������ƺ���һ����վ���ڵ��أ���ʽ���ֵ�����Ϊ���ڵġ������ȡ�������\n" NOR,me, target);
	
		
	me->set_temp("sltt/hxt", 1);
	me->add("neili", -380);
	me->add("jingli", -180);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);

	message_vision(RED "\n$N��$n�߳�һ�Ⱥ󣬺���ԴԴ���ϣ��⻳���Ⱥ�����ʱ���߳�ȥһ�㡣\n" NOR,me,target);
	me->start_perform(3,"�������ȡ�");
	call_out("remove_hxt",1,me,(int)skill/50);
	return 1;
}
int remove_hxt(object me,int count)
{
	if (!me||!me->query_temp("sltt/hxt")) return 0;
	if (!me->is_fighting()
		||me->query_skill_mapped("leg")!="shaolin-tantui"
		||me->query_skill_prepared("leg")!="shaolin-tantui"
		||count--<0)
	{
		me->delete_temp("sltt/hxt");
		message_vision(RED"$N����һ����������һ��������й���������ȡ�������\n"NOR,me);
		return 1;
	}

	call_out("remove_hxt",1,me,count--);

}

string perform_name(){ return HBRED+HIW"������"NOR; }
int help(object me)
{
        write(HIC"\n���ֵ���֮�������ȡ�������"NOR"\n");
        write(@HELP
	���ֵ���Ϊ���������ȷ������ü�ʵ���ȹ���ǿ�����������
	��������У��öԷ�������Է��߳�һ�ž���ɱ�У�����ַ�
	��ʤ�������޿ɶ㣬�˵��������ǳ���
		
	ע�⣺�����ֵ��ȡ����ȷ����������˺�����Ӱ�����ȵı���
		�������ֻ������������������ȷ����мǣ�

	ָ�perform leg.huaixin

Ҫ��  
	����������� 2400 ���ϣ�      
	��ǰ�������� 600  ����
	��ǰ�������� 500  ���ϣ�  
	���ֵ��˵ȼ� 200 ���ϣ�
	�׽���ȼ� 200 ���ϣ�
	�����ȷ��ȼ� 200 ���ϣ�	
	�����ȷ�Ϊ���ֵ��ȣ�
	�����м�Ϊ���ֵ��ȣ�
	�����ޱ�����
	��Ч������С��40��
                
HELP
        );
        return 1;
}
