// pi.c ��ǹ��--����
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return RED"����"NOR; }
int perform(object me, object target)
{
	string msg;
	int extra;
	object weapon;
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);
	if(me->is_busy())
		return notify_fail("��������æ���ң���Ͼ��������\n");
    if( (int)me->query_skill("yangjia-qiang",1) < 100|| (int)me->query_skill("spear",1) < 100)
        return notify_fail("��Ŀǰ������ʹ��������������\n");
    if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "spear")
			return notify_fail("��ʹ�õ��������ԡ�\n");
	if( (int)me->query("neili") < 1500 )
         return notify_fail("�������������\n");
	if( (int)me->query("jingli") < 1000 )
         return notify_fail("��ľ���������\n");
    if( me->query_skill_mapped("spear") != "yangjia-qiang"
        || me->query_skill_mapped("parry") != "yangjia-qiang")
         return notify_fail("�������޷�ʹ�á����������й�����\n");

	if( !target
		||	!target->is_character()
		||	!me->is_fighting(target) )
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	
	extra = me->query_skill("yangjia-qiang",1)/4 ;
	me->add_temp("apply/attack", extra);	
	me->add_temp("apply/damage", extra);
	message_vision(RED  "$N���е�"+ weapon->name() +"�ó�һ��ǹӰ��"+weapon->name() +"���Ƴ��գ�ͻȻ��$n���ȥ��" NOR,me,target);
	COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
	COMBAT_D->do_attack(me,target, weapon, random(3)?1:3);
	COMBAT_D->do_attack(me,target, weapon, random(3)?1:3);
	me->add_temp("apply/attack", -extra);
	me->add_temp("apply/damage", -extra);
    me->start_perform(3+random(2), "��������");

	me->start_busy(2);
	return 1;
}

int help(object me)
{
   write(YEL"\n���ǹ��"HIG"����"YEL"����"NOR"\n");
   write(@HELP
	���ǹ���Ǵ��Ա��������ҽ���ǹ�����������ϻ���
	���¶���Ϊʵս�����С�����ǹ������ս���к�Ȼ����
	����ַ���ʤ����ɱ�����Ĵ󡣵������У��Լ�Ҳ����
	��������á�

	ָ�perform spear.shanji

Ҫ��
	���ǹ�� 100 ����
	����ǹ�� 100 ����
	��ǰ���� 1500 ���ϣ�
	��ǰ���� 1000 ���ϣ�
HELP
   );
   return 1;
}
