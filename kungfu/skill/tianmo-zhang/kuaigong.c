//kuaigong.c ����
//cre by sohu@xojh,Դ��������������һս
//�����������ƣ�����������ʱ���;�����ʱ�ұ�΢΢һ�飬������ת�������泩�����ɵô�
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
       int i,j,skill;
       j=me->query_skill("tianmo-zhang",1)/100;
	   if (j<3) j=3;
	   skill=me->query_skill("tianmo-zhang",1);
       if( !target ) target = offensive_target(me);

       if( !target || !me->is_fighting(target) )
            return notify_fail("���칥������ֻ����ս���жԶ���ʹ�á�\n");

       if( objectp(me->query_temp("weapon")) )
            return notify_fail("�������ֲ���ʹ�á���ħ�ơ���\n");

       if( (int)me->query_skill("tianmo-zhang", 1) < 250 )
            return notify_fail("�����ħ�ƻ�������죬ʹ������������������\n");

       if (me->query_skill_mapped("force") != "tianmo-gong" )
          if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("����ʹ�õ������ڹ����ԡ�\n"); 
                
       if(!me->query_skill("xixing-dafa", 1))
          if(me->query_skill("tianmo-gong", 1) < 250)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ�������칥��������\n");       

       if (me->query_skill_prepared("strike") != "tianmo-zhang"
        || me->query_skill_mapped("strike") != "tianmo-zhang"
        || me->query_skill_mapped("parry") != "tianmo-zhang")
           return notify_fail("�������޷�ʹ�á���������\n");                                                                                 

       if( (int)me->query("max_neili") < 2500) 
           return notify_fail("������̫����ʹ�������칥��������\n");      

       if( (int)me->query("neili") < 1000)
           return notify_fail("����������̫����ʹ�������칥��������\n");

       message_vision(HIB"\n$N����$n����ʽ���λ���������һϲ��������$n�������У�\n"NOR,me,target);
   
       me->add("neili", -350);
  
         message_vision(HIR"\n$n��$N�������е��Ʒ����䣬���缲�籩��㹥�˹�������ʱ�����޴룬�����޼���������$n�����ϡ�\n"NOR, me, target);
         me->add_temp("apply/attack",skill/3);
		 me->add_temp("apply/damage",skill/4);
		 target->add_busy(1+random(2));
		 for (i = 0; i < j; i++)
         {
                if (!me->is_fighting(target))
                        break;
				if (!random(4)&& target->is_busy())
				{
                  message_vision(HIY"\n$nһ��С��Ϊ$N�Ʒ����У����ۡ���һ���³�һ����Ѫ��\n"NOR, me, target);
                  target->receive_damage("qi", 1000+random(3000),me);
                  target->receive_wound("qi", 500+random(1000),me);
				}
                COMBAT_D->do_attack(me, target, 0, random(3)?3:1);
        }
		// me->add("max_neili", -50);
	     
		 me->add_temp("apply/attack",-skill/3);
		 me->add_temp("apply/damage",-skill/4);
      
      me->start_perform(4,"�칥����");
      return 1;
}

string perform_name(){ return HIR"�칥����"NOR; }

int help(object me)
{
        write(HIC"\n��ħ��"+HIR"���칥������"NOR"\n");
        write(@HELP
	��ħ���������������������ǧ�������Ŀ����似���������µ���ƽ��
	ϰ������Ҫ�����似�������������������뷽֤��ʦһս����ħ�Ƶİ�
	�Ϊ����֪���칥����ץס�Է��ķ�϶����ʽ���������ٹ����Է���
	�У������Ӧ��Ͼ�ӡ�

	ָ�perform strike.kuaigong
	
Ҫ��
	��ħ��Ҫ��  250
	��ħ��Ҫ��  250
	�����ڹ�Ҫ��250
	�����Ʒ�Ҫ��250
	��ǰ����״̬: 1000
	�������Ҫ��2500
		

HELP
        );
        return 1;
}
