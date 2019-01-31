// jd.c 
// by emnil   98.10.4
//edit by sohu 2014
#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name() {return HIG"�ⶾ"NOR;}

int exert(object me, object target)
{
        int skill;

        if(target != me && !present(target,environment(me)))
                return notify_fail("�������û������ˣ�\n");

        if((int)me->query_skill("dulong-dafa",1) < 250  )
                return notify_fail("��Ķ����󷨹����������޷��⻯�����ƶ���\n");
		if((int)me->query_skill("medicine",1) < 100  )
                return notify_fail("��ı������������޷��⻯�����ƶ���\n");
		if((int)me->query_skill("poison",1) < 150  )
                return notify_fail("��Ķ��Ʋ������޷��⻯�����ƶ���\n");
        if((int)me->query_skill("shenlong-yaoli",1) < 180  )
                return notify_fail("�������ҩ��ѧ��������ȱ���޷��⻯�����ƶ���\n");

        if((int)me->query("neili") < 500
         || (int)me->query("max_neili")< 2500  )
                return notify_fail("�������������\n");

        skill= me->query_skill("dulong-dafa",1) + me->query_skill("shenlong-yaoli",1)+ me->query_skill("medicine",1);
         if((int)target->query("huagu") > skill)
            target->add("huagu",-skill);
        else
            target->delete("huagu");
        if( target != me)
          message_vision(HIW"\n$N���ֵ�ס$n��˫�ƣ�������$n���ϵĶ��رƳ����⡣\n\n"NOR,me,target);
        else 
          message_vision(HIW"\n$N��ͷ�󺹣��þ��������ڵĶ��رƳ����⡣\n\n"NOR, me);
     
		target->clear_condition("huagu_poison");
        target->clear_condition("qianli_poison");
        target->clear_condition("7bug_poison");
        target->clear_condition("fugu_poison");
		target->clear_condition("snake_poison");
        target->clear_condition("sld_shexin");
        me->add("neili",-1000);
		if (!me->query("quest/sld/dldf/pass"))
			me->add("max_neili",-random(10));
		me->start_busy(5);
        if( target != me) target->start_busy(5);
        me->add("jingli",-400);
        return 1;
}
int help(object me)
{
        write(WHT"\n������֮"+HIG"���ⶾ��"WHT"��\n\n");
        write(@HELP
	�����������������ڹ����������ǿ�ɽ��ʦ
	������������ɶ����ķ����������������߶�
	�����ԣ�������ǿ����һ�档
	���ⶾ�������������������ڹ��ķ��Ͷ���
	������ҩ��֪ʶ���ϣ�������������һ����
	���ֶ��ظ��뻯�⡣
	ע�⣺��û�н⿪���������⣬���������
	ʹ���ߵ����������
	
	ʹ��ָ�yun jiedu
		
Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	�������Ҫ�� 2500 ���ϣ�
	�����ڹ��ȼ� 250  ���ϣ�
	�����󷨵ȼ� 250 ���ϣ�
	��������ȼ� 100 ���ϣ�
	����ҩ��ȼ� 180 ���ϣ�
	���Ƽ������� 150 ���ϣ�
	�����ڹ�Ϊ�����󷨣�
	
HELP
        );
        return 1;
}
