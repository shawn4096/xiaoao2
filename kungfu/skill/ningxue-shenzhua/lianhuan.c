

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;


int perform(object me, object target)
{
        int lv,lvf, i, hit;
         string weapon, lzg_msg;

        if( !target ) target = offensive_target(me);
        
		if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("��Ѫ��ץ��������ץ����ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�������ץ������\n");   
        if( (int)me->query_skill("ningxue-shenzhua", 1) < 500 )
                return notify_fail("�����Ѫ��ץ��������죬ʹ������������ץ����������\n");
        if (me->query_skill_prepared("claw") != "ningxue-shenzhua"
        || me->query_skill_mapped("claw") != "ningxue-shenzhua")
                return notify_fail("�������޷�ʹ�á�������ץ�������й�����\n");  
        if( (int)me->query_str() < 60 )
                return notify_fail("���ڱ�������60���޷�ʹ�á���Ѫ��������!\n");

	    if( me->query_skill("force",1)<500 )
		        return notify_fail("�����ڵĻ����ڹ��ȼ�����������ʹ�á�������ץ������\n");
        if( (int)me->query_skill("claw", 1) < 500 )
                return notify_fail("��Ļ���צ���ȼ���������ʹ������������ץ����������\n");
        if( me->query("max_neili") < 15000 )
                return notify_fail("����������̫����ʹ������������ץ������\n");      
        if( (int)me->query("neili") <1500 )
                return notify_fail("����������̫����ʹ������������ץ������\n");
      
        
        lv = me->query_skill("ningxue-shenzhua",1);
        hit = (lv/70);
        
		if(hit > 8) hit = 8;
        if(hit <3) hit = 3;
		
		if (target->is_busy())
		{
			message_vision(HIY"$N��$n�Ѿ��Թ˲�Ͼ�����һ������Ѫ����������צ�У���Ѫ��ץ������ʱ���Ӳ��١�\n"NOR,me,target);
			target->add_condition("nxsz_hurt",1);
			lv+=lv/4;
		}
        me->add_temp("apply/attack", lv/4);
		me->add_temp("apply/claw", lv/6);
        me->add_temp("apply/damage", lv/6);
       
		lzg_msg = HIR"\n$NĬ������������һƬ���Σ�����������˫�֣���Ȼ��$n�������У�������Ѫ��ץ������������ץ����:��ʱ \n";
/*
        if(hit >= 2)lzg_msg += HIG"�����־����������־���"NOR;
        if(hit >= 4)lzg_msg += HIY"�������־����������־���"NOR;
        if(hit >= 6)lzg_msg += HIM"�������־�������ץ�־���"NOR;
        if(hit >= 8)lzg_msg += HIC"�������־����������־���"NOR;
 */       
        lzg_msg += "��\n"+chinese_number(hit)+"ʽ����������ץӰ����$n����������\n"NOR;

        message_vision(lzg_msg, me, target);
        
		me->set_temp("lzg_times",hit);
        //me->set_temp("nxsz/shenzhua",0);
        
		me->set_temp("action_flag", member_array("claw", keys(me->query_skill_prepare())));
        //me->set_temp("baocan",hit);
		
		if (hit>7)
		{
			   
                COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				 me->set_temp("nxsz/shenzhua",8);
		}
			
		else{
        for( i=0; i < hit; i++ )
        {
                
				me->add_temp("nxsz/shenzhua", 1);
                COMBAT_D->do_attack(me, target, weapon, 3);
        }
		}


       message_vision(HIR"\n��"+chinese_number(hit)+"ʽ�������಻����"+chinese_number(hit)+"���仯�ں�Ϊһ������ޱȣ�\n"NOR, me);

        me->add("neili", -hit*50+20);
        me->add("jing", -hit*50);
        me->add_temp("apply/attack", -lv/4);
        me->add_temp("apply/damage", -lv/6);
		me->add_temp("apply/claw", -lv/6);
       // me->add_temp("apply/parry", lv/5);
	    me->start_perform(6,"��������ץ����");
        me->start_busy(1+random(2));
        me->delete_temp("nxsz/shenzhua");
        
        return 1;
}

string perform_name(){ return HBRED+HIY"������ץ��"NOR; }

int help(object me)
{
   write(WHT"\n��Ѫ��צ��"HBRED+HIY"������ץ��"WHT"����"NOR"\n");
   write(@HELP
	����Ѫ��צ������ػ��ܶ����½��������ĳ������ա������У�
	���д���צ֮�ˣ������ȫ��ѪҺ�����������ɽ���һ�㣬��ҩ
	���Ρ�������ץ������˲���������У�����ץ��Է�Ҫ��������Ѫ
	��ץ���ռ�������
	
	ָ�perform claw.shenzhua

Ҫ��
	��ǰ���� 1500 ���ϣ�
	������� 15000 ���ϣ� 
	������� 60 ���ϣ� 
	��Ѫ��צ�ȼ� 500 ���ϣ�
	����צ���ȼ� 500 ���ϣ�
	�����ڹ��ȼ� 500 ���ϣ�
	����צ��Ϊ��Ѫ��צ��
	�����м�Ϊ��Ѫ��צ��
	��צ�������ޱ�����

HELP
   );
   return 1;
}
