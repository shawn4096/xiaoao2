//By KinGSo@���� 2006��5��
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
string perform_name(){ return HIG"����"NOR; }
int perform(object me, object target)
{
        int damage, p;
        int ns;
        string msg;
        
        if( !target ) target = offensive_target(me);

        
        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("�����ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������\n");   
        if( (int)me->query_skill("huagu-mianzhang",1) < 300 )
                return notify_fail("��Ļ��������Ʒ���Ϊ���㣬ʹ�������ơ�\n");
		if( (int)me->query_skill("strike",1) < 300 )
                return notify_fail("��Ļ����Ʒ���Ϊ���㣬ʹ�������ơ�\n");
        if( (int)me->query("neili") < 1500 )
                return notify_fail("����������̫�������ܴ�����ơ�\n");
        if( (int)me->query("max_neili") < 3000 )
                return notify_fail("����������̫�������ܴ�����ơ�\n");
		if( (int)me->query_skill("poison", 1) < 145 )
                return notify_fail("��Ķ��ƹ������㣬���ܻ��ǡ�\n");
		if( (int)me->query_skill("shenlong-yaoli", 1) < 145 )
                return notify_fail("�������ҩ�������㣬���ܻ��ǡ�\n");
        if( (int)me->query("jiali") < 100 )
                return notify_fail("�����ڼ������㣬��ôʹ�����ư�����\n");
        if( me->query_skill_mapped("force")!="dulong-dafa" )
                return notify_fail("�㼤�����ڹ���������ôʹ�����ư�����\n");
		if (me->query_skill_prepared("strike") != "huagu-mianzhang"
			|| me->query_skill_mapped("parry") != "huagu-mianzhang"
            || me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("�������޷�ʹ�����ƣ�\n");                
       if(me->query("gender")=="Ů��") 
        	return notify_fail("�㲻�����ˣ��в���ʹ�û��Ǿ���\n");
        msg = HBGRN+HIW "$N��������Ц��,һ����ƮƮ����$n���˹�ȥ��\n"NOR;
        if (random(me->query_skill("strike",1)) > target->query_skill("parry",1)/2
        || me->query("combat_exp") > random(target->query("combat_exp")/3))
           {
                msg +=HIR "���ֻ���˵�һ����$n��һ�����У�\n"NOR;

				target->add_busy(1);
                ns = (int)me->query_skill("huagu-mianzhang",1) /20;
                damage = (int)me->query_skill("huagu-mianzhang",1)+(int)me->query_skill("dulong-dafa",1)+(int)me->query_skill("poison",1)+(int)me->query_skill("shenlong-yaoli",1);
                damage += random(me->query("jiali") * me->query_str());
                damage *= 3;
                if(target->query("neili") < me->query("neili")) damage *= 2;
                if (damage>7000) damage=7000+random(1000);  
                
				target->add_condition("neishang", ns + random(ns));
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
				if (!random(2))
					target->add_condition("huagu_poison",1);

                me->add("neili", -damage/2);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += HIG"����$n���ؿڣ���������,$n���������������,�������ǲ��⡣\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
          
        }
		else {
                me->start_busy(2);
                msg += HIG"$n������ƽ�����䣬����һ�ã�$N��һ�Ʊ㼴��ա�\n"NOR;
        }

        message_vision(msg, me, target);
		me->add("jingli",-random(200));
		me->add("neili",-random(300));
		me->add_busy(2);
		me->start_perform(4,"����");
        return 1;
}

int help(object me)
{
   write(HIG"\n�������ơ�"HIG"����"NOR"����"NOR"\n");
   write(@HELP
	�����������ߵ������似����һ�ּ�Ϊ��������������
	���������ƻ��е��˿�ʼ���粻����������ʱ��������
	������ȫ��������������࣬������ϣ��อ���ѣ���
	�����ԣ����޾��Ρ�
	���������С����ơ�������Ҫ������֮�ھ��˵У�����
	������Ч�������и��ʱ����Ƕ����ˡ�	
   
	ָ�perform strike.mianzhan

Ҫ��
	�������Ҫ�� 3000 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	�������Ƶȼ� 300 ���ϣ�
	�˵м���Ҫ�� 100 ���ϡ�
	����ҩ��Ҫ�� 145 ���ϣ�
	���Ƶȼ�Ҫ�� 145 ���ϣ�
	�����Ʒ�Ϊ�������ƣ�
	�ұ��Ʒ�Ϊ�������ƣ�	
	�����м�Ϊ�������ƣ�
	�����ڹ�Ϊ�����󷨣�
	�������ʹ�ã�

HELP
   );
   return 1;
}

