// focus.c, ���� by darken@SJ
// By Spiderii@ty����Ч��
#include <ansi.h>

inherit F_CLEAN_UP;
void remove_effect(object me,int count);
string exert_name(){ return HBBLU"��Ԫ����"NOR; }

int exert(object me)
{      
       int skill;
       skill = me->query_skill("guiyuan-tunafa",1);
       if( !me->is_fighting() && (int)me->query_skill("guiyuan-tunafa",1)<350 )
                return notify_fail("��ֻ����ս����ʹ�á���Ԫ��������\n");

        if( (int)me->query_skill("guiyuan-tunafa", 1) < 100 )
                return notify_fail("��Ĺ�Ԫ���ɷ�����Ϊ��������\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("�������������\n");

        if(me->query_temp("tz/focus"))
                return notify_fail("���Ѿ���ʹ���ˡ�\n");

        message_vision(HBBLU"$N΢΢һ���񣬹�Ԫһ����������˫�֣������ƺ���ǿ�˲��١�\n" NOR, me);
        if (me->query_skill("guiyuan-tunafa",1)<350)
        {
			me->start_busy(1);
        }
        me->add_temp("apply/strength", me->query_skill("guiyuan-tunafa", 1)/15);

		me->add_temp("apply/attack", me->query_skill("guiyuan-tunafa", 1)/10);
		me->add_temp("apply/strike", me->query_skill("guiyuan-tunafa", 1)/10);
        me->add("neili", -400);
        me->set_temp("tz/focus",skill /10);
        call_out("remove_effect", 1, me, skill/10);
        if (me->query_skill("guiyuan-tunafa",1)<350) me->start_exert(1, "����Ԫ������");
        return 1;
}
void remove_effect(object me, int count)
{
       if (!me) return;
       if( count < 1){
		   
           me->add_temp("apply/strength", -(me->query_skill("guiyuan-tunafa", 1)/15));

		   me->add_temp("apply/attack", -(me->query_skill("guiyuan-tunafa", 1)/10));
           me->add_temp("apply/strike", -(me->query_skill("guiyuan-tunafa", 1)/10));
		   message_vision(HIW"$N�˹���ϣ��������������ָ��糣��\n"NOR, me);
		   me->delete_temp("tz/focus");
           return;
        }
        call_out("remove_effect", 1 , me ,count -1);
}

int help(object me)
{
        write(HIR"\n��Ԫ���ɷ�֮����Ԫ��������"NOR"\n\n");
        write(@HELP 
	����ˮ��Ư��ǧ���������Ʒ���ˮ��Ư����
	������������Ԫ���ɷ�Ϊ���ư��ڴ��е���
	���ķ�����Ϊ�����������Ǿ��ұ���֮����
	��Ϊ���±�������Ͼ�������ڹ������
	��Ԫ���ɷ�һֱ�ڽ����������ԡ���������
	���ӻ�Ե�ɺϵõ������ķ�����ô������ѧ
	�ؽ�������һ����̨�ס�
        
	yun guiyuan

Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	�������Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	�����ڹ��ȼ� 100 ���ϣ�
	�����ڹ�Ϊ��Ԫ���ɷ���                              
HELP
        );
        return 1;
}