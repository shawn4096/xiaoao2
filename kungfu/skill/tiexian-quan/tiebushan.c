//tiexian.c ����������
//by sohu
//�Ű���

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIW"����������"NOR; }

int perform(object me, object target)
{
	object weapon;
	int skill;


	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("��������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("�������ֲ��ܴ��С�\n");

	if( (int)me->query_skill("tiexian-quan", 1) < 100 )
		return notify_fail("�������ȭ��������죬�޷�ʹ��������������\n");

	if ( me->query_skill_mapped("cuff") != "tiexian-quan"
	|| me->query_skill_mapped("parry") != "tiexian-quan")
		return notify_fail("�������޷�ʹ��������������\n");

	if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("��Ļ����ڹ������ߡ�\n");
	if( (int)me->query_skill("cuff", 1) < 100 )
		return notify_fail("��Ļ���ȭ�������ߡ�\n");

	if((int)me->query("max_neili") < 3000 )
		return notify_fail("������������Ϊ�������޷�ʹ�á���������������\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("�㵱ǰ����̫��������ʹ�á���������������\n");
	if( me->query_temp("txq/tiebushan") )
		return notify_fail("������ʹ�á���������������\n");
	message_vision(WHT "\n$N�����˹�����ת������������������ʩչ������ȭ�ġ���������������\n"NOR,me);
	me->add_temp("apply/armor",skill/6);
	me->add_temp("apply/defense",skill/5);
	me->add_temp("apply/constitution",skill/30);
	me->set_temp("txq/tiebushan",skill);

	call_out("remove_effect",1,me,(int)skill/50);

	
	return 1;
}
int remove_effect(object me,int count)
{
	int skill;
	if (!me) return 0;
	skill=me->query_temp("txq/tiebushan");
	if (!me->is_fighting()
		||count<0)
	{
		me->add_temp("apply/armor",-skill/6);
		me->add_temp("apply/defense",-skill/5);
		me->add_temp("apply/constitution",-skill/30);
		me->delete_temp("txq/tiebushan");
		message_vision(WHT "\n$Nͻ��һ���������������������������չ���\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me,count--);
	
}
int help(object me)
{
        write(CYN"\n����ȭ֮����������������"NOR"\n");
        write(@HELP
	����ȭ���ǽ�����������Ű����ľ�ѧ�����䳣��������
	��������ţ������������һ��������������ȭһ������
	���г��ߣ���Ϊ�ķ�������ͬʱҲ����һ���������Ĺ�Ч

	ָ�perform cuff.tiebushan

Ҫ��  
	�����������  1400 ���ϣ�
	��ǰ��������  500  ���ϣ�
	����ȭ���ȼ� 250 ���ϣ�
	�����ڹ��ȼ� 250 ���ϣ�
	����ȭ���ȼ� 100 ���ϣ�
	����ȭ������ȭ��
	�����м�����ȭ��
	�����ұ�����ȭ��
HELP
        );
        return 1;
}
                                                                                                                                                    