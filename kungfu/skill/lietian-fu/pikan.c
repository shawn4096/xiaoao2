//pikan.c by sohu@xojh
//���츫

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
		string msg;
		int p,damage;
		int ski=me->query_skill("lietian-fu",1);
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("lietian-fu", 1) < 140 )
                return notify_fail("������츫������̫ǳ���޷�ʹ�á�������������\n");
        if( (int)me->query_skill("axe", 1) < 140 )
                return notify_fail("��Ļ�����������̫ǳ���޷�ʹ�á�������������\n");


      
        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("�������̫ǳ���޷�ʹ�á�������������\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("����������㣬�޷�ʹ�á�������������\n");
        if( (int)me->query("jingli") < 500 )
                return notify_fail("��ľ������㣬�޷�ʹ�á�������������\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "axe"
            || me->query_skill_mapped("axe") != "lietian-fu" 
			|| me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("���׼�����򲻶ԡ�\n");

        message_vision(HIR"$N���һ��������ȫ������������磬���󸫳���һ����$n��ȥ��\n" NOR,me,target);
        
		if (random(me->query_skill("axe",1))>target->query_skill("parry",1)/2
			||random(me->query_str(1))>target->query_str(1)/2)
		{
		
			damage = me->query_skill("axe",1) +me->query_skill("lietian-fu",1);
			damage += me->query_skill("force",1);
			damage = damage*me->query_str()+ random(damage);
			if (damage > 3500) damage = 3500+random(damage-3500)/100;
			
			target->receive_damage("qi", damage, me);
			target->receive_wound("qi", damage/3, me);

			msg = RED"$N����������ʽ�򵥣�$n������������һ��ͷ���У�\n"NOR;
	
			if (random(2)) {
				p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
				msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			}else {
				p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
				msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
			}
	   		message_vision(msg, me, target);		
		}
		else {
			msg = CYN"����$p�Ṧ׿Խ����������һ�ԡ�\n"NOR;
			//me->add("neili", -100);
			message_vision(msg, me, target);
		}
		me->add("neili", -100);
		me->add("jingli", -50);

		me->start_perform(2, "������");
	
        return 1;
}

string perform_name(){ return HBRED+HIW"������"NOR; }

int help(object me)
{
        write(HIR"\n���츫֮������������"NOR"\n\n");
        write(@HELP 
	���츫֮�������������������ǵ������ɵ�
	һλǰ�����ˣ��и��ڿ�������ж̱����
	���������մ���˵���״���ܽ�������һ
	�׽���ɱ�ĸ�������ս���з����˾޴��
	���á�����ͷ��ֱ��Ч�����ӳ�����
	
	ָ�perform axe.pikan

Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	�������Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	���������ȼ� 140 ���ϣ�
	���츫���ȼ� 140 ���ϣ�
	��������Ϊ���츫����
	�����м�Ϊ���츫����
	�����ڹ�Ϊ��Ԫ���ɷ���
	�ֳָ���������
HELP
        );
        return 1;
}