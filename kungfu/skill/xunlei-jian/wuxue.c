// wuxue.c Ѹ�׽� perform һ����Ѫ
// cck 13/6/97
//edit by sohu
//Դ�Է�������ʽ
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int remove_wuxue(object target);

int perform(object me, object target)
{
        object weapon;
        string msg;
        string msg1;
	
		int skill,damage;
		skill=me->query_skill("xunlei-jian",1);
		damage=skill+me->query_skill("xuantian-wuji",1)+me->query_skill("jingmai-xue",1);
		damage=damage*3+random(damage);

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��һ����Ѫ��ֻ����ս���жԶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( (int)me->query_skill("xunlei-jian", 1) < 350 )
                return notify_fail("���Ѹ�׽���������죬����ʹ�á�һ����Ѫ����\n");

		if(!me->query("quest/kl/xlj/wuxue/pass"))
                return notify_fail("����δѧ�ᡸһ����Ѫ��������\n");

		if( me->query_skill_mapped("sword")!="xunlei-jian" )
			//||me->query_skill_mapped("parry")!="xunlei-jian" 
                return notify_fail("��û�ܼ���Ѹ�׽�������ʹ�á�һ����Ѫ����\n");
		if( (int)me->query_con() < 50 )
                return notify_fail("��һ����Ѫ����Ҫ�߸��ǣ���ĺ�����ǲ���50������ʹ�á�һ����Ѫ����\n");

        if( (int)me->query("neili", 1) < 1500 )
                return notify_fail("����������̫��������ʹ�á�һ����Ѫ����\n");
        if( (int)me->query("jingli", 1) < 1000 )
                return notify_fail("�����ھ���̫��������ʹ�á�һ����Ѫ����\n");         
             
		if( target->query_temp("xlj/wuxue") )
                return notify_fail("�Է��Ѿ�������ġ�һ����Ѫ����ʽ��\n");
        msg = HIC "$N������ת���⣬��͸���⣬һ����������ƶ�ʱ����$n�������Ѩ��ʹ��Ѹ�׽�"HIR"��һ����Ѫ��"HIC"�ľ�����\n" NOR;
//        msg1 = BBLU+HIY "$N��Хһ���������ָ,���ƹ��쵫ȴ�����ޱȡ�\n" NOR;
        message_vision(msg, me, target);
		if (random(me->query_skill("sword",1))>target->query_skill("parry",1)/2
		||random(me->query_skill("force",1))>target->query_skill("force",1)/2)
		{
			message_vision(HIR "$nһʱ���⣬Ϊ$N����͸����������ס����ҪѨ����ʱ����������\n" NOR,me,target);
			if (!random(3))
			{
				target->apply_condition("no_perform",1);
			}else target->apply_condition("no_exert",1);

			target->add_busy(2+random(2));
			target->apply_condition("neishang",10+random(4));
			if (random(me->query_con(1))>target->query_con(1)/3)
			{
				message_vision(RED "$N��һ����$n��ɼ���İ��ˣ����˿����������������͸��������$n�ش���\n" NOR,me,target);
				target->receive_wound("qi",damage,me);
				//target->receive_damage("qi",damage*2,me);
				if (wizardp(me))
					write("damage="+damage);
			}
			me->add_temp("apply/sword",skill/3);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			me->add_temp("apply/sword",-skill/3);
			target->set_temp("xlj/wuxue",skill);
			if (objectp(target))
				call_out("remove_wuxue",10-(int)skill/150,target);

		}else me->start_busy(1);	
		
        me->add("neili", -250);
        me->add("jingli", -150);

        return 1;
}
int remove_wuxue(object target)
{
	if (!objectp(target)) return 1;
		target->delete_temp("xlj/wuxue");	
	return 1;
}

string perform_name() {return RED"һ����Ѫ"NOR;}

int help(object me)
{
    write(HIY"\nѸ�׽�����һ����Ѫ����"NOR"\n");
    write(@HELP
	һ����Ѫ���������ɸ��ַ��������ž���������ǿ����ڹ�����
	��ʹ�ڽ���֮�У���͸���䣬�����������Է��������������
	�κ��˺���������ȴ���ܵ��ش����䲻����������Ҳ��У��˵�
	�Ǻ����ľ��У�������Ҫ����������̡�
	���������ڻ����ڹ���Ϊ������������Ϊ�йأ�������ǲ��ͻ�
	������ֶԶԷ��׺ݵ�ɱ�С�����Խ����񣬳���Ƶ��Խ�ߡ�

	ָ�perform wuxue
	
Ҫ��
	�����޼��ȼ� 350 �����ϣ�
	Ѹ�׽����ȼ� 350 �����ϣ�
	���������ȼ� 350 �����ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ��Ч���� 50 ���ϣ�
	��������ΪѸ�׽���
	�ڹ����ޣ�
	���ֳֽ���������    

HELP
	);
	return 1;
}

