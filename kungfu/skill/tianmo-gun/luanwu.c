//Ⱥħ����
//xjqx 2008/12/30

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name(){ return HIG"Ⱥħ����"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i;
    
    if( !target ) target = offensive_target(me);
     
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("Ⱥħ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if (me->query_skill_mapped("force") != "tianmo-gong" 
		&& me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("����ʹ�õ������ڹ����ԡ�\n");  
    if(me->query_skill("xixing-dafa", 1)<250)
       if(me->query_skill("tianmo-gong", 1) < 250)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ������Ⱥħ���衹��\n");   
    if( (int)me->query_skill("tianmo-gun", 1) < 250 ) 
                return notify_fail("���������ħ����δ���ɣ�����ʹ��Ⱥħ���裡\n");
    if((int)me->query_skill("club", 1) < 250 )
                return notify_fail("��Ļ�������������죬������ʹ��Ⱥħ���衣\n");
    if((int)me->query_dex()<35 )
                return notify_fail("�������������������ʹ��Ⱥħ���衣\n");
    if (!objectp(weapon = me->query_temp("weapon")) 
		|| weapon->query("skill_type") != "club"
        || me->query_skill_mapped("club") != "tianmo-gun"
        || me->query_skill_mapped("parry") != "tianmo-gun")
                return notify_fail("������ʹ����Ⱥħ����ô��\n");
                
    if((int)me->query("max_neili") < 1200 )
                return notify_fail("���������Ϊ����������ʹ��Ⱥħ���裡\n");
    if((int)me->query("neili") < 800 )
                return notify_fail("�������������㣬����ʹ��Ⱥħ���裡\n");

        message_vision(HIG"\n$N������"+weapon->name()+HIG+"�����������趯�����������쳣����$n������$N���ҹ�֮�ڣ�����������С�\n"NOR, me, target);

        i = (int)me->query_skill("tianmo-gun",1);
        me->add("neili", -200);
        me->add_temp("apply/attack",  i/3);
        me->add_temp("apply/damage",  i/5);
        me->set_temp("tmg/lw",1);
		target->add_busy(1);
        if (objectp(target)&&me->is_fighting(target))
       		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<450)?1:3);
        if (objectp(target)&&me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        if (objectp(target)&&me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<450)?1:3);
		if (objectp(target)&&me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack",  -i/3);
        me->add_temp("apply/damage",  -i/5);
        me->delete_temp("tmg/lw");
        me->start_perform(3+random(2),"��Ⱥħ���衹");

        me->start_busy(3);
        target->start_busy(1);
        return 1;
}

int help(object me)
{
   write(WHT"\n��ħ������"HIG"Ⱥħ����"WHT"����"NOR"\n");
   write(@HELP
	��ħ������������̸߼��书�������ϴ�ʮ����ħ�ų���
	�ų˷�����������ʮ����Χ����ɽ�����λ�������䲻
	���������������书�зǳ���Ҫ���书ʧ�������ܽ⿪��
	�����⣬��ħ������������һ��̨�ס�
	 
	ָ�perform club.luanwu

Ҫ��
	����������� 1200 ���ϣ�
	��ǰ�������� 800 ���ϣ�
	������ħ���ȼ� 250 ���ϣ�
	���Ǵ󷨵ȼ� 250 ���ϣ�
	���������� 35 ���ϣ�
	�����м�Ϊ������ħ����

HELP
   );
   return 1;
}
