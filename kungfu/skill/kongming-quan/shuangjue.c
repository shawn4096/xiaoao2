// ����˫��


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
   int lvl;
  lvl = (int)me->query_skill("kongming-quan", 1)+(int)me->query_skill("xiantian-gong", 1)/2;
  
  if( !target ) target = offensive_target(me);
  if( !objectp(target)
	 || !me->is_fighting(target)
	 || !living(target)
	 || environment(target)!=environment(me))
		return notify_fail("������˫����ֻ����ս���жԶ���ʹ�á�\n");

  if( objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ�á�����˫������\n");

   if( (int)me->query_skill("kongming-quan", 1) < 500 )
		return notify_fail("��Ŀ���ȭ��������죬ʹ����������˫����������\n");

   if(me->query_skill_mapped("force")!="xiantian-gong")
        return notify_fail("����˫����Ҫ���칦������ʹ����������˫����������\n");
   if( (int)me->query_skill("parry", 1) < 500 )
           return notify_fail("��Ļ������ܵȼ���������ʹ����������˫����������\n");

   if( (int)me->query_skill("dodge",1) < 500 )
		return notify_fail("����Ṧ�ȼ�����������ʹ�á�����˫������\n");
		
   if( (int)me->query_skill("xiantian-gong",1) < 500 )
		return notify_fail("������칦�ȼ�����������ʹ�á�����˫������\n");
   if( !me->query("quest/jiebai/pass")||!me->query("quest/hubo/pass"))
		return notify_fail("�㲢δ����ܲ�ͨ���ڣ�����ʹ�á�����˫������\n");

   if( me->query_skill_prepared("cuff") != "kongming-quan"
	 || me->query_skill_mapped("cuff") != "kongming-quan")
		return notify_fail("�������޷�ʹ�á�����˫������\n");

   if( me->query_skill_mapped("parry") != "kongming-quan")
		return notify_fail("����Ҫ�����м�Ϊ����ȭ������ʹ�á�����˫������\n");
    if(me->query_temp("kmg/shuangjue"))
	    return notify_fail("������ʹ��������С�\n");

   if( (int)me->query("max_neili") < 15000)
		return notify_fail("����������̫����ʹ����������˫������\n");

   if( (int)me->query("neili") < 2000 )
		return notify_fail("����������̫����ʹ����������˫������\n");

   if( (int)me->query("jingli") < 1500 )
           return notify_fail("������̫���ˣ�ʹ����������˫������\n");


    message_vision(HIW"\n$N����������Ĭ��ھ������������ɡ���ͨ���Ρ�������Ū��ͯӹ���档��ʹ������ȭ������"NOR+HBCYN+HIW"����˫��"NOR+HIW"����\n"NOR,me);
	message_vision(HBYEL+HIW"\n\nһ�����ᾢ��������֮�������һ���ศ��ɣ�����$n��\n"NOR,me,target);
  

	me->add_temp("apply/attack", lvl/2);
	me->add_temp("apply/damage", lvl/5);
	me->add_temp("apply/cuff", lvl/3);
	me->add_temp("apply/strength", lvl/10);
	
	if (me->query_temp("xtg/wuqi")) {
		me->set_temp("xtg/wuqi1",lvl);
		me->add_temp("apply/damage", lvl/5);
    }
	me->set_temp("kmq/shuangjue",1);
    
	COMBAT_D->do_attack(me, target, 0, 3);

	if ( me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, 3);

	if ( me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, 3);


	if ( me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, 3);
 
	if ( me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, 3);
	if (wizardp(me))
	{
		write("lvl="+lvl);
	}
	me->add_temp("apply/attack",-(lvl/2));
	me->add_temp("apply/damage", -(lvl/5));
	me->add_temp("apply/cuff", -(lvl/3));
	me->add_temp("apply/strength",-(lvl/10));
   if (me->query_temp("xtg/wuqi1"))	me->add_temp("apply/damage", -(lvl/5));
   me->add("jingli", -100);
   me->add("neili", -200);
   me->delete_temp("xtg/wuqi1");
   me->start_busy(1+random(2));
   me->delete_temp("kmq/shuangjue");
   me->start_perform(5,"������˫����");

   return 1;
}


string perform_name(){ return WHT"����˫��"NOR; }

int help(object me)
{
	write(HIC"\n����ȭ֮������˫������"NOR"\n\n");
	write(@HELP
	����ȭ�����������ȭ�������ܲ�ͨ�ӡ����¾����л�
	�����ģ������¾��������Ե�������ǿ����ľǿ���ۡ�
	��ǿ���£��������ϡ������ƣ�������Ī������ˮ������
	��ǿ��Ī֮��ʤ����������֮����֮ʤǿ����֮ʤ�գ�
	����Ī��֪��Ī���С��ǽ���ʮ����ȴ����ѧ��������
	���ȭ��������ȭ֮���־��������ǿգ�ʵ�������黯
	ʵ�ĸ����ھ��������ޱȡ������Բ�ǿ�����������ȿ�
	�����ʵ����
	������˫�����ǽ�����ȭ�ڻ��ͨ�����������ɾ���
	������һ�𣬽������ͯ������˫�ֻ���������������
	�󣬴���ֻ�н����칦���������º󷽿�ʩչ����ȫ��
	���Ӳ�����
	
	ָ��; perform cuff.shuangjue

Ҫ��
	����������� 15000 ���ϣ�
	��ǰ�������� 2000  ���ϣ�
	��ǰ�������� 1500  ���ϣ�
	����ȭ���ȼ� 500 ���ϣ�
	�����Ṧ�ȼ� 500 ���ϣ�
	���칦���ȼ� 500 ���ϣ�
	�����мܵȼ� 500 ���ϣ�
	����ȭ���м�Ϊ����ȭ��
	��ȭ��Ϊ����ȭ�ҿ��֡�
			

HELP
	);
	return 1;
}