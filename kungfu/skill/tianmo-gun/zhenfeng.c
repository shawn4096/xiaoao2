//zhenfeng.c �����ԣ���Ӳ��Ӳ 
//cre by sohu@xojh 2014/5
//һ��һ���������ԣ���Ӳ���ᣬ˫������ȫ��������򳤽��Ǵ����۶ϲ��ɡ�
//��һ��˫���ĺ󾢶������಻�����������������ֱ���ȥ�����ҽ��Ϻ󾢻ᷴ������ίʵ�޷��ɽ⡣
#include <ansi.h>
#include <combat.h>
//inherit SKILL;
//#include <combat_msg.h>
inherit F_SSERVER;

int perform(object me, object target)
{
   int lvl;
   int damage;
   object weapon;
   object weapon1;
   weapon1=target->query_temp("weapon");
   lvl = (int)me->query_skill("tianmo-gun", 1);
   
   if( !target ) target = offensive_target(me);
   if( !objectp(target)
      || !me->is_fighting(target)
      || !living(target)
      || environment(target)!=environment(me))
      return notify_fail("�������ԡ�ֻ����ս���жԶ���ʹ�á�\n");

   if (!weapon1
	   ||weapon1->query("skill_type")=="club"
       ||weapon1->query("skill_type")=="spear"
	   ||weapon1->query("skill_type")=="axe"
	   ||weapon1->query("skill_type")=="hammer")
        return notify_fail("�������ԡ�ֻ�ܺ��������ս��ʹ�á�\n");
   if( (int)me->query_skill("tianmo-gun", 1) < 350 )
                return notify_fail("�����ħ����������죬ʹ�����������ԡ�������\n");

   if (me->query_skill_mapped("force") != "tianmo-gong" 
	   && me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("����ʹ�õ������ڹ����ԡ�\n");  

   if(me->query_skill("xixing-dafa", 1)<350)
      if(me->query_skill("tianmo-gong", 1) < 350)
         return notify_fail("�������ڵ��ڹ���Ϊ��ʹ�������Կ��ƿ졹��\n");  

   if(  me->query_skill_mapped("club") != "tianmo-gun")
                return notify_fail("�������޷�ʹ�á������ԡ���\n");
   

   if (!objectp(weapon = me->query_temp("weapon")) 
          || weapon->query("skill_type") != "club"
          || me->query_skill_mapped("club") != "tianmo-gun"
          || me->query_skill_mapped("parry") != "tianmo-gun")
                 return notify_fail("�������޹������ʹ�á������ԡ���\n");

   if( (int)me->query("max_neili") < 4000)
                return notify_fail("�������̫����ʹ�����������ԡ���\n");

   if( (int)me->query("neili") < 1500 )
                return notify_fail("����������̫����ʹ�����������ԡ���\n");

   if( (int)me->query("jingli") < 1500 )
           return notify_fail("������̫���ˣ�ʹ�����������ԡ���\n");

	message_vision(HIY"\n$N����ڳ�һ�����ƣ�˫��ִ"+weapon->query("name")+HIY"��׼$n���е�"+weapon1->query("name")+HIY"ӭ����ȥ��\n"NOR,me,target);
	
	message_vision(HIY"\n˫�������γ������Ծ��棬��$N��Ӳ��$n�������ᣬ˫������ȫ���������"+weapon1->query("name")+HIY"�Ǵ����۶ϲ��ɣ�\n"NOR,me,target);
    
	if (weapon->query("rigidity")>weapon1->query("rigidity")
		&& me->query("neili",1)>target->query("neili",1)
		&& random(me->query_str())>target->query_str()/3)
   {
	    message_vision(HIR"\n�����Ӵ���$n��������һ�ȣ�"+weapon1->query("name")+HIR"ž��һ������������أ�\n"NOR,me,target);
		//weapon1->broken("�Ҷϵ�");
		weapon1->move(environment(me));
		//target->receive_damage("qi",2000+random(5000));
    }
	//��һ��
       me->add_temp("apply/attack",  lvl/3);
       me->add_temp("apply/damage",  lvl/6);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                   
       me->add_temp("apply/attack",  -lvl/3);
       me->add_temp("apply/damage",  -lvl/6);

    if (me->is_fighting(target))
    {
		message_vision(HIC"\n��һ��˫���ĺ󾢶������಻����$N��������ֱ���ȥ��"+weapon1->query("name")+HIC"�Ϻ󾢶�ʱ������ȥ,��ʱ���˲��ᣡ\n"NOR,me,target);
//���мȶϣ��Է������������������ֻ����ȥ�Ͻ���˫ϥ�򵹣�Ҫ��Ȼ������ǰһ�ˣ������������֮�ơ�
        target->receive_wound("qi",random(1000),me);
		if (!weapon1)
        {
		  message_vision(HIY"\n$n���б��мȶϣ�$N�����������������ֻ����ȥ�Ͻ���˫ϥ�򵹣�Ҫ��Ȼ������ǰһ�ˣ������������֮�ƣ�\n"NOR,me,target);
          target->add_busy(2+random(2));
        }
//�ڶ���
       me->add_temp("apply/attack",  lvl/3);
       me->add_temp("apply/damage",  lvl/5);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                   
       me->add_temp("apply/attack",  -lvl/3);
       me->add_temp("apply/damage",  -lvl/5);


    }
	
//������
    damage =  me->query_skill("tianmo-gun",1)*3;
    if (me->is_fighting(target)){
	   message_vision(HIB"\n$n���б��мȶϣ�$N�����������������ֻ����ȥ�Ͻ���˫ϥ�򵹣�Ҫ��Ȼ������ǰһ�ˣ������������֮�ƣ�\n"NOR,me,target);
	   if ( damage > 4000 )
         damage = 4000 + (damage - 4000)/100;
 	   target->apply_condition("no_exert", 1+ random(2));
       target->receive_damage("qi", damage, me);
       target->receive_wound("qi", damage/3, me); 
       me->add_temp("apply/attack",  lvl/3);
       me->add_temp("apply/damage",  lvl/5);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                   
       me->add_temp("apply/attack",  -lvl/3);
       me->add_temp("apply/damage",  -lvl/5);
	}
	//�������45��,������
    if(me->query("str") > 45 &&me->is_fighting(target)){
         message_vision(HIR"$N���Է�����ײײ�������ٳ������ﻹ���Է����ᣬһ�С���ɨǧ��������$n���ؿ�ɨ��ȥ��\n"NOR,me,target);
         damage =  me->query_skill("tianmo-gun",1)*3;
         if ( damage > 5000 )
                        damage = 5000 + (damage - 5000)/100;
         target->apply_condition("no_perform", 1+ random(2));
         target->receive_damage("qi", damage, me);
         target->receive_wound("qi", damage/4, me);
 
          me->add_temp("apply/attack",  lvl/3);
          me->add_temp("apply/damage",  lvl/5);
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                   
          me->add_temp("apply/attack",  -lvl/3);
          me->add_temp("apply/damage",  -lvl/5);
       }
        me->add("jingli", -100);
        me->add("neili", -500);
       
        me->start_busy(1+random(2));
        me->delete_temp("tmgf/zhenfeng");
        me->start_perform(2+ random(2),"�������ԡ�");

        return 1;
}


string perform_name(){ return HIR"������"NOR; }

int help(object me)
{
        write(HIR"\n��ħ��֮�������ԡ���"NOR"\n\n");
        write(@HELP
	��ħ�������������ʮ����ħ֮����Գ��ħ���ų˷�͡��׺���ħ���ų���
	�ֵܶ����������������𽭺�������ʮ����Χ����ɽ�����䲻����ʹ��
	���ž����Ӵ�ʧ��������������˵�ڻ�ɽ��ɽʯ�����ֹ���ħ����ʽ��
	��������д�������Լ�̽����
	������������׾���ɵľ����������������������ƽ⹦Ч��ͨ����
	�����Ĺ�����������Ӳ�ȿ�����Ч���Ƴ���[����]��[����]��[ǹ��]��
	[����]����������������⣬�Ը����������Ч�����������ʹ�á�Ҳ
	����˵�����书�ǿ����������ɵĶ����似��
	
	ָ�perform club.zhengfeng

Ҫ��
	������� 4000 ���ϣ�
	��ǰ���� 1500  ���ϣ�
	��ǰ���� 1500  ���ϣ�
	��ħ�����ȼ� 350 ���ϣ�
	�����ڹ��ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	�����м�Ϊ��ħ����
	�����ڹ�Ϊ��ħ�������Ǵ�
	�����������45������������ӣ�
               

HELP
        );
        return 1;
}
