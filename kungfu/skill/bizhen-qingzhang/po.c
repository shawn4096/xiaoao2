// po.c �������ƾ��У�������
// By sohu

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    object weapon;
    int damage, dp;
    string msg;

    if( !target ) target = offensive_target(me);

    if( !target || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("�������ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if( (int)me->query_skill("bizhen-qingzhang", 1) < 200 )
        return notify_fail("��ı������Ʋ�����죬����ʹ�á������ơ���\n");

    if( (int)me->query_skill("strike", 1) < 200 )
        return notify_fail("��Ļ����Ʒ��ȼ��������޷�ʹ���������ơ���\n");
    if( (int)me->query_skill("force", 1) < 200 )
        return notify_fail("��Ļ����ڹ��ȼ��������޷�ʹ���������ơ���\n");
    if( me->query_skill_mapped("strike")!="bizhen-qingzhang" 
		||me->query_skill_prepared("strike")!="bizhen-qingzhang" )
        return notify_fail("�㼤�����Ʒ����ԣ��޷�ʹ���������ơ���\n");

    if( (int)me->query("neili", 1) < 1000 )
        return notify_fail("����������̫����ǿʹ�������������棡\n");

    message_vision( HIG "$N˫���������ɡ������ơ��û���һ����Ӱ��ͻȻ���������£��γ�һ��������������״��ֱ��$n����Ҫ����\n"NOR,me,target);

    if (living(target))
           dp = target->query_skill("force",1)/2;
    else    dp = target->query_skill("force",1)/4;

    if (random(me->query_skill("force",1)) > dp
		||random(me->query_str(1))>target->query_str(1)/2)
    {

        damage = (int)me->query_skill("bizhen-qingzhang", 1) + (int)me->query_skill("force",1);
		damage=me->query("str")*damage/10;
        damage = damage + random(damage) ;
		
        target->receive_damage("qi", damage,me);
		target->apply_condition("neishang",2);
        target->start_busy(4);
        message_vision(HIR"$Nֻ��ȫ���Ѩ������̣���ͷһ�𣬿�����Ѫ����������\n"NOR,me);
    }
    else
    {
        me->start_busy(1);
        message_vision(CYN"$N���Ʋ����æ�ŵ�һ�����Ǳ���״�ı��˿�ȥ��\n"NOR,target);
    }
	me->start_perform(3,"������");
	me->add("neili", -300);
    me->add("jingli", -100);

    return 1;
}
string perform_name() {return HIC"������"NOR;}

int help(object me)
{
   write(HIC"\n��������֮��" HIG"������"HIC"����"NOR"\n\n");
   write(@HELP
	����������Ħ���ʿл�̿͵Ķ����ؼ���һ��ʩչ
	��������ſգ�������Ϊ��ӿ�������Ʒ����쳣��
	�ص�һ�ֹ�������������������һ�㣬Ȼ��˲�䱬
	�ƣ����Է�������˵�һ����ʽ��
	
	ָ�perform strike.po

Ҫ��: 
	��ǰ�������� 1000 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	�������Ƶȼ� 200 ���ϣ�
    �����ڹ��ȼ� 200 ���ϣ�
	�����Ʒ��ȼ� 200 ���ϣ�
	�����Ʒ�Ϊ�������ƣ�
	�ڹ����ޣ�
	���֣����������ơ�

HELP
   );
   return 1;
}



