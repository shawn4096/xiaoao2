// wushuang.c ��˫�޶�
// by hunthu
// modified by Olives@SJ 5/4/2001
// for some judgement fault
// ����һ���򵥵�quest,���������� By lsxk@hsbbs 2007/7/25

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIR"��˫�޶�"NOR;}

int perform(object me, int amount)
{
        string msg;
        object weapon, target;
        int skill, damage,p;
        weapon = me->query_temp("weapon");
        skill= me->query_skill("zixia-gong",1);

        if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("����˫�޶�,����һ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query("hsjj/wushuang") != "pass" )
                return notify_fail("��ֻ����˵���⡸��˫�޶�,����һ����֮�����Ըþ������л�һ�ϲ�ͨ��\n");

        if (!weapon || weapon->query("skill_type") != "sword"
                        || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("�������޷�ʹ������˫�޶�,����һ����֮����\n");

        if((int)me->query_skill("huashan-jianfa", 1) < 300 )
                return notify_fail("��Ļ�ɽ������򲻹����޷�����˫�޶�,����һ������\n");

        if((int)me->query_skill("sword", 1) < 300 )
                return notify_fail("��Ļ���������������죬ʹ��������˫�޶�,����һ����������\n");

        if( (int)me->query_skill("zixia-gong", 1) < 300 )
			if( (int)me->query_skill("huashan-qigong", 1) < 300 )
                return notify_fail("��Ļ�ɽ�ڹ���Ϊ������ʹ��������˫�޶�,����һ����������\n");/**/

        if (me->query_skill_mapped("force") != "zixia-gong" && me->query_skill_mapped("force") != "huashan-qigong")
                return notify_fail("û����ϼ����ɽ������Ϊ���������޷�ʹ������˫�޶�,����һ���������ģ�\n");

        if (me->query("max_neili") < 3000)
                return notify_fail("����˫�޶ԣ�����һ�����������ھ�ѧ����������Ϊ�������޷�������������Ľ��С�\n");

        if (me->query("neili") < 1500)
                return notify_fail("�������������\n");

        if (me->query("jingli") < 1000)
                return notify_fail("��ľ���������\n");

        me->add("neili", -800);
        me->add("jingli", -200);
        msg =HIR"\n$NͻȻ��һ����Х�����е�"+weapon->name()+HIR"��˸������Χ��$n��Χ���̣��������!\n"+
                "�͵���$Nһ��ͦ����ֱ��$n�Ŀڣ������ǽ������磬�������ס�\n"NOR;
        if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		  || random(me->query_dex(1))>target->query_dex(1)/2
          || target->is_busy() ){
          msg += HIW"\n$n���һ��������һ��������ѽ������ʱ���������Ѵ�����������\n$N������ǰ���ͣ�"+
                weapon->query("name")+HIW+"����������$n�����ţ��ۼ���һ������$n���϶Դ�������ֱû������\n"NOR;
          message_vision(msg, me, target);
		  target->add_busy(1);

          me->add_temp("apply/damage",skill*3/2);
          me->add("jiali",skill*2/3);
		  damage=me->query_skill("huashan-jianfa",1)+me->query_skill("sword",1)+me->query_skill("huashan-qigong",1);
		  damage=damage*2+random(damage);

		  if (userp(target)&&damage>3500) damage=3500;
		
		  target->receive_damage("qi",damage,me);
		  target->receive_wound("qi",damage/4,me);
          target->set_temp("must_be_hit",1);
          COMBAT_D->do_attack(me,target,me->query_temp("weapon"),3);
          target->delete_temp("must_be_hit");
          me->add_temp("apply/damage",-skill*3/2);
          me->add("jiali",-skill*2/3);
          me->start_busy(1);
          me->start_perform(1+random(4), "����˫�޶ԣ�����һ����");
          return 1;
        }
        else if(random(me->query("combat_exp",1)) > (target->query("combat_exp",1)/5)){
           msg += HIG"\n$n�����е��������ĺã���֪��һ���������ף�����������棬��æб������,ȴҲ�����Ǳ���\n"NOR;
          message_vision(msg, me, target);
          target->add_busy(3+random(3));
          me->start_perform(2+random(2), "����˫�޶ԣ�����һ����");
          return 1;
        }
        msg += HIC"\n$n����һ��������б���������б�����׼��$N����������������Ȼ��Ȼͦ��������$N���ʺ�\n"NOR;
        damage = skill*2;
        me->receive_damage("qi", damage);
        p = (int)me->query("qi")*100/(int)me->query("max_qi");
        msg += "( $N"+eff_status_msg(p)+" )\n";
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"), me->query("huashan/quest") == "����"?3:1);

        me->start_perform(1+random(3), "����˫�޶ԣ�����һ����");
        return 1;
}

int help(object me)
{
   write(WHT"\n��ɽ������"HIR"��˫�޶ԣ�����һ��"WHT"����"NOR"\n");
   write(@HELP
    �⡸��˫�޶�,����һ�����������ǻ�ɽ��Ů��Ϊ����
	�ﲮ��Ŀ쵶���Դ���һ�о���.���н����Կ��ƿ�,��
	ð�����ɵ�Σ�մ̳������޴��һ��,���ܳɹ�����,��
	���ַ���Ҳ��.���ǻ�ɽ���������е��׺�����.

    ָ�perform sword.wushuang

Ҫ��
	��ϼ�� 300 ����ɽ����300��
	��ɽ���� 300 ����
	�������� 300 ����
	������� 3000 ���ϣ�
	��ǰ���� 1500 ���ϣ�
	��ǰ���� 1000 ���ϡ�
˵����
	���Գɹ����õ����������Դ��ں󷽿�ʹ�á�

HELP
    );
    return 1;
}
