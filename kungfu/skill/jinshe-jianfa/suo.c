// suo.c ������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, damage;
		
		weapon = me->query_temp("weapon");
        if (!objectp(weapon)
			|| weapon->query("skill_type")!="sword")
           return notify_fail("��û�ý�������������ʹ�þ��У�\n");
		
		if (weapon->query("id") != "jinshe sword" && weapon->query("id") != "yinshe sword")
           return notify_fail("��û�ý��߽������߽�������ʹ�þ��У�\n");
        skill = me->query_skill("jinshe-jianfa",1);
        
		if( !target ) target = offensive_target(me);
		if (!me->query("quest/���߽���/pass"))
			return notify_fail("����δȫ��������߽����������ʹ�ô˾��У�\n");
        if( !me->is_fighting() )
            return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon2 = target->query_temp("weapon")))
            return notify_fail("�Է�û��ʹ�ñ��������ò��ˡ�����������\n");

        if( skill < 450)
            return notify_fail("��Ľ��߽����ȼ�����, ����ʹ�á�����������\n");
		if (me->query_skill_mapped("sword")!="jinshe-jianfa"
			||me->query_skill_mapped("parry")!="jinshe-jianfa")
	        return notify_fail("��û�м������߽���, ����ʹ�á�����������\n");

        if( me->query("neili") < 3000 )
            return notify_fail("��������������޷����á�����������\n");
        if( me->query("jingli") < 1000 )
            return notify_fail("��ľ����������޷����á�����������\n");
        msg = HIC "$N����"+weapon->query("name")+HIC"����һ�����ν�⣬б��һ����һ�С��������������⵹�����ù���$n��"+weapon2->name()+HIC"�ϡ�\n";
        message_vision(msg, me, target);

        ap = me->query_skill("sword",1)/3 + skill/2;
        dp = target->query_skill("dodge",1)/2;
        
         if( random(ap) > dp/2
			 ||random(me->query_str(1))>target->query_str(1)/2
			 || !living(target))
        {
            if(userp(me))
                 me->add("neili",-200);
            msg = "$n��ʱ������ǰ���һ��������һ������";
         
			msg += weapon2->name();
            if (weapon2->query("skill_type")=="sword")
            {
				msg += "���ַɳ���\n" NOR;
				target->add_busy(3);
				weapon2->move(environment(target));

            }else {
				msg+="��ȻΪ��β������������ʱ��������һ�Σ�\n"NOR;
				target->add_busy(1);
			}
			msg+=HIR"$nΪ��������ʽ�����ƣ�һʱ��������ӿ����Ϣ��������Ȼ�޷��������У�\n"NOR;
			target->add_condition("no_perform",1);
        }
        else
        {
            if(userp(me))
                 me->add("neili",-100);
            msg = "$n����������������" + weapon2->name()+
"бб˳��һ��һ����˻�����\n"NOR;
            me->start_busy(1);
        }
        message_vision(msg, me, target);
		me->add("neili",-350);
		me->add("jingli",-300);

        return 1;
}


int help(object me)
{
        write(HIY"\n���߽���֮������������"NOR"\n\n");
        write(@HELP
	�����ɾ���ѩ�������������ĵľ����书. ��ϧ��������
	�����ؼ����ָ�ɺü�����, ���߿��������Ҳ����ǰ
	�ഫ�ڴ�������ؼ��еĽ���, ��, �Ʒ�����ܷ��ӽ�
	�߽�������������. ������ҿ��Ի�ý��߽�, ��ʹ����
	�����ϲ�¥��
	�����������ý��߽�����֮β�̵����ã����Է�����ǣ��
	���ڽ���������ֱ����ס���ǽ���������ǣ�ƹ�Ч��

	ָ�perform sword.suo

Ҫ��
	��ǰ���� 3000 ����;
	��ǰ���� 1000 ���ϣ�
	���߽��� 450 ���ϣ�
	�����������С��30,
	�����������߽�����
	�����мܽ��߽�����
	�ڹ����ޣ�
    ��װ�����߽��������߽�
	�⿪����3����ʹ�á�

HELP
        );
        return 1;
}

string perform_name(){ return HIR"������"NOR; }
