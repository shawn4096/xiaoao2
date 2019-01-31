// tiao.c ���־�
//Created by Redhat@Sjmud 2009/4/7
//by sohu

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIY"���־�"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int ap, dp;

	int damage;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	weapon = me->query_temp("weapon");
	tweapon = target->query_temp("weapon");

	if( !weapon
	 || weapon->query("skill_type") != "spear"
	 || me->query_skill_mapped("spear") != "huyan-qiang" )
		return notify_fail("�������޷�ʹ�á����־�����\n");


	if((int)me->query_skill("huyan-qiang", 1) < 200 )
		return notify_fail("��ĺ���ǹ����������죬����ʹ�á����־�����\n");

	if((int)me->query("neili") < 2000 )
		return notify_fail("�������������\n");

	if( (int)me->query_str() < 35 )
		return notify_fail("�������������㣬�޷�ʹ�á����־�����\n");

	if( me->query_skill_mapped("spear") != "huyan-qiang")
        return notify_fail("����Ҫ����ǹ��Ϊ����ǹ��������ʹ�á����־�����\n");
	
	if( me->query_temp("hyq/tiao") )
        return notify_fail("�㷽�Ÿ�ʹ�ù������־�����\n");

	if (tweapon)	
		msg = HIG"$N˫����ǹ��������"+weapon->name()+HIR"����$n��"+tweapon->query("name")+HIR"���������Ȼ��ȥ��\n"NOR;
	else 
		msg = HIR"$N˫����ǹ��������"+weapon->name()+HIR"ʩչ�����־�����˳������$n��ǰ�ء�\n"NOR;

	ap = me->query("combat_exp")/10000 * me->query_str(1);
	dp = target->query("combat_exp")/10000 * target->query_str(1);
	me->set_temp("hyq/tiao",1);

	me->add("neili",-200);
	me->add("jingli",-100);
	
	damage=me->query_skill("huyan-qiang",1)+me->query_skill("spear",1);
	damage=damage*me->query_str()/10+random(damage);
	
	if (damage>4000) damage=4000+random(1000);

	if( random(ap + dp) > dp )
	{
		if(tweapon)
		{
			msg += HIY"$nֻ��"+tweapon->name()+HIY"ѹ��ȴԽ��Խ�أ���Ҳ�޷����ƣ�һ�����ղ�ס�����б��������˳�ȥ��\n"NOR;
			target->add_busy(1+random(2));
			tweapon->unequip();
			tweapon->move(environment(me));
		}
		else {
			msg += HIY"$nһʱ���飬Ϊ$N���е�"+weapon->query("name")+HIY"�����У���ʱ����һ��Ѫ������\n"NOR;
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/3,me);			
		}
		
	}
	else {
		
           msg += MAG"$n�����˹�����һ�Զ�ܣ���$N���־��������Σ�\n"NOR;

	}	
	message_vision(msg, me, target);
	call_out("remove_effect",2,me);

	return 1;
}
int remove_effect(object me)
{
	if (!me) return 0;
	me->delete_temp("hyq/tiao");
	return 1;
}

int help(object me)
{
	write(HBMAG"\n����ǹ��֮�����־�����"NOR"\n");
	write(@HELP
	����ǹ���Ǻ��ӼҴ�������Դ��ս��ʵս��ǿ����
	�ڽ����߹ֵ���������ȫ�𷢣��ԳӸ���ʹ��ǹ������
	Ϊ���
	�Է����б�������������ɣ����ޱ�������ֱ�ӱ�Ϊ��
	�̶Է���������ȫ�𷢵Ķ��ž�����

	ָ�perform spear.tiao

Ҫ��	
	��ǰ�������� 2000 ���ϣ�
	����ǹ���ȼ� 200 ���ϣ�
	��Ч�������� 35 ���ϣ�
	����ǹ��Ϊ����ǹ����
	װ��ǹ����
HELP
	);
	return 1;
}