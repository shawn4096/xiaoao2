// jue.c ������
//����pxj������ʽ�������˺�������

#include <ansi.h>
string perform_name(){ return HBRED+HIY"������"NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("pixie-jian", 1) < 400 )
                return notify_fail("��ı�а����������죬����ʹ�þ����롣\n");
		if( (int)me->query_skill("sword", 1) < 400 )
                return notify_fail("��Ļ�������������죬����ʹ�þ����롣\n");
		if( (int)me->query_skill("dodge", 1) < 400 )
                return notify_fail("��Ļ����Ṧ������죬����ʹ�þ����롣\n");
        if( (int)me->query_dex() < 65  )
                return notify_fail("�����̫�ͣ�����ʹ�þ����롣\n");
 
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("�������������㣡\n");     
		if( (int)me->query("jingli", 1) < 500 )
                return notify_fail("�����ھ������㣡\n");  

        if (!weapon || !(weapon->id("needle"))
			|| me->query_skill_mapped("dodge") != "pixie-jian"
			|| me->query_skill_mapped("parry") != "pixie-jian"
			|| me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("�������޷�ʹ�þ����롣\n");
        if( me->query("gender")!="����")
                return notify_fail("�����и�֮�ˣ�����ܶ��ñ�а�������⣿\n");

        message_vision(RED"\n$Nһ�����,�͵�������$n��ȥ����ָһ������öϸ����˳�ȥ������$n����Ŀ��\n\n"NOR, me, target);
  
        me->add("neili", -random(1000));
        me->add("jingli", -random(500));
      
      if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 
		  || random(me->query_dex(1)) >(int)target->query_dex(1)/2)
	  {
        message_vision(HIR"\n$n⧲����������һ�����������룡\n"NOR, me, target);
        tell_object(target, HIY "��о�ϸ���������Լ���ͫ��֮�У��������ֱ�����ԣ���������֮�ǣ�\n" NOR);
        
		if (!me->query("quest/pixie/super") || !QUEST_D->queryquest(me,"kuihua/book"))
        {
					me->start_busy(2);
        }
                target->start_busy(2);
                me->add("neili", -300);
                damage = (int)target->query("max_qi");
                damage = damage/2;
				if (me->query("quest/pixie/super") || QUEST_D->queryquest(me,"kuihua/book"))
					damage=damage+random(damage);

                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
				target->apply_condition("no_perform",1);
                if(userp(me) && me->query("env/damage"))
		           tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR); 
	            
if(userp(target)&& target->query("env/damage"))
		           tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);
	  
          me->query_temp("weapon")->move(target);
                if (userp(target))
					target->kill_ob(me);
               }
               else 
               {
                target->start_busy(2);
                me->query_temp("weapon")->move(environment(target));
                target->kill_ob(me);
                message_vision(HIY"\n����$n������$N����ͼ���������˿�ȥ��\n"NOR, me, target);
                me->add("neili", -random(300));
               }

        return 1;
}


int help(object me)
{
   write(WHT"\n��а������"HBRED+HIY"������"WHT"����"NOR"\n");
   write(@HELP
	��������˽�������Ҫ��һ��а����֯������ȫƾ���˺ö�
	���г����似�������������а�����������ν�����������
	�ľ��������������������ְ汾�������ڱ�а���������ɡ�
	���������ơ�
	�������롹�����˹����룬ֱ��Է�ͷ�������к󣬶Է���
	�����ܼ���Ĵ��ˣ�����һ�г��䲻��ĺ��У�
    
	ָ�perform sword.jue

Ҫ��
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 500 ���ϣ�
	��а���� 400 ���ϣ�
	�������� 400 ���ϣ�
	�����Ṧ 400 ���ϣ�
	������ 65  ���ϣ�
	�����Ṧ��а����
	�����мܱ�а������
	����������а������
	���ֳ���״����;

HELP
   );
   return 1;
}
