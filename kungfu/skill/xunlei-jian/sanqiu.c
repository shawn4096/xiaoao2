// sanqiu.c Ѹ�׽� perform һ������
// cck 13/6/97
//edit by sohu
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        string msg1;
	
		int skill;
		skill=me->query_skill("xunlei-jian",1);

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��һ�����ֻ����ս���жԶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( (int)me->query_skill("xunlei-jian", 1) < 180 )
                return notify_fail("���Ѹ�׽���������죬����ʹ�á�һ�������\n");
        if( (int)me->query_skill("sword", 1) < 180 )
                return notify_fail("��Ļ�������������죬����ʹ�á�һ�������\n");

        if( (int)me->query_skill("force", 1) < 180 )
                return notify_fail("��Ļ����ڹ��ȼ�����������ʹ�á�һ�������\n");
		if( me->query_skill_mapped("sword")!="xunlei-jian" )
			//||me->query_skill_mapped("parry")!="xunlei-jian" )
                return notify_fail("��û�ܼ���Ѹ�׽�������ʹ�á�һ�������\n");
		if( (int)me->query_str() < 30 )
                return notify_fail("��һ�������Ҫ�߱�������ĺ�����������30������ʹ�á�һ�������\n");

        if( (int)me->query("neili", 1) < 250 )
                return notify_fail("����������̫��������ʹ�á�һ�������\n");
        if( (int)me->query("jingli", 1) < 200 )
                return notify_fail("�����ھ���̫��������ʹ�á�һ�������\n");         
             
		if( me->query_temp("xlj/sanqiu") )
                return notify_fail("������ʹ�á�һ�������\n");
        msg = BBLU+HIC "$NͻȻ���������ÿһ����������Ѥ�ý��⣬���罾����������Ѹ�ײ����ڶ�֮�Ʒ�����$n��������������\n" NOR;
        msg1 = BBLU+HIY "$N��Хһ���������ָ,���ƹ��쵫ȴ�����ޱȡ�\n" NOR;

        message_vision(msg, me, target);
	/*	if (!userp(target)) {
			skill=skill+me->query_skill("xuantian-wuji",1)/6;
			me->add_temp("apply/sword",skill/4);
			me->add_temp("apply/damage",skill/5);
			target->start_busy(1);
			//me->set_temp("xlj/sq",1);
		}*/
		me->add_temp("apply/attack",skill/4);
		//me->add_temp("apply/sword",skill/5);
		me->add_temp("apply/damage",skill/5);
		me->set_temp("xlj/sanqiu",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
//		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

		me->add_temp("apply/attack",-skill/4);
		//me->add_temp("apply/sword",-skill/5);
		me->add_temp("apply/damage",-skill/5);
        me->add("neili", -150);

        message_vision(msg1, me, target);
		me->start_perform(3,"��һ�����");   
		me->delete_temp("xlj/sanqiu");
		me->delete_temp("xlj/sq");
        return 1;
}

string perform_name() {return HIC"һ������"NOR;}

int help(object me)
{
    write(HIY"\nѸ�׽�����һ�������"NOR"\n");
    write(@HELP
	Ѹ�׽��������صĳ����������ɺ����������ر仯���á�
	������ɽ��ߵغ����ױ������Ķ࣬�ɴ����򽣷��Ŀ��
	���⡣
	һ������Ǹп�ʱ����׾Թ�϶���ҴҶ�������Ѹ��
	���п��ٹ����Է����������ֱر��似��
    
	ָ�perform sanqiu
	
Ҫ��
	Ѹ�׽����ȼ� 180 �����ϣ�
	���������ȼ� 180 �����ϣ�
	�����ڹ��ȼ� 180 �����ϣ�
	��ǰ����Ҫ�� 250 ���ϣ�
	��ǰ����Ҫ�� 200 ���ϣ�
	��ǰ��Ч���� 30 ���ϣ�
	��������ΪѸ�׽�����
	�ڹ����ޣ�
	���ֳֽ���������    

HELP
	);
	return 1;
}

