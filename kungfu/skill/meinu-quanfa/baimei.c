// baimei.c by sohu@xojh


#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return MAG"���ĺ���"NOR;}

int calc_damage(int,int,object,object);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total,mp,tp; 
        mp=me->query_per();tp=target->query_per();
        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("�����ĺ�����ֻ����ս��ʱʹ�ã�\n");
 
        if( me->query("per")<28 )                              
             return notify_fail("���������ò��ʵ��ª��ʩչ�����ĺ�����ֻ��������Ż��\n");  

        if( objectp(weapon=me->query_temp("weapon")) )                              
                return notify_fail("�����������������޷�ʩչ�����ĺ�������\n");               
        
        if( (int)me->query_skill("meinu-quanfa", 1) < 100 )
                return notify_fail("�����Ůȭ������������������ʹ�á����ĺ�������\n");
		if( (int)me->query_skill("cuff", 1) < 100 )
                return notify_fail("��Ļ���ȭ������������������ʹ�á����ĺ�������\n");

        if (me->query_skill_mapped("cuff") != "meinu-quanfa"||me->query_skill_prepared("cuff") != "meinu-quanfa")
                return notify_fail("ֻ��ʹ����Ůȭ��ʱ����ʹ�á����ĺ�������\n");
		if (me->query_skill_mapped("parry") != "meinu-quanfa")
                return notify_fail("ֻ��ʹ����Ůȭ��ʱ����ʹ�á����ĺ�������\n");

        if( (int)me->query_skill("yunu-xinjing", 1) < 100 )
                return notify_fail("�����Ů�ľ�����������������ʹ�á����ĺ�������\n");       

        if((int)me->query("jingli") <500)
                return notify_fail("�����ھ������㣬����ʹ�á����ĺ�������\n");       
        if((int)me->query("max_jingli") <1000)
                return notify_fail("��������������㣬����ʹ�á����ĺ�������\n");       

        if((int)me->query("max_neili") < 1500) 
                return notify_fail("����������������㣬����ʹ�á����ĺ�������\n");      		
        if((int)me->query("neili") < 800) 
                return notify_fail("�������������㣬����ʹ�á����ĺ�������\n");      	
        if( me->query_skill_mapped("force") != "yunu-xinjing")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��Ů�ľ���ִ�������ʹ�á����ĺ�������\n");
        me->add("jingli",-100);
        me->add("neili",-random(200));
        if (me->query("gender")=="����"&&me->query("per")>=28)
        {
			msg=HIG"$N��Ȼ����Ϊ���ӣ����������ò��ʵ������Ů�ӣ�������Ů��״������ǳЦ�����ο��֮״��\n"+
				"��$n��΢��������֮�ʣ�ʩչ����Ĺ�ɾ��������ĺ�������\n"NOR;
        }
        msg = HIC"$N����ǳЦ�����ο�������������$n��������֮����ʩչ����Ĺ�ɾ��������ĺ�����"NOR;
        if(random((int)me->query_skill("meinu-quanfa",1)) > (int)target->query_skill("parry",1)/2
          ||random((int)me->query("combat_exp"))> (int)target->query("combat_exp")/2
          ||target->is_busy() ){
                me->start_busy(1);
                total = 0;
                msg +=MAG "\n\n$Nʹ��һ�С�"HIM"�ļ��麺"MAG"����������Ť������Ծ����У�˫�ƻ��裬�����ָ���գ�����ʮ�˴�����$n��С����\n"+
					"����������Ůȭ�����������һ�У�һ���������绢������ǰ���εε�ģ��ȫȻ��ͬ��\n"NOR;
                i = calc_damage((int)me->query_skill("meinu-quanfa",1),(int)me->query_skill("yunu-xinjing",1),me,target);
				if (me->query("gender")=="Ů��"&&mp>tp&&me->query("per")>29) 
					i=i*me->query_per(1)/100;
                total += i;
               if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
			//��ѧ
				
				if (userp(target) && total>2000) total=2000+random(1000);
			   
                target->receive_damage("qi", total, me );
               // target->receive_wound("qi", total/6 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "����" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 

                msg =HIG "\n$Nʹ��һ�С�"HIM"Ƽ������"HIG"����������Ȼ������Բ�������һ��ܷܷ���֣�����$n�����ۣ�\n"+
                         "��û��$n��Ӧ������$N����������һת������ת��$n���Ҳ࣬��һָȴ��ָ����$n��̫��Ѩ��\n"NOR;

                //i = calc_damage((int)me->query_skill("meinu-qunfa",1),(int)me->query_skill("yunu-xinjing",1),me,target);
				//if (me->query("gender")=="Ů��"&&mp>tp&&me->query("per")>29) i=i*3/2;
                total += i/6;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
				
				if (userp(target) && total>2500) total=2500+random(1000);

                target->receive_damage("qi", total, me );
               // target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "�沿" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     

                msg =HIR "\n$Nʹ��һ�С�"HIB"��Ĺ�ľ�"HIR"����ֻ��$N����֧�ã���������ӳ������г�̾һ�������ּ���֮�⡣\n"+
                         "���б�Ϊ�������ʱ��������Ϊ��ʱ��Ƥ����֮�٣����������书��ɸ�����ȴ��������\n"NOR;

               // i = calc_damage((int)me->query_skill("meinu-quanfa",1),(int)me->query_skill("yunu-xinjing",1),me,target);
				//if (me->query("gender")=="Ů��"&&mp>tp&&me->query("per")>29) i=i*3/2;
                total += i/6;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
				
				if (userp(target) && total>3000) total=3000+random(1000);

                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/4 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "�ؿ�" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));
                me->start_perform(3,"�����ĺ�����");
        }
         else {
                msg +=MAG "\n\n$Nʹ��һ�С�"HIM"�ļ��麺"MAG"����������Ť������Ծ����У�˫�ƻ��裬�����ָ���գ�����ʮ�˴�����$n��С����\n"NOR;
                msg += "����$n������$N����ͼ��û���ϵ�������ææ���Ա�һ�������˹�ȥ��\n";
                msg =HIG "\n$Nʹ��һ�С�"HIG"Ƽ������"HIG"����������Ȼ������Բ�������һ��ܷܷ���֣�����$n�����ۣ�\n"+
                         "��û��$n��Ӧ����������������һת������ת��$n���Ҳ࣬��һָȴ��ָ����$n��̫��Ѩ��\n"NOR;
                msg += "$n����һ�������漴�侲�������ڿ�����һ��������$N���ţ�$Nֻ���ɿ����֡�\n";
                msg =HIR "\n$Nʹ��һ�С�"HIB"��Ĺ�ľ�"HIR"����ֻ��$N����֧�ã���������ӳ������г�̾һ�������ּ���֮�⡣\n"+
                         "���б�Ϊ�������ʱ��������Ϊ����֮�٣���ȴ��������\n"NOR;
                msg += "$n��$N��ס������Σ���ң���������סҪ����ͬʱ�߸�Ծ�𣬷�����ͷײ�أ���$Nײ�˳�ȥ��\n";
                message_vision(msg,me,target);
                me->start_busy(1+random(2));
                me->start_perform(4,"�����ĺ�����");
        }
        return 1;
}

