//By sohu@xojh ��ħ��

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name(){ return HIR"��ħ��"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i;
    
    if( !target ) target = offensive_target(me);
     
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("��ħ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

   // if(me->query_skill_mapped("force") != "huntian-qigong")
               // return notify_fail("����ڹ����ǻ����������޷�ʹ�÷�ħ����\n");
    if( (int)me->query_skill("force", 1) < 350 )
                return notify_fail("��Ļ����ڹ���δ���ɣ�����ʹ�÷�ħ����\n");
    if( (int)me->query_skill("fengmo-zhang", 1) < 350 ) 
                return notify_fail("��ķ�ħ�ȷ���δ���ɣ�����ʹ�÷�ħ����\n");
    if((int)me->query_skill("staff", 1) < 350 )
                return notify_fail("��Ļ����ȷ�������죬������ʹ�÷�ħ����\n");
    if((int)me->query_dex(1) < 40 )
                return notify_fail("��������������ɣ�����ʹ�÷�ħ����\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "fengmo-zhang"
        || me->query_skill_mapped("parry") != "fengmo-zhang")
                return notify_fail("�����ڲ�������ħ�ȷ���ʹ���˷�ħ��ô��\n");
                
    if((int)me->query("max_neili") < 4500 )
                return notify_fail("���������Ϊ����������ʹ�÷�ħ����\n");
    

    message_vision(HIR"\n$N״�����ŭ����ڣ����һ������Ȼ���ˣ������е�"+weapon->query("name")+RED"��Բ�ˣ�˲����$n�ӳ�һ������У�\n"NOR,me,target);

       
    i = me->query_skill("fengmo-zhang",1);
	if (me->query_skill("huntian-qigong",1)>350)
		    i += (int)me->query_skill("huntian-qigong",1)/5;
        
		me->add("neili", -300);
        me->add_temp("apply/attack",  i/3);
        me->add_temp("apply/damage",  i/4);
        
        me->set_temp("fmz/fengmo",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<350)?1:3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<250)?1:3);
		
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
	       
		if (me->is_fighting(target)
		&& me->query_skill_prepared("hand")=="suohou-shou"
		&& me->query_skill("suohou-shou",1)>300)
		{
		 weapon->unequip(); 
	     me->add_temp("apply/hand", i/3);
		 message_vision(HIR"$N�����е�"+weapon->query("name")+HIR"�������У�������������Ȼʩչ������������������!\n"NOR,me,target);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
		 target->add_busy(1);
		 me->add_temp("apply/hand", -i/3);
         weapon->wield();
		}
        me->add_temp("apply/attack",  -i/3);
        me->add_temp("apply/damage",  -i/4);
        me->delete_temp("fmz/fengmo");
    
    me->start_busy(1);
    target->start_busy(1);
	me->start_perform(3+random(2),"����ħ����");
    return 1;
}

int help(object me)
{
   write(WHT"\n��ħ�ȷ�֮"HIR"����ħ������"NOR"\n");
   write(@HELP
	��ħ�ȷ�����ؤ�����ݷֶ������Ϊ�ĳ����似�����ȷ�ԭ��Դ�����֡�
	�����ڽ���������������������ȥܽ�澫��ʹ�÷�ħ�ȷ����Ͼ�������ʽ
	Խ��Ϭ������ħ������ƾ��һ���������ܲ����Լ��İ�Σ��ȫ��������˲
	��ʩչ��һ������й�������Է�Ŀ��Ͼ�ӣ�����Ӧ����
	ע�⣺���������� hand ������,300��������ٳ�һ�С�����������,350
	   ����������������������ʹ���칦���з�Ծ��
	
   ָ�perform staff.fengmo

Ҫ��  
	������� 4500 ���ϣ�
	��ǰ���� 2000 ���ϣ�
	��ħ�ȷ��ȼ� 350 ���ϣ�
	�����ڹ��ȼ� 350 ���ϣ�
	������ 40 ���ϣ�
	�����м�Ϊ��ħ�ȷ�,
	װ���ȷ�

HELP
   );
   return 1;
}
