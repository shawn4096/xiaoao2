// youlong.c ����
// by sohu@xojh
//��һ�㶯�������
//��������aoto�����

#include <ansi.h>

inherit F_SSERVER;

void remove(object me,object target,int cs);

int perform(object me, object target)
{
        string msg;
        int skill; 
        

        if( !me->is_fighting() )
                return notify_fail("���������С�ֻ����ս��ʱʹ�ã�\n");
        if( (skill=(int)me->query_skill("youlong-shenfa",1)) < 300 )
                return notify_fail("�������������������������ʹ�á��������С���\n");

	if (me->query_skill_mapped("dodge") != "youlong-shenfa")
		return notify_fail("ֻ��ʩչ������ʱ����ʹ�á��������С���\n");
	if( (int)me->query_skill("dulong-dafa", 1) < 300 )
        return notify_fail("��Ķ����󷨹������㣬�����á��������С���\n");

	if( (int)me->query_skill("dodge", 1) < 300 )
        return notify_fail("��Ļ����Ṧ�������㣬�����á��������С���\n");
    if((int)me->query("jingli", 1)<1000)
		return notify_fail("�����ھ������㣬����ʹ�á��������С���\n");       
	if(((int)me->query("neili", 1)<1500) ) 
		return notify_fail("�������������㣬�����ٴ�ʹ�á��������С���\n"); 

    if (me->query_temp("ylsf/youlong")) return notify_fail("������ʹ�á��������С���\n"); 
	
   	msg = HIG "\n$N��Ȼ��һ����������������һ�㣬�������ߣ���������Ѹ����������\n"NOR; 
	message_vision(msg, me);
	me->add("jingli",-100);
	me->add("neili",-200);

	me->add_temp("apply/dodge",skill/6);
	me->set_temp("ylsf/youlong",skill);
	
	if (me->query("quest/sld/ylsf/youlong/pass")
		&&me->query_temp("dldf/dulong")
		&&me->is_busy())
	{
		message_vision(BLU"$N�о��Լ���Щæµ�������󷨶�����˲�䷢����ǿ��ʩչ�������е���ʽ\n����һ��������Ļ������֣�˲�仯�⣡\n"NOR,me);
		me->start_busy(-1);
	}

	call_out("remove_youlong",60,me,(int)skill/30);
    return 1;       
}

void remove_youlong(object me,int count)
{
	int skill;
	if (!me||!me->query_temp("ylsf/youlong")) return;
	skill=me->query_temp("ylsf/youlong");	
		me->add_temp("apply/dodge",-skill/6);
		me->delete_temp("ylsf/youlong");
		message_vision(BLU"$N������ͣ�����������λָ�������\n"NOR,me);
		return;		
}
string perform_name(){ return HIY"��������"NOR; }


int help(object me)
{
   write(HIG"\n������֮��"HIY"��������"NOR"����"NOR"\n");
   write(@HELP
	�������������������ص��Ṧ����ԭ������
	ģ�����εķ�ʽ����ս���ж����ͽ������𵽷�
	����Ҫ�ĸ����������á�
	����������ս��ʱ���л�����ѶԷ��Ĳ���ǣ��
	�˹�������ܷ���ϰ�á�	
   
	ָ�perform dodge.youlong

Ҫ��
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�������ȼ� 300 ���ϣ�
	������Ҫ�� 300 ���ϡ�
	�����ṦΪ��������
	�����ڹ�Ϊ�����󷨣�
	��ʹ��������������Լ�busy

HELP
   );
   return 1;
}

