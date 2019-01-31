// Code of �Ѻ�
// Modified by sohu@xojh
//��צ 
//����צ������

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill,damage;
        
		skill=me->query_skill("jiuyin-shenzhua",1);
		damage=skill+me->query_skill("daode-jing",1)+me->query_skill("jiuyin-zhengong",1);
		damage=damage*me->query_str(1)/7+random(damage);

        if (!target ) target = offensive_target(me);

        if (!target||!target->is_character()||!me->is_fighting(target) )
                return notify_fail("��������צ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		weapon=target->query_temp("weapon");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������������������ʹ����������צ����\n");

        if ((int)me->query_skill("jiuyin-shenzhua",1)< 450)
                return notify_fail("��ľ�����צ��Ϊ������\n");

        if (me->query_skill_mapped("claw")!="jiuyin-shenzhua"
			||me->query_skill_prepared("claw")!="jiuyin-shenzhua")
                return notify_fail("����δ����������צ��\n");
        if (!me->query_skill("jiuyin-zhengong"))
                return notify_fail("����δѧ������湦���޷�ʩչ���Ͼ�Ĺ���\n");
		if (!me->query_skill("daode-jing"))
                return notify_fail("����δѧ����¾����޷�ʩչ���Ͼ�Ĺ���\n");

        if (me->query("jiali") < 50)
                return notify_fail("��ĳ�����ô�ᣬ�ֺα�ʹ��ɱ���أ�\n");
        if (me->query("max_neili")<15000) return notify_fail("����������������\n");

        if (me->query("neili")<2000) return notify_fail("�������������\n");

        if (me->query("jingli")<=1500) return notify_fail("��ľ���������\n");
		if (me->query_temp("jysz/shenzhua"))
			return notify_fail("������ʹ�þ�����צ������\n");
        
		message_vision(HBWHT+RED "\n$N�ͺ�һ����������˫ָ���������澭��"NOR+HIM"��������צ��"HBWHT+RED"�Ĺ���ʩչ��������ָ��צ��������ָ��������\n\n" NOR, me,target);
		message_vision(HIM"������ʩչ�������Թ������󣬱���˲�䱩�ǣ�����ǿ����\n"NOR,me);
		me->add_temp("apply/claw",skill/4);
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/damage",skill/6);
		me->add_temp("apply/strength",skill/20);
		me->set_temp("jysz/shenzhua",skill);
		call_out("remove_shenzhua",1,me,(int)skill/30);
		
		if (random(me->query_skill("force",1))>target->query_skill("force",1)/2
		//	||random(me->query_str(1))>target->query_str(1)/2
			||random(me->query_dex(1))>target->query_dex(1)/2)
		{
			if (weapon)
			{
				message_vision(MAG"$N˫צ�ζ���ǰ��������ס$n������$n��ע��ֱ������"+weapon->query("name")+"�ϣ�\n"NOR,me,target);
				message_vision(YEL"$nһʱ���飬Ϊ$Nץס"+weapon->query("name")+YEL"��˦�����ϣ�\n"NOR,me,target);
				weapon->move(environment(target));
				
			}
			else {
				message_vision(HIC"$n������ϣ�����Ʈ�����㡢�á�����ʽ�����绨����\n"NOR,me,target);
				message_vision(HIG"$n��˲����ס���ùǣ���ʱ������ԣ��������ã�\n"NOR,me,target);
				target->receive_damage("qi",damage,me);
				target->receive_wound("qi",damage,me);
				target->add_busy(3);
			}
		}
		me->add("neili",-800);
		me->add("jingli",-500);
        return 1;
}
int remove_shenzhua(object me,int count)
{
	int skill;
	if (!me) return 0;
	skill=me->query_temp("jysz/shenzhua");
	if (count<0
		||!me->is_fighting()
		||me->query_skill_mapped("claw")!="jiuyin-shenzhua"
		||me->query_skill_mapped("parry")!="jiuyin-shenzhua")
	{
		message_vision(HBWHT+MAG "\n$N��������һ��������������צ���򻺻��չ���\n\n" NOR, me);
		me->add_temp("apply/claw",-skill/4);
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/6);
		me->add_temp("apply/strength",-skill/20);
		me->delete_temp("jysz/shenzhua");
		me->start_perform(3,"������צ");
		return 1;
	}
	
	call_out("remove_shenzhua",1,me,count--);
}

string perform_name(){ return HBMAG+HIW"������צ"NOR; }

int help(object me)
{
        write(RED"\n������צ֮��������צ����"NOR"\n\n");
        write(@HELP
	������צ���Ǿ����澭�Ͼ�Ĺ���Ϊһ�����˻���
	���������Ǽ�������צ���Ĵ�ȫ������似��������
	צʩչ��צ���������������Ĺ���������ſ̣���
	�Թ�ĹҲ��������
	������צ�ھ���������ʹ֮�£�����˫ָ������������
	��Է��б����и��ʴ���ñ�������û�п��ܽ��Է�
	��Ѩ���ش���

	ע�⣺set ������צ ���� �и���������Ч��
	
	ָ�perform claw.shenzhua

Ҫ��  
	��ǰ���������� 2000 ���ϣ�
	������������� 15000 ���ϣ�
	��ǰ���������� 1500 ���ϣ�
	������צ�ĵȼ� 450 ���ϣ�
	����צ���ĵȼ� 450 ���ϣ�
	�����ڹ��ĵȼ� 450 ���ϣ�
	����צ��Ϊ������צ��                
	��צ��Ϊ������צ��
	�����ޱ�����	

HELP
        );
        return 1;
}
