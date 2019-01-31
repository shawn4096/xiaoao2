
// Ѫ���󷨣�Ѫ���ŵ�������ѧ�������ӵ����Ĺ���
// xuedao.c 

#include <ansi.h>
inherit F_SSERVER;
//inherit F_CLEAN_UP;
int help(object me);

void remove_effect(object me, int amount);

string exert_name(){ return HBRED+HIY"Ѫ����"NOR; }

int exert(object me)
{
	int skill, i;
	
	if(!me->is_fighting()) 
	     return notify_fail("��ֻ����ս������Ѫ�����������Լ��ĵ���������\n");

	if( (int)me->query("neili") < 5000  ) 
		return notify_fail("�������������\n");
	if( (int)me->query("jingli") < 3000  ) 
		return notify_fail("��ľ���������\n");

	if( me->query_skill("force", 1) < 500 )
        return notify_fail("��Ļ����ڹ���Ϊ���δ����ʩչֻ���˼�����\n");
	if( me->query_skill("xuedao-jing", 1) < 500 )
        return notify_fail("���Ѫ����������Ϊ���δ����ʩչֻ���˼�����\n");
	if (!me->query("quest/xd/xdj/xuedao/pass"))
	{
		return notify_fail("����δ����Ѫ�������еĴ󷨾������裬�޷�ʩչ��\n");

	}
	if( (int)me->query_temp("xdj/xuedao") ) 
		return notify_fail("���Ѿ���ʩչѪ�������ˡ�\n");

   // skill = (int)me->query_skill("force",1) + (int)me->query_skill("xuedao-dafa",1);
    skill = (int)me->query_skill("xuedao-jing",1);
  
	message_vision(MAG "\n$N��Ȼ������𼦶������������ƽ�������˫�ַ���������������Ҷ��������������,��ʽԽ��Խ�֡�\n" 
					        +"������������ʱ˫�ֳŵأ���ʱ��Ծ��գ�����ʱ��ͷ���ص������°���ȴƾ��������������!\n"
					        +"$N��������������΢΢�����ͬʱ�����Ŵ���������У���������ʮ�ֹŹ֣������еĵ�ȴ����ʶ�Ļ��˻Ρ�\n"
							+"�����ƺ���ø�Ϊ���ͣ�\n"NOR, me);
      me->add_temp("apply/attack", skill/6);
      me->add_temp("apply/blade", skill/4);
	  me->add_temp("apply/damage", skill/5);

      me->set_temp("xdj/xuedao", skill);
	  
	  call_out("remove_effect", 1, me,(int)skill/30);	

	  return 1;
}

void remove_effect(object me, int count)
{    
     int skill;
	 if (!me||!me->query_temp("xdj/xuedao")) return;
	 skill=me->query_temp("xdj/xuedao");
	 if( !me->is_fighting()
		||count-- < 0 )
	 {
		  me->add_temp("apply/attack", -skill/6);
		  me->add_temp("apply/blade", -skill/4);
		  me->add_temp("apply/damage", -skill/5);
		  me->delete_temp("xdj/xuedao");
		  tell_object(me, MAG"\n���Ѫ�����ؼ�������ϣ�����Ҳ�𽥻ָ�ԭ����\n"NOR);
		  return;
       } 
	  call_out("remove_effect",1,me,count--);
	
}

int help(object me)
{
        write(HIR"\nѪ����֮��Ѫ���󷨡���"NOR"\n");
        write(@HELP
	Ѫ���������ຣ�ڽ�Ѫ���ŵ�һ��������Ѫ������������
	���ų����ֵ�һа�ɸ��֡���Ҫԭ�������Ϊ�������ص�
	�ڹ��͵������䣬��������벻����Ч����Ѫ������Ѫ
	���ŵ�����֮����Ѫ���ؼ��ľ����似���Ǻ��ĵ��Ӳ�����
	ע�⣺��ѩ�ȼ�ս�����л������������������Ȼ�����
	������ÿ����̼��ɡ�

	˵����Ѫ���������Ѫ���Ŷ��ڵ������������鼫�£�
	�ܶ๦�������ھ��͵���ʹ�ü��ɽ�ϣ�ʹ��Ѫ���Ŷ���
	���������þ��ж���֮����
	
	ָ�exert xuedao

Ҫ��
	��ǰ�������� 5000 ���ϣ�
	��ǰ�������� 3000 ���ϣ�
	Ѫ�����ĵȼ� 500 ���ϣ�
	�����ڹ��ȼ� 500 ���ϣ�
	�����ڹ�ΪѪ������

HELP
        );
        return 1;
}