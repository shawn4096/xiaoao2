#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        int lvl, j,i;
	object weapon;
	lvl = me->query_skill("yinlong-bian", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target)
	|| !necessary(target) )
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ����������\n");

	if( me->query_skill("yinlong-bian", 1) < 500 )
		return notify_fail("��������޷�������죬�޷�ʩչ����������\n");

	weapon = me->query_temp("weapon");

	if ( ! weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "yinlong-bian"
	|| me->query_skill_mapped("parry") != "yinlong-bian")
		return notify_fail("�������޷�ʩչ����������\n");
		
		
    if (!me->query("quest/jiuyin1/pass"))
		return notify_fail("����δϰ�þ����澭�ϲ�ľ�΢�ؾ��������޷�ʩչ����������\n");
		
    if (me->query_skill_mapped("strike")!="jiuyin-shenzhang"
		&&me->query_skill_prepared("strike")!="jiuyin-shenzhang")
        return notify_fail("��û�м����������ƣ������޷�ʩչ����������\n");
	if (me->query_skill_mapped("force")!="jiuyin-zhengong")		
        return notify_fail("��û�м��������湦�������޷�ʩչ����������\n");
	if (me->query_skill("jiuyin-zhengong", 1) < 500)
		return notify_fail("��ľ����湦��򲻹����޷�ʩչ����������\n");
	if ( me->query_skill("jiuyin-shenzhua", 1) < 500)
		return notify_fail("��ľ�����צ��򲻹����޷�ʩչ����������\n");
    if ( me->query_skill("jiuyin-shenzhang", 1) < 500)
		return notify_fail("��ľ������ƻ�򲻹����޷�ʩչ����������\n");
	if ( me->query_skill("jiuyin-shenfa", 1) < 500)
		return notify_fail("��ľ�������򲻹����޷�ʩչ����������\n");

	if ( me->query("max_neili") < 2000)
		return notify_fail("��������������޷�ʩչ����������\n");

	if ( me->query("neili") < 1000)
		return notify_fail("��������������޷�ʩչ����������\n");

	if ( me->query("jingli") < 1000)
		return notify_fail("��ľ����������޷�ʩչ����������\n");

	message_vision(HIB"$Nʹ������������������Ѹ���ޱȵĹ���$n��\n"NOR,me, target);

	j = lvl /3;

	if ( lvl > 200 )
		j = to_int(lvl/200.0 * lvl/3.0);

	me->add_temp("apply/attack", j);
	me->add_temp("apply/whip", j);
	me->add_temp("apply/damage", j/2);

    message_vision(HIB"$N�����޷���Ȼ��ɣ��������ޣ�һ�ޱ�һ��������\n"NOR,me,target);
 //       i=0;
       
    if (random(me->query_int(1)) > target->query_int(1)/3)
    {
        	message_vision(HIB"$n��$Nʩչ�ľ�������ǿ��ѹ���£��������ˣ�����һƬ����֮�У�����˵�����ˡ�\n"NOR,me,target);
        //	i=1;
			target->start_busy((int)lvl/50);
    } else{
			message_vision(HIC"$n���ٺ��ˣ����ܷ��أ����ݴ��͡�\n"NOR,me,target);
			target->start_busy(3+random(3));
	}
        
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        
	if ( me->is_fighting(target)&&me->query_temp("jiuyin/powerup")){
		message_vision(HIB"$N�ľ���������Ȼ��ɣ���ת���⣬������Ϣ�������޷�����������$nһʱ����Ϊ�޾����ˡ�\n"NOR,me,target);
		target->recieve_damage("qi",random(2000),me);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
     }
	if ( me->is_fighting(target)&&me->query_temp("jiuyin/fast")) {
		message_vision(HIC"$N��������ת֮�£�������ȣ������޷���Ȼ���ù����Ѳ⡣\n"NOR,me,target);
		me->add_temp("apply/whip",me->query_temp("jiuyin/fast")/2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/whip",-me->query_temp("jiuyin/fast")/2);

    }
    if ( me->is_fighting(target)){
		
		weapon->unequip(); 
		message_vision(HIM"$N������¾���������ת���֮���޲�������������ʽ�Ѿ�����һ�񡣳�$n����֮�ʣ�����һ�������ּ������С�\n"NOR,me,target);
        
		me->add_temp("apply/strike",j);
		me->add_temp("apply/claw",j);
		COMBAT_D->do_attack(me, target,me->query_temp("weapon"), 3);
		COMBAT_D->do_attack(me, target,me->query_temp("weapon"), 3);
		//����������˫�У�
		message_vision(HIM"$N����һ����������Ȼ�ص����С�\n"NOR,me,target);
		me->add_temp("apply/strike",-j);
		me->add_temp("apply/claw",-j);
		weapon->wield();		
    }
	if ( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if ( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	if ( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        me->add_temp("apply/attack", -j );
        me->add_temp("apply/whip", -j);
        me->add_temp("apply/damage",-j/2);

    me->start_perform(5+random(2), "����������");
	me->add("neili", -400);
	me->add("jingli", -150);
	//if(i==1) target->start_busy( lvl/50 ); 
	return 1;
}

string perform_name(){ return HIB"������"NOR; }

int help(object me)
{
        write(HIB"\n�����޷�֮������������"NOR"\n\n");
        write(@HELP
        Ҫ��  ��ǰ���� 1000 ���ϣ�
                ������� 2000 ���ϣ�
                ��ǰ���� 1000 ���ϣ�
                �����޷��ȼ� 500 ���ϣ�
                �����湦�ȼ� 500 ���ϣ�
                �������ȼ� 500 ���ϣ�
				�������Ƶȼ� 500 ���ϣ�
				������צ�ȼ� 500 ���ϣ�
                �����޷�Ϊ�����޷���
                �����м�Ϊ�����޷���
                ���ֱֳ�����

HELP
        );
        return 1;
}
