// posuo.c ��Ӱ���
//������׶�������뵽��ɳ��Ӱ��
//���Ź���ԭ�����嶾��,��Ҫ�ý���׶��������
//�⿪����1

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,damage;
	string msg;
	object weapon;
	if (me->query("family/family_name")=="������")
	{
		skill=me->query_skill("hansha-sheying", 1);
	}
	else skill=me->query_skill("jinshe-zhuifa", 1);
	
	damage=skill+me->query_skill("throwing",1);
	damage=damage*me->query_dex()/5;



	if (! target) target = offensive_target(me);
	if (! target ||	! me->is_fighting(target))
		return notify_fail("����Ӱ��涡�ֻ����ս����ʹ�á�\n");

    if (!objectp(weapon = me->query_temp("weapon")) 
       ||(string)weapon->query("skill_type") != "throwing") 
           	return notify_fail("���ֳֵĲ��ǰ���������ʹ�á���Ӱ��涡���\n");
    if (weapon->query_amount() < 1)
           	return notify_fail("���ֳֵİ����������޷�ʹ�á���Ӱ��涡����У�\n");
	
	if (!me->query("quest/jinshe2/pass"))
		return notify_fail("����δ�⿪����2������ʹ�á���Ӱ��涡����У�\n");
	//if (!me->query("quest/sld/hssy/posuo/pass"))
		//return notify_fail("����δ�⿪��Ӱ��涣�����ʹ�á���Ӱ��涡����У�\n");
	
	if (me->query_skill("jinshe-zhuifa", 1) < 450)
		return notify_fail("��Ľ���׶��������죬����ʹ�á���Ӱ��涡���\n");
	if (me->query_skill("throwing", 1) < 450)
		return notify_fail("��Ļ�������������죬����ʹ�á���Ӱ��涡���\n");
	if (me->query_skill("jinshe-zhangfa", 1) < 450)
		return notify_fail("��Ľ����Ʒ�������죬����ʹ�á���Ӱ��涡���\n");
	if (me->query_skill("jinshe-zhuifa", 1) < 450)
		return notify_fail("��Ľ���׶��������죬����ʹ�á���Ӱ��涡���\n");
	if (me->query("family/family_name")=="������"&&me->query_skill("chansi-shou", 1) < 450)
		return notify_fail("��Ľ��߲�˿�ֲ�����죬����ʹ�á���Ӱ��涡���\n");
	if (me->query("family/family_name")=="������"&&me->query_skill("shenlong-tuifa", 1) < 450)
		return notify_fail("��������ȷ�������죬����ʹ�á���Ӱ��涡���\n");
	if (me->query("family/family_name")=="������"&&me->query_skill("hansha-sheying", 1) < 450)
		return notify_fail("��ĺ�ɳ��Ӱ������죬����ʹ�á���Ӱ��涡���\n");
	if (me->query_skill_mapped("throwing")!="jinshe-zhuifa"
		&&me->query_skill_mapped("throwing")!="hansha-sheying")
		return notify_fail("����Ҫ��������׶����ɳ��Ӱ������ʹ�á���Ӱ��涡���\n");
	if ((int)me->query("neili") < 1000)
		return notify_fail("�����������ˡ�\n");
	if ((int)me->query("jingli") < 500)
		return notify_fail("�㾫�������ˡ�\n");
	
	if (me->query("gener")!="Ů��")
	{
		skill=skill/3;
	}
	if (me->query_per(1)>25&&me->query_skill("poison",1)>150)
	{
		skill=skill+me->query_skill("poison",1);
	}
	weapon->add_amount(-1);

      message_vision(HIC "$N" HIC "��߳һ��ͻȻ���֣���ʮ����������������$n���еĽ�����ײ���еĽ����������������裬���������\n" NOR,me,target);
	  me->add_temp("apply/attack",skill/3);
	  me->add_temp("apply/damage",skill/4);
	  me->add_temp("apply/throwing",skill/4);

	  if (present("jinshe zhui",me))
	    if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/2
		  || random(me->query_dex()) > (int)target->query_dex()/2) 
	  {
               
         message_vision(HIR"\nֻ��$n�ҽ�һ��������"+HIY+"����׶"+HIR+"�Ѿ�����ȫ��ҪѨ�������Ѿ������ɸ���ˣ�\n"NOR, me, target);
         tell_object(target, HIY "������ȫ�����¶����������ˣ�\n" NOR);
         target->receive_damage("qi", damage,me);
         target->receive_wound("qi", damage/3,me);
         target->kill_ob(me);      
		 COMBAT_D->report_status(target, random(2));
       }
	   //�����̺�ɳ��Ӱ��һ��
	  if (me->query("family/family_name")=="������")
	   {	   
		   //�ڶ���
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			//�����У������Ʒ�
			weapon->unequip();
			if (me->query_skill("strike")=="jinshe-zhangfa"
				&&me->query_skill("jinshe-zhangfa",1)>450)
			{
				message_vision(HIY"\n����һ�̣�������涣�ͻȻʩչ�������Ʒ��Ĺ����ֱ���ת���Բ���˼��Ƕ�ͻȻ����$n��\n"NOR, me, target);
				target->apply_condition("no_exert",1);
				me->add_temp("apply/strike",skill/3);
				//me->prepare_skill("none");
				me->prepare_skill("strike");
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->add_temp("apply/strike",-skill/3);
			}
			weapon->wield();
			//������ ����
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			//������ ��˿��
			weapon->unequip();
			if (me->query_skill("hand")=="chansi-shou"
				&& me->query_skill_mapped("hand")=="chansi-shou"
				&& me->query_skill("chansi-shou",1)>450)
			{
				message_vision(HIM"\n$N�������磬��͹���£�˫�ֺ���Ϊ���߲�˿�ֵ���ʽ���㡢�����������ɻ�������$n�ϰ����Ѩ��\n"NOR, me, target);
				target->add_busy(2);
				me->prepare_skill("hand");
				me->add_temp("apply/hand",skill/3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->add_temp("apply/hand",-skill/3);
			}
			weapon->wield();
	//����
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		//�ȷ�
			weapon->unequip();
			if (me->query_skill("leg")=="shenlong-tuifa"
				&& me->query_skill_mapped("leg")=="shenlong-tuifa"
				&& me->query_skill("shenlong-tuifa",1)>450)
			{
				message_vision(HIR"\n$NԾ���գ�˲�������߳����У��������ȷ�����ʽ����$n�ϰ����Ѩ��\n"NOR, me, target);
				me->prepare_skill("leg");
				me->add_temp("apply/leg",skill/3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->add_temp("apply/leg",-skill/3);
			}
			weapon->wield();
        }
		else {
			me->set_temp("jszf/posuo",1);
			me->add_temp("apply/throwing",(int)skill/3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			me->delete_temp("jszf/posuo");
			me->add_temp("apply/throwing",-(int)skill/3);
		}

		me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/4);
		me->add_temp("apply/throwing",-skill/4);

		me->add("neili", -500);
        me->add("jingli", -300); 
		
		me->start_perform(5,"����Ӱ��涡�");
        me->add_busy(2);
		return 1;
}

string perform_name(){ return YEL"��Ӱ���"NOR; }
int help(object me)
{
         write(HIB"\n����׶��֮����Ӱ��涡���"NOR"\n");
        write(@HELP
	����׶���ǽ����ɾ������似����Ӱ����������ߵ�
	Ѹ�����ߣ����ٳ��У����䰵����
	�������̵ĺ�ɳ��Ӱ�似�������˲����ݻ����Ѿ���
	���ܴ���죬���������书�ں���һ��
	
	ָ�perform throwing.posuo

Ҫ��
	����׶���ȼ���450 ����
	���������ȼ���450 ����
	�����Ʒ��ȼ�  450 ���� 
	��ɳ��Ӱ�ȼ���450 (����������)
	���߲�˿�ȼ���450 (����������)
	�����ȷ��ȼ���450 (����������)
	��ǰ��������1000 ����
	��ǰ��������500 ����
	��Ҫ��������׶����ɳ��Ӱ
	�ڹ����ޡ�
	�ְֳ�����

HELP
        );
        return 1;
}
