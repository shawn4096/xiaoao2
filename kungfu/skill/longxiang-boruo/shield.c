// shield.c
// changed by emnil@sj  2/2/2k
// changed by hunthu@sj 2/20/2001
#include <ansi.h>
inherit F_CLEAN_UP;

int exert(object me)
{
	int skill, skill1;
	
	if ((int)me->query_skill("longxiang-boruo", 1) < 250)
		return notify_fail("��������������Ϊ��������\n");

	if((int)me->query("max_neili") < 2500)
		return notify_fail("���������Ϊ̫��������ɡ�\n");

	if( (int)me->query("neili") < 1000 ) 
		return notify_fail("�����������Ҫǿ������֧�֣��������������\n");

	if (me->query_temp("xs/shield"))
		return notify_fail("���Ѿ��������������ˡ�\n"); 
    if (!me->query("quest/dls/longxiang/pass"))
    {	
		if (me->query_temp("xs/longxiang"))
			me->add("max_neili",-1);

    }
    
	skill = me->query_skill("longxiang-boruo",1) / 8;
    //��������ӳ�
	if (me->query("lx/gree")==11)
    {
		skill=skill+me->query_skill("force",1)/9;
    }
	else if (me->query("lx/gree")==12)
	{
		skill=skill+me->query_skill("force",1)/8;
	}
	else if (me->query("lx/gree")==13)
	{
		skill=skill+me->query_skill("force",1)/7;
	}

	if (me->query("quest/dls/longxiang/pass"))
	{
		message_vision(HBYEL+HIM "$N��������һ����������������ת���������ܷ·������һ�����ܣ�\n" NOR, me);
		
	}else message_vision(CYN"$N��������һ����������������ת���������ܷ·������һ�����ܣ�\n" NOR, me);

	

	me->add_temp("apply/dodge", skill);
	me->add_temp("apply/armor", skill);
	me->add_temp("apply/parry", skill);
    me->add_temp("apply/defense", skill);
	me->set_temp("xs/shield", skill);
	me->add("neili", -random(500));
	call_out("remove_effect",(int)skill*7/2,me);
	if( me->is_fighting() ) me->start_busy(random(2));
	if (!me->query("quest/dls/longxiang/pass")) me->start_exert(1, "����");
	return 1;
}

void remove_effect(object me)
{
        int amount;
        if (!me) return;
        amount = me->query_temp("xs/shield");

        if ( (int)me->query_temp("xs/shield") ) {
                me->add_temp("apply/dodge", - amount);
                me->add_temp("apply/armor", - amount);
				me->add_temp("apply/parry", - amount);
				me->add_temp("apply/defense", - amount);
                me->delete_temp("xs/shield");
                message_vision(RED "$N���Ϻ��һ�����ǽ�žž���켸����ɢȥ�˻���������\n" NOR, me);
	}
	return;
}

string exert_name(){ return CYN"����"NOR; }

int help(object me)
{
        write(CYN"\n���������֮�����ܡ���"NOR"\n\n");
        write(@HELP

	�ǡ���������ơ�����ʮ���㣬��һ�㹦��
	ʮ��ǳ�ף���������֮�ˣ�ֻҪ�õ����ڣ�
	һ�����м������ɡ��ڶ���ȵ�һ�����һ
	������ʱ�����ꡣ�������ֱȵڶ������һ
	������ʱ�߰��ꡣ��˳ɱ�������Խ����Խ
	�ѽ�չ��������������������һ�㣬��
	��������ʮ�����Ͽ๦�������һ�ţ���ɮ
	��ʿ��������������һʮ���㡸�����������
	ȴ��δ��һ������ʮ�����ϡ��⹦��ѭ��
	�����������޲�������֮�������˵�����		
	ǧ����䣬���ձ����ʮ���㾳�磬ֻ����
	���ޣ�������еĸ�ɮ��ʿ������������֮
	ǰ�������߲㡢�ڰ˲㣬��ǵ�������ɣ�
	��һ�����������������ٲ���Ĵ�Σ������
	����䣬�·�����һλ��ɮ�����˵ھŲ㣬
	�������;�������������ʮ��ʱ����ħ����
	�޷����ƣ����ڿ���������ҹ���Ծ�����������
	
	����ָ��:yun shield

Ҫ��

	��ǰ���� 1000 ���ϣ�
	������� 2500 ���ϣ�
	����������ȼ� 250 ���ϡ�
	�⿪�������⣬���������ʱ䡣

HELP
        );
        return 1;
}
