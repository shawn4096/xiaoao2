//shigu.c һ����ָ
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

string perform_name(){ return HIR"һ����ָ"NOR; }

int perform(object me, object target)
{
      string msg; 
      int i, damage,p;                                  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("������û�бʣ��޷�д��һ����ָ��\n");

      if( !target ) target = offensive_target(me);
       
      if( !target || !me->is_fighting(target) )
         return notify_fail("һ����ָֻ����ս���жԶ���ʹ�á�\n");
      if (!me->query("quest/tls/yiyangshu/pass"))
         return notify_fail("��ֻ����˵��һ����ָ��������ȴ����ʹ�á�\n");
   
      if((int)me->query_skill("yingou-bifa",1) < 400 )
         return notify_fail("��������ʷ���������죬����дһ����ָ��\n");
       if(me->query_int() < 50 )
         return notify_fail("��ĺ������Բ���50������дһ����ָ��\n");
      
      if((int)me->query_skill("literate",1) < 300 )
         return notify_fail("��Ķ���д�ֵȼ�����������д��һ����ָ��\n");  
	  if(me->query("family/family_name") !="������" )
	//	  || me->query("family/master_name")!="һ�ƴ�ʦ"
         return notify_fail("�㲻�������µ��ӣ��޷�д��һ����ָ��\n");  
	   if(me->query_skill_mapped("force")!="qiantian-yiyang" )
         return notify_fail("����ڹ��輤��Ǭ��һ����������д��һ����ָ��\n");  
      //if((int)me->query_skill("yiyang-zhi",1) < 400 )
         //return notify_fail("���һ��ָ�ȼ�����������д��һ����ָ��\n");
      if((int)me->query_skill("qiantian-yiyang",1) < 400 )
         return notify_fail("���Ǭ��һ���ȼ�����������д��һ����ָ��\n");
      if (me->query_skill_mapped("force")!="qiantian-yiyang")
		  if(me->query_skill_mapped("force")!="kurong-changong")
         return notify_fail("�㼤�����ڹ�����Ǭ��һ�����������������д��һ����ָ��\n");

      if((int)me->query("max_neili") < 5000 )
         return notify_fail("�������̫�����޷�д��ǿ��������һ����ָ! \n");
      
      if((int)me->query("neili") < 800 )
         return notify_fail("�������̫���ˣ�д����һ����ָ�޸���֮����\n");       

      if((int)me->query("jingli") < 500 )
         return notify_fail("��ľ���̫���ˣ�д����һ����ָ�޸���֮����\n");       
         
      if(me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("�������޷�д����һ����ָ����\n");
	  if (me->query_temp("ygbf/yiyang"))
	     return notify_fail("����������ʩչ��һ����ָ����\n");


      i = me->query_skill("yingou-bifa",1)+me->query_skill("qiantian-yiyang",1)+me->query_skill("yiyang-zhi",1)+me->query_skill("literate",1);
      i=i/4;                                                                                 
      me->set_temp("ygbf/yiyang",i);
      msg = HBYEL+HIR"$N����Ǭ��һ��������һ��ָ�����뵽�����ʷ�����ʽ�У������������죬����������\n" NOR;
      me->add("neili", - random(500));
      me->add("jingli", -100);
    
      message_vision(msg, me, target);
	  me->add_temp("apply/brush",i/3);
	  me->add_temp("apply/attack",i/3);
	  me->add_temp("apply/damage",i/6);
      //me->start_perform(6,"��һ����ָ��");
      call_out("effect_check",2,me,target,i);
	  return 1;
}

void effect_check (object me, object target, int count)
{
        int i;
		if (!me) return;
	
	    i=me->query_temp("ygbf/yiyang");
		
		if (objectp(me) && me->query_temp("ygbf/yiyang"))
		{
           if (count-- > 0 && me->is_fighting(target))
		   {
               call_out("effect_check", 2, me, target, count);
               return;
           }
		}         
            
		tell_object(me,HIY"����һ�������������һ�����������ͷš�\n"NOR);
        me->add_temp("apply/brush",-i/3);
		me->add_temp("apply/attack",-i/3);
		me->add_temp("apply/damage",-i/6);
        me->delete_temp("ygbf/yiyang");
        
		return;   
}
int help(object me)
{
	write(HIR"\n�����ʷ�֮��һ����ָ��������"NOR"\n");
	write(@HELP
	�����ʷ�����һ�ƴ�ʦ������������Ķ����似������״Ԫ����
	�����Ըߣ����԰�ʦһ�ƴ�ʦ���似ͻ���ͽ�����Ϊ�Ĵ����
	���书����ߡ����Ź�������֮�����ڽ�һ��ָ���鷨�ں���һ
	����ʽ�м����ŵ�Ѩ�����˷���ʤ����
	�����ڴ�ʤ�������һս������һ����ָ����������ͨë�ʶ�ս
	��������һ��ָ����ʽʩչ�����鷨���������ɴ��������¡�
	
	ָ�perform brush.yiyangshu

Ҫ��	
	������� 5000 ���ϣ�		
	��ǰ���� 800 ���ϣ�
	��ǰ���� 500  ���ϣ�
	�����ʷ� 400 ���ϣ�
	��Ч���� 50 ���ϣ�
	����д�� 300 ���ϣ�
	�����ʷ�Ϊ�����ʷ�
	�����м�Ϊ�����ʷ���
	�����ڹ�Ǭ��һ������
	�ֱֳ���������
	
HELP
	);
	return 1;
}

