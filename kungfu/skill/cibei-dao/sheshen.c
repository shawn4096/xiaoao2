// This program is a part of NITAN MudLIB
// sheshen.c ������ιӥ��

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me,int count);

int perform(object me)
{
        object weapon;
        int skill;
        string msg;

        if (userp(me) && ! me->query("quest/sl/cbd/pass"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ������ιӥ����\n");
        
		if ((int)me->query_skill("cibei-dao", 1) < 250)
                return notify_fail("��Ĵȱ�����������죬����ʹ�á�����ιӥ����\n");
        if ((int)me->query_skill("blade", 1) < 250)
                return notify_fail("��Ļ�������������죬����ʹ�á�����ιӥ����\n");

        if ((int)me->query("neili") < 500 )
                return notify_fail("��������������޷�ʹ�á�����ιӥ����\n");
		if (me->query_skill_mapped("blade")!="cibei-dao")
		        return notify_fail("��û�м����������м�Ϊ�ȱ������޷�ʹ�á�����ιӥ����\n");

        if ((int)me->query_temp("cbd/sheshen"))
                return notify_fail("���Ѿ����˹����ˡ�\n");
        if (me->query_skill_mapped("parry")!="cibei-dao")
                return notify_fail("��û���мܴȱ�����\n");

        if (!objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        skill = me->query_skill("cibei-dao", 1);
		if (me->query_skill_mapped("force")=="yijin-jing")
		{
			skill=skill+me->query_skill("yijing-jing",1)/3;
			message_vision(RED"$N�����־�ѧ�׽���ȱ���������������\n"NOR,me);
		}
        msg = YEL "$N" YEL "ʹ���ȱ�����������ιӥ����������Ĺ������˵�" +
              weapon->query("name") + YEL "�ϣ�����һƬ����,���������ˮй��ͨ��\n" NOR;
        
		message_vision(msg, me);
	
        me->add_temp("apply/attack", skill / 3);
        me->add_temp("apply/defense", skill / 4);
		me->add_temp("apply/parry", skill / 4);
		me->add_temp("apply/armor", skill / 4);
		me->add_temp("apply/armor", skill / 4);

        me->set_temp("cbd/sheshen", skill);

        call_out("remove_effect",1,me,skill/50);

        me->add("neili", -100);
        //if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me,int count)
{
	int skill;
	if (!me) return;
	if (me->query_temp("cbd/sheshen")==0) return;
	
	skill=me->query_temp("cbd/sheshen");

	if (count<0
		||me->query_skill_mapped("parry")!="cibei-dao"
		||!me->is_fighting())
	{
        me->add_temp("apply/attack", -skill / 3);
        me->add_temp("apply/defense", -skill / 4);
		me->add_temp("apply/parry", -skill / 4);
		me->add_temp("apply/armor", -skill / 4);
		me->add_temp("apply/armor", -skill / 4);
        me->delete_temp("cbd/sheshen");
        tell_object(me, "��ġ�����ιӥ��������ϣ��������ջص��\n");
		return;
    }
	call_out("remove_effect",1,me,count--);

}
string perform_name(){ return YEL"����ιӥ"NOR; }
int help(object me)
{
         write(HIB"\n�ȱ�����֮������ιӥ����"NOR"\n");
        write(@HELP
	����ιӥ��ѡ�Է�̾�����£������̺��ἺΪ�˵Ĵ�����ѧ
	�ȱ�����������ǿ����Ҫ���Ƿ�������ʹ���к󣬵����еĴ�
	��֮����ԣ�����������������ϰ�׽������������
	ע�⣺��������������ͯ���Ĺۺ���֮��ѧ,���������� 
	
	ָ�perform blade.sheshen

Ҫ��
	�ȱ�������450
	����������450
	��ǰ������500
	�輤���мܴȱ�����       
HELP
        );
        return 1;
}
