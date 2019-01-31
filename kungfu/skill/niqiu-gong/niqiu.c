//niqiu.c ��������pfm
//cre by sohu@xojh

#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me,object target)
{
	string msg;
	int i;
	if( !target ) target = offensive_target(me);
        else me->set_temp("offensive_target", target);
	if( me->query_skill("force",1) < 200 )
		return notify_fail("��Ļ����ڹ����������ʹ������������\n");  

	if( me->query_skill("niqiu-gong",1) < 200 )
		return notify_fail("������������������ʹ������������\n");  

	if (me->query_skill_mapped("dodge") != "niqiu-gong")
		return notify_fail("�������޷�ʹ����������\n");
	
	if( me->query("jingli", 1) < 200 )
		return notify_fail("�����ھ���������\n");

	if( me->query("neili", 1) < 200 )
		return notify_fail("����������������\n");

	if (me->query_temp("niqiu/fast"))
		return notify_fail("������ʹ����������\n");
    if (!me->is_fighting())
  		return notify_fail("������ֻ����ս���в���ʩչ��\n");
	if (!me->query("quest/shediao/nqg/pass"))
		return notify_fail("������ֻ��ͨ�����ܻ�������洫����ʩչ��\n");
	if ( me->query_skill("dodge",1) <200)
		return notify_fail("������������������޷�ʹ����������\n");

	msg = HIB"\nͻ����Ӱ�ζ���$N����һ��������������ת����Ť�������������֣����ٶ�ȴ���죬��Ȼ����$n���ϣ�\n"NOR; 

	me->add("neili", -100);
	me->add("jingli", -100);
	message_vision(msg, me,target);
	i = me->query_skill("niqiu-gong", 1)/5;
	
	me->add_temp("apply/dexerity", i/4);
	me->add_temp("apply/dodge", i/2);
	me->add_temp("apply/parry",i/2);
	
	me->set_temp("niqiu/fast", i);
	if (me->query_skill("niqiu-gong",1)<500)
	   me->start_perform(2, "������");
	
	call_out("remove_effect", 1, me,target, (int)me->query_skill("niqiu-gong", 1)/5);
	return 1;
}

void remove_effect(object me,object target, int count)
{
	int i;
	if (!me) return;
	
	i = me->query_temp("niqiu/fast");

	if (!objectp(target) 
		||me->query_skill_mapped("dodge") != "niqiu-gong"
		|| count-- < 1
		||!me->is_fighting())
	{
		me->add_temp("apply/dexerity", - i/4);
		me->add_temp("apply/dodge", -i/2);
		me->add_temp("apply/parry",-i/2);
		me->delete_temp("niqiu/fast");
		message_vision(HIB"$Nֹͣ������������ת�����ָ���������\n"NOR, me);
		return;
	}

    if (objectp(target)
		&& target->query("id")!=me->query("id")
		&& me->query_skill("qimen-bagua",1)>180
		&& me->is_fighting()
		&& !random(6)	
		&& random(me->query_skill("niqiu-gong",1))>target->query_skill("dodge",1)/2)
    {
		message_vision(HIB"$N������ϣ�$n����һ������æ��������$N���ֿ��֮�������ѳ���ֱ�ϣ�\n"
						+"˫����ָ��׶���ֽ�$n�ؿڡ���⡱�������顱��Ѩ��ȷ���ϳ˵�Ѩ����\n"NOR,me,target);
		target->add_busy(1+random(2));
		target->add_condition("no_exert",1);
    }
	
	call_out("remove_effect", 1, me,target,count);
}

string perform_name(){ return HIC"������"NOR; }

int help(object me)
{
        write(HIC"\n������֮������������"NOR"\n\n");
        write(@HELP
	���������������ں���̶�п�����������һ����
	�����ö�����Դ�ɾ�Ѱ��һ�Ƹ���Ĺ����У�����
	�Ŷ��ص��Ṧ���ӵ����쾡�¡������Ṧ�������أ�
	����һ������һ����������Ţ��ˮ�У�������硣
	
	ע�⣺set ������ ���� ����Ч���Ч��

	perform dodge.niqiu

Ҫ��
	��ǰ���� 200 ���ϣ�
	��ǰ���� 200 ���ϣ�
	�����Ṧ�ȼ� 200 ���ϣ�
	�����ڹ��ȼ� 200 ���ϣ�
	������Ϊ��������

HELP
        );
        return 1;
}
