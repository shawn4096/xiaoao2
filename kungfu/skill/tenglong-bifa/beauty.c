// beauty ��������
// 19991002001
// Update By lsxk@hsbbs 2007/6/5

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HBMAG+HIW"��������"NOR;}

int calc_damage(int,int,object,object);
int b_attack(object me,object target,object weapon);
int perform2(object me,object target,object weapon);
int perform3(object me,object target,object weapon); 

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int skill,lvl,i,total; 
        skill=me->query_skill("tenglong-bifa",1);
		lvl=skill+me->query_skill("dulong-dafa",1)/4;
		weapon=me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

         if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("���������С�ֻ����ս��ʱʹ�ã�\n");

       // if(me->query("family/master_id")!="su quan")
         //       return notify_fail("���������С�ֻ�а�������������ã�\n");
		if(!me->query("quest/sld/tlbf/beauty/pass"))
                return notify_fail("���������С���ֻ����˵�����������δ�ڻ��ͨ��\n");

        if( !objectp(weapon) 
			|| weapon->query("skill_type")!="dagger")                    
                return notify_fail("���������ذ�ײ����á��������С���\n");
       

        
        if( (int)me->query_skill("chansi-shou", 1) < 500 )
               return notify_fail("��Ľ��߲�˿�ֻ���������������ʹ�á��������С���\n");

        if (me->query_skill_mapped("hand") != "chansi-shou")
               return notify_fail("ֻ��ʹ�ý��߲�˿��ʱ����ʹ�á��������С���\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 500 )
               return notify_fail("��������ȷ�����������������ʹ�á��������С���\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
               return notify_fail("ֻ��ʹ�������ȷ�ʱ����ʹ�á��������С���\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 500 )
                return notify_fail("�������ذ������������������ʹ�á��������С���\n");

        if (me->query_skill_mapped("dagger") != "tenglong-bifa"
			||me->query_skill_mapped("parry") != "tenglong-bifa")
                return notify_fail("ֻ�м�������ذ��ʱ����ʹ�á��������С���\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 500 )
                return notify_fail("��Ķ����󷨹������㣬�����á��������С���\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�á��������С���\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("�������������㣬����ʹ�á��������С���\n");      

        if(me->query("gender") == "����" ) 
                return notify_fail("����Ů����ô��ʹ�á��������С��أ�\n");
        
		if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��������ִ�������ʹ�á��������С���\n");
		if (me->query_temp("tlbf/beauty"))
			return notify_fail("������ʹ�á��������С���\n");

        me->add("jingli",-100);
        me->add("neili",-400);

        message_vision(HBMAG+HIW"$N��$n��������֮�������շ�����������ʽ�ڻ��ͨ���ԡ��������С��ķ�ʽʩչ������\n"NOR,me,target);
		message_vision(HBMAG+HIW"$N���е�"+weapon->name()+HBMAG+HIW"��������������������������С����¡�����������衹���������\n"NOR,me,target);
		me->set_temp("tlbf/beauty",1);
       
		if(random(me->query_skill("tenglong-bifa",1)) > target->query_skill("parry",1)/4
          || random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/6
          ||(!userp(target) &&target->is_busy()) )
		{
                //me->start_busy(1);
                total = 0;
                i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("tenglong-bifa",1),me,target);
                total += i;
				if (me->query("gender")=="Ů��" && random(me->query_per(1))>35)
				{
					total=total+i*((int)me->query("per")/25);
					target->add_busy(2+random(2));
					message_vision(HBYEL"$N��������,��ȻһЦ����ʱ��$n��������һ����"NOR,me,target);
				}
				message_vision(HIY "\n\n$Nʹ��һ�С�"HIM"��������"HIY"��������΢����������Ť�����㷴�ߣ���$nС����ȥ��\n"+
                          "����˳�Ʒ�������§ס$nͷ�������ֱ��ж�׼$n���Ļ�ȥ��\n"NOR,me,target);
               
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                
                if (userp(target))
				    if (total>5000) total=5000+(total-5000)/100;
				//else if (total>8000) total=8000+(total-8000)/100;
                
				target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "ͷ��" );
                msg = result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ i+ WHT"�㹥���˺���\n"NOR);    
                if(target&&userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ i+ WHT"���˺���\n"NOR); 
               
		}else{

				message_vision(" ����$n������$N����ͼ��û���ϵ�������ææ���Ա�һ�������˹�ȥ��\n",me,target);
				//return 1;
				me->add_busy(1);

		}
				//׷�ӹ�����
				 		
		if (me->is_fighting()
			&&objectp(target)
			&&me->query("quest/sld/tlbf/beauty/pass"))
        {
					message_vision(HIG"$N�ڷ�Ծ$nͷ��֮�ʣ������ȷ���ȹ�׽Ŷ�Ȼ������ת����$n�������ȣ����ǡ�"HIR"����ԧ����"HIG"����\n"NOR,me,target);
					me->add_temp("apply/attack",skill/2);
					me->add_temp("apply/damage",skill/3);
					me->add_temp("apply/leg",skill/2);
					weapon->unequip();
					me->prepare_skill("leg", "shenlong-tuifa");
					target->add_busy(1);
					COMBAT_D->do_attack(me,target,me->query_temp("weapon"),3);
					COMBAT_D->do_attack(me,target,me->query_temp("weapon"),3);
					me->add_temp("apply/attack",-skill/2);
					me->add_temp("apply/damage",-skill/3);
					me->add_temp("apply/leg",-skill/2);
					weapon->wield();
        }
		//���Ӷ����󷨽⿪��Ƕ��
		if (me->query_temp("quest/sld/dldf/pass"))
		{
			me->start_perform(3,"��������");
		}else me->start_perform(6,"���������С�");

		if (me->is_fighting()&&objectp(target)&&weapon)					
			perform2(me,target,weapon);
		
		me->delete_temp("tlbf/beauty");
		return 1;
}

//�ڶ���
int perform2(object me,object target,object weapon)
{
        string msg,result;
        int skill,lvl,i,total; 
        skill=me->query_skill("tenglong-bifa",1);
		lvl=skill+me->query_skill("dulong-dafa",1)/4;
		if (!objectp(target)||!objectp(weapon))
		{
			me->delete_temp("tlbf/beauty");
			return 0;
		}
		me->set_temp("tlbf/beauty",1);
		if( !target ) target = offensive_target(me);

				message_vision(HIC "\n$N����б�㣬ʹ��һ�С�"HIG"С�����"HIC"�����Դ�������Լ��ؿ����䣬˳���ڵ���һ����������������\n"+
                         "��$n������������ű��������ֳ�ȭ����$n���ġ�\n"NOR,me,target);
				
                i = calc_damage((int)me->query_skill("tenglong-bifa",1),(int)me->query_skill("chansi-shou",1),me,target);
                total += i;
				if (!userp(target))
					if (total>8000) total=8000+(total-8000)/100;
		       // else if (total>6000) total=6000+(total-6000)/100;
                
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "����" );
                result = replace_string( result, "$w", weapon->query("name") );
                msg = result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
				//��������
			//	if (me->is_fighting(target)&& objectp(target))
				//	COMBAT_D->do_attack(me,target,weapon,3);


                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ i+ WHT"�㹥���˺���\n"NOR);    
                if(target&&userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ i+ WHT"���˺���\n"NOR);
				if (me->is_fighting(target)&& me->query_per()>25)
                {
					message_vision(HIR"$n��$N���Լ���ȻһЦ���������ߵ�֮�ʣ�$N���ֺ�Ȼ���ɽ��߲�˿�ֵ���ʽ����Ȼ����$n��˫����\n"NOR,me,target);
					if (random(me->query("combat_exp"))>target->query("combat_exp")/3)
					{
						message_vision(RED"$n��$N�⼲�籩��Ĺ�����ʽ����һ���亹��������Щ��æ����������\n"NOR,me,target);
						target->add_busy(2);
						target->add_condition("no_exert",1);
					}
					me->add_temp("apply/attack",skill/2);
					me->add_temp("apply/damage",skill/4);
					me->add_temp("apply/hand",skill/2);
					weapon->unequip();
					me->prepare_skill("leg");
					me->prepare_skill("hand", "chansi-shou");
					COMBAT_D->do_attack(me,target,weapon,3);//��5��
					COMBAT_D->do_attack(me,target,weapon,3);//6
					me->add_temp("apply/attack",-skill/2);
					me->add_temp("apply/damage",-skill/4);
					me->add_temp("apply/hand",-skill/2);
					weapon->wield();
                }
				//���Ӷ����󷨽⿪��Ƕ��
				if (me->query_temp("quest/sld/dldf/pass"))
				{
					me->start_perform(3,"��������");
				}else me->start_perform(6,"���������С�");
				if (me->is_fighting()
					&&objectp(target)
					&&weapon)
					call_out("perform3",1,me,target,weapon);
                me->delete_temp("tlbf/beauty");
				return 1;
}
				
