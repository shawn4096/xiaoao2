// jingtao ���κ���

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return HIY"���κ���"NOR; }
void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev;
        lev = me->query_skill("huagu-mianzhang", 1) +me->query_skill("dulong-dafa", 1)/6;
       // lev2 = me->query_skill("strike", 1)/6;
		if (!userp(target))
		{
			lev=lev+me->query_skill("dulong-dafa", 1)/8;
		}
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("�����κ��ˡ�ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á����κ��ˡ���\n");   
        if( (int)me->query_skill("huagu-mianzhang", 1) < 220 )
                return notify_fail("��Ļ������ƻ�������죬ʹ���������κ��ˡ�������\n");
        if (me->query_skill_prepared("strike") != "huagu-mianzhang"
		 || me->query_skill_mapped("parry") != "huagu-mianzhang"
		 || me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("�������޷�ʹ�á����κ��ˡ����й�����\n");  

        if( (int)me->query_skill("dulong-dafa", 1) < 220 )
                return notify_fail("��Ķ����󷨵ȼ���������ʹ���������κ��ˡ�������\n");
		if( (int)me->query_skill("strike", 1) < 220 )
                return notify_fail("��Ļ����Ʒ��ȼ���������ʹ���������κ��ˡ�������\n");
        if(me->query("gender")=="Ů��") 
        	return notify_fail("�㲻�����ˣ��в���ʹ�û��Ǿ���\n");
		if( me->query("jingli") < 1000 )
                return notify_fail("�����ھ���̫����ʹ���������κ��ˡ���\n");      
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫����ʹ���������κ��ˡ���\n");
        message_vision(HIB"\n$N����Ĭ��������ֽ̻壬���бŷ���һ��Ī��������,�����������羪�κ���һ��ȫ��������\n"NOR,me);
        me->add_temp("apply/attack", lev/4);
		me->add_temp("apply/strike", lev/4);
        me->add_temp("apply/damage",lev/6);
		if (!userp(target))
		{
			me->add_temp("apply/attack",lev/5);
			me->add_temp("apply/damage",lev/6);
			target->add_busy(2);
			me->set_temp("hgmz/jthit",1);
		}
		//me->set_temp("action_flag", member_array("strike", keys(me->query_skill_prepare())));
        me->set_temp("hgmz/jingtao",1);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
        if(me->is_fighting(target)) 
		{
                if( random(me->query("combat_exp"))>target->query("combat_exp")/2)
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                else
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        }
		if(me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
		me->add_temp("apply/attack", -lev/4);
        me->add_temp("apply/strike", -lev/4);
		me->add_temp("apply/damage",-lev/6);
		if (me->query_temp("hgmz/jthit"))
		{
			me->add_temp("apply/attack",-lev/5);
			me->add_temp("apply/damage",-lev/6);
			me->delete_temp("hgmz/jthit");
		}

		me->delete_temp("hgmz/jingtao");

		me->add_busy(1);
        me->add("neili", -300);
		me->add("jingli", -200);
		me->start_perform(4,"�����κ��ˡ�");
        return 1;
}
int help(object me)
{
   write(HIY"\n�������ơ�"HIY"���κ���"HIY"����"NOR"\n");
   write(@HELP
	�����������ߵ������似����һ�ּ�Ϊ��������������
	���������ƻ��е��˿�ʼ���粻����������ʱ��������
	������ȫ��������������࣬������ϣ��อ���ѣ���
	�����ԣ����޾��Ρ�
	�����κ��ˡ������ǻ�����������ֱ�Ӻ���Ѹ�ٵľ�����

	ָ�perform strike.jingtao

Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�������Ƶȼ� 220 ���ϣ�
	�����󷨵ȼ� 220 ���ϣ�
	�����Ʒ��ȼ� 220 ���ϣ�
	�����Ʒ�Ϊ�������ƣ�
	�����м�Ϊ�������ƣ�
	�䱸�Ʒ�Ϊ�������ƣ�
	�����ڹ�Ϊ�����󷨣�
	����ʹ�ã�
          
HELP
   );
   return 1;
}
