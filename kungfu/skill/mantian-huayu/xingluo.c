//xingluo.c �����岼  �ڰ����书
//cre by sohu@xojh 2014/6
#include <ansi.h>
#include <combat.h>


inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i, p;
        int n,damage;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;
		skill = me->query_skill("mantian-huayu", 1)+me->query_skill("force", 1)/6;
		if (me->query_skill_mapped("force")=="tianmo-gong") skill = me->query_skill("mantian-huayu", 1)+me->query_skill("tianmo-gong", 1)/5;
		if (me->query_skill_mapped("force")=="xixing-dafa") skill = me->query_skill("mantian-huayu", 1)+me->query_skill("xixing-dafa", 1)/3;
        
        if (!target) target = offensive_target(me);

        if (userp(me) && !me->query("quest/hmy/mthy/xingluo/pass"))
                return notify_fail("����Ȼ��˵�������岼�������������δѧ�ᡣ\n");

        if (!target || !me->is_fighting(target))
                return notify_fail("�����岼����ֻ����ս���жԶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "throwing")
                return notify_fail("���������в�û�����Ű������޷�ʩչ�����岼\n");

        if (weapon->query_amount() < 20)
                return notify_fail("����Ҫ�ж�ʮö��������ʩչ������ʩչ�����岼\n");

        if (skill < 350)
                return notify_fail("������컨�꼼�ܲ�����죬����ʩչ�����岼��\n");

        if ((int)me->query_skill("force",1) < 350)
                return notify_fail("����ڹ���򲻹�������ʩչ�����岼��\n");

        if ((int)me->query("neili") < 2000)
                return notify_fail("�������������㣬����ʩչ�����岼��\n");
        if (me->query_temp("mthy/xingluo"))
                return notify_fail("������ʩչ�����岼������\n");
        if (!living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg= RED "$N" RED "����Ծ�𣬶�Ȼ��ʮָ���ţ������������е�"
             + weapon->name() + RED "�����\n���еİ�������Բ�ط�֮�ƣ���$n" RED "�������У�\n" NOR;

        my_exp = me->query("combat_exp")/1000;
        ob_exp = target->query("combat_exp")/1000;
        me->set_temp("mthy/xingluo",1);
        n = 5 + random(2);
        if (random(my_exp) > ob_exp) n += 6 + random(5);
        if (random(my_exp / 2) > ob_exp) n += 8 + random(6);
        if (random(my_exp / 3) > ob_exp) n += 10 + random(8);
        if (weapon->query_amount() < n) n = weapon->query_amount();

		if (random(my_exp) > ob_exp/2
			||random(me->query_skill("throwing",1))>target->query_skill("parry",1)/2)
        {

                msg += HBRED "���$n" HBRED "����������ȫ�����±�$P" HBRED "���"
                       HBRED + chinese_number(n) + HBRED "��Ѫ������Ŀ�������"
                       "���̶á�\n" NOR;
			    damage=n*skill;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
				if (me->query("env/damage"))
				{
					tell_object(me, RED"���������޴����"+target->query("name")+"�����"+damage+RED"���˺���\n"NOR);
				}
	            p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                message_vision(msg, me, target);
                
        } else
        {
                msg += CYN "$p" CYN "����$P" CYN "�������أ����Ҵ��⣬��"
                       "������㿪�����а�����\n" NOR;
                message_vision(msg, me, target);
        }

        //weapon->set_amount(0);
		me->add_temp("apply/attack",skill/2);
		me->add_temp("apply/damage",skill/4);
		me->add_temp("apply/throwing",skill/4);
		while (n--)
        {
          if (objectp(target)&&me->is_fighting(target))
    		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);			   
				 

         }
		me->add_temp("apply/attack",-skill/2);
		me->add_temp("apply/damage",-skill/4);
		me->add_temp("apply/throwing",-skill/4);

		me->delete_temp("mthy/xingluo");
        me->add("neili", -random(2000));
        me->start_busy(2);
        me->start_perform(4, "�������岼��");
        return 1;
}
string perform_name(){ return HIC"�����岼"NOR; }
int help(object me)
{
        write(HIC"\n���컨��֮"HIC"�������岼����"NOR"\n");
        write(@HELP
	���컨�갵���ַ�����������̾���֮һ������������ǧ��������
	�����ַ����Ǿ�տ��������������Ůɢ�������ڴ�����๥���似
	�����岼����÷ׯ����֮���϶��ڰ��ӵĳ�����������ʱ���ڣ���
	���е����ӷ����ȥ��ר��Է�Ѩ��,����ʤ����
	ѧϰ������Ҫ��ڰ�����̡�
	
	ָ��;perform throwing.xingluo

Ҫ��  
	�����ڹ��ȼ� 350 ���ϣ�
	���컨��ȼ� 350 ���ϣ�
	��ǰ���� 2000 ���ϣ�
	����׼��������
HELP
        );
        return 1;
}
