// zuijiu.c ��� by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{                                  
      int i, lvl, addlvl,dk;
      object weapon;
      dk=me->query_condition("drunk");
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
       
		message_vision(HIY"\n$N���Լ�������ġ������ⲻ�������Ĳ�����������У��������ģ��������ʹ����������򡹡�\n"NOR,me);
            
		//��������벻��Ӧ�о޴�����
		if (dk>0)			
		{
			 message_vision(GRN "ֻ��$N���һ�ھ�����һʽ��������ơ���Χ��$nһҡһ�ڵ��߶��ţ��������������\n" NOR, me, target);
		      me->add_temp("apply/damage", dk*10);
			  me->add_temp("apply/attack", addlvl);
		      me->add_temp("apply/club", addlvl/2);
              me->add_temp("apply/parry", addlvl/2);
              me->add_temp("apply/dodge", addlvl/2);   
		}
		else
		{	
            me->add_temp("apply/attack",addlvl/3);
		    me->add_temp("apply/club", addlvl/3);
            me->add_temp("apply/parry", addlvl/3);
            me->add_temp("apply/dodge", addlvl/3);   	
			me->add_temp("apply/damage", addlvl/3);
		}
      	me->set_temp("zuijiu", 1);
      	for(i=0; i < lvl; i++){
      	   	if(!me->is_killing(target->query("id")) 
      	   	&& !target->is_killing(me->query("id"))
      	   	&& !target->is_fighting(me))
      	   	break;
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
              	me->add_temp("zuijiu", 1);
                me->receive_damage("neili", 100);
                me->receive_damage("jingli", 50);
      	}      	
        
        if (me->query_temp("zuijiu")) {
			me->delete_temp("zuijiu");
			me->add_temp("apply/damage", -dk*10);
			me->add_temp("apply/attack", -addlvl);
		    me->add_temp("apply/club", -addlvl/2);
            me->add_temp("apply/parry", -addlvl/2);
            me->add_temp("apply/dodge", -addlvl/2);
		}
		else 
		{	
           	me->add_temp("apply/damage", -addlvl/3);
			me->add_temp("apply/attack", -addlvl/3);
		    me->add_temp("apply/club", -addlvl/3);
            me->add_temp("apply/parry", -addlvl/3);
            me->add_temp("apply/dodge", -addlvl/3);
		}
		target->set_temp("faint_by",me);//����һ����ǣ�����Ī���������� by renlai
		//target->set_temp("last_damage_from", "��"+me->query("name")+"��ʹ���֮����ơ�������ɱ");
        me->start_perform(4, "����ơ�");		
		//me->clear_conditions_by_type("drunk");
        tell_object(me, HIG"\n������һ�ң���Ҳ�޷�ά�����������⾳�ˡ�\n"NOR); 
        return 1;
}

int help(object me)
{
	write(HIC"\n���֮����ơ���"NOR"\n");
	write(@HELP

	Ҫ��
		������� 2500 ���ϣ�
		��ǰ���� 1500 ���ϣ�
		����ȼ� 150 ���ϣ�
		�׽�ȼ� 150 ���ϣ�
		�����м�Ϊ�������
		����������25��
		ע�⣺��ƺ󽫳����ͷ��������������������Ƴ̶��йأ�
HELP
	);
	return 1;
}
