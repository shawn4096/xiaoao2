// jieti.c ��ħ����
// action@SJ 2009/1/17

#include <ansi.h>
inherit F_CLEAN_UP;
string exert_name(){ return HBRED"��ħ����"NOR; }

int exert(object me, object target)
{
	int skill;

	if( me->query("max_neili") < 3500 )
		return notify_fail("��Ĺ���������\n");
    if( me->query("neili") < 1500 )
		return notify_fail("�������������\n");
	if( me->query_skill("tianmo-gong", 1) < 250 )
		return notify_fail("�����ħ���ȼ�������\n");

	if( me->query_skill_mapped("force") != "tianmo-gong" )
		return notify_fail("����ڹ����ԡ�\n");
    if (me->query_temp("tmg/tianmo"))
		return notify_fail("���Ѿ�����ʹ�á���ħ����󷨡��ˡ�\n");
	if( me->query_temp("tmg/jieti") )
		return notify_fail("���Ѿ����ˡ���ħ����󷨡��ˡ�\n");

	skill = (int)me->query_skill("tianmo-gong")/100;
	if( skill < 2 ) skill = 2;

	me->receive_damage("neili", -500);
	message_vision(BRED"$N���쳤Х��������ħ����󷨣�˫Ŀ��ó�죬��ɫ��죬�����Ѫ���������\n" NOR, me);

    me->set_temp("tmg/jieti",1); 
    me->add_temp("apply/strength", (int)me->query_skill("tianmo-gong", 1)/20); 
	me->add_temp("apply/armor", me->query_skill("tianmo-gong", 1)/6); 
   	me->add_temp("apply/damage", me->query_skill("tianmo-gong", 1)/4); 
	me->add_temp("apply/club", me->query_skill("tianmo-gong", 1)/5);
	me->add_temp("apply/axe", me->query_skill("tianmo-gong", 1)/5);
	me->add_temp("apply/blade", me->query_skill("tianmo-gong", 1)/5);
	me->add_temp("apply/strike", me->query_skill("tianmo-gong", 1)/5);
	me->add_temp("apply/throwing", me->query_skill("tianmo-gong", 1)/5);
	me->add_temp("apply/sword", me->query_skill("tianmo-gong", 1)/5);
	call_out("remove_effect", 1, me, skill);
	me->start_exert(1, "��ħ����");
	if( me->is_fighting() )
		me->start_busy(random(2));
	return 1;
}

void remove_effect(object me, int count)
{
	//int amount;
	//message_vision(HIR"$N������Ѫ���Ϸɽ�����ȫ������ȴԽ��Խǿ��\n"NOR);
	count=count-1;
	if( objectp(me) && me->query_temp("tmg/jieti") ) {
		if( count>0 )
		{
			
			if (!random(5))
			{
              message_vision(HIR"$N������Ѫ���Ϸɽ�����ȫ������ȴԽ��Խǿ����\n"NOR,me);
			  me->receive_damage("qi",random(500),me);
			}
			call_out("remove_effect", 2, me, count);
			return;
		}
		//amount = me->query_temp("tmg/jieti");
		
        me->add_temp("apply/strength", -(int)me->query_skill("tianmo-gong", 1)/20); 
		me->add_temp("apply/armor", -me->query_skill("tianmo-gong", 1)/6); 
     	me->add_temp("apply/damage", -me->query_skill("tianmo-gong", 1)/4); 
		me->add_temp("apply/club", -me->query_skill("tianmo-gong", 1)/5);
	    me->add_temp("apply/axe", -me->query_skill("tianmo-gong", 1)/5);
		me->add_temp("apply/blade", -me->query_skill("tianmo-gong", 1)/5);
		me->add_temp("apply/strike", -me->query_skill("tianmo-gong", 1)/5);
		me->add_temp("apply/throwing", -me->query_skill("tianmo-gong", 1)/5);
		me->add_temp("apply/sword", -me->query_skill("tianmo-gong", 1)/5);
        me->add("max_neili",-2-random(3));
		me->receive_wound("qi",random(2000),"��ħ����͸֧��");
		me->delete_temp("tmg/jieti");
		me->add_condition("hmy_jieti",(int)count);
		tell_object(me, BRED"���["+BRED+"��ħ����"+NOR+"]������ϣ��������ջص����������ή�Ҳ�����Ȼ�Ѿ������ܵ����ص��˺���\n"NOR);
	}
}


int help(object me)
{
	write(HBRED"\n��ħ��֮����ħ���塹��"NOR"\n\n");
        write(@HELP
	��ħ������������̵������ڹ��������г���
	�����ܽ��������ɣ��ʺ����ŵ�����������
	������󣬸�����������̵��似Ҳ��������
	�ϲ�����������
	��Ҫע���������ħ����������������Ͼ�
	���ط�������ã���ҪӦ���ڶ����ڴ������
	�����ͷ����ķ��ţ�ʹ������ע�⣬�ô󷨻�
	�����ʧ��ҵ��������ֵ�������򲻵��ѣ�
	��Ҫ����ʹ�á�
	
	ָ�exert jieti

Ҫ��  
	�������  2500 ���ϣ�
	��ǰ����  1500 ���ϣ�
	��ħ��    250  ���ϣ�
			
HELP
        );
        return 1;
}