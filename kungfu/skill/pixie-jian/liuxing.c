// hero ����������
// 19991002001
#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIW"����������"NOR;}

int calc_damage(int,int,object,object);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total; 
        
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("�����������С�ֻ����ս��ʱʹ�ã�\n");

        if(!me->query("quest/pxj/super2/pass") )
                return notify_fail("��Ա�а����������δ��⣬����ʹ�á����������С���\n");

        //if(me->query("quest/pxj/super2/pass") )
          //      return notify_fail("��Ա�а����������δ��⣬����ʹ�á����������С���\n");

        if( !objectp(weapon=me->query_temp("weapon")) ) {
                        
                        return notify_fail("������������������á����������С���\n");
        }
        if (weapon->query("skill_type") != "sword"
			|| me->query_skill_mapped("dodge") != "pixie-jian"
			|| me->query_skill_mapped("parry") != "pixie-jian"
			|| me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("�����ڼ������ԣ��޷�ʹ�ñ�а����\n");
        
        if( (int)me->query_skill("pixie-jian", 1) < 350 )
                return notify_fail("��ı�а������������������ʹ�á����������С���\n");

		if( (int)me->query_skill("sword", 1) < 350 )
                return notify_fail("��Ļ�����������������������ʹ�á����������С���\n");
      
        if((int)me->query("max_neili", 1) < 4000) 
                return notify_fail("������������Ϊ�еͣ�����ʹ�á����������С���\n"); 

        if((int)me->query("jingli", 1) < 1000)
                return notify_fail("�����ھ������㣬����ʹ�á����������С���\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("�������������㣬����ʹ�á����������С���\n");      

        if(me->query("gender")=="����"||me->query("gender")=="Ů��") 
                return notify_fail("ֻ�ж��ñ�а��������������ˣ�����ʹ�á����������С���\n");      
      
        me->add("jingli",-200);
        me->add("neili",-400);

        message_vision(HIW"$N��������ȣ��������ת��$n����ǰ��˲��һ�����ݣ���������$n����󣬼��������ӳ�һƬ��Ӱ��״�����ǲ��á�\n"
		+"$n������ǰ�������������������硣\n"NOR,me,target);
		
        if(random((int)me->query_skill("pixie-jian",1))> (int)target->query_skill("parry",1)/3
          ||random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/2
          ||(!userp(target)&& target->is_busy()) )
		{
                me->add("neili",- random(400)-400 );
                me->add("jingli",-random(200)- 200);
                total = 0;
				i = calc_damage((int)me->query_skill("pixie-jian",1),(int)me->query_skill("sword",1),me,target);
                total += i;
				if (me->query("gender")=="����" && random(me->query("dex"))>45)
				{
					//������45�������������
					if (userp(me)&&!userp(target)) total=total+i*(int)me->query("dex")/25;
				    else total=total+random(total/5);
				  
					message_vision(BYEL"$N��������,��������ָ����$n��ȻһЦ����������֮������ʱ��$n��������һ����\n",me,target);
				}
                msg=CYN "\n$Nʹ��һ�С�"HIY"���Ǿ���"CYN"����������΢ǰ�㣬���·�����ȫ���̳�һ��������һƬ���⣡\n"+
                           "$n���Ѿ�����$N����ߣ�������Ʈ����Ϊʵ����$n����ʤ����\n"NOR;
               
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",total));
                
                
                if(userp(me) && me->query("env/damage"))
				   tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ total+ WHT"�㹥���˺���\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ total+ WHT"���˺���\n"NOR); 
				if (me->query("gender")!="����") total=1000;

				target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/8 , me);
                
				result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "С��Ѩ" );
                
				msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
				//�ڶ���

                msg =RED "\n$Nʹ��һ�С�"HIW"��������"RED"������׹һ�������������Եأ���˲�䱬����һƬ���õĽ���\n"+
                         "ȫ��ն��$n��û�����һЩ��λ����������ѵ���ʹ��$N��ʱ�����ٳ���\n"NOR;

                i = calc_damage((int)me->query_skill("pixie-jian",1),(int)me->query_skill("force",1),me,target);
                total += i;
                //if (userp(me)&&!userp(target)) i=total;
                
                if(userp(me) && me->query("env/damage")) 
		          tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ total+ WHT"�㹥���˺���\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ total+ WHT"���˺���\n"NOR); 
      			
				if (me->query("gender")!="����") total=1000;

                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/8 , me);
                
				result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "С��" );
                result = replace_string( result, "$w", weapon->query("name") );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
				//������
                msg =YEL "\n$N���ټ��㣬�����ڿգ�һ��һ����Χ��$n����ʩչ����ʮ���������ǡ�"HIC"���Ƿ���"YEL"������ʽ��\n"+
                         "��Ӱ��磬���ⶶ�����������ļ����£���˸��亮�⣬����$n����ǰ������Ѩ��\n"NOR;

                i = calc_damage((int)me->query_skill("pixie-jian",1),(int)me->query_skill("dodge",1),me,target);
                total += i;
				//if (userp(me)&&!userp(target)) i=total;
                if (me->query("gender")!="����") total=1000;
				if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",total));
                

                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/8 , me);
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
                me->start_perform(4,"�����������С�");
        }
        else {
                msg = WHT "\n$NٿȻʩչ�⡸"HIY"����������"WHT"����$n����һ�����㿪�������������С�\n"NOR;
                
                message_vision(msg,me,target);

                me->start_busy(1);
                me->start_perform(1,"�����������С�");
        }

        return 1;
}

int calc_damage(int skill,int skill2,object me,object target)
{
        int i;

            i = (random(skill+skill2)*2-(int)target->query_skill("parry",1))*6;
            if (i<0) i = -i;
            
			i += random(i*1/5);
            if( i < (skill2*5)) i = (int)target->query("max_qi",1)/3;
            
			if (userp(me)&&!userp(target))
				i=i;
				//i=i*1.2;
            if(userp(target)) i = i/2;         
            if (me->query("gender")!="����") i=i/10;
           
            return i;
}

int help(object me)
{
   write(WHT"\n��а����֮��"HIR"����������"WHT"����"NOR"\n");
   write(@HELP
	��������˽�������Ҫ��һ��а����֯������ȫƾ���˺ö�
	���г����似�������������а�����������ν�����������
	�ľ��������������������ְ汾�������ڱ�а���������ɡ�
	���������ơ�
	�����������С��������ñ�а���������������Է�����
	�����Է���������磬���ǲ��ã�����һ�г��䲻��ĺ��У�
    �������Թ��󷽿ɷ����������������������45������
	�ٴ�������

	ָ�perform sword.liuxing

Ҫ��
	��ǰ���� 1800 ���ϣ�
	������� 4000 ����
	��ǰ���� 1000 ����
	��а���� 350 ���ϣ�
	�������� 350 ���ϣ�
	�����Ṧ 350 ���ϣ�
	������ 60  ���ϣ�
	�����Ṧ��а����
	�����мܱ�а������
	����������а������
	���ֳֽ�������;

HELP
   );
   return 1;
}
