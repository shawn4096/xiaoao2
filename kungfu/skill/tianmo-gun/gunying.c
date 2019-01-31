//gunying.c
//��Ӱ��ɽ�����ط��أ��������ͽ���
#include <ansi.h>
#include <combat.h>
//inherit SKILL;
//#include <combat_msg.h>
inherit F_SSERVER;
int remove_effect(object me,int num);

int perform(object me, object target)
{
   int lvl;
   object weapon;
   lvl = (int)me->query_skill("tianmo-gun", 1);
   
   if( !target ) target = offensive_target(me);
   if( !objectp(target)
      || !me->is_fighting(target)
      || !living(target)
      || environment(target)!=environment(me))
      return notify_fail("����Ӱ��ɽ��ֻ����ս���жԶ���ʹ�á�\n");

   if( (int)me->query_skill("tianmo-gun", 1) < 450 )
                return notify_fail("�����ħ����������죬ʹ��������Ӱ��ɽ��������\n");

   if (me->query_skill_mapped("force") != "tianmo-gong" 
	   && me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("����ʹ�õ������ڹ����ԡ�\n");  

   if(me->query_skill("xixing-dafa", 1)<450)
      if(me->query_skill("tianmo-gong", 1) < 450)
         return notify_fail("�������ڵ��ڹ���Ϊ��ʹ��������Ӱ��ɽ����\n");  

   if(  me->query_skill_mapped("club") != "tianmo-gun")
                return notify_fail("�������޷�ʹ�á���Ӱ��ɽ����\n");
   

   if (!objectp(weapon = me->query_temp("weapon")) 
          || weapon->query("skill_type") != "club"
          || me->query_skill_mapped("club") != "tianmo-gun"
          || me->query_skill_mapped("parry") != "tianmo-gun")
                 return notify_fail("�������޹������ʹ�á���Ӱ��ɽ����\n");

   if( (int)me->query("max_neili") < 14000)
                return notify_fail("�������̫����ʹ��������Ӱ��ɽ����\n");

   if( (int)me->query("neili") < 1500 )
                return notify_fail("����������̫����ʹ��������Ӱ��ɽ����\n");

   if( (int)me->query("jingli") < 1500 )
           return notify_fail("������̫���ˣ�ʹ��������Ӱ��ɽ����\n");
   if( me->query_temp("tmgf/gunying"))
           return notify_fail("����������ʩչ����Ӱ��ɽ����\n");

	message_vision(RED"\n$N��ִ"+weapon->query("name")+RED"����ת�����γ�һƬ��Ӱ����ħ��������������\n"NOR,me,target);
	
	message_vision(HIY"\n$nֻ��$N��Ӱ��ɽ��һ���Ӵ��ѹ��ӭ�������\n"NOR,me,target);
    if (me->query_skill_mapped("force")=="xixing-dafa")
    {
		lvl=lvl+me->query_skill("xixing-dafa", 1)/3;
    }else if (me->query_skill_mapped("force")=="tianmo-gong")
    {
		lvl=lvl+me->query_skill("tianmo-gong", 1)/6;
    }
	if (me->query("quest/hmy/tmgf/jueji")=="pass")
	{
		lvl=lvl+me->query_skill("club",1)/4;
		message_vision(HIR"$N�Ѿ�����ħ���ڻ��ͨ���Ѵﵽ��豹���֮��������һ����������Ī��������\n"NOR,me);
	}
	me->set_temp("tmgf/gunying",lvl);

	me->add_temp("apply/attack",lvl/4);
	me->add_temp("apply/damage",lvl/5);
	me->add_temp("apply/club",lvl/5);
	me->add_temp("apply/defense",lvl/4);
	me->add_temp("apply/parry",lvl/3);
	
        me->add("jingli", -100);
        me->add("neili", -500);
       
       // me->start_busy(1+random(2));
        
        //me->start_perform(2+ random(2),"����Ӱ��ɽ��");
		call_out("remove_effect",1,me,(int)lvl/10);

        return 1;
}

int remove_effect(object me,int num)
{
	int lvl;
	
	if (!me) return 0;
	lvl=me->query_temp("tmgf/gunying");
	if (num<0
		||!me->is_fighting()
		)
	{
		me->add_temp("apply/attack",-lvl/4);
		me->add_temp("apply/damage",-lvl/5);
		me->add_temp("apply/club",-lvl/5);
		me->add_temp("apply/defense",-lvl/4);
		me->add_temp("apply/parry",-lvl/3);
		me->delete_temp("tmgf/gunying");
		message_vision(RED"$N����һ��������������ͣ�����������һ�ݣ�Ԩͣ���ѣ�\n"NOR,me);
		return 1;
	}
	num=num-2;
	call_out("remove_effect",1,me,num);
	return 1;
}

string perform_name(){ return RED"��Ӱ��ɽ"NOR; }

int help(object me)
{
        write(HIR"\n��ħ��֮����Ӱ��ɽ����"NOR"\n\n");
        write(@HELP
	��ħ�������������ʮ����ħ֮����Գ��ħ���ų˷��
	���׺���ħ���ų����ֵܶ����������������𽭺�����
	��ʮ����Χ����ɽ�����䲻����ʹ�����ž����Ӵ�ʧ
	��������������˵�ڻ�ɽ��ɽʯ�����ֹ���ħ����ʽ��
	��������д�������Լ�̽����
	��Ӱ��ɽ���������ƿ�ľ������������γ�һƬ��Ӱ
	�������ӹ�����������ͬʱ����߹����ķ���������
	�����ڲ����������ֳ�һ������׾���ɣ�����ʤ��
	ע�⣺�⿪��ɽʯ������󣬴������������ͷš�

	ָ�perform club.gunying

Ҫ��
	����������� 14000 ���ϣ�
	��ǰ�������� 1500  ���ϣ�
	��ǰ�������� 1500  ���ϣ�
	��ħ�����ȼ� 450 ���ϣ�
	�����ڹ��ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	�����м�Ϊ��ħ����
	�����ڹ�Ϊ��ħ�������Ǵ�

HELP
        );
        return 1;
}
