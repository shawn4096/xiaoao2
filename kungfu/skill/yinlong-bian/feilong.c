
// feilong.c ����������֮����������
// Build by fengyue@CB 2008-10-20
// ������� zaqz,howkjie,axj@CB


#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int lvl, skill, skill1,jiali;
	object weapon;
	string name;

	weapon = me->query_temp("weapon");
	if (weapon) name = weapon->query("name");

	if( !target ) target = offensive_target(me);
     
	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("����������ֻ����ս���жԶ���ʹ�á�\n");

	if (!weapon
	 || weapon->query("skill_type") != "whip"
	 || me->query_skill_mapped("whip") != "yinlong-bian")
		return notify_fail("�㲻�ñ�����ôʹ�á�����������\n");             

	if( (int)me->query_skill("yinlong-bian",1) < 450 )
		return notify_fail("��ľ��������޲�����죬����ʹ�á�����������\n");
      
	if( (int)me->query_skill("whip",1) < 450 )
		return notify_fail("��Ļ����޷��ȼ�����������ʹ�á�����������\n");  

	if( (int)me->query_skill("claw", 1) < 450 )
		return notify_fail("���צ���ȼ�����������ʹ�á�����������\n");
  
	if( (int)me->query_skill("force", 1) < 450 )
		return notify_fail("����ڹ��ȼ�����������ʹ�á�����������\n");

	if( (int)me->query("max_neili") < 10000 )
		return notify_fail("�������̫��������ʹ�á�����������\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("�������̫���ˣ��޷�ʹ�ó�������������\n");

	if( (int)me->query("jingli") < 500 )

		return notify_fail("��ľ���̫���ˣ��޷�ʹ�ó�������������\n");
/*

����ж��������д�����jifa claw ���� jybgz,���߲���9ysz ...
��ôִ���������ǲ��Եġ�*/
	if (me->query_skill_mapped("claw") != "jiuyin-baiguzhua"
	 && me->query_skill_mapped("claw") != "jiuyin-shenzhua")
		return notify_fail("��û�м��������׹�צ�������޷�ʹ�á������������й�����\n");
		
    if (me->query_skill(me->query_skill_mapped("claw"),1)<450)
		return notify_fail("���"+ me->query_skill_mapped("claw") +"�ȼ�̫�ͣ������޷�ʹ�á������������й�����\n");
    		
		
	skill = me->query_skill("yinlong-bian", 1);
	skill1 = me->query_skill("claw", 1);
    lvl =  skill / 4;

	lvl += skill1 / 5;

	
	if (me->query("quest/em/zzr/pass"))
	{
		message_vision(HIC"\n$N������������ָ�㣬����"+name+HIW"�͵�˦�����ھ����Ī�⣬��ޱ������߲�����\n"NOR, me,target);

		lvl+=me->query_skill("jiuyin-zhengong",1);
	}
	jiali = me->query("jiali");

	message_vision(HIW"\n$N����һ��һ�Σ�����"+name+HIW"�͵�˦������������������������磬ʸ�ö�����\n"NOR, me,target);
	message_vision(HIB"$N����ʳ�ж�ָ����צ״����$n������ȥ��һ����צ��ȫ�Ƕ���ͷ����ǰ����Ѩ��\n"NOR, me,target);
	me->add("neili", -350); 
	me->add("jingli", -100); 

	if ( skill > 200)
		lvl = to_int((skill+skill1)/8.0* skill/200.0);

	if ( jiali > 100) {
		me->set("jiali", 100);
		me->set_temp("lyjiali", 1);
	}

	me->set_temp("feilong", 1);
	me->add_temp("apply/attack", lvl);
	me->add_temp("apply/damage", lvl/2);
	me->add_temp("apply/claw", lvl);
	me->add_temp("apply/whip", lvl);
//��һ��
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

//�ڶ���
	if ( me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);

         	weapon->unequip(); 

// ��һ��������ж�9ybgz�������ж���û��9yzg֧�֡�Ϊ�˷�ֹ��Ҽ�����Ŀ��֡�

	if( me->is_fighting(target) 
		&& me->query_skill_prepared("claw") == "jiuyin-baiguzhua" 
		&& me->query_skill_mapped("claw") == "jiuyin-baiguzhua" )
	{
		
		if (me->query("quest/jiuyin2/jybgz/pass"))
			 {
				 message_vision(HIR"\n$N��ʹ�����׹�צ��ָצ�Ӷ��䰵����������Ȼ�ѵ�÷��������洫��������������������ޱȣ�\n"NOR, me,target);
                target->set_temp("must_be_hit",1);
                target->add_busy(4);
                COMBAT_D->do_attack(me, target, 0, 3);
				COMBAT_D->do_attack(me, target, 0, 3);
                message_vision(HIR"\n$N���ָ���ǰ̽�������׹�צ��ָ��ץ��$nͷ��,�ۼ���һץ֮�£���ʱ����ͷ������֮�֣�\n"NOR, me,target);    				
               	              
                COMBAT_D->do_attack(me, target, 0, 3);
                target->delete_temp("must_be_hit",1) ; 				 
			 }		
         else if(me->query_skill("jiuyin-zhengong",1) >= 120)
         {
			 
		    	message_vision(HIM"\n$N��ʹ�����׹�צ��ָצ�Ӷ����������˻˻���죬����������������������������ޱȣ�\n"NOR, me,target);
                target->set_temp("must_be_hit",1);
                target->add_busy(3);
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
				//COMBAT_D->do_attack(me, target, 0, random(2)?1:3);                      
               	message_vision(HIM"\n$N���ָ���ǰ̽�������׹�צ��ָ��ץ��$n�ؿ�,�ۼ���һץ֮�£���ʱ���ǿ�������֮����\n"NOR, me,target);         
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
                target->delete_temp("must_be_hit",1) ; 		
         }		 
		  
		  COMBAT_D->do_attack(me, target, 0, random(2)?1:3); 
          COMBAT_D->do_attack(me, target, 0, random(2)?1:3); 

}
// ��2��������жϼ���9����צ�;����湦��

	if( me->is_fighting(target) 
		&& me->query_skill_prepared("claw") == "jiuyin-shenzhua" 
		&& me->query_skill_mapped("claw") == "jiuyin-shenzhua" )
	{
         if( me->query_skill("jiuyin-zhengong",1) >= 120 )
              {
              		if (me->is_fighting(target)&& objectp(target))
					{
						
						message_vision(HIM"\n$Nצ���þ�������֧�֣�����Զ�Ǿ����׹�צ�ɱȣ�����������ף������ޱȣ�\n"NOR, me,target);
                        target->set_temp("must_be_hit",1);
                        target->add_busy(5);
                        COMBAT_D->do_attack(me, target, 0, 3);
					}
					if (me->is_fighting(target)&& objectp(target))
					{
               			message_vision(HIM"\n$N���ָ���ǰ̽��������צ��������ץ��$n�ؿ�,�ۼ���һץ��������ʱ���ǿ�������֮����\n"NOR, me,target);
                        target->set_temp("must_be_hit",1);
                        COMBAT_D->do_attack(me, target, 0, 3);
                        target->delete_temp("must_be_hit",1) ; 
					}
               }
			   COMBAT_D->do_attack(me, target, 0, random(2)?1:3);  
			if (me->is_fighting(target)&& objectp(target))
				COMBAT_D->do_attack(me, target, 0,3); 
            if (me->is_fighting(target)&& objectp(target))
				COMBAT_D->do_attack(me, target, 0, 3); 
			           
	}
    weapon->wield();

	if ( me->query_temp("lyjiali"))
	{
 		me->set("jiali", jiali);
		me->delete_temp("lyjiali");
	}

	me->add_temp("apply/attack", -lvl);
	me->add_temp("apply/whip", -lvl);
	me->add_temp("apply/damage", -lvl/2);
	me->add_temp("apply/claw", -lvl);
        me->start_busy(1);
	me->delete_temp("feilong");
	me->start_perform(5, "����������");
	return 1;
}

