//rebuild by jpei 2010
//ԭ����˼·��Щ��
 
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

 int perform(object me, object target)
 {
         string msg;
         object weapon;
         int jf,zf,sf,lvl,i,j;
         jf = me->query_skill("jinshe-jianfa", 1);
         zf = me->query_skill("jinshe-zhang", 1);
         sf = me->query_skill("wudu-yanluobu", 1);
         lvl=( jf + zf +sf ) /3;        
         weapon = me->query_temp("weapon");
 
         if( !target ) target = offensive_target(me);
        if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)
          || environment(target)!= environment(me))
                return notify_fail("�����߿��衹ֻ����ս���жԶ���ʹ�á�\n");
 
 
        if (!weapon || weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "jinshe-jianfa")
                 return notify_fail("�������ʹ�ý�ʱ����ʹ�������߿��衹��\n");
 
        if(me->query_skill("jinshe-jianfa", 1) < 450 )
                 return notify_fail("��Ľ��߽�����������죬ʹ���������߿��衹������\n");
		if(me->query_skill("jinshe-zhangfa", 1) < 450 )
                 return notify_fail("��Ľ����Ʒ���������죬ʹ���������߿��衹������\n");
        if( (int)me->query_skill("force",1) < 450 )
                 return notify_fail("��Ļ����ڹ��ȼ�������ʹ���������߿��衹������\n");
 
         if( (int)me->query_str() < 37)
                 return notify_fail("�������������ǿ����ʹ���������߿��衹������\n");
 
         if( (int)me->query_dex() < 37)
                 return notify_fail("�����������Ѹ�ͣ�ʹ���������߿��衹������\n");

         if( (int)me->query("dex") < 20 ||(int)me->query("str") < 20 || (int)me->query("int") < 20)
                 return notify_fail(HIG"��ɵͷɵ��,���ֱ��ŵ�,�����ʲô��.\n"NOR);
              
         if( (int)me->query("max_neili") < 5000 )
                 return notify_fail("����������̫����ʹ���������߿��衹��\n");      
 
         if( (int)me->query("neili") < 500 )
                 return notify_fail("�������������㣬ʹ���������߿��衹��\n");

		 if (me->query("quest/���߽���/pass"))
		 {
			 i=3;
		 }else if (me->query("quest/jinshe2/pass"))
		 {
			 i=2;
		 }else i=1;
		 //weapon = me->query_temp("weapon");

//�ж������ǲ��ǽ��߽���������,������bug
         if((weapon->query("id") == "jinshe sword" && weapon->query("owner")=="��ѩ��")
		   ||(weapon->query("id") == "yinshe sword" && weapon->query("spec"))
		   || !userp(me))
			   me->set_temp("jsjf/shejian", 1); 
   //�嶾���޲�����
         if( me->query_skill("wudu-yanluobu", 1) > 450
			 && me->query_skill_mapped("dodge") == "wudu-yanluobu")
           {     
			 
			 me->add_temp("apply/dexerity",sf /10);
             me->add_temp("apply/attack",sf /4); 
             me->set_temp("jsjf/sfup",1); 
           }
//�����Ʒ�����
         if( me->query_skill("jinshe-zhangfa", 1) > 450
			 && me->query_skill_mapped("strike") == "jinshe-zhangfa"
		     && me->query_skill_prepared("strike") == "jinshe-zhangfa")
           {          
		     me->add_temp("apply/strength", zf/10);
             me->add_temp("apply/damage", zf/6);
             me->set_temp("jsjf/zfup",1);
           }       

		
         message_vision(HIC"\n$Nһ������"+weapon->name()+HIC"ʹ�����߽�������֮�أ���"HIY+chinese_number(i)+HIC"�ؽ��߿���֮"HIY"���߿���"HIC"������Ȼ�ӿ����ٱ���\n"NOR,me);
         //��ͨ����
		 me->add_temp("apply/damage", lvl /6);
         me->add_temp("apply/attack", lvl /4);
         me->add_temp("apply/dexerity",sf /10);
		 me->add("neili",-800);
		 me->add("jingli",-500);
//��ͨ��������
         if (!me->query_temp("jsjf/shejian"))
         {
			 for (j=0;j>5 ;j++ )
			 {
				if (objectp(target)&&me->is_fighting())
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			 }
			 me->add_temp("apply/damage", -lvl /6);
			 me->add_temp("apply/attack", -lvl /4);
			 me->add_temp("apply/dexerity",-sf /10);
			 me->add_busy(2);
			 me->start_perform(5,"���߿���");

			 return 1;

         }
