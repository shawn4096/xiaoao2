// zhuihun.c ׷�� 
//
// by sohu@xojh 2015

#include <ansi.h>

inherit F_SSERVER;
int remove_effect(object me,object target,object weapon,int conut);

int perform(object me, object target)
{
       object weapon = me->query_temp("weapon");  
       int skill;
    
       if( !target ) target = offensive_target(me);
       
       if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
           return notify_fail("��׷�������ֻ����ս���жԶ���ʹ�á�\n");
       if(!me->query("quest/xx/zhg/pass"))
           return notify_fail("����Ȼ��˵����׷�깳���������Ӳ�û��ѧ�ᡣ\n");
       if ( (int)me->query_skill("huagong-dafa", 1) < 500 )
           return notify_fail("����ڹ��ȼ�����������ʹ�á�׷���������\n");
    
       if ( (int)me->query_skill("zhuihun-gou", 1) < 500 )
           return notify_fail("�����ɽ׷�깳������죬�����������ӡ�׷���������\n");
    
       if (!weapon 
        || weapon->query("skill_type") != "hook"
        || me->query_skill_mapped("hook") != "zhuihun-gou")
           return notify_fail("�������޷�ʹ�á�׷�����������߹�������\n");
    
       if ( (int)me->query("max_neili") < 15000 )
           return notify_fail("���������Ϊ����������ʹ�á�׷���������\n");

       if ( (int)me->query("max_jingli") < 1000 )
           return notify_fail("��ľ�����Ϊ����������ʹ�á�׷���������\n");

       if ( (int)me->query("neili") < 700 )
           return notify_fail("����������̫��������ʹ�á�׷���������\n");
    
       if ( (int)me->query_temp("zhuihun/lpf") ) 
           return notify_fail("������ʹ����ɽ׷�깳֮��׷���������\n");
    
       if (me->query_skill_mapped("force") != "huagong-dafa")
           return notify_fail("����ڹ������޷�ʹ�á�׷���������\n");

       message_vision(HBBLU+HIW "\n$N��Ȼ�����Ŀ���������һ����׷�꣡����"+weapon->name()+HBBLU+HIW"��Ȼ��һ���趯������ƬƬ��â��\n"NOR, me,target);  
	   if (me->query_skill_mapped("force")=="huagong-dafa")
	   {
		   message_vision(HBBLU+HIW "\n$N������Ļ����󷨹ĵ�����������һ�������$n���ֹ�ȥ��\n"NOR, me,target);    
	   }	                

  
       me->set_temp("zhg/zhuihun",1);
         
       skill = me->query_skill("zhuihun-gou", 1);
    
      
       me->add_temp("apply/hook",   skill/5);
       me->add_temp("apply/attack",  skill/3);

       me->add_temp("apply/damage",  skill/5);
       
       
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       
	   me->add_temp("apply/hook",   -skill/5);
       me->add_temp("apply/attack",  -skill/3);

       me->add_temp("apply/damage",  -skill/5);
       me->delete_temp("zhg/zhuihun");
	   me->add("neili", -(me->query_skill("force",1)));
       me->add("jingli", - 100);
	   me->add_busy(2+random(1));
       me->start_perform(5, "׷�����");
       return 1;
}

string perform_name(){ return HBBLU+HIW"׷�����"NOR; }

int help(object me)
{
        write(HIB"\n׷�깳��֮��׷���������"NOR"\n");
        write(@HELP
	׷�깳���������ɵĲ���֮�أ���׷�����֮��
	����������ɶ����书�����󷨣�����书����
	�ա������ص�ͷ������뾡�¡�
	׷������������������������ۼ���Ȼ��˲��
	���У����кݶ�������
		
	ָ�perform hook.zhuihun
		
Ҫ��
	�������Ҫ�� 15000 ���ϣ�      
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 700 ���ϣ�
	�����󷨵ȼ� 500 ���ϣ�
	׷�깳���ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	�����������м�Ϊ׷�깳����
	�����ڹ�Ϊ�����󷨣�
	�ֳֹ��������
	            
                
HELP
        );
        return 1;
}
