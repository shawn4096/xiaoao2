// lianhualuo.c ������ by sohu@xojh 2014 
// ��λ��ؤ��������������䣬���������Ĳ����Ϳ��������дʣ�ǣ�ƶ���
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIM"������"NOR; }

string *color = ({ RED+"",GRN+"",YEL+"",BLU+"",MAG+"",CYN+"",
HIR+"",HIG+"",HIY+"",HIB+"",HIM+"",});

int perform(object me, object target)
{
	int tbusy, i, j;
	string msg;
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 ||!target->is_character()
	 ||!me->is_fighting(target) )
		return notify_fail("�������䡹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("�������䡹ֻ�ܿ���ʹ�á�\n");

	if( me->query_skill_prepared("strike") != "lianhua-zhang"
	 || me->query_skill_mapped("strike") != "lianhua-zhang"
	 || me->query_skill_mapped("parry") != "lianhua-zhang" )
		return notify_fail("������������Ʋ��ܳ����湦�� \n");

	if( me->query_skill("huntian-qigong",1) < 260 )
		return notify_fail("��Ļ�������������������ʹ�á������䡹!\n");

	if( me->query_skill("lianhua-zhang",1) < 260 )
		return notify_fail("�����������Ϊ������������ʹ���������䡹����!\n");

	if( me->query_skill_mapped("force") != "huntian-qigong" )
		return notify_fail("����ڹ����ԡ�\n");

	if( me->query("max_neili") < 1800 )
		return notify_fail("���������Ϊ��Ƿ���\n");
    
	if( me->query_skill_mapped("dodge") !="xiaoyaoyou" )
		return notify_fail("����δ������ң�Σ�ʹ�ò����������䡹��\n");
	if( me->query("neili") < 500 )
		return notify_fail("��������������, ����ʹ�á������䡹! \n");

	if( me->query("jingli") < 500 )
		return notify_fail("�����ھ�������, ����ʹ�á������䡹! \n");

	if( target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

	if( me->query_temp("lhz/lhl") )
		return notify_fail("����������ʹ�á������䡹������������Ѫ��ӿ�����ڻ�����ʹ�á������䡹! \n");
	
	message_vision(HIG"\n$N��Ȼ������ң�Σ����¶�ʱ���Ѹ���ޱ�����������ƮƮ���ж���硣\n"
                       +"$nһʱ���죬$N˫������ǰһ����Ȼ��˫���ⷭ���ֻ�������ԲȦ��ͻȻ��Ϯ��$n��\n"NOR,me,target);
	

	//me->start_perform(3, "������");
	me->set_temp("lhz/lhl",1);
	tbusy = (int)me->query_skill("lianhua-zhang",1) / 100 ;
	if( tbusy < 2 ) tbusy = 2;
	if( tbusy > 3 ) tbusy = 3+random(2);


	i= me->query("combat_exp")/100000;
	j=target->query("combat_exp")/100000;
	if( random(i + j) > j 
		||random(me->query_dex(1))>target->query_dex(1)/2)
	{

		if( !userp(target) ) target->add_busy(tbusy);
		else target->add_busy(1+random(2));
		
		message_vision(HIM "����$N���º���һ��������һ�ǡ�ǧҶ����������ǰ��������$n��ǰ����������㱬��������\n"+
		"ͬʱ��$Nһ����Ĳ�������������������ˮ��������������ɫɫ�ʣ�Цɷ�Ƕ�����ү�������볪����������\n"+
		"$nһʱ���죬��$N����Ӱ�죬һ���ĸ����꣬������ʱΪ���Ʒ����ơ�\n"NOR,me,target);
		me->add("neili",-200);
		me->add("jingli",-50);
		//me->start_perform(2, "������");
		target->receive_damage("jing",100+random(1000),me);
		me->delete_temp("lhz/lhl");
		return 1;
	}
	else {
		message_vision(HIM"$n�䱻�⾫���һ���������������������ʽ�·�ȴ˿�����ң���Ҳ��ǿ����������\n" NOR,me,target);
		if( me->is_fighting(target) && random(i) > j/3
			||random(me->query_int(1))>target->query_int(1)/2 ) {
			message_vision(HIG"ֻ�Ǳ������Ʒ����ˣ�$N����һ����������ǰ�ƽ����������������ơ�����\n" NOR,me,target);
			//message_vision(msg, me, target);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="Ů��"?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="Ů��"?3:1);
			me->start_busy(random(2));
			me->start_perform(3, "������");
		}
		else if( me->is_fighting(target) && random(i) > random(j)/3 ) {
			message_vision(HIB"ֻ�Ǳ������Ʒ�ɨ�������̣�$n���Լ��ϰ����ػ�Ҳ������и��\n" NOR,me,target);
			
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="Ů��"?3:1);
			me->start_busy(random(2));
			me->start_perform(2+random(2), "������");
		}
	//    message_vision(msg, me, target);
		me->add("neili",-250);
		me->add("jingli",-150);
	}
	me->delete_temp("lhz/lhl");
	return 1;
}

int help(object me)
{
        write(HIM"\n�����Ʒ�֮�������䡹��"NOR"\n");
        write(@HELP
	������Ϊ�����ƾ���֮һ�������ﵽ�߿ɽ�����ң�ε��似��ʩչ
	�����������������һ����Ϊǣ�Ƶ��ˣ������������Ʊ��߱߳�
	���ŶԷ��������ڶԷ�æ��֮�ʣ���Ȼ��������״���Ʒ档����
	ʤ�������г��������似�й��⣬�������������й�ϵ��
	�����书���ǰ��г����������輤������������

	ָ�perform strike.lianhualuo

Ҫ��  
	������� 1800 ���ϣ�
	��ǰ���� 500 ���ϣ�
	��ǰ���� 500 ���ϣ�
	�����Ƶȼ� 260 ���ϣ�
	���������ȼ� 260 ���ϣ�
	�����м�Ϊ�����ơ�
HELP
        );
        return 1;
}
