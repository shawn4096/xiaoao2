//���ν�,��Ϊ������
////2014-08-07
//by sohu
#include <ansi.h>
#include <combat.h>

 inherit F_SSERVER;

 string perform_name() {return HIB"���ν�"NOR;}
int sltf_shexing(object me,int count);


 int perform(object me, object target)
 {
	 //������
        object weapon;
        string msg,result;
        int skill; 
	//ʹ�������ж�
		if( !target ) target = offensive_target(me);

		if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
                 return notify_fail("���ν�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

		if (me->query_skill_prepared("leg") != "shenlong-tuifa"
            || me->query_skill_mapped("leg") != "shenlong-tuifa"
			|| me->query_skill_mapped("parry") != "shenlong-tuifa" )
                return notify_fail("�������޷�ʹ�����νŽ��й�����\n");  

         if((int)me->query_skill("shenlong-tuifa", 1) < 220 )
                 return notify_fail("��������ȷ�������죬����ʹ�����νš�\n");

		 if((int)me->query_skill("leg", 1) < 220 )
                 return notify_fail("��Ļ����ȷ�������죬����ʹ�����νš�\n");

         if((int)me->query_skill("dulong-dafa", 1) < 220 )
                 return notify_fail("��Ķ����󷨲�����񣬲���ʹ�����νš�\n");

         if((int)me->query("max_neili") < 1000)
                 return notify_fail("���������̫��������ʹ�����νš�\n");
		  if((int)me->query("max_neili") < 500)
                 return notify_fail("�㵱ǰ����̫��������ʹ�����νš�\n");


         if((int)me->query("jingli") < 500)
                 return notify_fail("�����ھ���̫��������ʹ�����νš�\n");

         if( me->query_temp("weapon")) 
                 return notify_fail("�����ű����޷�ʹ�����νš�\n");

        if (me->query_skill_mapped("parry") != "shenlong-tuifa")
                return notify_fail("��û�м��������ȷ�Ϊ�мܣ�\n");

		if( me->query_skill_prepared("leg") != "shenlong-tuifa")
				return notify_fail("��û�м����ȷ�Ϊ��ǰ�书��ʽ��\n");

         if(me->query_skill_mapped("force") != "dulong-dafa")
                 return notify_fail("��������ʹ�õ��ڹ�ͬ��������ִ�������ʹ�����νš�\n");
         if(me->query_temp("sltf/shexing"))
                 return notify_fail("����������ʹ�����νž�����\n");

	//��ʽ����
	message_vision(BLU"$N˫��������֮״����������������ǰ�У��������似����ͬ�����ǡ�"HIC"���ν�"BLU"��������\n\n"NOR,me,target);
	// ��1hit
	
	  skill=me->query_skill("shenlong-tuifa",1);
	  if (me->query("gender")=="����")
	  {
		skill+=me->query_skill("xunsheshu",1);
		message_vision(HIG"$N����ѵ�ߵľ����ڻ��ͨ�����һ���䣬���ô˾������ǵ���Ӧ�֣�����������\n\n"NOR,me);

	  }
	  //��������
	 me->add_temp("apply/attack",skill/8);
	 if (me->query("gender")=="����") me->add_temp("apply/damage",skill/8);
	 me->add_temp("apply/leg",skill/6);
	 me->set_temp("sltf/shexing",skill);
	 call_out("sltf_shexing",1,me,skill/40);
	 message_vision(BLU"$Nһ������$n����ǰ����ź�Ȼʩչ����"HIR"���־�"BLU"����ס$n�Ĳ��ӣ��ҽ��漴������ȥ��\n\n"NOR,me,target);

	 if (random(me->query_dex(1))>target->query_dex(1)/2)
	 {
		message_vision(BLU"$n����һ�����У���ʱ��Щͷ�ؽ��ᣬ�������죡\n\n"NOR,me,target);
		target->add_bus(1);
	 }
	  me->add("neili",-100-random(200));
	  me->add("jingli",-100-random(100));
	return 1;
	
 }

//�˺����㺯��
int sltf_shexing(object me,int count)
{
        int skill;
		if (!me) return 1;
		skill=me->query_temp("sltf/shexing");
		if (!me->is_fighting()
			|| me->query_temp("weapon")
			|| me->query_skill_prepared("leg")!="shenlong-tuifa"
			|| me->query_skill_mapped("leg")!="shenlong-tuifa"
			|| count<0)
		{
			 me->add_temp("apply/attack",-skill/8);
			 me->add_temp("apply/leg",-skill/6);
			 if (me->query("gender")=="����") me->add_temp("apply/damage",-skill/8);
			 me->delete_temp("sltf/shexing");
			 message_vision(BLU"$N˫�ű��ԭ��������һ��������\n\n"NOR,me);
			 return 1;
		}
		call_out("sltf_shexing",1,me,count--);

}


//����
int help(object me)
{
   write(WHT"\n�����ȷ�֮��"BLU"���ν�"WHT"����"NOR"\n");
   write(@HELP
	�����ȷ�Ϊ�������������ż��ܣ�ģ������
	̬֮����ն��������ų����ţ�����ַ�
	��ʤ����
	���ν���ģ������֮״��һ�Ź�ס�Է�����
	����һ��������жԷ������������߿���ʹ
	�Է�ֱ�ӵ������ԡ�ʩչ���С�������ȷ�
	���к��ȷ���������������ϰѵ����������
	����Ů���Բ
	
	ָ�perform leg.shexing
	
Ҫ��
	�������Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 500 ����
	��ǰ����Ҫ�� 500 ���ϣ�
	�����ȷ��ȼ� 220 ���ϣ�
	�����ȷ��ȼ� 220 ���ϣ�
	�����󷨵ȼ� 220 ���ϣ�
	�輤���ȷ������ȷ���
	�豸�ȷ�Ϊ�����ȷ�
	�輤���ڹ�Ϊ�����󷨣�
HELP
      );
   return 1;
}
