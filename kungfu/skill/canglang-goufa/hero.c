// hero Ӣ������
// 19991002001
#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIR"Ӣ������"NOR;}

int calc_damage(int,int,object,object);
int perform1(object me,object target,object weapon);
int perform2(object me,object target,object weapon);
int perform3(object me,object target,object weapon);


int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total,skill; 
        skill=me->query_skill("canglang-goufa",1);
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("��Ӣ�����С�ֻ����ս��ʱʹ�ã�\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("��Ӣ�����С�ֻ�а��˽���������ã�\n");

        if( !objectp(weapon=me->query_temp("weapon"))||weapon->query("skill_type")!="hook" ) {
                          
                return notify_fail("��������Ź������������á�Ӣ�����С���\n");
        }
     
        
        if( (int)me->query_skill("huagu-mianzhang", 1) < 500 )
                return notify_fail("��Ļ������ƻ���������������ʹ�á�Ӣ�����С���\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("ֻ��ʹ�û�������ʱ����ʹ�á�Ӣ�����С���\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 500 )
                return notify_fail("��������ȷ�����������������ʹ�á�Ӣ�����С���\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
                return notify_fail("ֻ��ʹ�������ȷ�ʱ����ʹ�á�Ӣ�����С���\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 500 )
                return notify_fail("��Ĳ��˹�������������������ʹ�á�Ӣ�����С���\n");

        if (me->query_skill_mapped("hook") != "canglang-goufa")
                return notify_fail("ֻ��ʹ�ò��˹���ʱ����ʹ�á�Ӣ�����С���\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 500 )
                return notify_fail("��Ķ����󷨹������㣬�����á�Ӣ�����С���\n");

       
        if((int)me->query("max_neili", 1) < 4000) 
                return notify_fail("������������Ϊ�еͣ�����ʹ�á�Ӣ�����С���\n"); 

        if((int)me->query("eff_jingli", 1) < 2500) 
                return notify_fail("�����ھ�����Ϊ�еͣ�����ʹ�á�Ӣ�����С���\n"); 

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�á�Ӣ�����С���\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("�������������㣬����ʹ�á�Ӣ�����С���\n");      

        if(me->query("gender")!= "����") 
                return notify_fail("ֻ�����˲���ʹ�á�Ӣ�����С���\n");      

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��������ִ�������ʹ�á�Ӣ�����С���\n");

        me->add("jingli",-100);
        me->add("neili",-200);

        msg = HIR"$N��$n��������֮����ƴ��ȫ��ʹ�����������֮����������Ӣ�����С�\n"NOR;
		msg += HIR"\n$N˫���趯"+weapon->query("name")+HIR",�ܲ�͸�磬˲��ʹ�������ཱུ��������³���������������ٶ������������\n"NOR;
    
		if(random((int)me->query_skill("canglang-goufa",1))*8/5 > (int)target->query_skill("parry",1)
          ||random((int)me->query("combat_exp"))*8/5 > (int)target->query("combat_exp")
          ||(!userp(target)&& target->is_busy()) )
		{
                me->start_busy(1);
                me->add("neili",- random(400)-400 );
                me->add("jingli",-random(200)- 200);
                total = 0;
				i = calc_damage((int)me->query_skill("huagu-mianzhang",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
				if (me->query("gender")=="����" && random(me->query("str"))>35)
				{
					
					if (userp(me)&&!userp(target)) total=total+i*(int)me->query("str")/35;
				    else total=total+random(total/2);
				  
					//message_vision(BYEL"$N��������,��ȻһЦ����ʱ��$n��������һ����",me,target);
				}
                msg += HIR "\n$Nʹ��һ�С�"HIY"����ٶ�"HIR"����һ����ɦ$nҸ�׼�ȪѨ���������֮�ʣ���һ��ͬ\n"+
                           "ʱ����$n���С��Ѩ������ˤ����ϡ�\n"NOR;
               
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                
                if (total>6000) total=6000+random(1000);
               
                if(userp(me) && me->query("env/damage"))
				   tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ i+ WHT"�㹥���˺���\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ i+ WHT"���˺���\n"NOR); 
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/4 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "С��Ѩ" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
				COMBAT_D->do_attack(me,target,weapon,3);
		}
		//�������ӽ���		
		if (me->query_skill_mapped("strike")=="huagu-mianzhang"
			&& me->is_fighting(target)
			&& me->query("quest/sld/clgf/canglang/pass"))
		{

			
					message_vision(YEL"$N�������������֣�ת����$n�ĳ�һ�����ᾢ�����ǡ�"HIR"��������"YEL"������ʽ��\n"NOR,me,target);
					message_vision(YEL"$nֱ��һ������ľ��������������Լ���й����㴫����\n"NOR,me,target);

					me->add_temp("apply/attack",skill/2);
					me->add_temp("apply/damage",skill/4);
					me->add_temp("apply/strike",skill/4);
					weapon->unequip();

					me->prepare_skill("strike", "huagu-mianzhang");
					COMBAT_D->do_attack(me,target,weapon,3);//�ڶ���
					
					me->add_temp("apply/attack",-skill/2);
					me->add_temp("apply/damage",-skill/4);
					me->add_temp("apply/strike",-skill/4);
					weapon->wield();
                
		}	
				
				
		if (me->is_fighting()&& objectp(target))
			perform1(me,target,weapon);
		return 1;

}
//no 2��ʽ


int perform1(object me,object target,object weapon)
{
	string msg,result;
	int i,total,skill;
        skill=me->query_skill("canglang-goufa",1);

	
			

                msg =HIR "\n$Nʹ��һ�С�"HIW"³�����"HIR"�������ȼ�װ��$nߵͷ��ͻȻһ��������������$n����\n"+
                         "�������ֻһ���ƣ�����ץ��$n�ҽ����ף����ֱ��������$nС����һ��������$nͷ�½��ϣ�\n"+
                         "����������\n"NOR;

                i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
                //if (userp(me)&&!userp(target)) i=total;
                if (random(me->query_str())>target->query_str()/2)
                {
					message_vision(HIC"$nһ��С��Ϊ��������ס���ֽŲ��ܶ������������ѡ�\n"NOR,me,target);
					target->apply_condition("no_force",2);
					target->add_busy(2);
                }
                if(userp(me) && me->query("env/damage")) 
		          tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ i+ WHT"�㹥���˺���\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ i+ WHT"���˺���\n"NOR); 
                
				if (total>7000) total=7000+random(1000);

                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "С��" );
                result = replace_string( result, "$w", weapon->query("name") );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
				
				if (me->query_skill_mapped("leg")=="shenlong-tuifa" 
					&& me->is_fighting(target)
					&& me->query("quest/sld/clgf/canglang/pass"))
                {
					message_vision(HIG"$N�ڷ�Ծ$nͷ��֮�ʣ������ȷ���Ȼ������ת����$nС�Ȳ�λ��Ȼɨȥ�����ǡ�"HIR"��ɨ�㹦"HIG"��������\n"NOR,me,target);
					message_vision(YEL"���ȷ���ʽֻ��һ�У���ȴ����������,�Ʋ��ɵ���\n"NOR,me,target);

					me->add_temp("apply/attack",skill/2);
					me->add_temp("apply/damage",skill/4);
					me->add_temp("apply/leg",skill/4);
					weapon->unequip();
					me->prepare_skill("strike");
					me->prepare_skill("leg", "shenlong-tuifa");
					COMBAT_D->do_attack(me,target,weapon,3);//�ڶ���
				//	COMBAT_D->do_attack(me,target,weapon,3);//3
					me->add_temp("apply/attack",-skill/2);
					me->add_temp("apply/damage",-skill/4);
					me->add_temp("apply/leg",-skill/4);
					me->prepare_skill("leg");
					me->prepare_skill("strike", "huagu-mianzhang");
					weapon->wield();
                }
		if (me->is_fighting()&& objectp(target))
			 perform2(me,target,weapon);
		return 1;


}

int perform2(object me,object target,object weapon)
{
	string msg,result;
	int i,total,skill;
        skill=me->query_skill("canglang-goufa",1);



                msg =HIR "\n$Nʹ��һ�С�"HIC"���ཱུ��"HIR"����������ײ��ʮָ��$n�ؿ���ץ���������֮�ʣ�\n"+
                         "ͻȻһ����������������Ծ��˫��һ�֣�������$n��ͷ��ͬʱ˫��Ĵָѹס$n\n"+
                         "̫��Ѩ��ʳָ��ü����ָ���ۡ�\n"NOR;

                i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
				//if (userp(me)&&!userp(target)) i=total;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ i+ WHT"�㹥���˺���\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ i+ WHT"���˺���\n"NOR); 
               
				if (total>8000) total=8000+random(1000);

                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "ͷ��" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
                
               
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�ܹ������"RED+ total+ WHT"�㹥���˺���\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ��������ܹ������"RED+ total+ WHT"���˺���\n"NOR);  
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));               
				//����������
				if (me->is_fighting()&& objectp(target)&& me->query("quest/sld/clgf/canglang/pass"))
					perform3(me,target,weapon);
      
				me->start_perform(5,"��Ӣ�����С�");
                me->start_busy(1+random(3));                    

        return 1;
}

int perform3(object me,object target,object weapon)
{
		
		int skill;
        skill=me->query_skill("canglang-goufa",1);
        if (!objectp(weapon))
			return 1;    
		message_vision(HIW"$NӢ������ʹ�꣬�����⾳���ڣ���������������չ���̲�ס��Хһ����\n����"+weapon->query("name")+HIW"˳�������ó�һ�ɲ������⣬��ʽ��ʱ��������ޱȡ�\n"NOR,me,target);
		me->add_temp("apply/attack",skill/2);
		me->add_temp("apply/damage",skill/4);
		me->add_temp("apply/hook",skill/4);
				//	message_vision(HIC"��һ�У�"NOR,me,target);
		COMBAT_D->do_attack(me,target,weapon,3);//�ڶ���
		if (me->query("str")>34 && me->query_temp("sld/wudi2")) 
		{
			message_vision(HIR"$N�����󷨷������������������ľ�����������ʽ������ʱ������\n"NOR,me,target);

			target->set_temp("must_be_hit",1);
			me->add_temp("apply/damage",skill/5);
			
			COMBAT_D->do_attack(me,target,weapon,3);
			COMBAT_D->do_attack(me,target,weapon,3);
			me->add_temp("apply/damage",-skill/5);

			target->delete_temp("must_be_hit");

		}
		me->add_temp("apply/attack",-skill/2);
		me->add_temp("apply/damage",-skill/4);
		me->add_temp("apply/hook",-skill/4);
				
				
		return 1;
}

int calc_damage(int skill,int skill2,object me,object target)
{
        int i;

            i = (random(skill+skill2)*2-(int)target->query_skill("parry",1))*10;
            if (i<0) i = -i;
            i += random(i*2/5);
            if( i < (skill2*5)) i = (int)target->query("max_qi",1)/3;
            if (userp(me))
				i=i*1.5;
            if(userp(target)) i = i* 2/5;         
            
            return i;
}
int help(object me)
{
   write(WHT"\n���˹�����"HIR"Ӣ������"WHT"����"NOR"\n");
   write(@HELP
	���˹�������������������������Լ�����ѧ�似
	��������������һ�׹����似��ȥ���ͼ򣬹���Ϭ
	��������ʤ����������ڱ����ϴ��е��Ӷ��ԣ���
	�Ƿǳ�ʵս�Ĺ�������Ӣ���������ǵ��͵Ľ���
	�似�������Լ��ߵı����ͷḻ��ս�����飬�Ե�
	��ʵʩ���е��͵Ĵ����
	ע�⣺�����������35�������ٴ����ӡ�

	ָ�perform hook.hero
	
Ҫ��
	�������Ҫ�� 4000 ���ϣ�
	�����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 800 ���ϣ�
	�������Ƶȼ� 500 ���ϣ�
	�����ȷ��ȼ� 500 ���ϣ�
	���˹����ȼ� 500 ���ϣ�
	�����󷨵ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	�����ұ��Ʒ�Ϊ�������ƣ�
	�����ȷ�Ϊ�����ȷ���
	��������Ϊ���˹�����
	�����ڹ�Ϊ�����󷨣�
	�ֳֹ���������
	�Ա����� ���ԡ�
HELP
   );
   return 1;
}
