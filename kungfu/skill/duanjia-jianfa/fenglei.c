//���� fenglei.c 

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIC"��������"NOR;}

int perform(object me, object target)
{
        object weapon;
        int i,a;

        weapon = me->query_temp("weapon");
       
        if( !target ) target = offensive_target(me);
         if( !objectp(target)) return notify_fail("��Ҫ��˭������\n");

        if( !me->is_fighting() )
                return notify_fail("���������̡�ֻ����ս����ʹ�á�\n");
 
        weapon = me->query_temp("weapon");
        if (!weapon || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "duanjia-jianfa")
                return notify_fail("�����޽�,����ôʹ�ó����������̡���\n");

        if( (int)me->query("max_neili") < 1300 )
                return notify_fail("����������������\n");
		if( (int)me->query("max_jingli") < 900 )
                return notify_fail("��������������\n");
                
        if( (int)me->query("neili") < 500 )
                return notify_fail("�������������\n");

        if( (int)me->query("jingli") < 300 )
                return notify_fail("��ľ���������\n");

        if( (int)me->query_str() < 25 )
                return notify_fail("��ı���������\n");

        if( (int)me->query_skill("duanjia-jianfa",1) < 100 )
                return notify_fail("��Ķμҽ����ȼ�������\n");
        if( (int)me->query_skill("qingyan-zhang",1) < 100 )
                return notify_fail("������������Ƶȼ�������\n");
        if(!me->query_skill("kurong-changong", 1))
          if(me->query_skill("qiantian-yiyang", 1) < 100)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ�������������̡���\n");        
         
        if (me->query_skill_mapped("force") != "kurong-changong" )
          if(me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

        if( (int)me->query_skill("duanjia-jianfa",1) < 100 )
                return notify_fail("��Ķμҽ����������ң��޷�ʹ�á��������̡�������\n");

        if( (int)me->query_skill("sword",1) < 100 )
                return notify_fail("��Ľ������費�����޷�ʹ����˸���ġ��������̡�������\n");

        if( (int)me->query_skill("qingyan-zhang",1) < 100 ||
            me->query_skill_mapped("strike") != "qingyan-zhang")
                return notify_fail("������������ƻ������ң��޷�ʹ�á��������̡�������\n");

        if( (int)me->query_skill("strike",1) < 100 )
                return notify_fail("����Ʒ����費�����޷�ʹ����˸���ġ��������̡�������\n");

        if (me->query_skill_prepared("strike") != "qingyan-zhang"
		    || me->query_skill_mapped("strike") != "qingyan-zhang")
                return notify_fail("�㼤�����Ʒ����ԣ��޷�ʹ�á��������̡����й�����\n");
        if (me->query_skill_mapped("sword") != "duanjia-jianfa"
			 || me->query_skill_mapped("parry") != "duanjia-jianfa")
                return notify_fail("�㼤���Ľ������ԣ��޷�ʹ�á��������̡����й�����\n");

        if( (int)me->query_skill("tianlong-xiang",1) < 100 )
                return notify_fail("��������軹�����ң��޷�ʹ�á��������̡�������\n");
        
        i = (int)(me->query_skill("duanjia-jianfa",1)+me->query_skill("qingyan-zhang",1))/5;
        if (i < 250) target->start_busy(1+random(2));
        message_vision(BLU"\n$N������ϣ�����"HIM"����������"BLU"������"HIW"�μҽ���"BLU"��ʩչ���С�"HIR"��������"BLU"����\n"NOR, me,target);

		if(me->query("quest/tls/ailao/pass")){
		   message_vision(HIC"$N���Լ��������"+HIR+"����ɽ����"+HIC+"�����ڶμҽ����У������ݺᣬ����������\n"NOR,me);
		   //�׼�������
		   i=i+me->query_skill("qiantian-yiyang",1)/10;
		}
		if (i > 150) i=150;

        me->add("neili",-(150+random(50))); 
        me->add("jingli",-50); 
		me->set_temp("fenglei",4);
		for(a=0;a<4;a++)
        {
		    if(me->query("quest/tls/ailao/pass"))
		     {
                     //    message_vision(HIC"$N���Լ��������"+HIR+"����ɽ����"+HIC+"�����ڶμҽ����У�����������\n"NOR,me);
						 		
						if(objectp(target)) target->add_busy(1);

						 me->add_temp("apply/attack", i/3 );                        
                         me->add_temp("apply/damage", i/5   );
                         me->add_temp("apply/sword", i /5  );                         
		                 switch(random(2))
						 {
							case 0:
						      if(me->is_fighting(target))
		                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
							  break;
							case 1:
						      weapon->unequip();
                             // if(me->is_fighting(target))
								me->add_temp("apply/strike", i /4  );
		                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
								me->add_temp("apply/strike", -i /4);
							  weapon->wield();
							  break;
					     }
                         me->add_temp("apply/sword", -i /5);                      
                         me->add_temp("apply/damage", -i/5 );
                         me->add_temp("apply/attack", -i/3 );
              } else {
		                 me->add_temp("apply/attack", i /4 );                         
                         me->add_temp("apply/sword", i /6 );
                         me->add_temp("apply/damage", i /6 );
                         switch(random(2))
						{
							case 0:
						      if(me->is_fighting(target))
		                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); 
							  break;
							case 1:
						      weapon->unequip();
                             // if(me->is_fighting(target))
								me->add_temp("apply/strike", i /4  );
		                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); 
							  me->add_temp("apply/strike", -i /4);
							  weapon->wield();
							  break;
					     }
						 me->add_temp("apply/damage", - i/6  );
                         me->add_temp("apply/sword", - i /6 );
                        // me->add_temp("apply/strike", - i /4 );
                         me->add_temp("apply/attack", - i /4 );
			}
        }
        
		me->delete_temp("fenglei");
		//me->delete_temp("fl_sword");
        me->start_perform( 4 + random(2), "���������̡�");
		
me->start_busy(2);
        return 1;
}

int help(object me)
{
        write(HIR"\n�μҽ���֮���������̡���"NOR"\n\n");
        write(@HELP
	�����������Ǵ���μҽ����ľ��⣬�����˻��壬ͬʱ
	Ҳ��������ʿ�����˴���һ��ָ�����书�⣬��������
	�似���������������Ļ����ǿ����������У���������
	���Ƶ���ʽ���⿪�����������⽣����Ծ��
	
	perform sword.fenglei

Ҫ��
	��ǰ���� 500 ���ϣ�
	������� 1300 ���ϣ�
	����� 900 ���ϣ�
	�����Ʒ� 100 ����
	���������� 100����
	�μҽ��� 100����
	Ǭ��һ�� 100 ����
	����Ҫ�� 25 ���ϣ�
	�����Ʒ�Ϊ������
	��������Ϊ�μҽ�����
	�����м�Ϊ�μҽ�����
	���Ʒ�Ϊ���������ƣ�
	���ֱֳ�����

HELP
        );
        return 1;
}
