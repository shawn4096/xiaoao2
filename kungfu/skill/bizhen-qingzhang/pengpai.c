// bizhen-qingzhang  �������� ������
//KinGSo
 
#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

string perform_name() {return HBBLU HIC"������"NOR;}

int perform(object me, object target)
{
        int lev;
        
        if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
                return notify_fail("�������ơ�ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á������ơ���\n");   

        if( (int)me->query_skill("bizhen-qingzhang", 1) < 100 )
                return notify_fail("����Ʒ���������죬ʹ�����������ơ�������\n");

        if((int)me->query_skill("force",1) < 160 ) 
                return notify_fail("����ڹ���Ϊ��������ʹ�����������ơ�������\n");
               

        if (me->query_skill_prepared("strike") != "bizhen-qingzhang" 
         || me->query_skill_mapped("strike") != "bizhen-qingzhang" )
                return notify_fail("�������޷�ʹ�á������ơ���\n"); 
    

        if( (int)me->query("neili") < 1000)
                return notify_fail("����������̫����ʹ�����������ơ���\n");

        if( (int)me->query("jingli") < 1000 )
                return notify_fail("�����ھ���̫�٣�ʹ�����������ơ���\n");
       
		

        lev = (int)me->query_skill("bizhen-qingzhang", 1); 
        
        message_vision(HBBLU HIC"\n$N�ĵ��Ʒ磬˫�ƻ����һ����Ȧ���������ơ����ƶ�������ʱһ����ӿ�����Ƶľ����粨��һ����$nӿ����\n"NOR,me,target);
        me->add_temp("apply/damage", lev/6);
        me->add_temp("apply/attack", lev/6);       

		me->set_temp("bzqz/pengpai",1);
        COMBAT_D->do_attack(me, target, 0, 3);
	    if( me->is_fighting(target))
		 COMBAT_D->do_attack(me, target, 0, 3);
       
        if( me->is_fighting(target)
			&& (int)me->query_skill("bizhen-qingzhang",1) > 120 ) 
		{
            if((int)me->query_skill("bizhen-qingzhang",1)>=250 )
                    COMBAT_D->do_attack(me, target, 0, 3);
            else
                    COMBAT_D->do_attack(me, target, 0, 1);
            
        }
        if( me->is_fighting(target) 
			&& (int)me->query_skill("bizhen-qingzhang",1) > 159 )
		{
            if((int)me->query_skill("bizhen-qingzhang",1)>=250 )
         		COMBAT_D->do_attack(me, target, 0, 3);
	        else	COMBAT_D->do_attack(me, target, 0, 1);
            
        }
        
        me->add_temp("apply/damage", -lev/6);
        me->add_temp("apply/attack", -lev/6);
        me->add("neili", -500);
        me->add("jingli", -200);
		me->delete_temp("bzqz/pengpai");
        me->start_perform(5,"�������ơ�");
        return 1;
}

int help(object me)
{
   write(HIC"\n�������ơ�"HBBLU HIC"������"HIC"����"NOR"\n\n");
   write(@HELP
	����������Ħ���ʿл�̿Ͷ��ž�����һ��ʩչ
	��Χ��Բһ���ڽ�Ϊ�������֣���ν���Ⱦ�����
	ӿ�糱������������
	
	ָ�perform strike.pengpai

Ҫ��: 
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	�������Ƶȼ� 400 ���ϣ�
    �����ڹ��ȼ� 400 ���ϣ�
	�����Ʒ�Ϊ�������ƣ�
	�ڹ����ޣ�
	���֣����������ơ�

HELP
   );
   return 1;
}

