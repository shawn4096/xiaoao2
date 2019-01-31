// zhuihun.c ׷�� 
//
// by sohu@xojh 2015

#include <ansi.h>

inherit F_SSERVER;
//int remove_effect(object me,object target,object weapon,int conut);

int perform(object me, object target)
{
       object wep2;
       int skill,i,count;
       object *inv;
	   object weapon = me->query_temp("weapon");  

       if( !target ) target = offensive_target(me);
       
       if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
           return notify_fail("��׷�������ֻ����ս���жԶ���ʹ�á�\n");
       if(!me->query("quest/xx/tsz/zhuihun/pass"))
           return notify_fail("����Ȼ��˵����׷������������Ӳ�û��ѧ�ᡣ\n");
       if ( (int)me->query_skill("force", 1) < 500 )
           return notify_fail("����ڹ��ȼ�����������ʹ�á�׷���������\n");
    
       if ( (int)me->query_skill("tianshan-zhang", 1) < 500 )
           return notify_fail("�����ɽ׷�깳������죬�����������ӡ�׷���������\n");
    
       if (!weapon 
        || weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "tianshan-zhang")
           return notify_fail("�������޷�ʹ�á�׷��������������Է���\n");
    
       if ( (int)me->query("max_neili") < 15000 )
           return notify_fail("���������Ϊ����������ʹ�á�׷���������\n");

       if ( (int)me->query("max_jingli") < 1000 )
           return notify_fail("��ľ�����Ϊ����������ʹ�á�׷���������\n");

       if ( (int)me->query("neili") < 700 )
           return notify_fail("����������̫��������ʹ�á�׷���������\n");
    
       if ( (int)me->query_temp("tsz/zhuihun") ) 
           return notify_fail("������ʹ����ɽ׷�깳֮��׷���������\n");
    
     //  if (me->query_skill_mapped("force") != "huagong-dafa")
       //    return notify_fail("����ڹ������޷�ʹ�á�׷���������\n");

       message_vision(HBBLU+HIW "\n$N��Ȼ�����Ŀ���������һ����׷�����������"+weapon->name()+HIW"ת�����糵�֣�����ƬƬ��â��\n"NOR, me,target);  
	   message_vision(HBBLU+HIW "\nȫȻ���˸��˰�Σ������ֻ��$n��Ҫ�������к�������׷�����������\n"NOR, me,target);  
       
	   skill = me->query_skill("tianshan-zhang", 1);

	   if (me->query_skill_mapped("force")=="huagong-dafa")
	   {
		   message_vision(HIW "\n$N������Ļ����󷨾����ĵ�����������һ��"HIB"����"HIW"��$n���ֹ�ȥ��\n"NOR, me,target);
		   skill=skill+me->query_skill("huagong-dafa",1)/5;
	   }	                

  
       me->set_temp("tsz/zhuihun",skill);
         
    
      
       me->add_temp("apply/staff",   skill/5);
       me->add_temp("apply/attack",  skill/3);

       me->add_temp("apply/damage",  skill/5);
       
       
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		
		inv = all_inventory(me);
		for(count=0, i=0; i<sizeof(inv); i++) 
		{
         //  if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
           if( inv[i]->query("skill_type") == "hook" ) 
		   {
			   wep2 = inv[i];
			   break;
		   }
		}
	   if (objectp(wep2) && me->query_temp("tsz/lpf"))
       {
		   message_vision(HBWHT+HIB"$N��ʱʩչ����������������Ѿ������뻯��˳�ֳ������������"+wep2->query("name")+HBWHT+HIB"���ȷ���ʽ����$n��\n"NOR,me,target);
		   me->add_temp("apply/attack",skill/4);
		   me->add_temp("apply/damage",skill/4);
		   me->add_temp("apply/staff",skill/4);

		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		   me->add_temp("apply/attack",-skill/4);
		   me->add_temp("apply/damage",-skill/4);
		   me->add_temp("apply/staff",-skill/4);

       }

	   me->add_temp("apply/staff",   -skill/5);
       me->add_temp("apply/attack",  -skill/3);

       me->add_temp("apply/damage",  -skill/5);
       me->delete_temp("tsz/zhuihun");
	   me->add("neili", -(me->query_skill("force",1)));
       me->add("jingli", - 100);
	   me->add_busy(2+random(1));
       me->start_perform(5, "׷�����");
       return 1;
}

string perform_name(){ return HBBLU+HIW"׷�����"NOR; }

int help(object me)
{
        write(HIB"\n��ɽ�ȷ�֮��׷���������"NOR"\n");
        write(@HELP
	��ɽ�ȷ��������ɵĲ���֮�أ���׷�����֮��
	����������ɶ����书�����󷨣�����书����
	�ա������ص�ͷ������뾡�¡�
	׷������������������������ۼ���Ȼ��˲��
	���У����кݶ�������ע�⣬��ʩչ���������
	���������������������������״̬�»����ʩ
	չһ�н�ΪϬ������ʽ��
		
	ָ�perform staff.zhuihun
		
Ҫ��
	�������Ҫ�� 15000 ���ϣ�      
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 700 ���ϣ�
	�����󷨵ȼ� 500 ���ϣ�
	��ɽ�ȷ��ȼ� 500 ���ϣ�
	�����ȷ��ȼ� 500 ���ϣ�
	�����ȷ����м�Ϊ��ɽ�ȷ���
	�������ڹ���
	�ֳ����������
	            
                
HELP
        );
        return 1;
}
