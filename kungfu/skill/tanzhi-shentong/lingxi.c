// lingxi.c ��Ϭһָ by sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h"

int perform(object me, object target)
{
        string msg;
        object weapon;
        int damage, p;

        if( !target ) target = offensive_target(me);

        if( !target ||!living(target)|| !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��Ϭһָֻ�ܶ�ս���еĶ���ʹ�á�\n");

      
		if (!me->query("thd/wuji/lingxi"))
		    return notify_fail("����Ȼ��˵������Ϭһָ����һ�У�����ȴδ���ڡ�\n");
        if( me->query_skill_mapped("finger") !="tanzhi-shentong" 
			|| me->query_skill_mapped("parry") !="tanzhi-shentong"
			|| me->query_skill_prepared("finger") !="tanzhi-shentong")
                return notify_fail("��ļ������书���ԣ�ʹ��������ָ��ͨ��\n");
        if (me->query_skill_mapped("force")!="bihai-chaosheng")
                return notify_fail("��ļ������ڹ����ԣ�ʹ��������ָ��ͨ��\n");
		if( (int)me->query_skill("bihai-chaosheng", 1) < 250 )
                return notify_fail("��ĵ�ָ��ͨ������죬�޷�ʹ����Ϭһָ��\n");
		if( (int)me->query_skill("tanzhi-shentong", 1) < 250 )
                return notify_fail("��ĵ�ָ��ͨ������죬�޷�ʹ����Ϭһָ��\n");

        weapon = me->query_temp("weapon");
        if (weapon) return notify_fail("��Ϭһָ�����ʹ�á�\n");

        if ( (int)me->query("neili") < 400)
                return notify_fail("��������������޷�ʹ����Ϭһָ��\n");

        msg = HIC "$N˫��һǰһ�󣬻����������ָͻ��һ��������������һ�ɣ������С�������ֱϮ$nǰ�ء�\n";

        damage = (int)me->query_skill("tanzhi-shentong", 1) + (int)me->query_skill("bihai-chaosheng", 1)+(int)me->query_skill("qimen-bagua", 1) ;
        damage =damage*2+ random(damage);
        if (!userp(target))
           damage=damage*2;
		me->add_temp("apply/finger",(int)me->query_skill("tanzhi-shentong", 1)/3);
        if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 3
			||random(me->query_skill("finger",1)) > (int)target->query_skill("parry",1) / 3) {
                msg += HIR"$n�������������ۡ���һ������ָ������ǰ�ء�����Ѩ����\n"NOR;
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage / 3,me);
                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "����");
                msg += "( $n" + eff_status_msg(p) + " )\n";
				target->apply_condition("no_exert",1);
				if (!userp(target))
				   target->set_temp("must_be_hit",1);
				me->add_temp("apply/damage",me->query_skill("tanzhi-shentong", 1)/4);
				COMBAT_D->do_attack(me, target, 0, 3);
				me->add_temp("apply/damage",-me->query_skill("tanzhi-shentong", 1)/4);
				if (!userp(target))
				    target->delete_temp("must_be_hit");
        } 
        else if (random(me->query("combat_exp")) > (int)target->query("combat_exp") * 2 / 3) {
                msg += HIY"$n���Ա�һ�����ù��˾��磬û�뵽���ָ����Ȼ�л�������$n����ת������������$p�ĺ󱳡�\n"NOR;
                target->receive_damage("qi", damage / 2,me);
                target->receive_wound("qi", damage / 4,me);
				target->add_busy(1+random(1));
                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "����");
                msg += "( $n" + eff_status_msg(p) + " )\n";
        }
        else {
                msg += HIY"$n���Ա�һ�����ù��˾��磬ȴ��Ȼ�������ָ����Ȼ�л�������æ��ֻ��һ��ǰ�˲ſ��������ģ���Ǳ�֮����\n" NOR;
        }
		me->add_temp("apply/finger",-me->query_skill("tanzhi-shentong", 1)/3);
        message_vision(msg, me, target);
        me->add("neili", -300);
        me->start_busy(3);
        me->start_perform(3, "��Ϭһָ");
        return 1;
}
string perform_name(){ return BLU"��Ϭһָ"NOR; }
int help(object me)
{
        write(BLU"\n��ָ��֮ͨ����Ϭһָ����"NOR"\n");
        write(@HELP

	ʩչ��ָ��ͨ����ǿ��һ�У����̺�������
	���ھ�������һָ��������ָ��ͨ��������
	�ţ�ʩչ������Ϭһָ�����������������
	�ǣ��޼���Ѱ�����������޴󣬶��Ҿ���һ
	����������Ч�����似Ϊ�����似�����Ժ�
	ս�������Լ�����ָ�����ж�������Ҫ��
	
	perform finger.lingxi

Ҫ��
	�̺������ȼ� 250 ���ϣ�
	��ָ��ͨ�ȼ� 250 ���ϣ�
	����ָ���ȼ� 250 ���ϣ�
	���������ȼ� 250 ���ϣ�
	�������Ҫ�� 3000 ���ϣ�
	����ָ��Ϊ��ָ��ͨ��
	��ָ��Ϊ��ָ��ͨ��
	�����м�Ϊ��ָ��ͨ��
	�����ڹ��̺�������
                
HELP
        );
        return 1;
}
