//��������
//����new systemҪ��������ΪA+
// edit by sohu@xojh

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

string perform_name() {return HIY"��������"NOR;}

int perform(object me, object target)
{
          int lvl,lvl2;

        lvl = me->query_skill("anran-zhang", 1) ;
		
		if (userp(me))
		    lvl=lvl/2;
		else lvl=lvl/4;
	    
		if (me->query("gender")=="Ů��") lvl/=4;
		if (me->query("gender")=="����")
			return notify_fail("�����������ͣ����������ס�ֻ����ս����ʹ�á�\n");
;

        if( !target ) target = offensive_target(me);

        if( !target 
         || !me->is_fighting(target) )
                return notify_fail("���������ס�ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á��������ס���\n");   

        if( (int)me->query_skill("anran-zhang", 1) < 250 )
                return notify_fail("�����Ȼ�����ƻ�������죬ʹ�������������ס�������\n");

        if( (int)me->query_skill("force", 1) < 250 )
                return notify_fail("��Ļ����ڹ��ȼ���������ʹ�������������ס�������\n");

        if ( me->query_skill_mapped("strike") != "anran-zhang"
          || me->query_skill_prepared("strike") != "anran-zhang"
          || me->query_skill_mapped("parry") != "anran-zhang"
           )
             return notify_fail("�������޷�ʹ�á��������ס�������\n");       

        if((int)me->query("max_neili") < 3500 )
                return notify_fail("����������̫����ʹ�������������ס���\n");      

        if((int)me->query("neili") < 1000 )
                return notify_fail("����������̫����ʹ�������������ס�������\n");
		if((int)me->query("jingli") < 500 )
                return notify_fail("����������̫����ʹ�������������ס�������\n");
     
		if (me->query("divorce"))
					return notify_fail("��������飬����ʹ�÷��ӳ���Ȼ�����ƾ�����\n"); 
        me->set_temp("jishi", 3); 
        message_vision(HIY"\n$NͻȻһ���ķ�����֮��ӿ����ͷ�����ǡ��������ס����������������������Ȼ����������\n"NOR,me,target);
        me->add_temp("apply/damage", lvl/3);
        me->add_temp("apply/attack", lvl);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if (present(target,environment(me)) && me->is_fighting(target))
	    {
		    if (me->query_skill("anran-zhang",1)<350)
		                  target->add_busy(1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        }
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        me->add_temp("apply/damage", -lvl/3);
        me->add_temp("apply/attack", -lvl);

        me->add("neili", -random(300));
        me->add("jingli", -random(150));
        me->delete_temp("jishi");
        me->start_perform(3,"��������");        
        me->start_busy(1+random(1));
        return 1;
}

//�������� ���࣬��Ϊ�����似 150��ˢ��������

int help(object me)
{
        write(HIB"\n��Ȼ������"+HIY"���������ס�"NOR"\n");
        write(@HELP

	����Ժ�С��Ů�ھ���ȶϳ���ǰ���֣�������ҹ˼��
	����С��Ů����������������������Ȥ�����ں���֮��
	���������������һʮ�����Ʒ������������Ʒ�����Ϊ
	��Ȼ��������ƣ�ȡ���ǽ��͡��𸳡����Ǿ���Ȼ���
	�����ߣ�Ψ�������֮�⡣���Ʒ�������������������
	�壬��һ������ۺ�������Խ������Խ��ʵ������
	�ض��ú���!
	�������������������ʱ�ڱȽϼ��ҵ��Ʒ�������һ��
	�֣���Ϊ�������У����ܲ��ã��Թ����أ�ʵ����Ȼ��
	��Ҫ�ľ������������޷�ʹ�á�
	
	perform strike.jishi

Ҫ��
	�����Ʒ�Ҫ�� 250 ������
	��Ȼ�Ʒ�Ҫ�� 250 ������
	�����ڹ�Ҫ�� 250 ������
	�������Ҫ�� 3500 ����	
	��ǰ����Ҫ�� 1000 ����
	��ǰ����Ҫ�� 500 ����
	�����Ҽ����Ʒ����м�Ϊ��Ȼ��
HELP
        );
        return 1;
}
