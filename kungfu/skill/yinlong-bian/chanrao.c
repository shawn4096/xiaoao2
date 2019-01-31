#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("���ƾ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill("yinlong-bian",1) < 250)
		return notify_fail("��ľ��������޻�������죬����ʹ�ò��ƾ���\n");

	if( !weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "yinlong-bian" 
	|| me->query_skill_mapped("parry") != "yinlong-bian" ) 
		return notify_fail("�������޷�ʹ�ò��ƾ���\n");

	if( me->query("neili") < 1500 )
		return notify_fail("�������������\n");

	if( target->is_busy() )
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
	
	msg = HIG "\n$N��Ȼ�����е�"+weapon->query("name")+HIG"ʹ�����ƾ����趯����Ѹ��,������һ������һ��,����ȫȻ��������֮�⣡\n";

	if(random(me->query("combat_exp") )> target->query("combat_exp")/2
		||random(me->query_dex(1)) > target->query_dex(1)/2)
	{
		msg += HIY "\n���$p��$Pһ�������ȱ����ʵʵ�����������ڵ����޷�����\n" NOR;
		target->start_busy((int)me->query_skill("yinlong-bian",1)/50);
		if (!me->query("quest/em/zzr/pass"))
			me->start_perform(4,"���ƾ�");
	}
	else {
		msg += HIW "����$p������$P�Ĳ��ƾ�������һԾ��㿪�ˡ�\n" NOR;
		me->start_perform(2,"���ƾ�");
	}
	message_vision(msg, me, target);

	if (!me->query("quest/em/zzr/pass"))
		me->start_busy(random(2));
	me->add("jingli", -100);
	me->add("neili", -400);
    return 1;
}

string perform_name(){ return HIG"���ƾ�"NOR; }

int help(object me)
{
        write(HIG"\n����������֮�����ƾ�����"NOR"\n\n");
        write(@HELP
	�����������Ǿ����澭�¾����������书���ʹ����ơ������׹�ץ
	��������޷�ʩչ����������ֻ��Ҫ�㹻�ļ��ɾ���ʩչ���в���
	���ҷ�������Ҳ�Ƿ��겻͸���������ܡ�
	���ƾ����Գ��޵���ת֮�������Է���ס���Ӷ����ƶԷ��ж�����
	ʽ��һ���Է����ˣ��Ʊ����㱻������ü��������Ե�ɺ���������
	ָ�㣬���н���С��Ծ��
    
ָ�perform whip.chanrao
		
Ҫ��  
	��ǰ���� 1500 ���ϣ�
	������� 1500 ���ϣ�
	��ǰ���� 1500 ���ϣ�
	���������޵ȼ� 130 ���ϣ�
	�����޷�Ϊ���������ޣ�
	�����м�Ϊ���������ޣ�
	���ֱֳ�����

HELP
        );
        return 1;
}
