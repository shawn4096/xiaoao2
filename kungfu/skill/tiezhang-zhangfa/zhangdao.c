// �Ƶ�
//cre by sohu@xojh 2014/10
#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill;

        if(!target ) target = offensive_target(me);
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á��Ƶ�����\n");       
        if((int)me->query("neili") < 1000  ) 
                return notify_fail("��ĵ�ǰ����������\n");
        if((int)me->query_temp("tzzf/zhangdao") ) 
                return notify_fail("���Ѿ����Ƶ����˹��С�\n");
        if((int)me->query_skill("tiezhang-zhangfa", 1) < 350 )
                return notify_fail("��������Ʒ���������죬ʹ�������Ƶ�������\n");
        if((int)me->query_skill("force",1) < 350 )
                return notify_fail("��Ļ����ڹ��ȼ�������ʹ�������Ƶ�������\n");
        if((int)me->query_str() < 60 )
                return notify_fail("�������������ǿ����ʹ�������Ƶ�������\n");
        if( (int)me->query_skill("guiyuan-tunafa", 1) < 350 )
                return notify_fail("��Ĺ�Ԫ�����ɷ��ȼ���������ʹ�������Ƶ���������\n");
        if (!me->query("quest/tz/tzzf/zhangdao/pass"))
                return notify_fail("����˵���Ƶ�����������δ������а��塣\n");
        
		if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("�������޷�ʹ�á��Ƶ�����\n");

        skill = me->query_skill("tiezhang-zhangfa",1);
        skill = skill + me->query_skill("strike",1)/2;
        skill = skill / 6;
		
        me->add("neili", -(me->query_skill("strike",1)+100));
        me->add("jingli", -100);
        message_vision(YEL "$N�ͺ�һ�����˾����֣�һ˫������ɫ˲����ѩ�ף�Ӳ�羫����\n" NOR, me, target);
        if (me->query("quest/hubo/pass")) {
			skill=skill+me->query_skill("force",1)/8;
			message_vision(HIC"$N��˫�ֻ���֮�����뵽�Ƶ�֮�У�����������\n"NOR,me,target);
		}
		me->set_temp("tzzf/zhangdao", skill);
        me->add_temp("apply/attack", skill);
        me->add_temp("apply/damage", skill);
		call_out("remove_effect",1,me,skill/20);

     //   me->start_call_out( (: call_other, this_object(), "remove_effect", me, skill*3/2 :), skill/2);
        if( me->is_fighting() &&me->query_skill("tiezhang-zhangfa",1)<450) me->start_busy(1);
        return 1;

}

void remove_effect(object me, int amount)
{        
        int skill;
		if (!me) return;
	
        skill = me->query_temp("tzzf/zhangdao");
		if (!me->is_fighting()
			||amount<0)
		{
			me->add_temp("apply/attack", -skill);
			me->add_temp("apply/damage", -skill);
			me->delete_temp("tzzf/zhangdao");
			message_vision(YEL "\n$N�Ƶ��˹���ϣ�˫���𽥻ָ���ԭ״��\n" NOR, me);   
			return;
		}
		call_out("remove_effect",1,me,amount--);
     
}
string perform_name(){ return HIC"�Ƶ�"NOR; }

int help(object me)
{
        write(WHT"\n�����Ʒ�֮"HIC"���Ƶ�����"NOR"\n");
        write(@HELP
	������ǧ�����ƹ���ʮ������֮һ����
	�����Ƶ��������Ǿ���ʮ����ڹ����
	���ƣ������Ƶ�ʱ���ڹ��������Ʒ��
	Ե�����������Ҳ�����Ƶ�������ȫƾ
	һ������֧�š��˹���������ƵĹ�
	�������˺���
	ע�⣺�⿪˫�ֻ����󣬴�����������
	
	perform strike.zhangdao
        
Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�   
	�����Ʒ��ȼ� 350 ���ϣ�
	�����ڹ��ȼ� 350 ���ϣ�
	��Ч����Ҫ�� 60  ���ϣ�
	�����Ʒ�Ϊ�����Ʒ���
	�����м�Ϊ�����Ʒ���
	�������Ʒ��������ޱ�����
HELP
        );
        return 1;
}

