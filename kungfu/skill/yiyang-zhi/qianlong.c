//yiyang-zhi's perform qianlong
//Ǳ������
//COOL@SJ,20000401

#include <ansi.h>
inherit F_SSERVER;
void yyzql_attack(object me,object target,int count);
 
int perform(object me, object target)
{       
        string msg;
        int skill,ap,dp;
		skill=me->query_skill("yiyang-zhi",1);
        
		if( !target ) target = offensive_target(me);
		
		if( !target 
         || !target->is_character()
         || !present(target,environment(me)) )
                return notify_fail("��Ǳ�����á���\n");
        if( !living(target) )
        	return notify_fail("�Է��Ѿ��ι�ȥ�ˡ�\n");
		if( !me->is_fighting(target) )
 				return notify_fail("��ֻ�ܶ�ս���еĶ��ֳ���Ǳ�����á���\n"); 
 		//ѹ�ƣ�����
		if( target->query_temp("yyz_ql/recive") )
 			return notify_fail("�����Ѿ����ܲ�����ġ�Ǳ�����á������ˡ�\n"); 
 		
            
        if( me->query_temp("weapon") )
                return notify_fail("ֻ�п��ֲ���ʩչ��Ǳ�����á���\n"); 

        if( (int)me->query_skill("yiyang-zhi", 1) < 300 ||
            (int)me->query_skill("finger", 1) < 300 )
                return notify_fail("���еĹ��򻹲�����죬����ʹ�á�Ǳ�����á���\n");

        if(!me->query_skill("kurong-changong", 1))
           	if(me->query_skill("qiantian-yiyang", 1) < 300)
                	return notify_fail("�������ڵ��ڹ���Ϊ��ʹ������Ǳ�����á���\n");        
         
        if (me->query_skill_mapped("force") != "kurong-changong" )
            	if (me->query_skill_mapped("force") != "qiantian-yiyang")
                	return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

        if (me->query_skill_prepared("finger") != "yiyang-zhi"
			|| me->query_skill_mapped("parry") != "yiyang-zhi"
           || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("�������޷�ʹ����Ǳ�����á����й�����\n");                                                                                 
      
        if( (int)me->query("max_neili") < 4000 )
                return notify_fail("������������Ϊ̫��������ʹ�á�Ǳ�����á���\n");
		if( (int)me->query("neili") < 1000 )
                return notify_fail("��ĵ�ǰ������Ϊ̫��������ʹ�á�Ǳ�����á���\n");
		if( (int)me->query("jingli") < 1000 )
                return notify_fail("��ĵ�ǰ������Ϊ̫��������ʹ�á�Ǳ�����á���\n");
   		if (me->query_temp("yyz_ql"))
				return notify_fail("������ʹ�á�Ǳ�����á�������\n"); 
    
 		message_vision(HBGRN+HIW"\n$N����������ת������һ��ָ������ʼ��������ڴ���һ��ָ������Ǳ�����á�����ʽ��\n"NOR,me);
	
        
        if ((string)me->query("class")=="bonze")
         	message_vision(WHT "\n$N��Ȼ�ͻ���һ����"+target->name()+WHT"`~~~~`,����������ǧ����ħ������������˿�ش�����\n"NOR,me,target);    
		else message_vision(WHT "\n$N��Ȼ���һ����"+target->name()+WHT",��������������������$n˫�������ˡ����졣\n"NOR,me,target); 
     
        me->set_temp("yyz_ql",skill);
		
		me->add("neili",-100-random(1000));
        me->add("jingli",-100-random(500));
       	

		message_vision(HBWHT+HIR"$N��һָ���ľ��˴�����Ԫ����ֻ�����Լ�ƣ��֮���������˾���һ��ͻȻ���˵���ľһ�㡣\n"NOR,me);
		
        //Ŀ������������
		call_out("yyzql_attack",1,me,target,(int)skill/100);
		
		if ((int)me->query("yyz/degree")>4 && me->query_skill("yiyang-zhi",1)<450)
        {
			me->start_perform(2,"Ǳ������");
        }
		/*else
			me->start_perform(1,"Ǳ������");
			*/
       	
		return 1;
}
//�����Ƴ���

void yyzql_attack(object me,object target,int count)
{
	int skill,damage,ap,dp;
	if (!me) return;
	skill=me->query_skill("yiyang-zhi",1);
	damage=skill+me->query_skill("qiantian-yiyang",1)+me->query_skill("buddhism",1);
	damage=damage*2+random(damage);
	ap=me->query("combat_exp")/100000;
    //�뿪����
	if (count<0
		||!objectp(target)
		|| !me->is_fighting(target)
		|| me->query_temp("weapon")
		|| me->query_skill_mapped("finger")!="yiyang-zhi")
	{	
		
		me->delete_temp("yyz_ql");
		message_vision(HIC"\n\n$N�³�һ����������ɫ�ʲ԰�֮ɫ����Ȼ������һ�кķѲ��پ�����\n"NOR,me);
		me->add_busy(2);
		me->add("neili",-600);
		me->add("jingli",-400);
		me->start_perform(4,"Ǳ������");
		return;
	}
	dp=target->query("combat_exp")/100000;
    
	


	
	switch (random(5))
	{
		case 0:
			//�������һ��
			message_vision(HIR"$N�ۼ�$n����ʶ�ĸ񵲣���ȻһЦ��˳������$n��������$nǰ����ʮ������Ѩ��������ָ���С�\n"NOR,me,target);
		    message_vision(CYN "$n���˼��أ���æ�����ֵ���ͻȻ֮�䣬$nü��Ѩһ����ȣ�����������ֱ��������\n"
						+"���������Ӷ�������������Ѹ������һ��������ڴ�������Ϊһ���ڳ�������Ϊ����\n"
						+"$N����һ�м���������;����Ϊָ���͡���һ����ָ���ƿն�����\n\n"NOR, me,target);     
			target->add_busy(2);
			me->add_temp("apply/finger", skill/3);
			me->add_temp("apply/damage", skill/3 );
			target->set_temp("must_be_hit",1);
			COMBAT_D->do_target(me, target, 0, userp(me)?3:1);
			target->delete_temp("must_be_hit");
			me->add_temp("apply/finger", -skill/3);
			me->add_temp("apply/damage", -skill/3);
			break;
		case 1:
			//�Ʒ�
			message_vision(HIR"$Nһ��ָ����һ���Ӵ���$n��Ѩλ�����紺ѩ���࣬�������뵽$n�����磬���߲�Ϣ��\n"NOR,me,target);
			
			if (random(me->query_int(1))>target->query_int(1)/2 && !target->query_temp("yyz_ql/recive"))
			{
				message_vision(HIY"$n������һָ���پ��������飬��������������������������\n"NOR,me,target);
				target->add_temp("apply/dodge",-skill/3);
				target->add_temp("apply/defense",-skill/3);
				target->add_temp("apply/attack",-skill/2);
				target->set_temp("yyz_ql/recive",skill);
				//���ܳ�pfm
				target->apply_condition("no_perform",2);
				call_out("yyzql_back",skill/30,target);
			}else{
				message_vision(HIW"$n����ҧ���Լ���⣬��������״̬����Ȼ�����Զ㿪��\n"NOR,me,target);

			}
			break;
		case 2:
			//�����������˷���
			
			//call_out("yyzql_target2");
			message_vision(RED"$N�ͺ�һ����һ��ָ������ӿ���ȣ�$nֻ����ɾ����������뵽�Լ�����֮�С�\n"NOR,me,target);
			if (random(me->query_skill("force",1))>target->query_skill("force",1)/2
				||random(me->query("neili"))>target->query("neili")/2)
			{
				message_vision(HBRED+HIW"��ɹ������������$n�ĵ���󣬷·𱻵�ȼ���Ƶã�$nֻ���Լ������Ĵ����ߣ������������ѡ�\n"NOR,me,target);
				target->apply_condition("no_exert",1+random(3));
				target->set("jiali",0);
				if (damage>target->query("neili"))
				{
					target->add("neili",-(int)target->query("neili")/2);
				}else
					target->add("neili",-damage);
				message_vision(HIY"$n��Ȼ����һ��ָ�����ˣ��۵�����һ����Ѫ��\n"NOR,me,target);
				target->receive_wound("qi",damage/3,me);
				target->apply_condition("yyz_hurt",2+random(2));
				
			}else {
				message_vision(HIG"$n��΢���˵����ˣ�����һ��������ת��������$N��������Ϯ��\n"NOR,me,target);
				me->add_busy(1);

			}
			break;
		case 3:
			//�ƾ������˾�
			message_vision(HIW"$nֻ��ü��ӡ�ü���һ��������Ҫ���Լ���˫ü˺��һ�㡣\n"NOR,me,target);

			message_vision(WHT "$n����һ��������ʶ��$n��һ���䣬ɲ�Ǽ��������⣬���ڶ�ǰ,ȴ������������һ����$Nһָ������$n�����ġ�\n"NOR, me, target);

			if( random(me->query_skill("finger",1))>target->query_skill("parry",1)/2
				||random(ap)>dp/2)
			{
        		if (random(target->query("kar"))<15 && !userp(target))
				{
					message_vision(YEL"$n��Ȼ�����Ƶ�ס��$N����һָ����һ�����������Ʊ�Ѹ������ü�ģ�����������$nֻ��ͷ�����ǣ���ǰһ�ڡ�\n"NOR,me,target);
					target->unconscious();
					
				}
				
        		target->receive_damage("jingli",1000+random(3000),me);
				target->receive_damage("jing",500+random(2000),me);
				target->add_busy(2);
        		//
        		me->add("neili",-random(1000));
        		me->add("jingli",-random(500));
			}else {
				message_vision(HIY"$N��һָ���У�����ԴԴ���ϵ����룬ȴ����$n����տ���Ҳ��$N���һ������æ��ֹ����һʽ��\n"NOR,me,target);
				me->add_busy(1);
			}
			break;
		case 4:

			if(random(2))
			{
     			message_vision(HIY "\n\n$n����$N��Ȼʹ��һ��һ��ָ��������ף�ָ�籾����Ϊ��΢��һ�����Լ��Ļ������������Ϊ�񾢣���������һ����\n"+
                "���ƶ��룬$nһ��֮�£�ָ����ֱ��ü�ģ�$n���ֲ�������һ�����С�\n"NOR, me, target);   
         		target->apply_condition("no_exert", target->query_condition("no_exert") + 5);
			} else
			{
                message_vision(WHT "\n$n����$N��Ȼʹ��һ��һ��ָ��������ף�ָ�籾����Ϊ��΢��һ�����Լ��Ļ������������Ϊ�񾢣�\n"+
											"��������һ�������ƶ��룬$nһ��֮�£�ָ����ֱ��ü�ģ�$nӦ�����٣����Ƶ�������֮��������������\n"+
											"�����Ʊ����ڶ�ǰ����ž����һ����ָ�������������ڡ�$n�������˾�ȫ��������ָ�磬�����ּ���֧�ţ�\n"
											+"����һ��ָ�磬�������أ��������ƿ�֮��һ�α�һ�θ��ң���Ȼ��һС�����ھ�͸��ü��ҪѨ��\n"NOR, me, target);        
                target->apply_condition("no_exert", target->query_condition("no_exert") + 3);
                target->apply_condition("no_perform", target->query_condition("no_perform") + 3);
				target->receive_damage("qi",damage,me);
			}

   
			if ((int)random(me->query("neili"))>(int)target->query("neili")/2)
			{
	         	message_vision(RED "$n��Ȼ�����Ƶ�ס����һָ����һ�����������Ʊ�Ѹ������ü�ģ�$nֻ��ͷ������,һ��ѣ�Ρ�\n"NOR,me,target);
        		target->receive_damage("qi",damage,me);
        		target->receive_wound("qi",damage/3,me);
   
        		message_vision( HIY"$Nһָ���У�����ԴԴ���ϵ����룬һ����һ���Ĺ���Ϯ������ӿ���ȡ�\n"NOR,me);
        		me->add("neili",-random(2000));
        		me->add("jingli",-random(1000)); 
        		
			}
	
			break;
	
	 }
	

	call_out("yyzql_attack",1,me,target,count-3);

}




//Ǳ���ָ�����
void yyzql_back(object target)
{
	int skill;
	if (!target) return;
	skill=target->query_temp("yyz_ql/recive");
	
	message_vision(WHT"$N����һ���������ڲ���������ǹ�һ��ָ����������ɢ�ˣ�\n"NOR,target);
	target->add_temp("apply/dodge",skill/3);
	target->add_temp("apply/defense",skill/3);
	target->add_temp("apply/attack",skill/2);
	target->delete_temp("yyz_ql/recive");
	return;
}
string perform_name() {return HIC"Ǳ������"NOR;}

int help(object me)
{
   write(HIY"\nһ��ָ֮��"HIC"Ǳ������"WHT"����"NOR"\n\n");
   write(@HELP
	
	Ǳ�����ã����Ǵ����һ��ָ������ʩչһ��ָ�����������ж�
	��Է���ʱ�о�����������һ��ָ�����ڶԷ������ͷź󣬶Է���
	��ʱ������ʧ���������;�����������Ϊ�˹��������ڹ��˵е���
	ʽ������Լ�Ҳ��Ĵ����������Է����ǹ���̫�������п��ܳ���
	�������Ե�������֮��֮��һ��ָ��������Ʒ���ɡ�

	ָ�perform finger.qianlong

Ҫ��: 
	����������� 4000 �����ϣ�
	��ǰ�������� 1000 �����ϣ�
	��ǰ�������� 1000 �����ϣ�
	һ��ָ�ĵȼ� 300 ���ϣ�
	�����ڹ��ȼ� 300 ���ϣ�
	�����ڹ��ȼ� 300 ���ϣ�
	����ָ��Ϊһ��ָ��
	���֣���һ��ָ��

HELP
   );
   return 1;
}