int perform3(object me,object target,object weapon) 
{
	 string msg,result;
     int skill,lvl,i,total; 
     skill=me->query_skill("tenglong-bifa",1);
	 lvl=skill+me->query_skill("dulong-dafa",1)/4;
	 
		if (!objectp(target)||!objectp(weapon))
		{
			me->delete_temp("tlbf/beauty");
			return 0;
		}
		me->set_temp("tlbf/beauty",1);
				message_vision(MAG "\n$Nʹ��һ�С�"HIR"�������"MAG"��������˳��һ�����ڱ�����һ�㣬����������$N�ʺ�\n"+
                         "���ȥ��$N��������һ�����Ǳ�������$n�ؿڡ�\n"NOR,me,target);
				//if (objectp(target))
			    i = calc_damage((int)me->query_skill("tenglong-bifa",1),(int)me->query_skill("dulong-dafa",1),me,target);
                total += i;
				
				if (!userp(target))
					if (total>10000) total=10000+(total-10000)/100;
		      //  else if (total>7000) total=7000+(total-7000)/100;
                
				if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                

                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(total,"����");
                result = replace_string( result, "$l", "�ؿ�" );
                msg = result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);  
				//��������			
				//���ӹ���
				if (me->is_fighting()
					&& objectp(weapon)
					&& objectp(target)
					&& me->query("quest/sld/tlbf/beauty/pass"))
				{
					b_attack(me,target,weapon);	
				}
				//call_out("b_attack",1,me,target,weapon);
			

     
				if(userp(me) && me->query("env/damage"))
				{
					tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ i+ WHT"�㹥���˺���\n"NOR);  
					tell_object(me,WHT"��ġ���Ů���С���"+ target->query("name") +"�ܹ������"RED+ total+ WHT"�㹥���˺���\n"NOR);    
				}
         
				if(target&&userp(target)&& target->query("env/damage"))     { 
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ i+ WHT"���˺���\n"NOR); 
					tell_object(target,WHT""+ me->query("name") +"�ġ���Ů���С������ܹ������"RED+ total+ WHT"���˺���\n"NOR);          
				}
                
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));
                
				//���Ӷ����󷨽⿪��Ƕ��
				if (me->query_temp("quest/sld/dldf/pass"))
				{
					me->start_perform(3,"��������");
				}else me->start_perform(6,"���������С�");
				me->delete_temp("tlbf/beauty");
				return 1;
}

