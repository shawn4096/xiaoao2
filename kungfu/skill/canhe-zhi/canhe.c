// canhe.c �κϾ�
// cre by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string *xue1 = ({ 
        "��׶Ѩ",
        "�ٻ�Ѩ",
        "־��Ѩ",
        "�羮Ѩ",
        "�͹�Ѩ",
        "�ڹ�Ѩ",
        "���Ѩ",
        "����Ѩ",
});



int perform(object me, object target)
{
	string msg,xuename;
	int i,skill;
	skill=me->query_skill("canhe-zhi",1);
	i=skill/100;
	xuename=xue1[random(sizeof(xue1))];
	if( !target ) target = offensive_target(me);

    if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
		return notify_fail("���κϾ���ֻ����ս����ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("��������ʹ�á��κϾ�����\n");

	if( (int)me->query_skill("canhe-zhi",1) < 400 )
		return notify_fail("��Ĳκ�ָ������죬����ʹ�á��κϾ�����\n");

	if( (int)me->query_skill("shenyuan-gong",1) < 400 )
		return notify_fail("�����Ԫ���ȼ�����������ʹ�á��κϾ�����\n");

	if( (int)me->query_str(1) < 50 )
		return notify_fail("��ı�������ǿ������ʹ�á��κϾ�����\n");

	if( (int)me->query("max_neili") < 8000 )
		return notify_fail("�������̫��������ʹ�á��κϾ�����\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("�������̫���ˣ��޷�ʹ�ó����κϾ�����\n");

	if (me->query_skill_prepared("finger") != "canhe-zhi"
	|| me->query_skill_mapped("finger") != "canhe-zhi")
		return notify_fail("�������޷�ʹ�á��κϾ������й�����\n");

    if ( me->query_skill_mapped("force") != "shenyuan-gong")
        return notify_fail("û����Ԫ��֧�����ʹ�á��κϾ�����\n");
	if ( me->query_skill_mapped("parry") != "canhe-zhi"
	&& me->query_skill_mapped("parry") != "douzhuan-xingyi")
		return notify_fail("�������޷�ʹ�á��κϾ������й�����\n");

	if( me->query_temp("chz/canhe"))
		return notify_fail("������ʹ�òκ�ָ�����⹥�����κϾ�����\n");
	//if( me->query_temp("chz/ci"))
		//return notify_fail("������ʹ�òκ�ָ�����⹥�����κϾ�����\n");
	msg = HIC"\n$NĬ��κ�ָ��������"HIR"��"HIC"�����ͷ�����"HIB"��"HIC"�������������ߵ����з���"+chinese_number(i)+"�Ρ�\n"+
		"�����ɵ�����������������������ɾ�������ڡ�"HIY+xuename+HIC"�������ƴ�����\n" NOR;
	message_vision(msg, me);

	me->set_temp("chz/canhe", skill);
	me->set_temp("chz/xuewei",xuename);
	
	me->add_temp("apply/attack",skill/5);
	me->add_temp("apply/finger",skill/5);
	me->add_temp("apply/damage",skill/5);
	call_out("check_fight",1,me,(int)skill/20,xuename);
	
	return 1;
}

void check_fight(object me, int count,string xuename)
{
	int skill;
	if(!me) return;
	
	skill=me->query_temp("chz/canhe");
	
	if(!me->is_fighting()
	|| me->query_skill_mapped("finger") != "canhe-zhi"
	|| me->query_skill_prepared("finger") != "canhe-zhi"
	|| me->query_temp("weapon")
	|| count < 0 )
	{
	
		me->add_temp("apply/attack",-skill/5);
		me->add_temp("apply/finger",-skill/5);
		me->add_temp("apply/damage",-skill/5);
		me->delete_temp("chz/canhe");
		message_vision(HIC"$N�������"HIY+xuename+HIC"�������������ͷţ��ع鵤�\n"NOR,me);
		me->add_busy(2);
		me->start_perform(3, "���κϾ���");
		return;
	}
	call_out("check_fight", 1, me, count--,xuename);
}

string perform_name(){ return HBCYN+HIR"�κϾ�"NOR; }

int help(object me)
{
        write(HIC"\n�κ�ָ֮���κϾ���"NOR"\n\n");
        write(@HELP
	�κ�ָ����Ľ���ϵľ�ѧ�������������ת���ƣ�����Ľ��
	�Ҵ��ľ����似���κ�ָ��ǿ�������������������������
	�Է���������ϰ�òκ�ָ�ľ����ؼ���������������������
	�ɵ�ָ��������
	�κϾ��ǽ�Ľ���϶��ص��������������Ѱ�ҶԷ���������
	��ǿ������ص���������ָ�������������ش���

ָ�perform finger.canhe

Ҫ��
	��ǰ���� 1000 ���ϣ�
	������� 8000 ���ϣ�
	�κ�ָ�ȼ� 400 ���ϣ�
	��Ԫ���ȼ� 400 ���ϣ�
	����ָ��Ϊ�κ�ָ��
	�м�Ϊ�κ�ָ��ת����
	��ָ��Ϊ�κ�ָ��
	��ǰ������С��50��
	�����ޱ���,

HELP
        );
        return 1;
}
                                
