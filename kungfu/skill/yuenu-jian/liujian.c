// ɳ�����󽣷� ԽŮ�״�
// by Jpei@NT 2009/05

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HIY"��������"NOR;}

int perform(object me,object target)
{
    object weapon;
    int skill;
	skill=me->query_skill("yuenu-jian",1);
	//if (me->query_skill("force",1)>=550)
		//skill=skill+me->query_skill("force",1)/10;
    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
    if( (int)me->query_skill("yuenu-jian", 1) < 450 )
                return notify_fail("��Ľ�����δ���ɣ�����ʹ����������������\n");
    if((int)me->query_skill("sword", 1) < 450 )
                return notify_fail("��Ļ�������������죬����ʹ������������\n");
    if (!objectp(weapon = me->query_temp("weapon")) 
		|| weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "yuenu-jian")
                return notify_fail("�������޽������ʹ������������\n");
                
    if((int)me->query("max_neili") < 15000 )
                return notify_fail("���������Ϊ����������ʹ������������\n");
    if((int)me->query("neili") < 1000 )
                return notify_fail("�������������㣬����ʹ������������\n");
    
	message_vision(HIY"\n$N���к������ұ�׳֮�⣬�������������ã����н��ǽ������ţ�����ȴ�Ǽ��󣬽�������$n����֮��������ԽŮ����֮������������"NOR"��\n"NOR, me,target);
    
	me->set_temp("ynj/6j",1);

    me->add_temp("apply/strength",  skill/20);
    me->add_temp("apply/attack",  skill/2);
    me->add_temp("apply/damage", skill/3);
    me->add_temp("apply/sword", skill/3);
    
	     COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    me->delete_temp("ynj/6j");
    me->add_temp("apply/strength",  -skill/20);
    me->add_temp("apply/attack",  -skill/2);
    me->add_temp("apply/damage", -skill/3);
    me->add_temp("apply/sword", -skill/3);
    target->start_busy(1);
    me->start_perform(5,"������������");
   
    me->add("neili", -500);
	return 1;
}

int help(object me)
{
   write(WHT"\nԽŮ����"HIY"��������"WHT"����"NOR"\n");
   write(@HELP
	ԽŮ�����ഫ�Ǵ���ս��ʱ��һλԽ����������Ĺ���
	�Ӱ�Գ���������һ�׽�����Խ��������н����Ҫ���
	�����Ϊ��ѵ��ʿ�����������������֡��и�Ů����
	�����У�����ʿ��һ�׽����������Ժ�ȴ����������
	�����������Ǿ���ԽŮ�������ƺ����׽�����
	���������������΢���ף��������Ķ�������Ż���
	�������������űջ�����˥���ˡ�����ս֮������ʵ��
	����ʾ���ǡ���֮�ƺø�����֮�ƾ廢��
	ԽŮ���������������������������ã����н��ǽ�����
	�ţ�ȴ����ָ������֮�����������ҡ�ֻ��Ů�Բ��ܷ�
	�ӳ����������

	perform sword.liujian

Ҫ��
	���������Ҫ 15000 ���ϣ�
	��ǰ������Ҫ 1000 ���ϣ�
	���������ȼ� 450 ���ϣ�
	ԽŮ�����ȼ� 450 ���ϣ�
	��������ΪԽŮ������
	�ֳֽ���������
HELP
   );
   return 1;
}
