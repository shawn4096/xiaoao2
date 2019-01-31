// lianhuan.c for murong-jianfa
// by snowman@SJ 01/05/1999.
// modify by leontt@SJ 26/09/2000.

#include <ansi.h>

inherit F_SSERVER;
int perform(object me,object target)
{
	object weapon;
	int i;
	int skill=me->query_skill("murong-jianfa",1);

	if( !target ) target = offensive_target(me);
	
	if( !target || !me->is_fighting(target) || !living(target)
	|| environment(target)!=environment(me))
		return notify_fail("�߽�����ָֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill_mapped("force") != "shenyuan-gong")
		return notify_fail("����ڹ�������Ԫ�����޷�ʹ���߽�����ָ��\n");

	if( (int)me->query_skill("shenyuan-gong", 1) < 500 )
		return notify_fail("����ڹ���δ���ɣ�����ʹ���߽�����ָ��\n");

	if( (int)me->query_skill("murong-jianfa", 1) < 500 )
		return notify_fail("��Ľ�����δ���ɣ�����ʹ���߽�����ָ��\n");

	if(!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "murong-jianfa")
		return notify_fail("������û�н����޷�ʹ���߽�����ָ��\n");

    if((me->query_skill_mapped("parry") != "murong-jianfa")
        &&(me->query_skill_mapped("parry") != "douzhuan-xingyi"))
         return notify_fail("����мܹ��򲻶ԣ��޷�ʹ���߽�����ָ��\n");
	if( (int)me->query_skill("canhe-zhi", 1) < 500 )
		return notify_fail("��Ĳκ�ָ��δ���ɣ�����ʹ���߽�����ָ��\n");
	if((int)me->query("max_neili") < 12000 )
		return notify_fail("���������Ϊ����������ʹ���߽�����ָ��\n");
	if((int)me->query("neili") < 1000 )
		return notify_fail("�������������㣬����ʹ���߽�����ָ��\n");
	if((int)me->query("jingli") < 1000 )
		return notify_fail("�����ھ������㣬����ʹ���߽�����ָ��\n");
	if((int)me->query_temp("mrjf/lianhuan"))
		return notify_fail("������ʹ���߽�����ָ��\n");
	if(me->query_skill_mapped("finger") != "canhe-zhi"
	 || me->query_skill_prepared("finger") != "canhe-zhi")
		return notify_fail("��û����ָ���޷�ʹ���߽�����ָ��\n");
	if((int)me->query_skill("sword", 1) < 500 )
		return notify_fail("��Ļ�������������죬�����ڽ�����ʹ���߽�����ָ��\n");

	message_vision(MAG"\n$N"MAG"ʹ��Ľ�ݽ���֮���衸�߽�����ָ��������$P����ʳָ��"+weapon->name()+MAG"��һ����������������ӳ��ֱϮ$n"MAG"��\n"NOR, me,target);
	me->set_temp("mrjf/lianhuan", 7);

	me->receive_damage("neili", 100);
	me->receive_damage("jingli", 100);
	
	me->add_temp("apply/attack", skill/3);
	me->add_temp("apply/damage", skill/4);

	//me->add_temp("apply/dodge",i/3);

	
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (me->query("quest/mr/dzxy/pass"))
	{
		message_vision(HIM"$N��ת�������������,�ڹ���տ��Բ�ڻ�ͨ������ת���䣬�������ͣ�\n"NOR,me);
		me->start_perform(1, "���߽�����ָ��");
		//i=14;
	}
	else {
		//i=7;
		me->start_perform(3, "���߽�����ָ��");
	}
	i=7;
	call_out("check_fight", 1, me, i);
	return 1;
}


//�˳�����
void remove_effect(object me)
{
	int skill;
	if(!me) return;
	skill=me->query_skill("murong-jianfa",1);

	me->delete_temp("mrjf/lianhuan");

    me->add_temp("apply/attack", -skill/3);
 
	me->add_temp("apply/damage", -skill/4);

	if (living(me))
		message_vision(HIY"\n$N"HIY"�ġ��߽�����ָ������������ϣ����ص�������չ���\n"NOR, me);
	me->start_perform(5, "���߽�����ָ��");
	return;
}
//���״̬
void check_fight(object me, int i)
{
	object weapon, target;

	if (!me ) return;

	target = offensive_target(me);

	if(i<0
	|| !living(me)
	|| !target
	|| !me->is_fighting(target)
	|| environment(target)!=environment(me)
	|| !me->query_temp("mrjf/lianhuan")
	|| me->query("neili") < 1000
	|| me->query("jingli") < 1000)
		return remove_effect(me);

	if(me->query_skill_mapped("sword") != "murong-jianfa") {
		tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á��߽�����ָ��������\n");
		return remove_effect(me);
	
	}
    else if(me->query_skill_mapped("force") != "shenyuan-gong") {
		tell_object(me, HIR"����ʱ�Ļ��ڹ�����������ʹ�á��߽�����ָ��������\n");
		return remove_effect(me);
   } else if((me->query_skill_mapped("parry") != "murong-jianfa")
       &&(me->query_skill_mapped("parry") != "douzhuan-xingyi"))
   {
		tell_object(me, HIR"����ʱ�Ļ��мܣ���������ʹ�á��߽�����ָ��������\n");
		return remove_effect(me);
	} 
    else if(!objectp(weapon = me->query_temp("weapon"))
		|| weapon->query("skill_type") != "sword")
	{
		tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á��߽�����ָ��������\n");
		return remove_effect(me);
	}
	else {
		me->receive_damage("neili", 50);
		me->receive_damage("jingli", 50);
		if (objectp(target) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		call_out("check_fight", 1, me, i--);
	}
}

string perform_name(){ return MAG"�߽�����ָ"NOR; }
int help(object me)
{
        write(HIG"\nĽ�ݽ���֮"+MAG"���߽�����ָ��"NOR"\n\n");
        write(@HELP
	Ľ�ݽ���������Ľ���似�еľ�����ʽ���Ǻ��ĵ��Ӳ���
	�佣���ص��Ǽ��ݲ������ں����½������������ֱ����
	�ã����ڲ�ͬ����������Ľ�ݼҴ��ڹ�֧�֣���Ϊ���ָ�
	��һ��¥�����м���ָ�������⿪��ת���ƾ����似����
	������һ��¥��

ָ�perform sword.lianhuan

Ҫ��
	��ǰ�������� 1000 ���ϣ�
	����������� 12000 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	Ľ�ݽ����ȼ� 500 ���ϣ�
	��Ԫ�����ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	��������ΪĽ�ݽ�����
	�����м�ΪĽ�ݽ�����ת���ƣ�
	�����ڹ�Ϊ��Ԫ����
	����ָ��Ϊ�κ�ָ
	�ֳֽ����似
HELP
        );
        return 1;
}