// xing.c �ǹ���
// cre by sohu@xojh

#include <ansi.h>
//#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg,*limbs;

        int i,damage,p; 
        i = me->query_skill("xingyi-zhang", 1); 
		
		if( !target ) target = offensive_target(me);
        if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("���ǹ��㡹ֻ����ս���жԶ���ʹ�á�\n");
      
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("ʹ�á��ǹ��㡹ʱ˫�ֱ�����ţ�\n");
        if(me->query("max_neili")<1400)
                return notify_fail("�����������������޷�ʹ�á��ǹ��㡹��\n");
        if( (int)me->query_skill("xingyi-zhang", 1) < 100 )
                return notify_fail("��������Ʋ�����죬����ʹ�á��ǹ��㡹��\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 100 )
                return notify_fail("�����Ԫ���ȼ�����������ʹ�á��ǹ��㡹��\n");

        if( (int)me->query_dex() < 20 )
                return notify_fail("���������ǿ������ʹ�á��ǹ��㡹��\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
        || me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("�������޷�ʹ�á��ǹ��㡹���й�����\n");                                                                                
        if (me->query_skill_mapped("parry") != "xingyi-zhang"
         && me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("�������мܲ��ԣ��޷�ʹ�á��ǹ��㡹���й�����\n");  

        if( (int)me->query("neili") < 700 )
                return notify_fail("����������̫��������ʹ�á��ǹ��㡹��\n");
        
		message_vision(HIC "\n$N����һ����������Ԫ��������ת��˫��һ��,�������γ��������Ӱ����$n,�������ǰ���$n��Χ��˸������\n"+
			HIC"$n�о����翴������ķ��ǵ�㡣������Ľ�������ƾ���"HIW"�ǹ���"HIC"��\n" NOR,me, target);
       
		message_vision(HIW"\n$N�������������������һ�С�"HIC"�ǹ���"HIW"����$n��ȥ������ķ��Ƿ·��ܵ�������ٿ�����۳������ǹ⣬����$n��\n"NOR,me,target);
		
		if(random(i) > target->query_skill("parry",1)/2
		 ||random(me->query_str())>target->query_str()/2)
		{
           damage = i+me->query_skill("strike",1)+me->query_skill("shenyuan-gong",1)+me->query_skill("douzhuan-xingyi",1);
           damage =4*damage;
		   damage = damage+random(damage);
          // if(target->query_skill("parry",1) - 50 > i)
            // damage = damage/2;
          // if(target->query_skill("parry",1) >i*2)
             // damage = random(1000);

			  damage = damage+random(damage);
           limbs = target->query("limbs");
		
		   if (userp(target)&& damage > 3000) damage = 3000;
		   if (wizardp(me))
           {
			   message_vision("damage="+damage+"\n",me);
           }
		   if (damage>3500) damage=3500+random(1000);
		 
		   if(damage > 3000)
              message_vision(HIY"\nͻȻ֮�䣬$n������Ѩһʹ�����类һ�����ϣ���һ�¾�ʹ��$n��ǰ������ð��\n"NOR,me,target);            
           if (damage<3000) damage=3000;
           
		   target->receive_damage("qi", damage, me);
		   target->apply_condition("neishang",3+random(2));
           target->receive_wound("qi", damage/2, me);
           //��Է�����
		         //     target->set_temp("last_damage_from", "�����ƴ���")

		   target->add("neili", -damage/5);
           
           p = (int)target->query("qi")*100/(int)target->query("max_qi");

           msg = damage_msg(damage, "����");
           msg += "( $n"+eff_status_msg(p)+" )\n";
          
		   message_vision(msg, me, target);
           

		   if(userp(me) && me->query("env/damage"))
	          tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR);
           
		   if(userp(target)&& target->query("env/damage"))
	          tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);
           //me->start_busy(1);
           me->add("jingli", -20);
           if (userp(target)) target->add_busy(1);
		   else target->add_busy(2);
		   
		   if (!userp(target) && me->query_temp("sy/shenyuan"))
				target->add_busy(2);		   
        }        
        else {
          
           tell_object(me, HIY"����"+target->query("name")+"�����������ͼ��бԾ�ܿ��˹�����\n"NOR);

		   me->start_busy(2);         
        }
		me->add_temp("apply/damage",i/6);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
		me->add_temp("apply/damage",-i/6);
		me->add("neili", -150);
        me->add("jingli", -100);
        me->start_busy(random(1));
		
		me->start_perform(3,"�ǹ���");
        return 1;
}

string perform_name(){ return HIY"�ǹ���"NOR; }
int help(object me)
{
        write(HIC"\n�����Ʒ�֮"+HIY+"���ǹ��㡹"NOR"\n\n");
        write(@HELP
	����Ľ�ݸ��ڽ�������ʱ����ʹ�õ���ʽ����������
	��������˲������ȫ���������ǹ�Ϊ��������Ԫ��
	Ϊ������Ȼ�䱬��һ��ǿ�����������е������¡���
	���ͼ����������кܴ��ϵ��

	ָ�perform strike.xing

Ҫ��  
	��ǰ�������� 700 ���ϣ�
	����������� 1400 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	�����Ʒ��ȼ� 100 ���ϣ�
	��Ԫ�����ȼ� 100 ���ϣ�
	�����Ʒ��ȼ� 100 ���ϣ�
	������Ҫ�� 20  ���ϣ�
	�����Ʒ�Ϊ�����ƣ�
	�����м�Ϊ�����ƻ�ת���ƣ�
                
HELP
        );
        return 1;
}
