// by darken@SJ
#include <ansi.h>
#include <combat.h>

 inherit F_SSERVER;
 string perform_name(){ return HBRED"��������"NOR; }
 int perform(object me, object target)
 {
         int j;
         string msg;
         j = me->query_skill("tiezhang-zhangfa", 1);
		 j =j*me->query_str()/10;
         if( !target ) target = offensive_target(me);

         if( !target 
           || !me->is_fighting(target)
           || !living(target)
           || environment(target)!= environment(me))
                 return notify_fail("���������ơ�ֻ����ս���жԶ���ʹ�á�\n");

         if( objectp(me->query_temp("weapon")) )
                 return notify_fail("�������ֲ���ʹ�á��������ơ���\n");

         if( (int)me->query_skill("tiezhang-zhangfa", 1) < 250 )
                 return notify_fail("������Ʋ�����죬ʹ�������������ơ�������\n");

         if( (int)me->query_skill("guiyuan-tunafa", 1) < 250 )
                 return notify_fail("���Ԫ���ɷ�������ʹ�������������ơ�������\n");

         if( (int)me->query("jiali") < 120 )
                 return notify_fail("�����������ʹ�������������ơ�������\n");

         if (me->query_skill_mapped("force") != "guiyuan-tunafa")
                 return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

         if( (int)me->query_skill("force",1) < 250 )
                 return notify_fail("����ڹ��ȼ�����������ʹ�á��������ơ���\n");

         if( (int)me->query_str() < 55 )
                 return notify_fail("�������������ǿ����ʹ�������������ơ�����\n");

         if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
          || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
          || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                 return notify_fail("�������޷�ʹ�á��������ơ���\n");

         if( (int)me->query("max_neili") < 2000)
                 return notify_fail("����������̫����ʹ�������������ơ���\n");

         if( (int)me->query("neili") < 1000 )
                 return notify_fail("����������̫����ʹ�������������ơ���\n");
         if( (int)me->query("jingli") < 800 )
                 return notify_fail("����������̫����ʹ�������������ơ���\n");
         if( target->query_temp("pushan") )
                 return notify_fail("����ô��������\n");

         msg = HIR "\n$N������һ���������һ����������֣���ָ�ſ���ʩ�������Ʒ��е�"HIC"���������ơ�"HIR"����$n̫��Ѩ��\n"NOR;
         if ( target->query("combat_exp")/2 < random(me->query("combat_exp"))
			 ||random(me->query_str())>target->query_str()/2) 
		{
              msg += HIY"\n$n˫��һ����Ӳ�ǽ�����$N��һ�ƣ�\n"NOR;
              
			  if (target->query_str()/3 < random(me->query_str()))
			  {
                  target->add_temp("apply/strength",-me->query_str()/2);
                  target->set_temp("tzzf/pushan",me->query_str()/2);
                  target->receive_wound("qi",j/2,me);
                  target->receive_damage("qi",j*2,me);
				  if (objectp(target))
					call_out("remove_effect",(int)j/80,target);
                  msg += HIR"\nֻ��������һ����$n����Ǿ�Ȼ��Ӳ����������ˣ�\n"NOR;
                  
              } else {
                  msg += HIR"\n$n�۵����һ����Ѫ���ƺ����˼��ص����ˣ�\n"NOR;
                 
                  target->receive_wound("qi",j,me);
                  target->receive_damage("qi",j*2,me);
              }
              message_vision(msg, me, target);
              COMBAT_D->report_status(target);
         } else {
             msg += HIY"\n$n���������ͣ�����Ӳ������æת��ܿ���\n"NOR;
             msg += HIR"\n��֪$N�Ѿ���������������������������֣�\n"NOR;
             message_vision(msg, me, target);
             me->set_temp("tzzf/pushan",1);
                 if(objectp(target)
             && me->is_fighting(target))
                     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             if(objectp(target)
             && me->is_fighting(target))
                     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             me->delete_temp("tzzf/pushan");
         }               

         me->add("neili", -1000);
         me->start_busy(random(2));
         
         me->start_perform(3,"���������ơ�");
         return 1;
 }
int remove_effect(object target)
{
	int str;
	if (!target) return 0;
	str=(int)target->query_temp("tzzf/pushan");
	if (target->query_temp("tzzf/pushan"))
	{
		target->add_temp("apply/strength",str);
		message_vision(YEL"\n��$Nǿ�������ڹ����ϳ��֮�£����˵��������ƴ�Ϊ��ת,������������\n"NOR,target);
		return 1;
	}


}

int help(object me)
{
        write(HIC"\n�����Ʒ�֮���������ơ���"NOR"\n\n");
        write(@HELP 
	��������������ʮ������֮һ�����ۻ������
	���������У���ָ�ſ���������״����Է�̫
	��Ѩ�����Է�äĿ���ֵֵ�������յ��˽
	�ǵľ޴��˺������к�˫������������й�

	perform strike.pushan
		
Ҫ��
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 800 ���ϣ�
	�����Ʒ��ȼ� 250 ���ϣ�
	�����ڹ��ȼ� 250 ���ϣ�
	�����Ʒ��ȼ� 250 ���ϣ�
	��Ч����Ҫ�� 60  ���ϣ�
	�������Ҫ�� 120 ���ϣ�
	�����Ʒ�Ϊ�����Ʒ���
	�����м�Ϊ�����Ʒ���
	�����ڹ���Ԫ���ɷ���
HELP
        );
        return 1;
}