// bahuang.c by sohu@xojh �˻����� ������Ч

#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name(){ return HBYEL"�˻����Ͼ�"NOR; }

int exert(object me, object target)
{
	int skill;

	if( me->query("neili") < 500 )
		return notify_fail("�������������\n");
    if( me->query("max_neili") < 1500 )
		return notify_fail("����������������\n");
	if( me->query_skill("bahuang-gong", 1) < 100 )
		return notify_fail("��İ˻�����Ψ�Ҷ��𹦵ȼ�������\n");

	if( me->query_skill_mapped("force") != "bahuang-gong" )
		return notify_fail("����ڹ����ԡ�\n");

	if( me->query_temp("bhg/bahuang") )
		return notify_fail("���Ѿ����ˡ��˻�����Ψ�Ҷ����ˡ�\n");

	skill = me->query_skill("bahuang-gong",1);
	
    me->set_temp("bhg/bahuang",skill);
	
	me->receive_damage("neili", -300);
	
	message_vision(HBYEL+HIG "$N����Ϣ��������ʳָָ�죬����ʳָָ�أ����кٵ�һ�����ǿ����������������������\n" NOR, me);
    message_vision(HBYEL+HIG "��$N�˻�����Ψ�Ҷ�����ת֮�£�$Nֻ�����ܾ����������Լ�����ӿ�����������֣�����һ��"+HIR"��ǽ��\n" NOR, me);
	
	me->add_temp("apply/parry", skill/6); 

	if (me->query("bhg/biguan")==1) 
    {
		message_vision(HIG "$N�Ѿ����ϻ�ͯһ�Σ��о����������������\n" NOR, me);
        me->add_temp("apply/defense", skill/5); 
		me->add_temp("apply/armor", skill/5); 
    }
   if (me->query("bhg/biguan")==2) 
    {
		message_vision(HIY "$N�Ѿ����ϻ�ͯ���Σ��о�����������������\n" NOR, me);
        me->add_temp("apply/defense", skill/4); 
		me->add_temp("apply/armor", skill/4); 
        me->add_temp("apply/dodge", skill/4); 
    }
	if (me->query("bhg/biguan")==3) 
    {
		message_vision(HIR "$N�Ѿ����ϻ�ͯ���Σ��о����������Ȼ���������\n" NOR, me);
        me->add_temp("apply/defense", skill/3); 
		me->add_temp("apply/armor", skill/3); 
        me->add_temp("apply/dodge", skill/3); 
        me->add_temp("apply/dexerity", skill/10);
		me->add_temp("apply/parry", skill/3);
    }
	call_out("remove_effect", 1, me, skill);
	//�������֣��������ڶ�������
	me->start_exert(1, "�˻�����Ψ�Ҷ���");
	if( me->is_fighting() && me->query_skill("bahuang-gong",1)<450)
		me->start_busy(1+random(1));
	return 1; 
}

void remove_effect(object me, int count)
{
	int skill;

	if (!objectp(me)||!me->query_temp("bhg/bahuang")) return;
	skill = me->query_skill("bahuang-gong",1);

	if( !me->is_fighting()
		||count < 0 ) {
		if (me->query("bhg/biguan")==1) 
	    {
			me->add_temp("apply/defense", -skill/5); 
			me->add_temp("apply/armor", -skill/5); 
		}
		if (me->query("bhg/biguan")==2) 
		{
		
			me->add_temp("apply/defense", -skill/4); 
			me->add_temp("apply/armor", -skill/4); 
			me->add_temp("apply/dodge", -skill/4); 
		}
		if (me->query("bhg/biguan")==3) 
		{		
			me->add_temp("apply/defense", -skill/3); 
			me->add_temp("apply/armor", -skill/3); 
			me->add_temp("apply/dodge", -skill/3); 
			me->add_temp("apply/dexerity", -skill/10);
			me->add_temp("apply/parry", -skill/3);
		}
        me->add_temp("apply/parry",-skill/6); 
		me->delete_temp("bhg/bahuang");
		tell_object(me, HBYEL"��ġ��˻����Ϲ���������ϣ������������ջص��\n"NOR);
		return;
	}
		call_out("remove_effect", 1, me, count--);
			   
	
}

int help(object me)
{
	write(HIW"\n�˻�����Ψ�Ҷ���֮���˻����Ͼ�����"NOR"\n\n");
        write(@HELP
	�˻�����Ψ�Ҷ�����������ң���������ɾ���֮һ
	����ͯ���޳ִ˹���������ʦ�ֵı�ڤ�񹦡�ʦ����
	��ˮ������С�������࿹�⡣�˻�����Ψ�Ҷ���ԭ
	��������֮��ǿ���Ĺ�����ÿ��ʮ����Ҫ�չ�һ�Σ�
	���ϻ�ͯһ�Σ�ÿһ�η��ϻ�ͯ�չأ������ķ�����
	������������������������Ṧ�����������ԡ�
	ע�⣺450����ǰ�����ж�busy��
		
	ָ�yun bahuang
	
Ҫ��
	�������  1500 ���ϣ�
	��ǰ����  500  ���ϣ�
	�˻�����Ψ�Ҷ���  100  �����ϣ�
HELP
        );
        return 1;
}