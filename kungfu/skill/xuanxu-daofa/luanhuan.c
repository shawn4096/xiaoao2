// luanhuanjue.c  �һ���

#include <ansi.h>
#include <combat.h>
inherit SKILL;
inherit F_SSERVER;
void check_fight(object me, object target,int j);
private void remove_effect(object me); 
int perform(object me, object target)
{
      string msg;
	  int dm,i,j;	  	
      object weapon = me->query_temp("weapon");  
	  i=me->query_skill("xuanxu-daofa",1);
	  j=2;
      //int j = (int)me->query_skill("xuanxu-daofa", 1)/5;
   
	  if( !target ) target = offensive_target(me);
      if (!objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "blade")                
        return notify_fail("���鵶����Ҫ�����õ�����ʩչ��\n");
      if( me->is_busy() )
        return notify_fail("����æ���ء�\n");
      if( !target || !me->is_fighting(target) )
        return notify_fail("�һ���ֻ����ս���жԶ���ʹ�á�\n");
             
      if( (int)me->query_skill("xuanxu-daofa", 1) < 100 )
        return notify_fail("������鵶��������죬����ʹ�һ�����\n");
      
      if( (int)me->query_skill("force", 1) < 100 )
        return notify_fail("��Ļ����ڹ��ȼ�����������ʹ���һ�����\n");

      if( (int)me->query_skill("blade", 1) < 100 )
        return notify_fail("��Ļ��������ȼ�����������ʹ���һ�����\n");  
      
      if( (int)me->query_skill("taoism", 1) < 100 )
        return notify_fail("��Ե����ķ����򲻹�����޷�ʹ�ó��һ�����\n");
      
      if( (int)me->query("max_neili") < 1500 )
        return notify_fail("�������̫��������ʹ���һ�����\n");
      
      if( (int)me->query("neili") < 500 )
        return notify_fail("�������̫���ˣ��޷�ʹ�ó��һ�����\n");   

      if (!weapon || weapon->query("skill_type") != "blade"
		  || me->query_skill_mapped("parry") != "xuanxu-daofa"
          || me->query_skill_mapped("blade") != "xuanxu-daofa")
        return notify_fail("��û�м������鵶����\n");
                                                                                 
      if( me->query_temp("blade_lh") )
          return notify_fail("������ʹ�����鵶�����һ�����\n");
   
	  if (i<350)
       {
			dm=i+me->query_skill("blade",1);
            dm/=3;
			j=4;
	   } 
	  else dm=i/5;
      msg = HIY"$Nʹ�����鵶���еľ���"+HIC"[�һ�����]"+HIY"�������ɻ���һȦһȦ�Ļ������ʵ�$n��ǰһƬ��Ӱ�⻷��\n"NOR;
	 
      me->add("neili", -100);
      me->set_temp("blade_lh", dm);
  	  me->add_temp("apply/attack",dm);
	  me->add_temp("apply/damage",dm/4);
      if (random(me->query("combat_exp"))>target->query("combat_exp")/3)
      {

		   msg += HIR"$N��$n���֮�ʻ���һƬ��Ӱ�����ƻ�����ʵ��Ѹ���ޱȡ�����$n��ǰ�ء�\n"NOR;           
		   if (!userp(target))
		      target->start_busy(1+random(2));
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
       }
	  message_vision(msg, me, target);
	  if (objectp(target)&&me->is_fighting(target)&&me->query_skill_mapped("strike")=="zhenshan-mianzhang"&&me->query_skill("xuanxu-daofa",1)>150)
	  {
		 switch (random(4))
	      {
                     case 0:                             
                              message_vision(HIG"$N����������һ��,����һƬ��Ӱ��Ѹ���ޱȡ�\n"NOR,me);
					          if (me->is_fighting(target))
			                   {
                                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
                                target->add_busy(1+random(2));
								}
                               break;        
                     case 1:
                                            
                              message_vision(HIC"$N����������������һ��Ϊ����һ��������˫��˲��������\n"NOR,me);
							  if (me->query_skill_mapped("force")=="yinyun-ziqi")
							    message_vision(HIB"$N�����ڹ���һ����������ʹ���������γɵĵ����ε�$n������ʹ���ѡ�\n"NOR,me,target);
                            
			                  if (me->is_fighting(target))
			                   {
							     //target->receive_damage("qi",dm*2);
							     //target->receive_wound("qi",dm);
                                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
                                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);  
								 //j=j-1;
							   }
                              break;                              
                      case 2:                                                 
                              message_vision(HIB"$N�����������������������£������Ͻ�����ˮ��©��\n"NOR,me);
							   if (me->is_fighting(target))
			                   {
							     me->add_temp("apply/parry",dm/3);
                                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
                                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
                                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
							     me->add_temp("apply/parry",-dm/3);
								 //j=j-1;
							   }
                             
                              break;                              
                      case 3:                                      
                              message_vision(HIR"$N�����������ĵ����ݺ����أ�������������Ȼ�������ڹ��ںϵ�����֮�С�\n"NOR,me);
							  if (me->is_fighting(target))
			                  {
							   me->add_temp("apply/blade",dm/4);
                               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
                               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
                               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
                               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
							   me->add_temp("apply/blade",-dm/4);
							  // j=j-1;
							  }
                              break;                                 
                     }
	  }
	  me->add_temp("apply/attack",-dm);
      me->add_temp("apply/damage",-dm/4); 
      message_vision(HIY"����þ�������˥�ߣ����е��⽥����\n"NOR,me);
	  me->delete_temp("blade_lh");
      me->start_perform(4,"�����һ�");		
     
      return 1;
}


string perform_name(){ return HIY"�һ�����"NOR; }
int help(object me)
{
         write(HIB"\n���鵶��֮"+HIY"���һ�������"NOR"\n");
        write(@HELP
	���鵶�������䵱���ŵ��ӵ��似���õ������ǿ�ɽ��ʦ
	���������ڴ�������ʱ��ʹ�õ��书���ܹ�ʮ���У�����
	�����ƾ����书׷ɱ�������ڵڰ�����������޵���ն
	ɱ���Դ�����������
	���鵶���һ������������ں��������쳣�ḻ��ս������
	���㼯�����к�ǿ��ʵսЧ����
	
	ָ�perform blade.luanhuan

Ҫ��
	��������100
	���鵶����100
	����������100
	��ѧ�ķ���100
	���������1500
	��ǰ������500
	��ѧ�ķ���100
	�����������鵶����
	�����м����鵶����
	�ڹ����ޣ�
	����ɽ���ơ�
	�ֳֵ���������
HELP
        );
        return 1;
}
