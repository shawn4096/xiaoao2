// huifeng.c �ط��
// cre by sohu
// �ط�������Դ�����ʦ̫�������޼���������

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me,object target)
{
        object weapon;
        string msg;
        int i = me->query_skill("huifeng-jian",1) / 4;

        if( !target ) target = offensive_target(me);

         if( !objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("���ط����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("����ڹ����Ƕ����ķ����޷�ʹ������ķ���\n");
        if( me->query_skill("linji-zhuang", 1) < 180 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�á��ط������\n");
        if( me->query_skill("huifeng-jian", 1) < 180 )
                return notify_fail("��Ľ�����δ���ɣ�����ʹ�á��ط������\n");
        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("������û�н����޷�ʹ�á��ط������\n");

        if(me->query_skill_mapped("parry") != "huifeng-jian")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�á��ط������\n");
        if(me->query("max_neili") < 1500 )
                return notify_fail("���������Ϊ����������ʹ�á��ط������\n");
        if(me->query("neili") < 500 )
                return notify_fail("�������������㣬����ʹ�á��ط������\n");
        if(me->query("jingli") < 500 )
                return notify_fail("�����ھ������㣬����ʹ�á��ط������\n");
        if(me->query_temp("miejue"))
                return notify_fail("������ʹ�á��ط������\n");
        if(me->query_skill("sword", 1) < 150 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ�á��ط������\n");
      

        message_vision(HIC "$N�����������ף�������������������$N��$n��������ȥ����һ�̣���һ����˲Ϣ���̳����У�����֮�����͡�\n"+
							weapon->query("name")+HIC"΢�࣬��һ�б㼴��������������Է����У�����ֱָ$n����ҪѨ����ֱ�Ƿ�����˼��\n"NOR,me,target);
        me->add("neili",-200);
		me->add("jingli",-100);
		me->add_temp("apply/attack",i*2);
		me->add_temp("apply/damage",i);
		me->set_temp("hfj/huifeng",1);
        message_vision(HIR"�����$N"+weapon->query("name")+HIR"������������ָ����$n�ʺ�!\n"	NOR,me,target);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
		
		message_vision(HIY"ȴ��$NƮ����ϣ�����оٽ�����������$n��أ������ѷ�ס��$n��������֮�ء�"NOR,me,target);
		target->add_busy(2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
		
		message_vision(HIG"$N��ʱ�ӽ�б�ã�����$n����\n"NOR,me,target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/attack",-i*2);
		me->add_temp("apply/damage",-i);
		me->start_perform(3,"���ط����"); 
		me->delete_temp("hfj/huifeng");
		me->start_busy(1);
		
        return 1;
}

string perform_name(){ return HIC"�ط��"NOR; }

int help(object me)
{
        write(HIW"\n�ط������֮���ط������"NOR"\n\n");
        write(@HELP
	�ط���������Ƕ�ü����֮�أ���ɽ��ʦ����������ʱ�ھ���
	��Ϊ�ḻ�������ǳ�������һ���������ϣ���ϼҴ���ѧ��
	�书���輫Ϊ��񡣺�������������ã�������������ʮ��
	��󳹴��򣬳���Ϊ�ᣬ������ü��ѧ--�ط��������
	�ط�������ʦ̫�ڹ�������ս���޼�ʱ��ʩչ������������
	����ʽ������Ϭ���������ڿ죬��ʱ���ڿ������У���������
	����ʤ�������в������ͻ�ɥ���ڴ���֮�¡�

	ָ�perform sword.huifeng

Ҫ��
	��ǰ���������� 500 ���ϣ�
	������������� 1500 ���ϣ�
	��ǰ���������� 500 ���ϣ�
	�ط�������ȼ� 180 ���ϣ�
	�ټ�ʮ��ׯ�ȼ� 180 ���ϣ�
	�����ڹ�Ϊ�ټ�ʮ��ׯ��
	��������Ϊ�ط��������
	�����м�Ϊ�ط��������
	�ֳֽ��������

HELP
        );
        return 1;
}


