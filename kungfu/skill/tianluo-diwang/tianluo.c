// zhuona.c ���޵�����
// cre by sohu@xojh
#include <ansi.h>

inherit F_SSERVER;
void dohit(object me,object target); 

string perform_name(){ return HIC"���޵���"NOR; }

int perform(object me, object target)
{
	int skill,hits;
	string msg,shou;
	
	if(!me->is_fighting())
		return notify_fail("��û��ս�����أ�\n");
	
	hits=(int)me->query_skill("tianluo-diwang",1)/100;
	
	if(!target) target = offensive_target(me);

	if( (skill=(int)me->query_skill("tianluo-diwang", 1)) < 150 )
		return notify_fail("������޵����ƻ��������죬�޷�ʩչ�����޵�����������\n");
	if( (int)me->query_skill("yunu-xinjing", 1) < 150 )
		return notify_fail("�����Ů�ľ����������죬�޷�ʩչ�����޵�����������\n");
	if( (int)me->query_skill("hand", 1) < 150 )
		return notify_fail("��Ļ����ַ����������죬�޷�ʩչ�����޵�����������\n");
	if(//me->query_skill_mapped("parry") != "tianluo-diwang"
		me->query_skill_prepared("hand") != "tianluo-diwang"
		||me->query_skill_mapped("hand") != "tianluo-diwang")
		return notify_fail("��û�м������޵����ƣ�\n");
	
	if ( me->query_temp("weapon"))
		return notify_fail("���ֳ����������ʹ�á����޵�����������\n");
	if (target->query_temp("tldw/zhuona"))
		return notify_fail("������ʹ�á����޵�����������\n");
	if(me->query("gender")=="����")
		return notify_fail("������Զ��֣������ʩչ�����޵�����������\n");
	if(me->query("gender")=="����") shou="�޳�������";
	else shou="��������";
	if(me->query("max_neili")<1500)
		return notify_fail("����������������޷�ʹ�á����޵�����������\n");
	if(me->query("neili")<500)
		return notify_fail("�������������޷�ʹ�á����޵�����������\n");
	if(me->query("jingli")<500)
		return notify_fail("�㵱ǰ�����������޷�ʹ�á����޵�����������\n");
	msg = HIC"\n$Nһ˫"+shou+"�ӳ�������һ�գ�����һ�ģ���$n���˻�������ߵ����Ǳ��ģ�˲���ĳ���ʮһ��\n"+
			HIC"$N���Ʒ����������֮�ڣ����ֵ������ر۷��ˣ�����$N˫�۷��裬��ֻ�������ƻ�����ǧ��ǧ�ƣ�\n"NOR;
	message_vision(msg,me,target);
	//me->set_temp("tldw/zhuona",1);
	if (random(me->query_dex(1))>target->query_dex(1)/3)
	{
		msg = HIY"\n��ƾ$n��ηɹ�������Ų��ʼ��շת����$N��Χ��������Ȧ�ӡ�\n"NOR; 
		message_vision(msg, me, target);
		target->start_busy(hits);
		target->set_temp("tldw/zhuona",1);
		call_out("dohit",1,me,target);

	}else {  
		msg = HIW"\n$n����һ�ݣ���$N΢΢һЦ���㿪�����С����޵����ơ�������\n"NOR; 
		message_vision(msg, me, target);
		me->add_busy(1);		
	}
	me->add("neili",-random(200));
	me->add("jingli",-random(100));
	if (objectp(target))
		call_out("do_effect",hits,me,target);
	me->start_perform(1,"���޵�����");
	return 1;
}


void dohit(object me,object target) 
{
	int damage;
	if (!objectp(target)) return;

	damage = (me->query("neili")-target->query("neili"))*me->query("jiali");
	if (damage<1) damage=1;
	if (damage>2000) damage=2000;
	
	message_vision(HIR"\n$n�ۼ�˫��Ҫ��ס$N�Ĳ��ӣ���֪�������۽���δ��֮�ʣ�$Nб��������һ�����ѳ�������Ȧ��\n"+
		"$næ�ر�ȥ׽����һ�¼��弲�����Լ��Ƶ������ˣ���Ҳ���㲻�ȣ�����һ�������ñ���������ʹ����\n"NOR, me, target);
	target->apply_condition("no_exert",1);
	target->receive_damage("qi",damage,me);
	target->receive_wound("qi",damage/4,me);
	me->add_temp("apply/attack",me->query_skill("tianluo-diwang",1)/2);
	me->add_temp("apply/damage",me->query_skill("tianluo-diwang",1)/5);

	COMBAT_D->do_attack(me, target,0, 3);
	me->add_temp("apply/attack",-me->query_skill("tianluo-diwang",1)/2);
	me->add_temp("apply/damage",-me->query_skill("tianluo-diwang",1)/5);
	return;
	
}
void do_effect(object me,object target)
{
	if (!target) return;
	target->delete_temp("tldw/zhuona");
	tell_object(me,target->name(1)+HIC"���ڰ��������е����޵����ƣ���������һ������\n"NOR);
	tell_object(target,HIC"�����ڰ��������е����޵����ƣ���������һ������\n"NOR);
	return;
}

int help(object me)
{
   write(WHT"\n���޵����ơ�"HIC"���޵���"WHT"����"NOR"\n");
   write(@HELP
	��Ĺ��������ѧ���ɹ�Ĺ��ʦ���ֳ�Ӣ������
	Ϊ�����ޱȵ��Ʒ���Ϊ�����С��ŮΪʦ��
	���䴫�ڡ�����������ϰ�����Ṧ��Ʈ����
	�飬�仯�򷽡���ϰ����߾��磬����˫��
	��ס�žŰ�ʮһֻ��ȸ��
	ע�⣺������׽����ף����Զ�����Է���
	���ĸ��ʡ����Դ���40���Ժ���Ůȭ������


	perform hand.tianluo
	
Ҫ��
	�������Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	���޵����ȼ� 150 ���ϣ�
	�����ַ��ȼ� 150 ���ϣ�
	��Ů�ľ��ȼ� 150 ���ϣ�
	�����ұ��ַ�Ϊ���޵����ƣ�
	
	
HELP
   );
   return 1;
}
