//wuji.c

#include <ansi.h>
void remove_effect(object me,int skill);


string exert_name() {return HIW"�����޼�"NOR;}

int exert(object me)
{      
    int skill;
    skill = me->query_skill("xuantian-wuji", 1)/10;
       
	if ( !me->is_fighting())
		return notify_fail("��ֻ����ս����ʹ�á��޼�����\n");

	if( (int)me->query_skill("xuantian-wuji", 1) < 180 )
		return notify_fail("��������޼�����Ϊ�������޷�ʹ�á��޼�����\n");

	if (me->query_skill_mapped("force") != "xuantian-wuji")
		return notify_fail("�����ڹ��С������޼�����\n");

	if( (int)me->query("neili") < 300 )
		return notify_fail("��Ŀǰ������̫���ˣ��޷�ʹ�á������޼�����\n");

	if( (int)me->query("max_neili") < 1500 )
		return notify_fail("���������Ϊ��ô�����ʹ�á������޼�����\n");

    if(me->query_temp("xtwj/riyue"))
		return notify_fail("���������á������޼����ķ���\n");   
	

	message_vision(HIC "$N���������޼��ķ���ֻ��$Nȫ��һ���������ֵ���������������ƮȻ���ɡ�\n" NOR, me);
    me->add_temp("apply/parry", me->query_skill("xuantian-wuji", 1)/2);
    me->add_temp("apply/armor", me->query_skill("xuantian-wuji", 1)/2);
	
	me->add("neili", -300);
    
	me->set_temp("xtwj/riyue",skill);
	
	
	if (me->query_skill("xuantian-wuji",1)<450)
    {
		me->start_exert(2, "���޼���");
    }
	call_out("remove_effect", 1, me, skill);
	return 1;
}

void remove_effect(object me, int count)
{
	
	 if (objectp(me)) {
        if  ( !me->is_fighting() || count < 0 ) {
			
        
			me->delete_temp("xtwj/riyue");
			me->add_temp("apply/parry", -me->query_skill("xuantian-wuji", 1)/2);
			me->add_temp("apply/armor", -me->query_skill("xuantian-wuji", 1)/2);
			message_vision(HIC"\n$N�������޼���������ϣ��������ջص��\n"NOR, me);
			return;
		}
		call_out("remove_effect", 2, me, count -1);
        return;

	}
}


int help(object me)
{
        write(WHT"\n�����޼����������޼�����"NOR"\n");
        write(@HELP
	�ˡ��޼���һʽ���������������ڹ��ķ������޼�����Ϊ������
	���������������¾���Ϊ�޼����ܣ�������������ͬʱ����
	����ʹ�Է�������Ч��
	
	exert wuji

Ҫ��:
	�����޼��� 180 �����ϣ�
	������� 1500 �㣻
	��ǰ���� 300 �㣻
              
HELP
        );
        return 1;
}


