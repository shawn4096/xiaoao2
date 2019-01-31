// qingliang.c
// by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{                                  
      int i, lvl, addlvl,dk;
      object weapon;
      
	  if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target))
                return notify_fail("���������ֻ����ս���жԶ���ʹ�á�\n");
//�ʷ��򵶷�
      if (!objectp(weapon = me->query_temp("weapon")) 
        || (weapon->query("skill_type") != "brush"&&weapon->query("skill_type") != "blade"))
                return notify_fail("����������ԣ������޷�ʹ�á�������򡹡�\n");
      
	  if (me->query_skill_mapped("blade") != "qingliang-shan"
			||me->query_skill_mapped("parry") != "qingliang-shan"
			|| me->query_skill_mapped("brush") != "qingliang-shan")
                return notify_fail("�㼤�����ԣ������޷�ʹ�á����־�����\n");

      if( (int)me->query_skill("qingliang-shan",1) < 450 )
                return notify_fail("��������Ȳ�����죬����ʹ�á�������򡹣�\n");      

      if( (int)me->query_skill("force",1) < 450 )
                return notify_fail("��Ļ����ڹ��ȼ�����������ʹ�á�������򡹣�\n");  
      if( (int)me->query_skill("blade",1) < 450 )
                return notify_fail("��Ļ��������ȼ�����������ʹ�á�������򡹣�\n");  
      if( (int)me->query_skill("brush",1) < 450 )
                return notify_fail("��Ļ����ʷ��ȼ�����������ʹ�á�������򡹣�\n");  
      
      
      if( (int)me->query_dex() < 70 )
                return notify_fail("���������ǿ������ʹ�á�������򡹣�\n");
      
      if( (int)me->query("max_neili") < 12500 )
                return notify_fail("�������̫��������ʹ�á�������򡹣�\n");
            
      lvl = (int)me->query_skill("qingliang-shan", 1);
      addlvl = (int)me->query_skill("qingliang-shan", 1)+(int)me->query_skill("blade", 1)/2+(int)me->query_skill("brush", 1)/2+(int)me->query_skill("force", 1)/2;
         
	  addlvl=addlvl/2;
        
      	
	  if( (int)me->query("neili") < 1500 )
		      return notify_fail("�������̫���ˣ��޷�ʹ�ó���������򡹣�\n");
      	
	  dk=lvl / 80;
      	
	  if(dk > 8) dk = 8; 
      	
      message_vision(HBGRN+HIW "$N��Цһ��������һ�������������Χ��$n���ٵ�����շת��һʽ"NOR+HIM"���������"+HBGRN+HIW"����������������������ꡣ\n" NOR, me, target);

		me->add_temp("apply/attack", addlvl/3);
		me->add_temp("apply/brush", addlvl/4);
        me->add_temp("apply/blade", addlvl/5);
        me->add_temp("apply/damage", addlvl/5);
       

      	me->set_temp("qls/kuaida", 1);
      	
		for(i=0; i < dk; i++)
		{
      	   
			if(!me->is_fighting() 
				&& !target->is_killing(me->query("id"))
				&& !target->is_fighting(me))
      	   	break;
			if (me->query("neili")<50
				||me->query("jingli")<50)
			break;
			
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
           	//me->add_temp("qls/kuaida", 1);
            me->receive_damage("neili", 50);
            me->receive_damage("jingli", 10);
      	}
      	me->delete_temp("qls/kuaida");

		me->add_temp("apply/attack", -addlvl/3);
		me->add_temp("apply/brush", -addlvl/4);
        me->add_temp("apply/blade", -addlvl/5);
        me->add_temp("apply/damage", -addlvl/5);

		me->start_perform(6, "���������");
        tell_object(me, HIW"\n���������ʽѸ���ޱȣ��㽫��������һ�ϻ����չ���\n"NOR); 
        return 1;
}
string perform_name(){ return HIM"�������"NOR; }

int help(object me)
{
	write(HIC"\n������֮��������򡹣�"NOR"\n");
	write(@HELP
	�������������������ʿ���ž���������Ϊ�����ȿ���
	�����̹����ֿ��Ի��������������׻�˵һ��̣�һ��
	�գ���������������ΪϬ�������ڲ���������Ů�����
	��������Ҳ�����ɵ���Ҫ��ҹ���
	ע�⣺
	
	perform brush.kuaida

Ҫ��
	����������� 12500 ���ϣ�
	��ǰ�������� 1500 ���ϣ�
	�����ȵĵȼ� 450 ���ϣ�
	�����ڹ��ȼ� 450 ���ϣ�
	�����ʷ��ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	���������� 70  ���ϣ�
	��������Ϊ������
	�����ʷ�Ϊ������
	�����м�Ϊ�����ȣ���
	�ڹ����ޣ�
	�ֳֵ����������
HELP
	);
	return 1;
}
