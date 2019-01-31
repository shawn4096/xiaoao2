#include <ansi.h>

int exert(object me)
{
	int i;

	if (me->query_skill_mapped("force")!="jiuyin-zhengong")
	    return notify_fail("�㼤�����ڹ����ԣ��޷�ʩչ�����ܾ���\n");
	if(me->query_temp("jiuyin/powerup"))
		return notify_fail("��������ʹ�����ܾ���\n");
    if ((int)me->query_skill("force", 1) < 500)
		return notify_fail("��Ļ����ڹ���Ϊ��������\n");
	if ((int)me->query_skill("jiuyin-zhengong", 1) < 500)
		return notify_fail("��ľ����湦��Ϊ��������\n");

	if ((int)me->query_skill("daode-jing", 1) < 500)
		return notify_fail("��ĵ��¾���Ϊ��������\n");

	if( (int)me->query("neili") < 5000 )
		return notify_fail("�������������\n");
//Ϊʲô��force������jiuyin-zhengong���ж�ô��
	//i = me->query_skill("force")/5;
	i = me->query_skill("jiuyin-zhengong")/2;
	//i = i*3;
	me->add("neili", -500);
	//me->start_exert(3, "�����ܾ�");
	me->add_temp("apply/dodge", i);
    me->add_temp("apply/parry", i);
	me->add_temp("apply/defense", i*3/2);
	me->add_temp("apply/armor", i*3/2);
	me->add_temp("apply/attack", i);
	me->add_temp("apply/damage", i/3);
	//me->add_temp("apply/whip", i);
	me->add_temp("apply/strike", i);
	me->add_temp("apply/cuff", i);
	me->add_temp("apply/claw", i);
	me->set_temp("jiuyin/powerup", 1);
	message_vision(HBBLU+HIW"$N��������ܾ���������ת���������������γ�һ������������������Ȼ������\n"NOR, me);

	//if ( me->is_fighting())
		//me->start_busy(random(2));
	call_out("remove_effect", (int)me->query_skill("force")/4, me, i);
	return 1;
}

void remove_effect(object me, int i)
{
	if (!me) return;
	me->delete_temp("jiuyin/powerup");
	me->add_temp("apply/dodge", - i);
	me->add_temp("apply/attack", - i);
    me->add_temp("apply/parry", - i);
	me->add_temp("apply/defense", -i*3/2);
	me->add_temp("apply/armor", -i*3/2);
	me->add_temp("apply/damage", - i/3);
	//me->add_temp("apply/whip", - i);
	me->add_temp("apply/strike", - i);
	me->add_temp("apply/cuff", - i);
	me->add_temp("apply/claw", - i);
	message_vision(HIC"$N�ľ����ܾ���ʹ��ϣ������³�һ��������\n"NOR, me);
}

string exert_name(){ return HBBLU+HIW"�����ܾ�"NOR; }

int help(object me)
{
        write(HBBLU+HIW"\n�����湦֮�������ܾ�����"NOR"\n\n");
        write(@HELP
	�����澭���Ǳ�����ƽ�˻�����������״Ԫ���ڣ�ԭΪ�Ĺ٣�
	��У�ԡ����ء�����ͨ��ѧ����������ѱ���ǲ�������̣�
	�ٱ����ܰ��󣬻��Ѳ���������ƥ��ɱ�������̶��ˣ�����
	��������Ѱ�𡣻��Ѳ�����ȥ�����˾�����ɱ��Ϊѩ���
	��������40���꣬��˼�ƽ�����书֮����40����书���
	�����˾��ѷ׷�л�������Ѹп���ǧ�����Լ������书�γ�
	�������澭���������ᣬ�������䡣
	������澭Ϊ���֮�׵����������ã������ܲ�ͨ���䣬��
	ݱ�������������ܲ�ͨΪ��а��ƭ�����²���ߣ��ܲ�ͨ��
	�䲻����
	Ҫ��  
		��ǰ����ֵΪ 5000 ���ϣ�
		���¾��ĵȼ� 500 ���ϣ�
		�����ڹ��ȼ� 500 ���ϣ�
		�����湦�ȼ� 500 ���ϡ�
    ע�⣺
		set �����湦 ���� ��������������Է���Ч�˺��Լ�����
		
HELP
        );
        return 1;
}
