// haoran.c ��Ȼһ��
//sohu@xojh
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage, ap,dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��Ȼһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("haotian-zhang", 1) < 200)
                return notify_fail("�������Ʋ�����죬����ʹ�ú�Ȼһ����\n");

        if ((int)me->query_skill("force",1) < 200)
                return notify_fail("����ڹ���Ϊ����������ʩչ��Ȼһ����\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("�����������������޷�ʹ�ú�Ȼһ����\n");

        if (me->query_skill_mapped("strike") != "haotian-zhang")
                return notify_fail("������û�м�������Ʒ����޷�ʹ�ú�Ȼһ����\n");

        if (me->query_temp("weapon"))
                return notify_fail("�������ֲ��ܹ�ʹ�ú�Ȼһ����\n");

        message_vision(HIC "$N" HIC "���һ����������$n" HIC "���ϣ�˫��"
              "ͬʱ���������������һ�С���Ȼһ����������\n" NOR,me);
  		message_vision(HIY "$pֻ��һ�ɺƵ��ľ�������������������ͣ�\n" NOR,me,target);

        if (living(target))
                dp = target->query_skill("force") / 2;
        else    dp = 0;
		ap=me->query_skill("haotian-zhang",1);
		if (me->query_temp("xtg/wuqi"))
		{
			ap=ap+me->query_skill("xiantian-gong",1)/2;
		}
        if (random(ap) > dp
			||random(me->query_str())>target->query_str()/2)
        {
               // me->start_busy(2);
                me->add("neili", -250);
                
				damage = 250*me->query("jiali");
              
				message_vision(HIR "���$p" HIR "��$P" HIR "���������㣬��æ���ˣ������$P" HIR "һ�ƻ��˸����У���Ѫ��ֹ����\n" NOR,me,target);

				target->receive_damage("qi",damage,me);
				target->receive_wound("qi",damage/3,me);

		} else
        {
                me->start_busy(1);
                me->add("neili", -60);
                message_vision(CYN "����$p" CYN "ʶ����$P"CYN "��һ�У�ббһԾ�ܿ���\n" NOR,me,target);
        }
		me->start_perform(4,"��Ȼһ��");
		
        return 1;
}

string perform_name(){ return HIC"��Ȼһ��"NOR; }

int help(object me)
{
        write(HIC"\n�����֮����Ȼһ������"NOR"\n");
        write(@HELP
	�������ȫ���ǰ���书֮һ���������к��ĵ��������书
	ȫƾһ���������ڣ����಻������ʹ���������Է���������
	����ȫ��߼��书�Ļ�����ȫ�����������������
	��Ȼһ���ǽ�ȫ�澢�����ۣ�Ȼ����Ȼ�Ƴ������Է����ö�
	���޷���ܣ�ֻ��Ӳ������ʽ���������ͣ�����Ϊ��������
	
	ָ�perform strike.haoran

Ҫ��
	���칦���ĵȼ� 200  ���ϣ�
	ԧ�������ȵȼ� 200  ���ϣ�
	�����ȷ��ĵȼ� 200  ���ϣ�
	��������Ҫ�� 1500 ���ϣ�
	��ǰ������Ҫ�� 800  ���ϣ�
	�����ұ��Ʒ�Ϊ����ƣ�
	�������칦��
	�����ұ��Ʒ�Ϊ����ơ�
HELP
        );
        return 1;
}

