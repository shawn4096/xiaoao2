// by sohu@xojh 2013

#include <ansi.h>

inherit F_SSERVER;
#include <combat_msg.h>
int perform(object me, object target)
{
        object weapon;
		int ski=me->query_skill("yanxing-daofa",1)+me->query_skill("sixiang-zhang",1);
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("�������ҵ�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("yanxing-daofa", 1) < 100 )
                return notify_fail("��Ĺ���̫ǳ���޷�ʹ�á������ҵ�������������\n");

        if( (int)me->query_skill("sixiang-zhang", 1) < 100 )
                return notify_fail("��������Ʒ�����̫ǳ���޷�ʹ�á������ҵ�������������\n");
      
        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("�������̫ǳ���޷�ʹ��һ����˫�ƹ�����\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("����������㣬�޷�ʹ�á������ҵ�������������\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "blade"
            || me->query_skill_mapped("blade") != "yanxing-daofa" 
			|| me->query_skill_prepared("strike") != "sixiang-zhang")
                return notify_fail("���׼�����򲻶ԡ�\n");

        me->add("neili", -200);
        me->add("jingli", -40);
        message_vision(HIY"$N�����ټ�ׯ���������У����Ƕ�ü�������ҵ���������Ѹ����$n��ȥ��\n" NOR,me,target);
        me->add_temp("apply/attack", ski/2);
		if (userp(me) && me->query_skill("yanxing-daofa",1)<350)
        {
			me->add_temp("apply/damage", ski/6);
			me->add_temp("apply/strike", ski/5);
        }
				
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
        //COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        if (me->is_fighting(target)&&me->query_skill("yanxing-daofa",1)>150&&me->query("class")!="bonze")
        {
			weapon->unequip();
            message_vision(HIC"$N�������쵶Ӱ�����������$nΪ$N�ĵ������Ի󣬲��Ծ����뵶Ӱ֮�С�\n"NOR,me,target);
			target->add_busy(1);
            me->add_temp("apply/attack", ski/3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
			me->add_temp("apply/attack", -ski/3);
            weapon->wield();
        }
	   me->add_temp("apply/attack", -ski/2);
       if (userp(me)&&me->query_skill("yanxing-daofa",1)<350)
        {
			
	        me->add_temp("apply/damage", -ski/6);
			me->add_temp("apply/strike", -ski/5);
        }
		me->start_perform(4,"�����ҵ�");
        me->start_busy(1);
        return 1;
}

//string perform_name(){ return HIY"�����ҵ�"NOR; }
string perform_name(){ return HIY"�����ҵ�"NOR; }


int help(object me)
{
	    write(HIY"\n���е���֮�������ҵ���\n"NOR);
        write(@HELP 
	���е������Ƕ��ҵ������ŵ��似��������
	�����Լ������ܽ�����������һ��ʵ�õ�����
	�õ����������������ϻ�����������һ��
	��Ч������Ϊɱ����ΪŨ�񣬲�Ϊ�������ţ�
	���ʦ̫��ϲ������ˣ������书�������
	���Ӵ�ʦѧϰ���׼ҵ��������ơ�
	
	ָ�perform blade.luandao

Ҫ��
	��ǰ�������� 500 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	�����Ʒ��ȼ� 100 ���ϣ�
	�����ڹ��ȼ� 100 ���ϣ�
	�����Ʒ��ȼ� 100 ���ϣ�
	�����Ʒ�Ϊ�����Ʒ����ұ������Ʒ���
	�����м�Ϊ���е�����
	�������ޡ�
	�ֳֵ�������
HELP
        );
        return 1;
}

