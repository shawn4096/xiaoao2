// pomo.c  ��ī���齣����Դ�Ե�����
//��������ī���齣��������ô���׺���ա�������������������ô������������
//cre by sohu@xojh 2014

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int i, a,skill;

	if( !target ) target = offensive_target(me);
    skill=me->query_skill("qixian-wuxingjian",1);
	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("����ī���齣��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	//if( me->query_temp("qxwxj/shan") )
		//return notify_fail("������ʹ�á����һ���������\n");
 
        if( (int)me->query_skill("qixian-wuxingjian", 1) < 350 )
		   return notify_fail("����������ν��ȼ����㣬�޷�ʹ������ī���齣����\n");
 
        if( (int)me->query_skill("sword", 1) < 350 )
		   return notify_fail("��Ļ��������ȼ����㣬�޷�ʹ������ī���齣����\n");


        if( (int)me->query_skill("force", 1) < 350 )
		    return notify_fail("��Ļ����ڹ��ȼ����㣬�޷�ʹ������ī���齣����\n");

        if( (int)me->query("max_neili") < 2500 )
		   return notify_fail("���������Ϊ̫ǳ���޷�ʹ������ī���齣����\n");

	    if( (int)me->query("neili") < 1000 )
		   return notify_fail("����������㣬�޷�ʹ������ī���齣����\n");
		
		if( (int)me->query("jingli") < 1000 )
		   return notify_fail("��ľ������㣬�޷�ʹ������ī���齣����\n");

	    //if( me->query_skill_mapped("force") != "xixing-dafa" )
		  // return notify_fail("��û��ʹ�����Ǵ󷨣��޷�ʹ������ī���齣��?\n");

	    if( !objectp(weapon = me->query_temp("weapon"))
	     || weapon->query("skill_type") != "sword"
	     || me->query_skill_mapped("sword") != "qixian-wuxingjian" )
	    	return notify_fail("��ʹ���ˡ���ī���齣��ô?\n");

        i = (int)me->query_skill("qixian-wuxingjian",1) +(int)me->query_skill("xixing-dafa",1) /3;
        
        me->add("neili",-(150+random(50))); 
        me->add("jingli",-50); 
		me->set_temp("qxwxj/pomo",3);
		me->add_temp("apply/attack",skill/3);
        me->add_temp("apply/damage",skill/4);
		message_vision(HIB"$N��Ȼ�����������������ī�����죬����"+weapon->query("name")+HIB"����һ֧���ʣ�ʩչ�������󿪴�ϡ�\n"+
			"$N�����۽������߿��裬�ʷ�ɭ�ϣ�һ�ʱʱ��糤���Ĵ̻������ǵ�������������ī���齣����"NOR,me,target);
        
        for(a=0;a<3;a++)
        {		     
		     if (me->is_fighting(target))
		      {		      
		         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
				 
			   }
			
        }
		if (me->is_fighting(target)&&me->query("quest/hmy/qxwxj/pomo/pass")) //quest��
	    {
			message_vision(HIG"$N����"+weapon->query("name")+HIG"��ǰֱ�̶�ȥ������ת��ʩչ����Ϊ��������ʽ���������������̽���ͷӲ����������ī��\N"NOR,me,target);
            me->add_temp("apply/sword",skill/2);
			me->add_temp("apply/damage",skill/2);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            me->add_temp("apply/damage",-skill/2);
			me->add_temp("apply/sword",-skill/2);
			message_vision(HIC "$N" HIC "һ������������" + weapon->query("name") + HIC
              "��������ԲȦ������������Ȧ������������֮�������$n" HIC
              "��ǰ��ȥ��\n"NOR,me,target);
			if (me->is_fighting(target)&&random(me->query_skill("sword",1))>target->query_skill("parry",1)/2)
			{
			   message_vision(HIR"ֻ���������ң�����Ϯ�壬΢΢һ�㣬��������������Ѫ�ɽ���\n"NOR,me,target);
			   target->receive_damage("qi",3000+random(2000),me);
			   target->receive_wound("qi",1000+random(1000),me);
			   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			}else
			{
				message_vision(CYN"����$n" CYN "������Ѹ�ͣ�����һԾ��������$N" CYN "�������ļ�����\n"NOR,me,target);
			}
			 
    	}
		me->add_temp("apply/attack",-skill/3);
        me->add_temp("apply/damage",-skill/4);
		me->delete_temp("qxwxj/pomo");
		//me->delete_temp("gl_sword");
        me->start_perform( 3 + random(2), "����ī���齣��");
        me->start_busy(1);
        return 1;
}

string perform_name(){ return HIB"��ī���齣"NOR; }
int help(object me)
{
        write(HIY"\n�������ν�"+HIB"����ī���齣��"NOR"\n");
        write(@HELP
		
	����ī���齣�����Ǵ���÷ׯ���ѵĵ����������ųƾơ�������������
	һ���书��ɲ⣬��������һ�δ���֮�н��þ�����Ũ��֮�ʣ���
	�������������н��Լ��Ľ����ͽ������뵽�⸱���С���ʾ�����⿪
	������Сquest����ý���������Ծ��
	
	ָ�perform sword.pomo

Ҫ��
	�����ڹ��ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	�������ν��� 350 ���ϣ�
	�����ض������ڹ�֧�֣�
	���Ǵ��ж���ӳɡ�

HELP
        );
        return 1;
}