int calc_damage(int skill,int skill2,object me,object target)
{
			int i;

            i = (random(skill+skill2)*2-(int)target->query_skill("parry",1))*10;
            if (i<0) i = -i;
            i += random(i/2);

            if(!userp(me)) i = i/3;

			return i; 
}

int help(object me)
{
   write(WHT"\n��Ůȭ����"MAG"���ĺ���"WHT"����"NOR"\n");
   write(@HELP
	Ϊ����������С���Ĺ����ʦ�ֳ�Ӣ������ȭ��ÿһ��
	����ģ��һλ�Ŵ���Ů����ǧ��������Ů���Ī�����
	����̬�������У��������Ƽ���ʫ�⣬�������ġ���
	��ҹ��������׹¥���ļ��麺�����ߵ��С�ľ���乭��
	�༧��ʫ���϶���ҩ���������ˡ�������ױ��Ƽ������
	�������ġ�����΢���������ǡ���ÿһ�ж�����һ����
	ʷ��ʣ�ʩչ�����򲽲��������������������������
	���л�����ʤ��������Դ�ȭ����ʤ���ַ����Ķ�����
	�����ޱȵĴ���͡�
	ע�⣺���Դ���40���Ժ����޵�������
	
	perform cuff.baimei
   
Ҫ��
	��ǰ����Ҫ�� 800 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	�����Ҫ�� 1000 ����
	�������Ҫ�� 1400 ���ϣ�
	��Ůȭ���ȼ� 100 ���ϣ�
	����ȭ���ȼ� 100 ���ϣ�
	��Ů�ľ��ȼ� 100 ���ϣ�
	������òҪ�� 27  ����
	������׼��ȭ��Ϊ��Ůȭ����
	�����м�Ϊ��Ůȭ��
	Ů�������ƣ�����ƫ����
		
HELP
   );
   return 1;
}
