//  jingtian.c ������Ƹ� 
//  by Leontt 2000.6.11

#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
      int lvl,lvl1;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl = (int)me->query_skill("pangen-fu", 1);
      if( !target ) target = offensive_target(me);
     
     if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("�̸���ڸ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
    
      if (!weapon || weapon->query("skill_type") != "axe"
       || me->query_skill_mapped("axe") != "pangen-fu")
            return notify_fail("��ʹ�õı��в��ԣ��޷�ʹ�á�������Ƹ�����\n");             

      if( (int)me->query_skill("pangen-fu",1) < 220 )
            return notify_fail("����̸�����������죬����ʹ�á�������Ƹ�����\n"); 
      if ( me->query_skill_mapped("axe") != "pangen-fu"
            || me->query_skill_mapped("parry") != "pangen-fu")
            return notify_fail("�������޷�ʹ�á��̸���ڡ�������\n");
     
      if( (int)me->query_skill("axe",1) < 220 )
        return notify_fail("��Ļ��������ȼ�����������ʹ�á�������Ƹ�����\n");  
     
      if( (int)me->query_skill("qiantian-yiyang", 1) < 220 )
        return notify_fail("���Ǭ��һ�����ȼ�����������ʹ�á�������Ƹ�����\n");
      if( me->query_str() < 40 )
            return notify_fail("��������������޷�ʹ�á��̸���ڡ�������\n");

      if( (int)me->query("max_neili") < 2000 )
        return notify_fail("����������̫��������ʹ�á�������Ƹ�����\n");
      if( (int)me->query("neili") <500 )
        return notify_fail("��ĵ�ǰ����̫��������ʹ�á�������Ƹ�����\n");     
      
      message_vision(HIY"\n$NͻȻ���һ��,��������������"+weapon->query("name") +HIY"��Բ�������������޸�������Ϊ\n"+
                          "���أ�����$Nȫ��ʩչ��������ֹǧ�ֱ�о������֮����\n"NOR, me,target);
      me->add("neili", - (200+random(200)));
      me->add("jingli", -80);      
      lvl1= lvl + me->query_dex() + me->query_str();
      me->add_temp("apply/axe", lvl/6);
      me->add_temp("apply/strength", lvl1 /20 );
      me->add_temp("apply/attack", lvl/4);
      me->add_temp("apply/damage", lvl/8);
      me->set_temp("pgf/jingtian", 1);
	  
	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
      if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);  
	  if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
      if (present(target,environment(me))
       && me->is_fighting(target)
       && me->query_skill("pangen-fu", 1) > 250){
       if(random(me->query("combat_exp")) > target->query("combat_exp")/3)     
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       else 
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
      }
      me->add_temp("apply/axe",- lvl/6);
      me->add_temp("apply/strength", -lvl1 /20 );
      me->add_temp("apply/attack",- lvl/4);
      me->add_temp("apply/damage",- lvl/8);
      me->delete_temp("pgf/jingtian");
      me->start_busy(random(2));
      me->start_perform(5,"��������Ƹ���");
      return 1;
}
string perform_name() {return HIR"�������"NOR;}

int help(object me)
{
   write(WHT"\n�̸���ڸ���֮��"HIR"�������"WHT"����"NOR"\n\n");
   write(@HELP
	�̸���ڸ����Ǵ������Ը����Ĵ�����ɽ���ӹ��óϵĶ����似��
	�丫����Ȼ��ʽƽ������ȴ��ƽ������ʽ���̲�ɱ�����������ͣ���
	��������ɱ�л��ǵ��µ���������������͡��������ʽ���ǽ���ͷ
	�趯�������������У������˷��ڵأ��˵��������ޱȡ�����������
	��ʽ�����������й�ϵ��

	perform axe.jingtian

Ҫ��: 
	������� 4000 �㣻
	��ǰ���� 1000 �㣻
	�̸����� 220  ���ϣ�
	�������� 220 ���ϣ�
	Ǭ��һ�� 220 ���ϣ�
	������� 40  ����
	��������Ϊ�̸�������
	�����м�Ϊ�̸�������
	װ����ͷ��

          
HELP
   );
   return 1;
}
