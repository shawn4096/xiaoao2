// by darken@SJ
// Modify By River@SJ 2001.6.18

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int mulan_attack(object me,object target);

string perform_name(){ return HIC"��Ů��"NOR; }

//���ٰ���ɨѩ������¶��ĳرߵ�������ҹ���������������ٳؽ�������
int perform(object me, object target)
{
        string msg;
		int skill = me->query_skill("yunu-jianfa", 1);
        object weapon = me->query_temp("weapon");  
        

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("����Ů����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_skill("force", 1) < 300 )
                return notify_fail("����ڹ����δ�����޷�ʩչ����Ů������\n");
		if( me->query_skill("yunu-xinjing", 1) < 300 )
                return notify_fail("�����Ů�ľ����δ�����޷�ʩչ����Ů������\n");

        if( me->query_skill("dodge",1) < 300 )
                return notify_fail("����Ů�������Ṧ��ϣ�����ʩչ��\n");

        if( me->query_skill("sword",1) < 300 )
                return notify_fail("������������δ�㣬�޷�ʹ�á���Ů������\n");

        if( me->query("neili") < 1000 )
                return notify_fail("�����������ʹ�á���Ů������\n");
		if( me->query("gender") =="����" )
                return notify_fail("�������������޷�ʩչʹ�á���Ů������\n");
        if( me->query("jingli") < 500 )
                return notify_fail("��ľ�������ʹ�á���Ů������\n");
        if (me->query_temp("ynjf/yunu"))
        		return notify_fail("������ʹ�á���Ů������\n");
        
		if( me->query_skill_mapped("force") !="yunu-xinjing")
                return notify_fail("�㼤�����ڹ����ԣ��޷�ʹ�á���Ů����������\n"); 

        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "yunu-jianfa"
		 || me->query_skill_mapped("parry") != "yunu-jianfa" )
                return notify_fail("�������޽�����ʹ�á���Ů��������\n");

        msg = HIW"\n$N���н���ǰͦ���������������ʵ�Ҵ̵�,���һ����Х��ʹ������Ů���ơ�������ֳ����㣬����$n��\n" NOR;
       		
		if (me->query("family/family_name")=="��Ĺ��" 
			&& me->query_per()>28 
			&& me->query_skill("yunu-jianfa",1)>350
			&& me->query("gender")=="Ů��")
		{
			 msg += HIM"\n$N���о�������,��ʽ�����鶯,ʹ��ʱ������������,��̬ƮƮ����,����Ʈ�ݷ���,���˼���̬֮��\n" NOR;
			 if (userp(target))
				target->add_busy(1+random(3));
			 else target->add_busy(3+random(1));
			 skill=skill+me->query_skill("yunu-xinjing",1)/4;
		}
		message_vision(msg , me, target);
        
		me->set_temp("ynjf/yunu",4);

		me->add_temp("apply/attack", skill/3 );
        me->add_temp("apply/damage", skill/4 );
        me->add_temp("apply/sword", skill/5 );
		me->add("neili", -300);
        me->add("jingli", -100);
		
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("ynjf/yunu",-1);
        if (me->is_fighting() && objectp(target))
		{
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			me->add_temp("ynjf/yunu",-1);
			//�⿪ľ����ϣ����öԷ�busy����
			if ( me->query("quest/gumu/ynjf/mulan/pass")
				&& me->query_skill("yunu-jianfa",1)>400
				&& me->query_skill_mapped("dodge")=="yunu-shenfa")
			{
				message_vision(YEL"$N��Ů����ʹ��������ˮ����շת��Ų֮�ʣ���$nǡ������æ����״̬�л��ɳˡ�\n"
				+"�û���ǰ���ݣ�����׼����ľ�����䡹����ʽ��\n"NOR,me,target);
				call_out("mulan_attack",1,me,target);
			}
		}
		if (me->is_fighting() && objectp(target))
		{
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
			me->add_temp("ynjf/yunu",-1);
		}
		if (me->is_fighting() && objectp(target))
		{
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
			me->add_temp("ynjf/yunu",-1);
		}
        me->delete_temp("ynjf/yunu");
		me->add_temp("apply/attack", -skill/3 );
        me->add_temp("apply/damage", -skill/4 );
		me->add_temp("apply/sword", -skill/5 );
		me->start_perform(4,"����Ů����");

        return 1; 
}

int mulan_attack(object me,object target)
{
	object weapon;
	int i,damage;
	if (!me||!objectp(target)) return 0;
	weapon=me->query_temp("weapon");
	if (!weapon) return 0;

	i=(int)me->query_skill("yunu-jianfa",1);
	damage=(i*5+me->query_skill("sword",1))*me->query_per();

	message_vision(HIR"\n$N����ǰԾ������֮�ʣ������е�"+weapon->query("name")+HIR"ͻȻͦ���򱳺�̳�����$n���ؿڣ�\n"NOR, me,target);
    message_vision(HIR"\n������Ů������һ��"HIC"��ľ�����䡹"HIR"������\n"NOR, me,target);
	me->add("neili", -100);
    me->add("jingli",-50);
	
	if (random(me->query("combat_exp"))>target->query("combat_exp")/2
		|| random(me->query_dex(1))>target->query_dex(1)/2)
    {  
	    message_vision(HIY"\n\n$n��׷��֮�ʣ���$N���С�ľ�����䡹һ�������ؿڣ���Ѫ�Ž���\n"NOR,me,target);
		if (userp(target))
		{		
			target->receive_damage("qi",3000+random(1000),me);
			target->receive_wound("qi",1000+random(500),me);
		}
		else {
			target->receive_damage("qi",4000+random(2000),me);
			target->receive_wound("qi",2000+random(1000),me);
		}
		target->apply_condition("no_exert",1);
		if (!userp(target)) target->add_busy(2);
		
		me->add_temp("apply/damage",i);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if (me->query_skill("yunu-jianfa",1)>200 && me->is_fighting())
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/damage",-i);
	            	
    }else
	{
		message_vision(HIC"\n\n$n���¼�æ���ˣ�����������У�����һ���亹��\n"NOR,me,target);
		me->add_busy(1);
	}
	return 1;	

}

int help(object me)
{
        write(HIG"\n��Ů����֮"+HIW"����Ů������"NOR"\n\n");
        write(@HELP
	��Ů�������ǹ�Ĺ�ɾ�������,���о�������,��ʽ�����鶯,
	ʹ��ʱ������������,��̬ƮƮ����,��������Ʈ�ݷ���,����
	�˼���ȡʤ.
	��Ů���ǽ������н�Ϊͻ�������м�������������Ĺ����ʹ��
	�ǳ�����Ҫ�������似��Ů��ʹ�ñ����������Ե����ơ�
	��ʾ������Ե�ɺ������Խϸߣ����Խ����к�ľ��������Ч��
	�ϣ��γɸ�ǿ�Ĺ���Ч��,��Ů������400�����ϡ�
	��Ů���Դ����м��������ã���Ĺ�����мǡ�
	
	perform sword.yunu

Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	��Ů�����ȼ� 300 ���ϣ�
	��Ů�ľ��ȼ� 300 ���ϣ�
	���������ȼ� 300 ���ϣ�
	�����Ṧ�ȼ� 300 ���ϣ�
	��������Ϊ��Ů������
	�����м�Ϊ��Ů������
	�����ڹ�Ϊ��Ů�ľ���
	���ֳֽ���������
HELP
        );
        return 1;
}
