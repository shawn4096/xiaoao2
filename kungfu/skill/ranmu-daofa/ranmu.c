// ranmu.c ȼľ��
// by sohu@xojh

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
void remove_effect(object me, int count);

int perform(object me, string arg)
{
      object weapon, target;
      int i, j, z;       
      j = me->query_skill("ranmu-daofa", 1);
      weapon = me->query_temp("weapon");  
      

      if( !target ) target = offensive_target(me);

      if( !target || !me->is_fighting(target) )
           return notify_fail("��ȼľ����ֻ����ս���жԶ���ʹ�á�\n");

        if (!weapon || weapon->query("skill_type") != "blade"
       || me->query_skill_mapped("blade") != "ranmu-daofa")
           return notify_fail("�������޷�ʹ����ȼľ����������\n");

        if (weapon->query("id") != "mu dao")
           return notify_fail("��û��ľ�����޷�ʹ����ȼľ����������\n");
		if (!me->query("quest/sl/rmdf/ranmu/pass"))
	       return notify_fail("��ֻ����˵��ȼľ��������δ�ڻ��ͨ���޷�ʹ����ȼľ����������\n");

        if(me->query_skill("ranmu-daofa", 1) < 160 )
                return notify_fail("���ȼľ������򲻹���ʹ������ȼľ����������\n");

        if(me->query_skill("blade", 1) < 140 )
                return notify_fail("��Ļ�������������죬ʹ������ȼľ����������\n");

        if( (int)me->query_skill("force") < 200 )
                return notify_fail("����ڹ��ȼ�������ʹ������ȼľ����������\n");

        if( (int)me->query_str() < 32)
                return notify_fail("�������������ǿ����ʹ������ȼľ����������\n");

        if( (int)me->query_dex() < 30)
                return notify_fail("�����������Ѹ�ͣ�ʹ������ȼľ����������\n");
 
       if(me->query_skill("yijin-jing", 1) < 170 )   
                return notify_fail("����׽��Ϊ�������޷�ʹ�á�ȼľ����������\n");  
	   if (me->query_skill_mapped("parry")!="ranmu-daofa"&&me->query_skill_mapped("parry")!="cibei-dao")
                return notify_fail("����мܲ��ԣ��޷�ʹ�á�ȼľ����������\n");  
       if (me->query_temp("fumo"))
			return notify_fail("����������ʹ�á���շ�ħ���񹦡�\n"); 
		
       if(me->query_temp("rmdf/ranmu")) 
			return notify_fail("����������ʹ�á�ȼľ����������\n"); 


       if (me->query("neili") < 1000)
			return notify_fail("�������������\n");
       if (me->query("jingli") < 800)
			return notify_fail("��ľ���������\n");
        me->add("neili", -300);
        me->add("jingli", -500);
        message_vision(HIR"$N����ִ�������ֵ��ƺ�Ҿ��ͻȻ����һ��������������Ͻ�շ�ħ�����������������žŰ�ʮһ����\n"
						+"��$Nǿ���ھ�֧���£����е�ľ���Ϳ�������Ħ������ʱ����һ�Ż��棬������������$n����Χס��\n"NOR,me,target);
        
		me->add_temp("apply/strength", j/10);
        me->add_temp("apply/attack", j/2); 
        me->add_temp("apply/damage", j/3);
        me->add_temp("apply/blade", j/4);

        me->set_temp("rmdf/ranmu", j);
        
		call_out("remove_effect", 1, me,(int)j/50);

        return 1;
}

void remove_effect(object me, int count)
{
       
    int j;
	object weapon;
	
	if (!me) return;
//	if (!me->query_temp("rmdf/ranmu")) return;
	
	j=me->query_temp("rmdf/ranmu");
	weapon=me->query_temp("weapon");

	if (count<0
		||!me->is_fighting()
		||!weapon
		|| weapon->query("id")!="mu dao"
		||me->query_skill_mapped("blade")!="ranmu-daofa")
	{
		
		me->add_temp("apply/strength", -j/10);
        me->add_temp("apply/attack", -j/2); 
        me->add_temp("apply/damage", -j/3);
        me->add_temp("apply/blade", -j/4);
		me->delete_temp("rmdf/ranmu");
		message_vision(HIR"$N������ȼľ�����ġ�ȼľ�������չ���\n"NOR,me);
		return;
	}
	call_out("remove_effect",1,me,count--);
}

string perform_name(){ return HIR"ȼľ��"NOR; }

int help(object me)
{
        write(HIY"\nȼľ����֮��ȼľ������"NOR"\n\n");
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
	
	ָ�perform blade.ranmu 

Ҫ��  
	��ǰ�������� 1000 ���ϣ�
	����������� 10000 ���ϣ�
	��ǰ�������� 800 ���ϣ�
	ȼľ�����ȼ� 350 ���ϣ�
	�׽���ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	�����Ʒ��ȼ� 350 ���ϣ�	
	��������Ϊȼľ������
	�����м�Ϊȼľ������ȱ�����
	�����ڹ�Ϊ�׽�񹦣�
	���ֳ�ľ����

HELP
        );
        return 1;
}
