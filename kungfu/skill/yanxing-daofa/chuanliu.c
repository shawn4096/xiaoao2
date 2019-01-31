// chuanliu.c
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int skill,i;
	i=0;
	weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);
	
	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("��ֻ����ս����ʹ�����д�������\n");

	if (!objectp(weapon) || (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if((int)me->query_skill("force", 1) < 350 )
		return notify_fail("��Ļ����ڹ��ȼ�����������ʹ�����д�������\n");

	//if (me->query_skill_mapped("force") != "linji-zhuang")
		//return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

	if ((int)me->query_skill("yanxing-daofa", 1) < 350 )
		return notify_fail("������е����ȼ�����������ʹ�����д�������\n");

	if ((int)me->query_skill("blade", 1) < 350 )
		return notify_fail("��Ļ���������������죬����ʹ�����д�������\n");

	if ( me->query_skill_mapped("blade") != "yanxing-daofa"
	 || me->query_skill_mapped("parry") != "yanxing-daofa" )
		return notify_fail("�������޷�ʹ�����д�������\n");

	if ((int)me->query("neili") < 2000 )
		return notify_fail("����������̫��������ʹ�����д�������\n");

	if ((int)me->query("max_neili") < 5000 )
		return notify_fail("����������̫��������ʹ�����д�������\n");

	if (me->query_temp("em/chuanliu") ) 
		return notify_fail("���Ѿ���ʹ�����д������ˣ�\n");
    
	message_vision(HIY"\n$N�����ټ�ʮ��ׯ������ӿ����ֻ��������" + weapon->name() +HIY"��Ȼһ����\n"NOR, me);
	skill = me->query_skill("yanxing-daofa",1)/6;
	skill += random(skill);
	//if ( skill > 100) skill = 100 + random(skill-100)/10;
	if (me->query_skill("jiuyin-zhengong",1))
    {
		i=(int)me->query_skill("jiuyin-zhengong",1)/60;
		message_vision(HIB"\n$N���Լ������ٳ��������ʽ�ںϵ�����֮�У����е�" + weapon->name() +HIB"���ٴ�����"+chinese_number(i)+"�Ρ�\n"NOR, me,target);
		
    }
    skill += i*60;
	if ( skill > 200) skill = 200 + random(skill-200)/10;
	if (userp(me))
	{
		me->add_temp("apply/attack", skill);
		me->add_temp("apply/damage", skill);
		me->add_temp("apply/strength", skill/10);
	}
	
	//me->add_temp("apply/blade", skill);
	//me->add_temp("apply/damage", skill);
	me->set_temp("em/chuanliu", skill);
    
   
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	if (me->is_fighting(target)&& me->query_skill("yanxing-daofa", 1) > 350)
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);

	
	me->add("neili", -300);
	if (me->query("gender")!="����" || me->query("class")=="bonze"||!me->query("quest/em/yxdf/jueji/pass"))
	{
		if (me->query_skill("yanxing-daofa",1)<400)
		{ 
		//me->start_busy(random(2));
			me->start_perform(2, "���д�����");
		}
		else if (me->query_skill("yanxing-daofa",1)<450)
			me->start_perform(1, "���д�����");
		message_vision(YEL"����������ˣ��������ֵ����ĺ�������֮����������Щ��ɬ�Ѷ���\n"NOR,me);
	}
	//if (objectp(target)&&me->is_fighting())
		call_out("remove_effect", 1, me, target, weapon, skill);
	return 1;
}

void remove_effect(object me, object target,object weapon, int skill)
{
	//int skill=me->query_temp("em/chuanliu");
	if(!me) return;
	if(!me->is_fighting(target)
	|| !weapon
	|| me->query_temp("weapon") != weapon
	|| me->query_skill_mapped("blade") != "yanxing-daofa"
	|| me->query_skill_mapped("parry") != "yanxing-daofa"){
		if( weapon)
			message_vision(HIW"$N����"+weapon->query("name")+HIW"�ĵ�����������ʧ�ˣ�\n"NOR, me);
		if (userp(me))
	    {
		   me->add_temp("apply/attack", -skill);
		   me->add_temp("apply/damage", -skill);
		   me->add_temp("apply/strength", -skill/10);
	    }

		me->delete_temp("em/chuanliu");
		return;
	}
	call_out("remove_effect", 1, me, target, weapon, skill);
}

string perform_name(){ return HIR"���д�����"NOR; }

int help(object me)
{
        write(HIR"\n���е���֮�����д���������"NOR"\n\n");
        write(@HELP 
	���е������Ƕ�ü�׼ҵ����似��������º���
	ѧϰϰ�á������е����׼ҵ���ʹ�ã���������
	���ټ�ׯ���ʹ�ã�Ҳ��һ�Ų��׵��似��
	�������ǽ�����ʩչ���󣬼�����������Ĵ���
	Ҳ��һ���������ص��ǽ�ȫ�����ۼ��ڵ��ϣ�
	�������ϣ������ĺϣ������˺��������������
	ע�⣺�����н⿪�º����������������

	ָ�perform blade.chuanliu

Ҫ��
	��ǰ�������� 2000 ���ϣ�
	����������� 5000 ���ϣ�
	���е����ȼ� 350 ���ϣ�
	�����ڹ��ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	��������Ϊ���е�����
	�����м�Ϊ���е�����
	�����ڹ����ޣ�
	���ֳֵ������,
	

HELP
        );
        return 1;
}
