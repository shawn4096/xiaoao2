// By KinGSo@���� 2006��4��25�� ����
//2006.12.29���Help
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

#define RI "��" HIY "�����޼�" NOR "��"
string perform_name(){ return HBRED HIY"�����޼�"NOR; }
int perform(object me)
{
        object *obs;
        string msg;
        int damage;
        int ap, dp;
        int flag;
        int i;
        int p;

        

        me->clean_up_enemy();
        if (! me->is_fighting())
                return notify_fail(RI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(RI "ֻ�ܿ���ʩչ��\n");
                
        if (me->query("max_neili") < 5000)
                return notify_fail("�����������Ϊ�����������޷�ʹ��" RI "��\n");

        if (me->query_skill("jiuyang-gong", 1) < 450)
                return notify_fail("��ľ����񹦻�������죬����ʩչ" RI "��\n");

        if (me->query_skill_mapped("cuff") != "jiuyang-gong")
                return notify_fail("������û�м���������Ϊȭ�ţ�����ʩչ" RI "��\n");

        if (me->query_skill_mapped("force") != "jiuyang-gong")
                return notify_fail("������û�м���������Ϊ�ڹ�������ʩչ" RI "��\n");

        if (me->query_skill_prepared("cuff") != "jiuyang-gong")
                return notify_fail("������û��׼��ʹ�þ����񹦣�����ʩչ" RI "��\n");

        if ((int)me->query("neili") < 8000)
                return notify_fail("��������������޷�����" RI "��\n");

        msg = HIY "ֻ��$N" HIY "˫Ŀ΢�գ��������졣���Ķ�ʱ����һ���ޱȴ��۵�"
              "���ţ����ǰ�\n�塸" NOR + HIW "�����޼�" NOR + HIY "������ʱ"
              "����������ɳ���𣬿������ȣ��������ڡ�$N" HIY "\n�漴��£����"
              "�����ű��ѿ����������ܵ����������â���Ժ��������ԡ�\n\n" NOR;

        message_vision(msg, me);

        me->add("neili", -5000);
        me->start_busy(3);

        ap = me->query_skill("force", 1) +
             me->query_skill("cuff", 1) +
             me->query_skill("parry", 1) +

             me->query_skill("jiuyang-gong", 1) +
             me->query("con") * 12;

        obs = me->query_enemy();
        for (flag = 0, i = 0; i < sizeof(obs); i++)
        {
                dp = obs[i]->query_skill("force") * 2 +
                     obs[i]->query_skill("dodge", 1) +
                     obs[i]->query("con") * 9;

                if (ap / 2 + random(ap) > dp)
                {
                        switch (random(2))
                        {
                        case 0:
                                tell_object(obs[i], HIR "��ֻ����ǰ����������Χ����������"
                                                    "�ڣ���â��������һ��͸����롣\n" NOR);
                                break;

                        default:
                                tell_object(obs[i], HIR "��ֻ����ǰ����������Χ����������"
                                                    "�ڣ���â����ǧ��ϸ��һ����������㡣\n"
                                                    NOR);
                                break;
                        }

                        damage = ap * 9 + random(ap * 20);

                        obs[i]->receive_damage("qi", damage, me);
                        obs[i]->receive_wound("qi", damage / 2, me);

                        obs[i]->receive_damage("jing", damage / 16, me);
                        obs[i]->receive_wound("jing", damage / 20, me);

	                p = (int)obs[i]->query("qi") * 100 / (int)obs[i]->query("max_qi");

                        switch (random(5))
                        {
                        case 0:
                                msg = HIR "ֻ��" + obs[i]->name() +
                                      HIR "һ���Һ�������������������"
                                      "�ۡ���Ż��һ�����Ѫ��\n" NOR;
			        msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 1:
                                msg = HIR "ֻ��" + obs[i]->name() +
                                      HIR "���ɳ���Զ�����صĵ�����"
                                      "���ϣ������ս�����Ҳû����վ��"
                                      "��\n" NOR;
			        msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 2:
                                msg = HIR "ֻ��" + obs[i]->name() +
                                      HIR "����ײײ�����������������"
                                      "�ڵء���ü������������һ�ɽ���"
                                      "��\n" NOR;
			        msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 3:
                                msg = HIR "��â������" + obs[i]->name() +
                                      HIR "ȴ�Ǵ�����������Ҳ��������"
                                      "����Ѫ������Ť����ɷ�ǿֲ���\n" NOR;
			        msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        default:
                                msg = HIR + obs[i]->name() +
                                      HIR "��æ������ˣ���ֻ����ǰ��"
                                      "â���ǣ�һ��������ȫ���Ѷ�����"
                                      "���˿ڣ���Ѫ�ɽ���\n" NOR;
			        msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;
                        }
                        obs[i]->start_busy(1);
                        message("vision", msg, environment(me), ({ obs[i] }));
                        obs[i]->add("neili", -8000);
                        flag = 1;
                } else
                {
                        tell_object(obs[i], HIY "��ֻ����ǰ����������Χ������"
                                            "�����ڣ���֮����æ�����ڹ�������"
                                            "������\n" NOR);
                }
                if (obs[i]->query("neili") < 0)
                        obs[i]->set("neili", 0);
        }

        if (! flag) 
                message_vision(HIY "ֻ����â������ȴû���κ��˱�$N"
			       HIY "���л��С�\n\n" NOR, me, 0, obs);
me->start_perform(6,"�������޼���");
        return 1;
}

int help(object me)
{
	write(HBRED HIY"\n�����񹦡������޼�����"NOR"\n");
        write(@HELP
       �����񹦵��ռ��������ܷ�����
       ��һ����ҪĪ���������ս����
       ʩչ���У�����ɱ������������
       ���ڳ������ж��ֶ����ܵ�ͬ��
       �Ĵ����


	Ҫ��  �������  10000 ���ϣ�
                ��ǰ����  5000 ���ϣ�
                �����񹦵ȼ� 450 ���ϣ�
                ����ȭ���ȼ� 450���ϣ�
                �����ڹ�Ϊ�����񹦡�
                ����������Ϊȭ����
                ׼��ʹ�þ����񹦡�

               
HELP
        );
        return 1;
}

