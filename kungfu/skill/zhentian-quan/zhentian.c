// zhentian.c ����ȭ-�������

#include <ansi.h>
#include <combat.h>
inherit SKILL;
inherit F_SSERVER;

string perform_name(){ return HIC"�������"NOR; }

void remove_effect(object target);
void check_fight(object me,object target);

int perform(object me, object target)
{
    int lvl;
    lvl = (int)me->query_skill("zhentian-quan", 1);
   
    if( !target ) target = offensive_target(me);
    
    if( !target || !me->is_fighting(target) )
      return notify_fail("�����������ֻ����ս���жԶ���ʹ�á�\n");

    if (me->query_skill_prepared("cuff") != "zhentian-quan"
      || me->query_skill_mapped("cuff") != "zhentian-quan")
      return notify_fail("�������޷�ʹ�á�������������й�����\n");      

    if( (int)me->query_skill("zhentian-quan",1) < 100 )
      return notify_fail("�������ȭ������죬����ʹ�á������������\n");
    
    if( (int)me->query_skill("cuff",1) < 100 )
      return notify_fail("��Ļ���ȭ���ȼ�����������ʹ�á������������\n");  
    
    if( (int)me->query_skill("xuantian-wuji", 1) < 100 )
      return notify_fail("��������޼����ȼ�����������ʹ�á������������\n");

    if( (int)me->query("max_neili") < 1400 )
      return notify_fail("��Ĺ���̫��������ʹ�á������������\n");
    
    if( (int)me->query("neili") < 800)
      return notify_fail("�������̫���ˣ��޷�ʹ�ó��������������\n");   
    
    if( (int)me->query("jingli") < 200 )
      return notify_fail("�����ھ���̫�٣�����ʹ�á������������\n");
  
    if(me->query_temp("klpfm/zhentian"))
      return notify_fail("����ʱ����ʹ�á�����������ˡ�\n");  
                                                                               
    message_vision(HIC"\n$Nʩչ������ȭ�ġ����������������ת׾��ȴ��ȥ����죬ȭ����������������$n��ȥ��\n"NOR, me,target);
    message_vision(HIW"\n$N��ȭ���Х��������ӿ�������������γ����˵���֮����\n"NOR, me,target);

    me->add("neili", - 150);
    me->add("jingli", -100);      
    
    if( random(lvl) > (int)target->query_skill("parry",1)/2
	  ||random(me->query_str(1))>target->query_dex(1)/2)
	{
	  message_vision(HIY"\n$nһʱ���죬��ʱ��$N��������֮����Ӱ�죬����������̶����֮�С�\n"NOR, me,target);
	  target->add_busy(1);
		if( !target->query_temp("kl_zhentian")   ) {
		  target->add_temp("apply/attack", -lvl/6);
		  target->add_temp("apply/dodge", -lvl/6);
		  target->add_temp("apply/parry", -lvl/6); 
		  target->set_temp("kl_zhentian",lvl); 
		  if (objectp(target))
			  call_out("zhentian",lvl/20,me,target); 
		}  
    }
    else {
	  message_vision(YEL"\n$n�Ṧ��������ʱ����$N�����е������������Χ��\n"NOR, me,target);
    }
    
	me->add_temp("apply/attack", lvl/5 );
	me->add_temp("apply/damage", lvl/6 );
	me->add_temp("apply/cuff", lvl/6 ); 

	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (me->query("gender")=="����")?3:1);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (me->query("gender")=="����")?3:1);
	   
	   if(me->query("gender")=="����"&& me->is_fighting()) 
	   {
			me->add_temp("apply/attack", lvl/5 );
			me->add_temp("apply/damage", lvl/6 );
		    message_vision(HIW"\n$N������ͣ�����ȭ��ʩչ�����£�һ���ĳ����������𶯵ĺ��һ�����졣\n"NOR, me,target);
			me->add("neili", - 100);
			me->add("jingli", -50);   

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			me->add_temp("apply/attack", -lvl/5 );
			me->add_temp("apply/damage", -lvl/6 );				
		}
	me->add_temp("apply/attack", -lvl/5 );
	me->add_temp("apply/damage", -lvl/6  );
	me->add_temp("apply/cuff",-lvl/6 ); 
	
	me->delete_temp("klpfm/zhentian");
	me->start_busy(2);
	me->start_perform(4,"�����������");
    return 1; 
}

void zhentian(object target)
{
    int lvl;
	if (!objectp(target)) return;
	lvl=target->query_temp("kl_zhentian");
	target->add_temp("apply/attack", lvl/6);
    target->add_temp("apply/dodge", lvl/6);
    target->add_temp("apply/parry", lvl/6);
    target->delete_temp("kl_zhentian");
    tell_object(target, HIB"�㽥���侲����������ȭ����ɵ�����״̬�ָֻ��糣��\n"NOR);
	return;
}

int help(object me)
{
write(HIC"\n����ȭ֮�������������"NOR"\n\n");
write(@HELP
	����ȭ�����������µ��������似��ƾ����������
	�Կ��ٳ�ȭ���Ϳ�������Ħ�����γɵ�����֮������
	��Խ�ߣ�����Ч��Խǿ����������֮�⡣���������
	�����ô��������Ӱ�첢�������֡��������У�����
	����������������ǿ����������Ʋ����һ�С�
	����������������ж��似�����Ч����
	
	ָ�perform cuff.zhentian
Ҫ��
	������� 1400 ���ϣ�
	��ǰ���� 800 ���ϣ�
	��ǰ���� 200 ���ϣ�
	�����޼� 100 ���ϣ�
	����ȭ�� 100 ���ϣ�
	����ȭ�� 100 ���ϣ�
	�������ұ�������ȭ��
	���ڵ���ʽ������ɵ���busy�ҹ����½���

HELP
);
return 1;
}
