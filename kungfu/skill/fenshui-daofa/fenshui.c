// paishui.c
// modify by sohu@xojh
//���������似���

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>


inherit F_SSERVER;
int get_current_day_phase();
nosave mapping *day_phase = NATURE_D->query_day_phase(); 

int perform(object me, object target)
{
	object weapon, ob;
	string msg; 
	int skill;
	skill=me->query_skill("fenshui-daofa",1);
	
	 if( !target ) target = offensive_target(me);
         if( !target || !target->is_character() || !me->is_fighting(target) )
 	      return notify_fail("����ˮ������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        
 	
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");
           
         
	if( (int)me->query("max_neili") < 1600 )
		return notify_fail("���������������ˣ�\n");

	if( (int)me->query_skill("blade",1) < 140 ||
	    me->query_skill_mapped("blade") != "fenshui-daofa")
		return notify_fail("��ġ������������������ң��޷�ʹ�á���ˮ��������\n");
        
    if( (int)me->query_skill("fenshui-daofa",1) < 140 )
            return notify_fail("��ġ���ˮ�������������ң��޷�ʹ�á���ˮ��������\n");
	if( (int)me->query("neili") < 800 )
            return notify_fail("��ĵ�ǰ��������800���������ң��޷�ʹ�á���ˮ��������\n");
	if( (int)me->query("jingli") < 500 )
            return notify_fail("��ĵ�ǰ��������500���������ң��޷�ʹ�á���ˮ��������\n");
        msg = HIW "$N��Ȼ������һ���ݺ��������ᣬ������������,״����ˮʽ������$n�����ţ�\n" NOR;
        message_vision(msg, me, target);
     if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 )	
	 {  
		msg = HIW "$Nֻ��������˸������ޱȣ�$n��״��ϲ������������������ͬ�ķ�������\n" NOR;	
	    message_vision(msg, target,me);
	   
	    target->add_busy(1);
		if (!userp(target)) target->add_busy(1);
		
	  }
	me->add_temp("apply/attack",skill/4);
	me->add_temp("apply/attack",skill/5);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	me->add_temp("apply/attack",-skill/4);
	me->add_temp("apply/attack",-skill/5);

	me->add("neili", -150);
	me->add("jingli",-80);
	me->start_busy(random(1));
    me->start_perform(3,"��ˮ����");
	return 1;
}


string perform_name(){ return HIW"��ˮ����"NOR; }

int help(object me)
{
        write(HIB"\n��ˮ����֮����ˮ��������"NOR"\n\n");
        write(@HELP
	��ˮ��������ɽ��������ſ����书�����в�����ɳ����
	����������ˮ�ϣ�������һ�Ŷ��صķ�ˮ�����似����ˮ
	��������˲�䱬�����С�

	ָ�perform blade.fenshui

Ҫ��
	��ǰ�������� 800 ���ϣ�
	����������� 1600 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��ˮ�����ȼ� 140 ���ϣ�
	���������ȼ� 140 ���ϣ�
	��������Ϊ��ˮ������
	�ڹ����ޣ�
	���ֳֵ��������

HELP
        );
        return 1;
}