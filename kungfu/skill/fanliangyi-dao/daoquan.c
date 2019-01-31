// shenfeng.c ������
// by look
#include <ansi.h>

inherit F_SSERVER;


int perform(object me, object target)
{
        int lvl;
        object weapon = me->query_temp("weapon");
        lvl = ( (int)me->query_skill("fanliangyi-dao", 1) + (int)me->query_skill("poyu-quan", 1) ) /4;

        if( !target ) target = offensive_target(me);
     
        if( !target || !me->is_fighting(target) )
                return notify_fail("�������ơ�ֻ����ս���жԶ���ʹ�á�\n");
	
        if (!weapon || weapon->query("skill_type") != "blade"
        || me->query_skill_mapped("blade") != "fanliangyi-dao")
                return notify_fail("������û�е����޷�ʹ�á������ơ���\n");             
        if (me->query_skill_mapped("blade") != "fanliangyi-dao"
			||me->query_skill_mapped("parry") != "fanliangyi-dao")
                return notify_fail("��û�м��������ǵ����޷�ʹ�á������ơ���\n");             

        if( (int)me->query_skill("fanliangyi-dao",1) < 100 )
                return notify_fail("��ķ����ǵ�������죬����ʹ�á������ơ���\n");
      
        if( (int)me->query_skill("blade",1) < 100 )
                return notify_fail("��Ļ��������ȼ�����������ʹ�á������ơ���\n");  

        if( (int)me->query_skill("poyu-quan", 1) < 100 )
                return notify_fail("�������ȭ���ȼ�����������ʹ�á������ơ���\n");
        if( (int)me->query_skill("qimen-bagua", 1) < 100 )
                return notify_fail("������Ű��Եȼ�����������ʹ�á������ơ���\n");

        if( (int)me->query_skill("zixia-gong", 1) < 100 )
			if( (int)me->query_skill("hushan-qigong", 1) < 100 )
                return notify_fail("��Ļ�ɽ�ڹ��ȼ�����������ʹ�á������ơ���\n");

        if( (int)me->query("max_neili") < 800 )
                return notify_fail("�������̫��������ʹ�á������ơ���\n");
      
        if( (int)me->query("neili") < 400 )
                return notify_fail("�������̫���ˣ��޷�ʹ�ó��������ơ���\n");   
                                                                                 
        if (me->query_skill_prepared("cuff") != "poyu-quan"
          || me->query_skill_mapped("cuff") != "poyu-quan")
                return notify_fail("�������޷�ʹ�á������ơ����й�����\n");


        message_vision(HIC"\n$N����һ����Х����������ʹ���������ơ�����$n������ش����ȭһ����\n"NOR, me,target);
        me->add("neili", -(300+random(100))); 
        me->add("jingli", -100);      
        me->add_temp("apply/attack", lvl/4);
		me->add_temp("apply/cuff", lvl/3);
		me->add_temp("apply/damage", lvl/5);
		me->add_temp("apply/blade", lvl/5);

        weapon->unequip(); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(objectp(target)&&me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       weapon->wield();
       if(objectp(target)&&me->is_fighting(target))
		{ 
       //       weapon->unequip();
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
         //     weapon->wield();
        }
		me->add_temp("apply/attack", -lvl/2);
		me->add_temp("apply/cuff", -lvl/3);
		me->add_temp("apply/damage", -lvl/5);
		me->add_temp("apply/blade", -lvl/5);

        me->start_busy(1);
	    me->start_perform(4 , "�������ơ�");
        return 1;
}
string perform_name(){ return HIR"������"NOR; }
int help(object me)
{
        write(HIC"\n�����ǵ�֮�������ơ���"NOR"\n");
        write(@HELP
	���׵����Ĳ��������롸�����ɡ��ġ������ǽ�����һ����
	������������б仯���������а˰���ʮ�İ�仯������
	��ɽ�߰��������ڹ�����һս�����˷�֪���ⷴ���ǵ�Ҳ
	���˲��õľ�ѧ��
	���������Ƿ����ǵ���ѧ��˲��ʩչ����ȭһ������
	��������߲���ʩչ��

	ָ�perform blade.hebi

Ҫ��
	��ɽ��������ϼ�����ĵȼ� 100  ���ϣ�
	�����ǵ��ĵȼ� 100  ���ϣ�
	���������ĵȼ� 100  ���ϣ�
	���Ű��Եĵȼ� 100  ����
	��ǰ������Ҫ�� 1000  ���ϣ�
	��ǰ������Ҫ�� 1000  ���ϣ�
	��������Ϊ�����ǵ���
	�����м�Ϊ�����ǵ���
	�����ڹ����ޣ�
	�ֳֵ���
HELP
        );
        return 1;
}
