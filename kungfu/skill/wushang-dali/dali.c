// by SOHU@XOJHU 2014.1
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon,weapon2;
		int ski;
		weapon=me->query_temp("weapon");
		weapon2=target->query_temp("weapon");
		ski=me->query_skill("wushang-dali",1)+me->query_skill("tianwang-zhua",1)/2;
        //write("weight="+weapon->query("weight"));
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("�����ϴ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("wushang-dali", 1) < 250 )
                return notify_fail("������ϴ����ƹ���̫ǳ���޷�ʹ�á����ϴ�����������\n");
		 if( (int)me->query_skill("staff", 1) < 250 )
                return notify_fail("��Ļ����ȷ�����̫ǳ���޷�ʹ�á����ϴ�����������\n");
        if( !weapon||weapon->query("skill_type")!="staff")
                return notify_fail("������ϴ����Ʊ������ȷ�����������ʹ�á�\n");
        if( (int)me->query_skill("tianwang-zhua", 1) < 250 )
                return notify_fail("�������צ����̫ǳ���޷�ʹ�á����ϴ�����������\n");
        if( me->query_temp("wushang_dali") )
                return notify_fail("������ʹ�á����ϴ���������������\n");
        if( (int)me->query("max_neili") < 2500 )
                return notify_fail("�������̫ǳ���޷�ʹ�á����ϴ�����������\n");
        if( (int)me->query_str() < 50 )
                return notify_fail("�����Ч�����������޷�ʹ�á����ϴ�����������\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("����������㣬�޷�ʹ�á����ϴ�����������\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "staff"
            || me->query_skill_mapped("staff") != "wushang-dali" 
			|| me->query_skill_prepared("claw") != "tianwang-zhua"
			|| me->query_skill_mapped("force") != "longxiang-boruo")
                return notify_fail("���׼�����򲻶ԡ�\n");

        me->add("neili", -200);
        me->add("jingli", -40);
		me->set_temp("wushang_dali",1);
        message_vision(RED"$N"+RED"���һ����˫���������е�"+weapon->query("name")+RED+"����һ�ɾ��磬��Ȼ��$n������ȥ��\n" NOR,me,target);
        message_vision(HIY"$N"+HIY"��ʱ˫���þ���������Ҳͬʱʹ���ˣ�"+weapon->query("name")+HIY"����������������������һ����\n" NOR,me,target);
		
		if (!userp(target))
        {
			me->add_temp("apply/attack", ski/2);
	        me->add_temp("apply/damage", ski/4);
			me->add_temp("apply/staff", ski/4);
			me->set_temp("wsdl/dalitemp",1);
        }
		if (random(me->query_str(1))>target->query_dex(1)/2)
		{
		    if (weapon2)
			{ 
				message_vision(HIR"$N������������ͣ�$n���ж�$N�������ӣ��������е�"+weapon2->query("name")+HIR"ӭ����ȥ��\n"NOR,me,target);
			    if (random(me->query_str(1))>target->query_str(1)/2 && weapon2->query("imbue")<3)
			    {
				 message_vision(HIY"$nֻ��һ�ɴ������������ھ������е�"+weapon2->query("name")+HIY"��ʱ��Ϊ���ء�\n"NOR,me,target);
				 weapon2->broken("�Ҷϵ�");			     
				 target->receive_damage("qi",1000+ski*5,me);
                 target->receive_wound("qi",ski/2,me);
			     }			  
			}else {
                 message_vision(RED"$nֻ��һ�ɴ������������ھ�����Ѫ��ӿ���۵��³�һ����Ѫ��\n"NOR,me,target);
				 target->receive_damage("qi",2000+ski*5,me);
                 target->receive_wound("qi",ski,me);
			}
		 
		 }else message_vision(HIC"$n΢΢һЦ�����Ա�����ȥ��$N���н�����ڵ��ϣ��γ�һ���޴����ӡ�\n"NOR,me,target);		
		
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
       if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?3:1);
        if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
        if(me->is_fighting(target)
			&&me->query_skill_mapped("staff")=="wushang-dali"
			&&me->query_skill_mapped("claw")=="tianwang-zhua")
    	{	
		  weapon->unequip();
		  message_vision(WHT"$N�������е�"+weapon->query("name")+WHT"ͻȻ��ָ��ץ��ʩչ������������צ������\n"NOR,me,target);

		  me->add_temp("apply/attack",me->query_skill("tianwang-zhua",1)/2);
		  me->add_temp("apply/damage",me->query_skill("tianwang-zhua",1)/4);
		  if (!userp(target))
			target->add_busy(2);
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
		  me->add_temp("apply/attack",-me->query_skill("tianwang-zhua",1)/2);
		  me->add_temp("apply/damage",-me->query_skill("tianwang-zhua",1)/4);
          weapon->wield();        
		}
		if (me->query_temp("wsdl/dalitemp"))
        {
			me->add_temp("apply/attack", -ski/2);
	        me->add_temp("apply/damage", -ski/4);
			me->add_temp("apply/staff", -ski/4);
			me->delete_temp("wsdl/dalitemp");
        }
		me->start_perform(3,"���ϴ���");
		me->delete_temp("wushang_dali");
        me->start_busy(1);
        return 1;
}

string perform_name(){ return HIR"���ϴ���"NOR; }

int help(object me)
{
        write(HIR"\n���ϴ�����֮�����ϴ�������"NOR"\n\n");
        write(@HELP 
	���ϴ������Ǵ����µ��ӳ��ڵ��似����
	�Խ��ַ������Ӵ���ͣ����������������
	���ǽ��ַ�������ϯ�����ӡ�������Ӣ��
	��һս������һ�ƴ�ʦ����ӣ���������
	�������ס���Ҫ������צ��ϣ������γ�
	��Ч��������Ӱ��������
	ע�⣺��Ч����������Ҫ50��
	
	ָ�perform staff.dali
	
Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	�������Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	����צ���ȼ� 250 ���ϣ�
	�����ڹ��ȼ� 250 ���ϣ�
	�����ȷ��ȼ� 250 ���ϣ�
	����צ��Ϊ����צ���ұ�����צ��
	�����м�Ϊ���ϴ����ƣ�
	�����ȷ�Ϊ���ϴ����ƣ�
HELP
        );
        return 1;
}