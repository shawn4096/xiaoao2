// tianyin.c ���ڴ���ӡ֮��ӡ
#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HIY"��������ӡ��"NOR; }

int perform(object me, object target)
{
	int lvl;
	string msg;

	if( !target ) target = offensive_target(me);


    if( !target  
          || !me->is_fighting(target)
          || !objectp(target)
          || environment(target)!= environment(me))
           return notify_fail("��������ӡֻ�ܶ�ս���еĶ���ʹ�á�\n");

	    if( objectp(me->query_temp("weapon")) )
		   return notify_fail("�������ֲ���ʹ�á���������ӡ������\n");		
	    if((int)me->query_skill("longxiang-boruo",1)<250)
           return notify_fail("��������������Ϊ������\n");	
        if( (int)me->query_skill("dashou-yin", 1) < 250 )
		   return notify_fail("������ڴ���ӡ��Ϊ����������ʹ�á���������ӡ������\n");
		if(me->query_skill_mapped("hand")!="dashou-yin" 
		||me->query_skill_prepared("hand")!="dashou-yin"
		||me->query_skill_mapped("parry")!="dashou-yin")
		   return notify_fail("��û�м������м����ڴ���ӡ������ʹ�á���������ӡ������\n");
        if((int)me->query("max_neili",1)<1000)
           return notify_fail("���������Ϊ̫���޷�ʹ�ñ��ơ�\n");                        
        if( (int)me->query("neili", 1) < 500 )
		   return notify_fail("����������̫��������ʹ�á���������ӡ������\n");
        if((int)me->query_skill("poison",1)<80)
            return notify_fail("��Ķ����������޷�����ͳ��ƶ���\n");			
	    //if( me->query_temp("dls/dsy"))
            //return notify_fail("������ʩչ����ӡ������\n");			
	    msg = HIY "$NĬ���ŭ�䣬�����ڹ���ʮָ���ɣ�˫�ֶ�Ȼ��������������һ���Ϻ�֮������$n��\n"NOR;
	    msg +=  "����һ�С�"HIG"�������������콵ħ��ӡ"NOR"����\n\n"NOR;
        message_vision(msg, me, target);  
		
		me->set_temp("dls/dsy",1);
        //if( objectp(target)&&!target->is_killing(me) ) target->kill_ob(me);

        if( objectp(target)&&target->query_temp("fanzhen")){
             msg=HIY"$n ������������$Nһ�ƻ����ؿ�֮�ϣ�ֻ�����һ����$N���ƶ�������������أ�\n"
                   +"$Nʧ�����У�����ղ������񹦣�����æ�������ܡ�\n"NOR;     	
                me->add("neili", -300);
                me->apply_condition("dsy_poison", 1+random(1) );
             	message_vision(msg, me, target);
               // return 1;
        }	

    
	lvl =( (int)me->query_skill("poison",1) +  (int)me->query_skill("dashou-yin", 1) ) /3 ;

    //if (me->query_skill("dashou-yin",1)>350 ||!userp(me))
	      // lvl=lvl/3;
	//if (userp(target)) lvl=lvl/2;
	//else lvl=lvl/2;

		me->add_temp("apply/damage", lvl);
	    me->add_temp("apply/strength", lvl/10);
	    me->add_temp("apply/hand", lvl);
	    me->add_temp("apply/attack", lvl);
		
	if( objectp(target) && me->is_fighting() )
	{
		if (random(5)>2 && !target->query_condition("dsy_poison"))
		{
			message_vision(HIG"$N���з���һƬ�̹⣬ӡ��$n���ؿڣ�$nһ��С���ж��ˡ�\n"NOR,me,target);
			target->apply_condition("dsy_poison", random(3) + 2 );
		}
		COMBAT_D->do_attack(me, target, 0, random(2)?3:1);

	}
	if(objectp(target) && me->is_fighting() )
		COMBAT_D->do_attack(me, target, 0, me->query_skill("dashou-yin",1)>160?3:1);

	if( objectp(target) && me->is_fighting() )
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
    
	if (me->query("quest/dls/dsy/tianyin/pass") && objectp(target)&& me->is_fighting())
	{
		message_vision(HIR"$N����Ĭ������ǻۡ������������������ܲ�������Ȼ�ĳ�һ�ƣ�ӡ��$n��ǰ�أ�\n"NOR,me,target);
		me->add_temp("apply/hand",lvl);
		//me->add_temp("apply/damage",lvl);
		COMBAT_D->do_attack(me, target, 0, 3);
		me->add_temp("apply/hand",-lvl);
		//me->add_temp("apply/hand",lvl);
	}
	me->add_temp("apply/damage", -lvl);
	me->add_temp("apply/strength",- lvl /10);
	me->add_temp("apply/hand",- lvl);
	me->add_temp("apply/attack",- lvl);
	
    me->delete_temp("dls/dsy");
	me->start_perform(4, "�������������콵ħ��ӡ");
	me->start_busy(1+random(2));
	return 1;
}


int help(object me)
{
        write(HIG"\n����ӡ���������������콵ħ��ӡ����"NOR"\n\n");
        write(@HELP

	��������ӡ�������Ͻ�ħ��ӡ��������������߶�������Ѫɷ�綾
	�������ˡ������������з����ǿ���ڹ������Լ������ˣ������
	�Լ�ע�⡣�����������еȲ����붾�ƹҹ���
	
	ָ�perform hand.tianyin

Ҫ��
	����������� 1000 ���ϣ�
	��ǰ�������� 700  ���ϣ�
	��ǰ�������� 500  ���ϣ�
	����ӡ�ĵȼ� 250  ���ϣ�
	����������� 250 ���ϣ�
	�����ȼ�   80   ����
HELP
        );
        return 1;
}
