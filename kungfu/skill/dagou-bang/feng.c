// chan.c �򹷰���--���־�
// Modify by looklove@SJ 3/16/2001
// Update by lsxk@hsbbs 2007/7/2
// ��λ�ɷ����似���������������似

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HBMAG+HIW"���־�"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int mexp, texp, mlvl, tlvl, b;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	weapon = me->query_temp("weapon");
	tweapon = target->query_temp("weapon");

	if( !objectp(weapon)
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("parry") != "dagou-bang"
	 || me->query_skill_mapped("stick") != "dagou-bang" )
		return notify_fail("�������޷�ʹ�ô򹷰������־�����\n");

	mexp = (int)me->query("combat_exp")/100000;
	texp = (int)target->query("combat_exp")/100000;
	mlvl = (int)me->query_skill("dagou-bang",1);
	tlvl = (int)target->query_skill("dodge",1);

	b = me->query_skill("bangjue",1);

	if( mlvl < 400 )
		return notify_fail("��Ĵ򹷰�����������죬����ʹ�á����־�����\n");
	if( b < 150 )
		return notify_fail("��Ĵ򹷰���������죬�޷�ʹ�������־�����\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 400 )
		return notify_fail("��Ļ��������������㣬�޷�ʹ�������־�����\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("��������������޷�ʹ�������־�����\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("��ľ�������������ʹ�������־�����\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("�����������֧����ʹ�á����־�����\n");

	if( me->query_temp("dgb/feng") )
		return notify_fail("������ʩչ�����־�����\n");	
	if( me->query_condition("no_perform") )
		return notify_fail("��Ķ����Ѿ�Ϊ�㡸���־�������ס����ʽ���ŵ������ɡ�\n");	


	message_vision( HBYEL"$Nʹ���򹷰����ġ����־���������"+weapon->query("name")+HBYEL"���һ�Ű�Ӱ��������ס�Ż���\n"NOR,me);
	
	if( tweapon )
		message_vision(HBGRN"\nֻ��$n��"+tweapon->query("name")+HBGRN"�ӵ�����"+weapon->query("name")+HBGRN"�͸��򶫣�"+tweapon->query("name")+HBGRN"������"+weapon->query("name")+HBGRN"�浽����\n"NOR,me,target);
	else
		message_vision(HBGRN"\nֻ��"+weapon->query("name")+HBGRN"��Ӱ���Σ����в���$n�����Ѩ��$n���ܵ��޴����в���򹷰����澫���ޱȡ�\n"NOR,me,target);
	
	//message("wizard", HIG"���־���busy�غ���"+busy+"��ʹ����EXP"+mexp+"������EXP"+texp+", "+x+","+y+"��\n"NOR, environment(me), me);
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

//����������
	
	if (random(mlvl)>tlvl/2
		||random(me->query_int(1))>target->query_int(1)/2)
	{
	
		if (me->query("env/�򹷰����־�")=="����")
		{
			if (!me->query_temp("dgb/feng"))
			{
				message_vision(HIG "\n\n$Nʩչ�Ĵ򹷰�������Ϊ����һ���������ɵ�"+weapon->query("name")+HIG"�Կ�ʹ��Բת���硣$nһʱ��Ȼ���Թ��롣\n" NOR,me,target);

				me->add_temp("apply/parry",mlvl/3);
				me->add_temp("apply/defense",mlvl/3);
				me->add_temp("apply/dodge",mlvl/3);
				me->add_temp("apply/armor",mlvl/3);
				me->set_temp("dgb/feng",mlvl);
				call_out("check_fight",1,me,mlvl/20);
			}

		}
		if (me->query("env/�򹷰����־�")=="����"
			&&me->query("quest/gb/dgb/wugou/pass"))
		{
		
			if (!me->query_temp("dgb/feng"))
			{
				message_vision(HIM "\n\n$n���˾����$N���е�"+weapon->query("name")+HIM"��֪$N��һ��ʹ���ǡ��򹷰������еġ��⡱�־�������ȫ�Ǻ�ʹ��\n"+
				"������������һ��"+weapon->query("name")+HIM"����һƬ��ǽ���������ţ�ֻҪ���˲�̤��һ�����Ǿ��ް�����ʩ���������ܷ���\n"NOR,me,target);

				if (me->is_fighting()
					&&objectp(target))
				{
					message_vision(HIW "$Nʹ�����⡱�־�����ӰƮƮ���Զ�ָ��$n����ҪѨ����ʱ��$n��ǰ����֮�ؾ�����ס�ˡ�\n" NOR,me,target);
					if (userp(target)) target->add_condition("no_perform",b/100);
					else target->add_condition("no_perform",b/50);
					//target->set_temp("dgb/feng",mlvl);
				}
			}

		}

	}		
	else {
		message_vision(HIW "$n��������������"+weapon->query("name")+HIW"��һ�ƣ����־�˲���߽⡣\n" NOR,me,target);
		me->start_busy(1+random(2));
	}
	if (me->query_skill("dagou-bang",1)>550 && !me->query("quest/gb/dgb/bangjue/pass"))
		me->start_perform(1, "���־�");

	me->add("neili", -200);
	me->add("jingli", -60);
	return 1;
}

void check_fight(object me,int count)
{
	object weapon;
	int mlvl;
	if (!me) return;	
	if (!me->query_temp("dgb/feng")) return;
	mlvl=me->query_temp("dgb/feng");
	weapon=me->query_temp("weapon");
	if( !me->is_fighting()
	 || !weapon
	 || weapon->query("skill_type")!="stick"
	 || count<0
	 || me->query_skill_mapped("parry") != "dagou-bang"
	 || me->query_skill_mapped("stick") != "dagou-bang")
	{      
	        
			me->add_temp("apply/parry",-mlvl/3);
			me->add_temp("apply/defense",-mlvl/3);
			me->add_temp("apply/dodge",-mlvl/3);
			me->add_temp("apply/armor",-mlvl/3);
			me->delete_temp("dgb/feng");
			
			message_vision(HBYEL "$N����һ��������ֹͣ�˴򹷰��������־��������������İ�Ӱ����ʧ��\n" NOR,me);
			if (me->query_skill("dagou-bang",1)<450) me->start_perform(1, "���־�");

			return;
	}

	call_out("check_fight", 1, me,count--);
}
int help(object me)
{
	write(HBMAG"\n�򹷰������־�����"NOR"\n");
	write(@HELP
	������߹��Դ򹷰�֮�������ɣ�������������
	Ϊؤ�ﲻ��֮�أ���򹷰������־��������Ǻ��߹�
	�����ʹ��һ�г���������һ��ʩչ��������������
	���ŷ�ס��ʹ�öԷ���ʽ���Թ��룬�Է���ǿ�й���
	��ʱ���ٴ򹷰��ķ��������Ծ��ƶ��Ĳ������š�
	�����书��˫�����顢�似�ȼ���˫�����Ծ��й���
	һ���Է����⣬���ή����Ӧ�Ĺ�����550������
	
	ע�⣺���־������ֹ�Ч�����غͷ���������ͨ����
		Ч��������ɷ��־���ʹ�á������Ǵ��������
		�����������������ǶԶԷ����з��й�Ч������
		��Ч���ǽ⿪�򹷰������Σ�����ʽ�Ϳھ��ں�
		�󷽿�ʹ�á�
		
		set �򹷰����־� ����
		set �򹷰����־� ���� 
			
	ָ�perform stick.feng
	
Ҫ��
	����������� 2000 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	�򹷰����ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	�򹷰����ȼ� 150 ���ϣ�
	�����м�Ϊ�򹷰���
HELP
	);
	return 1;
}
