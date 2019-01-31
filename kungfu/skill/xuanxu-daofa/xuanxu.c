// xuanxu.c ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
void check_fight(object me);
int perform(object me, object target)
{
      string msg;             
      object weapon = me->query_temp("weapon");                      
      int j = (int)me->query_skill("xuanxu-daofa", 1);
      
	  if( !target ) target = offensive_target(me);
     
      if( me->is_busy() )
        return notify_fail("����æ���ء�\n");
      if( !target || !me->is_fighting(target) )
        return notify_fail("�����ֻ����ս���жԶ���ʹ�á�\n");
             
      if( (int)me->query_skill("xuanxu-daofa", 1) < 200 )
        return notify_fail("����������������죬����ʹ�������\n");
      
      if( (int)me->query_skill("force", 1) < 200 )
        return notify_fail("��Ļ����ڹ��ȼ�����������ʹ���������\n");

      if( (int)me->query_skill("blade", 1) < 200 )
        return notify_fail("��Ļ��������ȼ�����������ʹ���������\n");  
      
      if( (int)me->query_skill("taoism", 1) < 150 )
        return notify_fail("��Ե����ķ����򲻹�����޷�ʹ�ó��������\n");
      
      if( (int)me->query("max_neili") < 2000 )
        return notify_fail("�������̫��������ʹ���������\n");
      
      if( (int)me->query("neili") < 500 )
        return notify_fail("�������̫���ˣ��޷�ʹ�ó��������\n");   

      if (!weapon || weapon->query("skill_type") != "blade"
		  || me->query_skill_mapped("parry") != "xuanxu-daofa"
          || me->query_skill_mapped("blade") != "xuanxu-daofa")
        return notify_fail("��û�м������鵶����\n");

                                                                                 
      if( me->query_temp("xxd/xuanxu")   )
          return notify_fail("������ʹ���������\n");

      msg = HIY"$Nʹ����������еľ���������������ɻ���ֻ�ʵ�$n��ǰһƬӰ����\n"NOR;
      me->add("neili", -200);
	  me->add("jingli", -100);

      me->set_temp("xxd/xuanxu", j);
	  me->add_temp("apply/attack",j/5);
	  me->add_temp("apply/damage",j/6);
	  me->add_temp("apply/blade",j/5);

	  call_out("check_fight",1,me);

    //  me->start_call_out( (: call_other, __FILE__, "remove_effect", me, j :), j);
   //   me->start_call_out( (: call_other, __FILE__, "check_fight", me, target :), 1);
      message_vision(msg, me, target);   

      return 1;
}

void check_fight(object me)
{
    object weapon;  
	int j;
	if (!me||!me->query_temp("xxd/xuanxu")) return;
	weapon=me->query_temp("weapon");
	j=me->query_temp("xxd/xuanxu");

    if(me->query_skill_mapped("blade") != "xuanxu-daofa"
       || !weapon
       || weapon->query("skill_type") != "blade"
       || !me->is_fighting() 
	   || me->query_skill_mapped("parry") != "xuanxu-daofa")
	{
	
		  me->add_temp("apply/attack",-j/5);
		  me->add_temp("apply/damage",-j/6);
		  me->add_temp("apply/blade",-j/5);
		  me->delete_temp("xxd/xuanxu");
		  message_vision(HIC"$N��Ϣ�೤�����������е������³������������������!\n"NOR,me);
		  return;
	}
	call_out("check_fight",1,me);

}
string perform_name(){ return HIC"�����"NOR; }
int help(object me)
{
         write(HIB"\n�������֮"+HIY"���������"NOR"\n");
        write(@HELP
	������������䵱���ŵ��ӵ��似���õ������ǿ�ɽ��ʦ
	���������ڴ�������ʱ��ʹ�õ��书���ܹ�ʮ���У�����
	�����ƾ����书׷ɱ�������ڵڰ�����������޵���ն
	ɱ���Դ�����������
	������ǽ��䵱�����ķ����뵽�����У�������ϣ�����
	���ã�ʵս���������䲻�⡣
	
	ָ�perform blade.xuanxu

Ҫ��
	�����ڹ���200
	���������200
	����������200
	��ѧ�ķ���150
	���������2000
	��ǰ������500
	�����������鵶��
	�����м����鵶��
	�ڹ�����
	����ɽ���ơ�
	�ֳֵ�������
HELP
        );
        return 1;
}
