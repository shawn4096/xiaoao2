// This program is a part of NITAN MudLIB
// qinna.c ����

#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me,object target)
{
        string msg;
        object weapon;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����֡����á�ֻ����ս���жԶ���ʹ�á�\n");

        skill = me->query_skill("fengyun-shou", 1);

        if (skill < 140)
                return notify_fail("��ķ����ֵȼ�����������ʹ�á����á���\n");
		if (me->query_skill("yijin-jing", 1) < 140)
                return notify_fail("����׽�ȼ�����������ʹ�á����á���\n");
		if (me->query_skill("hand", 1) < 140)
                return notify_fail("��Ļ����ַ��ȼ�����������ʹ�á����á���\n");

        if (me->query("neili") < 500)
                return notify_fail("��������������޷����á����á���\n");
         if (me->query("jingli") < 500)
                return notify_fail("��ĵ�ǰ�����������޷����á����á���\n");

        if (me->query_skill_mapped("hand") != "fengyun-shou"
			||me->query_skill_prepared("hand") != "fengyun-shou") 
                return notify_fail("��û�м��������֣��޷�ʹ�á����á���\n");
       if (target->is_busy())
              return notify_fail("�Է��Ѿ���æ�����ˣ��ò�����ô�����ɣ�\n");

       if (!living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "����ǰ������$n" HIC "��������ֻ��$P"
              "���ֺ��ۺ�Ť����ץ��˦�������ۻ����ң�\n" NOR;
 
		ap = me->query("combat_exp")/1000;
		dp = target->query("combat_exp")/1000;
	
        if (random(ap) > dp/2
			||random(me->query_skill("hand",1))>target->query_skill("parry",1)/2)
        {
                me->add("neili", -80);
                damage =me->query_skill("hand",1)+me->query_skill("fengyun-shou",1) ;
                message_vision(HIR "$p" HIR "�����ֿ����վ�����$P"HIR "���������к��Ǳ�ѹ�Ƶ��޷�������\n" NOR,me,target);
				target->receive_damage("qi",damage,me);
				target->receive_damage("qi",damage/3,me);
				if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR);

                target->add_busy(1);
                
        } else
        {
                message_vision(CYN "����$p" CYN "�Ŀ�����$P" CYN
                       "����ʽ�������һһ��⣬û¶���������\n" NOR,me,target);
                me->add("neili",-20);
                me->start_busy(2);
        }
        return 1;
}

string perform_name(){ return HIY"������"NOR; }

int help(object me)
{
        write(HIC"\n������֮����������������"NOR"\n");
        write(@HELP
	��������һ�������ַ������似�����Ժ�߼��ַ�ǧҶ��
	�Ļ����似���������ֵ��ӳ��뽭����ϰ���似��
	���ص��ǽ����ֵ��������ںϵ�ʵս�У������ս���ö�
	����������ס�Է���Ҫ����λ���Ӷ�һ���ƵС�
	
	ָ�perform hand.qinna
		
Ҫ��  
	����������� 1500 ���ϣ�      
	��ǰ�������� 500  ����
	��ǰ�������� 500  ���ϣ�  
	�����ַ��ȼ� 150 ���ϣ�
	�׽���ȼ� 150 ���ϣ�
	�����ַ��ȼ� 150 ���ϣ�	
	�����ַ�Ϊ�����֣�
	�����ޱ�����
                
HELP
        );
        return 1;
}