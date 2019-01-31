
#include <ansi.h>

inherit F_SSERVER;
//inherit COMBINED_ITEM;
//inherit SKILL;
void back(object target);

int perform(object me, object target)
{
       int damage;
		object weapon = me->query_temp("weapon");
		damage=me->query_skill("jisnhe-zhuifa",1)+me->query_skill("throwing",1)+me->query_skill("jisnhe-zhangfa",1);
		damage=damage*me->query_str()/10+random(damage);

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("jinshe-zhuifa", 1) < 120 )
                return notify_fail("��Ľ���׶��������죬����ʹ����Ӱ�����\n");

		if( (int)me->query("neili", 1) < 500 )
				return notify_fail("�������������㣡\n");  
        if( (int)me->query_str() < 40  )
                return notify_fail("��ı���̫�ͣ��޷�ͬʱ������ô�����׶��\n");
       
        if (!weapon 
		|| weapon->query("skill_type")!="throwing"
		|| weapon->query("id")!="jinshe zhui"
        || me->query_skill_mapped("throwing") != "jinshe-zhuifa")
                return notify_fail("�������޷�ʹ����Ӱ�����\n");
        
		if (weapon->query_amount()<1)
             return notify_fail("�����ϵİ����������޷�ʹ����Ӱ�����\n");  
        weapon->add_amount(-1);
        
		me->add("neili", -450);
        me->add("jingli", -150);
		
        message_vision(RED"$N��߳һ��ͻȻ���֣�����������������������еĽ�����ײ���еĽ����������������裬���������\n"NOR, me, target);
        message_vision(RED"$n��ǰɲ�Ǽ亮â������������âҫ�����ɽ�⣬����������磬æ�����п��裬�뻤סȫ��\n"NOR, me, target);;

	  if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 
		  &&random(me->query_str(1)) > (int)target->query_dex()/3)
	 {
					destruct(weapon);
					message_vision(HIR"\nֻ��$n�ҽ�һ��������"+HIY+"����׶"+HIR+"�Ѿ�����ȫ��ҪѨ�������Ѿ������ɸ���ˣ�\n"NOR, me, target);
					tell_object(target, HIY "������ȫ�����¶����������ˣ�\n" NOR);
					target->receive_damage("qi", damage,me);
					target->receive_wound("qi", damage/4,me);
					target->kill_ob(me);
	 }
	  else {
			 message_vision(HIY"$n��ͷ����һ������������㿪��$N������������\n"NOR, me, target);
			 //weapon->move(environment(me));
			 me->start_busy(random(3));
			 target->kill_ob(me);
	}
		  
    return 1;
}


string perform_name(){ return HIG"�����Ӱ"NOR; }
int help(object me)
{
         write(HIB"\n����׶��֮�������Ӱ����"NOR"\n");
        write(@HELP
	����׶���ǽ����ɾ������似�������Ӱ�������ߵ�
	Ѹ�����ߣ����ٳ��У����䰵����
	�����Ӱ�����ý���׶���ص���״�γɵ������ӰӰ
	��Է��жϣ���ʧ֮�����Է��ش���
	
	ָ�perform throwing.sheying

Ҫ��
	����׶���ȼ���250 ����
	���������ȼ���250 ����
	��ǰ��������1000 ����
	��ǰ��������500 ����
	��Ҫ��������׶��
	�ڹ����ޡ�
	�ֳֽ���׶������

HELP
        );
        return 1;
}

