//kuangdao.c �ﲮ��Ŀ��쵶��Ϊ���� 
//cre by sohu@xojh
#include <ansi.h>
inherit F_SSERVER;
    
   string perform_name(){ return HIW"���쵶"NOR; }
    
   int perform(object me,object target)
 {
       object weapon;
       int i;
      
       if( !target ) target = offensive_target(me);
       
       if( !objectp (target) || !me->is_fighting(target) || !living(target)
          || environment(target)!=environment(me))
                   return notify_fail("���쵶ֻ�ܶ�ս���еĶ���ʹ�á�\n");  
       if( !me->query("quest/hmy/tmd/kuaidao/pass")) 
                   return notify_fail("��ֻ����˵�����쵶����������δ���ɣ�����ʹ�ÿ��쵶��\n");
       if( (int)me->query_skill("tianmo-dao", 1) < 450 ) 
                   return notify_fail("��Ŀ��쵶��δ���ɣ�����ʹ�ÿ��쵶��\n");

                 
       if((int)me->query_skill("blade", 1) < 450 )
                   return notify_fail("��Ļ�������������죬������ʹ�ÿ��쵶��\n");
	    if((int)me->query_skill("force", 1) < 450 )
                   return notify_fail("��Ļ����ڹ�������죬������ʹ�ÿ��쵶��\n");
      
	   if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "blade"
           || me->query_skill_mapped("blade") != "tianmo-dao"
           || me->query_skill_mapped("parry") != "tianmo-dao")
                   return notify_fail("������ʹ���˿��쵶ô��\n");
                   
       if((int)me->query("max_neili") < 9000 )
                  return notify_fail("������������Ϊ����������ʹ�ÿ��쵶��\n");
       if((int)me->query("neili") < 2000 )
                 return notify_fail("�������������㣬����ʹ�ÿ��쵶��\n");
  
       message_vision(HIW"\n$N��ͻ�ؼӿ죬ʹ���쵶����ν�������书���޼᲻�ݣ�Ψ�첻�ơ�\n",me);
       message_vision(HIM"$N���α仯��˲������������������������������ħ�����ľ��С����쵶��!\n",me);
		i = (int)me->query_skill("tianmo-dao",1)/4;
		target->receive_damage("qi",i*(2+random(4)),me);
        me->set_temp("tmd/kf1",1);
		
		//me->start_perform(2,"�����쵶��");
      
		me->add("neili", -300);
		me->add_temp("apply/attack",  i);
        me->add_temp("apply/damage",  i/4);
        me->add_temp("apply/blade",  i/4);
      
	  if (me->is_fighting(target))
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
     
     // if (me->is_fighting(target))
         //COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
      
      if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
	  if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);

	  if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
     me->delete_temp("tmd/kf1");
           
	  if(me->query("quest/hmy/tmd/kuaidao/pass")&&objectp(target))
	 {
			message_vision(HBYEL+RED"$N��Ȼ�����쵶�ľ����ڻ��ͨ,����һ��������������ת�����еĵ�����ʱһ�䡣\n"NOR,me);
			message_vision(HBYEL+RED"��ʽ�Ѿ�����������Ͼ�������������籩��һ�㣬���⽫$n���ֹ�����\n"NOR,me,target);


			if (userp(target))
				target->add_busy(2);

			else target->add_busy(4);
			me->add_temp("apply/attack",  i/4);
			me->add_temp("apply/damage",  i/5);
			me->set_temp("tmd/kf2",1);
			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
            if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);                 
            if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
/*
			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
*/
			//target->receive_damage("qi",i*2,me);

			me->delete_temp("tmd/kf2");

			me->add_temp("apply/attack",  -i/4);
			me->add_temp("apply/damage",  -i/5);
		}
		
		me->add_temp("apply/attack",  -i);
        me->add_temp("apply/damage",  -i/4);
	    me->add_temp("apply/blade",  -i/4);

			me->delete_temp("tmd/kfdf");

			me->start_perform(6,"�����쵶��");

			me->start_busy(2+random(2));

			return 1;
 }

int help(object me)
{
        write(HIB"\n��ħ��֮�����쵶����"NOR"\n\n");
        write(@HELP
	���쵶Դ�Խ��������ﲮ��ľ�ѧ���뵱���ڻ���¥��
	�����һս��ʹ�ÿ��쵶���𽭺���Ѱ���쵶��������
	���ԣ�����Ե�ɺϻ���ﲮ����洫����ÿ쵶��������
	�����ͷš�
	
ָ��:perform blade.kuangdao

Ҫ��
	��ǰ�������� 9000 ���ϣ�
	����������� 3000 ���ϣ�
	��ħ�����ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	�����ڹ��ȼ� 450 ���ϣ�
	��������Ϊ��ħ����
	�����м�Ϊ��ħ����
	�����ڹ����ޣ�
	���ֳֵ��������
HELP
        );
        return 1;
}
