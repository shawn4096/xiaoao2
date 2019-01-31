// zuijiu.c ��� by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{                                  
      int i, lvl, addlvl,dk;
      object weapon;
      dk=me->query_conditions("drunk");
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target))
                return notify_fail("���������ֻ����ս���жԶ���ʹ�á�\n");

      if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "club"
        || me->query_skill_mapped("club") != "zui-gun")
                return notify_fail("�������޷�ʹ�á�������򡹡�\n");
  
      if( (int)me->query_skill("zui-gun",1) < 150 )
                return notify_fail("������������죬����ʹ�á�������򡹣�\n");
      
      if( me->query_skill_mapped("force") != "yijin-jing" )
                return notify_fail("��������ʹ���ڹ��޷�ʹ����������򡹡�\n");

      if( (int)me->query_skill("yijin-jing",1) < 150 )
                return notify_fail("����׽�ȼ�����������ʹ�á�������򡹣�\n");  
       
      if( (int)me->query_str() < 25 )
                return notify_fail("��ı�������ǿ������ʹ�á�������򡹣�\n");
      
      if( (int)me->query("max_neili") < 2500 )
                return notify_fail("�������̫��������ʹ�á�������򡹣�\n");
            
        lvl = (int)me->query_skill("zui-gun", 1);
        addlvl = (int)me->query_skill("zui-gun", 1)+(int)me->query_skill("yijin-jing", 1)/2;
        addlvl=addlvl/2;
        if(lvl < 120) return notify_fail("��ĵȼ�̫�ͣ��޷�ʹ�ó���������򡹣�\n");

      	if( (int)me->query("neili") < 1500 )
                return notify_fail("�������̫���ˣ��޷�ʹ�ó���������򡹣�\n");
      	lvl /= 20;
      	lvl--;
      	if(lvl > 8) lvl = 8; 
      	if(lvl < 1) return notify_fail("��ĵȼ�̫�ͣ��޷�ʹ�ó���������򡹣�\n");
        message_vision(GRN "ֻ��$N���һ�ھ�����һʽ��������ơ���Χ��$nһҡһ�ڵ��߶��š�\n" NOR, me, target);
		message_vision(HIY"\n$N���Լ�������ġ������ⲻ�������Ĳ�����������У��������ģ��������ʹ����������򡹣��������������\n"NOR,me);
        
		me->add_temp("apply/attack", addlvl);
		me->add_temp("apply/club", addlvl/2);
        me->add_temp("apply/parry", addlvl/2);
        me->add_temp("apply/dodge", addlvl/2);
       
		if (dk>0)
		{
		       me->add_temp("apply/damage", dk*addlvl/2);
			   me->set_temp("slzg/zuijiu1",1);
		}
		else  
		{
			me->add_temp("apply/damage", addlvl/2);
			me->set_temp("slzg/zuijiu2",1);
		}
      	me->set_temp("zuijiu", 1);
      	for(i=0; i < lvl; i++){
      	   	if(!me->is_killing(target->query("id")) 
      	   	&& !target->is_killing(me->query("id"))
      	   	&& !target->is_fighting(me))
      	   	break;
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
           	me->add_temp("zuijiu", 1);
                me->receive_damage("neili", 50);
                me->receive_damage("jingli", 10);
      	}
      	me->delete_temp("zuijiu");
        me->add_temp("apply/attack", -addlvl);
		me->add_temp("apply/club", -addlvl/2);
        me->add_temp("apply/parry", -addlvl/2);
        me->add_temp("apply/dodge", -addlvl/2);
        if (me->query_temp("slzg/zuijiu1"))
		{
		    me->add_temp("apply/damage", -dk*addlvl/2);
			me->delete_temp("slzg/zuijiu1");
		}
		if (me->query_temp("slzg/zuijiu2"))
		{
		    me->add_temp("apply/damage", -addlvl/2);
			me->delete_temp("slzg/zuijiu2");
		}	
        
		me->start_perform(5, "���������");
		me->delete_temp("slzg/zuijiu");

        tell_object(me, HIG"\n������һ�ң���Ҳ�޷�ά�����������⾳�ˡ�\n"NOR); 
        return 1;
}

int help(object me)
{
	write(HIC"\n���֮����ơ���"NOR"\n");
	write(@HELP
	������������ֹ��������ڹ����似�������书��
	Ѱ�������似������ͬ����Ҫ�����������״̬��
	���ɷ������������ע�⣬�����������״̬�й�
	
	perform club.zuijiu

Ҫ��
	������� 2500 ���ϣ�
	��ǰ���� 1500 ���ϣ�
	����ȼ� 150 ���ϣ�
	�׽�ȼ� 150 ���ϣ�
	�����м�Ϊ�����
	��������Ϊ�������
	����������25��
	ע�⣺�˺�����Ƴ̶��йأ�
HELP
	);
	return 1;
}