//�������α�������

         if(me->query_temp("jsjf/sfup"))
         {      
            message_vision(HIY"\n\n$N����"+weapon->name()+HIY"�����������Ƴ�������⣬������$N����Ϊ"HIR+chinese_number(i)+HIY"�������������Σ�Χ��$n������ת����\n"NOR,me,target);
            message_vision(HIR"$N�����а���ޱ�,$n��ʱ�����ۻ�����,��$N���˸����ֲ�����\n"NOR,me,target);                     
            if(!userp(target)) target->add_busy( sf/100 + random(2));
		 }


         if(me->query_temp("jsjf/shejian") )
		 {  
			    //���߽�������                                                             
			 if( me->query_skill("jinshe-jianfa",  1) > 450
				 && me->query_skill_mapped("sword") == "jinshe-jianfa")
			  {     
				 	message_vision(MAG"$N�ֳ�"+weapon->name()+MAG",���߽����ڹ�����������£�������ʱ������\n"NOR,me);
					me->add_temp("apply/sword", lvl /4);
					me->add_temp("apply/parry", lvl /4);
					me->add_temp("apply/damage", lvl/6);
					me->set_temp("jsjf/jfup",1);
			  }        


			if (me->is_fighting(target)) 
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
							  message_vision(HIY"                                                                     ��������������\n"NOR,me);       
							  message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);
							  message_vision(HIY"                                                                     ��������������\n"NOR,me);       
	   
			if (me->is_fighting(target)) 
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
							  message_vision(HIY"                                                                     ��������������\n"NOR,me);       
							  message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);       
							  message_vision(HIY"                                                                     ��������������\n"NOR,me);       

			if (me->is_fighting(target))
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
							  message_vision(HIY"                                                                     ��������������\n"NOR,me);       
							  message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);       
							  message_vision(HIY"                                                                     ��������������\n"NOR,me);       
			if (me->is_fighting(target))
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
							  message_vision(HIY"                                                                     ��������������\n"NOR,me);       
							  message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);       
							  message_vision(HIY"                                                                     ��������������\n"NOR,me);       
		 	
			if (objectp(target)&&me->is_fighting())
			{
				weapon->unequip(); 
				message_vision(HIB"$N����Ȼһ�գ��ڱ��ܹ�����˳���ĳ�һ�ƣ�\n"NOR,me,target);
				me->add_temp("apply/strike",lvl/4);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->add_temp("apply/strike",-lvl/4);
				weapon->wield();
			}

		 } 
		 else if( objectp(target)
				&& me->query_temp("jsjf/zfup"))
		 {
			  message_vision(HIC"\nͻȻ$N����$n���ٱ��ߣ���Ȼ����һ�����ƣ�\n"NOR,me,target);
			  me->start_perform(4,"�����߿��衹");
				  if (objectp(target)&&me->is_fighting())
					  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				
				  if (objectp(target)&&me->is_fighting()) 
				  {
					 weapon->unequip(); 
					 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
					 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
					 weapon->wield();
				  }
		}       

       if (me->query_temp("jsjf/sfup"))
	   {
                me->add_temp("apply/dexerity",-sf /10);      
                me->add_temp("apply/attack",   -sf /4); 
				me->delete_temp("jsjf/sfup");
       }
       if (me->query_temp("zfup"))
	   {  
                me->add_temp("apply/strength", -zf/10);
                me->add_temp("apply/damage", -zf/ 6);
				me->delete_temp("jsjf/zfup");
       }
       if( me->query_temp("jsjf/jfup"))
	   {
                me->add_temp("apply/sword",     - lvl/4);
                me->add_temp("apply/parry",      - lvl/4);
                me->add_temp("apply/damage",  - lvl/6);
				me->delete_temp("jsjf/zfup");
       }
		
       me->delete_temp("jsjf/shejian");

       me->add_temp("apply/damage", -lvl /6);
       me->add_temp("apply/attack", -lvl /4);
       me->add_temp("apply/dexerity",-sf /10);  
       me->start_busy(1+random(2));
       target->start_busy(1);
       me->start_perform(6,"�����߿��衹");

       return 1;
 }


int help(object me)
{
        write(HIY"\n���߽���֮�����߿��衹��"NOR"\n\n");
        write(@HELP
	�����ɾ���ѩ�������������ĵľ����书. ��ϧ��������
	�����ؼ����ָ�ɺü�����, ���߿��������Ҳ����ǰ. 
	�ഫ�ڴ�������ؼ��еĽ���, ��, �Ʒ�����ܷ��ӽ�
	��������������. ������ҿ��Ի�ý��߽�, ��ʹ������
	���ϲ�¥��

	ָ�perform sword.kuangwu

Ҫ��
	��ǰ���� 500 ����;
	������� 5000 ���ϣ�
	���߽��� 450 ���ϣ�
	�����Ʒ� 450 ���ϣ�
	�����ڹ� 450 ���ϣ�
	������,���Բ���С��20,
	�����������С��20,
	����������������37
	��һ�׶Σ����߽����ȼ� 450 ���ϣ������ڹ��ȼ� 450 ���ϣ�
	��������Ϊ���߽�����
	�ڶ��׶Σ������Ʒ��ȼ� 450 ���ϣ�����׼���Ʒ�Ϊ�����Ʒ���
	�����׶Σ��嶾���޲��ȼ� 450 ���ϣ������ṦΪ�嶾���޲���
                
    ���⣬���װ���˽��߽��������߽��������ɸ���һ��¥��

HELP
        );
        return 1;
}

string perform_name(){ return HBYEL+HIR"���߿���"NOR; }
