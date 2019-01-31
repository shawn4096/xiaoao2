// yuanyang.c  ԧ���
// Modified by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIY"ԧ"HIR"��"HIG"��"NOR; }

int perform(object me, object target)
{
        int lvl,damage;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("ԧ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("��������ʹ�á�ԧ��š���\n");

		if( (int)me->query_skill("yuanyang-lianhuantui", 1) < 100 )
                return notify_fail("���ԧ�������˲�����죬�޷�ʩչ��ԧ��š�\n");
        if ((int)me->query_skill("xiantian-gong", 1) < 100)
                return notify_fail("������칦��򲻹����޷�ʩչ��ԧ��š�\n");
        if ( (int)me->query("max_neili") < 1000)
                return notify_fail("�����������������޷�ʩչ��ԧ��š�\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʩչ��ԧ��š�\n");
		if (me->query_dex() < 35)
                return notify_fail("��ĺ������������޷�ʩչ��ԧ��š�\n");
        if (me->query_skill_prepared("leg") != "yuanyang-lianhuantui"
            || me->query_skill_mapped("leg") != "yuanyang-lianhuantui")
                return notify_fail("�������޷�ʹ��ԧ��Ž��й�����\n");
        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("ԧ�����Ҫ���칦����������\n");
        if (me->query_temp("yylht/yuanyang"))
                return notify_fail("������ʹ��ԧ��ž�����\n");
        
		lvl = me->query_skill("yuanyang-lianhuantui",1);
		damage=lvl+me->query_skill("xiantian-gong",1);
		
		if (me->query("gender")=="����")
		{
			damage=damage*me->query_dex()/4+random(damage);
			if (damage>5000) damage=damage+random(500);
		}else {

			damage=damage*me->query_dex()/8+random(damage);
			if (damage>4000) damage=damage+random(500);
		}
		
		
		//message_vision(HBYEL+HIW "$N��������������Ծ��������У�ʹ��ȫ��̡�ԧ��š��������ȹ���$n��\n"NOR,me, target);
      //  me->set_temp("yylht/yuanyang",1);
		me->start_perform(2, "ԧ���");

		message_vision(CYN "$N���һ�������У��������ƣ�������Σ�����һ����Ӱ������$n,����"RED"��ԧ�š�"CYN"����ʽ��\n"NOR,me, target);
		if (random(me->query_skill("yuanyang-lianhuantui",1))>target->query_skill("parry",1)/2)
		{
			message_vision(YEL"$n����һ�٣�Ϊ$N�ŷ����󣬶�ʱ�������������ɵ�����һ�ͣ�\n"NOR,me, target);
			if (userp(target))
				target->add_busy(2);
			else target->add_busy(4);

		}
		if (random(me->query_dex())>target->query_dex()/3)
		{
			message_vision(HBRED"$N��һ�������û����������$n�����ߣ�\n"NOR,me, target);
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
		me->add_temp("apply/leg",lvl/5);
		
		me->set_temp("yylht/yuan",1);
		COMBAT_D->do_attack(me, target, 0, me->query("gender")=="����"?3:1);
		me->delete_temp("yylht/yuan");

		me->add_temp("apply/leg",-lvl/5);
		me->add_temp("apply/attack",-lvl/4);
		me->add_temp("apply/damage",-lvl/5);
		if (objectp(me)
			&&objectp(target)
			&&me->is_fighting())
			call_out("yang_attack", 1, me, target);
        return 1;
}

void yang_attack(object me, object target)
{
        int i,lvl,damage;
        if (!me||!target) 
return;
		lvl = me->query_skill("yuanyang-lianhuantui",1);
		
		damage=me->query_skill("yuanyang-lianhuantui",1)+me->query_skill("xiantian-gong",1);
		damage=damage*2+random(damage);
		message_vision(RED "$N����˳����չ����������֮�ƣ�һʽ"HIY"����š�"RED"����ʽʹ����\n"NOR,me, target);
 
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
		me->set_temp("yylht/yang",1);
        me->add_temp("apply/attack",lvl/4);
        me->add_temp("apply/damage",lvl/4);
               for (i = 0; i < 2; i++){
					if (objectp(target)&& me->is_fighting())
						COMBAT_D->do_attack(me, target, 0, userp(me)?1:3);
				}
        me->add_temp("apply/attack",-lvl/4);
        me->add_temp("apply/damage",-lvl/4);
		me->delete_temp("yylht/yang");				
      

		me->start_perform(3, "ԧ���");
		me->add("neili",-150);
		me->add("jingli",-100);
		return;
}
int help(object me)
{
        write(HIG"\nԧ��������֮��ԧ��š���"NOR"\n");
        write(@HELP
	ԧ����������ȫ��̵��������书֮һ���ýŷ�
	ȫƾһ�������Ƴ������������һ������������
	�Է�����Է�����ʤ����
	ԧ����Ƿֱ��߳�3�У���һ��Ϊԧ�����ƣ���Ҫ
	�����У��Ի�Է������Է����У�������������
	���޴������ڶԷ��˺�������Ҫ������������
	�ơ�

	ָ�perform leg.yuanyang

Ҫ��
	���칦���ĵȼ� 100  ���ϣ�
	ԧ�������ȵȼ� 100  ���ϣ�
	�����ȷ��ĵȼ� 100  ���ϣ�
	��������Ҫ�� 1000 ���ϣ�
	��ǰ������Ҫ�� 200  ���ϣ�
	��������Ҫ�� 35   ���ϣ�
	�����ұ��ȷ�Ϊ����ԧ���ȣ�
	�������칦��
	�����ұ�ԧ��������
HELP
        );
        return 1;
}


