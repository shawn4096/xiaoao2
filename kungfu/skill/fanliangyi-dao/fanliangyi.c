// fanliangyi.c ������
// ���з���
// by sohu
// ͨ��effect ����
#include <ansi.h>

inherit F_SSERVER;


int perform(object me, object target)
{
        int lvl;
        object weapon = me->query_temp("weapon");
        lvl =  (int)me->query_skill("fanliangyi-dao", 1);

        if( !target ) target = offensive_target(me);
     
        if( !target || !me->is_fighting(target) )
                return notify_fail("�������Ǿ���ֻ����ս���жԶ���ʹ�á�\n");

        if (!weapon || weapon->query("skill_type") != "blade"
			|| me->query_skill_mapped("blade") != "fanliangyi-dao")
                return notify_fail("������û�е����޷�ʹ�á������Ǿ�����\n");             

        if( (int)me->query_skill("fanliangyi-dao",1) < 450 )
                return notify_fail("��ķ����ǵ�������죬����ʹ�á������Ǿ�����\n");
      
        if( (int)me->query_skill("blade",1) < 450 )
                return notify_fail("��Ļ��������ȼ�����������ʹ�á������Ǿ�����\n");  

        if( (int)me->query_skill("poyu-quan", 1) < 450 )
                return notify_fail("�������ȭ���ȼ�����������ʹ�á������Ǿ�����\n");
      
        if( (int)me->query_skill("hushan-qigong", 1) < 450 )
                return notify_fail("��Ļ�ɽ�����ȼ�����������ʹ�á������Ǿ�����\n");


      
        if( (int)me->query("neili") < 1000 )
                return notify_fail("��ĵ�ǰ����̫���ˣ��޷�ʹ�ó��������Ǿ�����\n");   
        if( (int)me->query("jingli") < 1000 )
                return notify_fail("��ĵ�ǰ����̫���ˣ��޷�ʹ�ó��������Ǿ�����\n");                                                                                   
        if (me->query_skill_prepared("cuff") != "poyu-quan"
          || me->query_skill_mapped("cuff") != "poyu-quan")
                return notify_fail("�������޷�ʹ�á������Ǿ������й�����\n");
		if (me->query_temp("flyd/flyj"))
                return notify_fail("������ʩչ�������Ǿ�����\n");   

        message_vision(HIC"\n$N�������䣬ʩչ������ǰ��ȫ��ͬ����ʽ��·�����Ƿ����ǵ����еġ������Ǿ�������������ʱ���׽��������\n"NOR, me,target);
        me->add("neili", -(300+random(100))); 
        me->add("jingli", -100);      
        me->add_temp("apply/attack", lvl/4);
		me->add_temp("apply/blade", lvl/5);
		me->add_temp("apply/damage", lvl/5);
		me->add_temp("apply/parry", lvl/4);
		me->add_temp("apply/dodge", lvl/4);

		me->set_temp("flyd/flyj",lvl);

		call_out("remove_effect",0,me,(int)lvl/20);
		//me->start_perform(4 , "�������Ǿ���");
        return 1;
}

int remove_effect(object me,int count)
{
	int lvl;
	object weapon;
	if (!me) return 0;
	lvl=me->query_temp("flyd/flyj");
	weapon=me->query_temp("weapon");
	if (count<0
		||!me->is_fighting()
		||me->query_skill_mapped("blade")!="fanliangyi-dao"
		||me->query_skill_mapped("parry")!="fanliangyi-dao"
		||!weapon
		||weapon->query("skill_type")!="blade")
	{
        me->add_temp("apply/attack", -lvl/4);
		me->add_temp("apply/blade", -lvl/5);
		me->add_temp("apply/damage", -lvl/5);
		me->add_temp("apply/parry", -lvl/4);
		me->add_temp("apply/dodge", -lvl/4);

		me->delete_temp("flyd/flyj");
		message_vision(HIC"$N�������ʣ������Ǿ������������չ���\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me,count--);

}
string perform_name(){ return HBWHT+HIB"�����Ǿ�"NOR; }
int help(object me)
{
        write(HIC"\n�����ǵ�֮�������Ǿ�����"NOR"\n");
        write(@HELP
	���׵����Ĳ��������롸�����ɡ��ġ������ǽ�����һ����
	������������б仯���������а˰���ʮ�İ�仯������
	��ɽ�߰��������ڹ�����һս�����˷�֪���ⷴ���ǵ�Ҳ
	���˲��õľ�ѧ��
	�����Ǿ����Ƿ����ǵ���ѧ��ʩչ�����������ӵ�����
	������߲��ַ�����

	ָ�perform blade.fanliangyi

Ҫ��
	��ɽ��������ϼ�����ĵȼ� 450  ���ϣ�
	�����ǵ��ĵȼ� 450  ���ϣ�
	���������ĵȼ� 450  ���ϣ�
	����ȭ���ĵȼ� 450  ���ϣ�
	���Ű��Եĵȼ� 200  ����
	��ǰ������Ҫ�� 1000  ���ϣ�
	��ǰ������Ҫ�� 1000  ���ϣ�
	��������Ϊ�����ǵ���
	�����м�Ϊ�����ǵ���
	�����ڹ����ޣ�
	�ֳֵ���
HELP
        );
        return 1;
}
