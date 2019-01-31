// xixing.c ���Ǵ�

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string exert_name(){ return HIR"���Ǿ�"NOR; }

int exert(object me)
{
	int skill, i;

	if( (int)me->query("neili") < 2000  ) 
		return notify_fail("�������������\n");
	if( (int)me->query_skill("xixing-dafa",1) < 100  ) 
		return notify_fail("������Ǵ󷨵ȼ�������\n");
	if( (int)me->query_skill("force",1) < 100  ) 
		return notify_fail("��Ļ����ڹ��ȼ�������\n");
	
	if( (int)me->query_temp("xxdf/xixing") ) 
		return notify_fail("���Ѿ����˹����ˡ�\n");

    skill = (int)me->query_skill("xixing-dafa",1);
    i=skill;
	
	me->add("neili", -200+random(200));
    message_vision(HBBLU+HIW "\n$N����һ�ۣ����Ǵ��񹦷�����һ�ɾ�����$N������ת��Ϣ���γ�һ���������ֵ�������\n" NOR, me);
    
//���Ǵ󷨾�������
	if (me->query("quest/xxdf/pass")==2)
    {
      message_vision(HBBLU+HIW "\n$N�Ѿ����������е��洫�����Լ������������������ںϣ�����������\n" NOR, me);
      i=i+(int)me->query_skill("xixing-dafa",1)/5;
      me->add_temp("apply/defense", i/6);
	  me->add_temp("apply/armor", i/6);
	  me->add_temp("apply/damage", i/10);
    }
	
	me->set_temp("xxdf/xixing", i);

	me->add_temp("apply/attack", i/4);
	//me->add_temp("apply/dexerity", i/10);	
    me->add_temp("apply/parry", i/5);

    
	call_out("remove_effect", 1, me, (int)skill/15);

	if( me->is_fighting() && me->query_skill("xixing-dafa",1)<450 ) me->start_busy(1+random(1));
	me->start_exert(1,"���Ǵ�");
	return 1;
}

void remove_effect(object me, int count)
{    
     int amount;
	 if (!me) return;
	 
	 amount = me->query_temp("xxdf/xixing");

	 if( count < 0 || !me->is_fighting()) 
	 {

		me->add_temp("apply/attack", - amount/4);
	// me->add_temp("apply/dexerity", - amount/10);
		me->add_temp("apply/parry", - amount/5);
	
		if (me->query("quest/xxdf/pass")==2)
		{          
			me->add_temp("apply/defense",- amount/6);
			me->add_temp("apply/armor", - amount/6);
			me->add_temp("apply/damage",- amount/10);
		}
		me->delete_temp("xxdf/xixing");
		message_vision(HBBLU+HIW "\n$N��"HIR"���Ǵ�"HIC"������ϣ��������ջص��\n" NOR, me);
		//tell_object(me, HIC"\n���"HIR"���Ǵ�"HIC"������ϣ��������ջص��\n"NOR);
		return;
	 
	 }
     call_out("remove_effect", 2, me, count-1);
     return;      
    
}
int help(object me)
{
        write(HIR"\n���Ǵ�"+HIB"�����Ǿ���"NOR"\n");
        write(@HELP
	���Ǵ������������ǰ���������е��ش��似���뵱����������������񼼣�
	��һΪ�������䣬���Ϊ���Ǵ󷨣�ǰ�˽�����������λʱѡ����ϰ���Ǵ󷨡�
	��Ȼ�����ݺ��������ܵ����ɣ������Ǵ󷨵Ĺ����ǿ��Ҳ����ѡ�����Ҫԭ��
	�����ڣ�������Ϊ̸֮��ɫ�䡣����������������һս�������Ǵ��س�����
	�ɼ�������������
	��ӹ�������������޶���Ц�������н����Ǵ󷨹����ڱ�ڤ�񹦣������ڱ�վ
	�����Ǵ��У�����ǿ�����ǵ��ص㡣��վ���Ǵ��ܹ���Ϊ�������⡣
	��һ�Σ���÷ׯ�гɹ���������У����ڵ������ƽ����⡣
		��Ҫ��Ч;���ӷ��������Լ���Ӧ����				
	�ڶ��Σ��ɹ���ʦ�����в��������������ָ�㡾�ڹ�����Ψ��������̵��ӿ���
		��Ч;�������������������������Ч������
	
Ҫ��
	�����ڹ��ȼ� 100 ���ϣ�
	���Ǵ󷨵ȼ� 100 ���ϣ�
	350��С�ɣ�450���ɡ�

HELP
        );
        return 1;
}
