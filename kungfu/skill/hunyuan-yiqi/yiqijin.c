// sohu@xojh
//һ���� yiqijin.c
//���ֿ��������似

#include <ansi.h>
void remove_effect(object me,string ks);

int exert(object me)
{    
      int skill;
	  string ks,ksc;
	 
	  skill=me->query_skill("hunyuan-yiqi",1);
	  if ( !me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ�á�һ��������\n");
	  if(!me->query("quest/sl/hyyq/yiqijin/pass"))
                return notify_fail("��ֻ����˵�����Ź��򣬵������޷�ʹ�á�һ��������\n");
      if( (int)me->query_skill("hunyuan-yiqi", 1) < 450 )
                return notify_fail("����׽�ڹ���Ϊ�������޷�ʹ�á�һ��������\n");
      if( (int)me->query_skill("force", 1) < 450 )
                return notify_fail("��Ļ����ڹ���Ϊ�������޷�ʹ�á�һ��������\n");
 

      if (me->query_skill_mapped("force") != "hunyuan-yiqi")
                return notify_fail("�����ڹ��С�һ��������\n");

      if( (int)me->query_con() < 50 )
                return notify_fail("��ĺ������̫�ͣ������޷�ʹ�á�һ��������\n");
 
      if( (int)me->query("neili") < 2000 )
                return notify_fail("��Ŀǰ������̫���ˣ��޷�ʹ�á�һ��������\n");   
    
      if( (int)me->query("jingli") < 1000 )
                return notify_fail("��ľ�������������ʹ�á�һ��������\n");   
      
	  if( me->query_temp("hyyq/yiqijin"))
                return notify_fail("���������á�һ��������\n");
     
	  ks=me->query("env/��Ԫһ����");  																			   
	  if (!ks)
				return notify_fail("��Ҫ��һ������ʹ��������ֹ����ϣ�\n");
	   if ((int)me->query_skill(ks,1)<450)
				return notify_fail("����Ż����似����450�����������ԣ�\n");
	 
	/*  skills=me->qury_skill();
	  for (i=0;i<sizeof(skills);i++ )
	  {
		  if (ks==skills[i]) break;
		  else return notify_fail("�����û��ѧ���Ź������ʹ��һ������\n");
	  }*/
	  ksc=to_chinese(ks);					   
      
	 
	  message_vision(HBYEL"\n$N����һ����������Ԫһ������ת��Ϣ������һ�������İ�����ʹ��"+ksc+HBYEL"�У���������������ž�������죡\n\n" NOR, me);
    
      me->set_temp("hyyq/yiqijin",skill);
	  
	  me->add_temp("apply/"+ks, skill/3);		

      me->add("neili", -500);  
	  me->add("jingli", -300);  

      call_out("remove_effect", (int)me->query_skill("hunyuan-yiqi", 1)/40, me,ks);
      
	  me->start_exert(2,"��Ԫһ����");
      return 1;
}

void remove_effect(object me,string ks)
{
        int skill;
		if( !me||!me->query_temp("hyyq/yiqijin")) return;
		skill=me->query_temp("hyyq/yiqijin");
 	    me->add_temp("apply/"+ks, -skill/3);	
		me->delete_temp("hyyq/yiqijin");
		message_vision(HIR"\n$N����һ������������һ����������ɢ����\n"NOR, me);    
	    return;
}
string exert_name(){ return HIR"һ����"NOR; }

int help(object me)
{
        write(HIY"\n��Ԫһ����֮��һ��������"NOR"\n");
        write(@HELP
	���ֻ�Ԫһ�����������»����ķ������ۻ�Ԫһ����
	�ȿ�������һ������Ҳ����������ͷ�Ϲ���������
	�����Ȼ���籾�ŵ�һ���׽��������������
	��̥���׽�ķ���Ҳ�ǲ��׵��ڹ��ķ���
	һ����ȫƾһ�������������ֵ�����������Ӳ����ʩ
	չ�������ڶ��������������������Կ�����Ч����Ҫ
	���ܷ���ʹ�á�

	ע�⣻set ��Ԫһ���� xx [leg,strike,claw,hand
	finger,cuff �����书Ӣ��]

	ָ�exert yiqijin

Ҫ��  
	��Ԫһ�����ȼ� 450  ���ϣ�
	�����ڹ��ĵȼ� 450  ���ϣ�
	������ǵ����� 50   ���ϣ�
	��ǰ���������� 2000 ���ϣ�
	��ǰ�ľ������� 1000  ���ϡ�

HELP
        );
        return 1;
}
