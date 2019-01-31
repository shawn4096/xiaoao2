// throw.c �����ȷ��綾
// By Yzuo 97.04

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage;
		damage=me->query_skill("lingshe-zhangfa",1)+me->query_skill("hamagong",1);
		damage=damage+random(damage/2);
        if( !target ) target = offensive_target(me);

        if( environment(me)->query("no_fight") )
                return notify_fail("���ﲻ�ܹ�������! \n");

        if( !target || !target->is_character() )
                return notify_fail("�綾ֻ�ܶԶ���ʹ�á�\n");

        if( (int)me->query_skill("hamagong", 1) < 350 )
                return notify_fail("��ĸ�󡹦������죬�����綾��\n");

        if( (int)me->query_skill("lingshe-zhangfa", 1) < 350 )
                return notify_fail("��������ȷ�������죬�����綾��\n");

        if( (int)me->query("neili", 1) < 2000 )
                return notify_fail("������������������綾��\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
            return notify_fail("��ʹ�õ��������ԡ�\n");

        if( (string)weapon->query("id") != "guaishe zhang" )
                return notify_fail("������û�����ȣ������綾��\n");

        me->add("neili", -200);

        msg = MAG "$N��䷢���̶��ĸ�����죬����ǰͷ��С���͵���ͷ��һ��ۺ춾�������������$n��\n";

        me->start_busy(1);
        if( random( (int)me->query_skill("lingshe-zhangfa",1))
          > target->query_skill("dodge",1)/3 )
        {
                msg += MAG "���$p��$P��ͷС��һ�����У�\n" NOR;
                if (target->query("neili")/4 < random(me->query("neili")))
                {
                   msg += MAG "$pֻ�ŵ�һ�����㣬��ǰ��ģ��������\n" NOR;
                   target->receive_damage("qi",damage,me);
                   target->receive_wound("qi",damage/3,me);
                   target->receive_wound("jing", damage/5,me);
                   target->apply_condition("snake_poison", random(me->query_skill("lingshe-zhangfa",1)/10) + 1 +target->query_condition("bt_poison")); 
                   target->apply_condition("snake_poison", random(me->query_skill("lingshe-zhangfa",1)/10) + 1 +target->query_condition("bt_poison"));
                   if (userp(target)) target->add_busy(1+random(1));
                   else target->add_busy(2 + random(5));
                   message_vision(msg, me, target);
                   COMBAT_D->report_status(target);
                }
                else
                {
                   msg += CYN "$p����������һ���������߶���ȥ����ʱ�߶�����$PƮ�˻�ȥ��\n" NOR;
                   msg += MAG "$Pֻ�ŵ�һ�����㣬��ǰ��ģ��������\n" NOR;
                   me->receive_damage("qi",damage/3,me);
                   me->receive_wound("qi",damage/5,me);
                   me->receive_wound("jing", damage/10,me);
                   me->apply_condition("snake_poison", random(me->query_skill("lingshe-zhangfa",1)/10) + 1 +me->query_condition("snake_poison"));
                   me->start_busy(1 + random(2));
                   message_vision(msg, me, target);
                   COMBAT_D->report_status(me);
                }

        } else {
                msg += CYN"����$p��æ����һ�ԣ����˿�ȥ��\n" NOR;
                me->start_busy(3);
                message_vision(msg, me, target);
        }
        if( !target->is_killing(me) ) target->kill_ob(me);
        return 1;
}

string perform_name(){ return MAG"�綾"NOR; }

int help(object me)
{
        write(HIC"\n�����ȷ�֮"+HIB"���綾��"NOR"\n\n");
        write(@HELP
	�����ȷ����ǰ���ɽ��ѧ�������ڣ�ŷ����һ�������ߺ͸�󡹦���ｭ����ƾ�����
	���񼼵���������ƺ�������������ɽһ����ѧ������ɽ��ѧ�Ժ��������ա��綾
	����Ϊ��ɫ�������ȷ����������������йأ�����ƾ�����ɽ�Ĺ����ȷ������к�
	��ʹ�öԷ��ڷ���ʤ��֮��Ϊ�߶�����Ⱦ��
	ע�⣺��װ�������ȷ��д˹�Ч��
	Ҫ�󣺵�ǰ���� 2000  ���ϣ�
		�����ȷ��ȼ� 350 ���ϣ�
		�����ȷ��ȼ� 350 ���ϣ�
		��󡹦�ĵȼ� 350 ���ϣ�		
		����ȭ��Ϊ����ȭ����
		�����м�Ϊ�����ȷ���

HELP
        );
        return 1;
}