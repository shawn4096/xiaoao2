 // wudu �嶾��

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	  int lv;
      object weapon;

      weapon = me->query_temp("weapon");
	  lv = me->query_skill("wudu-bian",1);
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
		  return notify_fail("���嶾�ޡ�ֻ����ս���жԶ���ʹ�á�\n");

      if (!weapon || weapon->query("skill_type") != "whip"
       || me->query_skill_mapped("whip") != "wudu-bian")
		  return notify_fail("������û�бޣ��޷�ʹ�á��嶾�ޡ���\n");             

      if( (int)me->query_skill("wudu-bian",1) < 220 )
	      return notify_fail("������߱޷�������죬����ʹ�á��嶾�ޡ���\n");
      if( (int)me->query_skill("poison",1) < 100 )
	      return notify_fail("��Ķ��Ʋ�����죬����ʹ�á��嶾�ޡ���\n");
      if( (int)me->query_skill("whip", 1) < 220 )
		  return notify_fail("��Ļ����޷��ȼ�����������ʹ�á��嶾�ޡ���\n");
      if( (int)me->query_skill("dodge", 1) < 220 )
		  return notify_fail("��Ļ����Ṧ�ȼ�����������ʹ�á��嶾�ޡ���\n");
	  if (me->query("gender")=="����")
	 	  return notify_fail("�嶾����Ҫ���������������Բ���ʹ�á��嶾�ޡ���\n");

      if( (int)me->query("neili") < 300 )
		  return notify_fail("�������̫�٣�����ʹ�á��嶾�ޡ���\n");
	  if( (int)me->query("jingli") < 500 )
		  return notify_fail("��ľ���̫�٣�����ʹ�á��嶾�ޡ���\n");
	  if (me->query_skill_mapped("whip")!="wudu-bian"
		 ||me->query_skill_mapped("parry")!="wudu-bian")
		  return notify_fail("�㼤���ı޷����ԣ�����ʹ�á��嶾�ޡ���\n");
	 
	  message_vision(HIB"\n$N�����е�"+weapon->query("name")+HIB+"�����������£�ÿһ�ж���Ϊ���죬����ѭ�Ź����;����$nϮȥ��\n"NOR, me,target);
	  message_vision(HIB"\n$N������Բ�����嶾�̡��嶾�ޡ�����ʩչ������\n"NOR, me,target);

      me->add("neili", -200); 
      me->add("jingli", -50);

	  if (!userp(target)&&me->query("gender")=="Ů��") 
	  {
		  lv += lv+me->query_dex();
		 // lv=lv+
	  }

	  if (me->query("gender")=="Ů��"&& me->query_skill("poison",1)>100)
	  {
		  lv=lv+me->query_skill("poison",1);
	  }
	  //������������Ů��һ��
	  if (me->query("gender")=="����") 
		  lv=lv/3;

      me->set_temp("wdb/wudu",5);
      me->add_temp("apply/attack", lv/4);
	  me->add_temp("apply/whip", lv/5);
	  me->add_temp("apply/damage", lv/5);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	  //���ַ���ħ��
	  if (me->is_fighting(target)
		  &&me->query_skill_mapped("hand")=="tianmo-shou"
		  &&me->query_skill_prepared("hand")=="tianmo-shou")
      {
			message_vision(HIG"$N�����е�"+weapon->query("name")+HIG"�ջ����䣬˳��һ������ħ�֡����㡢��������Է������Ѩ��\n"NOR,me,target);
			me->add_temp("apply/hand", lv/5);
			me->add_temp("apply/damage", lv/8);
			weapon->unequip();
			target->add_busy(1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
			me->add_temp("apply/damage", -lv/8);
			me->add_temp("apply/hand", -lv/5);
			weapon->wield();
      }
	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);  

      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  

	  me->add_temp("apply/attack", -lv/4);
      me->add_temp("apply/whip", -lv/5);
	  me->add_temp("apply/damage", -lv/5);
	  me->delete_temp("wdb/wudu");	
      me->start_perform(3,"���嶾�ޡ�");
      return 1;
}
string perform_name(){ return HIB"�嶾��"NOR; }

int help(object me)
{
        write(HIC"\n�嶾�޷�"+HIB"���嶾�ޡ�"NOR"\n");
        write(@HELP
	�嶾�޷������嶾�̸��ݽ�������������о���������һ��
	��ѧ�������鶯Ϭ�������ն������Ҵ������趯֮�ʣ�����
	�������������緢�������ǳ����������ħ�֣�������
	�������ʽ��
	ע�⣺�˺��붾�ƺ����й�����Ů��������
	
	ָ�perform whip.wudu

Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	��ǰ����Ҫ�� 300 ���ϣ�
	�����޷�Ҫ�� 220 ���ϣ�
	�嶾�޷�Ҫ�� 220 ���ϣ�
	�������ȼ� 220 ���ϣ�
	��������ȼ� 100 ���ϣ�
	�����޷�Ϊ�嶾�޷���
	�����м�Ϊ�嶾�޷���
	�ֱֳ���������

HELP
        );
        return 1;
}
