//��������
//by sjxa@winnerlife
//2014-08-07
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>


string perform_name() {return HIG"��������"NOR;}

void back(object target);

int perform(object me, object target)
{
	
		int lvl,lv, i, hit;
		string weapon,msg;

		lvl = me->query_skill("chansi-shou",1);
        lv =(int)lvl/15;

		if( !target ) target = offensive_target(me);

        if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("���������š�ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á��������š���\n");   
				
        if( (int)me->query_skill("chansi-shou", 1) < 250 )
                return notify_fail("���������˿�ֻ�������죬ʹ�������������š�������\n");
                
        if (me->query_skill_prepared("hand") != "chansi-shou"
			|| me->query_skill_mapped("parry") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou")
                return notify_fail("�㼤�����ԣ������޷�ʹ�á��������š����й�����\n");  

        if( (int)me->query_skill("dulong-dafa", 1) < 250 )
                return notify_fail("��Ķ����󷨵ȼ���������ʹ�������������š�������\n");
                
        if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("����ڹ������޷�ʹ�á��������š���\n");               
		            
        if( me->query("max_neili") < 3000 )
                return notify_fail("����������̫����ʹ�������������š���\n"); 
                     
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫����ʹ�������������š���\n");
		
        if( (int)target->query_temp("chss/duozhu") ) 
                return notify_fail("�Է��Ѿ�Ϲ�ˣ�\n");
	//����
	  //��ʽ
		message_vision(MAG"$N������ǰ��˫��ͻȻ�Բ���˼��ĽǶȣ�����һ�У�$n�㲻������ʱ�������ҡ�\n"NOR, me, target);
	  // attack
        message_vision(RED"$N΢΢һ����Ц����Ȼʹ����"HIY"��������"RED"����һ������$n��ͷ������˫��ֱȡ$n˫Ŀ��\n"NOR, me, target);
		if (me->query("gender")=="Ů��")
		{
			i=3;
			lvl=lvl+me->query_skill("dulong-dafa",1)/5;
		}
		else i=2;

		if (random(me->query("combat_exp"))>target->query("combat_exp")/i
			||random(me->query_dex(1))>target->query_dex(1)/i)
		{
			message_vision(HIR"$n�ҽ�һ����˫Ŀ��ʱѪ����ע��Ŀ�����ӡ�\n"NOR,me,target);
			target->set_temp("chss/duozhu", 1);
			target->add_temp("apply/attack", - lvl/3);
			target->add_temp("apply/dodge", - lvl/2);
			target->add_temp("apply/parry", -lvl);
			target->receive_damage("qi", 2000+random(3000),me);
			target->receive_wound("qi", 1000+random(1000),me);
			target->set_temp("chss/duozhu",lvl);
			target->set_temp("block_msg/all",1);
			if (objectp(target))
				call_out("back", 3 + lv,target);
		}
		else if (random(me->query_int(1))>target->query_int(1)/i)
		{
			message_vision(HIW"$n���Ʋ����æ�ո��������ж�ܣ��������һ���������Ǳ�����һ���亹��\n"NOR,me,target);
			target->receive_damage("qi", random(1000),me);
			target->receive_wound("qi", random(400),me);
			me->add_busy(1+random(2));
		}
		else {
			message_vision(HIC"$n����Ԥ�ϵ����У���ͷ����һ������������㿪��$N��һ�У�\n"NOR,me,target);
			me->start_busy(2);
		} 		
			
		me->add("neili",-random(400));
		me->add("jingli",-random(200));
		if (!me->query("quest/sld/chss/pass"))
		{
			me->add_busy(1);
			me->start_perform(2, "���������š�");
		}
		return 1;
}

void back(object target)
{
	int lvl;
	if(!target) return;
	
	lvl==target->query("chss/duozhu");

   	target->add_temp("apply/attack", lvl/3);
	target->add_temp("apply/dodge",lvl/2);
	target->add_temp("apply/parry", lvl);
    target->set_temp("block_msg/all", 0);
	target->delete_temp("chss/duozhu");

    if(living(target)) 
		tell_object(target, HIW "��������˫Ŀû�б�����ŪϹ�����ֿ��Կ�����������\n" NOR);
	return;
}



int help(object me)
{
   write(WHT"\n���߲�˿��֮��"HIG"��������"WHT"����"NOR"\n");
   write(@HELP
	���߲�˿�����������̲���֮�أ��ǽ��и���
	��Ħ�������ϵ��߶��ݻ��������˵��ǵ�����
	�գ��������֡�ʩչ�������������ţ�һ��С
	���ܵ�ǿ�ҵĹ����������п��ܳ��ֱ����߶�
	�������ʧ����Σ�ա�Ů��Ч��ǿ�����ԡ�
	
   ע�⣺Ů�Խ⿪��˿������󣬴��д��,����
	   ��Ϊ����ʽ���ʹ�á�

	ָ�perform hand.tuxin
	   
Ҫ��
	���������Ҫ�� 3000 ���ϣ�
	��ǰ������Ҫ�� 1000 ���ϣ�
	������˿�ֵȼ� 250 ���ϣ�	
	�����󷨵ĵȼ� 250 ���ϣ�
	�����ַ��ұ�������˿��
	�����м�Ϊ���߲�˿�֣�
	�����ڹ�Ϊ�����󷨣�
	Ů���������ԣ�
    
HELP
      );
   return 1;
 }
