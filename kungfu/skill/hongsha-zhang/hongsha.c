// hongsha.c
// by sohu@xojh 2015

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HBRED+HIW"��ɰѪ����"NOR;}

int perform(object me, object target)
{
  string msg, dodge_skill;
  int damage, p, jiali, skill, neili, neili2;
  

  if( !target ) target = offensive_target(me);

  if( !target || !target->is_character() ||  !me->is_fighting(target) 
      || environment(target)!=environment(me) || !living(target))
         return notify_fail("����ɰѪ������ֻ����ս�����á�\n");

  if( me->query_temp("weapon")) 
         return notify_fail("���������������ʹ�ó�����ɰѪ��������\n");
         
  if( (skill = (int)me->query_skill("hongsha-zhang", 1)) < 350 )
         return notify_fail("��ĺ�ɰ�Ʋ�����죬����ʹ����ɰѪ��������\n");
  if (!me->query("quest/xd/hongsha/pass"))
         return notify_fail("��ĺ�ɰ����δ����ͨ������ʹ����ɰѪ��������\n");

  if( (int)me->query_skill("xuedao-jing", 1) < 350 )
         return notify_fail("����ڹ���򲻹�������ʹ�á���ɰѪ��������\n");

  if( me->query_skill_mapped("force") != "xuedao-jing")
         return notify_fail("�����õ��ڹ��͡���ɰѪ�������໥��ͻ��\n");

  if (me->query_skill_prepared("strike") != "hongsha-zhang" ||
      me->query_skill_mapped("strike") != "hongsha-zhang")
         return notify_fail("������Ƚ���ɰ���������Ʒ�֮�в��С�\n");

  if( (jiali = (int)me->query("jiali")) < 50 )
         return notify_fail("�����ϲ�����������ôʹ�ó�����ɰѪ����������\n");

  if( (neili = (int)me->query("neili")) < 500 )
         return notify_fail("����������㣬����ʩչ����ɰѪ��������\n");
  if( (int)me->query("max_neili") < 1500 )
         return notify_fail("����������㣬����ʩչ����ɰѪ��������\n");
  if( (int)me->query("jingli") < 300 )
         return notify_fail("��ľ������㣬����ʩչ����ɰѪ��������\n");
  if (me->query_temp("hsz/hongsha"))
         return notify_fail("������ʩչ����ɰѪ��������\n");
  me->receive_damage("neili", random(100) );
  me->receive_damage("jingli", 50);
  
  message_vision(HIR "\n$N��Ȼ��������˫�ƣ��ͺ�һ��������һ��Ѫ������������˫�ƶ�ʱ���"HBRED+HIW"Ѫ��"NOR+HIR"һƬ��\n"NOR,me,target);
  
  me->add_temp("apply/attack",skill/5);
  me->add_temp("apply/damage",skill/8);
  me->add_temp("apply/strike",skill/5);
  
  me->set_temp("hsz/hongsha",skill);
  call_out("remove_effect",1,me,skill/30);
  me->add("jingli",-100);
  me->add("neili",-150-random(100));

  return 1;
}

int remove_effect(object me,int count)
{
	int skill;
	if (!me) return 0;
	skill=me->query_skill("hongsha-zhang",1);
	if (!me->is_fighting()
		||me->query_skill_mapped("strike")!="hongsha-zhang"
		||me->query_skill_prepared("strike")!="hongsha-zhang"
		||me->query_temp("weapon")
		||count<0)
	{
		me->add_temp("apply/attack",-skill/5);
		me->add_temp("apply/damage",-skill/8);
		me->add_temp("apply/strike",-skill/5);
		me->delete_temp("hsz/hongsha");
		message_vision(HIR"$N������˫�۵ĺ�ɰѪ����ֹͣ����ɫ��ʱɷ��һƬ��\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me,count--);
	

}
int help(object me)
{
	write(RED"\n��ɰ��֮����ɰѪ��������"NOR"\n\n");
        write(@HELP
	��ɰ������Ѫ���ŵ��������似����ɰ����ȡ��ѩɽ
	�綾֮���������Ѫ�������ö���֮��ѪҺ�д���
	���ԡ�ͬʱ��ΪѪҺ���̺���Щ����֮�������ɰ��
	����Ѫ���ŵ��ķ�ȴ������֮�⡣
	��ɰѪ��������ƾ��ƽʱ�����ĺ�ɰ��Ѫ���̲��ڵ�
	�����ʩչʱ�����ڱۣ��Ʒ���������������ܻ�
	�á�
	
	ָ�perform strike.hongsha

Ҫ��
	�������  1500 ���ϣ�
	��ǰ����  500  ���ϣ�
	Ѫ����    350  �����ϣ�
	��ɰ�Ʒ�  350  �����ϣ�
	�����Ʒ�Ϊ��ɰ�ƣ�
	�����м�Ϊ��ɰ�ƣ�
	�����ұ���ɰ�ƣ�
HELP
        );
        return 1;
}