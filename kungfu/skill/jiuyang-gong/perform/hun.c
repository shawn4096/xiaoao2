// By KinGSo@���� 2006��4��26�� ����
//By KingSo 2006.12.31 �������help
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
#define HUN "��" HIR "����һ��" NOR "��"
string perform_name(){ return HIR"����һ��"NOR; }
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, p;


       

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUN "ֻ�ܿ���ʩչ��\n");

        if (me->query_skill("jiuyang-gong", 1) < 200)
                return notify_fail("��ľ����񹦻�������죬����ʩչ" HUN "��\n");

        if (me->query_skill_mapped("cuff") != "jiuyang-gong")
                return notify_fail("������û�м���������Ϊȭ�ţ�����ʩչ" HUN "��\n");

        if (me->query_skill_mapped("force") != "jiuyang-gong")
                return notify_fail("������û�м���������Ϊ�ڹ�������ʩչ" HUN "��\n");

        if (me->query_skill_prepared("cuff") != "jiuyang-gong")
                return notify_fail("������û��׼��ʹ�þ����񹦣�����ʩչ" HUN "��\n");

        if (me->query("neili") < 2000)
                return notify_fail("�����������������ʩչ" HUN "��\n");
 
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "��ǰһ����˫�ֻ�Ȧ���ĵ�̫��֮�⡣���Ķ�ʱ��"
              "��һ�����ţ���$n" HIR "�����ȥ��\n" NOR;
 
        ap = me->query_skill("jiuyang-gong", 1) * 2 + me->query("con") * 20 +
             me->query_skill("force", 1);
        dp = target->query_skill("force") + target->query("con") * 10 +
             target->query_skill("force", 1);

        me->add("neili", -800);

        if (ap / 2 + random(ap) < dp)
        {
                msg += HIY "Ȼ��$n" HIY "ȫ���ֵ������ڽ�$N" HIY
                       "���������Ų�����\n" NOR;
	        me->start_busy(3);
        } else
        {
               
                damage = ap * 5 + random(ap * 10);
                me->add("neili", -150);
              if(target->query("neili") > me->query("neili")) damage /= 2;

                if (damage > 8000) damage = 8000 + random(7000);  

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                me->add("neili", -500);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");

                msg +=HIR "$n" HIR "��æ������ˣ�����������ø��죬ֻ��$p" HIR "һ���ҽУ���Ѫ�ɽ���\n" NOR;
        msg += "( $n"+eff_status_msg(p)+" )\n"; 
             me->start_busy(2);

        }
        message_vision(msg, me, target);
         me->start_perform(5,"������һ����");

        return 1;
}
int help(object me)
{
	write(HIR"\n�����񹦡�����һ������"NOR"\n");
        write(@HELP
       �������ۺ���ھ�������������
       ��һ���������ˣ����������ǿ
       �󣬵������ʺܸߡ�

	Ҫ��  �������  2000 ���ϣ�
                ��ǰ����  2000 ���ϣ�
                �����񹦵ȼ� 200 ���ϣ�
                �����ڹ�Ϊ�����񹦡�
                ����������Ϊȭ����
                ׼��ʹ�þ����񹦡�
HELP
        );
        return 1;
}

