//kaishu.c ����
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string perform_name(){ return HIC"����"NOR; }

int perform(object me, object target)
{
      string msg; 
      int i;                                  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("������û�бʣ��޷�д�����飡\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("����ֻ����ս���жԶ���ʹ�á�\n");
             
      if((int)me->query_skill("yingou-bifa",1) < 200 )
         return notify_fail("��������ʷ���������죬����д�����飡\n");
      if((int)me->query_int() < 40 )
         return notify_fail("������Բ���������д�������䱮�ģ�\n");
	  
      if((int)me->query_skill("literate",1) < 200 )
         return notify_fail("��Ķ���д�ֵȼ�����������д�������䱮�ģ�\n");

      if((int)me->query_skill("qiantian-yiyang",1) < 200)
         return notify_fail("���Ǭ��һ�����ȼ�����������д�������䱮�ģ�\n");  
      
      if((int)me->query("max_neili") < 2000 )
         return notify_fail("�������̫����д�����վ������Ŀ���! \n");
      
      if((int)me->query("neili") < 500 )
         return notify_fail("�������̫���ˣ�д���Ŀ�������������\n"); 

      //if( target->is_busy() )
         //return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

      if (me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("�㼤���似���ԣ������޷�д�������项��\n");

      i = random((int)(me->query_skill("yingou-bifa",1)/50));
      //if(i < 3) i=3;
      if(i > 3) i=3;  
	  //if (userp(target)) i=1;
	
      msg = HIC"$Nһת�����б�ҡ�ϣ����д�𡸷����䱮�����ģ��鷨֮���е�Ѩ����Ѩ֮�����鷨��\n"+
               "������������������������������ΰ��������һ�����ݵ�����������з����Ͻ������翬��\n"+
               "���һ�ʲ�����\n" NOR;
      me->add("neili", - 200);
      if(random(me->query_skill("literate", 1)) > target->query_skill("literate", 1)/2
       || random(me->query_skill("force",1)) > target->query_skill("force",1)/2){
            //me->start_busy(1);
            if (!userp(target)) target->add_busy(i);
            msg += HIR"$n���鷨ֻ�����ţ��Ķ��ñ��ĵ��⾳��ֻ��$N���еı��������Լ����ϸ���ҪѨ����\n"+
                      "���裬ֻ��������ס�����ؿ�Ҫ����ͻ��ϥͷһ�飬ԭ���ѱ�$N��ת�ʿڣ�������Ѩ����\n"NOR;
			target->receive_damage("qi",random(3000),me);
					
			
      }
      else {
       
             msg += HIY"��֪$p����д���������䱮����Ԥ�Ƶõ�$P��һ��֮������д��һֱ����Ҳ�صþ���������\n"+
                      "˿����������\n"NOR;
             me->add_busy(1);
      }
      message_vision(msg, me, target);
      
	  if (me->is_fighting()&& objectp(target))
    	  call_out("kaishu_attack",1,me,target);
	    
	  me->start_perform(3,"���� �项");
      return 1;
}
int kaishu_attack(object me,object target)
{
      if (!me||!target) return 1;
    
	  message_vision(YEL"��һ�п������硸��Ůɢ�������鷨�ս���ȣ��������ˣ��ʱ���գ������������֮���ʽһ����\n"
							+"��������$n���ؿ�,��Ѫ�Ľ���\n"NOR,me,target);
	  target->receive_wound("qi",2000+random(1000),me);	
	  me->add_temp("apply/damage",me->query_skill("yingou-bifa",1)/4);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		me->add_temp("apply/damage",-me->query_skill("yingou-bifa",1)/4);
		return 1;
}



int help(object me)
{
	write(HIC"\n�����ʷ�֮�����项������"NOR"\n");
	write(@HELP
	�����ʷ�����һ�ƴ�ʦ������������Ķ����似������״Ԫ����
	�����Ըߣ����԰�ʦһ�ƴ�ʦ���似ͻ���ͽ�����Ϊ�Ĵ����
	���书����ߡ����Ź�������֮�����ڽ�һ��ָ���鷨�ں���һ
	����ʽ�м����ŵ�Ѩ�����˷���ʤ����
	�����ڴ�ʤ�������һս�����ÿ������������ͨë�ʶ�ս����
	�ÿ��鷽ʽʩչ���������䱮�����������¡�
	
ָ�perform brush.kaishu

Ҫ��	
	������� 2000 ���ϣ�		
	��ǰ���� 500 ���ϣ�
	�����ʷ��ȼ� 200 ���ϣ�
	��Ч���� 40 ���ϣ�
	����д�ֵȼ� 200 ���ϣ�
	�����ʷ�Ϊ�����ʷ�
	�����м�Ϊ�����ʷ���
	�ֱֳ���������
HELP
	);
	return 1;
}
