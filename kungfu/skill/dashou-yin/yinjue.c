//yinjue.c ���ڴ���ӡ֮��ӡ��
//By sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return MAG"��ӡ�ܾ�"NOR; }
int remove_effect(object me,int count);

int perform(object me, object target)
{
	int skill;
	string msg;

		if( !target ) target = offensive_target(me);

		if( !target || !target->is_character() || !me->is_fighting(target) )
			return notify_fail("����ӡ�ܾ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");


		if( objectp(me->query_temp("weapon")) )
			return notify_fail("�������ֲ���ʹ�á���ӡ�ܾ�������\n");		
		if((int)me->query_skill("longxiang-boruo",1)<450)
            return notify_fail("��������������Ϊ������\n");	
        if( (int)me->query_skill("dashou-yin", 1) < 450 )
			return notify_fail("������ڴ���ӡ��Ϊ����������ʹ�á���ӡ�ܾ�������\n");
        if((int)me->query("max_neili",1)<5000)
            return notify_fail("���������Ϊ̫���޷�ʹ�ñ��ơ�\n");                        
        if( (int)me->query("neili", 1) < 1500 )
			return notify_fail("����������̫��������ʹ�á���ӡ�ܾ�������\n");
		if( (int)me->query("jingli", 1) < 1500 )
			return notify_fail("�����ھ���̫��������ʹ�á���ӡ�ܾ�������\n");
		if( me->query_temp("dsy/yinjue"))
			return notify_fail("������ʹ�á���ӡ�ܾ�����\n");
		if( !me->query("quest/dls/dsy/yinjue/pass"))
			return notify_fail("����˵������ӡ�ܾ�������δѧ�ᡣ\n");
		if (me->query_skill_mapped("hand")!="dashou-yin"
			||me->query_skill_mapped("parry")!="dashou-yin"
			||me->query_skill_prepared("hand")!="dashou-yin")
			return notify_fail("��û�м���������ʹ�á���ӡ�ܾ�������\n");
		
		
		skill=me->query_skill("dashou-yin",1);

		message_vision( MAG"$N" MAG "�ͺ�һ��������Ĭ����ʮ��·��ӡ�������ϸ������Ʋ��ϱ任��ʩչ�����ھ�ѧ��"HIY"��ӡ�ܾ�"NOR"��!\n" NOR,me,target);

		me->add("neili", -150);
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/hand",skill/4);
		me->add_temp("apply/strength",skill/20);
		me->add_temp("apply/defense",skill/4);
		remove_effect(me,(int)skill/30);
		me->set_temp("dsy/yinjue",skill);
		return 1;
}
int remove_effect(object me,int count)
{
	int skill;
	if (!me||!me->query_temp("dsy/yinjue")) return 0;
	skill=me->query_temp("dsy/yinjue");
	if (!me->is_fighting()
		||me->query_skill_mapped("hand")!="dashou-yin"
		||me->query_skill_prepared("hand")!="dashou-yin"
		||me->query_skill_mapped("parry")!="dashou-yin"
		||count--<0	)
	{
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/hand",-skill/4);
		me->add_temp("apply/defense",-skill/4);
		me->add_temp("apply/strength",-skill/20);

		me->delete_temp("dsy/yinjue");
		message_vision(MAG"$N��Ȼ�����һ������������й����ӡ���Ĺ�����\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me,count);
}
int help(object me)
{
        write(HIY"\n���ڴ���ӡ����ӡ�ܾ�����"NOR"\n");
        write(@HELP
	���ڴ���ӡ��������ӡ�ܾ���,�����ڴ���ӡ����ɵ���ʽ
	�������Ʒ׷����ӣ��任��ˣ���Ч��ͬ�����������и���
	�ܽ������ʽ����Ϊ��ʮ��ʽ��һ���ǳɣ������޴�
	ע�⣺
		set ӡ�� �������� ���ӱ���	
		set ӡ�� ��վ�   ���ӷ���
		set ӡ�� ��ƿ��	  ���Ӹ���
		set ӡ�� ������   ������
		set ӡ�� �ܾ�	  �ۺ�����
	ָ�perform hand.yinjue

Ҫ��  
	��ǰ���� 1500 ���ϣ�      
	������� 5000 ���ϣ�
	��ǰ���� 1500 ���ϣ�  
	���ڴ���ӡ�ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	�����ַ�Ϊ���ڴ���ӡ;
	�����м�Ϊ���ڴ���ӡ��
	�����ڹ�����������;
	���ַ�����ӡ��
	
HELP
        );
        return 1;
}

