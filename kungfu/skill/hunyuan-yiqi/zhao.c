// sohu@xojh
//������ zhao.c
//���ֳ��ڷ�����

#include <ansi.h>
void remove_effect(object me,int count);

int exert(object me)
{    
      int skill;
	  skill=me->query_skill("hunyuan-yiqi",1);
	  if ( !me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ�á������֡���\n");
	
      if( (int)me->query_skill("hunyuan-yiqi", 1) < 350 )
                return notify_fail("����׽�ڹ���Ϊ�������޷�ʹ�á������֡���\n");
      if( (int)me->query_skill("force", 1) < 350 )
                return notify_fail("��Ļ����ڹ���Ϊ�������޷�ʹ�á������֡���\n");
 

      if (me->query_skill_mapped("force") != "hunyuan-yiqi")
                return notify_fail("�����ڹ��С������֡���\n");

      if( (int)me->query_con() < 50 )
                return notify_fail("��ĺ������̫�ͣ������޷�ʹ�á������֡���\n");
 
      if( (int)me->query("neili") < 1000 )
                return notify_fail("��Ŀǰ������̫���ˣ��޷�ʹ�á������֡���\n");   
    
      if( (int)me->query("jingli") < 800 )
                return notify_fail("��ľ�������������ʹ�á������֡���\n");   
      if( me->query_temp("hyyq/zhao"))
                return notify_fail("���������á������֡���\n");
                                                                                 
      message_vision(HIY"\n$N��Ԫһ����������������ת���������������γ�һ�ɱ��������������絹�۵Ľ��ӣ��������֡������֡��Ĺ���\n\n" NOR, me);
    
      me->set_temp("hyyq/zhao",skill);
	  
	  me->add_temp("apply/armor", skill/5);		
      me->add_temp("apply/parry", skill/5);
	  //me->add_temp("apply/dodge", skill/5);
	  me->add_temp("apply/defense", skill/5);

      me->add("neili", -200);  
	  me->add("jingli", -100);  

      call_out("remove_effect", 1, me, (int)me->query_skill("hunyuan-yiqi", 1)/40);
      if (me->query_skill("hunyuan-yiqi",1)<350)
      {
		  me->start_exert(2,"�������֡�");
      }
      return 1;
}

void remove_effect(object me,int count)
{
        int skill;
		if( !me||!me->query_temp("hyyq/zhao")) return;
		skill=me->query_temp("hyyq/zhao");
        if( count < 1
			||!me->is_fighting())
	   {
			  
		  me->add_temp("apply/armor", -skill/5);		
		  me->add_temp("apply/parry", -skill/5);
		  //me->add_temp("apply/dodge", -skill/5);
		  me->add_temp("apply/defense", -skill/5);
		  me->delete_temp("hyyq/zhao");
		  message_vision(HIR"\n$NĬ���ţ�ɢȥ��������ȫ�����µġ������֡�������\n"NOR, me);    
		  return;
		}
     
        call_out("remove_effect", 1, me,count -1);
		return;
}
string exert_name(){ return HIY"������"NOR; }

int help(object me)
{
        write(HIY"\n��Ԫһ����֮�������֡���"NOR"\n");
        write(@HELP
	���ֻ�Ԫһ�����������»����ķ������ۻ�Ԫһ����
	�ȿ������������֣�Ҳ����������ͷ�Ϲ���������
	�����Ȼ���籾�ŵ�һ���׽��������������
	��̥���׽�ķ���Ҳ�ǲ��׵��ڹ��ķ���
	��������ƾ��һ��������ת���������γɱ���������
	��ʱ��������������Ч������
	
	ָ�exert zhao

Ҫ��  
	��Ԫһ�����ȼ� 350  ���ϣ�
	�����ڹ��ĵȼ� 350  ���ϣ�
	������ǵ����� 50   ���ϣ�
	��ǰ���������� 1000 ���ϣ�
	��ǰ�ľ������� 800  ���ϡ�

HELP
        );
        return 1;
}