int b_attack(object me,object target,object weapon)
{
		
		
		int skill;
		if (!me||!target||!weapon) return 0;
		skill=me->query_skill("tenglong-bifa",1);

		message_vision(HBRED"$n��Ȼ��$N��ذ����Ȼ������ǰ�����������û��$N������Ц�����������������У�����������\n"NOR,me,target);
		message_vision(HIW"$n�̲�ס��$N�ȵ��������ˣ����浱�����������������Ы�������־�Ȼ��˺ݶ���\n"NOR,me,target);

		me->set_temp("tlbf/beautya",1);
		me->add_temp("apply/attack",skill/2);
		me->add_temp("apply/damage",skill/4);
		if (me->is_fighting(target)&& objectp(target))
			COMBAT_D->do_attack(me,target,weapon,3);
		if (me->is_fighting(target)&& objectp(target))
			COMBAT_D->do_attack(me,target,weapon,3);
		if (me->is_fighting(target)&& objectp(target))
			COMBAT_D->do_attack(me,target,weapon,3);
		me->delete_temp("tlbf/beautya");

		me->add_temp("apply/attack",-skill/2);
		me->add_temp("apply/damage",-skill/4);        
		me->start_perform(6,"���������С�");

		return 1;

}

int calc_damage(int skill,int skill2,object me,object target)
{
			int i;
			if (!me||!objectp(target)) return 0;
		
            i = ( (skill+skill2)*2 - (int)target->query_skill("parry",1) )*10;
            if (i<0) i = -i;
               i += random(i*2/5);
            if( i < (skill2*5)) i = (int)target->query("qi",1)/2;   

            if(userp(target)) return  i/3;


			return i*3/5;
}

int help(object me)
{
   write(WHT"\n����ذ��֮��"HBMAG+HIW"��������"WHT"����"NOR"\n");
   write(@HELP
	����ذ�����������������������Ĳ���֮��
	�仯��ˣ�����ʤ������ν��Ů�˵����Ʒ�
	�ӵ����쾡�¡�
	���������ǽ�������Ů�������似֮��ɣ�
	�����ȷ������в�˿�ּ�����ذ��֮�У�ս
	���ڼ䣬����Ѳ⣬����ʤ����
	ע�⣺��ò���������к��˺��Ļ�����
	
	perform dagger.beauty

Ҫ��
	��ǰ������Ҫ�� 1500 ���ϣ�
	��ǰ������Ҫ�� 1000 ���ϣ�
	���߲�˿�ֵȼ� 500 ���ϣ�
	�����ȷ��ĵȼ� 500 ���ϣ�
	����ذ���ĵȼ� 500 ���ϣ�
	�����󷨵ĵȼ� 500 ���ϣ�
	�����ڹ�Ϊ�����󷨣�
	����ذ��Ϊ����ذ��
	�����м�Ϊ����ذ����
	�����ȷ�Ϊ�����ȷ���
	�����ַ�Ϊ���߲�˿�֣�
	�Ա����� Ů��
HELP
   );
   return 1;
}
