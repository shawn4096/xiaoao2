//chansi.c ���߲�˿
//by sjxa@winnerlife
//2-14-08-08
//edit by sohu,���¶�λ�似����Ϊ���߲�˿�֣�
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

string perform_name() {return HIY"����"HIW"��˿"NOR;}

void chan(object me, object target,int count);

int perform(object me, object target)
{
		int lv, i;
		string weapon,msg;

		lv = me->query_skill("chansi-shou",1);
		lv=(int)lv/100;

		if( !target ) target = offensive_target(me);

        if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("�����߲�˿��ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á����߲�˿����\n");   
		if( !me->query("quest/sld/chss/pass"))
                return notify_fail("��ֻ����˵����˿�־�����������ʹ�á����߲�˿����\n");   
                
        if( (int)me->query_skill("chansi-shou", 1) < 300 )
                return notify_fail("���������˿�ֻ�������죬ʹ���������߲�˿��������\n");
                
        if (me->query_skill_prepared("hand") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou"
			|| me->query_skill_mapped("parry") != "chansi-shou" )
                return notify_fail("�������޷�ʹ�á����߲�˿�����й�����\n");  

        if( (int)me->query_skill("dulong-dafa", 1) < 300 )
                return notify_fail("��Ķ����󷨵ȼ���������ʹ���������߲�˿��������\n");
                
        if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("����ڹ������޷�ʹ�á����߲�˿����\n");               
		            
        if( me->query("max_neili") < 5000 )
                return notify_fail("����������̫����ʹ���������߲�˿����\n"); 
                     
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫����ʹ���������߲�˿����\n");

		if((int)target->query_temp("chss/chan"))
                return notify_fail("�Է��Ѿ�����ס�ˣ����ֹ����ɡ�\n");
		if(me->query("gender")=="����")
                return notify_fail("ֻ��Ů�Բ���ʹ�ò�˿�ֵ�����֮�⡣\n");

        if (userp(target)) i=2;
		else i=3;
        
		
		message_vision(HBRED+HIW "����$n���в�����˼����α���֮�ʣ�$N�����������ǰ��˫���������������ס$n��˫��!\n" NOR,me,target);

		if (random(me->query_dex())>target->query_dex()/i
			||random(me->query_skill("hand",1))>target->query_skill("parry",1)/i)			
		{
			 message_vision(HBRED+HIW "$N������$n�ı��ж���,һ·����$n"HIC"�ڹأ���أ����أ����󣬷縮����̨"HBRED+HIW"�������ҪѨ!\n" NOR,me,target);

			 target->set_temp("chss/chan", lv);
			 if (me->query("gender")=="Ů��")
				target->add_busy(lv+1);
			 else target->add_busy(1);
			 
			 if (objectp(target)&& me->is_fighting())
				 call_out("chan",1, me,target,lv);
		}
		else
		{
			message_vision(HIW "$n�����������ͼ�������㣬����ܹ�����һ��!\n" NOR,me,target);
			me->start_busy(2);
		}
		me->add("neili",-random(250));
		me->add("jingli",-random(100));
		//me->start_perform(3,"���߲�˿��");
	
		return 1;
}



void chan(object me, object target,int count)
{

	int lv;
	//int k;
	if(!target||!me) return;

	lv = me->query_skill("shenlong-chansishou",1);
	lv=lv/100;
	if (me->query("gender")!="Ů��") return;
	
	if (!me->is_fighting()
		||count<0)
	{
		message_vision(HBRED+HIC"$N�����޷���ά�ֶ�$n�Ĳ��ƣ����ò��ɿ���˫�ۡ�\n" NOR,me,target);
		target->delete_temp("chss/chan");
		return;

	}

		message_vision(HBRED "$n�о���һ���������ƣ�����Խ��Խ���ѣ���ǰ������ģ����\n" NOR,me,target);
	
		target->add("jing",- lv*20);
		target->add("neili",- lv*50);
		target->add("jingli",- lv*20);
		target->apply_condition("no_perform", 1);
		if (!userp(target))
			target->add_busy(1);
		if (objectp(me)&&objectp(target))
			call_out("chan",2, me,target,count--);
		return;
}

int help(object me)
{
   write(WHT"\n��"HIY"���߲�˿"WHT"����"NOR"\n");
   write(@HELP
	���߲�˿�����������̲���֮�أ��ǽ��и���
	��Ħ�������ϵ��߶��ݻ��������˵��ǵ�����
	�գ��������֡�ʩչ������һ������������
	�ֵı仯���仯��һ�������������԰��ѡ�

	perform hand.chansi
	
Ҫ��
	���������Ҫ�� 5000 ���ϣ�	
	��ǰ������Ҫ�� 1000 ���ϣ�
	���߲�˿�ֵȼ� 300 ���ϣ�
	�����󷨵ĵȼ� 300 ���ϣ�
	�輤���ұ��ַ�Ϊ���߲�˿��
	�����ڹ�Ϊ�����󷨣�
	�����������ԣ�
	����Ů��ʹ��;
HELP
      );
   return 1;
   }