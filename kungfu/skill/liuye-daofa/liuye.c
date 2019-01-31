//pikan.c by sohu@xojh


#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
		string msg;
		int p,damage;
		int ski=me->query_skill("liuye-daofa",1);
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("����Ҷ������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("liuye-daofa", 1) < 160 )
                return notify_fail("�����Ҷ����������̫ǳ���޷�ʹ�á���Ҷ������������\n");

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 160 )
                return notify_fail("��������Ʒ�����̫ǳ���޷�ʹ�á���Ҷ������������\n");
      
        if( (int)me->query("max_neili") < 1600 )
                return notify_fail("�������̫ǳ���޷�ʹ�á���Ҷ������������\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("����������㣬�޷�ʹ�á���Ҷ������������\n");
        if( (int)me->query("jingli") < 500 )
                return notify_fail("��ľ������㣬�޷�ʹ�á���Ҷ������������\n");
        if( target->is_busy() )
                return notify_fail("�Է��Ѿ���æ���ң�����ʹ�á���Ҷ������������\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "blade"
            || me->query_skill_mapped("blade") != "liuye-daofa" 
			|| me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("���׼�����򲻶ԡ�\n");

        message_vision(HIG"$N�����е�"+weapon->query("name")+HIG"˲�����£��ᾢ��˸����紵��Ҷ���������$n��\n" NOR,me,target);
        
		if (random(me->query_skill("blade",1))>target->query_skill("parry",1)/2
			||random(me->query_dex(1))>target->query_dex(1)/2)
		{
		
			

	
	   		message_vision(RED"$N������Ҷ�������ľ��裬ϸ��������������˿��$n�����������Ϊ��Ӱ����\n"NOR, me, target);	
			target->add_busy(1+random(3));

		}
		else {
			msg = CYN"����$p�Ṧ׿Խ����������һ�ԡ�\n"NOR;
			me->add("neili", -100);
			message_vision(msg, me, target);
			me->start_busy(1);
		}	
		//me->start_perform(2, "��Ҷ����");
		me->add("neili", -100);
		me->add("jingli", -50);

        return 1;
}

string perform_name(){ return HIG"��Ҷ����"NOR; }

int help(object me)
{
        write(HIG"\n��Ҷ������֮����Ҷ��������"NOR"\n\n");
        write(@HELP 
	��Ҷ�������������ư�������ŵ��似������������
	�ͳ��������꿹�к��ܽ�������һ��ʵ�õ�������
	��������ҶΪ��������ϸ�壬�����ˣ���Ҷ������
	�Ƿ������������ȴ��ؽ�����Ҫ������������ӯ��Ҫ
	�������ö��ֲ�С��Ϊ��Ӱ���Ի��������似�ȼ�
	�����йء�
	
	ָ�perform blade.liuye
		
Ҫ��  
	��ǰ���� 500 ���ϣ�
	������� 1600 ���ϣ�
	��ǰ���� 500 ���ϣ�
	�����Ʒ��ȼ� 160 ���ϣ�
	��Ҷ�����ȼ� 160 ���ϣ�
	�����ڹ��ȼ� 160 ���ϣ�
	�����м�Ϊ��Ҷ������
	��������Ϊ��Ҷ����
	�����ڹ�Ϊ��Ԫ���ɷ���
	�ֳֵ�������
HELP
        );
        return 1;
}