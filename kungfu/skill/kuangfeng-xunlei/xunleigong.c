// Ѹ�׺ǹ�
//xunleigong.c 
//�ǳ����似�����ͶԷ�������ʧ��

#include <ansi.h>
inherit F_SSERVER;
    
    
   int perform(object me,object target)
 {
       object weapon;
		int i;
      
       if( !target ) target = offensive_target(me);
       
       if( !objectp (target) || !me->is_fighting(target) || !living(target)
          || environment(target)!=environment(me))
                   return notify_fail("Ѹ�׺ǹ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
  
      
       if( (int)me->query_skill("kuangfeng-xunlei", 1) < 250 ) 
                   return notify_fail("��Ŀ��Ѹ�׻�δ���ɣ�����ʹ��Ѹ�׺ǹ���\n");
		if( (int)me->query_skill("mizong-fofa", 1) < 200 ) 
                   return notify_fail("������ڷ𷨻�δ���ɣ�����ʹ��Ѹ�׺ǹ���\n");
                 
       if((int)me->query_skill("brush", 1) < 250 )
                   return notify_fail("��Ļ����ʷ�������죬������ʹ��Ѹ�׺ǹ���\n");
       if((int)me->query_skill("hand", 1) < 250 )
                   return notify_fail("��Ļ����ַ�������죬������ʹ��Ѹ�׺ǹ���\n"); 
	   if((int)me->query_skill("force", 1) < 250 )
                   return notify_fail("��Ļ����ڹ�������죬������ʹ��Ѹ�׺ǹ���\n");
	   if((int)me->query_skill("dodge", 1) < 250 )
                   return notify_fail("��Ļ����ڹ�������죬������ʹ��Ѹ�׺ǹ���\n");
	   if((int)me->query_dex(1) < 50 )
                   return notify_fail("��ĺ���������50��������ʹ��Ѹ�׺ǹ���\n");
//�����������ӣ����ֿ���
	   if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "brush"
           || me->query_skill_mapped("brush") != "kuangfeng-xunlei"
           || me->query_skill_mapped("parry") != "kuangfeng-xunlei")
                   return notify_fail("�����ڼ�������ʹ����Ѹ�׺ǹ�ô��\n");
                   
       if((int)me->query("max_neili") < 6000 )
                  return notify_fail("������������Ϊ����������ʹ��Ѹ�׺ǹ���\n");
       if((int)me->query("neili") < 2000 )
                 return notify_fail("�������������㣬����ʹ��Ѹ�׺ǹ���\n");
       if((int)me->query("jingli") < 1000 )
                 return notify_fail("�����ھ������㣬����ʹ��Ѹ�׺ǹ���\n");
       if (me->query_temp("kfxl/xlg"))
				return notify_fail("������ʩչʹ��Ѹ�׺ǹ���\n");
	   if (target->query_temp("kfxl/xlg"))
		        return notify_fail("�Է����������Ѹ�׺ǹ���\n");
		message_vision(WHT"\n$N����"+weapon->query("name")+WHT"��$n�������£������������������ڼ�����ͬʱ��$n���ϴ����ǳ⣬����Ѹ��!\n"NOR,me,target);
    
		i = (int)me->query_skill("kuangfeng-xunlei",1)/4;

		
		if (!target->query_temp("kfxl/xlg")
			&&(random(me->query_skill("force",1))>target->query_skill("force",1)/2)||random(me->query_int())>target->query_int()/2)
		{
			message_vision(HIM"\n$N��$n����һ��������������ǳ⣬$nһʱ���飬��ʱΪ��Ѹ�׺ǹ�����ס���ַ�һ��!\n"NOR,me,target);
			target->add_busy(2);
			target->add_temp("apply/attack",-i/5);
			target->add_temp("apply/parry",-i/5);
			target->add_temp("apply/dodge",-i/5);
			target->set_temp("kfxl/xlg",i);
			call_out("remove_effect",1,target);
		}
        
		me->set_temp("kfxl/xlg",1);      
		me->add("neili", -350);
		me->add("jingli", -250);
 
		call_out("me_effect",1,me);
		return 1;
 }

 int me_effect(object me)
 {
	if (!me) return 0;
	me->delete_temp("kfxl/xlg");
	message_vision(HIM"\n$Nƽ�ľ�����������Ѹ�׺ǹ�ֹͣ��ʹ!\n"NOR,me);

	return 1;
} 
 int remove_effect(object target)
 {
	int i;
	if (!target||!target->query_temp("kfxl/xlg")) return 0;
	i=target->query_temp("kfxl/xlg");
	target->add_temp("apply/attack",i/5);
	target->add_temp("apply/parry",i/5);
	target->add_temp("apply/dodge",i/5);
	target->delete_temp("kfxl/xlg");
	message_vision(HIM"\n$n����˲��ͨ���Ѹ�׹�������������������!\n"NOR,target);

	return 1;

 }
string perform_name() {return HIR"Ѹ�׺ǹ�"NOR;}

int help(object me)
{
	write(WHT"\n���Ѹ�ס�"HIR"Ѹ�׺ǹ�"WHT"����"NOR"\n");
	write(@HELP
    ���Ѹ���ǻ�������ʽ������������ͬ���ַ����ʹ����
	�ڴ�ʤ�غ���ԭȺ��һս���ܷ���ָ��ʩչ�����Ѹ�׺�
	�����Ǿ��ޡ����к����ԡ������ڹ��ȼ��ҹ�
	ע�⣺�˹����������ʩչ����Ѹ�׺ǹ���Ϻ�Ч�����ѡ�

	ָ�perform brush.kuangfeng

Ҫ��
	�����ڹ��ȼ� 350 ����
	�����ʷ��ȼ� 350 ��
	���Ѹ�׵ȼ� 350 ��
	�����Ṧ�ȼ� 350 ����
	��ǰ����Ҫ�� 2000 ���ϣ�
	�������Ҫ�� 6000 ���ϣ�
	��ǰ����Ҫ�� 1000  ���ϡ�
	�����ַ�Ϊ���Ѹ�׺ǹ���
	�����ʷ�Ϊ���Ѹ�׺ǹ���
	�ֱֳ���������
HELP
	);
	return 1;
}
