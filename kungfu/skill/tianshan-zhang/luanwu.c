//By lsxk@hsbbs 2007/10/19
//Ⱥħ����

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name(){ return HIB"Ⱥħ"HIR"����"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i;
    
    if( !target ) target = offensive_target(me);
     
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("Ⱥħ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if(me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("����ڹ����ǻ����󷢣��޷�ʹ��Ⱥħ���裡\n");
    if( (int)me->query_skill("huagong-dafa", 1) < 160 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ��Ⱥħ���裡\n");
    if( (int)me->query_skill("tianshan-zhang", 1) < 160 ) 
                return notify_fail("�����ɽ�ȷ���δ���ɣ�����ʹ��Ⱥħ���裡\n");
    if((int)me->query_skill("staff", 1) < 160 )
                return notify_fail("��Ļ����ȷ�������죬������ʹ��Ⱥħ���衣\n");
    if((int)me->query_skill("poison", 1) < 100 )
                return notify_fail("��Ķ���������죬������ʹ��Ⱥħ���衣\n");
    if((int)me->query_dex(1) < 30 )
                return notify_fail("��������������ɣ�����ʹ��Ⱥħ���衣\n");
	if (me->query_skill_mapped("claw") != "sanyin-zhua"
        || me->query_skill_prepared("claw") != "sanyin-zhua")
                return notify_fail("���輤����׼���������צ�������޷�ʹ��Ⱥħ���衣\n");
    if (!objectp(weapon = me->query_temp("weapon")) 
		|| weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "tianshan-zhang"
        || me->query_skill_mapped("parry") != "tianshan-zhang")
                return notify_fail("������ʹ����Ⱥħ����ô��\n");
                
    if((int)me->query("max_neili") < 1500 )
                return notify_fail("���������Ϊ����������ʹ��Ⱥħ���裡\n");
    if((int)me->query("neili") < 500 )
                return notify_fail("�������������㣬����ʹ��Ⱥħ���裡\n");

        message_vision(HIB"\n$NͻȻһ���ֽУ��Ų�Ʈ��������˲����Ȼ��$n�ӳ����У���������֮����\n"NOR,me,target);

       
        i = (int)me->query_skill("tianshan-zhang",1);
		if (me->query_skill("huagong-dafa",1)>350)
		    i += (int)me->query_skill("huagong-dafa",1)/5;
        if (!userp(target))
			i += (int)me->query_skill("huagong-dafa",1)/5;
		me->add("neili", -300);
        me->add_temp("apply/attack",  i/2);
        me->add_temp("apply/damage",  i/5);
        me->set_temp("tsz/lw",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<250)?1:3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<350)?1:3);       
       // COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	
     if (me->is_fighting(target))
	 { 
		 weapon->unequip(); 
	     me->add_temp("apply/claw", i);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
		 me->add_temp("apply/claw", -i);
         weapon->wield();
	 }
	 if (me->is_fighting(target))
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack",  -i/2);
        me->add_temp("apply/damage",  -i/5);
        me->delete_temp("tsz/lw");
    me->start_busy(1);
    target->start_busy(1);
	me->start_perform(4+random(2),"��Ⱥħ���衹");
    return 1;
}

int help(object me)
{
   write(WHT"\n��ɽ�ȷ���"HIB"Ⱥħ"HIR"����"WHT"����"NOR"\n");
   write(@HELP
	��ɽ�ȷ���λ�������ɳ��������似����������
	���޵����Դ˺��н���������Ϊ��ɽ�ȷ��л���
	���������ܵ��˺�ɨһƬ��������
	
	perform staff.luanwu
  
Ҫ��
	�������Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	��ɽ�ȷ��ȼ� 160 ���ϣ�
	�����󷨵ȼ� 160 ���ϣ�
	������Ҫ�� 30 ���ϣ�
	�����ȼ�Ҫ�� 100 ���ϣ�
	�����м�Ϊ��ɽ�ȷ�,
	�����ȷ�Ϊ��ɽ�ȷ���
	�����ұ�צ��Ϊ�������צ��
	�������������
	350���Ծ��450����΢��ǿ��

HELP
   );
   return 1;
}
