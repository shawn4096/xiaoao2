// hengsao cred by sohu@xojh ̫��ȭ��ɨǧ��


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
  int lvl,i,j;
  string msg;
  lvl = (int)me->query_skill("taizu-quan", 1);
  if (me->query("max_pot") >= 350 ) lvl = lvl /4 ;//250��˥��
  
  if( !target ) target = offensive_target(me);
  if( !objectp(target)
	 || !me->is_fighting(target)
	 || !living(target)
	 || environment(target)!=environment(me))
		return notify_fail("����ɨǧ����ֻ����ս���жԶ���ʹ�á�\n");

   if( objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ�á���ɨǧ������\n");

   if( (int)me->query_skill("taizu-quan", 1) < 100 )
		return notify_fail("���̫��ȭ��������죬ʹ��������ɨǧ����������\n");

   if(!me->query_skill("force", 1) || (int)me->query_skill("cuff",1)<100)
   if( (int)me->query_skill("parry", 1) < 100 )
           return notify_fail("��Ļ������ܵȼ���������ʹ��������ɨǧ����������\n");

   if( (int)me->query_skill("dodge",1) < 100 )
		return notify_fail("����Ṧ�ȼ�����������ʹ�á���ɨǧ������\n");


   if( me->query_skill_prepared("cuff") != "taizu-quan"
	 || me->query_skill_mapped("cuff") != "taizu-quan")
		return notify_fail("�������޷�ʹ�á���ɨǧ������\n");


   if( me->query_skill_mapped("parry") != "taizu-quan")
		return notify_fail("����Ҫ�����м�Ϊ̫��ȭ������ʹ�á���ɨǧ������\n");


   if( (int)me->query("max_neili") < 1300)
		return notify_fail("�������̫����ʹ��������ɨǧ������\n");

   if( (int)me->query("neili") < 500 )
		return notify_fail("����������̫����ʹ��������ɨǧ������\n");

   if( (int)me->query("jingli") < 500 )
           return notify_fail("������̫���ˣ�ʹ��������ɨǧ������\n");
   if (me->query("family/family_name")=="��ͨ����")
	{
	   i=3;
       j=1;
	}
   else 
	{
	   i=1;
       j=6;
	}

   message_vision(HIC"\n$N����������ǰ�����첢���ڿۣ��ҽ�Ϊ֧�㣬�������̣��漴������ǰ����ת�������������У�\n"NOR,me);

   //if(!userp(target) && me->query("max_pot") <= 350)  target->set_temp("must_be_hit",1);

	me->add_temp("apply/attack", lvl/j);
	me->add_temp("apply/damage", lvl/j);
	me->add_temp("apply/cuff", lvl/j);
	me->add_temp("apply/strength", lvl/3);
    me->set_temp("tzq/hengsao",1);
      COMBAT_D->do_attack(me, target, 0, i);

	if (objectp(target) && me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, i);

	if (objectp(target) && me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, i);

   //�ȴ����ܺ�
	if ( objectp(target) && me->is_fighting(target)&&me->query("quest/�����˲�/�书/quanli")){
	   message_vision(HIR"$N��Ȼ�����崦����ȭ���̫��ȭ�ڻ��ͨ����ʽ��Ȼ�򵥣���ÿһ�з�����ȴ����������\n"NOR,me,target);
       target->add_temp("must_be_hit",1);
	   me->add_temp("apply/damage",lvl/5);
       COMBAT_D->do_attack(me, target, 0, 3);	  
	   target->delete_temp("must_be_hit");
	   me->add_temp("apply/damage",-lvl/5);
	}
	
	if (objectp(target) && me->is_fighting(target) && me->query("quest/baduanjin/pass2"))
	{
		message_vision(HIB"$N��Ȼ�����λ����ķ���̫��ȭ�ڻ��ͨ��ÿһ�з���������Ī�����ܡ�\n"NOR,me,target);
		target->add_temp("must_be_hit",1);
	   me->add_temp("apply/damage",lvl/2);
       COMBAT_D->do_attack(me, target, 0, 3);
	   COMBAT_D->do_attack(me, target, 0, 3);	   
	   target->delete_temp("must_be_hit");
	   me->add_temp("apply/damage",-lvl/2);		
	}

	
	me->add_temp("apply/attack",- lvl/j);
	me->add_temp("apply/damage", -lvl/j);
	me->add_temp("apply/cuff", -lvl/j);
	me->add_temp("apply/strength",- lvl / 3);
    me->add("jingli", -100);
    me->add("neili", -200);
	me->delete_temp("tzq/hengsao");
    me->start_busy(random(2));

	if (!me->query("quest/baduanjin/pass2")) me->start_perform(2+ random(2),"����ɨǧ����");
	else
		me->start_perform(2,"����ɨǧ����");

	return 1;
}


string perform_name(){ return HIR"��ɨǧ��"NOR; }

int help(object me)
{
	write(HIR"\n̫��ȭ֮"+HIY"����ɨǧ����"NOR"\n\n");
	write(@HELP
	�ഫΪ��̫���Կ�ط�������ʳ�̫��ȭ��̫��ȭ������ʵս�������񶷣�
	����磬����磬ǰ���죬����׷�����ֻ���һ���ݡ��ص�Ϊ��·�Ͻ���
	������չ����ʽ������������������ã���ʵ���棬��ȭ��������
	��̿���������ǿ���侢�������ڳš�����ն�������á��������У�����
	����è�������绢�������������������硱��
	
	ע�⣺250����Ч����ʼ˥�������⿪�����˲����Ⲣ�������ָ�㣬
	����н��ٴη�Ծ�����н�Ϊ��ͨ���շ����޵á�
	Ҫ��
		������� 1300 ���ϣ�
		��ǰ���� 500  ���ϣ�
		��ǰ���� 500  ���ϣ�
		̫��ȭ�ȼ� 100 ���ϣ�
		�����ڹ� �Ṧ �м� ȭ�� �ȼ� 100 ���ϣ�
		����ȭ��Ϊ̫��ȭ��
		�����м�Ϊ̫��ȭ��
		��ȭ��Ϊ̫��ȭ�ҿ��֡�

HELP
	);
	return 1;
}
