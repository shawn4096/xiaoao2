//��������
// by sjxa@winnerlife
//2014-08-07
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

string perform_name() {return HIR"��������"NOR;}

int perform(object me, object target)
{
		int lv, i, hit;
		string weapon,msg;

		lv = me->query_skill("chansi-shou",1)+me->query_skill("dulong-dafa",1)/5;		

		if( !target ) target = offensive_target(me);

        if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("���������衿ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á��������衿��\n");   
                
        if( (int)me->query_skill("chansi-shou", 1) < 350 )
                return notify_fail("��Ľ��߲�˿�ֻ�������죬ʹ�������������衿������\n");
                
        if (me->query_skill_prepared("hand") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou"
			|| me->query_skill_mapped("parry") != "chansi-shou" )
                return notify_fail("�������޷�ʹ�á��������衿���й�����\n");  

        if( (int)me->query_skill("dulong-dafa", 1) < 350 )
                return notify_fail("��Ķ����󷨵ȼ���������ʹ�������������衿������\n");
                
        if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("����ڹ������޷�ʹ�á��������衿��\n");               
		            
        if( me->query("max_neili") < 5000 )
                return notify_fail("����������̫����ʹ�������������衿��\n"); 
                     
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫����ʹ�������������衿��\n");
      
        
		if(me->query("gender")=="Ů��")
		{
			msg=HBRED+HIG"$N�����ζ���ȫ������������������������Ȼ������һ���������з�����˻~~����һ�����硾"HIY"��������"HBRED+HIG"��ʱ�ĺ�Х��\n\n"NOR;
		
			// add busy
			msg+=HBBLU"$N������â����ʵ�ʻ�һ�������$n�о��Լ��·�һֻ�����ľ��������Ķ�ס����ʱ�������á�\n\n"NOR;
			target->add_busy(1);
			//add �쳣״̬
			msg+=HIR"$N�ַ����Ī���Ա����ꡢ�����塢�ᡢ������������������$nȫ���Ѩ��\n"NOR;
			message_vision(msg,me,target);
	
			switch(random(3))
			{
				case 0:
					message_vision(HIW"$nһ��������Ȼ�᲻������ԭ����"HIC"��Ϫ"HIW"������"HIC"���"HIW"���Ѿ���$N���У�\n"NOR,me,target);
					target->add_condition("no_exert",1+random(5));
					break;
				case 1:
					message_vision(HIB"$n��Ϣ���ң�ԭ����"HIW"�羮"HIB"������"HIW"����"HIB"���Ѿ���$N���У�\n"NOR,me,target);
					//target->add_condition("no_perform",1+random(5));
					target->add_busy(2);
					target->receive_damage("qi",random(1000),me);
					break;
				case 2:
					message_vision(HIC"$n�ƺ�һ����ԭ����"HIG"����Ѩ"HIC"���Ѿ���$N���У�\n"NOR,me,target);
					target->start_lost(1+random(5));
					break;
			}
			// 4hit
			message_vision(HIM"\n������$N����һ���Դ����塢���������ꡢѹ���ڡ����ַ�˲��������С�\n"NOR,me,target);
			me->set_temp("chss/lw", 4);
			message_vision(HIY"$n��֧�ҵ����κ�$N�ַ������ǧ����ʱ�������С�\n"NOR,me,target);
			
			me->add_temp("apply/attck",lv/2);
			me->add_temp("apply/damage",lv/4);
			
			//message_vision(HIB"                                                                   ����  "HIY"����"NOR  HIB"  ����\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

			//message_vision(HIB"                                                                   ����  "HIY"���ߡ�"NOR  HIB"  ����\n"NOR,me);
	
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);

			//message_vision(HIB"                                                                   ����  "HIY"���ҡ�"NOR  HIB"  ����\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

			//message_vision(HIB"                                                                   ����  "HIY"���衿"NOR  HIB"  ����\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			me->add_temp("apply/attck",-lv/2);
			me->add_temp("apply/damage",-lv/4);

			
		}
		else
		{
			//���ԣ���ֻ��4hit

			message_vision(HIM"\n$N����һ���Դ����塢���������ꡢѹ���ڡ����ַ�˲��������С�\n"NOR,me,target);
			me->set_temp("chss/lw", 4);
			
			//me->add_temp("apply/attck",lv/5);
			//me->add_temp("apply/damage",lv/8);
			//message_vision(HIB"                                                                   ����  "HIM"����"NOR  HIB"  ����\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

			//message_vision(HIB"                                                                   ����  "HIM"������"NOR  HIB"  ����\n"NOR,me);
	
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

			//message_vision(HIB"                                                                   ����  "HIM"���ҡ�"NOR  HIB"  ����\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),  random(3)?1:3);

			//message_vision(HIB"                                                                   ����  "HIM"���衿"NOR  HIB"  ����\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),  random(3)?1:3);
			//me->add_temp("apply/attck",-lv/5);
			//me->add_temp("apply/damage",-lv/8);
		
		}
		me->delete_temp("chss/lw");

		me->start_perform(5, "���������衹");
		me->add("neili",-200-random(400));
		me->add("jingli",-random(200));

		return 1;

}
//����
int help(object me)
{
   write(WHT"\n���߲�˿��֮��"HIR"��������"WHT"����"NOR"\n");
   write(@HELP
	���߲�˿�����������̲���֮�أ��ǽ��и���
	��Ħ�������ϵ��߶��ݻ��������˵��ǵ�����
	�գ��������֡�ʩչ�����������ܶ�������
	����㹥��Է���Ů��Ч��ǿ�����ԡ�

	perform hand.luanwu
	   
Ҫ��
	���������Ҫ�� 5000 ���ϣ�
	��ǰ������Ҫ�� 1000 ���ϣ�
	������˿�ֵȼ� 350 ���ϣ�	
	�����󷨵ĵȼ� 350 ���ϣ�
	�����ַ��ұ�������˿��
	�����м�Ϊ���߲�˿�֣�
	�����ڹ�Ϊ�����󷨣�
	Ů���������ԣ�
HELP
      );
   return 1;
   }