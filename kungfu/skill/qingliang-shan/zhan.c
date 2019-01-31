// zhan.c չ�־�
// by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
void remove_effect(object me,int count);

int perform(object me, object target)
{                                  
      int skill,lvl;
      object weapon;
      
	  if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target))
                return notify_fail("��չ�־���ֻ����ս���жԶ���ʹ�á�\n");
//�ʷ��򵶷�
      if (!objectp(weapon = me->query_temp("weapon")) 
		|| (weapon->query("skill_type") != "brush"&&weapon->query("skill_type") != "blade"))
		  return notify_fail("����������ԣ������޷�ʹ�á�չ�־�����\n");
      
	  if (me->query_skill_mapped("blade") != "qingliang-shan"
			||me->query_skill_mapped("parry") != "qingliang-shan"
			|| me->query_skill_mapped("brush") != "qingliang-shan")
                return notify_fail("�㼤�����ԣ������޷�ʹ�á����־�����\n");

      if( (int)me->query_skill("qingliang-shan",1) < 350 )
                return notify_fail("��������Ȳ�����죬����ʹ�á�չ�־�����\n");
      
      if( (int)me->query_skill("force",1) < 350 )
                return notify_fail("��Ļ����ڹ��ȼ�����������ʹ�á�չ�־�����\n");  
      if( (int)me->query_skill("blade",1) < 350 )
                return notify_fail("��Ļ��������ȼ�����������ʹ�á�չ�־�����\n");  
      if( (int)me->query_skill("brush",1) < 350 )
                return notify_fail("��Ļ����ʷ��ȼ�����������ʹ�á�չ�־�����\n");  
      
      
      if( (int)me->query_dex() < 60 )
                return notify_fail("���������ǿ������ʹ�á�չ�־�����\n");
      if( (int)me->query("neili") < 1500 )
		      return notify_fail("�������̫���ˣ��޷�ʹ�ó���չ�־�����\n");
      if( (int)me->query("max_neili") < 5000 )
                return notify_fail("�������̫��������ʹ�á�չ�־�����\n");
      if( me->query_temp("qls/zhan"))
                return notify_fail("������ʩչ��չ�־�����\n");
           
      skill = (int)me->query_skill("qingliang-shan", 1);
      
	  lvl = (int)me->query_skill("qingliang-shan", 1)+(int)me->query_skill("blade", 1)/2+(int)me->query_skill("brush", 1)/2;
        
	  lvl=lvl/4;   
      	
      message_vision(HIW"$N����"NOR+weapon->query("name")+HIW"��ˢ����һ��չ����ʩչ��"+HIW"��չ�־���"+HIW"���γ�һƬ��Ӱ�����Լ�����ס��ˮй��ͨ��\n" NOR, me, target);

	  me->add_temp("apply/parry", lvl/3);
	  me->add_temp("apply/armor", lvl/5);
      me->add_temp("apply/dodge", lvl/5);
        
	 
     me->set_temp("qls/zhan", lvl);
     //call_out("remove_effect",1,me,);
	 remove_effect(me,(int)skill/50);
     return 1;
}

void remove_effect(object me,int count)
{
	int lvl;
	object weapon;
	if (!me||!me->query_temp("qls/zhan")) return 0;
	lvl=me->query_temp("qls/zhan");
	weapon=me->query_temp("weapon");

	if (!me->is_fighting()
		||me->query_skill_mapped("brush")!="qingliang-shan"
		||me->query_skill_mapped("blade")!="qingliang-shan"
		||me->query_skill_mapped("parry")!="qingliang-shan"
		||!objectp(weapon)
		||count<0)
	{
		me->add_temp("apply/parry", -lvl/3);
		me->add_temp("apply/armor", -lvl/5);
		me->add_temp("apply/dodge", -lvl/5);
		me->delete_temp("qls/zhan");
		if (weapon)
			tell_object(me, HIW"\n������һ�ң�������"+weapon->query("name")+HIW"һ�գ���ȥ�ˡ�չ�־�����\n"NOR); 
		else tell_object(me, HIW"\n������һ�ң���ȥ�ˡ�չ�־�����\n"NOR); 
		return;
	}
	call_out("remove_effect",1,me,count-1);

}

string perform_name(){ return YEL"չ�־�"NOR; }

int help(object me)
{
	write(HIC"\n������֮��չ�־�����"NOR"\n");
	write(@HELP
	�������������������ʿ���ž���������Ϊ�����ȿ���
	�����̹����ֿ��Ի��������������׻�˵һ��̣�һ��
	�գ���������������ΪϬ�������ڲ���������Ů�����
	��������Ҳ�����ɵ���Ҫ��ҹ���
	չ�־��ǽ���������������չ�����γ�һƬ��Ӱ������
	�ʷ�չ�����γ�һƬ��Ӱ����ס����Ҫ�������ڰ�����
	�����з�����Ч��
	
	ע�⣺set ������ �� �е�Ѩ��������Ч

	ָ�perform brush.zhan

Ҫ��
	����������� 5000 ���ϣ�
	��ǰ�������� 1500 ���ϣ�
	�����ȵĵȼ� 350 ���ϣ�
	�����ڹ��ȼ� 350 ���ϣ�
	�����ʷ��ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	���������� 60  ���ϣ�
	��������Ϊ������
	�����ʷ�Ϊ������
	�����м�Ϊ�����ȣ���
	�ڹ����ޣ�
	�ֳֵ����������
HELP
	);
	return 1;
}
