// kuangfeng.c  ������
// Modified by Darken@SJ

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIG"������"NOR; }

int perform(object me, object target)
{
        int lvl;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        //if (!(me->query("thd/perform") & 4))
		if (!me->query("thd/wuji/kuangfeng"))
                return notify_fail("����Ȼ��˵���������������һ��������񼼣�����ȴδ��Ƶ������ڡ�\n");
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("��������ʹ�á�����������\n");
        if( (int)me->query_skill("luoying-zhang", 1) < 100 )
                return notify_fail("�����Ӣ���Ʋ�����죬�޷�ʩչ����������\n");
        if( (int)me->query_skill("xuanfeng-tui", 1) < 100 )
                return notify_fail("�������ɨҶ�Ȳ�����죬�޷�ʩչ����������\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 100)
                return notify_fail("��ı̺���������򲻹����޷�ʩչ����������\n");
        if ( (int)me->query("max_neili") < 1000)
                return notify_fail("��������������޷�ʩչ����������\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʩչ����������\n");
        if (me->query_skill_prepared("leg") != "xuanfeng-tui"
            || me->query_skill_mapped("leg") != "xuanfeng-tui"
			//|| me->query_skill_prepared("strike") != "luoying-zhang"
            || me->query_skill_mapped("strike") != "luoying-zhang" )
                return notify_fail("�������޷�ʹ�ÿ��������й�����\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("��ı̺���������Ϊ�������޷�ʹ�ÿ��������й�����\n");
        if (me->query_temp("thd/kuangfeng"))
                return notify_fail("������ʹ���һ�����������\n");
        if (me->query_temp("thd/is_fast")) lvl += 100;
        lvl = me->query_skill("xuanfeng-tui",1);
		if (!userp(target)&& me->query_skill("xuanfeng-tui",1)<250)
            lvl=lvl*1.2;

	    message_vision(HBGRN "$Nһ����Х��ȭ����ʩ��ʹ���һ�����������Ѹ�����׵ع���$n��\n"NOR,me, target);
        me->set_temp("thd/kuangfeng",1);
		me->start_perform(6, "������");
		call_out("kuangfeng_attack", 1, me, target, "leg", lvl);
        return 1;
}

void kuangfeng_attack(object me, object target, string skill, int lvl)
{
        int i,lvl1;
        if (!me) 
return;
		
if(me)

			me->receive_damage("neili", 50+random(50));
       // lvl1=me->query_skill("xuanfeng-tui",1)+me->query_skill("bihai-chaosheng",1)/4;
		
		if (!objectp(target) || !me->is_fighting(target) || lvl <= 0 || me->query("neili") <= 100) {
                message_vision(HIG"$N���ν�����ֹͣ�˿�������\n"NOR, me);
                //me->prepare_skill("cuff");
				//me->prepare_skill("claw");
				//me->prepare_skill("finger");
				//me->prepare_skill("hand");
				//me->prepare_skill("strike");
				//me->prepare_skill("strike","luoying-zhang");
                me->prepare_skill("leg", "xuanfeng-tui");				
				me->delete_temp("thd/kuangfeng");
				me->start_perform(5, "������");
                return;
        } else {
                if (skill == "strike") {
                        me->prepare_skill("leg");
                        me->prepare_skill("strike", "luoying-zhang");
                        message_vision(HIG"$N����Ϊ�ƣ���Ӱ���ɣ������һ����裬Ѹ���ޱȵ���$n��ȥ��\n"NOR, me, target);
                        //remove_call_out("kuangfeng_attack");
						call_out("kuangfeng_attack", 2, me, target, "leg", lvl-50);
                } else {
                        me->prepare_skill("strike");
                        me->prepare_skill("leg", "xuanfeng-tui");
                        message_vision(HIY"$N����Ϊ�ȣ�����������ӿ���ڵ�������һ���磬Ѹ���ޱȵ���$n��ȥ��\n"NOR, me, target);
                        //remove_call_out("kuangfeng_attack");
						call_out("kuangfeng_attack", 2, me, target, "strike", lvl-50);
                }
                me->add_temp("apply/attack",lvl/5);
                me->add_temp("apply/damage",lvl/5);
                for (i = 0; i < 5; i++){
					if (objectp(target)&& me->is_fighting())
						COMBAT_D->do_attack(me, target, 0, random(3)?1:3);
				}
                me->add_temp("apply/attack",-lvl/5);
                me->add_temp("apply/damage",-lvl/5);
				return;
       }
}

int help(object me)
{
        write(HIG"\n������������"NOR"\n");
        write(@HELP
	������Ϊ�һ�������֮һ����а��ҩʦ������
	�������÷����͵�߾����澭�¾�һŭ֮��
	�����еĵ��Ӵ�ϽŽ������ɣ���������
	�����ı��������󣬻�ҩʦ����󶯣�����
	����һ���ȷ����������ӡ����Ź�������Ӣ��
	�����������ɨҵ������ֿ��ٹ�����Ϊ��ҩ
	ʦ������Ķ��ž�����������Ӣ���ƣ�����
	����ɨҶ�ȣ�ѭ����ֹ��ע�⣺������������
	��ÿ�غ����½��������������ת��������
	��ʱ�ޡ�

	perform leg.kuangfeng

Ҫ��
	�̺��������ȼ� 100  ���ϣ�
	��Ӣ���Ƶȼ� 100  ���ϣ�
	����ɨҶ�ȵȼ� 100  ���ϣ�
	��������Ҫ�� 1000 ���ϣ�
	�����ұ��ȷ�Ϊ�����ȣ�
	ÿ�غ�����������������
HELP
        );
        return 1;
}


