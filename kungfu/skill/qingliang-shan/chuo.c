// chuo.c ���־�
// by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
void remove_effect(object me,int count);

int perform(object me, object target)
{                                  
      int skill,damage;
      object weapon;
      
	  if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target))
                return notify_fail("�����־���ֻ����ս���жԶ���ʹ�á�\n");
//�ʷ��򵶷�
      if (!objectp(weapon = me->query_temp("weapon")) 
        || (weapon->query("skill_type") != "brush"&&weapon->query("skill_type") != "blade"))
                return notify_fail("����������ԣ������޷�ʹ�á����־�����\n");
      
	  if (me->query_skill_mapped("blade") != "qingliang-shan"
			||me->query_skill_mapped("parry") != "qingliang-shan"
			|| me->query_skill_mapped("brush") != "qingliang-shan")
                return notify_fail("�㼤�����ԣ������޷�ʹ�á����־�����\n");

      if( (int)me->query_skill("qingliang-shan",1) < 150 )
                return notify_fail("��������Ȳ�����죬����ʹ�á����־�����\n");      

      if( (int)me->query_skill("force",1) < 250 )
                return notify_fail("��Ļ����ڹ��ȼ�����������ʹ�á����־�����\n");  
      if( (int)me->query_skill("blade",1) < 250 )
                return notify_fail("��Ļ��������ȼ�����������ʹ�á����־�����\n");  
      if( (int)me->query_skill("brush",1) < 250 )
                return notify_fail("��Ļ����ʷ��ȼ�����������ʹ�á����־�����\n");  
      
      
      if( (int)me->query_dex() < 30 )
                return notify_fail("���������ǿ������ʹ�á����־�����\n");
      if( (int)me->query("neili") < 1500 )
		      return notify_fail("�������̫���ˣ��޷�ʹ�ó������־�����\n");
      if( (int)me->query("max_neili") < 2500 )
                return notify_fail("�������̫��������ʹ�á����־�����\n");
      if( target->query_temp("qls/chuo"))
                return notify_fail("�Է��Ѿ����ˡ����־�������Ѿ����Ͻ����ְɣ�\n");
      if(target->is_busy())
                return notify_fail("�Է��Ѿ���æ���ң�����Ѿ����Ͻ����ְɣ�\n");
           
      skill = (int)me->query_skill("qingliang-shan", 1);
      
	  damage = (int)me->query_skill("qingliang-shan", 1)+(int)me->query_skill("blade", 1)+(int)me->query_skill("brush", 1);
        
	  damage=damage*3+random(damage/3);   
      	
      message_vision(HIY"$N����"NOR+weapon->query("name")+HIY"��ˢ����һ�����������һ�𣬻���Ϊ�ʣ�ʩչ��"+HIW"�����־���"+HIY"����$n���������$n���˹�ȥ��\n" NOR, me, target);

	//  me->set_temp("qls/chuo", 1);
	  if (random(me->query_dex())>target->query_dex()/3
		  ||random(me->query_skill("qingliang-shan",1))>target->query_skill("parry",1)/2
		  ||random(me->query_int())>target->query_int()/2)
	  {
	     message_vision(HIR"$Nһ�´���$n�����ߣ�$n��ʱ�����Լ��������飬��Ѫ��ͨ��\n"NOR, me, target);
		 target->receive_damge("qi",damage,me);
		 target->receive_wound("qi",damage/4,me);
		 target->add_busy(2);
		 target->apply_condition("no_jiali",1);
		 target->apply_condition("no_exert",2);
		 target->set_temp("qls/chuo",1);
		 
	  }else	{
		me->add_busy(1);	
		message_vision(HIY"$n������Х���㿪��$N����ι�����\n"NOR,me,target);
	  }
     me->add("neili",-250);
	 me->add("jingli",-150);
     return 1;
}

string perform_name(){ return RED"���־�"NOR; }

int help(object me)
{
	write(HIC"\n������֮�����־�����"NOR"\n");
	write(@HELP
	�������������������ʿ���ž���������Ϊ�����ȿ���
	�����̹����ֿ��Ի��������������׻�˵һ��̣�һ��
	�գ���������������ΪϬ�������ڲ���������Ů�����
	��������Ҳ�����ɵ���Ҫ��ҹ���
	���־��ǽ�������������������һ����״��̹�������
	֮���Աʷ����ƴ��жԷ����ߣ���Է�ɥʧ������
	
	ָ�perform brush.chuo

Ҫ��
	����������� 2500 ���ϣ�
	��ǰ�������� 1500 ���ϣ�
	�����ȵĵȼ� 250 ���ϣ�
	�����ڹ��ȼ� 250 ���ϣ�
	���������ȼ� 250 ���ϣ�
	�����ʷ��ȼ� 250 ���ϣ�
	���������� 50  ���ϣ�
	��������Ϊ������
	�����ʷ�Ϊ������
	�����м�Ϊ������
	�ڹ����ޣ�
	�ֳֵ����������
HELP
	);
	return 1;
}
