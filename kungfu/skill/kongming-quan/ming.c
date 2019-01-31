// ming.c  
// by tiantian@sj 2000.6.19

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HIC"��"NOR; }

int perform(object me,object target)
{
    int lvl=me->query_skill("kongming-quan",1)+me->query_skill("xiantian-gong",1);
	
	if (!target) target = offensive_target(me);
	if (!target || !me->is_fighting(target))
		return notify_fail("�������־�ֻ����ս����ʹ�á�\n");                
    if (me->query_temp("weapon"))
		return notify_fail("���ֱֳ���������ʹ�á������־���\n");   
	if (me->query_skill("kongming-quan", 1) < 300)
		return notify_fail("��Ŀ���ȭ�в����죬������ʹ�á������־���\n");        
	if (me->query("neili") < 2000)
		return notify_fail("�������������㣬����ʹ�á������־���\n");
//	if (me->query_temp("kongming/kong"))
//		return notify_fail("������ʹ�á��ա��־���\n");      
    if (!me->query("quest/jiebai/pass"))
        return notify_fail("��û�к��ܲ�ͨ���壬����ʹ�á������־���\n");
	if (me->query_temp("kongming/ming"))
		return notify_fail("������ʹ�á������־���\n");      
	message_vision(HIC"\n$N��Хһ����ȭ����Ȼ�ӿ죬˫��ȭ��ԴԴ������ȭ���趯�������������������ˮй��ͨ��\n"NOR, me);
	me->add("neili", -300); 
	if (!me->query("quest/hubo/pass") )
		me->start_perform(2,"���־�");
	me->set_temp("kongming/ming", lvl);
	me->add_temp("apply/armor",lvl/3);
	me->add_temp("apply/parry",lvl/3);
	call_out("remove_effect", 1, me,(int)me->query_skill("kongming-quan")/10);
	return 1;
}

void remove_effect(object me,int count)
{
	
	int lvl;
	if (!me) return;
	lvl	=me->query_temp("kongming/ming");

	if (!me->is_fighting()
		||me->query_skill_mapped("cuff")!="kongming-quan"
		||count<0)
	{
		me->delete_temp("kongming/ming");
		me->add_temp("apply/armor",-lvl/3);
	    me->add_temp("apply/parry",-lvl/3);
		tell_object(me, HIC"\n��ȭ��һ�ϣ�ȫ����һ�𣬳��ֲ��ɵ�����������\n"NOR);
		return;

	}
	call_out("remove_effect",2,me,count--);
	//return;
	
}
int help(object me)
{
	write(HIY"\n����ȭ֮�����־�����"NOR"\n\n");
	write(@HELP
	����ȭ�����������ȭ�������ܲ�ͨ�ӡ����¾����л�
	�����ģ������¾��������Ե�������ǿ����ľǿ���ۡ�
	��ǿ���£��������ϡ������ƣ�������Ī������ˮ������
	��ǿ��Ī֮��ʤ����������֮����֮ʤǿ����֮ʤ�գ�
	����Ī��֪��Ī���С��ǽ���ʮ����ȴ����ѧ��������
	���ȭ��������ȭ֮���־��������ǿգ�ʵ�������黯
	ʵ�ĸ����ھ��������ޱȡ������Բ�ǿ�����������ȿ�
	�����ʵ����
	�����־��������Լ���������ʽ����ǿ����ķ���Ч��
	�Ե���Բ�ڻ�ͨ������Բ��ĵ���Ϊ���������Է�����
	���⣬����δѧ�������Ҫѧ�ᰤ��ı��⡣

	ָ�perform cuff.ming

Ҫ��	
	������� 3000 ���ϣ�
	��ǰ���� 1500  ���ϣ�
	��ǰ���� 1500  ���ϣ�
	����ȭ�ȼ� 300 ���ϣ�
	����ȭ���м�Ϊ����ȭ��
	��ȭ��Ϊ����ȭ�ҿ��֡�
	�⿪˫�ֻ������������ʹ�á�

HELP
	);
	return 1;
}