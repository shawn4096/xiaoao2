// lianhuan.c  ������
// Modified by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HBGRN+HIW"ԧ��������"NOR; }

int perform(object me, object target)
{
        int i,lvl,damage;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("��������ʹ�á������ߡ���\n");

		if( (int)me->query_skill("yuanyang-lianhuantui", 1) < 160 )
                return notify_fail("���ԧ�������Ȳ�����죬�޷�ʩչ�������ߡ�\n");
        if ((int)me->query_skill("xiantian-gong", 1) < 160)
                return notify_fail("������칦��򲻹����޷�ʩչ�������ߡ�\n");
        if ( (int)me->query("max_neili") < 1500)
                return notify_fail("�����������������޷�ʩչ�������ߡ�\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʩչ�������ߡ�\n");
        if (me->query_skill_prepared("leg") != "yuanyang-lianhuantui"
            || me->query_skill_mapped("leg") != "yuanyang-lianhuantui")
                return notify_fail("�������޷�ʹ�������߽��й�����\n");
        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("��������Ҫ���칦����������\n");
        if (me->query_temp("yylht/yuanyang"))
                return notify_fail("������ʹ�������߾�����\n");
        
		lvl = me->query_skill("yuanyang-lianhuantui",1);
		damage=lvl+me->query_skill("xiantian-gong",1)/2;
		damage=damage*3+random(damage);

		message_vision(HBYEL+HIW "$N��������������Ծ��������У�ʹ��ԧ�������ȵġ������ߡ������������籩�꣬��������$n��\n"NOR,me, target);
        me->set_temp("yylht/lianhuan",1);
		me->start_perform(6, "ԧ��������");


		me->add_temp("apply/attack",lvl/4);
		me->add_temp("apply/damage",lvl/5);
	
       for (i = 0; i < 4; i++)
	   {
			if (objectp(target)&& me->is_fighting())
				COMBAT_D->do_attack(me, target, 0, random(3)?1:3);
		}
		if (objectp(target)&& me->is_fighting()&&lvl>250)
			COMBAT_D->do_attack(me, target, 0, 3);
		if (objectp(target)&& me->is_fighting()&&lvl>300)
			COMBAT_D->do_attack(me, target, 0, 3);

		me->add_temp("apply/attack",-lvl/4);
		me->add_temp("apply/damage",-lvl/5);
		me->start_perform(5, "ԧ��������");
		me->add("neili",-250);
		me->add("jingli",-200);
		me->delete_temp("yylht/lianhuan");

		return 1;
}

int help(object me)
{
        write(HIG"\nԧ��������֮��ԧ�������ߡ���"NOR"\n");
        write(@HELP
	ԧ����������ȫ��̵��������书֮һ���ýŷ�
	ȫƾһ�������Ƴ������������һ������������
	�Է�����Է�����ʤ����
	�����������ڿ��У�ƾ��һ��������������Է�
	��������ʽ��250����ǰ���Գ����У�300����
	���������ӡ�

	ָ�perform leg.yuanyang

Ҫ��
	���칦���ĵȼ� 160  ���ϣ�
	ԧ�������ȵȼ� 160  ���ϣ�
	�����ȷ��ĵȼ� 160  ���ϣ�
	��������Ҫ�� 1500 ���ϣ�
	��ǰ������Ҫ�� 500  ���ϣ�
	�����ȷ����м�Ϊ����ԧ���ȣ�
	�����ڹ����칦��
	�����ұ�ԧ��������
HELP
        );
        return 1;
}


