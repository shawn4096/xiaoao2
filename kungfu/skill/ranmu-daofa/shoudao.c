// shoudao.c �ֵ�

// by sohu@xojh 

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, string arg)
{
      object weapon, target;
      int i, j, z;       
     j = me->query_skill("ranmu-daofa", 1);
     weapon = me->query_temp("weapon");  
      

      if( !target ) target = offensive_target(me);

      if( !target || !me->is_fighting(target) )
           return notify_fail("���ֵ���ֻ����ս���жԶ���ʹ�á�\n");

      if (weapon)
		   return notify_fail("���ֳ��������޷�ʩչȼľ�����С��ֵ���������\n");
	  if (me->query_skill_mapped("strike") != "ranmu-daofa"
		||me->query_skill_prepared("strike") != "ranmu-daofa")
		   return notify_fail("�����ڼ����Ʒ���ȼľ�������޷�ʹ�����ֵ���������\n");
	  if (me->query_skill_mapped("blade") != "ranmu-daofa")
		   return notify_fail("�����ڼ���������ȼľ�������޷�ʹ�����ֵ���������\n");
	  if (!me->query("quest/sl/rmdf/shoudao/pass"))
		   return notify_fail("����Ȼ��˵���ֵ�����������δ�õ����ڣ��޷�ʹ�����ֵ���������\n");

       if(me->query_skill("ranmu-daofa", 1) < 500 )
                return notify_fail("���ȼľ������򲻹���ʹ�������ֵ���������\n");

        if(me->query_skill("blade", 1) < 500 )
                return notify_fail("��Ļ���������������죬ʹ�������ֵ���������\n");
        if(me->query_skill("strike", 1) < 500 )
                return notify_fail("��Ļ����Ʒ���������죬ʹ�������ֵ���������\n");

        if( (int)me->query_skill("force",1) < 500 )
                return notify_fail("��Ļ����ڹ��ȼ�������ʹ�������ֵ���������\n");

        if( (int)me->query_str() < 80)
                return notify_fail("�������������ǿ������70��ʹ�������ֵ���������\n");

   
        if(me->query_skill("yijin-jing", 1) < 500 )   
                return notify_fail("����׽��Ϊ�������޷�ʹ�á��ֵ���������\n");  

        if(me->query_temp("rmdf/shoudao")) 
			return notify_fail("����������ʹ�á��ֵ���������\n"); 
//��շ�ħ��Ϊ���֣����������ý�շ�ħ�ӳ�
        if (me->query_temp("fumo"))
			return notify_fail("����������ʹ�ô������ȭ����շ�ħ���񹦡�\n"); 
        if (me->query("max_neili") < 15000)
			return notify_fail("����������������\n");

        if (me->query("neili") < 1000)
			return notify_fail("�������������\n");
        if (me->query("jingli") < 800)
			return notify_fail("��ľ���������\n");
		
        message_vision(HBRED+HIY"$N������ҫ���������������ǿ��֣���ʹ��ȴ�����ڡ�ȼľ��������ʽ����$n���������žŰ�ʮһ����\n"NOR,me,target);
        message_vision(HBRED+HIY"$N�˿������������䵶���ݿ�����ȫ���������书��·�ӡ�$N������ӿ��һ�����䣬����һ�죡\n"NOR,me,target);

		me->add("neili", -1500);
        me->add("jingli", -1000);
        
		me->add_temp("apply/attack", j/2); 
        me->add_temp("apply/damage", j/3);
		me->add_temp("apply/strike", j/3);

		me->set_temp("rmdf/shoudao",5);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if (me->is_fighting())
		{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
		if (me->is_fighting())
		{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
		if (me->is_fighting())
		{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
		if (me->is_fighting())
		{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
		me->delete_temp("rmdf/shoudao");
/*
		if (me->is_fighting()&&)
		{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}*/
		me->add_temp("apply/attack", -j/2); 
        me->add_temp("apply/damage", -j/3);
		me->add_temp("apply/strike", -j/3);

		me->start_perform(5,"ȼľ�ֵ�");
        return 1;
}

string perform_name(){ return HBRED+HIY"�ֵ�����"NOR; }

int help(object me)
{
        write(HIY"\nȼľ����֮���ֵ���������"NOR"\n\n");
        write(@HELP
	ȼľ�����������������ռ�����֮һ���ǵ����ļ�����似
	��������������ʮ�������в���֮�أ��书���������
	ƾ����������������������ƻ����������ޱȡ������书��
	���������ʦ��ϰ���������ʦԲ�ź󣬴��似�����޳ɣ�
	��һ����ɮ�Ħ��ƾ��С�������ݻ�ȼľ������ս������
	ʱ��ʹ�ô����似�������¡�
	
	ע�⣺��ϰ�ֵ�������Ҫ������ֻ����������޵���ɱ���
		�ȱ����Ĵȱ�֮�⣬��ɱ���ʹȱ����ں��ж����ֵ���
		���衣�мǣ��мǣ�
	
	ָ�perform strike.shoudao 

Ҫ��  
	��ǰ�������� 1000 ���ϣ�
	����������� 15000 ���ϣ�
	��ǰ�������� 800 ���ϣ�
	ȼľ�����ȼ� 500 ���ϣ�
	�׽���ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	�����Ʒ��ȼ� 500 ���ϣ�	
	�����Ʒ�Ϊȼľ������
	��������Ϊȼľ������
	�����м�Ϊȼľ������ȱ�����
	�����ڹ�Ϊ�׽�񹦣�
	�ҿ��֡�

HELP
        );
        return 1;
}
