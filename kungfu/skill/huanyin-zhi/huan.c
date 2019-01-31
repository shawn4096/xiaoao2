// huan.c
// by sohu@xojh

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";


int perform(object me, object target)
{
      string msg, dodge_skill;                                   
      int ap, dp,p,d;
      
      if( !target ) target = offensive_target(me);
     
      if( !objectp(target) || !me->is_fighting(target) || !living(target)
      || environment(target)!=environment(me))
                return notify_fail("�����־���ֻ����ս���жԶ���ʹ�á�\n");
             
      if( target->query("combat_exp") < 80000 )
                return notify_fail("ɱ������ţ������"+target->name()+"��û��Ҫʹ�û��־��ɡ�\n");
      if( me->query_temp("weapon") )
                return notify_fail("��������ʹ�á����־�����\n");
      
      if( (int)me->query_skill("huanyin-zhi",1) < 350 )
                return notify_fail("��Ļ���ָ������죬����ʹ�á����־�����\n");
      
      if( (int)me->query_skill("shenghuo-shengong",1) < 350 )
                return notify_fail("�����־�����Ҫ�ۺ���׽�ڹ�Ϊ������\n");
                  
      if (me->query_skill_mapped("force") != "shenghuo-shengong")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");
                
      if( target->query_condition("yzc_qiankun"))
                return notify_fail("�Է��Ѿ����С����־������㲻���ٷ������ˡ�\n");
      
      if( (int)me->query("max_neili") < 3500 )
                return notify_fail("���������Ϊ̫�Σ�����ʹ�á����־�����\n");
      
      if( (int)me->query("neili") < 1500 )
                return notify_fail("�������̫���ˣ��޷�ʹ�ó������־�����\n");   
            
      if( (int)me->query("jingli") < 500 )
                return notify_fail("��ľ���̫���ˣ��޷�ʹ�ó������־�����\n");   
                  
      if( (int)me->query_temp("hyz/huan"))
                return notify_fail("��ո�����һ�Ρ����־������ȵ�Ϣ��Ϣһ�°ɣ�\n");   
      if(target->query_temp("hyz/huan"))
                return notify_fail("�Է��Ѿ�������ġ����־�����\n");                                                            
      if (me->query_skill_prepared("finger") != "huanyin-zhi"
          || me->query_skill_mapped("finger") != "huanyin-zhi")
                return notify_fail("�������޷�ʹ�á����־������й�����\n");                                                                                 
       
     message_vision(HIB "$N" HIB "���������һ�����������Ĵ̳�һָ���������ᣬЮ��һ�ɺ�������$n" HIB "��\n" NOR,me,target);
                                         
      ap = me->query_skill("finger",1);
      dp = me->query_skill("dodge",1) ;   
      ap *= me->query("combat_exp")/100000;
      dp *= target->query("combat_exp")/100000;       
      d=ap*(me->query_skill("force",1)-target->query_skill("force",1))/1000;
	  me->set_temp("hyz/huan", 1);
      if( random(ap) > dp/2)
	  {
                message_vision(HIG "$p" HIG "��æ���ˣ�Ȼ����ָ�ε�������õ���$p" HIG "��ǰ��$p" HIG "��������һ����ս��\n" NOR,me,target);
                tell_object(target, HIC"��о���ָ������һ���������������������ڣ����һ�����������֫�ٺ��ŵ��������\n"NOR);
                target->receive_damage("jingli", d/2, me);
				target->receive_damage("neili", d, me);
                target->receive_wound("qi",d/3, me);
				target->set("jiali",0);
				//����buff,��ɢ��������no_exert
				target->apply_condition("no_exert",3);
				target->apply_condition("no_perform",3);
				target->add_temp("apply/attack",-ap/2);
				target->add_temp("apply/damage",-ap/4);
				target->set_temp("hyz/huan",1);
				call_out("remove_effect",15,target,ap);
              
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+d+ WHT"�㹥���˺���\n"NOR);
				
if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+d+ WHT"���˺���\n"NOR);
   
					 /**/
                target->apply_condition("huanyin_poison", 5+random(3));                                                   
                }
     else {
                me->start_busy(2);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
				message_vision(msg, me, target);   

      }                
      if (me->query_skill("huanyin-zhi",1)<450)
      {
		   me->start_perform(2,"���־�");
      } 
	  else  me->start_perform(1,"���־�");
      me->delete_temp("hyz/huan");

    
      return 1;
}

int remove_effect(object target,int ap)
{
	if (objectp(target)) return 0;
	target->add_temp("apply/attack",ap/2);
	target->add_temp("apply/damage",ap/4);
	target->delete_temp("hyz/huan");
	message_vision(HIC"$N����һ����������������ޱȵľ�������������\n"NOR,target);
	return 1;
}
string perform_name(){ return HIM"���־�"NOR; }

int help(object me)
{
        write(HIB"\n����ָ֮�����־�����"NOR"\n");
        write(@HELP
	����ָ�ǳ��������书�������Դ˼��������̹�����һս�����
	�������̵�ʥ�������ָ�������������������ص���һ����
	�ˣ�������������������������ܵ�������

	ָ�perform finger.huan

Ҫ��
	������� 3500 ���ϣ�      
	��ǰ���� 1500  ���ϣ�  
	����ָ�ȼ� 350 ���ϣ�
	�׽�ȼ� 350 ���ϣ�
	����ָ��Ϊ����ָ��               
	�����ޱ���,450���Ծ�����̺���pfm����ʱ�䣻
                               
HELP
        );
        return 1;
}
