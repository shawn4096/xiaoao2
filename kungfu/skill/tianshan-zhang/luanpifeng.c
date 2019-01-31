// luanpifeng.c ������ 
// by snowman@SJ 30/09/1999
// by sohu@xojh 2013
// ��ֲ���ȷ������޹���ȡ��
#include <ansi.h>

inherit F_SSERVER;
int remove_effect(object me,int conut);

int perform(object me, object target)
{
       object weapon;
       int skill;
		weapon = me->query_temp("weapon");  
       if( !target ) target = offensive_target(me);
       
       if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
           return notify_fail("�������硹ֻ����ս���жԶ���ʹ�á�\n");
       if(!me->query("quest/xx/tsz/luanpifeng/pass"))
           return notify_fail("����Ȼ��˵��������������������Ӳ�û��ѧ�ᡣ\n");
       
	   if ( (int)me->query_skill("huagong-dafa", 1) < 350 )
           return notify_fail("����ڹ��ȼ�����������ʹ�á������硹��\n");
    
       if (me->query_skill("tianshan-zhang", 1) < 350 )
           return notify_fail("�����ɽ�ȷ�������죬�����������ӡ������硹��\n");
       if (me->query_skill_mapped("dodge")!="zhaixingshu" )
           return notify_fail("��ļ���������ժ�����������������ӡ������硹��\n");

       if (!weapon 
        || weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "tianshan-zhang"
		|| me->query_skill_mapped("parry") != "tianshan-zhang")
           return notify_fail("��ļ����书���ԣ������޷�ʹ�á������硹����߹�������\n");
    
       if ( (int)me->query("max_neili") < 5000 )
           return notify_fail("���������Ϊ����������ʹ�á������硹��\n");

       if ( (int)me->query("max_jingli") < 1000 )
           return notify_fail("��ľ�����Ϊ����������ʹ�á������硹��\n");

       if ( (int)me->query("neili") < 700 )
           return notify_fail("����������̫��������ʹ�á������硹��\n");
    
       if ( (int)me->query_temp("tsz/lpf") ) 
           return notify_fail("������ʹ����ɽ�ȷ�֮�������硹��\n");
    
       if (me->query_skill_mapped("force") != "huagong-dafa")
           return notify_fail("����ڹ������޷�ʹ�á������硹��\n");

       message_vision(HBBLU "\n$N������⿪����ͷɢ������ɫ�Ұף�ͻȻ��һ�������е�"+weapon->name()+HBBLU"���һ����ţ�ȫȻ�����·���\n"NOR, me);                 
       message_vision(HBGRN+HIW "\n$N��Ȼ�ȷ�ɢ�ң�������"HIR"��ժ������"HIW"��ת����Ŵ�ȴ�Եô������£�ȫ�ǴӲ����ܵĽǶȻӳ�!\n"NOR, me);                 

         
       skill = me->query_skill("tianshan-zhang", 1);
           

       me->add_temp("apply/parry",  -skill/2);
       me->add_temp("apply/dodge",  -skill/2);
       me->add_temp("apply/attack",  skill/3);

       me->add_temp("apply/damage",  skill/5);

       me->add_temp("apply/staff",  skill/2);

		   
       me->set_temp("tsz/lpf",skill);

	   me->add("neili", -300);
       me->add("jingli", - 200);
       if (me->query_skill("tianshan-zhang",1)<350)
			me->start_perform(1, "������");
       
	   call_out("remove_effect", 1, me, (int)skill/10);
       return 1;
}

int remove_effect(object me,int count)
{
        int skill;
		object weapon;
		if(!me) return 0;

        if(!me->query_temp("tsz/lpf")) return 0;
        
		skill=me->query_temp("tsz/lpf");
		weapon=me->query_temp("weapon");
		if( !me->is_fighting()
         || me->query_skill_mapped("staff") != "tianshan-zhang"
		 ||!weapon
		 || weapon->query("skill_type")!="staff"
         || count < 0)
		{
           me->add_temp("apply/staff",  -skill/2);
		   me->add_temp("apply/attack", -skill/3);
		   me->add_temp("apply/damage", -skill/5);
 
		   me->add_temp("apply/parry", skill/2); 
		   
me->add_temp("apply/dodge", skill/2);
           me->delete_temp("tsz/lpf");
           if(living(me))
             message_vision(HBGRN+HIW "\n$N��ڴ�ڵش���������Ҳ�����ָ������������������˲��ٵ�������\n\n" NOR, me);
           return 1;
         }
         
		 call_out("remove_effect", 1 ,me , count -1);
}
string perform_name(){ return HIW"���������"NOR; }

int help(object me)
{
        write(HIB"\n��ɽ�ȷ�֮�������硹��"NOR"\n");
        write(@HELP
	��ɽ�ȷ��������ɵ���Ҫ�似����׷�����֮��
	����������ɶ����书�����󷨣�����书����
	�ա������ص�ͷ������뾡�¡�
	������Ҳ�ǲ�Ҫ���Ĵ򷨣����˵����˼�������
	���Լ�������ǰ�������»�ȡ���к��˺���˲��
	���У����кݶ�������
		
	ָ�perform staff.luanpifeng
		
Ҫ��
	�������Ҫ�� 5000 ���ϣ�      
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 700 ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	��ɽ�ȷ��ȼ� 350 ���ϣ�
	�����ȷ��ȼ� 350 ���ϣ�
	�����ȷ����м�Ϊ��ɽ�ȷ���
	�����ڹ�Ϊ�����󷨣�
	�ֳ����������
	            
                
HELP
        );
        return 1;
}
