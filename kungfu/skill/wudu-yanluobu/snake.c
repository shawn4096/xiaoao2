#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
	   int skill,tg_skill,time;
	   string msg;
	   if( !target ) target = offensive_target(me);
	   if( !target || !target->is_character() || !me->is_fighting(target) )
		  return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	   if( (int)me->query_skill("wudu-yanluobu", 1) < 450 )
		  return notify_fail("����嶾���ܲ���򲻹�������ʹ��������������\n");
	   if( (int)me->query_skill("dodge", 1) < 450 )
		  return notify_fail("��Ļ����Ṧ��򲻹�������ʹ��������������\n");
	   if( (int)me->query_skill("force", 1) < 450 )
		  return notify_fail("��Ļ����ڹ���򲻹�������ʹ��������������\n");
	   if( (int)me->query("neili", 1) < 1500 )
		  return notify_fail("����������̫��������ʹ�á�����������\n");
	   if( target->is_busy() )
		  return notify_fail(target->name() + "Ŀǰ����æ���ң��㻹��תʲô���Ͽ�����ɣ�\n");
	   msg = HIC "$N���к���һ�䣬ʹ�������������ľ�������Խ��Խ�졣ֻ��$N�ɿ���Ƴ����ߣ�հ֮��ǰ����֮�ں�һʱ�䵽������$N����Ӱ��\n"NOR;
	   message_vision(msg, me, target);
	   time = (int)me->query_skill("wudu-yanluobu",1)/50;
	   if (!userp(target)) 
		   skill = (int)me->query_skill("wudu-yanluobu",1) + (int)me->query_skill("dodge",1);
	   else skill=(int)me->query_skill("wudu-yanluobu",1);

	   tg_skill = (int)target->query_skill("dodge",1);
	   me->add("neili", -100);
	   if (random(skill) > tg_skill/2
		   ||random(me->query_int(1))>target->query_int(1)/2
		   || random(me->query("combat_exp"))>target->query("combat_exp")/2)
		{
		  target->add_busy(random(time)+1);
		  msg = HIR"$n���ɵ�һ�������޴룬��$N�������У�\n"NOR;
		  message_vision(msg, me, target);
		  //�����Է�
		  if (!target->query("wdylb/snake"))
		  {
			  message_vision(HBBLU+HIW"$N�������ߣ��鶯�쳣��$n"HBBLU+HIW"�پ��Լ�����������̶��״̬���\n"NOR,me,target);
			  target->add_temp("apply/dodge",skill/3);
			  target->add_temp("apply/parry",skill/3);
			  target->set_temp("wdylb/snake",skill);
			  call_out("ylb_attack",1,target,time);
		  }
		  return 1;
		}
		else
		   {
			me->start_busy(2+random(2));
			msg = HIR"����$n�Ծ��ƶ��������Ż���˿������$N��Ӱ��,$N�Լ����۵���ͷ�󺹣�\n"NOR;
			message_vision(msg, me, target);
		 }
		 return 1;
}
int ylb_attack(object target,int count)
{
	int skill;
	if (!target) return 0;
	if (!target->query_temp("wdylb/snake")) return 0;
	skill=target->query_temp("wdylb/snake");
	target->add_temp("apply/dodge",-skill/3);
	target->add_temp("apply/parry",-skill/3);
	target->delete_temp("wdylb/snake");
	tell_object(target,YEL"�㾫��һ�����ڰ�������������������Ӱ��!\N"NOR);
	return 1;
}
string perform_name(){ return HIC"��������"NOR; }
int help(object me)
{
        write(HIY"\n�嶾����֮����������:"NOR"\n\n");
        write(@HELP
	�嶾�̳��ϼ�����ſ���ϰ���ؼ�����������ɾ���ѩ��
	�Ժκ�ҩ��ϰ�ã����Ϊ��������ֵľ���֮һ����˵��
	���ھ�����似Ҫ���Լ�����Ҫ��ܸߡ�

	ָ�perform dodge.snake

Ҫ��
	�����ڹ�Ҫ�� 450 ������
	�嶾���޲��� 450 ��
	�����ṦҪ�� 450 ��
	��ǰ�ڹ�Ҫ�� 1500 ���ϣ�


HELP
);
return 1;
}
