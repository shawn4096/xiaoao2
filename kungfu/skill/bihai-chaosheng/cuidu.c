// Modified by Darken@SJ
#include <ansi.h>

string exert_name() { return HIG"���Ƕ��߶�"NOR; }

int exert(object me, object target)
{
        int level = me->query_skill("bihai-chaosheng",1);
        int num;

        if( !objectp(target) )
                return notify_fail("��Ҫ�߶�˭�Ķ��ԣ�\n");
        if( environment(me)->query("no_fight") )
                return notify_fail("���ﲻ�ܴ߶���\n");
        if (me->query("thdjj/ronghe")!="pass")
			if( me->is_fighting() || target->is_fighting())
                return notify_fail("����ڹ���δ�ںϹ�ͨ��ս���д߶�����������\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 350)
                return notify_fail("��ı̺���������Ϊ��������\n");
        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("���������Ϊ������\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("�������������\n");
        if( me == target ) 
                return notify_fail("�������Ⱑ��\n");
        if(!target->query("thd/fugu"))
                return notify_fail("����û���и��Ƕ���\n");

        num = target->query("thd/fugu");        
        me->add("neili", -300);
        me->add("jing", -500);
        target->receive_wound("qi",random(level)*num,me);
        target->receive_wound("jing",random(level)*num,me);
        target->set_temp("last_damage_from", me);
        target->add("neili",-random(level));
        if (me->query("thdjj/ronghe")=="pass") 
        {
			target->receive_wound("qi",level*3*num,me);
            target->receive_wound("jing",level*num,me);
			target->add_busy(2+random(3));
        }
		else target->add_busy(2+random(3));
        message_vision(HIW"$N����̺����������߶�$n�ĸ��Ƕ�֮����"NOR,me,target);
        message_vision(HIW"$n��"HIR"���Ƕ�"HIW"֮�������ˣ�\n"NOR,me,target);
        if(!target->is_killing(me)) me->kill_ob(target);
        me->add_busy(3+random(2));
        return 1;
}

int help(object me)
{
        write(HIG"\n�����Ƕ�---���־�����"NOR"\n");
        write(@HELP
	�һ�����Ӣ�ƾ���֮�߶���ʹ�ñ̺�������
	�߶����Ƕ��Ķ��ԣ���Ŀ��ľ������ܵ���
	�ˣ�ͬʱ���ֵ����ɢ���־ۼ���������
	�߶��и�������Ч�����⿪�һ������ںϾ�
	���󣬸��似����Ծ��
	
	ע�⣺��ս��������ǰ�����˰��¼�ö����
		�����ֳ����������������⿪�ں�����
		�������Ч���С�
	���ã�set �̺����� �߶�
	ָ�yun cuidu

Ҫ��
	�̺������ȼ� 350 ���ϣ�
	������� 1000 ���ϣ�
	��ս������ʹ�á�
HELP
        );
        return 1;
}

