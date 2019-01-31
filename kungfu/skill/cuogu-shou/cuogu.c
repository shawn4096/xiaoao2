// cuogu.c ����� 
// Modified by sohu@xojh
// ��Ѩ���˾���

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIG"�ֽ��Ǿ�"NOR; }

int perform(object me, object target)
{
        int lvl,damage;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("���ֽ��Ǿ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("��������ʹ�á����ֽ��Ǿ�������\n");

		if( (int)me->query_skill("cuogu-shou", 1) < 100 )
                return notify_fail("��ķֽ����ֲ�����죬�޷�ʩչ�����ֽ��Ǿ�����\n");
        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򲻹����޷�ʩչ�����ֽ��Ǿ�����\n");
        if ( (int)me->query("max_neili") < 1000)
                return notify_fail("�����������������޷�ʩչ�����ֽ��Ǿ�����\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʩչ�����ֽ��Ǿ�����\n");
		if (me->query_dex() < 35)
                return notify_fail("��ĺ������������޷�ʩչ�����ֽ��Ǿ�����\n");
        if (me->query_skill_prepared("hand") != "cuogu-shou"
		    || me->query_skill_mapped("parry") != "cuogu-shou"
            || me->query_skill_mapped("hand") != "cuogu-shou")
                return notify_fail("�����ڼ������ԣ��޷�ʹ�á��ֽ��Ǿ������й�����\n");
        if (me->query_temp("cgs/cuogu"))
                return notify_fail("������ʹ�á��ֽ��Ǿ���������\n");
        
		lvl = me->query_skill("cuogu-shou",1);
		damage=lvl+me->query_skill("force",1);
		
	
		//message_vision(HBYEL+HIW "$N��������������Ծ��������У�ʹ��ȫ��̡����ֽ��Ǿ������������ȹ���$n��\n"NOR,me, target);
      //  me->set_temp("yylht/yuanyang",1);
		me->start_perform(2, "���ֽ��Ǿ���");

		message_vision(CYN "$N������ϣ��ӳ�һƬ��Ӱ���㡢�á�����ж�������㹥��$n,����"RED"���ֽ��ǡ�"CYN"����ʽ��\n"NOR,me, target);
		if (random(me->query_skill("cuogu-shou",1))>target->query_skill("parry",1)/2)
		{
			message_vision(YEL"$n����һ�٣�Ϊ$N��סҪѨ�����ɵ�����һ�ͣ�\n"NOR,me, target);
			if (userp(target))
				target->add_busy(2);
			else target->add_busy(4);
		}
		if (random(me->query_dex())>target->query_dex()/3)
		{
			message_vision(HBGRN+HIW"$N��������ȣ�Χ��$nת��һȦ��˫�ַֺ�֮��ʹ�����ֽ�ʽ������ʱ��ס$n�Ľ��Ҫ����\n"NOR,me, target);
			target->receive_damage("qi",damage,me);
			if (me->query("gender")=="����")
				target->receive_wound("qi",damage/2,me);
			else target->receive_wound("qi",damage/3,me);
			if(userp(me) && me->query("env/damage"))
        		tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR);
		
			if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);

		}
		me->add_temp("apply/attack",lvl/4);
		me->add_temp("apply/damage",lvl/5);
		me->add_temp("apply/hand",lvl/5);
		
		me->set_temp("cgs/fenjin",1);
		COMBAT_D->do_attack(me, target, 0, me->query("gender")=="����"?3:1);
		me->delete_temp("cgs/fenjin");

		me->add_temp("apply/hand",-lvl/5);
		me->add_temp("apply/attack",-lvl/4);
		me->add_temp("apply/damage",-lvl/5);
		if (objectp(me)
			&&objectp(target)
			&&me->is_fighting())
			call_out("cuogu_attack", 1, me, target);
        return 1;
}

void cuogu_attack(object me, object target)
{
        int i,lvl,damage;
        if (!me||!target) 
return;
		lvl = me->query_skill("cuogu-shou",1);
		
		damage=me->query_skill("cuogu-shou",1)+me->query_skill("force",1);
		damage=damage*2+random(damage);
		message_vision(WHT"$N˫����ס$n�Ľ�ǣ�����һק������"HIY"�����ʽ��"RED"����ʽ��\n"NOR,me, target);
 
		if (target->is_busy())
		{
			message_vision(WHT"$N���ڿ��У��ۼ�$nΪԧ�������������ƴ���������˲���߳�������$n�ؿڣ�\n"NOR,me, target);
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage,me);
			if(userp(me) && me->query("env/damage"))
        		tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage*2+ WHT"�㹥���˺���\n"NOR);
		
			if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage*2+ WHT"���˺���\n"NOR);

		}
		me->set_temp("cgs/cuogu",1);
        me->add_temp("apply/attack",lvl/4);
        me->add_temp("apply/damage",lvl/4);
               for (i = 0; i < 2; i++){
					if (objectp(target)&& me->is_fighting())
						COMBAT_D->do_attack(me, target, 0, userp(me)?1:3);
				}
        me->add_temp("apply/attack",-lvl/4);
        me->add_temp("apply/damage",-lvl/4);
		me->delete_temp("cgs/cuogu");				
      

		me->start_perform(3, "���ֽ��Ǿ���");
		me->add("neili",-150);
		me->add("jingli",-100);
		return;
}
int help(object me)
{
        write(HIG"\n�ֽ�����֮���ֽ��Ǿ�����"NOR"\n");
        write(@HELP
	�ֽ������ǽ����߹�֮��ʥ��������ϵľ��������
	�ַ�����Էֽ��ǽ��Է���Ѩ��������Ҫ������˲
	�佫�Է���ס�������ش���

	ָ�perform hand.cuogu
Ҫ��
	�����ڹ��ĵȼ� 100  ���ϣ�
	�ֽ����ֵȼ� 100  ���ϣ�
	�����ַ��ĵȼ� 100  ���ϣ�
	��������Ҫ�� 1000 ���ϣ�
	��ǰ������Ҫ�� 200  ���ϣ�
	��������Ҫ�� 35   ���ϣ�
	�����ұ��ַ�Ϊ�ֽ����֣�
	�����ұ��ַ�Ϊ�ֽ����֣�
	�ڹ����ޡ�
HELP
        );
        return 1;
}


