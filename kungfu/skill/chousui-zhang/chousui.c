// chousui.c ��������
// Created and Modified by spiderii

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        
        int j, lvl = me->query_skill("chousui-zhang", 1);
        if (me->query("quest/hgdf/powerup"))
            lvl = me->query_skill("chousui-zhang", 1)+me->query_skill("huagong-dafa", 1);
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target)
         || !living(target) )
                return notify_fail("���������衹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        
        if( (int)me->query_skill("chousui-zhang", 1) < 400 )
                return notify_fail("��ĳ����ƹ���̫ǳ���������ˡ�\n");

        if( (int)me->query_skill("strike", 1) < 400 )
                return notify_fail("��Ļ����Ʒ�����̫ǳ���������ˡ�\n");

        
        if( (int)me->query_skill("force", 1) < 400 )
                return notify_fail("����ڹ�����̫ǳ���������ˡ�\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 400 )
                return notify_fail("��Ļ�����̫ǳ���������ˡ�\n");

        if( (int)me->query("max_neili") < 9000 )
                return notify_fail("�������̫ǳ���������ˡ�\n");

        if( (int)me->query("neili") < 3000 )
                return notify_fail("��������������������ˡ�\n");
        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang")
                return notify_fail("������ó����Ʋ���ʹ�á��������衹���й�����\n"); 
                                                                                         
        if(me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("�㷢���Լ����õ��ڹ��޷����С��������衹������\n");                
        
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á��������衹��\n");           
        
		j = lvl/3;

        if ( lvl > 350 )
                j = to_int(lvl/3.0 * lvl/275.0);
        message_vision(BLU"\n$N"BLU"����$n���ٵ�ת�˼�Ȧ������һ������צ���棬���������ƶ������Ϯ��$n�� "BLU"��\n"NOR, me,target);

        me->set_temp("csz/chousui", 3);
		if (wizardp(me))
		{
			write("j="+j);
		}
        me->add_temp("apply/strike", j);
        me->add_temp("apply/attack", j);
        me->add_temp("apply/damage", j/2);
        //�����ұ�sanyin-zhua >450�������
        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		
        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		
        if( me->is_fighting(target) )
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
		if (me->query_skill("sanyin-zhua",1)>450
			&&me->query_skill_mapped("claw")=="sanyin-zhua"
			&&me->query_skill_prepared("claw")=="sanyin-zhua"
			&&objectp(target)&&me->is_fighting())
        {
			me->prepare_skill("claw","sanyin-zhua");
			message_vision(HBWHT+HIB"$N����һЦ������Ϊץ����ͼץס$n������\n"NOR,me,target);
			if (random(me->query_str())>target->query_str()/2||random(me->query("combat_exp"))>target->query("combat_exp")/2)
			{
				target->add_busy(2);
				message_vision(CYN"$nһ��С��Ϊ$N������ץ��ץס����ʱ���β��ȡ�\n"NOR,me,target);
			}
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);

			me->prepare_skill("strike","chousui-zhang");
        }
		/*
		if( me->is_fighting(target)&&me->query("hgdf/powerup") )
	    {
			message_vision(HIB"$N����������������Ļ����󷨾���ʩչ�������ںڵ����ƺ�Ȼ��ʼ�����֮��������ɢ������\n"NOR,me,target);
			target->add_busy(1+random(1));
			target->set_temp("must_be_hit",1);
			message_vision(BLU"$nһ��С�����붾�����а���һ�����ã��ֽ��ƺ���Щ��ľ��\n"NOR,me,target);
			target->apply_condition("no_perform",1);
			target->apply_condition("no_exert",1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			target->delete_temp("must_be_hit");
		}*/
        me->add_temp("apply/strike", -j);
        me->add_temp("apply/attack", -j);
        me->add_temp("apply/damage", -j/2);

        

        me->delete_temp("csz/chousui");

        me->start_busy(random(2));
        me->add("neili", -300);
        me->add("jingli", -150);
        me->start_perform(3, "���������衹");
        return 1;
}

string perform_name(){ return HBBLU"��������"NOR; }

int help(object me)
{
        write(HBBLU"\n������֮���������衹��"NOR"\n\n");
        write(@HELP
	�����ɵĹ�����Ҫ����<��>�����¹������������������ζ
	������������ս���У�ƾ������ڹ������ڴ涾�Ƴ������˵е�
	һ�Ź��򡣡��������衹һʽ�����Կ������һ���־���������
	ʽ����Է��������а�����ѷ���,���⿪���������⣬����
	������һ̨�ף�
	ע�⣺�����ƺ�����ץ���Ի�����������Ч����������벻����
		ɱ����
	
	perform strike.chousui

Ҫ��
	��ǰ�������� 3000 ����;
	����������� 9000 ���ϣ�
	�����Ʒ��ȼ� 400 ���ϣ�
	�����󷨵ȼ� 400 ���ϣ�
	�����Ʒ��ȼ� 400 ���ϣ�
	�����ڹ��ȼ� 400 ����;
	�������ޱ�����

        
HELP
        );
        return 1;
}

