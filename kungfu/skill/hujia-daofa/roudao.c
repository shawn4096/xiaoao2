// roudao.c ���ҵ���֮���ᵶ����
// Create By lsxk@hsbbs 2007/5/12

#include <ansi.h>

inherit F_SSERVER;
string perform_name() {return HIG"�ᵶ��"NOR;}
int perform(object me, object target)
{
        string msg;
		int skill=me->query_skill("hujia-daofa",1);
        object weapon = me->query_temp("weapon");
        int busy;

        if( !target ) target = offensive_target(me);

         if( !objectp(target)
          ||!target->is_character()
          ||!me->is_fighting(target) )
                return notify_fail("���ᵶ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 450 )
                return notify_fail("��ĺ��ҵ���������죬����ʹ�á��ᵶ������\n");

        if ((int)me->query_skill("blade", 1) < 450 )
                return notify_fail("��Ļ�������������죬����ʹ�á��ᵶ������\n");

        if ((int)me->query_skill("force", 1) < 450 )
                return notify_fail("��Ļ����ڹ�������죬����ʹ�á��ᵶ������\n");

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "hujia-daofa")
//         || me->query_skill_mapped("parry") != "hujia-daofa")
                return notify_fail("�����ʹ�ú��ҵ�������ʹ�á��ᵶ������\n");

        if( (int)me->query("neili") < 2000 )
                return notify_fail("����������̫��������ʹ�á��ᵶ������\n");
        if( (int)me->query("jingli") < 1000 )
                return notify_fail("����������̫��������ʹ�á��ᵶ������\n");

        if( target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		if( target->query_temp("hjdf/rdj"))
                return notify_fail(target->name() + "�Ѿ�Ϊ���ᵶ�����У��ŵ������ɣ�\n");
     //    if( me->query_temp("hjdf/rdj"))
               // return notify_fail( "������ʩչ�ᵶ����\n");
		msg = HIG "$N��ʽһ�侹ʹ�����ҵ���֮���ᵶ����!����һ����$N����������û�����������ȴ���ᾢ�����о�����$n�����ߣ���\n"NOR;
		msg +=HIC"\n$N��ʽ���ƻ���������Χ��ˮй��ͨ��ʵ�����ǲ��ú����˵ĸ�����ʽ���Ż�������\n"NOR;
        me->add("neili", -200);
        me->add("jingli", -140);
        busy = (int)me->query_skill("hujia-daofa", 1)/150;
        if(random(me->query("combat_exp")) >  target->query("combat_exp")/2
           ||random(me->query_skill("force",1))>target->query("force",1)/2 )
		{
               msg += HIY"\n���$pһ�����⣬�����ͻ�������$P�����޷����У����°����Ծ�����\n" NOR;
               target->add_busy(busy);
               //me->set_temp("hjdf/rdj",skill);
			   target->add_temp("apply/parry",-skill/3);
			   target->add_temp("apply/dodge",-skill/4);
			   target->set_temp("hjdf/rdj",skill);
               call_out("check_fight", (int)skill/30, target,); 
        } else {
                msg += "\n$p���һ�������������Ṧ������$P�ĵ��з�Χ����Ҳ������������\n" NOR;
                me->start_busy(2);
                target->add("neili",-600);
               // target->apply_condition("no_exert",1);
        }
		//me->start_perform(6,"���ᵶ����");

        message_vision(msg, me, target);
        return 1;
}

void check_fight(object target)
{
      
		int skill;
		if (!target||!target->query_temp("hjdf/rdj")) return;
		skill=target->query_temp("hjdf/rdj");

		target->add_temp("apply/parry",-skill/3);
		target->add_temp("apply/dodge",-skill/4);
		target->delete_temp("hjdf/rdj");
		message_vision(HIG"$N���С��ᵶ�����ĸ��������õ����⡣\n"NOR, target);
        return;

}
int help(object me)
{
   write(WHT"\n���ҵ�����"HIG"�ᵶ��"WHT"����"NOR"\n");
   write(@HELP
	�ˡ��ᵶ�����������ھ�����Ϻ��ҵ����������ʽ��
	����һ�����ֲ�����������ʮ��������������ڹ���
	Ϊ��Խ�ȵ�����񣬳ɹ��ʾ�Խ�ߣ��ᵶ�����Ǻܺ�
	�ķ�����ʽ��������죬�ݵ��ڵ�������֮�С�����
	���Ǽ�Ϊ�����ķ��ط�����ʽ�����к�ս�������Լ�
	�ڹ���Ϊ�йء�Ŀ�����к󣬷���������½���
	
	ָ�perform blade.roudao

Ҫ��
	���ҵ��� 450 ����
	�������� 450 ����
	�����ڹ� 450 ����
	������� 5000 ���ϣ�
	��ǰ���� 2000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	��������Ϊ���ҵ�����
	�ֳֵ���������
HELP
   );
   return 1;
}
