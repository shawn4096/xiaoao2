// tantui.c ����
// by sohu@xojh

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int perform(object me, object target)
{

	int i,damage,p;
	string msg;
	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("�����ȡ�ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("ʹ�á����ȡ�ʱ˫�ֱ�����ţ�\n");

	if( (int)me->query_skill("shaolin-tantui", 1) < 100 )
		return notify_fail("��ĵ����Ȳ�����죬����ʹ�á����ȡ���\n");

	if( (int)me->query_skill("yijin-jing", 1) < 100 )
		return notify_fail("����׽�ȼ�����������ʹ�á����ȡ���\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		return notify_fail("��Ŀǰ���ڹ��޷�֧����ʹ�á����ȡ����й�����\n");  
	if (me->query_skill("leg",1)<100)
		return notify_fail("��Ŀǰ�Ļ����ȷ�����100����֧����ʹ�á����ȡ����й�����\n");  
		
	if( (int)me->query_dex() < 30 )
		return notify_fail("���������30������ʹ�á����ȡ���\n");

	if (me->query_skill_prepared("leg") != "shaolin-tantui"
	|| me->query_skill_mapped("leg") != "shaolin-tantui")
		return notify_fail("�������޷�ʹ�á����ȡ����й�����\n");  
											       
	if( (int)me->query("max_neili") < 1400 )
		return notify_fail("�������������̫��������ʹ�á����ȡ���\n");
	if( (int)me->query("neili") < 500 )
		return notify_fail("��Ŀǰ����̫�٣�����ʹ�á����ȡ���\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("�����ھ���̫�٣�����ʹ�á����ȡ���\n");


	message_vision(HIC"\n$N����Ծ�𣬶㿪$n�Ĺ�������$n��������������Ⱦ�һ���Աŷ�����$n�߳���\n" NOR,me, target);
	
		
	me->set_temp("sltt/tantui", 1);
	me->add("neili", -180);
	if(random(me->query_dex()) > target->query_dex()/2
	  ||random(me->query_skill("leg",1))>target->query_skill("dodge",1)/2)
	{
           damage = me->query_skill("leg",1)+me->query_skill("shaolin-tantui",1)+me->query_skill("dodge",1);
		   damage=damage*me->query_dex()/5;
           damage =3*damage;
		   damage += random(damage);
           
           
		   if (wizardp(me))
           {
			   message_vision("damage="+damage+"\n",me);
           }
		   
		   if (damage>3500) damage=3500+random(100);
		   if (userp(target)&& damage > 2500) damage = 2500;

		   if(damage > 2000)
              message_vision(HIR"\nͻȻ֮�䣬$n�ؿ�һʹ��$N��һ�����������Լ����ؿڣ�һ����Ѫ���ڣ�\n\n"NOR,me,target);            
           
		   target->receive_damage("qi", damage, me);
		   target->apply_condition("neishang",3+random(2));
           target->receive_wound("qi", damage/4, me);
           
           
		 //  limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"����ȫ����ѹ��һ���ʯһ����һ��һ��ѣ�α�����\n" NOR, ({ target }));  
           msg = damage_msg(damage, "����");
            msg += "( $n"+eff_status_msg(p)+" )\n";
          
		   message_vision(msg, me, target);
           
		   if(userp(me) && me->query("env/damage"))
	          tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR);
           
			if(userp(target)&& target->query("env/damage"))
	         tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);
           me->start_busy(1);
           me->add("jingli", -20);
           		   
        }        
        else {
           me->add("neili", -50);
           me->add("jingli", -50);
           tell_object(me, HIY"����"+target->query("name")+"�����������ͼ��бԾ�ܿ��˹�����\n"NOR);

		   me->start_busy(2);         
        }
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);

		message_vision(HIC "\n$N��һ�����꣬���н��ƻ�������ƮƮ���ڵ��ϡ�\n" NOR,me);

		me->delete_temp("sltt/tantui");
		me->add_busy(1);           

		me->start_perform(3,"�����ȡ�");

		return 1;
}


string perform_name(){ return RED"����"NOR; }
int help(object me)
{
        write(HIC"\n���ֵ���֮�����ȡ�������"NOR"\n");
        write(@HELP
	���ֵ���Ϊ���������ȷ������ü�ʵ���ȹ���ǿ�����������
	��������У��öԷ�������Է��߳�һ�ž���ɱ�У�����ַ�
	��ʤ�������޿ɶ㣬�˵��������ǳ���
		
	ע�⣺�����ֵ��ȡ����ȷ����������˺�����Ӱ�����ȵı���
		�������ֵ����������������ȷ����мǣ�

	ָ�perform leg.tantui

Ҫ��  
	����������� 1400 ���ϣ�      
	��ǰ�������� 500  ����
	��ǰ�������� 500  ���ϣ�  
	���ֵ��˵ȼ� 100 ���ϣ�
	�׽���ȼ� 100 ���ϣ�
	�����ȷ��ȼ� 100 ���ϣ�	
	�����ȷ�Ϊ���ֵ��ȣ�
	�����м�Ϊ���ֵ��ȣ�
	�����ޱ�����
	��Ч������С��30��
                
HELP
        );
        return 1;
}
