// feihua.c ���ɻ�
// cre by sohu@xojh 2014
// ���ݽ�ӹ�����ı�
// ���к��䣬����бб��ʹ��һ�ס����ɻ�������������һ·���ߵ�ȫ��б�ƣ�Ʈ�����ף����߰���б��֮�У�ż����Ю��һ�����ƣ�
#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return HIG"���ɻ�"NOR; }


int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time, lvl;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                 return notify_fail("�����ɻ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if((int)me->query_skill("liangyi-jian",1) < 450 )
				return notify_fail("������ǽ������������ʹ���������ɻ�����\n");
        if((int)me->query_skill("xuantian-wuji",1) < 450 )
                return notify_fail("��������޼������������ʹ���������ɻ�����\n");
        if( me->query_skill_mapped("sword") != "liangyi-jian"
			|| me->query_skill_mapped("parry") != "liangyi-jian" )
                return notify_fail("������û�������ǽ����޷�ʹ��������У�\n");
        if((string)me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("�㲻�������޼��ڹ�֧�����޷�ʹ��������еģ�\n");
        
        if(me->query_temp("lyj/feihua") )
                return notify_fail("�������Ѿ��������ʹ���ˡ����ɻ�����\n");
      
        if( me->query("jingli", 1) < 1000 )
                return notify_fail("��ĵ�ǰ������Ϊ����ʹ�á����ɻ�����\n");
        if( me->query_dex( ) < 60 )
				return notify_fail("��ĺ�������Ϊ����ʹ�á����ɻ�����\n");
        if((int)me->query("neili")<1500)
                return notify_fail("�������������\n"); 
        attack_time = random((int)me->query_skill("liangyi-jian",1) / 25)+1;
       
		if(attack_time < 3)
               attack_time = 3;
        if(attack_time > 7)  attack_time = 7;
        
		msg = HIY "$N����"+weapon->name()+HIY"���к��䣬����бб��ʹ��һ�ס����ɻ�������������һ·���ߵ�ȫ��б�ƣ�\n"+
			"\nƮ�����ף����߰���б��֮�У�ż����Ю��һ�����ƣ�ҡ����ɣ�ҡҷ�绨��\n"NOR;
     
		
		message_vision(msg, me, target);
        lvl = ((me->query_skill("liangyi-jian", 1) + me->query_skill("xuantian-wuji", 1)))/ 6;
        lvl=lvl/3;

		me->set_temp("lyj/feihua", lvl);
        me->add_temp("apply/dexerity", lvl);
        me->add_temp("apply/damage", lvl);
        me->add_temp("apply/attack", lvl);
        me->add_temp("apply/sword", lvl/2);

		for(i = 0; i < 2; i++)
			if (me->is_fighting()&&objectp(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
		//����������
		if (me->is_fighting()&&objectp(target))
		{
			    me->set_temp("lyj/feihua1",1);
				me->add_temp("apply/damage",lvl/4);
				if (userp(target))
					target->add_busy(1);
				else target->add_busy(4);
				message_vision(HBWHT+HIY"$N��Ȼʹ��һ�����ǽ����У�����ͻأ��$nһʱ���飬��ʱ��Щ��æ���ң�\n"NOR,me,target);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->delete_temp("lyj/feihua1");
				me->add_temp("apply/damage",-lvl/4);
		}
		//������ ��б��		
		if (me->is_fighting()&&objectp(target))				
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);	
		//������ ��б��	
		if (me->is_fighting()&&objectp(target))				
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);						
		//������ ����
		if (me->is_fighting()&&objectp(target))
		{
			    me->set_temp("lyj/feihua1",1);
				me->add_temp("apply/damage",lvl/4);
				me->add_temp("apply/sword",lvl/4);
				message_vision(HIR"$N��ʽ����Ϊ���ǽ����У�$nһʱ���飬Ϊ$N��������\n"NOR,me,target);
				target->receive_damage("qi",4000+random(3000),me);
				if (me->query("quest/kl/lyj/feihua/pass")
					&& me->query_skill_mapped("sword")=="liangyi-jian")
				{
					message_vision(HBRED+HIW"$Nһ����ʵ�˺󣬽�������ĺ󾢷����������������£�˲��������$n�Ĵ��Ѩ������Ѩ���͹�Ѩ��\n"NOR,me,target);
					message_vision(RED"$n����������ʱ���ƣ��޷��������У�\n"NOR,me,target);

					target->receive_damage("qi",random(5000),me);
					target->receive_wound("qi",random(2000),me);
					target->add_busy(2);
					target->apply_condition("no_enable",2);
				}
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->delete_temp("lyj/feihua1");
				me->add_temp("apply/damage",-lvl/4);
				me->add_temp("apply/sword",-lvl/4);
		}
		//�ڰ���
	//	if (me->is_fighting()&& objectp(target))				
	//			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);						

		me->add_temp("apply/damage", -lvl);
        me->add_temp("apply/attack", -lvl);
        me->add_temp("apply/dexerity", -lvl);
		me->add_temp("apply/sword", -lvl/2);

		me->delete_temp("lyj/feihua");

        me->add("neili", -300);
        me->add("jingli", -80);
	
		message_vision(HIY"$N�Ĺ��ƽ������������������������˿�����\n"NOR,me);		
		me->start_perform(6,"�����ɻ���");
		me->add_busy(1);
        return 1;
}

int help(object me)
{
    write(WHT"\n���ǽ�����"HIG"���ɻ�"WHT"����"NOR"\n");
    write(@HELP
	���ǽ������������ɾ���������������ʥ������Դ�
	������ɨ�������ۡ����������ִ�ս��һս������ƾ
	��ľ��Ǵ˽��������ǽ��������ڵ������ǽ�������
	������Ѹ�ݣ�������ʤ����ȴ�������鶯��䷢�ӵ�
	�������Ṧ�ã������ǽ�������������һ��¥��
	���ɻ��������ǽ��бȽ�����Ľ���������ȫ��б
	�ƣ����߰���б��֮�У�ż����Ю��һ�����ƣ����
	������׽�����⿪��������󣬴��з�Ծ��

	ָ�perform sword.feihua
	
Ҫ��
	�����޼��ȼ� 450 �����ϣ�
	���ǽ����ȼ� 450 �����ϣ�
	��Ч���ȼ� 60    ���ϣ�
	���������ȼ� 300 �����ϣ�
	�������Ҫ�� 5000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	���ֳֽ���������    

HELP
	);
	return 1;
}
