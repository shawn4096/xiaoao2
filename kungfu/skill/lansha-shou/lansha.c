 //lansha-shou.c 
//��ɰ��
//by sohu @xojh

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int lvl,damage;
		object weapon;
        lvl= me->query_skill("lansha-shou",1);
		weapon=me->query_temp("weapon");
        if (lvl<80)
                return notify_fail("�����ɰ�ֻ���������\n");         
        
        if( !target ) target = offensive_target(me);
        if( !target
			||!target->is_character()
			||!me->is_fighting(target) )
                return notify_fail("����ɰ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		if( (int)me->query("neili") < 600 )
			return notify_fail("�������������\n");

		if (!me->query_skill("lansha-shou",1)<250)
			return notify_fail("�����ɰ����δ����ͨ������ʹ����ɰ���졹��\n");

		if( (int)me->query_skill("force", 1) < 250 )
			 return notify_fail("����ڹ���򲻹�������ʹ�á���ɰ���졹��\n");
		if (me->query_temp("weapon"))
		{
			if( me->query_skill_mapped("throwing") != "lansha-shou")
			 return notify_fail("����뼤��throwing����ʵʩ����ͻϮ��\n");
			if( me->query_skill_mapped("throwing") != "lansha-shou")
			 return notify_fail("����뼤��throwing����ʵʩ����ͻϮ��\n");
		}
		if( me->query_skill_mapped("hand") != "lansha-shou"
			||me->query_skill_prepared("hand") != "lansha-shou")
			 return notify_fail("��û�����ַ�Ϊ����ɰ�֡���\n");
     
        
        damage= me->query_skill("lansha-shou",1)+me->query_skill("xuedao-jing",1)+me->query_skill("poison",1);
		damage=damage*2+random(damage);

        
		message_vision(HIB"$NͻȻ����˫�ƣ�����������˫���������������һƬ��һ��"HIC"����ɰ�֣�"HIB"����ʽ����$n���ؿڣ�\n" NOR,me);
        me->add_temp("apply/attack",lvl/4);
		me->add_temp("apply/damage",lvl/5);
		me->add_temp("apply/throwing",lvl/5);
		me->add_temp("apply/hand",lvl/5);

		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
        
        me->add("neili",-150);
		me->add("jingli",-100);
                 
        if (random(me->query_skill("lansha-shou",1))> target->query_skill("parry",1)/2
			||random(me->query_str())>target->query_con()/2)
		{
                target->receive_wound("qi",damage,me);
                message_vision(RED"$n"+RED"һ���ҽУ���$N"+RED"�ĵ��ؿڷ��ƣ��̲�ס������Ѫ��\n\n"NOR,me,target);
				target->add_busy(1);
				target->apply_condition("no_exert",1);
				target->apply_condition("lansha_poison",10+random(4));
	
        }               
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);

		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack",-lvl/4);
		me->add_temp("apply/damage",-lvl/5);
		me->add_temp("apply/throwing",-lvl/5);
		me->add_temp("apply/hand",-lvl/5);

		me->start_perform(4,"��ɰ����");
        return 1;
}  

string perform_name() {return HBBLU+HIG"��ɰ����"NOR;}

int help(object me)
{
	write(HBBLU+HIG"\n��ɰ��֮����ɰ���졹��"NOR"\n\n");
        write(@HELP
	��ɰ����Ѫ���ŵ������书������һλ��ɮ������
	�еļҴ��书����Ϊ���书�ȿ������������ַ���
	���Է����ֿ����Դ��ַ����Ͱ����������Ƿ�����
	ɰ�����˷���ʤ����ʮ�ִ������ա�
	
	perform throwing(hand).hongsha

Ҫ��
	�������  1500 ���ϣ�
	��ǰ����  500  ���ϣ�
	Ѫ����    350  �����ϣ�
	��ɰ�Ʒ�  350  �����ϣ�
	�����Ʒ�Ϊ��ɰ�֣�
	�����м�Ϊ��ɰ�֣�
	�ڹ�����;
	���ֻ�������ʹ�ã�
HELP
        );
        return 1;
}