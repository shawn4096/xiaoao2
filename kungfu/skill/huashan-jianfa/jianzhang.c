// jianzhang.c ����������

#include <ansi.h>
  string perform_name() {return HIC"����������"NOR;}

inherit F_SSERVER;

int perform(object me, object target)
{
      int lvl;
	  int a;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl = ( (int)me->query_skill("huashan-jianfa", 1) + (int)me->query_skill("hunyuan-zhang", 1) )/2;
      if( !target ) target = offensive_target(me);
     
      if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

     /* if( (string)me->query("gender") != "����" )
      return notify_fail("ֻ���е��Ӳ����ó�������������\n");	*/

      if (!weapon || weapon->query("skill_type") != "sword"
       || me->query_skill_mapped("sword") != "huashan-jianfa"
       || me->query_skill_mapped("parry") != "huashan-jianfa")
          return notify_fail("������û�н����޷�ʹ�ý�����������\n");             
      if( (int)me->query_skill("sword",1) < 200 )
          return notify_fail("��Ļ��������ȼ�����������ʹ�ý�����������\n");  
      if( me->query_temp("hs/jianzhang"))
          return notify_fail("������ʹ�ý�������������������ʹ�ã�\n");  
      if( (int)me->query_skill("hunyuan-zhang", 1) < 200 )
           return notify_fail("��Ļ�Ԫ�Ʒ��ȼ�����������ʹ�ý�����������\n");
      
      if( (int)me->query_skill("zixia-gong", 1) < 200 )
      
		  if( (int)me->query_skill("huashan-qigong", 1) < 200 )
      
		  return notify_fail("����ڹ��ȼ�����������ʹ�ý�����������\n");
      if( (int)me->query("max_neili") < 1500 )
          return notify_fail("�������̫��������ʹ�ý�����������\n");
      
      if( (int)me->query("neili") < 500 )
          return notify_fail("�������̫���ˣ��޷�ʹ�ó�������������\n");   
      if(me->query_temp("hs/jianzhang") )
          return notify_fail("������ʹ�ý�����������\n");                                                                   
      if (me->query_skill_prepared("strike") != "hunyuan-zhang"
          || me->query_skill_mapped("strike") != "hunyuan-zhang")
      return notify_fail("�������޷�ʹ�ý������������й�����\n");             

      message_vision(HIG"\n$NͻȻ��ʽһ�䣬���м��ƣ����вؽ�����$n����������������,���ǻ�ɽ���ھ�ѧ��"HIR"����������"HIG"����\n"NOR, me,target);
      me->add("neili", -300-random(100)); 
      me->add("jingli", -100);      
      me->add_temp("apply/strength", lvl /20 );
      me->add_temp("apply/sword", lvl/6);
      me->add_temp("apply/damage", lvl /6 );
      me->add_temp("apply/attack", lvl /5);
      me->set_temp("hs/jianzhang",1);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(1)?3:1);
	 if (me->query("quest/huashan")=="����")
     {
        message_vision(MAG"\n$N�����ھ����������޵õľ����������ֱ�֮�ϣ������е��������׷��ӳ�����\n"NOR, me,target);
		me->add_temp("apply/strength", lvl /20 );
		me->add_temp("apply/sword", lvl/10);
        me->add_temp("apply/damage", lvl /10 );
        me->add_temp("apply/attack", lvl /6);
		target->start_busy(2+random(2));
      }
     if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(1)?3:1);  
     if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
        weapon->unequip(); 
        me->add_temp("apply/strike", lvl/6);
     if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(1)?3:1); 
     if (me->is_fighting(target)) 
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(1)?3:1);  
         me->add_temp("apply/strike", -lvl/6);
         me->add_temp("apply/strength", -lvl /20 );
		 me->add_temp("apply/damage", -lvl /6);        
         me->add_temp("apply/sword", -lvl/6 );
		 me->add_temp("apply/attack", -lvl /5);
        
         weapon->wield();
      if (me->query("quest/huashan")=="����")
        {
       	me->add_temp("apply/strength", -lvl /20 );
		me->add_temp("apply/sword", -lvl/10);
        me->add_temp("apply/damage", -lvl /10 );
        me->add_temp("apply/attack", -lvl /6);
	    }
	  	 me->delete_temp("hs/jianzhang");
		 me->start_busy(1+random(2));
         me->start_perform(5, "��������������");
		 
return 1;
}


int help(object me)
{
    write(WHT"\n��ɽ������"HIC"����������"WHT"����"NOR"\n");
    write(@HELP
	��ɽ���ھ�ѧ������ɽ�������ۣ��ڶ�ʱ����
	�������������ƣ��������͡��������ϼ����
	��������

	ָ� perform sword.jianzhang

Ҫ�󣺡�
	��ϼ��/��ɽ���� 200 ������ 
	��ɽ����Ҫ�� 200 ������
	��Ԫ�Ʒ�Ҫ�� 200 ������
	�������Ҫ�� 1500 ����
	��ǰ����Ҫ�� 500  ����
	����������ɽ������
	�����мܻ�ɽ������
	�����Ʒ���Ԫ��
	�ֳֽ�������
HELP
);
 return 1;
}


