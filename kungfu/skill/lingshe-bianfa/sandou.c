 // sandou ����������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int lv;
      object weapon;

      weapon = me->query_temp("weapon");
	  lv = me->query_skill("lingshe-bianfa",1);
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
      return notify_fail("��������������ֻ����ս���жԶ���ʹ�á�\n");

      if (!weapon || weapon->query("skill_type") != "whip"
       || me->query_skill_mapped("whip") != "lingshe-bianfa")
      return notify_fail("������û�бޣ��޷�ʹ�á���������������\n");             

      if( (int)me->query_skill("lingshe-bianfa",1) < 100 )
			return notify_fail("������߱޷�������죬����ʹ�á���������������\n");
      if( (int)me->query_skill("dulong-dafa",1) < 100 )
			return notify_fail("��Ķ����󷨲�����죬����ʹ�á���������������\n");

      if( (int)me->query_skill("whip", 1) < 100 )
			return notify_fail("��Ļ����޷��ȼ�����������ʹ�á���������������\n");
      if( (int)me->query_skill("dodge", 1) < 100 )
			return notify_fail("��Ļ����Ṧ�ȼ�����������ʹ�á���������������\n");

      if( (int)me->query("neili") < 300 )
			return notify_fail("�������̫�٣�����ʹ�á���������������\n");
	  if( (int)me->query("jingli") < 500 )
			return notify_fail("��ľ���̫�٣�����ʹ�á���������������\n");
      if( (int)me->query_skill("qusheshu", 1) < 20 )
			return notify_fail("����������ȼ�����������ʹ�á����߲�����\n");
	  if(me->query_skill_mapped("force") != "dulong-dafa")
       		return notify_fail("������ʹ�õ��ڹ��붾������ִ�������ʹ�á���������������\n");
      if(me->query("gender")!="Ů��")
            return notify_fail("���Ů�ԣ��޷�ʹ�á����߲�����\n");
      message_vision(HIB"\n$N���﷢��˻˻�Ĺֽм���������"+weapon->query("name")+HIB+"�����������£������������б�������\n�γ������������ֵı�Ӱ��ѭ�Ź����;����$nϮȥ��\n"NOR, me,target);
      
	  me->add("neili", -200); 
      me->add("jingli", -50);

      //target->add_busy(1);
	  //me->start_busy(2);
	  if (!userp(target)) 
	  {
		  lv += lv+me->query_dex();
		 // lv=lv+
	  }
	  if (me->query_skill("poison",1)>150)
	  {
		  lv=lv+me->query_skill("poison",1);
	  }
      me->set_temp("lsbf/sandou",1);
      me->add_temp("apply/attack", lv/2);
	  me->add_temp("apply/whip", lv/4);
	  me->add_temp("apply/damage", lv/4);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);  
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);  
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
      
	  if (me->is_fighting(target)
		  &&me->query_skill("lingshe-bianfa",1)>250)
      {
			message_vision(HIG"$N�����е�"+weapon->query("name")+HIG"����ʩչ��������˻������ʽ����ͷ�γ������������Х�У�����$n��\n"NOR,me,target);
			me->add_temp("apply/attack", lv/2);
			me->add_temp("apply/damage", lv/5);
			weapon->unequip();
			//target->add_busy(2);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
			me->add_temp("apply/damage", -lv/5);
			me->add_temp("apply/attack", -lv/2);
			weapon->wield();
      }
	  me->add_temp("apply/attack", -lv/2);
      me->add_temp("apply/whip", -lv/4);
	  me->add_temp("apply/damage", -lv/4);
	  me->delete_temp("lsbf/sandou");	
      me->start_perform(3,"��������������");
      return 1;
}
string perform_name(){ return HIB"����������"NOR; }

int help(object me)
{
        write(HIC"\n���߱޷�"+HIB"��������������"NOR"\n");
        write(@HELP
	���߱޷����������̽����鰲ͨ����������������ϰ������
	һ������Ϊ���������ۣ�����һ����Ҳƾ����ʹ����ǰ�ж�
	����ѧ�����鶯Ϭ�������ն������Ҵ������趯֮�ʣ�����
	�������������߳����������ǳ�����������Ů���ӵ�������
	����
	ע�⣺�˺��붾�ƺ����й���,250�����ٳ�һ������˻��

	ָ�perform whip.sandou

Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	��ǰ����Ҫ�� 300 ���ϣ�
	�����޷�Ҫ�� 100 ���ϣ�
	���߱޷�Ҫ�� 100 ���ϣ�
	������Ҫ�� 100 ���ϣ�
	�����Ṧ�ȼ� 100 ���ϣ�
	�������ĵȼ� 20  ���ϣ�
	�����޷�Ϊ���߱޷���
	�����м�Ϊ���߱޷���
	�ڹ����������󷨣�
	�ֱֳ�������

HELP
        );
        return 1;
}
