// hansha.c ��ɳ��
//������׶�������뵽��ɳ��Ӱ��
//���Ź���ԭ�����嶾��,��Ҫ�ý���׶��������
//�⿪����1

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,damage;
	string msg;
	object weapon;
	skill=me->query_skill("hansha-sheying", 1);
	damage=skill+me->query_skill("jinshe-zhuifa",1);
	damage=damage*me->query_dex()/10;

	

	if (! target) target = offensive_target(me);
	if (! target ||	! me->is_fighting(target))
		return notify_fail("��ɳ��ֻ����ս����ʹ�á�\n");

    if (!objectp(weapon = me->query_temp("weapon"))
        // ||(string)weapon->query("id") != "jinshe zhui"
		 ||(string)weapon->query("skill_type") != "throwing"
         ||  weapon->query_amount() < 1)
           	return notify_fail("������û�ð����������㣬����ʹ�ú�ɳ�����У�\n");
	if (!me->query("quest/jinshe2/pass"))
		return notify_fail("����δ�⿪����2������ʹ�ú�ɳ�����У�\n");
	if (me->query_skill("jinshe-zhuifa", 1) < 350)
		return notify_fail("��Ľ���׶��������죬����ʹ�ú�ɳ����\n");
	if (me->query_skill("throwing", 1) < 350)
		return notify_fail("��Ļ�������������죬����ʹ�ú�ɳ����\n");
	if (me->query("family/family_name")=="������"&&me->query_skill("hansha-sheying", 1) < 350)
		return notify_fail("��ĺ�ɳ��Ӱ������죬����ʹ�ú�ɳ����\n");
	if (me->query_skill_mapped("throwing")!="jinshe-zhuifa"
		&& me->query_skill_mapped("parry")!="hansha-sheying")
		return notify_fail("����Ҫ��������׶����ɳ��Ӱ������ʹ�ú�ɳ����\n");
	if ((int)me->query("neili") < 1000)
		return notify_fail("�����������ˡ�\n");
	if ((int)me->query("jingli") < 500)
		return notify_fail("�㾫�������ˡ�\n");
	if (target->query_temp("block_msg/all"))
		return notify_fail("�Է��Ѿ�������ĺ�ɳ��Ӱ��\n");
	if (me->query("gender")!="Ů��")
	{
		damage=damage/3;
	}
		weapon->add_amount(-1);

        msg = HIY "$N" HIY "һ����Х������΢��������"+weapon->query("name")+HIY"��Ȼ���Ϸ�"
              "�����˸�Ȧ�����Ѹ��Ϯ��$n" HIY "����ǰ��\n" NOR;

        if (me->query_skill("hansha-shenying",1)/ 2 + random(skill) > target->query_skill("dodge", 1) 
			||random(me->query_skill("throwing",1))>target->query_skill("parry",1)/2
			||random(me->query_str(1))>target->query_dex(1)/2
			|| !living(target))
        {
        	target->receive_damage("qi", damage, me);
        	target->receive_wound("qi", damage/3, me);
        
        	msg += HIM "$N" HIM "���е�"+weapon->query("name")+HIM"������Ŀ�Ĺ�â����ҫ��$n" HIM "��ð�𻨣�$n" HIM"˲��ѣ��ʧ��\n" NOR;
        	msg += HIR""+weapon->query("name")+HIR"Ԥ�Ʋ�����˳��͸$n���ض�����\n" NOR;
            
			message_vision(msg, me, target);
        	me->set_temp("jinshe/hansha", 1);
        	target->set_temp("block_msg/all", 1);
			if (!target->query_temp("hssy/hansha"))
			{
				target->set_temp("hssy/hansha",skill);
				target->add_temp("apply/dodge",-skill/2);
				target->add_temp("apply/parry",-skill/2);
				target->add_temp("apply/defense",-skill/2);
				message_vision(HIG"$N��ǰ��ʱΪ�����������֣���������ɳ�У�����������\n"NOR,target);
			}
        	call_out("remove_hansha",1+random(2),target);
        } else
        {
            msg += CYN "$n" CYN "���а���һ������æ��"
                       "�ˣ���������ö����׶��\n" NOR;
			me->add_busy(1);       
        }
        me->add("neili", -500);
        me->add("jingli", -300); 
		message_vision(msg, me, target);
		//me->start_perform(1,"��ɳ��");
        me->reset_action();
		return 1;
}

void remove_hansha(object target)
{
	int skill;
	if (!target) return;
	skill=target->query_temp("hssy/hansha",skill);
 
	      //  message_combatd("$NĨ��Ĩ������" HIR "��Ѫ" NOR "�������������ۡ�\n",
			     //   target);
	        target->set_temp("block_msg/all", 0);
			if (target->query_temp("hssy/hansha"))
			{
				
				target->add_temp("apply/dodge",skill/2);
				target->add_temp("apply/parry",skill/2);
				target->add_temp("apply/defense",skill/2);
				target->set_temp("hssy/hansha",skill);
				message_vision(HIG"$N������������һ�ԣ�����һ�����������˺�ɳ��Ӱ��Ӱ�죡\n"NOR,target);
			}
	        tell_object(target,target->query("name")+HIR "����Ĩ������������Ѫ����������Χ���龰��\n"NOR);
	 
	return;
}

string perform_name(){ return HBYEL"��ɳ��"NOR; }
int help(object me)
{
         write(HIB"\n����׶��֮����ɳ������"NOR"\n");
        write(@HELP
	����׶���ǽ����ɾ������似�����ø߳���������
	���һö����׶������ŹֵĽǶ���������Զ�ʱ
	��ɶԷ�����Ŀ��������Ч��ͬʱ���ɱ�ˡ�Ů��
	������
	
	ָ�perform throwing.hansha

Ҫ��
	����׶���ȼ���350 ����
	���������ȼ���350 ����
	��ɳ��Ӱ�ȼ���350 (����������)
	��ǰ��������1000 ����
	��ǰ��������500 ����
	��Ҫ��������׶����ɳ��Ӱ
	�ְֳ�����
	�ڹ����ޡ�

HELP
        );
        return 1;
}
