// tuwu.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,damage;
	string msg;
	object weapon;
	skill = me->query_skill("jinshe-zhui", 1);
//	if (me->query_temp("jinshe/tuwu"))
		//return notify_fail("����õ���������û�����žͳ��С�\n");

	if (! target) target = offensive_target(me);
	if (! target ||	! me->is_fighting(target))
		return notify_fail("��������ֻ����ս����ʹ�á�\n");

    if (!objectp(weapon = me->query_temp("weapon"))
		||(string)weapon->query("skill_type") != "throwing" 
		||weapon->query_amount() < 1)
           	return notify_fail("������û�ð���������ʹ�þ��У�\n");

	if (me->query_skill("jinshe-zhuifa", 1) < 100)
		return notify_fail("��Ľ���׶��������죬����ʹ����������\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("�����������ˡ�\n");
	if (target->query_temp("block_msg/all")||target->query_temp("jszf/tuwu"))
		return notify_fail("�Է�����������������ˡ�\n");
        
		weapon->add_amount(-5);
		damage=me->query_skill("jisnhe-zhuifa",1)+me->query_skill("throwing",1)+me->query_skill("jisnhe-zhangfa",1);
		damage=damage*me->query_str()/15+random(damage);
		if (weapon->query_amount()<5)
		{
			return notify_fail("�����еİ��������ˣ��޷�ʹ����������\n");
		}
        msg = HIY "$N" HIY "һ����Х������΢��������"+weapon->query("name")+HIY"����һƬ��������Ȼ���Ϸ�"
              "�����˸�Ȧ�����Ѹ��Ϯ��$n" HIY "����ǰ��\n" NOR;
		message_vision(msg, me, target);
        if (skill / 2 + random(skill) > target->query_skill("dodge", 1)
		|| random(me->query_dex(1))>target->query_dex(1)/2	
		|| !living(target))
        {
        	me->add("neili", -200);
			if (wizardp(me)) 
			{
				write("damage="+damage);
			}
        	target->receive_damage("qi", damage, me);
        	target->receive_wound("qi", damage / 3, me);
        
        	msg = HIM "ֻ��һ����ɨҶ��������У�$N" HIM "���е�"+weapon->query("name")+
                       HIM"������Ŀ�Ĺ�â����ҫ��$n" HIM "��ð�𻨣�"
        	       "\n������ǰһ���ص������⣬$n" HIM
        	       "ɶҲ�������ˣ�\n" NOR;
            message_vision(msg, me, target);
        	//me->set_temp("jinshe/tuwu", 1);
        //	target->set_temp("block_msg/all", 1);
			//if (!target->query_temp("jszf/tuwu"))
			//{
				target->set_temp("jszf/tuwu",skill);
				target->add_temp("apply/dodge",-skill/2);
				target->add_temp("apply/parry",-skill/2);
			//}
			target->add_busy(2);
        	me->start_call_out((: call_other, __FILE__, "tuwu_end",target :),(int)skill/50);
        } else
        {
                msg = CYN "$n" CYN "���а���һ������æ��"
                       "�ˣ���������ö"+weapon->query("name")+"��\n" NOR;
                message_vision(msg, me, target);
        }
		
       // me->reset_action();
	return 1;
}

void tuwu_end(object target)
{
	int skill;
	if (!target) return;

	skill=target->query_temp("jszf/tuwu");

        if (living(target))
        {
	        message_vision("$NĨ��Ĩ������" HIR "��Ѫ" NOR "�������������ۡ�\n", target);
	     //   target->delete_temp("block_msg/all");
			target->add_temp("apply/dodge",skill/2);
			target->add_temp("apply/parry",skill/2);

	       // write(HIR "������Ĩ������������Ѫ����������Χ���龰��\n"NOR);
	        //if (me) me->delete_temp("jinshe/tuwu");
        }

	return;
}

string perform_name(){ return WHT"����"MAG"����"NOR; }
int help(object me)
{
         write(HIB"\n����׶��֮������������"NOR"\n");
        write(@HELP
	����׶���ǽ����ɾ������似�����������������ߵ�
	���¼���ʩչ��һƬ����������ʹ�öԷ�����һ����
	��֮�в����԰Σ����кͼ��ܵȼ��Լ����йء�
	
	ָ�perform throwing.tuwu

Ҫ��
	����׶���ȼ���100 ����
	���������ȼ���100 ����
	��ǰ��������1000 ����
	��ǰ��������500 ����
	��Ҫ��������׶��
	�ڹ����ޡ�
	�ְֳ�����

HELP
        );
        return 1;
}
