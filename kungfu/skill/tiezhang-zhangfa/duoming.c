// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"������צ"NOR; }

int perform(object me, object target)
{
        int skill,i;
        skill = (int)me->query_skill("tiezhang-zhangfa", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("��������צ��ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�������צ����\n");   
        if( skill < 200 )
                return notify_fail("��������Ʒ�������죬ʹ������������צ����\n");
        if(me->query_skill("guiyuan-tunafa",1) < 200 )
                return notify_fail("��Ĺ�Ԫ���ŷ�������죬ʹ������������צ����\n");
		 if(me->query_skill("strike",1) < 200 )
                return notify_fail("��Ļ����Ʒ�������죬ʹ������������צ����\n");
        if(me->query_skill_mapped("strike") != "tiezhang-zhangfa" 
			||me->query_skill_prepared("strike") != "tiezhang-zhangfa" )
               return notify_fail("�������޷�ʹ�á�������צ����\n");
        if( (int)me->query("max_neili") < 1500)
                return notify_fail("����������̫����ʹ������������צ����\n");      
        if( (int)me->query("neili") < 800 )
                return notify_fail("����������̫����ʹ������������צ����\n");
		if( (int)me->query("jingli") < 500 )
                return notify_fail("�����ھ���������ʹ������������צ����\n");
        message_vision(HBBLU"\n$N�������������ĳ������ֳ�ץ��ͬʱϮ��������ǿ����ɽ������ѹ��$n��\n"NOR,me,target);
        
		if (!userp(target))
        {
			i=3;
			me->add_temp("apply/damage",skill/6);
			me->set_temp("tzzf/duoming",1);
        }
		else i=2;
		if (random(me->query_dex()) > target->query_dex()/i) {
           message_vision(HIR"$N���ֳ�ץ���������������$n��$N��������ץס��\n"NOR,me,target);
           target->add_busy(1);
        }
        message_vision(HBBLU"\n$N��$n��Щ���ң�����һ�Ʒ����ľ�������$n��\n"NOR,me,target);
        me->add("neili", -random(500));
        me->add("jingli", -random(100));
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/damage",skill/5);
		if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/5);
		me->start_perform(3,"��������צ��");
		if (me->query_temp("tzzf/duoming"))
		{
			me->add_temp("apply/damage",-skill/6);
			me->delete_temp("tzzf/duoming");
		}
        return 1;
}


int help(object me)
{
        write(HIC"\n�����Ʒ�֮��������צ����"NOR"\n\n");
        write(@HELP 
	������צ������ʮ������֮һ����Ҫ����������
	�Ʒ����ص㣬��Ӳ������Ϊץ��ǣ�������Է���
	ͬʱ��������Է��ؿڣ��˵��������ޱȡ�

	perform strike.duoming
		
Ҫ��
	��ǰ���� 800 ���ϣ�
	��ǰ���� 500 ���ϣ�
	�����Ʒ��ȼ� 200 ���ϣ�
	�����ڹ��ȼ� 200 ���ϣ�
	�����Ʒ��ȼ� 200 ���ϣ�
	�����Ʒ�Ϊ�����Ʒ���
	�����м�Ϊ�����Ʒ���
	�����ڹ���Ԫ���ɷ���
HELP
        );
        return 1;
}