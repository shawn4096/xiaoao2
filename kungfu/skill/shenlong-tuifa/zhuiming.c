//׷����� 
//by sjxa@winnerlife
//2014-08-07

#include <ansi.h>
#include <combat.h>

 inherit F_SSERVER;

 string perform_name() {return HIC"׷�����"NOR;}

 int calc_damage(int,int,object,object);

 int perform(object me, object target)
 {
	 //������
        object weapon;
        string msg,result;
        int i,total; 
	//ʹ�������ж�
		if( !target ) target = offensive_target(me);

		if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
                 return notify_fail("��׷�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

		if (me->query_skill_prepared("leg") != "shenlong-tuifa"
            || me->query_skill_mapped("leg") != "shenlong-tuifa"
			|| me->query_skill_mapped("parry") != "shenlong-tuifa" )
                return notify_fail("�������޷�ʹ�á�׷����������й�����\n");  

         if((int)me->query_skill("shenlong-tuifa", 1) < 100 )
                 return notify_fail("��������ȷ�������죬����ʹ�á�׷���������\n");

		 if((int)me->query_skill("leg", 1) < 100 )
                 return notify_fail("��Ļ����ȷ�������죬����ʹ�á�׷���������\n");

         if((int)me->query_skill("dulong-dafa", 1) < 100 )
                 return notify_fail("��Ķ����󷨲�����񣬲���ʹ�á�׷���������\n");

         if((int)me->query("max_neili") < 1000)
                 return notify_fail("���������̫��������ʹ�á�׷���������\n");
		  if((int)me->query("max_neili") < 500)
                 return notify_fail("�㵱ǰ����̫��������ʹ�á�׷���������\n");


         if((int)me->query("jingli") < 500)
                 return notify_fail("�����ھ���̫��������ʹ�á�׷���������\n");

         if( me->query_temp("weapon")) 
                 return notify_fail("�����ű����޷�ʹ�á�׷���������\n");

        if (me->query_skill_mapped("parry") != "shenlong-tuifa")
                return notify_fail("��û�м��������ȷ�Ϊ�мܣ�\n");

		if( me->query_skill_prepared("leg") != "shenlong-tuifa")
				return notify_fail("��û�м����ȷ�Ϊ��ǰ�书��ʽ��\n");

         if(me->query_skill_mapped("force") != "dulong-dafa")
                 return notify_fail("��������ʹ�õ��ڹ�ͬ��������ִ�������ʹ�á�׷���������\n");
	//perform ����

	//��ʽ����
	message_vision(HIY"$N˫�������߳����ھ���Ȼ������ʹ����������ѧ��"HIB"׷�����"HIY"����˲����$n�͹����С�\n\n"NOR,me,target);
	// ��1hit
	
	message_vision(HIG"$N��ճ�$n���ؿڷ��߶���������������������"HIY"ǧ��׷��"HIG"�������͵��ھ���$n�о�����������޿ɱܡ�\n"NOR,me,target);
				i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("leg",1),me,target);
                if (i>2000) i=2000+random(1000);
              
				target->receive_damage("qi", i, me );
                //target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                msg = result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 
      if(userp(me) && me->query("env/damage"))             tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ i+ WHT"�㹥���˺���\n"NOR);    
      if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ i+ WHT"���˺���\n"NOR); 
	//��2hit
	  if (me->query_skill("shenlong-tuifa",1)>160&&me->is_fighting())
	  {
	
			message_vision(HIB"$N��Ȼ�߸�Ծ����������������ɨ����������׷�������С�"HIR"���ζ���"HIB"��,���ٵ���ת�����������˷�â�ľ޴����ţ�\n"NOR,me,target);
					i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("leg",1),me,target);
					if (i>2500) i=2500+random(1000);

					target->receive_damage("qi", i, me );
					target->receive_wound("qi", i/5 , me);
					result = COMBAT_D->damage_msg(i,"����");
					msg = result;
					message_vision(msg,me,target);
					COMBAT_D->report_status(target, 0); 
		  if(userp(me) && me->query("env/damage"))             tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ i+ WHT"�㹥���˺���\n"NOR);    
		  if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ i+ WHT"���˺���\n"NOR); 
		 
      } 
	  //����������
	  if (me->query_skill("shenlong-tuifa",1) >200 && me->is_fighting(target))
      {
		  message_vision(RED"$N�ڿ�����˲��һת�����α�������ޱȣ�����һ������,˫�������߳���ʹ����"HIC"������"RED"��,���������߳���\n"NOR,me,target);
		 		i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("leg",1),me,target);
                if (i>3000) i=3000+random(1000);

				target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/4 , me);
                result = COMBAT_D->damage_msg(i,"����");
                msg = result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 
      }
	  
	  //��������
	  
	  message_vision(HIY"$N��"HIB"׷�����"HIY"��ʩչ��ϣ����ȵ������ڵ��ϡ�\n"NOR,me,target);
	  me->add("neili",-random(200));
	  me->add("jingli",-random(100));
	  me->start_perform(3, "��׷�������");
	  me->add_busy(3);
	return 1;
	
 }

//�˺����㺯��
int calc_damage(int skill,int skill2,object me,object target)
{
        int i;

            i = ( (skill+skill2)*2 - (int)target->query_skill("parry",1) )*10;
            if (i<0) i = -i;
            i += random(i*2/5);
         if( i < (skill2*5)) i = (int)target->query("qi",1)/3;   

            if(userp(target)) i = i* 1 / 5;


      // return i*2 /5; 
		if (me->query("gender")=="����") return i*2 /6; 
		else if (me->query("gender")=="Ů��") return i*1 /6; 
	    else return i*1 /10; 
}

//����
int help(object me)
{
   write(WHT"\n�����ȷ�֮��"HIC"׷�����"WHT"����"NOR"\n");
   write(@HELP
	�����ȷ�Ϊ�������������ż��ܣ�ģ������
	̬֮����ն��������ų����ţ�����ַ�
	��ʤ��������������Ů�Խ���������֮��
	���������㣬����������
	
	ָ�perform leg.zhuiming
	
Ҫ��
	�������Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 500 ����
	��ǰ����Ҫ�� 500 ���ϣ�
	�����ȷ��ȼ� 100 ���ϣ�
	�����ȷ��ȼ� 100 ���ϣ�
	�����󷨵ȼ� 100 ���ϣ�
	�輤���ȷ������ȷ���
	�豸�ȷ�Ϊ�����ȷ�
	�輤���ڹ�Ϊ�����󷨣�
HELP
      );
   return 1;
   }
