//caoshu.c ����
//edit by sohu,
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

string perform_name(){ return HIM"�� ��"NOR; }
int perform(object me, object target)
{
      string msg; 
      int i,damage,p,drk;
	  
      object weapon = me->query_temp("weapon");
	  drk=me->query_conditions("drunk");
      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("������û�бʣ��޷�д�����飡\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("����ֻ����ս���жԶ���ʹ�á�\n");
             
      if( (int)me->query_skill("yingou-bifa",1) < 300 )
         return notify_fail("��������ʷ���������죬����д���飡\n");
      
      if( (int)me->query_skill("literate",1) < 220 )
         return notify_fail("��Ķ���д�ֵȼ�����������д�����飡\n");  
      if( (int)me->query_int() <45 )
         return notify_fail("������Բ���������д�����飡\n");  
      if( (int)me->query_skill("qiantian-yiyang",1) < 300 )
         return notify_fail("���Ǭ��һ�������ȼ�����������д�����飡\n");  

      if( (int)me->query("max_neili") < 3500 )
         return notify_fail("����������̫����д�������ɷ���Ĳ���! \n");
      
      if( (int)me->query("neili") < 1500 )
         return notify_fail("��ĵ�ǰ����̫���ˣ�д���Ĳ����޴����\n"); 
      
      if (me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("�������޷�д�������项��\n");

      i = me->query_skill("yingou-bifa",1)/3 + me->query_skill("brush",1) /3 + me->query_skill("literate")/2+drk;
      i = i /4;
      
	  msg = HIM"$N������裬�񱼼��ߣ�����ȫȻ�����·���ֻ���������񲡢���������а��\n"+
               "�������죬�������ߣ�ԭ��$N��ʱ���飬�����ƴ�����ġ���������������ų�\n"+
				"����ʥ�����˲���֮ʥ��\n" NOR;
	  message_vision(msg,me,target);
	  msg="\n";
      me->add("neili", - 250);
      me->add("jingli", -80);

	  me->add_temp("apply/strength", i /10);

	  me->add_temp("apply/brush",  i);
	  me->add_temp("apply/attack", i/2);
	  me->add_temp("apply/damage", i/3);

	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  

      if (me->is_fighting(target))
	      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  

	  if (me->is_fighting(target))
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
	  if (me->is_fighting(target))
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
	  me->add_temp("apply/strength", -i/10);
	  
me->add_temp("apply/attack", -i/2);
	  me->add_temp("apply/brush", -i);
	  me->add_temp("apply/damage", -i/3);

      if( (random(me->query_skill("literate", 1)) > target->query_skill("literate", 1)/2
           || random(me->query_skill("force",1)) > target->query_skill("force",1)/2)
           && me->is_fighting(target)
           && present(target,environment(me))){
          if (!userp(target))
          {
			  target->add_busy(4);
          }
          else target->add_busy(2);             
          damage = (int)me->query_skill("yingou-bifa", 1);               
          damage = damage/2 + random(damage);
          damage = damage * i * 2 / 3;
	  if (damage > 5000 ) damage = 5000;
          target->receive_damage("qi", damage,me);
          target->receive_wound("qi", damage/3,me);  
	  msg += HIB"ͻȻ$N�ʷ��â������д�����������������Ǹ��������֣����һ�ʹ���������ֱ��\n"+
                    "����$n���ϣ���ʱ��Ѫֱ����$n���������˺ü�����\n"NOR;
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      msg += "( $n"+eff_status_msg(p)+" )\n";
	  if(userp(me) && me->query("env/damage"))
		  tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR); 

	  if(userp(target)&& target->query("env/damage")) 
		  tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR); 
	  }
      else {
          me->start_busy(1);
          msg += HIG"$p���·�����Х���������䣬����һ�󼲷磬����$P��ȥ�������������������˲���\n"+
                    "�����ؽ������ᣬֻ��$p���в�ס����������ߺ��������$P���ǵͰ���������������\n"+
                    "$p���˸�����൱��\n"NOR;
          if (!(target->query("neili")< 200)) 
			  target->add("neili",- 100);
       }
       message_vision(msg, me, target);
	   
	   
       
	   me->start_perform(4,"�����项");

	   return 1;
}



int help(object me)
{
	write(HIM"\n�����ʷ�֮�����项������"NOR"\n");
	write(@HELP
	�����ʷ�����һ�ƴ�ʦ������������Ķ����似������״Ԫ����
	�����Ըߣ����԰�ʦһ�ƴ�ʦ���似ͻ���ͽ�����Ϊ�Ĵ����
	���书����ߡ����Ź�������֮�����ڽ�һ��ָ���鷨�ں���һ
	����ʽ�м����ŵ�Ѩ�����˷���ʤ����
	�����ڴ�ʤ�������һս�����á����项����������ͨë�ʶ�ս
	�����ÿ��鷽ʽʩչ�����������������������¡�������鷨
	֮���������ھ���״̬�������ʵ���������ʽ��������
	
ָ�perform brush.caoshu

Ҫ��	
	������� 3500 ���ϣ�		
	��ǰ���� 1000 ���ϣ�
	�����ʷ��ȼ� 300 ���ϣ�
	Ǭ��һ���ȼ� 300 ���ϣ�
	��Ч���� 45 ���ϣ�
	����д�ֵȼ� 220 ���ϣ�
	�����ʷ�Ϊ�����ʷ�
	�����м�Ϊ�����ʷ���
	�ֱֳ���������
HELP
	);
	return 1;
}