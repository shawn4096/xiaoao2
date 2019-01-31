// longxiang.c
// modefied by emnil@sj 2/2/00

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me,int count);

int exert(object me, object target)
{
    int i,skill;
    i=(int)me->query("lx/gree");
	if ( !me->is_fighting())
		return notify_fail("��ֻ����ս���У��������������ӹ�������\n");

	if ( me->query_skill("longxiang-boruo", 1) < 350 || i<7)
		return notify_fail("ֻ��������������������߲�֮�󣬲�����ǿ�Լ��Ĺ�������\n");

	if ( me->query("max_neili") < 2500)
		return notify_fail("���������Ϊ̫��������ɡ�\n");

	if ( me->query("neili") < 1000 ) 
		return notify_fail("�������������\n"); 

	if ( me->query_temp("xs/longxiang"))
		return notify_fail("���Ѿ������������ӹ�������\n"); 

	 skill = me->query_skill("longxiang-boruo",1) /8;

	if ( me->query_temp("xs/shield")&& !me->query("quest/dls/longxiang/pass"))
		me->add("max_neili",-1);
//����������������
	if (me->query("lx/gree")==11)
    {
		skill=skill+me->query_skill("force",1)/8;
    }
	else if (me->query("lx/gree")==12)
	{
		skill=skill+me->query_skill("force",1)/7;
	}
	else if (me->query("lx/gree")==13)
	{
		skill=skill+me->query_skill("force",1)/6;
	}

	if(wizardp(me)) tell_object(me,sprintf("add attack: %d\n",skill));
	
	if (me->query("quest/dls/longxiang/pass")){
		message_vision(HBMAG+HIW"\n$NǱ����������������������޷��������"+CHINESE_D->chinese_number(i)+"����������������Ͷ�����д�������\n" NOR, me);
		skill=skill*2;
	}
	else message_vision(MAG"\n$NǱ�������������������ת����������"+CHINESE_D->chinese_number(i)+"��������ָ��糣������ɫ����Լ͸��һ�����ţ�\n" NOR, me);
	

	me->add_temp("apply/attack", skill);
	//�����඼ͳһ������shield��
	if (me->query("quest/dls/longxiang/pass"))
	{
		
		me->add_temp("apply/attack",skill/2);
        me->add_temp("apply/damage",skill/4);
		me->add_temp("apply/hammer",skill/2);
		me->add_temp("apply/strike",skill/2);
		me->add_temp("apply/strength",skill/15);
	}
	me->set_temp("xs/longxiang", skill);
	me->add("neili", -350);

	call_out("remove_effect", 1, me, skill/10);

//	me->start_busy(random(2));
	if (!me->query("quest/dls/longxiang/pass"))
		me->start_exert(1, "����");
	return 1; 
}

void remove_effect(object me,int count)
{
	int skill;
	if ( !me || !me->query_temp("xs/longxiang"))
		return;
    skill=me->query_temp("xs/longxiang");
	if ( count < 1 || !me->is_fighting()) {
		me->add_temp("apply/attack", -skill);
		if (me->query("quest/dls/longxiang/pass"))
	     {
	    	me->add_temp("apply/attack",-skill/2);
            me->add_temp("apply/damage",-skill/4);
		    me->add_temp("apply/hammer",-skill/2);
			me->add_temp("apply/strike",-skill/2);
			me->add_temp("apply/strength",-skill/15);
	     }
		me->delete_temp("xs/longxiang");
		message_vision(MAG"$N����һ����������������һ�����ָֻ��糣��\n" NOR, me);
		return;
	}
	call_out("remove_effect", 1, me,count - 1);
}

string exert_name(){ return MAG"����"NOR; }

int help(object me)
{
        write(MAG"\n���������֮�����󡹣�"NOR"\n\n");
        write(@HELP
���������֮�����󡹣�

	�ǡ���������ơ�����ʮ���㣬��һ�㹦��ʮ��ǳ�ף���������֮�ˣ�ֻҪ�õ����ڣ�
	һ�����м������ɡ��ڶ���ȵ�һ�����һ������ʱ�����ꡣ�������ֱȵڶ������
	һ������ʱ�߰��ꡣ��˳ɱ�������Խ����Խ�ѽ�չ��������������������һ�㣬
	����������ʮ�����Ͽ๦�������һ�ţ���ɮ��ʿ��������������һʮ���㡸�����
	��������ȴ��δ��һ������ʮ�����ϡ��⹦��ѭ�򽥽����������޲�������֮������
	���˵�����ǧ����䣬���ձ����ʮ���㾳�磬ֻ�������ޣ�������еĸ�ɮ��ʿ��
	����������֮ǰ�������߲㡢�ڰ˲㣬��ǵ�������ɣ���һ�����������������ٲ�
	��Ĵ�Σ����������䣬�·�����һλ��ɮ�����˵ھŲ㣬�������;�������������
	ʮ��ʱ����ħ�����޷����ƣ����ڿ���������ҹ���Ծ�����������
		
	�ǽ��ֹ�ʦʵ�Ǹ�����������ţ�Ǳ�޿�ѧ���������٣��������ƵھŲ��ѹأ���ʱ
	�ѵ���ʮ��ľ��磬���������˸���䲻��˵�������ߣ�ȴȷ��ǰ�޹��ˡ�����
	��������������Ե�����ʱÿһ�ƻ���������ʮ��ʮ��Ĵ���������֪�����������
	���������������������������޵��֣�����������ʮһ�㣬Ҳ�Ѷ��ࡣ�����⿪����
	���������ܣ��������������������𽭺���

	ָ��;exert longxiang

Ҫ��	
	��ǰ���������� 1000 ���ϣ�
	������������� 2500 ���ϣ�
	����������ȼ� 350 ����,
	�����������غ��ܷ��������������

HELP
        );
        return 1;
}