// lingshe.c ����ȭ��֮�����߾���
// Modified by fengyue@SJ

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

string perform_name(){ return HIR"���߾�"NOR; }

int perform(object me, object target)
{
	int damage, p;
	object weapon;
	string msg;
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("�����߾���ֻ�ܶ�ս���еĶ���ʹ�á�\n");



	if( userp(me)&&( me->query_skill_mapped("force") != "hamagong"
        && me->query_skill_mapped("cuff") != "lingshe-quanfa") )
                return notify_fail("�����߾�������������ȭ����ϸ�󡹦����ʹ�á�\n");

        if( me->query_skill_prepared("cuff") != "lingshe-quanfa")
                return notify_fail("���ȭ�����ԣ����������ó������߾�����\n");  

        if( me->query_skill("lingshe-quanfa", 1) < 150 )
                return notify_fail("���ȭ����Ϊ��������\n");

        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("����������������Ӳ���������\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("���ȷ������е�������˵�ɣ���\n");     

     msg = MAG"\n�������йǶ����޹ǣ�������˷���������֮��$N��ʽһ�䣬ʹ��������ȭ������֮��"HIR"�����߾���"MAG"��\n"NOR;

	damage = me->query_skill("cuff") + me->query_skill("lingshe-quanfa") + me->query_skill("hamagong");
	damage += random(me->query("jiali") * 3);
	damage *= 2;
    
   if(target->query("neili") < me->query("neili")) damage *= 3;
   
   if (!userp(me)&& damage > 2000 && me->query("oyf/hmg")<3 ) damage = 2000+random(500); 
   

     target->receive_damage("qi", damage, me);
     target->receive_wound("qi", damage/2, me);
	p = (int)target->query("qi")*100/(int)target->query("max_qi");

	msg += HIR"$n���ֻӳ�����ֻ���ѽ���ȭ�ܿ�����֪�������֮��������һȭ����������ķ�λ������������صĴ���$n���ؿڣ�\n"NOR;
	msg += "( $n"+eff_status_msg(p)+" )\n"; 
        message_vision(msg, me, target);

   if(userp(me) && me->query("env/damage"))             tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"���˺���\n"NOR);  
   if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);   

   if(userp(me)) target->start_busy(2+random(2));
   

	me->set_temp("lsqf/ls",1);
   if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, 3);
   if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, 3);
   if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, 3);
    me->delete_temp("lsqf/ls",1);
	
	if (me->query_temp("hmg_nizhuan")&&me->query_temp("lsqf/wugu"))
	{
		
		if (random(10)>6 && me->is_fighting(target)&&objectp(weapon=target->query_temp("weapon"))){
		   message_vision(HIC"$N�⡰����ȭ��ȥ�Ƽ��죬ٿ��֮���Ѵ�$n���ϣ��͵����������޹�Ҫ����ȭ�ƺ�ת��˳�ֽ�$n���еı�������������\n"NOR,me,target);
           weapon->move(environment(target));		   
		}
		message_vision(HIR"$n����ʤ������������$N��ȭ�������¶���ʮ�ֹ����ѵ���$n��ʱ���»��ң���֪���Ӧ��!\n"NOR,me,target);

		COMBAT_D->do_attack(me, target, 0, 3);
		COMBAT_D->do_attack(me, target, 0, 3);
	}
	me->add("neili", -350);
	me->add("jingli", -150);
	me->start_busy(random(1));
	me->start_perform(4,"���߾�");
	return 1;
}

int help(object me)
{
   write(HIB"\n����ȭ��֮��"HIR"���߾�"HIB"����"NOR"\n");
   write(@HELP
	Ϊ����ŷ����֮��ѧ���������ڵ�һ�λ�ɽ�۽���ܺ�Ϊ
	���»��۽�ʱ������ʤ���ο����߶�����������ȭ����ʩչ
	ʱ�����ֱ��鶯���ߣ������޹ǣ�Ҫּ�����ֱ��ƺ�������
	��������������ʹ������Ϊ�ѽ�������ȭ�ܿ���ʹ��ȭ�ķ�
	λ�Ե÷�����˼������ȴ����������֮��ͻȻ�任����
	�����ˣ�ʹ���˴�о��ȶ�ʧ���Ȼ���
	���߾�������ȭ���Ĺ�������ʽ��һ�л��������к�����
	������󡹦�������������壬��Է��յ������˺���

	ָ�perform cuff.lingshe

Ҫ��
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	����ȭ�� 450 ���ϣ�
	����ȭ�� 450 ���ϣ�
	�����ڹ� 450 ���ϣ�
	��󡹦   450 ���ϣ�
	����ȭ��Ϊ����ȭ����
	�����м�Ϊ����ȭ��
	���ֲ��ܳ���������

HELP
   );
   return 1;
}
