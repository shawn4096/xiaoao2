//perform ku,���ݡ��ִ�
//cool@SJ 99529

#include <ansi.h>
void remove_effect(object me,int count);

int exert(object me)
{    
      int i=me->query_skill("kurong-changong", 1);
	  if( (int)me->query_skill("kurong-changong", 1) < 200 )
                return notify_fail("��Ŀ���������Ϊ�������޷�ʹ�á��ݡ��ִ󷨣�\n");

      if (me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("�����������������޷�ʩչ���ݡ��ִ���\n");
/*
      if (me->query_skill_mapped("parry") != "kurong-changong")
                return notify_fail("������ÿ���������Ϊ�мܣ�����ʹ�á��ݡ��ִ󷨡�\n");*/

      if( (int)me->query_con() < 35 )
                return notify_fail("��ĸ���̫�ͣ������޷�ʹ�á��ݡ��ִ󷨣�\n");
	  if( (int)me->query_skill("force",1) < 200 )
                return notify_fail("���������̫���ˣ��޷�ʹ�ó����ݡ��ִ󷨣�\n"); 
      if( (int)me->query("neili") < 500 )
                return notify_fail("�������̫���ˣ��޷�ʹ�ó����ݡ��ִ󷨣�\n");   
    
      if( (int)me->query("max_neili") < 2500 )
                return notify_fail("���������Ϊ��ô�����ʹ�á��ݡ��ִ󷨣�\n");   
                                                                                
      if( me->query_temp("pf_ku")   )
                return notify_fail("���������á��ݡ��ִ󷨣�\n");
      if( !me->query("quest/tls/kurong/pass") && me->query_temp("pf_rong")  )
                return notify_fail("�㹦����δ�ڻ��ͨ�����������õġ��١��ִ����ͻ��\n"); 
      if ( !me->is_fighting()) {
                message_vision(HBGRN+HIW"\n$N�������,˫���ſ��⻮�������ջ��ڵ�����𡸿ݡ��ִ󷨣�������ɢȫ������ɢ��һ��������\n\n" NOR, me);
                if (me->query_skill("kurong-changong",1)<350)
                {
					me->start_busy(1);
                }
                me->set_temp("pf_ku",1); 
                me->add_temp("apply/armor", i/2); 
                me->add("neili", -400);   
        } 
        else {
                message_vision(HBGRN+HIW"\n$Nȫ���Ƴ�һ�ƣ�˳���˳����ɣ��������𡸿ݡ��ִ󷨣������鲼ȫ������������һ��������\n\n" NOR, me);
                if (me->query_skill("kurong-changong",1)<550)
                {
					me->start_busy(1);
                }
                me->set_temp("pf_ku",1); 
                me->add_temp("apply/armor", i/2); 
                me->add("neili", -600);           
      }
	  me->set_temp("pf_ku",i);
      call_out("remove_effect", 1, me,i);
      return 1;
}

void remove_effect(object me,int count)
{
      int i;
	  if (!me) return;
	  i=me->query_temp("pf_ku");

	  if (!me->is_fighting() || count < 0)
	  {
	 	me->delete_temp("pf_ku");
		me->add_temp("apply/armor", -i/2); 
		message_vision(WHT"\n$N�����������������һ������ɢȥ������ȫ��������\n"NOR, me);
		return;
      }
	  call_out("remove_effect",1,me,count -1);
	  return ;
}

string exert_name() {return WHT"���־�"NOR;}

int help(object me)
{
        write(WHT"\n�������������־�����"NOR"\n");
        write(@HELP
	�����������Ǵ����������Ժ--���������ֿ��ٳ��ϵ��ڹ��ķ�
	�ഫ�����������ڰ˿���֮�䡣��˿����ֶ����ϱ��������÷�
	�У����Ƿֱ���һ��һ�٣������ϱ��ֱ��ǣ������޳���������
	�֣��������ң������޾��� ���������޿����ٷ��Ǵ�ɡ�����
	�������������������һ����ֻ�εð�ݰ��١�
	
	���־�������ʹ�����������������������⣬ǿ���������
	��ľ״������������������

Ҫ��:
	�������� 200 �����ϣ�
	������� 2500 ���ϣ�
	��ǰ���� 500 ���ϣ�
	������� 35  ���ϣ�
	�輤���ڹ�Ϊ����������

HELP
        );
        return 1;
}


