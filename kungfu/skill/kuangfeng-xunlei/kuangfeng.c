// ���
//kuangfeng.c 
//�����ʽ

#include <ansi.h>
inherit F_SSERVER;
    
      
int perform(object me,object target)
{
       object weapon;
		int i,j;
      
       if( !target ) target = offensive_target(me);
       
       if( !objectp (target) || !me->is_fighting(target) || !living(target)
          || environment(target)!=environment(me))
                   return notify_fail("��缲��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
  
    
       if( (int)me->query_skill("kuangfeng-xunlei", 1) < 250 ) 
                   return notify_fail("��Ŀ��Ѹ�׻�δ���ɣ�����ʹ�ÿ�缲����\n");

                 
       if((int)me->query_skill("brush", 1) < 250 )
                   return notify_fail("��Ļ����ʷ�������죬������ʹ�ÿ�缲����\n");
       if((int)me->query_skill("hand", 1) < 250 )
                   return notify_fail("��Ļ����ַ�������죬������ʹ�ÿ�缲����\n"); 
	   if((int)me->query_skill("force", 1) < 250 )
                   return notify_fail("��Ļ����ڹ�������죬������ʹ�ÿ�缲����\n");
	   if((int)me->query_skill("dodge", 1) < 250 )
                   return notify_fail("��Ļ����ڹ�������죬������ʹ�ÿ�缲����\n");
	   if((int)me->query_dex(1) < 50 )
                   return notify_fail("��ĺ���������50��������ʹ�ÿ�缲����\n");
//�����������ӣ����ֿ���
	   if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "brush"
           || me->query_skill_mapped("brush") != "kuangfeng-xunlei"
           || me->query_skill_mapped("parry") != "kuangfeng-xunlei")
                   return notify_fail("�����ڼ�������ʹ���˿�缲��ô��\n");
                    
       if((int)me->query("max_neili") < 6000 )
                  return notify_fail("������������Ϊ����������ʹ�ÿ�缲����\n");
       if((int)me->query("neili") < 2000 )
                 return notify_fail("�������������㣬����ʹ�ÿ�缲����\n");
       if((int)me->query("jingli") < 1000 )
                 return notify_fail("�����ھ������㣬����ʹ�ÿ�缲����\n");
        message_vision(WHT"\n$N����һЦ������"+weapon->query("name")+WHT"���������ػ��˻ӣ�������������������ͻ�ؼӿ�!\n"NOR,me,target);
        message_vision(MAG"�����ǿ��Ѹ�׵ľ��С���缲����,˲�����е�����$N����������Ϭ���ĵ�Ѩ��ʽ��$nĿ��Ͼ�ӣ�����ʤ����\n"NOR,me,target);
		
		i = (int)me->query_skill("kuangfeng-xunlei",1);

        j=5;
		
		if (target->query_temp("kfxl/xlg"))
		{
			j=j-1;
			message_vision(RED"$N֪��$nΪ�Լ�Ѹ�׺ǹ����ţ����а�Ц�����ָ������飡\n"NOR,me,target);

		}
		me->set_temp("kfxl/kfjg",1);
     
		me->add("neili", -300);
		me->add("jingli", -200);
        me->add_temp("apply/attack",  i);
        me->add_temp("apply/damage",  i/j);

        me->add_temp("apply/hand",  i/j);
        me->add_temp("apply/brush",  i/j);

		if (me->is_fighting(target))

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
		weapon->unequip();
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
		weapon->wield();
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
		weapon->unequip();

		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
		weapon->wield();
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

      	weapon->unequip();

		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		weapon->wield();
        
           
	    me->add_temp("apply/attack",  -i);
        me->add_temp("apply/damage",  -i/j);

        me->add_temp("apply/hand",  -i/j);
        me->add_temp("apply/brush",  -i/j);
	
		me->delete_temp("kfxl/kfjg");
		message_vision(YEL"$Nһ�������󣬳���һ�����������ָֻ�ԭ��״̬��\n"NOR,me,target);

		me->start_perform(5,"����缲����");

		me->start_busy(random(3));

		return 1;
 }

string perform_name() {return HBCYN+HIB"��缲��"NOR;}

int help(object me)
{
	write(WHT"\n���Ѹ�ס�"HIR"��缲��"WHT"����"NOR"\n");
	write(@HELP
    ���Ѹ���ǻ�������ʽ������������ͬ���ַ����ʹ����
	�ڴ�ʤ�غ���ԭȺ��һս���ܷ���ָ��ʩչ�����Ѹ�׹�
	���Ǿ��ޡ�
	ע�⣺�˹����������ʩչ����Ѹ�׹���Ϻ�Ч�����ѡ�

	ָ�perform brush.kuangfeng

Ҫ��
	�����ڹ��ȼ� 350 ����
	�����ʷ��ȼ� 350 ��
	���Ѹ�׵ȼ� 350 ��
	�����Ṧ�ȼ� 350 ����
	��ǰ����Ҫ�� 2000 ���ϣ�
	�������Ҫ�� 6000 ���ϣ�
	��ǰ����Ҫ�� 1000  ���ϡ�
	�����ַ�Ϊ���Ѹ�׹���
	�����ʷ�Ϊ���Ѹ�׹���
	�ֱֳ���������
HELP
	);
	return 1;
}
