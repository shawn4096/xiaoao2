// wofo.c yizhi-chan perform ����ҷ�
// By Spiderii Ч���޸�
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
	string msg;
	int busy ;
      if( !target ) target = offensive_target(me);
     
      if( !objectp(target) || !me->is_fighting(target) )
	  return notify_fail("������ҷ�ֻ����ս���жԶ���ʹ�á�\n");
	     
      if( objectp(me->query_temp("weapon")) )
	  return notify_fail("��������ʹ�á�����ҷ𡹣�\n");
      
      if( (int)me->query_skill("yizhi-chan",1) < 250 )
	  return notify_fail("���һָ��������죬����ʹ�á�����ҷ𡹣�\n");

      if( (int)me->query_skill("yijin-jing",1) < 250 )
	  return notify_fail("����׽�ڹ��ȼ�����������ʹ�á�����ҷ𡹣�\n");  
      
      if( (int)me->query_str() < 25 )
	  return notify_fail("��ı�������ǿ������ʹ�á�����ҷ𡹣�\n");
      
      if( (int)me->query("max_neili") < 2000 )
	  return notify_fail("�������̫��������ʹ�á�����ҷ𡹣�\n");
      
      if( (int)me->query("neili") < 500 )
	  return notify_fail("�������̫���ˣ��޷�ʹ�ó�������ҷ𡹣�\n");   
										 
      if (me->query_skill_prepared("finger") != "yizhi-chan"
       || me->query_skill_mapped("finger") != "yizhi-chan")
		return notify_fail("�������޷�ʹ�á�����ҷ𡹽��й�����\n");										 
      if( me->query_temp("wofo"))
		return notify_fail("������ʹ��һָ�������⹥��������ҷ𡹣�\n");
	  if( target->is_busy())
		return notify_fail("�Է��Ѿ���æ������,���޷�ʹ�á�����ҷ𡹣�\n");

	  if (target->is_busy()) return notify_fail("�Է����Թ˲�Ͼ���ŵ������ɣ�\n");
       
    
      message_vision(HIY"$NͻȻ���������գ�������ָ�������͵�һ����һ�ɾ����������������$n�����Ѩ��\n" NOR, me, target);   
      busy=3+random(me->query_skill("yizhi-chan",1))/100;
      if(busy>8)
      busy=8;
      if( wizardp(me)) tell_object(me,sprintf("busy=%d\n",busy));
     
	  if( random(me->query("combat_exp"))  > target->query("combat_exp")/2
		  ||random(me->query_skill("finger",1))>target->query_skill("parry",1)/3)
	  {
  	
       
		message_vision(HIW"\n$nֻ�е�Ѩ��һ�飬��������ɢ���������á�\n"NOR, me, target); 
		me->set_temp("wofo",1);  
		me->add("neili", -350);    
		target->start_busy(busy);    
					
		//call_out("remove_effect", me->query_skill("yizhi-chan") / 20 + 2, me);
      }
      else {
		msg = HIY"$n����$N����ͼ��һ�������ݵض����$N����һ�У�\n"NOR;	  
		message_vision(msg, me, target);					
		me->start_busy(1+random(2));
		me->add("neili", - 100);
      }
	  if (me->query_skill("yizhi-chan",1)<350 ||!me->query("quest/sl/yzc/pass"))
	  {
		me->start_perform(2,"����ҷ�");
		//me->start_busy(random(2));
	  }
	   me->delete_temp("wofo");
      return 1;
}

/*
void remove_effect(object me)
{
	if (!me) return;
	me->delete_temp("wofo");
       
	message_vision(HIR"$N�ġ�����ҷ��˹���ϣ���ɫ�ÿ����ˡ�\n"NOR, me);
}*/
string perform_name(){ return HIY"����ҷ�"NOR; }

int help(object me)
{
        write(HIB"\nһָ��֮������ҷ𡹣�"NOR"\n");
        write(@HELP
	�����ھ�һָ����Ϊ������ʮ����֮һ�����ڶ������ȱ���Ѫ�Ľᾧ
	�书���ص��ǣ���ȫ��������һָ������֮��ﵽ���������������
	����ǰ������ġ�֮Ŀ�ġ���һָǬ���̺���ǧ���磬�򷨹�һ���⾳
	�������ﵽ�����ʱ�������������ɽ�����ȫ��Ѩ�����֣�һ������
	�л�����öԷ����С�������Ч��һָ������ȫƾ�׽���Ĺ���֧
	�ţ�����Խǿ������Խ��Ϊ�����к��ڵ��ش��书��
	ע�⣺�����ͻ����书��ϣ����г������ϵĹ�����������ܻ�Ե�ɺ�
	�õ����δ�ʦ��ָ�㣬��һָ���������ٴ�������

	ָ��;perform finger.wofo

Ҫ��  
	������� 2000 ���ϣ�      
  	��ǰ���� 500  ���ϣ�  
	һָ���ȼ� 250 ���ϣ�
	�׽�ȼ� 250 ���ϣ�
	����ָ��Ϊһָ����               
	�����ޱ���,350���Ծ���������̺���pfmʱ�䡣��
                               
HELP
        );
        return 1;
}