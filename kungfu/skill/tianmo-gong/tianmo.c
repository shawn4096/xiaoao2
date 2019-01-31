// tianmo.c ��ħ��
// action@SJ 2009/1/17

#include <ansi.h>
inherit F_CLEAN_UP;
string exert_name(){ return HIR"��ħ��"NOR; }

int exert(object me, object target)
{
	int skill;

	if( me->query("neili") < 1000 )
		return notify_fail("�������������\n");

	if( me->query_skill("tianmo-gong", 1) < 150 )
		return notify_fail("�����ħ���ȼ�������\n");

	if( me->query_skill_mapped("force") != "tianmo-gong" )
		return notify_fail("����ڹ����ԡ�\n");

	if( me->query_temp("tmg/tianmo") )
		return notify_fail("���Ѿ����ˡ���ħ�󷨡��ˡ�\n");

	skill = me->query_skill("force")/3;
	if( skill > 150 ) skill = 150;

	me->receive_damage("neili", -300);
	message_vision(HIR"$Nһ����Х��˫Ŀ��ó�죬˫��һ�㣬�����ڿն������ܶ�ʱ���˷�ӿ�������ѵ�����\n" NOR, me);

    me->set_temp("tmg/tianmo",1); 
    me->add_temp("apply/armor", me->query_skill("tianmo-gong", 1)/6); 
    me->add_temp("apply/attack", me->query_skill("tianmo-gong", 1)/5);
    me->add_temp("apply/blade", me->query_skill("tianmo-gong", 1)/6); 
	//me->add_temp("apply/armor", me->query_skill("tianmo-gong", 1)/3); 
	call_out("remove_effect", 1, me, skill);
	
	me->start_exert(1, "��ħ��");
	if( me->is_fighting()&&me->query_skill("tianmo-gong")<450 )
		me->start_busy(random(2));
	return 1;
}

void remove_effect(object me, int count)
{
	int amount;
	if( objectp(me) && me->query_temp("tmg/tianmo") ) {
		if( count-- > 0 ) {
			call_out("remove_effect", 1, me, count);
			return;
		}
		amount = me->query_temp("tmg/tianmo");
		me->add_temp("apply/armor", -me->query_skill("tianmo-gong", 1)/6);
		me->add_temp("apply/attack",-me->query_skill("tianmo-gong", 1)/5);
        me->add_temp("apply/blade", -me->query_skill("tianmo-gong", 1)/6); 
        me->delete_temp("tmg/tianmo");
		tell_object(me, HIW"���["+HIR+"��ħ��"+HIW+"]������ϣ��������ջص��\n"NOR);
	}
}

int help(object me)
{
	write(HIR"\n��ħ��֮����ħ�󷨡���"NOR"\n\n");
        write(@HELP
	��ħ������������̵������ڹ��������г���
	�����ܽ��������ɣ��ʺ����ŵ�����������
	������󣬸�����������̵��似Ҳ��������
	�ϲ�����������
	��ħ����ת֮�󣬻���Ч�������кͷ�����
	������ڵ����ж���ĸ������á�
	Ҫ��  
		�������  2000 ���ϣ�
		��ǰ����  1000 ���ϣ�
		��ħ��    150  ���ϣ�
HELP
        );
        return 1;
}