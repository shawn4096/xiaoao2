// pangen.c �̸����
// cre by sohu@xojh 
#include <ansi.h>
inherit F_SSERVER;
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;
        me->clean_up_enemy();
        weapon = me->query_temp("weapon");
        target = me->select_opponent();
        skill = me->query_skill("pangen-fu",1);
        if( !(me->is_fighting() ))
            return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á��̸�ʽ��������\n");
        if ( !weapon || weapon->query("skill_type") != "axe") 
            return notify_fail("������û����ôʹ�á��̸���ڡ�������\n");
        if ( me->query("neili") < 500 || me->query("max_neili") < 1500 )
            return notify_fail("��������������ʹ�������̸�ʽ��������\n");
        if( skill < 100 )
            return notify_fail("��ġ��̸���ڸ����ȼ�����, ����ʹ�á��̸�ʽ��������\n");
		if( me->query_skill("axe",1) < 100 )
            return notify_fail("��ġ������������ȼ�����, ����ʹ�á��̸�ʽ��������\n");
		if( me->query_skill("qiantian-yiyang",1) < 100 )
            return notify_fail("���Ǭ��һ���ȼ�����, ����ʹ�á��̸�ʽ��������\n");
        if( me->query_str() < 30 )
            return notify_fail("��������������޷�ʹ�á��̸���ڡ�������\n");
        if ( me->query_skill_mapped("axe") != "pangen-fu"
            || me->query_skill_mapped("parry") != "pangen-fu")
            return notify_fail("�������޷�ʹ�á��̸���ڡ�������\n");
        msg = HBYEL+HIW"\n$NͻȻ���һ������ͬ���裬�־�˫���۽�$n����ǰ��ʹ����ʮ��·���̸���ڡ�������\n"NOR;
        message_vision(msg, me, target);
        ap = me->query("combat_exp") + skill * 400;
        dp = target->query("combat_exp") / 3;
        if( dp < 1 )
                dp = 1;
        
		if (me->query("class")!="bone")
		{
			me->add_temp("apply/damage",(int)me->query_skill("axe",1)/5);
			me->set_temp("pgf/pangen1",1);
		}
            //return notify_fail("���ǳ��ҵ���, ����ʹ�á��̸�ʽ��������\n");
/**/
		if( random(ap) > dp )
		{
           if(userp(me))
             me->add("neili",-300);
             msg = HIR "$nֻ������ǰ��Ӱ���أ�$n��������ܣ���ʧɫ����ܼ�����������\n"NOR;
             qi_wound = 3000;
             target->add_busy(2);
             if( qi_wound > target->query("qi") && target->query("qi") > 0 )
                qi_wound = target->query("qi")-1;
             target->receive_damage("qi", qi_wound,me);
             target->receive_wound("qi", qi_wound/3,me);
             target->add("neili", -random(400));
            
             me->start_busy(random(2));
        }
        else{
             msg = HIG "ֻ��$n����һ�������һζ�����ǿ�����$N�ġ��̸���ڡ�������\n"NOR;
             if(userp(me))
				me->add("neili",-100);
             me->start_busy(3);
        }
		
        message_vision(msg, me, target);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
		
		if (me->query_temp("pgf/pangen1")) {
			me->add_temp("apply/damage",-(int)me->query_skill("axe",1)/5);
			me->delete_temp("pgf/panggen1");
		}
		
		me->start_perform(3,"�̸�ʽ");
        return 1;
}

string perform_name() {return HIC"�̸�ʽ"NOR;}

int help(object me)
{
   write(WHT"\n�̸���ڸ���֮��"HIC"�̸�ʽ"WHT"����"NOR"\n\n");
   write(@HELP
	�̸���ڸ����Ǵ������Ը����Ĵ�����ɽ���ӹ��óϵĶ����似��
	�丫����Ȼ��ʽƽ������ȴ��ƽ������ʽ���̲�ɱ�����������ͣ���
	��������ɱ�л��ǵ��µ���������������͡��̸�ʽ���Ƿ���һ�С�
	����Է����öԷ��������㣬����������
	
	perform axe.pangen
   
Ҫ��:
	������� 1500 ���ϣ�
	��ǰ���� 500  ���ϣ�
	�̸����� 200  ���ϣ�
	�������� 200  ���ϣ�
	Ǭ��һ�� 200  ���ϣ�
	������� 30   ���ϣ�
	��������Ϊ�̸�������
	��������Ϊ�̸�������
	װ����ͷ��

          
HELP
   );
   return 1;
}
