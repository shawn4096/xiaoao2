// by darken@SJ
// Modify By River@SJ 2001.6.18

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
string perform_name(){ return HIW"һ��������"NOR; }
int perform(object me, object target)
{
	int skill = me->query_skill("quanzhen-jianfa", 1);
	object weapon = me->query_temp("weapon");  
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("һ��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_skill("force", 1) < 100 )
		return notify_fail("����ڹ����δ�����޷�ʩչһ�������壡\n");

	if( me->query_skill("dodge") < 100 )
		return notify_fail("һ�����������Ṧ��ϣ�����ʩչ��\n");

	if( me->query_skill("sword") < 100 )
		return notify_fail("�㽣�����δ�㣬�޷�ʹ��һ�������壡\n");

	if( me->query("neili") < 500 )
		return notify_fail("�����������ʹ��һ�������壡\n");

	if( me->query("jingli") < 150 )
		return notify_fail("��ľ�������ʹ��һ�������壡\n");

	if (me->query_temp("sanqing"))
		return notify_fail("������ʹ��һ�������壡\n");

	//if((int)me->query_temp("hebi"))
		//return notify_fail("������ʩչ˫���ϱڣ��޷�ʹ�á�һ�������塹������\n"); 

	if(!me->query_skill("xiantian-gong"))
		if(me->query_skill("yunu-xinjing", 1) < 100)
			return notify_fail("����ڹ���򲻹����޷�ʹ��һ�������塣\n");

	if (!weapon 
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "quanzhen-jianfa"
	|| (me->query_skill_mapped("parry") != "quanzhen-jianfa" && me->query_skill_mapped("parry") != "kongming-quan" ))
		return notify_fail("�������޽�����ʹ��һ�������壿��\n");

	msg = HIC"\n$N���н����Ȼ���߲��������һ����Х��ʹ��ȫ�潣���еľ���һ�������壬����ֳ����㣬����$n��\n" NOR;

	if (me->query("family/family_name")=="ȫ���")
	{
		if (me->query_skill("quanzhen-jianfa",1)<350)
			skill = skill+me->query_skill("xiantian-gong",1);
		else 
			skill = skill+me->query_skill("xiantian-gong",1)/2;
	}		

	if (me->query("family/family_name")=="��Ĺ��"&& me->query_skill("quanzhen-jianfa",1)<350&& me->query("gender")=="����")
	{
		msg += HIM"\n$N����Ů�ľ������Ṧ��������ȫ�潣���У���һ��������ʹ��ȴҲ����ģ������\n" NOR;
		skill = skill+me->query_skill("yunu-xinjing",1)/3;
	}
	message_vision(msg , me, target);
	me->set_temp("qzjf/sanqing",skill);
	me->add_temp("apply/attack", skill/3 );
	me->add_temp("apply/damage", skill/5 );
	me->add("neili", -300);
	me->add("jingli", -100);
	me->set_temp("sanqing", 1);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	me->start_perform(4,"һ��������");
	call_out("check_fight", 1, me, target, weapon, skill/30);
	return 1; 
}

void check_fight(object me,object target,object weapon,int count)
{
	int skill;
	if(!me) return;
	else skill = me->query_temp("qzjf/sanqing");

	if(!target
	|| !me->is_fighting(target)
	|| !weapon
	|| me->query_skill_mapped("sword") != "quanzhen-jianfa"
	|| count < 3 ){
		message_vision(HIW"\n�⼸��һ���ǳɣ��������������Ƴ��ȣ�ȡ��������壬����ȫ�潣���еľ������ڡ�\n\n"NOR, me);
		me->delete_temp("sanqing");
		me->add_temp("apply/attack", -skill/3);
		me->add_temp("apply/damage", -skill/5);
		return;
	}
	else {
		me->set_temp("sanqing", 1);
		if (me->query_skill("xiantian-gong", 1) > 100) 
		{
			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		}
		if (me->query_skill("xiantian-gong", 1) > 150) 
		{
			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		}
		if (me->query_skill("xiantian-gong", 1) > 200) 
		{
			if (me->is_fighting(target)){
				me->add_temp("apply/attack",me->query_skill("xiantian-gong",1)/10);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				me->add_temp("apply/attack",-me->query_skill("xiantian-gong",1)/10);
			}
		}
		me->delete_temp("sanqing");
		me->start_perform(3,"һ��������");
	}  
	call_out("check_fight", 2, me, target, weapon, count - 3);  
}

int help(object me)
{
        write(HIG"\nȫ�潣��֮"+HIW"��һ�������塹��"NOR"\n\n");
        write(@HELP
		Ҫ��  ��ǰ���� 500 ���ϣ�
			������� 1000 ���ϣ�
			��ǰ���� 150 ���ϣ�
			ȫ�潣���ȼ� 100 ���ϣ�
			���칦�ȼ� 100 ���ϣ�
			���������ȼ� 100 ���ϣ�
			�����Ṧ�ȼ� 100 ���ϣ�
			��������Ϊȫ�潣����
			�����м�Ϊȫ�潣�������ȭ��
			�����ڹ�Ϊ���칦��
			�������˳����书��ע��200����250���������ʵ��ķ�Ծ
			��ȫ������������칦����������������
HELP
        );
        return 1;
}
