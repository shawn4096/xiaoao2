// ailao.c ����ɽ��ʮ����

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int i, a,skill;

        if (!target) target=offensive_target(me);

        if (!target
                || !target->is_character()
                || !me->is_fighting(target))
                return notify_fail("�㲻��ս���У�\n");

//      if (target->is_busy())
//              return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɢ�\n");
        
        weapon=me->query_temp("weapon");
        if (!objectp(weapon) || weapon->query("skill_type") != "sword")
                return notify_fail("�������޽������ʹ�ó�����ɽ��ʮ������\n");

        if (me->query_skill("force", 1)<400)
                return notify_fail("����ڹ����δ�����޷���Ԧ����ɽ��ʮ������\n");
        
        if (me->query_skill("sword", 1) < 400)
                return notify_fail("�㽣����Ϊ�������޷�ʩչ����ɽ��ʮ������\n");
        
        if (me->query_skill("duanjia-jianfa",1)<400)
                return notify_fail("��μҽ���Ϊ�������޷�ʩչ����ɽ��ʮ������\n");
        
        if( me->query_skill_mapped("force") != "qiantian-yiyang")
			if( me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("�����õ��ڹ��밧��ɽ��ʮ������·��㣣�\n");
        if (me->query_skill_mapped("sword") != "duanjia-jianfa"
          || me->query_skill_mapped("parry") != "duanjia-jianfa")
                return notify_fail("�㼤���Ľ������ԣ��޷�ʹ�á�����ɽ��ʮ���������й�����\n");

        if (me->query("neili") <= 1500)
                return notify_fail("�����������ʹ�ð���ɽ��ʮ������\n");
       if (me->query("jingli") <= 1000)
                return notify_fail("��ľ�������ʹ�ð���ɽ��ʮ������\n");
        
		message_vision(HIW "\nͻȻ��$N����ͻ�䣬�����ݺᣬ����������������ǰ������������������������������\n"NOR, me, target);
        message_vision(HIR "\nʩչ������ɽ��ʮ����������$n����ʵʵ��������ʮ������\n\n" NOR, me, target);
		skill=me->query_skill("duanjia-jianfa",1);

	
		if (me->query("quest/tls/djjf/ailao/pass"))
		{
			a=7+random(4);
			if (me->query("class")!="bonze"&&me->query_temp("qtyy/yiyang")) 
				skill=skill+me->query_skill("qiantian-yiyang",1)/6;
			message_vision(HIY "\n$NǬ��һ����������ȫ���������ȣ��ͽ�����Ϊһ�壬����ɽ���������\n\n" NOR, me, target);
		}else a=6;
		
		me->add_temp("apply/sword",skill/5);
		me->add_temp("apply/attack",skill/5);
		me->add_temp("apply/damage",skill/5);	
		me->set_temp("djjf/ailao",1);
        
		for (i=1; i<=a; i++)
		{		
				if (me->is_fighting()&&objectp(target))
			         COMBAT_D->do_attack(me, target, weapon,random(2)?3:1);
		}
		me->add_temp("apply/sword",-skill/5);
		me->add_temp("apply/attack",-skill/5);
		me->add_temp("apply/damage",-skill/5);
		me->delete_temp("djjf/ailao");
        me->add("neili", -200);
        me->add("jing", -20);
		me->start_perform( 5, "������ɽ��ʮ������");
		me->start_busy(1);
        return 1;
}
string perform_name() {return HIR"����ɽ��ʮ����"NOR;}

int help(object me)
{
        write(HIR"\n�μҽ���֮������ɽ��ʮ��������"NOR"\n\n");
        write(@HELP
	�μҽ������Ǵ�����ʼҼҴ����似�������˻��壬ͬ
	ʱҲ��������ʿ�����˴���һ��ָ�����书�⣬������
	���似��������������ɽ��ʮ�������ǽ������⣬�Դ�
	�۹�һս���μҽ��������������⿪����ɽ�������
	ʽ��������ӡ�
	
	perform sword.ailao

Ҫ��
	��ǰ�������� 1500 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	�μҽ������� 400  ����
	������������ 400  ����
	Ǭ��һ������ 400  ��(��������)��
	�����ڹ����� 400  ����
	��������Ϊ�μҽ�����
	�����м�Ϊ�μҽ�����
	�����ڹ�ΪǬ��һ�������������
	���ֱֳ�����

HELP
        );
        return 1;
}
