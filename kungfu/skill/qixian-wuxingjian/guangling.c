// guangling.c
//updated by Zmud@Sjmud 10/3/2009

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int i, a;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("������ɢ�⡹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

		if( me->query_temp("qxwxj/guangling") )
			 return notify_fail("������ʹ�á�����ɢ�⡹��\n");
 
        if( (int)me->query_skill("qixian-wuxingjian", 1) < 400 )
		   return notify_fail("����������ν��ȼ����㣬�޷�ʹ��������ɢ�⡹��\n");
 
        if( (int)me->query_skill("sword", 1) < 400 )
		   return notify_fail("��Ļ��������ȼ����㣬�޷�ʹ��������ɢ�⡹��\n");

		
        if( (int)me->query_skill("force", 1) < 400 )
		    return notify_fail("��Ļ����ڹ��ȼ����㣬�޷�ʹ��������ɢ�⡹��\n");

        if( (int)me->query("max_neili") < 9000 )
		   return notify_fail("���������Ϊ̫ǳ���޷�ʹ��������ɢ�⡹��\n");

	    if( (int)me->query("neili") < 2000 )
		   return notify_fail("����������㣬�޷�ʹ��������ɢ�⡹��\n");
		
		if( (int)me->query("jingli") < 1000 )
		   return notify_fail("��ľ������㣬�޷�ʹ��������ɢ�⡹��\n");

	    //if( me->query_skill_mapped("force") != "xixing-dafa" )
		  // return notify_fail("��û��ʹ�����Ǵ󷨣��޷�ʹ��������ɢ�⡹?\n");

	    if( !objectp(weapon = me->query_temp("weapon"))
	     || weapon->query("skill_type") != "sword"
	     || me->query_skill_mapped("sword") != "qixian-wuxingjian" )
	    	return notify_fail("��ʹ���ˡ�����ɢ�⡹ô?\n");

        i = (int)me->query_skill("qixian-wuxingjian",1) /3 +(int)me->query_skill("xixing-dafa",1) /3;
        
        
		message_vision(MAG"$N�������˽��������ֽ����е�"+weapon->query("name")+MAG"����һ����һ���ܼ��������������������������Ž����ġ�����ɢ�⡹��\n"NOR,me);
		message_vision(HIG"$N����һ̾�������������ɣ�������������������֮�����޹���ɢ�������޻�̸֮����\n"NOR,me);
		message_vision(MAG"���$N�������ĵĿ���$nһ�ۣ��ȵ�����Ȼ��ˣ��Ҿ������ʶ��ʶ�����ɢ�����⣡\n"NOR,me,target);
		message_vision(HIM"$Nʩչ���������ν�����������ɢ�⡹��������ӯƮ�죬��ɢ���Ľ���ȴ�����������������죡\n"NOR,me);

		me->add("neili",-(150+random(50))); 
        me->add("jingli",-150); 
		me->set_temp("qxwxj/guangling",i);
		
		me->add_temp("apply/attack",i/3);
		me->add_temp("apply/sword",i/6);
		//me->add_temp();
		
		call_out("remove_effect",1,me,i/10);
		
        return 1;
}


void remove_effect(object me, int count)
{
        int i;
		if (!objectp(me)) return;
	    i=me->query_temp("qxwxj/guangling");
		
		if (objectp(me) && me->query_temp("qxwxj/guangling")){
                if (count-- > 0 && me->is_fighting()) {
                        call_out("remove_effect", 1, me, count);
                
                        return;
                }
		}
		me->add_temp("apply/attack",-i/3);
		me->add_temp("apply/sword",-i/6);

        message_vision(MAG"$N�ӹ���ɢ�⾳�����˳��������ٴ�Ϣ���������������չ���\n"NOR,me);
        me->delete_temp("qxwxj/guangling");
        
		return;
   
}

string perform_name(){ return HIM"����ɢ��"NOR; }
int help(object me)
{
        write(HIB"\n�������ν�"+HIY"������ɢ�⡹"NOR"\n");
        write(@HELP
	���������ν�������÷ׯ�������ϴ󣬻��ӹ��ĳ������������������ν���
	�ǻ��ӹ��Դ��ľ������Եе�ʱ��ͨ��������֮�й�ע�ϳ���������
	�����ҵ������񣬶Է�����������һ���������㲻֪������Ϊ�������ơ�
	�����滺���Է�����Ҳ�����滺���������裬�Է�����Ҳ���ż��衣��
	���ӹ����ϵ�����ȴ������ǡ���෴�������п��ٶ������ӱ����У���
	���Ʊ��޷����ܡ�
	������ɢ�⡹���������ν���ֻ�����������������Բ����˵У�Ч��ȫ��
	�����������������ҵ��У���������Խǿ�������������ӦҲԽ��������
	�����������������ǡ�������ɽ���񼼣�ʩչʱͨ�����β��ң����ϴ߼�
	�������������ͬ�죬�����ߵ����壬�ǻ��ӹ��书�еĵǷ��켫֮����
	450���ɡ�

	ָ�perform sword.guangling

Ҫ��
	�������Ҫ�� 9000 ����
	��ǰ����Ҫ�� 2000 ����
	��ǰ����Ҫ�� 1500 ����
	�����ڹ��ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	�������ν��� 400 ���ϣ�
	���н���������
	�����ض������ڹ�֧��,
	���Ǵ��ж���ӳɡ�

HELP
        );
        return 1;
}