string perform_name(){ return HIW"������"NOR; }

int help(object me)
{
	write(HIW"\n����������֮������������"NOR"\n\n");
	write(@HELP
	�����������Ǿ����澭�¾����������书���ʹ����ơ������׹�ץ
	��������޷�ʩչ����������ֻ��Ҫ�㹻�ļ��ɾ���ʩչ���в���
	���ҷ�������Ҳ�Ƿ��겻͸���������ܡ�
	����������ʹ�����޺;����澭�¾���书��ϣ�һ�����У�����
	Ī�⣬���м���צ����צ�����̺����ӡ�Զ���������������䣬��
	��ʤ������ü�������⿪���������⣬���л��Ծ��
	���������׹�צ�ܵ�÷�����֪���У�����������������צ��

ָ�perform whip.feilong

Ҫ��
	��ǰ�������� 500 ���ϣ�
	����������� 10000 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	���������޵ȼ� 450 ���ϣ�
	������(�׹�צ)צ 450 ���ϣ�	
	�����ڹ����� 450 ���ϣ�	
	�����޷�,�м�Ϊ���������ޣ�
	���ֱֳ�����

ע�⣺����������¼��ܣ��������벻����Ч��Ч��        
	����צ��Ϊ�����׹�צ�������צ���ұ�צ����
	�����湦�ȼ� 120 ����(���輤��)��		

		

HELP
        );
        return 1;
}
