//    /kungfu/skill/xingyi-zhang/daoying.c pfm daoying
// by leontt /22/6/2000

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int j;
        object weapon = me->query_temp("weapon");
        j = me->query_skill("murong-daofa",1);
        if (me->query_temp("sy/shenyuan"))
			j=j+me->query_skill("shenyuan-gong")/6;
		
		//if (!userp(target)) j=j/4;
        //else j =j /8;
 
		j=j/4;
        
		if( !target ) target = offensive_target(me);

        if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))               
                return notify_fail("��Ӱ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");                

        if( (int)me->query_skill("murong-daofa", 1) < 220 )
                return notify_fail("��ĵ�����δ���ɣ�����ʹ�õ�Ӱ�ƣ�\n");        

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "murong-daofa")
                return notify_fail("������û�е����޷�ʹ�õ�Ӱ�ƣ�\n");

        if((int)me->query_skill("xingyi-zhang", 1) < 220 )
                return notify_fail("����Ʒ���δ���ɣ�����ʹ�õ�Ӱ�ƣ�\n");  
        if((int)me->query_skill("strike", 1) < 220 )
                return notify_fail("��Ļ����Ʒ���δ���ɣ�����ʹ�õ�Ӱ�ƣ�\n");  
        if((int)me->query_skill("blade", 1) < 220 )
                return notify_fail("��Ļ�������������죬�����ڵ����м���ʹ�õ�Ӱ�ơ�\n");

        if((int)me->query_skill("murong-daofa", 1) < 220 )
                return notify_fail("���Ľ�ݵ���������죬�����ڵ����м���ʹ�õ�Ӱ�ơ�\n");     

       /* if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("����ڹ�������Ԫ�����޷�ʹ�õ�Ӱ�ƣ�\n");      */

        if(me->query_skill_mapped("strike") != "xingyi-zhang" 
         || me->query_skill_prepared("strike") != "xingyi-zhang")
                return notify_fail("��û�����ƣ��޷�ʹ�õ�Ӱ�ƣ�\n");

        if(me->query_skill_mapped("parry") != "xingyi-zhang")
		if(me->query_skill_mapped("parry") != "douzhuan-xingyi")

			if(me->query_skill_mapped("parry") != "murong-daofa")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�õ�Ӱ�ƣ�\n");

        if((int)me->query("max_neili") < 3000 )
                return notify_fail("������������Ϊ����������ʹ�õ�Ӱ�ƣ�\n");      

        if((int)me->query("neili") < 500 )
                return notify_fail("�������������㣬����ʹ�õ�Ӱ�ƣ�\n");      


        message_vision(HIR"\n$N���һ��ʹ��Ľ�ݾ�������Ӱ�ơ���ֻ��$P���浶�ߣ�ƬƬ�����м����������Ʒ�һ����$n��\n"NOR, me,target);
        
		
		me->add("neili", -200); 
        me->add("jingli", -150);
        
        me->add_temp("apply/attack", j); 
        me->add_temp("apply/blade",j);
        me->add_temp("apply/damage",j/2);
		me->set_temp("mr_daoying",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
		
if(objectp(target) && me->is_fighting(target))
        {
                weapon->unequip(); 
				me->add_temp("apply/strike",j*3/2);
				message_vision(HIR"\n$N��Ȼ���������ĵ�����ͻ��һ�ƣ�ӡ��$n��\n"NOR, me,target);
				target->add_busy(2);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				me->add_temp("apply/strike",-j*3/2);

				weapon->wield(); 
        }
        if(objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		
        if(objectp(target) && me->is_fighting(target) && random((int)me->query_str()) > 30)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

      
	    me->add_temp("apply/damage",-j/2);
        me->add_temp("apply/blade",-j);
        me->add_temp("apply/attack", -j);
		me->delete_temp("mr_daoying");
        me->start_busy(1+random(2));
		me->start_perform(4,"��Ӱ��");  
		return 1;
}
string perform_name(){ return HIR"��Ӱ��"NOR; }

int help(object me)
{
        write(HIC"\nĽ�ݵ���֮"+HIR+"����Ӱ�ơ�"NOR"\n\n");
        write(@HELP
	Ľ�ݵ�������Ľ�ݼ����д����ҳ��ǵ���Ҫ�����似��Ľ����
	�������Ǵ�������ᣬ��Ľ�ݴ���ʼ�������ھ���֮�䣬����
	����ʵս���������Ѿ��ںϲ����������ɵĵ���������һ����
	�������м��ơ��˵��������ޱȣ�����ʤ������Ϊ��Ϊ�ҳ���
	�ã������ڹ���������Ҫ��������Խ����������ǿ��
	
ָ�perform blade.daoying

Ҫ��
	��ǰ���� 500 ���ϣ�
	������� 3000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	�����Ʒ��ȼ� 220 ���ϣ�
	Ľ�ݵ����ȼ� 220 ���ϣ�
	�����Ʒ��ȼ� 220 ���ϣ�
	�����Ʒ�Ϊ�����ƣ�
	�����м�ΪĽ�ݵ�����ת���ƣ�
                
HELP
        );
        return 1;
}
