// wugu.c ����ȭ��֮�������޹ǡ�
// Modified by sohu@xojh

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

string perform_name(){ return HIG"�����޹�"NOR; }

int perform(object me, object target)
{
	int skill;
	skill=me->query_skill("lingshe-quanfa",1);        
        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("�������޹ǡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");


	if( userp(me)&&( me->query_skill_mapped("force") != "hamagong"
        && me->query_skill_mapped("cuff") != "lingshe-quanfa") )
                return notify_fail("�������޹ǡ�����������ȭ����ϸ�󡹦����ʹ�á�\n");

        if( me->query_skill_prepared("cuff") != "lingshe-quanfa")
                return notify_fail("���ȭ�����ԣ����������ó��������޹ǡ���\n");  

        if( me->query_skill("lingshe-quanfa", 1) < 350 )
                return notify_fail("���ȭ����Ϊ��������\n");

        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("����������������Ӳ���������\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("���ȷ������е�������˵�ɣ���\n");     
	if (me->query_temp("lsqf/wugu"))
			return notify_fail("������ʩչ�������޹ǡ�����\n");  
    message_vision(BLU"\n$NĬ������ȭ"HIR"�������޹ǡ�"BLU"Ҫ����˲���ڻ��ͨ��ȭ���еġ��ᡱ�����족�����桱������⾳������ȭ��������������\n"NOR,me);


	me->add_temp("apply/cuff",skill/6);
    me->add_temp("apply/attack",skill/4);
	me->add_temp("apply/damage",skill/8);

	if (me->query_temp("hmg_nizhuan"))
	{
	
		message_vision(HIC"$N��ȭ֮�֣�ͻȻ�����ָ�������������ţ�һ��һ�죬������󡹦������ָ�䵯����$n��ʱȫ���飬��Ϣ������\n"NOR,me,target);
		target->apply_condition("no_exert",2);
		target->add_busy(3+random(2));
	}

	me->set_temp("lsqf/wugu",skill);
 
	me->add("neili", -450);
	me->add("jingli", -250);
	call_out("lingshe_auto",1,me,(int)skill/50);
	return 1;
}

int lingshe_auto(object me,int count)
{
	int skill;
	
	if (!me) return;
	skill=me->query_temp("lsqf/wugu");
	if (count<0
		||!me->is_fighting()
		||me->query_skill_mapped("cuff")!="lingshe-quanfa"
		||me->query_skill_prepared("cuff")!="lingshe-quanfa")
	{
		me->add_temp("apply/cuff",-skill/6);
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/8);
		me->delete_temp("lsqf/wugu");
		message_vision(BLU"$N���߾���һ�ɣ��������޹ǡ�����ʽһͣ�������չ���\n"NOR,me);
		return 1;
	}
	call_out("lingshe_auto",1,me,count--);
	
}
int help(object me)
{
   write(HIB"\n����ȭ��֮��"HIG"�����޹�"HIB"����"NOR"\n");
   write(@HELP
	Ϊ����ŷ����֮��ѧ���������ڵ�һ�λ�ɽ�۽���ܺ�Ϊ
	���»��۽�ʱ������ʤ���ο����߶�����������ȭ����ʩչ
	ʱ�����ֱ��鶯���ߣ������޹ǣ�Ҫּ�����ֱ��ƺ�������
	��������������ʹ������Ϊ�ѽ�������ȭ�ܿ���ʹ��ȭ�ķ�
	λ�Ե÷�����˼������ȴ����������֮��ͻȻ�任����
	�����ˣ�ʹ���˴�о��ȶ�ʧ���Ȼ���
	
	ָ�perform cuff.wugu

Ҫ��
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	����ȭ�� 350 ���ϣ�
	����ȭ�� 350 ���ϣ�
	�����ڹ� 350 ���ϣ�
	��󡹦   350 ���ϣ�
	����ȭ��Ϊ����ȭ����
	�����м�Ϊ����ȭ��
	���ֲ��ܳ���������

HELP
   );
   return 1;
}
