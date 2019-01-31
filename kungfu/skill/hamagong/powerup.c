// powerup.c ��󡹦

#include <ansi.h>

inherit F_CLEAN_UP;


int exert(object me)
{
	int skill;

	//if (target != me)
	//	return notify_fail("��ֻ���Լ�ʹ�ø�󡹦�������Լ���ս������\n");
	if (me->query_skill_mapped("force")!="hamagong")
		return notify_fail("��ֻ���ø�󡹦�������Լ���ս������\n");
	if (me->query_skill("hamagong")<100)
		return notify_fail("��ĸ�󡹦��������100�����޷�������󡹦��\n");
	if (me->query_skill("force")<100)
		return notify_fail("��Ļ����ڹ�����100�����޷�������󡹦��\n");
	if ((int)me->query("neili") < 1000 )
		return notify_fail("�������������\n");

	if ((int)me->query_temp("hmg/powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("hamagong",1);
	me->add("neili", -200);
	message_vision(HBGRN+HIW "$N" HBGRN+HIW "���ڵ��ϣ�˫�ַ��أ�˫��������룬״���󡣬���ɡ����ɡ����ɡ��Ĵ��������\n"+
		"����$N���������У����ɼ��������һȦȦ�������ܲ���ɢ����\n" NOR,me);

	me->add_temp("apply/attack", skill / 10);
	//me->add_temp("apply/strike", skill / 10); //ͳһ����ת��ӣ��������ε��� by renlai
	//me->add_temp("apply/cuff", skill / 10);
	me->add_temp("apply/staff", skill / 10);
	//me->add_temp("apply/defense", skill / 3);
	//me->add_temp("apply/armor", skill / 5);
	me->set_temp("hmg/powerup",skill);

	call_out("remove_effect",1,me,skill/20);

	return 1;
}

void remove_effect(object me,int count)
{
        int skill;
		
		if (!me) return;

        skill=me->query_temp("hmg/powerup");
		if (!me->query_temp("hmg/powerup")) return;
		
		if (count<0
		||!me->is_fighting()
		||me->query_skill_mapped("force")!="hamagong")
        {
			me->add_temp("apply/attack", -skill / 10);
			//me->add_temp("apply/strike", -skill / 10);
			//me->add_temp("apply/cuff", -skill / 10);
			me->add_temp("apply/staff", -skill / 10);
			//me->add_temp("apply/defense", -skill / 3);
			//me->add_temp("apply/armor", -skill / 5);
	        me->delete_temp("hmg/powerup");
	        tell_object(me, HIG"���"HIR"����󡹦��"HIG"������ϣ��������ջص��\n"NOR);
			return;
        }
		call_out("remove_effect",2,me,count--);
}
string exert_name(){ return HIG"�����"NOR; }

int help(object me)
{
write(WHT"\n��󡹦�����������"NOR"\n");
write(@HELP
	ŷ����Ķ��ž�����󡹦����������ѧ�еľ�������
	�Դ������������ɷ���ֶ�����µ�һ�ĳƺź���
	��󡹦������Ѱ���书�����ӹ������ס�����ת����
	֮�������ǵ�������������ľ�����
	��󡾢�����Ǹ�󡹦�ľ��裬������ŷ�����ڻ�ɽ��
	���еĶ����ڹ��ķ����ǵ�ϵ��ֶ������
	ע�⣺set ��󡹦ɢ�� �Ὣ��󡶾���߶����ɢ��

	ָ�exert powerup

Ҫ��
	��ǰ���� 1000 ���ϣ�
	�����ڹ� 100 �����ϣ�
	��󡹦�� 100 �����ϣ�
HELP
);
return 1;

}
