// bingcan.c ���϶�����ʽ
// Created by sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        
        int j, lvl = me->query_skill("chousui-zhang", 1);
        
		j=lvl;

		if (!me->query("quest/xx/csz/bingcan/over"))
			 return notify_fail("����δ��ͨ���㾭���޷�ʹ�á����϶��ơ���\n");
		
		if (!me->query("quest/xx/csz/bingcan/pass"))
			 return notify_fail("����Ȼ��ͨ�����㾭����������ת�����˽⣬�޷�ʹ�á����϶��ơ���\n");

		if (me->query("quest/hgdf/powerup"))
			j = me->query_skill("chousui-zhang", 1)+me->query_skill("huagong-dafa", 1)/5;
        
		if (me->query("quest/xx/csz/bingcan/pass"))
		{
			j = j+me->query_skill("huagong-dafa", 1)/5;

		}

		if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target)
         || !living(target) )
                return notify_fail("�����϶��ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        
        if( (int)me->query_skill("chousui-zhang", 1) < 500 )
                return notify_fail("��ĳ����ƹ���̫ǳ���������ˡ�\n");

        if( (int)me->query_skill("strike", 1) < 500 )
                return notify_fail("��Ļ����Ʒ�����̫ǳ���������ˡ�\n");

        
        if( (int)me->query_skill("force", 1) < 500 )
                return notify_fail("����ڹ�����̫ǳ���������ˡ�\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 500 )
                return notify_fail("��Ļ�����̫ǳ���������ˡ�\n");

        if( (int)me->query("max_neili") < 15000 )
                return notify_fail("����������̫ǳ���������ˡ�\n");

        if( (int)me->query("neili") < 3000 )
                return notify_fail("��������������������ˡ�\n");
        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang")
                tell_object(me,"������ó����Ʋ���ʹ�á����϶��ơ����й�����\n"); 
                                                                                         
        if(me->query_skill_mapped("force") != "huagong-dafa")
                tell_object(me,"�㷢���Լ����õ��ڹ��޷����С����϶��ơ�������\n");                
        
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á����϶��ơ���\n");           
        
		
		j = j/3;

        if ( lvl > 350 )
                j = to_int(lvl/3.0 * lvl/350.0);

		message_vision(HBWHT+HIG"\n$N"HIG"˫�ųʶ��ֲ�վ�����ͺ�һ��������˫�ƣ��й�һ������֮������$n����\n"NOR, me,target);
		message_vision(HBWHT+HIB"����������϶��ļй��£�������ʱ��ĳ��棡\n"NOR, me,target);
		
        me->set_temp("csz/bingcan", 5);

        me->add_temp("apply/strike", j);
        me->add_temp("apply/attack", j);
        me->add_temp("apply/damage", j/2);
       
		if (wizardp(me)) write("j="+j);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);

        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
		if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		//if( me->is_fighting(target) )
               // COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
		if( me->is_fighting(target)&&me->query("hgdf/powerup") )
	    {
			message_vision(HIB"$N����������������Ļ����󷨾���ʩչ�������ںڵ����ƺ�Ȼ��ʼ�����֮��������ɢ������\n"NOR,me,target);
			target->add_busy(1+random(1));
			target->set_temp("must_be_hit",1);
			message_vision(BLU"$nһ��С�����붾�����а���һ�����ã��ֽ��ƺ���Щ��ľ��\n"NOR,me,target);
			target->apply_condition("no_perform",1+random(2));
			target->apply_condition("no_exert",1+random(2));
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			target->delete_temp("must_be_hit");
		}

        me->add_temp("apply/strike", -j);
        me->add_temp("apply/attack", -j);
        me->add_temp("apply/damage", -j/2);

        

        me->delete_temp("csz/bingcan");

        me->start_busy(random(2));
        me->add("neili", -300);
        me->add("jingli", -150);
        me->start_perform(3, "�����϶��ơ�");
        return 1;
}

string perform_name(){ return HBWHT+HIB"���϶���"NOR; }

int help(object me)
{
        write(HBBLU"\n������֮�����϶��ơ���"NOR"\n\n");
        write(@HELP
	�����ɵĹ�����Ҫ����<��>�����¹������������������ζ
	������������ս���У�ƾ������ڹ������ڴ涾�Ƴ������˵е�
	һ�Ź��򡣡����϶��ơ�һʽ�����Կ������һ���־���������
	ʽ����ʽƽƽ����������󣬼�������ɽ������ϵĸ�����Ч��
	�������ڳ����Ƶ��ռ���ʽ����Ҫ���ܷ���ʹ�ã�
	
	ָ�perform strike.bingcan

Ҫ��
	��ǰ�������� 3000 ����;
	����������� 15000 ���ϣ�
	�����Ʒ��ȼ� 500 ���ϣ�
	�����󷨵ȼ� 500 ���ϣ�
	�����Ʒ��ȼ� 500 ���ϣ�
	�����ڹ��ȼ� 500 ����;
	�����ڹ�������
	�����Ʒ�������
	�����м�Ϊ������
	�������ޱ�����

        
HELP
        );
        return 1;
}

