// ����ǹ.c 
//Created by sohu

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return RED"����ǹ"NOR; }
int perform(object me, object target)
{
	string msg;
	int extra;
	object weapon;
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);
	if( !target
		||	!target->is_character()
		||	!me->is_fighting(target) )
		return notify_fail("������ǹ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	
	
	if(me->is_busy())
		return notify_fail("��������æ���ң���Ͼ����ǹ����\n");
    if( (int)me->query_skill("huyan-qiang",1) < 100|| (int)me->query_skill("spear",1) < 100)
        return notify_fail("��Ŀǰ������ʹ����������ǹ����\n");
    if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "spear")
			return notify_fail("��ʹ�õ��������ԡ�\n");
	if( (int)me->query("neili") < 1500 )
         return notify_fail("�������������\n");
	if( (int)me->query("jingli") < 1000 )
         return notify_fail("��ľ���������\n");
    if( me->query_skill_mapped("spear") != "huyan-qiang")
         return notify_fail("�����ڼ������ԣ��޷�ʹ�á�����ǹ�����й�����\n");


	extra = me->query_skill("huyan-qiang",1)/4 ;
	me->add_temp("apply/attack", extra);	
	me->add_temp("apply/damage", extra);
	message_vision(RED  "$N������"+ weapon->name() +"�����������Σ�"+weapon->name() +"�ó�����ǹӰ����$n��ȥ��" NOR,me,target);
	COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
	COMBAT_D->do_attack(me,target, weapon, random(3)?1:3);
	COMBAT_D->do_attack(me,target, weapon, random(3)?1:3);
	me->add_temp("apply/attack", -extra);
	me->add_temp("apply/damage", -extra);
    me->start_perform(3+random(2), "������ǹ��");

	me->start_busy(2);
	return 1;
}

int help(object me)
{
   write(YEL"\n����ǹ��"HIG"����ǹ"YEL"����"NOR"\n");
   write(@HELP
	����ǹ���Ǻ��ӼҴ�������Դ��ս��ʵս��ǿ����
	�ڽ����߹ֵ���������ȫ�𷢣��ԳӸ���ʹ��ǹ������
	Ϊ���	
	����ǹ��������������ǹ��������Է���

	ָ�perform spear.lianhuan

Ҫ��
	����ǹ�� 100 ����
	����ǹ�� 100 ����
	��ǰ���� 1500 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	����ǹ������ǹ����
	����װ��ǹ������;

HELP
   );
   return 1;
}