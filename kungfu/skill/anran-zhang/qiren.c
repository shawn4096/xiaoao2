// cre by sohu@xojh �������
// ��ƴ�Է�������������ˡ�����������������״����
// qiren.c 
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me,object target)
{
        int i;       
        i = me->query_skill("anran-zhang", 1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !me->is_fighting(target) )
               return notify_fail("��������졹ֻ����ս���жԶ���ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�������졹������\n");   

        if( me->query_skill_prepared("strike") != "anran-zhang"
         || me->query_skill_mapped("strike") != "anran-zhang"
         || me->query_skill_mapped("parry") != "anran-zhang"
         )
               return notify_fail("����������ʹ�á�������졹������\n"); 

        if((int)me->query_skill("anran-zhang", 1) < 300 )
               return notify_fail("�����Ȼ��������Ʒ���򲻹���ʹ������������졹������\n");

        if((int)me->query_skill("strike", 1) < 300 )
               return notify_fail("��Ļ�������������죬ʹ������������졹������\n");

        if((int)me->query_skill("force",1) < 300 )
               return notify_fail("����ڹ��ȼ�������ʹ������������졹������\n");

        if (me->query("gender")=="����")
               return notify_fail("��������ȫ��ʹ��������Ȼ�����⡹������\n");

		if ((int)me->query("divorce")>0)
					return notify_fail("��������飬����ʹ�÷��ӳ���Ȼ�����������\n"); 
        if((int)me->query_str() < 60)
               return notify_fail("�������������ǿ��(60)��ʹ������������졹������\n");

        if((int)me->query_dex() < 30)
                return notify_fail("�����������Ѹ��(30)��ʹ������������졹������\n");

       
        if((int)me->query_temp("arz/qiren")) 
                return notify_fail("����������ʹ�á�������졹������\n"); 
		if (me->query("divorce"))
					return notify_fail("��������飬����ʹ�÷��ӳ������ˮ������\n");
      /*  if((int)me->query("max_qi") <= (int)me->query("eff_qi"))
                return notify_fail("�������ڵ��ľ�����ʹ�÷��ӳ����������\n"); */

        if((int)me->query("neili") < 2000 )
                return notify_fail("��ĵ�ǰ����������\n");

        if((int)me->query("jingli") < 1000)
                return notify_fail("��ĵ�ǰ����������\n");
		
		message_vision(WHT"\n$N����ۻ�ƽ���ϣ�̧ͷ���죬��������������һ�����Լ�ͷ���տ��ĳ���Ȼ������б�£��������ɻ��Σ�\n"+
                          "��ɢ���£�����һ�С�������졹����һ�������®��Բת�㱻��ʵ���޿ɶ�����\n"NOR,me,target);
		me->set_temp("arz/qiren",1);
		if (random(me->query_skill("force",1)*me->query("neili"))>target->query_skill("force",1)*me->query("neili")/2
			|| random(me->query_str())>target->query_str()/2)
		{
			 message_vision(HIG"\n\n$n���¾�����ӭ���ĵ�һ�£�˫���ཻ��$n���ɵ�����һ�Σ���ֻΪ$n�����д�\n"+
                          "�ⲻ֪$n�书��Ȼ��������$N����һ�ƶ�һ�ƣ�ȴԶ����$N�����ĺ�ʵ�ۻ롣\n"NOR,me,target);			
			 if (me->query("neili")>target->query("neili"))
			 {
				 message_vision(HIR"\n\n$n��ֵ������������֮�ʣ������ľ�������δ��֮�ʣ����ﻹ���мܵ�ס����ʱһ����Ѫ�����\n"NOR,me,target);
				 target->receive_damage("qi",me->query("neili")/5,me);				 
				 target->receive_wound("qi",me->query("neili")/20,me);
				 target->add("neili",-(int)target->query("max_neili")/4);
				 target->apply_condition("no_exert",1);
				 target->start_busy(2+random(3));
				 me->add("neili",-(int)me->query("neili")/10);
				 me->add_temp("apply/damage",i/5);
				 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				 me->add_temp("apply/damage",-i/5);
			 }
			 else 
			  {
				 message_vision(HIY"\n\n$n��ʱ������������Ϊ$N������ѹ�ȣ���Ϣ����Ϊ֮һ�ͣ����ζ�ʱ���ơ�\n"NOR,me,target);
				 target->receive_damage("qi",me->query("neili")/10,me);				 
				 target->receive_wound("qi",me->query("neili")/30,me);
				 target->add("neili",-(int)target->query("neili")/6);
				 me->add("neili",-(int)me->query("neili")/2);
			  }
		}
		else 
			message_vision(WHT"$n�³�����һ���������Ȳʵ������ã����ѵ����Ǵ�˵�еġ��������'��\n"NOR,me,target);
       
        me->add("jingli", -i/5);
       
        me->start_perform(3,"�������");
        me->delete_temp("arz/qiren");
		me->add_busy(1);
        return 1;
}

string perform_name(){ return HIW"�������"NOR; }
int help(object me)
{
        write(HIB"\n��Ȼ������"+WHT"��������졹"NOR"\n");
        write(@HELP

	����Ժ�С��Ů�ھ���ȶϳ���ǰ���֣�������ҹ˼��
	����С��Ů����������������������Ȥ�����ں���֮��
	���������������һʮ�����Ʒ������������Ʒ�����Ϊ
	��Ȼ��������ƣ�ȡ���ǽ��͡��𸳡����Ǿ���Ȼ���
	�����ߣ�Ψ�������֮�⡣���Ʒ�������������������
	�壬��һ������ۺ�������Խ������Խ��ʵ������
	�ض��ú���!
	�����������ƾ��ǿ��Ĺ����Ե��ƺͶԷ��Կ�������
	�����������������ƫ�ͣ���ô�ܵ����к󣬻�������
	������ģ���������æ����״̬���������޷�ʹ�á�


Ҫ��
	�����Ʒ�Ҫ�� 300 ������
	��Ȼ�Ʒ�Ҫ�� 300 ������
	�����ڹ�Ҫ�� 300 ������
	��ǰ����Ҫ�� 2000 ����
	��ǰ����Ҫ�� 1000 ����
	��ǰ����Ҫ�� 60  ����
	��ǰ��Ҫ�� 30  ����
	�����Ҽ����Ʒ����м�Ϊ��Ȼ��
HELP
        );
        return 1;
}
