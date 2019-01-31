// piaojian.c Ʈ����
// Created by sohu@xojh 2015 

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
	object weapon;
	int focus;
	int j,ap,dp,damage,p;
	string msg;
	if (me->query_skill_mapped("force") == "lengquan-shengong")
		focus =me->query_skill("force",1)+ me->query_skill("lengquan-shengong",1);
	else focus =me->query_skill("force",1);
	
	        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("��Ʈ������ֻ����ս����ʹ�á�\n");
        
	if( (int)me->query_skill("miaojia-jianfa", 1) < 400 )
		return notify_fail("�����ҽ�����������죬�޷�ʹ����Ʈ��������\n");

	if( (int)me->query_skill("force", 1) < 400 )
		return notify_fail("��Ļ����ڹ��ȼ����������޷�ʹ����Ʈ��������\n");
	if( (int)me->query_skill("sword", 1) < 400 )
		return notify_fail("��Ļ��������ȼ����������޷�ʹ����Ʈ��������\n");
	

	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("parry") != "miaojia-jianfa"
	|| me->query_skill_mapped("sword") != "miaojia-jianfa" )
		return notify_fail("���޷�ʹ����Ʈ��������\n");

	if (me->query_temp("mjjf/piaojian"))
		return notify_fail("������ʹ�á�Ʈ����������Ϣһ�°ɡ�\n"); 
    //if (target->is_busy())
	//	return notify_fail("�Է��Ѿ���æ�����ˣ�����ʹ�����С�Ʈ��������\n"); 
           
	if( (int)me->query("max_neili") < 5000)
		return notify_fail("���������Ϊ̫��޷�ʹ����Ʈ��������\n");
                
	if( (int)me->query("neili") < 1000)
		return notify_fail("����������̫����ʹ������Ʈ��������\n");
	if( (int)me->query("jingli") < 1000)
		return notify_fail("�����ھ���̫����ʹ������Ʈ��������\n");

	j = me->query_skill("miaojia-jianfa", 1);
			
	

	message_vision(HIW"ͻȻ֮�䣬$N��Ȼʩչ����ҽ����С�"HIC"���ý��׺����"HIW"����ʽ���������㣬����׺�չ�᰿�衣\n"NOR,me);
			
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER );
	
	

		
	message_vision(HIW"\n$n��֪$N���书�������Ȼ֮��Ϊ$Nͻ�����������Ի󣬶�ʱ��Щ����ʧ�롣\n"
	                  +"$N������չ���󣬽������಻������������������������ҽ�����"HIG"��Ʈ������"HIW"�ľ�����\n"NOR,me,target);

	me->set_temp("mjjf/piaojian",j);
	
	me->add_temp("apply/attack",j/4);
	me->add_temp("apply/parry", j/4);
	me->add_temp("apply/dodge", j/4);
	me->add_temp("apply/dexerity", j/10);

	call_out("effect_check",1,me,(int)j/25);

	me->add("neili", -400-random(200));
	me->add("jingli", -300-random(100));
    if (me->query_skill("miaojia-jianfa",1)<450)
		me->start_perform(1, "Ʈ����");
	
    return 1; 
}

int effect_check(object me,int count)
{
	int j;
	object weapon;
	//j=me->query_temp("mjjf/piaojian");
	
	if (!me) return 0;
	j=me->query_skill("miaojia-jianfa",1);

	weapon=me->query_temp("weapon");
	//write("j="+j);
	if (!me->is_fighting()
		||me->query_skill_mapped("sword")!="miaojia-jianfa"
		||!objectp(weapon)
		||weapon->query("skill_type")!="sword"
		||count< 1)
	{
		me->add_temp("apply/attack",-j/4);
		me->add_temp("apply/parry", -j/4);
		me->add_temp("apply/dodge", -j/4);
		me->add_temp("apply/dexerity", -j/10);
		me->delete_temp("mjjf/piaojian");

		//write("j1="+j/3);
		message_vision(HIW"$N����һ�ͣ����ζ�ʱ�ٻ�������Ʈ�������������С�\n"NOR,me);
		return 1;
	}
	call_out("effect_check",2,me,count--);
	//return 1;
}
string perform_name(){ return HIW"Ʈ����"NOR; }

int help(object me)
{
        write(YEL"\n��ҽ���֮��Ʈ��������"NOR"\n\n");
        write(@HELP
	��ҽ������Ǵ�������޵��ֵ����˷�Ҵ�����
	�ý���ʤ������䣬�����쳣������û������
	ʵ�������в��ɶ�õ�һ���似��
	��Ʈ����������������߳����Ṧ���ƣ�������
	�����ں���һ�𣬽�������Ʈ��֮�ƣ�������
	��ķ����Ͷ�ܣ���������ʽ�ɻ��һ���Ķ��
	�˺���Ч��
	ע�⣺��Ҫ����������мܷ���ʹ��
	
	ָ��:perform sword.piaojian

Ҫ��
	��ǰ�������� 1000 ���ϣ�
	����������� 5000 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	��ҽ����ȼ� 400 ���ϣ�
	�����ڹ��ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	��������Ϊ��ҽ�����
	�����м�Ϊ��ҽ�����
	���ֱֳ�����

HELP
        );
        return 1;
}
