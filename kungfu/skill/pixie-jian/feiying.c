// feiying.c ������Ӱ��

#include <ansi.h>
string perform_name(){ return MAG"������Ӱ��"NOR; }

inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill,count;

        if( !target ) target = me;
		count=(int)skill/20;        
        if( (int)me->query("neili") < 500  ) 
                return notify_fail("�������������\n");
        if( (int)me->query("jingli") < 200  ) 
                return notify_fail("��ľ���������\n");
        if( (int)me->query_temp("feiying") ) 
                return notify_fail("���Ѿ������ÿ�����Ӱ���ˡ�\n");
        if( (int)me->query_skill("pixie-jian", 1) < 150 )
                return notify_fail("��ı�а������û���ɣ��޷�ʹ�ÿ�����Ӱ����\n");
        if( (int)me->query_dex() < 30  )
                return notify_fail("�����̫�ͣ�����ʹ�ÿ�����Ӱ����\n");
       if(me->query_temp("pxj/feiying"))
                return notify_fail("���Ѿ���ʹ�ÿ�����Ӱ����\n");

        //skill = me->query_skill("dodge",1);
        skill =me->query_skill("kuihua-shengong",1) + me->query_skill("pixie-jian",1);
        skill = skill / 10;
        me->add("neili", -300);
        me->add("jingli", -250);
		if (me->query_skill("pixie-jian",1)>200)
		{
			if(!QUEST_D->queryquest(me,"kuihua/book"))
                return notify_fail("��Ա�а����������δ��⣬����ʹ�á���Ӱ������\n");
			if(me->query("gender")!="����" )
                return notify_fail("��û�Թ����Ա�а����������δ��⣬����ʹ�á���Ӱ������\n");

		}
        message_vision(
        MAG "ֻ��$N�������һ����ƾ�շ�����س��࣬����Ʈ������������Ӱ��һ�㡣\n" NOR, me);
        tell_object(me, MAG "��Ĭ�˿�����Ӱ�����ھ���й��������ƾ��̧��������\n" NOR);

        me->add_temp("apply/dodge", skill*3);
        me->add_temp("apply/parry", skill);

		if (QUEST_D->queryquest(me,"kuihua/book"))
		   me->add_temp("apply/dexerity",skill);
		
        
		me->set_temp("pxj/feiying", skill);

		call_out("remove_effect",1,me,count);
        if( me->is_fighting() &&me->query_skill("pixie-jian",1)<550) me->start_busy(1);

        return 1;
}

void remove_effect(object me, int count)
{
	int amount;
	if(!me) return;
	amount=me->query_temp("pxj/feiying");
	
	
	if (!me->is_fighting()
		||me->query_skill_mapped("sword")!="pixie-jian"
		||me->query_skill_mapped("dodge")!="pixie-jian")
	{
	
        me->add_temp("apply/dodge", - amount*3);
		me->add_temp("apply/parry", - amount);

		if (QUEST_D->queryquest(me,"kuihua/book"))
			me->add_temp("apply/dexerity",-amount);
        
		me->delete_temp("pxj/feiying");

		tell_object(me, MAG "��һ�������Ӱ���Ѿ�ʹ�꣬���ָֻ�������\n" NOR);
		return;
	}
	call_out("remove_effect",2,me,count -1);
	return;
}
int help(object me)
{
   write(WHT"\n��а������"MAG"������Ӱ��"WHT"����"NOR"\n");
   write(@HELP
	��������˽�������Ҫ��һ��а����֯������ȫƾ���˺ö�
	���г����似�������������а�����������ν�����������
	�ľ��������������������ְ汾�������ڱ�а���������ɡ�
	���������ơ�
	��������Ӱ�����ǽ�ǿ�����ͽ����ںϣ���������Լ���
	��ܣ�����⿪�����񹦣�����ʹ�á�550�����Ծ�����
	Ч����ǿ�������г���200����ֻ���Թ�������ζ���п������⡣
    
	ָ�perform sword.feiying

Ҫ��
	��ǰ���� 500 ���ϣ�
	��ǰ���� 200 ���ϣ�
	��а���� 150 ���ϣ�
	�����Ṧ 150 ���ϣ�
	������ 30  ���ϣ�
	�����Ṧ��а����

HELP
   );
   return 1;
}
