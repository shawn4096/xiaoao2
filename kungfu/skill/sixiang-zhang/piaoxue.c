// piaoxue.c by sohu@xojh


#include <ansi.h>

inherit F_SSERVER;


int calc_damage(int,int,object,object);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total; 
       
        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("��Ʈѩ���ơ�ֻ����ս��ʱʹ�ã�\n");
         
        if( objectp(weapon=me->query_temp("weapon")) )                              
                return notify_fail("�����������������޷�ʩչ��Ʈѩ���ơ���\n");               
        
        if( (int)me->query_skill("sixiang-zhang", 1) < 100 )
                return notify_fail("��������ƻ���������������ʹ�á�Ʈѩ���ơ���\n");

        if (me->query_skill_mapped("strike") != "sixiang-zhang")
                return notify_fail("ֻ��ʹ��������ʱ����ʹ�á�Ʈѩ���ơ���\n");
	//	if (me->query_skill_mapped("parry") != "sixiang-zhang")
             //   return notify_fail("ֻ��ʹ���������м�ʱ����ʹ�á�Ʈѩ���ơ���\n");

        if( (int)me->query_skill("linji-zhuang", 1) < 100 )
                return notify_fail("����ټ�ׯ����������������ʹ�á�Ʈѩ���ơ���\n");       

        if((int)me->query("max_jingli", 1) < 1000 )
                return notify_fail("�����������㣬����ʹ�á�Ʈѩ���ơ���\n");       

        if((int)me->query("max_neili", 1) < 1200) 
                return notify_fail("�������������㣬����ʹ�á�Ʈѩ���ơ���\n");      		
        if((int)me->query("neili", 1) < 500) 
                return notify_fail("��ĵ�ǰ�������㣬����ʹ�á�Ʈѩ���ơ���\n");      		
        if( me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("��������ʹ�õ��ڹ�ͬ�ټ�ׯ��ִ�������ʹ�á�Ʈѩ���ơ���\n");
        me->add("jingli",-100);
        me->add("neili",-400);
        
        msg = HIW"$N����ǰ�ݣ����������˰�Բ�����ֳ��ƣ���ǰ�����Ƴ���ʩչ�������ɡ�Ʈѩ���ơ�������\n"NOR;
        if(random((int)me->query_skill("sixiang-zhang",1))> (int)target->query_skill("parry",1)/2
          ||random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/2
          ||target->is_busy() ){
                me->start_busy(1);
                total = 0;
                msg +=CYN "\n$Nʹ��һ�С�"HIW"Ʈѩ"CYN"����˫�Ʒ��裬����Ʈ�ݣ��������磬������������Ϣ�ľ�������$n��\n"NOR;
                i = calc_damage((int)me->query_skill("sixiang-zhang",1),(int)me->query_skill("linji-zhuang",1),me,target);
				if (me->query("class")=="bonze") i=i+me->query_skill("dacheng-fofa",1);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "����" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 

                msg =HIC "\n$Nʹ��һ�С�"WHT"����"HIC"��������ֱ��$n�й������д��գ���������Ȼ���Ʒ磬����$n���沿��\n"NOR;

                //i = calc_damage((int)me->query_skill("meinu-qunfa",1),(int)me->query_skill("linji-zhuang",1),me,target);
				if (me->query("class")=="bonze") i=i+me->query_skill("dacheng-fofa",1);
                total += i/5;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "�沿" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
               if (me->query("emjy/pass")				   
				   &&me->query_skill_mapped("hand")=="jieshou-jiushi"
			       &&me->query_skill_mapped("strike")=="sixiang-zhang"
				   &&me->query_skill_prepared("hand")=="jieshou-jiushi"
				   &&me->query_skill_prepared("strike")=="sixiang-zhang")
               {
                 msg =HIY "\n$Nʹ��һ�С�"HIB"�������"HIY"����һ���ĳ�����������ؿ�Ҳ�ã�����Ҳ�ã���ͷҲ�ã�����Ҳ�ã���ʽƽƽ������\n"+
                         "һ�ɲ��䣬������֮����ȫ�����Զ����ɾ�������Ϊ������\n"NOR;

               // i = calc_damage((int)me->query_skill("sixiang-zhang",1),(int)me->query_skill("linji-zhuang",1),me,target);
			    if (me->query("class")=="bonze") i=i+me->query_skill("dacheng-fofa",1);
                total += i/6;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "�ؿ�" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
				}
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));
                me->start_perform(3,"��Ʈѩ���ơ�");
        }
        else {
                msg +=CYN "\n$Nʹ��һ�С�"HIW"Ʈѩ"CYN"����˫�Ʒ��裬����Ʈ�ݣ��������磬������������Ϣ�ľ�������$n��\n"NOR;
                msg += "����$n������$N����ͼ��û���ϵ�������ææ���Ա�һ�������˹�ȥ��\n";
                msg =HIC "\n$Nʹ��һ�С�"WHT"����"HIC"��������ֱ��$n�й������д��գ���������Ȼ���Ʒ磬����$n���沿��\n"NOR;
                         "��û��$n��Ӧ����������һת������ת��$n���Ҳ࣬��һָȴ��ָ����$n��̫��Ѩ��\n"NOR;
                msg += "$n����һ�������漴�侲�������ڿ�����һ��������$N���ţ�$Nֻ���ɿ����֡�\n";
               // msg =HIY "\n$Nʹ��һ�С�"HIB"�������"HIY"����һ���ĳ�����������ؿ�Ҳ�ã�����Ҳ�ã���ͷҲ�ã�����Ҳ�ã���ʽƽƽ������\n"+
                 //        "һ�ɲ��䣬������֮����ȫ�����Զ����ɾ�������Ϊ������\n"NOR;
                //msg += "$n��$N��ס������Σ���ң���������סҪ����ͬʱ�߸�Ծ�𣬷�����ͷײ�أ���$Nײ�˳�ȥ��\n";
                message_vision(msg,me,target);
                me->start_busy(1+random(2));
                me->start_perform(4,"��Ʈѩ���ơ�");
        }
        return 1;
}

int calc_damage(int skill,int skill2,object me,object target)
{
			int i;

            i = (random(skill+skill2)*2-(int)target->query_skill("parry",1))*10;
            if (i<0) i = -i;
            i += random(i*2/5);            
            if(!userp(me)) i = i/2;
            return i; 
}
string perform_name(){ return HIW"Ʈѩ����"NOR; }

int help(object me)
{
   write(HIC"\n�����ơ�"HIW"Ʈѩ����"HIC"����"NOR"\n");
   write(@HELP
	�����ƾ�ѧ�Ƕ�����Ҫ�Ŀ����似�������е�������в���
	�ı��֣����Ͷ��ҵ�����һ������似���־�ʽ�����󣬻�
	����һ���̶ȵķ�Ծ�����⿪���Ҿ�������������ƻ��
	�����С�������ա���ʵ�ַ�Ծ��
	
ָ��: perform strike.piaoxue
	
Ҫ��
	����������� 1200 ���ϣ�
	��������� 1000 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	�����Ʒ��ȼ� 100 ���ϣ�
	�����Ʒ��ȼ� 100 ���ϣ�
	�ټ�ʮ��׮�ȼ� 100 ���ϣ�
	���������˷�ԭ������΢���ơ�
		
HELP
   );
   return 1;
}
