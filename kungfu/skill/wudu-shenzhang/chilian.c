#include <ansi.h>
#include <combat.h>


int final(object me, object target);

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int damage;
        int ap, dp;

     //   if (userp(me) && ! me->query("can_perform/wudu-shenzhang/shi"))
      //          return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail( "���������ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill("force",1) < 300)
                return notify_fail("��Ļ����ڹ������������ʩչ���������ơ���\n");
		if (me->query_skill("strike",1) < 300)
                return notify_fail("��Ļ����Ʒ������������ʩչ���������ơ���\n");
		if (me->query("max_neili") < 3500)
                return notify_fail("�������������㣬����ʩչ���������ơ���\n");
		if (me->query("neili") < 1000)
                return notify_fail("��ĵ�ǰ�������㣬����ʩչ���������ơ���\n");
		if (me->query("jingli") < 1000)
                return notify_fail("��ĵ�ǰ�������㣬����ʩչ���������ơ���\n");
        if ((int)me->query_skill("wudu-shenzhang", 1) < 300)
                return notify_fail("����嶾���Ʋ�����죬����ʩչ���������ơ���\n");

        if (me->query_skill_prepared("strike") != "wudu-shenzhang"
			||me->query_skill_mapped("strike") != "wudu-shenzhang")
                return notify_fail("������û��׼���嶾���ƣ�����ʩչ���������ơ���\n");

        if (me->query("neili") < 1500)
                return notify_fail("�����������������ʩչ���������ơ���\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HBRED+HIW "$N" HIW "����һ�ݣ�˫��һ��֮�ʣ���������������˫��֮�䣬ֻ��˫��΢΢�������޵İ��Ϲ⣬�͵�����$n��\n" NOR;
		message_vision(msg,me,target);
        ap = me->query_skill("wudu-shenzhang",1);
        dp = target->query_skill("dodge",1);
        damage=ap*me->query_skill("poison",1)/10;
		me->set_temp("wdsz/chilian",3);
		if (random(ap) > dp/2
			||random(me->query("combat_exp"))>target->query("combat_exp")/2)
        {

			target->receive_damage("qi",damage,me);
			target->receive_damage("qi",damage/4,me);
			me->add_temp("apply/attack",me->query_skill("wudu-shenzhang",1)/2);
			me->add_temp("apply/damage",me->query_skill("wudu-shenzhang",1)/4);
			COMBAT_D->do_attack(me, target,0, 3);
			COMBAT_D->do_attack(me, target,0, 3);
			COMBAT_D->do_attack(me, target,0, 3);
			me->add_temp("apply/attack",-me->query_skill("wudu-shenzhang",1)/2);
			me->add_temp("apply/damage",-me->query_skill("wudu-shenzhang",1)/4);
			if (objectp(target))
			{
				message_vision(HIR "ֻ��$n" HIR "��$N" HIR "һ�����У����˼�����ȴ����ɫ��΢΢���ڡ�\n" NOR,me,target);
			    target->apply_condition("chilian_poison",2);
			    target->receive_wound("jing", random(400), me);
				COMBAT_D->do_attack(me, target,0, 3);
				me->start_busy(1);
			}
				//call_out("final",1,me,target); ������һ�Է����˾�û��Ϣ�ˣ�����ֱ��дһ������ by renlai
			
        } else
        {
                msg = CYN "����$p" CYN "�����ֿ죬����һ��$P"
                       CYN "�Ѷ��$N���С�\n" NOR;
                message_vision(msg, me, target);
				me->start_busy(2);
                target->start_busy(1);
        }
		me->delete_temp("wdsz/chilian");
		me->start_perform(4,"��������");
        return 1;
}

int final(object me, object target)
{
        if (!me||!target) return 1;
      
		if (objectp(target)&&me->is_fighting())
        {
			message_vision(HIR "ֻ��$n" HIR "��$N" HIR "һ�����У����˼�����ȴ����ɫ��΢΢���ڡ�\n" NOR,me,target);
			target->apply_condition("chilian_poison",2);
			target->receive_wound("jing", random(400), me);

        }
		//else message_vision(HIR "ֻ��$n" HIR "��$N" HIR "һ�����У����˼�����ȴ����ɫ��΢΢���ڡ�\n" NOR,me,target);


		me->add_temp("apply/attack",me->query_skill("wudu-shenzhang",1)/2);
		me->add_temp("apply/damage",me->query_skill("wudu-shenzhang",1)/4);
		COMBAT_D->do_attack(me, target,0, 3);
		me->add_temp("apply/attack",-me->query_skill("wudu-shenzhang",1)/2);
		me->add_temp("apply/damage",-me->query_skill("wudu-shenzhang",1)/4);       
		return 1;
}
string perform_name(){ return HBRED+HIW"��������"NOR; }

int help(object me)
{
   write(WHT"\n�嶾����֮��"HBRED+HIW"��������"WHT"����"NOR"\n");
   write(@HELP
	��Ĺ�ɵ�����Ī�����ѧ�������ɹ�Ĺ������
	��������Ī�����嶾�ش��ж���������Ʒ���
	���Ʒ��������ս����Ī��ºų������ӣ���
	����Ϊ�����ĺ����������������Ʒ�֮������
	���Ʒ������ʩչ������ʱ���Ϻ��о綾����
	�ж���ʱ���˿ڻ������ɰ���ָӡ����ʱ��
	����ɫ���ڡ���ʹ������	
	ע�⣺���Ʒ�������Ī������,�˺��Ͷ���
	�й�ϵ��
	ע�⣺set �嶾���� �嶾 ������Ч
	perform strike.chilian
	
Ҫ��
	�������Ҫ�� 3500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�嶾���Ƶȼ� 300 ���ϣ�
	�����Ʒ��ȼ� 300 ���ϣ�
	�����ұ��Ʒ�Ϊ�嶾���ƣ�	
	
HELP
   );
   return 1;
}
