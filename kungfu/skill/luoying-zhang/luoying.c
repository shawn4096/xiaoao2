// luoying.c ��Ӣ��

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      int lvl;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl =  (int)me->query_skill("luoying-zhang", 1);
      if( !target ) target = offensive_target(me);
    
      if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("��Ӣ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

      if (!weapon || weapon->query("skill_type") != "sword")
          return notify_fail("������û�н����޷�ʹ����Ӣ����\n");             

      if (me->query_skill_mapped("sword") != "luoying-zhang"
       || me->query_skill_mapped("parry") != "luoying-zhang")
          return notify_fail("����Ҫ��������Ϊ��Ӣ�����޷�ʹ����Ӣ����\n");             
      if( (int)me->query_skill("sword",1) < 160 )
          return notify_fail("��Ļ��������ȼ�����������ʹ����Ӣ����\n");  
      if( (int)me->query_skill("strike",1) < 160 )
          return notify_fail("��Ļ����Ʒ��ȼ�����������ʹ����Ӣ����\n");  

      if( (int)me->query_skill("luoying-zhang", 1) < 160 )
           return notify_fail("�����Ӣ�Ʒ��ȼ�����������ʹ����Ӣ����\n");
      
      if( (int)me->query_skill("bihai-chaosheng", 1) < 160 )
      
		  return notify_fail("����ڹ��ȼ�����������ʹ����Ӣ����\n");
      if( (int)me->query("max_neili") < 1500 )
          return notify_fail("�������̫��������ʹ����Ӣ����\n");
      
      if( (int)me->query("neili") < 500 )
          return notify_fail("�������̫���ˣ��޷�ʹ�ó���Ӣ����\n");   
      
	  if (me->query_skill_prepared("strike") != "luoying-zhang"
          || me->query_skill_mapped("strike") != "luoying-zhang")
		  return notify_fail("�������޷�ʹ����Ӣ�����й�����\n");             

      message_vision(YEL"\n$N���н���Ȼ������Ӣ���ף����м��ƣ����вؽ�����$n������������һ�ơ�"HIG"��Ӣ��"YEL"����\n"NOR, me,target);
      me->add("neili", -100-random(100)); 
      me->add("jingli", -100);      
      me->add_temp("apply/strength", lvl /20 );
      me->add_temp("apply/sword", lvl/5);
      me->add_temp("apply/damage", lvl /5 );
      me->add_temp("apply/attack", lvl /5);
    
	  me->set_temp("lyz/luoying",lvl);

	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(1)?3:1);
     
	 if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
        
		weapon->unequip(); 
        me->add_temp("apply/strike", lvl/4);
     if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);          
		 me->add_temp("apply/strike", -lvl/4);
         weapon->wield();
     
	 if (lvl>300 && objectp(target) && me->is_fighting(target))
	{
         message_vision(HIC"\n$N�����н�˳�ƻ��裬ʩչ����Ӣ�񽣵ľ��轣�С�"HIM"�ͷ׷׳�"HIC"��һ�еݳ���Ѥ���ޱȣ�\n"NOR, me,target);

		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);          
	}
		 me->add_temp("apply/strength", -lvl /20 );
		 me->add_temp("apply/damage", -lvl /5);        
         me->add_temp("apply/sword", -lvl/5 );
		 me->add_temp("apply/attack", -lvl /5);
    
	me->delete_temp("lyz/luoying");
	
	me->start_busy(1+random(2));

    me->start_perform(4, "����Ӣ����");
	
return 1;
}

string perform_name() {return HIM"��"HIC"Ӣ��"NOR;}

int help(object me)
{
    write(WHT"\n��Ӣ��֮��"HIC"��Ӣ��"WHT"����"NOR"\n");
    write(@HELP
	��Ӣ�Ʊ���Դ���һ�������Ӣ���ƾ��������Ƕ�а
	��ҩʦ�����һ���Ӣ���׶��ã�ֻ����������ϰ����
	���Խ����ƶ�����Ӣ�ƣ���Ӣ���������һ���Ӣ��
	��֮�⣬��ݹ����Է�����һ�ơ�300������Ӣ��С��

	ָ� perform sword.luoying

Ҫ�󣺡�
	�̺�����Ҫ�� 160 ������ 
	��������Ҫ�� 160 ������
	�����Ʒ�Ҫ�� 160 ������
	��Ӣ�Ʒ�Ҫ�� 160 ������
	�������Ҫ�� 1500 ����
	��ǰ����Ҫ�� 500  ����
	��������Ϊ��Ӣ���ƣ�
	�����Ʒ�Ϊ��Ӣ����
	�����м�Ϊ��Ӣ���ƻ�ָ��ͨ��
	���Ʒ�Ϊ��Ӣ����
	�ֳֽ�������
HELP
        );
	return 1;
}


