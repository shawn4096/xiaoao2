// honglian.c  ���浶 [������]
//2006��12��24��KinGSo�±༭,���HELP

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string perform_name(){ return HBYEL+HIR"������"NOR; }
int check_fight(object me);

int perform(object me, object target)
{
    int i,y,j,c;
          
      
    if( objectp(me->query_temp("weapon")) )
		return notify_fail("��������ֻ�ܿ���ʹ�á�\n");
     
	if( !target ) target = offensive_target(me);

    if( !target 
         || !me->is_fighting(target)
         || !objectp(target)
         || environment(target)!= environment(me))
		return notify_fail("��������ֻ����ս���жԶ���ʹ�á�\n");
        
	if((int)me->query_skill("huoyan-dao",1) < 450)
		return notify_fail("��Ļ��浶��Ϊ������ Ŀǰ����ʹ�á��������𡹡�! \n");

	if((int)me->query_skill("longxiang-boruo",1) < 450)
		return notify_fail("��������������Ϊ������ Ŀǰ����ʹ�á�������! \n");
	if((int)me->query_skill("force",1) < 450)
		return notify_fail("��������������Ϊ������ Ŀǰ����ʹ�á�������! \n");

	if( me->query_skill_mapped("strike") != "huoyan-dao")
		return notify_fail("�����ʹ�û��浶������ʹ�á������𡹵ľ�����\n");

	
	if( (int)me->query("max_neili") < 9000 )
		return notify_fail("���������Ϊ������\n");
	if((int)me->query("neili")<2500)
		return notify_fail("�������������\n"); 
	if((int)me->query("jingli")<1000)
		return notify_fail("��ľ���������\n"); 

    message_vision(RED "ֻ��$N��ɫ��Ȼ���ֽ�"HIW"��������ӡ"RED"��ͻȻһ��"HIR"��������"RED"Ѹ���ޱȵع���$n��\n"NOR,me, target);
    i = (int)me->query_skill("huoyan-dao", 1);
    y = (int)target->query_skill("parry", 1);
    
    //me->add_temp("apply/strength", i/20);
    me->add_temp("apply/attack", i/2);
    me->add_temp("apply/damage", i/5);
	me->set_temp("hyd/honglian/power",4);
	//���е���������������
    if(me->query_temp("hyd/power"))
	{
       message_vision(HIM "$N�ͺ�һ��,��ϵ���������"HIR"��������"HIM"����ʩչ�����£�$n��ȫ��$N�ĵ������㣡\n"NOR,me, target); 
       me->set_temp("hyd/honglian/power",3);
       target->start_busy(1+random(2));
    }
    
	COMBAT_D->do_attack(me, target, 0, random(2)?1:3); //��һ��

	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, i>350?3:1); //�ڶ���

	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, i>450?3:1); //������

	if ( me->is_fighting(target) &&me->query_temp("hyd/power")&& me->query_skill("huoyan-dao",1)>449)
	{
           me->add_temp("apply/attack",i/3);
		   me->add_temp("apply/damage",i/5);
		   COMBAT_D->do_attack(me, target, 0, 3); //������,����ɳ�൱
		   me->add_temp("apply/attack",-i/3);
		   me->add_temp("apply/damage",-i/5);
	}
/*
	if ( me->is_fighting(target) &&me->query_temp("hyd/power") && me->query_skill("huoyan-dao",1)>449 )
           COMBAT_D->do_attack(me, target,0, 3); //������
    if ( me->is_fighting(target) &&me->query_temp("hyd/power") 
    && me->query_skill("huoyan-dao",1) >549 
    && me->query_skill("longxiang-boruo",1) >549
    && me->query_temp("xs/longxiang"))
           COMBAT_D->do_attack(me, target,0, 3); //�����У�550������*/
                    
     me->delete_temp("hyd/honglian/power");
     me->add("jingli", -100*(1+random(2)));
     me->add("neili", -100*(2+random(2)));
     
    // me->add_temp("apply/strength", -i/20);
     me->add_temp("apply/attack", -i/2);
     me->add_temp("apply/damage", -i/5);
     me->start_perform(4,"��������");         
     return 1;
                 
}

int help(object me)
{
	write(HIR"\n���浶�ؼ��������𡹣�"NOR"\n");
	write(@HELP
	���浶���������,����ս�����ܹ�Ѹ�ݵ������Է���
	������Ͼ��е���ʩչ���������õ��������Ӷ��˵���ʤ��
	��������������´�ɣ���ս������������֮�������ܹ�
	������������������350���з�Ծ,450���ٴη�Ծ��
	
	ָ�perform strike.honglian

Ҫ��
	�������Ҫ�� 9000 ���ϣ�
	��ǰ����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	���������   450 ���ϣ�
	���浶�ȼ�   450 ���ϣ�
	�����ڹ��ȼ� 450 ���ϣ�    
HELP
	);
	return 1;
 }


