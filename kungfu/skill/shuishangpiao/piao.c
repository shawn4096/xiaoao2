//piao.c Ʈ
//BY BOBO@SJ
// modified by darken@SJ

#include <combat.h>
#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HIC"ˮ��Ʈ"NOR; }

void remove_effect(object me, int improve);
int help(object me);
int perform(object me)
{
      string msg;                                   
      int improve;
      
      if( (int)me->query_skill("shuishangpiao",1) < 140 )
           return notify_fail("���ˮ��Ʈ������죬����ʹ�á�Ʈ����\n");

      if( (int)me->query_skill("guiyuan-tunafa",1) < 140 )
           return notify_fail("��Ĺ�Ԫ���ɷ��ȼ�����������ʹ�á�Ʈ����\n");  

      if (me->query_skill("force",1)<140)
           return notify_fail("��Ļ����ڹ�������ʹ�á�Ʈ����\n");

      if( (int)me->query_dex() < 28 )
           return notify_fail("�����̫�ͣ�����ʹ�á�Ʈ����\n");
      
      if( (int)me->query_skill("dodge", 1) < 120 )
           return notify_fail("��Ļ����Ṧ̫����屿׾������ʹ�á�Ʈ����\n");
      
      if( (int)me->query("max_neili") < 1500 )
           return notify_fail("�������̫���ˣ��޷�ʹ�ó���Ʈ����\n");   
      if( (int)me->query("neili") < 500 )
           return notify_fail("�������̫���ˣ��޷�ʹ�ó���Ʈ����\n");   
      if (me->query_skill_mapped("dodge") != "shuishangpiao")
           return notify_fail("�����ڼ������Ṧ�޷��á�Ʈ��������\n");

      if( me->query_temp("piao"))
           return notify_fail("������ʹ��ˮ��Ʈ�����������Ʈ����\n");
       
      msg = HIC"$NͻȻ����һ������˫Ŀ����һ����һ̧�������ѵ�ˮ�㣬��������Ʈ������" +
               "������Ʈ�˹�����\n" NOR;
      
      message_vision(msg, me); 
      improve = (int)me->query_skill("shuishangpiao",1);
      me->add_temp("apply/dexerity", improve/10);
      me->set_temp("piao", 1); 
	  if (me->query("quest/tiezhang/piao"))
	  {
	   me->add_temp("apply/attack",improve/10);
	   me->add_temp("apply/armor",improve/8);
	   me->add_temp("apply/defense",improve/5);
	   }
      me->add("neili", -(100 + (int)me->query_skill("shuishangpiao",1)/10));           
      me->start_call_out((: call_other, __FILE__, "remove_effect", me, improve :), me->query_skill("shuishangpiao", 1)/5);
      return 1;
}

void remove_effect(object me, int improve)
{
      if(!me) return;
      me->add_temp("apply/dexerity", - improve/10);
	  if (me->query("quest/tiezhang/piao"))
	  {
	   me->add_temp("apply/attack",-improve/10);
	   me->add_temp("apply/armor",-improve/8);
	   me->add_temp("apply/defense",-improve/5);
	   }
       me->delete_temp("piao");
      tell_object(me, HIC"���������һ������ɢȥ�˵������۵�������\n"NOR);
}

int help(object me)
{
        write(HIR"\nˮ��Ư֮��Ư����"NOR"\n\n");
        write(@HELP 
		����ˮ��Ư��ǧ���������Ʒ���ˮ��Ư���������������뵱����ǧ����ܲ�ͨ
		�˴�׷�𣬱�������ܲ�ͨʼ��δ��׷������ǧ���ɴ˿ɼ��˾�����������
		ѧҪ���ѵ��ǣ����ܴ���ǧ������Ķ��⿪ˮ��Ư�����������������ܷ�����
        Ҫ��  ��ǰ���� 500 ���ϣ�
                ������� 1500 ���ϣ�
                ��ǰ���� 500 ���ϣ�
                �����Ṧ�ȼ� 140 ���ϣ�
                �����ڹ��ȼ� 140 ���ϣ�
                �����ṦΪˮ��Ư��                              
HELP
        );
        return 1;
}