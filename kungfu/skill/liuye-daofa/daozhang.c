// by darken@SJ

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
		int ski=me->query_skill("liuye-daofa",1)/2+me->query_skill("tiezhang-zhangfa",1)/2;
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("һ����˫��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("liuye-daofa", 1) < 100 )
                return notify_fail("�����Ҷ��������̫ǳ���޷�ʹ��һ����˫�ƹ�����\n");

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 100 )
                return notify_fail("��������Ʒ�����̫ǳ���޷�ʹ��һ����˫�ƹ�����\n");
      
        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("�������̫ǳ���޷�ʹ��һ����˫�ƹ�����\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("����������㣬�޷�ʹ��һ����˫�ƹ�����\n");
        if( (int)me->query("jingli") < 500 )
                return notify_fail("��ľ������㣬�޷�ʹ��һ����˫�ƹ�����\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "blade"
            || me->query_skill_mapped("blade") != "liuye-daofa" 
			|| me->query_skill_prepared("strike") != "tiezhang-zhangfa"
			|| me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("���׼�����򲻶ԡ�\n");

        me->add("neili", -200);
        me->add("jingli", -100);
		me->set_temp("lydf/daozhang",1);
        message_vision(BLU"$N�������������У������м������������Ʒ���Ѹ����$n��ȥ��\n" NOR,me,target);
        me->add_temp("apply/attack", ski/2);

		if (!userp(target))
        {
			me->add_temp("apply/attack", ski/3);
	        me->add_temp("apply/damage", ski/5);
			me->add_temp("apply/strike", ski/5);
			me->set_temp("lydf/daozhang",1);
        }
				
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        weapon->unequip();

        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        weapon->wield();
         if (me->query_temp("lydf/daozhang"))
        {
			me->add_temp("apply/attack", -ski/3);
	        me->add_temp("apply/damage", -ski/5);
			me->add_temp("apply/strike", -ski/5);
			me->delete_temp("lydf/daozhang");
        }
		me->add_temp("apply/attack", -ski/2);

		me->start_perform(4,"һ��Ю˫��");
        me->start_busy(1);
		me->delete_temp("lydf/daozhang");
        return 1;
}

string perform_name(){ return HIY"һ��Ю˫��"NOR; }

int help(object me)
{
        write(HIR"\n��Ҷ����֮��һ��Я˫�ơ���"NOR"\n\n");
        write(@HELP 
	��Ҷ�����������ư�������ŵ��似������������
	�ͳ��������꿹�к��ܽ�������һ��ʵ�õ�������
	���������������ϻ�������һ�����Ƶ�Ч������
	�в��ƣ����д�������ν����һ������
	
	ָ�perform blade.daozhang
		
Ҫ��  
	��ǰ���� 500 ���ϣ�
	������� 1500 ���ϣ�
	��ǰ���� 500 ���ϣ�
	�����Ʒ��ȼ� 100 ���ϣ�
	��Ҷ�����ȼ� 100 ���ϣ�
	�����ڹ��ȼ� 100 ���ϣ�
	�����Ʒ��ȼ� 100 ���ϣ�
	�����Ʒ�Ϊ�����Ʒ����ұ������Ʒ���
	�����м�Ϊ��Ҷ������
	��������Ϊ��Ҷ������
	�����ڹ�Ϊ��Ԫ���ɷ���
	�ֳֵ���������
HELP
        );
        return 1;
}