// fentian.c �ٻ����
// by hunthu

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int skill, damage,p;
        weapon = me->query_temp("weapon");  
        skill= me->query_skill("ranmu-daofa",1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("���ٻ���졹ֻ�ܶ�ս���еĶ���ʹ�á�\n");        

        if (!weapon || weapon->query("skill_type") != "blade"
                        || me->query_skill_mapped("blade") != "ranmu-daofa")
                return notify_fail("�������޷�ʹ�����ٻ���졹֮����\n");

        if (weapon->query("unique"))
                return notify_fail("������֮�����ڷ�����Ӱ����ȼ������ʩչ��\n");

        if((int)me->query_skill("ranmu-daofa", 1) < 300 )
                return notify_fail("���ȼľ������򲻹����޷����ٻ���졹��\n");

        if((int)me->query_skill("blade", 1) < 300 )
                return notify_fail("��Ļ���������������죬ʹ�������ٻ���졹������\n");

        if( (int)me->query_skill("yijin-jing", 1) < 300 )
                return notify_fail("����׽��Ϊ������ʹ�������ٻ���졹������\n");

        //if ((int)me->query_skill("strike",1) < 300)
          //      return notify_fail("����Ʒ���Ϊ̫��޷�ʹ�����ٻ���졹������\n");

        if (me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("û���׽��Ϊ���������޷�ʹ�����ٻ���졹�����ģ�\n"); 
	    
		if (me->query_skill_mapped("parry")!="ranmu-daofa"&&me->query_skill_mapped("parry")!="cibei-dao")
                return notify_fail("����мܲ��ԣ��޷�ʹ�á�ȼľ����������\n");  

        if (me->query_temp("jgq/fumo"))
                return notify_fail("����������ʹ�á���շ�ħ���񹦡�\n"); 


        if (me->query_temp("rmdf/fentian"))
                return notify_fail("������ʹ�á��ٻ���졹������");

        if (me->query("max_neili") < 5000)
                return notify_fail("���������Ϊ������\n");

        if (me->query("neili") < 500)
                return notify_fail("�������������\n");

        if (me->query("jingli") < 200)
                return notify_fail("��ľ���������\n");

        me->set_temp("rmdf/fentian",1);
        me->start_busy(2);
        me->add("neili", -800);
        me->add("jingli", -200);        
        msg =HIR"\n$N��Ȼһ����ȣ����е�"+weapon->query("name")+HIR"��һ�������ڿն���һ���ٲ�֮��������������棬\n"+
                "��ͷָ����һ���������ܶ�����$N�����ڵ����ڼ䲻�ݷ�֮�ʣ�����������������\n"NOR;

        if(random(me->query("combat_exp",1)) > target->query("combat_exp",1)/2
         ||((me->query_skill("blade",1))+ me->query_skill("strike",1))/2 > random(target->query_skill("dodge",1)))
		{
          skill= me->query_skill("ranmu-daofa",1)+me->query_skill("blade",1)+me->query_skill("buddhism",1);
          damage= skill*2;
          msg += HIR"\n$n��������������������ʧɫ���������޼��������ܴ��Χ�ڵ��С�\n"NOR;
          damage = damage+random(damage/2);

          if (damage > 3000) damage = 3000;
          target->receive_damage("qi", damage*4,me);
          target->receive_wound("qi", damage*2,me);
          
		  p = (int)target->query("qi")*100/(int)target->query("max_qi");
          msg += "( $n"+eff_status_msg(p)+" )\n";
          
          
		  me->start_perform((1+random(4)), "�ٻ����");
          me->start_busy(2+random(2));
          
          
		  message_vision(msg, me, target);
		  
		  if(userp(me) && me->query("env/damage"))
			  tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR); 
		  
if(userp(target)&& target->query("env/damage"))
			  tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR); 
		  
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          me->start_perform(2, "�ٻ����");
          me->delete_temp("rmdf/fentian");

		  return 1;
        }
        if(random(me->query("combat_exp",1)) > (target->query("combat_exp",1)/3))
		{
          message_vision(HIR"\n$n�����з�������է�����ҫ��Ҳ�������һ������æԾ����ܣ�Ҳ�Ѵ����Ǳ���\n"NOR,me,target);
          target->start_busy(3+random(2));
        
          me->start_perform(2, "�ٻ����");
		 
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		  me->delete_temp("rmdf/fentian");

          return 1;
        }
        msg += HIR"\n$n�������أ����������һ�ɾ����˳���˲���������ʱ���۳�һ��������������$N��\n"NOR;
        damage = skill*5;
        me->receive_damage("qi", damage,"�ٻ�����");
        me->receive_wound("qi", damage,"�ٻ�����");
        p = (int)me->query("qi")*100/(int)me->query("max_qi");
        msg += "( $N"+eff_status_msg(p)+" )\n";
        message_vision(msg, me, target);
		me->start_perform(2, "�ٻ����");

        me->delete_temp("rmdf/fentian");
        return 1;
}



string perform_name(){ return HBYEL+HIW"�ٻ����"NOR; }

int help(object me)
{
        write(HIY"\nȼľ����֮���ٻ���졹��"NOR"\n\n");
        write(@HELP
	ȼľ�����������������ռ�����֮һ���ǵ����ļ�����似
	��������������ʮ�������в���֮�أ��书���������
	ƾ����������������������ƻ����������ޱȡ������书��
	���������ʦ��ϰ���������ʦԲ�ź󣬴��似�����޳ɣ�
	��һ����ɮ�Ħ��ƾ��С�������ݻ�ȼľ������ս������
	ʱ��ʹ�ô����似�������¡�
	
	ע�⣺��ϰ�ֵ�������Ҫ������ֻ����������޵���ɱ���
		�ȱ����Ĵȱ�֮�⣬��ɱ���ʹȱ����ں��ж����ֵ���
		���衣�мǣ��мǣ�
	
	ָ�perform blade.fentian 

Ҫ��  
	��ǰ�������� 1000 ���ϣ�
	����������� 10000 ���ϣ�
	��ǰ�������� 800 ���ϣ�
	ȼľ�����ȼ� 300 ���ϣ�
	�׽���ȼ� 300 ���ϣ�
	���������ȼ� 300 ���ϣ�
	��������Ϊȼľ������
	�����м�Ϊȼľ������ȱ���;
	�����ڹ�Ϊ�׽�񹦣�
	���ֳ�ľ����

HELP
        );
        return 1;
}
/**/
