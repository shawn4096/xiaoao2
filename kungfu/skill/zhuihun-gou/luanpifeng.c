// luanpifeng.c ������ 
// by snowman@SJ 30/09/1999
// by sohu@xojh 2013

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
           return notify_fail("�������硹ֻ����ս���жԶ���ʹ�á�\n");
       if(me->query("xx/zhg/pass"))
           return notify_fail("����Ȼ��˵����׷�깳���������Ӳ�û��ѧ�ᡣ\n");
       if ( (int)me->query_skill("huagong-dafa", 1) < 350 )
           return notify_fail("����ڹ��ȼ�����������ʹ�á������硹��\n");
    
       if ( (int)me->query_skill("zhuihun-gou", 1) < 350 )
           return notify_fail("�����ɽ׷�깳������죬�����������ӡ������硹��\n");
    
       if (!weapon 
        || weapon->query("skill_type") != "hook"
        || me->query_skill_mapped("hook") != "zhuihun-gou")
           return notify_fail("�������޷�ʹ�á������硹����߹�������\n");
    
       if ( (int)me->query("max_neili") < 2500 )
           return notify_fail("���������Ϊ����������ʹ�á������硹��\n");

       if ( (int)me->query("max_jingli") < 1000 )
           return notify_fail("��ľ�����Ϊ����������ʹ�á������硹��\n");

       if ( (int)me->query("neili") < 700 )
           return notify_fail("����������̫��������ʹ�á������硹��\n");
    
       if ( (int)me->query_temp("zhuihun/lpf") ) 
           return notify_fail("������ʹ����ɽ׷�깳֮�������硹��\n");
    
       if (me->query_skill_mapped("force") != "huagong-dafa")
           return notify_fail("����ڹ������޷�ʹ�á������硹��\n");

       message_vision(HBBLU "\n$N������⿪����ͷɢ������ɫ�Ұף�ͻȻ��һ�������е�"+weapon->name()+HBBLU"���һ����ţ�ȫȻ�����·��������ų����ƿ���ʹ����\n"NOR, me);                 
  
       me->set_temp("zhuihun/lpf",1);
         
       skill = me->query_skill("zhuihun-gou", 1);
    
       me->add_temp("apply/parry",  -skill/5);
       me->add_temp("apply/dodge",  -skill/5);
       me->add_temp("apply/attack",  skill/2);

       me->add_temp("apply/damage",  skill/2);
       
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       
       me->add("neili", -(me->query_skill("force")));
       me->add("jingli", - 100);
       me->start_perform(4, "������");
       call_out("remove_effect", 1, me, target, weapon,5);
       return 1;
}

int remove_effect(object me,object target,object weapon,int count)
{
        if(!me) return 0;
        if(!me->query_temp("zhuihun/lpf")) return 0;
        if( !target 
         || !me->is_fighting(target)
         || weapon != me->query_temp("weapon")
         || me->query_skill_mapped("hook") != "zhuihun-gou"
         || count < 0){
           me->add_temp("apply/attack", -me->query_skill("zhuihun-gou", 1)/2);
		   me->add_temp("apply/damage", -me->query_skill("zhuihun-gou", 1)/2);
 
		   me->add_temp("apply/parry", me->query_skill("zhuihun-gou", 1)/5); 
		   
me->add_temp("apply/dodge", me->query_skill("zhuihun-gou", 1)/5);
           me->delete_temp("zhuihun/lpf");
           if(living(me))
             message_vision(HIG "\n$N��ڴ�ڵش���������Ҳ�����ָ������������������˲��ٵ�������\n\n" NOR, me);
           return 0;
         }
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3); 
         call_out("remove_effect", 1 ,me ,target, weapon, count -1);
}
string perform_name(){ return HIW"������"NOR; }

int help(object me)
{
        write(HIM"\n׷�깳��֮�������硹��"NOR"\n");
        write(@HELP
	׷�깳���������ɵĲ���֮�أ���׷�����֮��
	����������ɶ����书�����󷨣�����书����
	�ա������ص�ͷ������뾡�¡�
	������Ҳ�ǲ�Ҫ���Ĵ򷨣����˵����˼�������
	���Լ�������ǰ�������»�ȡ���к��˺���˲��
	���У����кݶ�������
		
	ָ�perform hook.luanpifeng
		
Ҫ��
	�������Ҫ�� 2500 ���ϣ�      
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 700 ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	׷�깳���ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	�����������м�Ϊ׷�깳����
	�����ڹ�Ϊ�����󷨣�
	�ֳֹ��������
	            
                
HELP
        );
        return 1;
}
