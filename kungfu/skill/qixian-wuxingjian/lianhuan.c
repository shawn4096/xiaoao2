//lianhuan.c ����������
//cre by sohu@xojh 2014/6/6
// 

#include <ansi.h>
#include <combat.h>

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
		return notify_fail("�����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");


 
        if( (int)me->query_skill("qixian-wuxingjian", 1) < 450 )
		   return notify_fail("����������ν��ȼ����㣬�޷�ʹ���������������\n");
 
        if( (int)me->query_skill("sword", 1) < 450 )
		   return notify_fail("��Ļ��������ȼ����㣬�޷�ʹ���������������\n");


        if( (int)me->query_skill("force", 1) < 450 )
		    return notify_fail("��Ļ����ڹ��ȼ����㣬�޷�ʹ���������������\n");

        if( (int)me->query("max_neili") < 9500 )
		   return notify_fail("���������Ϊ̫ǳ���޷�ʹ���������������\n");

	    if( (int)me->query("neili") < 3000 )
		   return notify_fail("����������㣬�޷�ʹ���������������\n");
		
		if( (int)me->query("jingli") < 2000 )
		   return notify_fail("��ľ������㣬�޷�ʹ���������������\n");

	    //if( me->query_skill_mapped("force") != "xixing-dafa" )
		  // return notify_fail("��û��ʹ�����Ǵ󷨣��޷�ʹ�������������?\n");
         //����ʹ�����ƣ���������
	    if( !objectp(weapon = me->query_temp("weapon"))
	     || weapon->query("skill_type") != "sword"
		 || !weapon->query("qinjian")
	     || me->query_skill_mapped("sword") != "qixian-wuxingjian" )
	    	return notify_fail("��ʹ���ˡ����������ô?\n");
        
		if( me->query_temp("qxwxj/lianhuan") )
		    return notify_fail("������ʹ�á������������\n");
		//���Ǵ��ж���ӳ�
        skill = (int)me->query_skill("qixian-wuxingjian",1) +(int)me->query_skill("xixing-dafa",1) /4;
  	      
        me->add("neili",-(150+random(50))); 
        me->add("jingli",-50); 
		me->set_temp("qxwxj/lianhuan",6);
		
		me->add_temp("apply/attack",skill/4);
        me->add_temp("apply/damage",skill/6);
		if (weapon->query("qinjian"))
		{
			message_vision(HIG"$N���α������ɣ����������ͳ�һ��"+weapon->query("name")+HIG",����$n������һ̾��\n"NOR,me,target);
			//����������������
			me->add_temp("apply/damage",skill/4);
			me->add_temp("apply/attack",skill/4);
			me->set_temp("qxwxj/lhqj",1);
		}
		
		
		message_vision(HIB"\n$N��������˫���������������"+weapon->query("name")+HIB"�ϣ�����ʱ��ʱ����������Ȼ�����������Ȼ���졣\n"+
			               "����һ�ᣬ����Խ��Խ��,ż�������߿�,��Ȼ���������죬������һ����$n���˳�һ���������������£�\n"+
			               "$n�㲻�������������岽��$Nʩչ���������������ν��ľ����������������\n"NOR,me,target);
      
        for(a=0;a<=7;a++)
        {		     
		     if (me->is_fighting())
		      {		      
		         
				 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);				
			   }
			
        }

		if (me->is_fighting(target)
			&&random(me->query("neili",1))>target->query("neili",1)/3
			//&&me->query("hmy/qxwxj/lianhuan")=="pass"
		) 
	    {
			message_vision(HIR"$N����"+weapon->query("name")+HIR"���������������������ݴ��ͻ�����$n����ܵ��ܵ���?\n"NOR,me,target);
            message_vision(HIW "ֻ��$N" HIW "˫Ŀ΢�գ�������" + weapon->query("name") +HIW "�����Ღ������ʱֻ������࣡��ƿ�֮���������ϣ�\n"+
								"�������۳�һ���������ν������������ֱ��$n" HIW "��ȥ�����ǡ�������������һ��������������\n" NOR,me,target);
            target->add("neili",-2000-random(5000));
			target->apply_condition("no_exert",2+random(3));
			target->apply_condition("neishang",2);
			message_vision(HIY"$nֻ���Լ��������ڲ��ѣ���ɫ�Ұף���ȻΪ$N���������ˡ�\n"NOR,me,target);
			me->add_temp("apply/sword",skill/4);
            me->add_temp("apply/damage",skill/4);
			me->set_temp("must_be_hit",1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            me->add_temp("apply/sword",-skill/4);
			me->add_temp("apply/damage",-skill/4);
			me->delete_temp("must_be_hit");

    	}
		if (me->query_temp("qxwxj/lhqj"))
		{
			me->add_temp("apply/damage",-skill/4);
			me->add_temp("apply/attack",-skill/4);
			me->delete_temp("qxwxj/lhqj");

		}
		me->add_temp("apply/attack",-skill/4);
        me->add_temp("apply/damage",-skill/6);
		me->delete_temp("qxwxj/lianhuan");
        me->start_perform( 5 + random(2), "�����������");
        me->start_busy(2);
        return 1;
}


string perform_name(){ return HIR"����������"NOR; }
int help(object me)
{
        write(HIY"\n�������ν�"+HIR"�����������"NOR"\n");
        write(@HELP
	���������ν���ֻ�����������������Բ����˵У�Ч��ȫ�ڼ�������
	���������ҵ��У���������Խǿ�������������ӦҲԽ����������
	���������������ǡ�������ɽ���񼼣�ʩչʱͨ�����β��ң����ϴ�
	���������������ͬ�죬�����ߵ����壬�ǻ��ӹ��书�еĵǷ���
	��֮����
	��������������Ǵ���÷ׯ���ѵĻ��ӹ��������ǽ��������ϴ�
	һ���书��ɲ⣬�ڹ����Ǽ�����������������ν����ǵ���
	һ�����������ж�������Ϊ������������ν��������������Է�����
	�Է��ڹ�Խ����������˺�Խ�����˷���ʤ����
	
	ָ��;perform sword.lianhuan

Ҫ��
	�����ڹ��ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	�������ν�   450 ���ϣ�
	����������� 9500��
	���赱ǰ���� 3000��
	���赱ǰ���� 2000��
	�����ض������ڹ�֧�֣�
	���Ǵ��ж���ӳɡ�

HELP
        );
        return 1;
}