// duanyun.c �ͱڶ���
// by sohu@xojh 2014

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage,skill;
        string msg;
		object weapon;
		skill=me->query_skill("liangyi-jian",1);
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
			return notify_fail("���ͱڶ��ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "sword")
            return notify_fail("��ʲô��Ц��ûװ��������ʹ�����ɷ��١���\n");
                
		if( (int)me->query_skill("liangyi-jian",1)<350)
			return notify_fail("��������ǽ���������죬����ʹ�á��ͱڶ��ơ���\n");
		if( (int)me->query_skill("xuantian-wuji",1)<350)
			return notify_fail("��������޼���������񣬲���ʹ�á��ͱڶ��ơ���\n"); 
		if( (int)me->query_skill("sword",1)<350)
			return notify_fail("��Ļ�������������񣬲���ʹ�á��ͱڶ��ơ���\n"); 
        if( (int)me->query("max_neili",1)<2500)
			return notify_fail("�������������̫��������ʹ�á��ͱڶ��ơ���\n");                
		if( (int)me->query("neili",1)<1000)
			return notify_fail("�����ڵ�ǰ����̫��������ʹ�á��ͱڶ��ơ���\n");
		if( (int)me->query("jingli",1)<1000)
			return notify_fail("�����ڵ�ǰ����̫��������ʹ�á��ͱڶ��ơ���\n");
		if( (int)me->query_dex(1)<50)
			return notify_fail("��������Ч��̫��������ʹ�á��ͱڶ��ơ���\n");	
	                        
		message_vision(HIY "$N�����޷��Զ�������бб�̳�һ��,ʹ�����������ǽ����е���ɽ�������ͱڶ��ơ���\n"
			HIG "ɲ�Ǽ����ذ�����ɳ��ʯ��������Ӱ��$n��ȫ��Ҫ����̣��򿳣�������ȥ��\n" NOR,me,target);
		
		if (userp(target)) 
			skill=skill+me->query_skill("xuantian-wuji",1)/3;
		
		me->add_temp("apply/attack",skill/3);
		me->add_temp("apply/damage",skill/5);
		me->set_temp("lyj/duanyun",4);
		if( (int)me->query_skill("art", 1) >= 200)
		{
			if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(target)?1:3);
			
			if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(target)?1:3);
			if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
			if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
			me->add("neili", -200);
		}
        if (random(me->query("neili")) > target->query("neili")/3 
			||random(me->query_dex())>target->query_dex()/2 )
		{
			               
			message_vision(HIC "\n$N���С��ͱڶ��ơ������ֱ䣬����ʽ��������գ���Ȼһ��������Ѹ�����ס�\n" NOR,me,target);
			damage= skill+(int)me->query_skill("sword",1)+(int)me->query_skill("xuantian-wuji",1)+(int)me->query_skill("liangyi-jue",1);
			damage = damage*3 + random(damage);                
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/2,me);
			me->add("neili",-100);
			msg=HIY"������������Ϊ�������з�ʩ����ʱ����������\n"NOR;
			if( damage < 2000 ) 
				msg += HIY"\n���$n��$N������һ�����ƺ�һ������ʱ��Ѫ��ע��\n"NOR;
			else if( damage < 3000 ) msg += HIY"���$n��$N������������������һ������������\n"NOR;
			else if( damage < 5000 ) msg += RED"���$n��$N���ص����������������ܵ������׻�һ�㣬��������������\n"NOR;
			
			else msg += HIR"���$n��$N�ġ��ͱڶ��ơ���͸ǰ�ģ���ǰһ�ڣ��������ɳ�������\n"NOR;
			
			message_vision(msg, me, target);
			
			me->add_temp("apply/damage",skill/6);
			me->add_temp("apply/sword",skill/5);
			
			COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
			if (me->query("quest/kl/lyj/duanyun/pass")&&me->query_skill("liangyi-jian",1)>400)
			{
				message_vision(HIM "\n$N������ǽ������龫�裬���ͱڶ��ơ�����δ�������ǽ��������ᣬ��Ϊ����ĽǶ�һ���̳���\n" NOR,me,target);
				target->set_temp("must_be_hit",1);
				me->add_temp("apply/damage",skill/6);
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
				me->add_temp("apply/damage",-skill/6);
				target->delete_temp("must_be_hit");
			}
			me->add_temp("apply/damage",-skill/6);
			me->add_temp("apply/sword",-skill/5);

			
		}
		else
		{
			me->start_busy(3);
            msg = CYN"����$p������$P����ͼ����û���ϵ���\n"NOR;
			message_vision(msg, me, target);
		}
		me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/5);
		me->delete_temp("lyj/duanyun");	
		me->start_perform(4,"�ͱڶ���");
		return 1;
}

string perform_name() {return HIC"�ͱڶ���"NOR;}

int help(object me)
{
    write(WHT"\n���ǽ�����"HIC"�ͱڶ���"WHT"����"NOR"\n");
    write(@HELP
	���ǽ������������ɾ���������������ʥ������Դ�
	������ɨ�������ۡ����������ִ�ս��һս������ƾ
	��ľ��Ǵ˽��������ǽ��������ڵ������ǽ�������
	������Ѹ�ݣ�������ʤ����ȴ�������鶯��䷢�ӵ�
	���¡��������Ṧ�������ǽ�������������һ��¥
	ע�⣺�������г��ϴ����ܴ��а��أ��������ֲ���
	С��Ծ��
    
	ָ�perform sword.duanyun
	
Ҫ��
	�����޼��ȼ� 350 �����ϣ�
	���ǽ����ȼ� 350 �����ϣ�
	��Ч���ȼ� 50    ���ϣ�
	���������ȼ� 350 �����ϣ�
	�������Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�����黭Ҫ�� 200 ���ϣ�
	���ֳֽ���������    

HELP
	);
	return 1;
}
