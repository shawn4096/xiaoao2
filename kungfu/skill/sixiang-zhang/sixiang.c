// piaoxue.c by sohu@xojh
//������ѧ�����Ϻ�������Դ������֮ͼ���仯��λ��������������
//[1]  ���Ʒ�����������������������ֱ仯���Ӷ��������Ʒ�������һ��ʩչ�����������˺����������У��޷������Ƿǳ�ʵ�õ������� [2] 
//sixiangyi.c ��������

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
                return notify_fail("�������⡹ֻ����ս��ʱʹ�ã�\n");
         
        if( objectp(weapon=me->query_temp("weapon")) )                              
                return notify_fail("�����������������޷�ʩչ�������⡹��\n");               
        
        if( (int)me->query_skill("sixiang-zhang", 1) < 200 )
                return notify_fail("��������ƻ���������������ʹ�á������⡹��\n");

        if (me->query_skill_mapped("strike") != "sixiang-zhang"
			||me->query_skill_prepared("strike") != "sixiang-zhang")
                return notify_fail("ֻ��ʹ��������ʱ����ʹ�á������⡹��\n");
	    if (me->query_skill_mapped("dodge") != "anying-fuxiang")
                return notify_fail("������ֻ��ʹ�ð�Ӱ�����Ṧʱ����ʹ�á������⡹��\n");

        if( (int)me->query_skill("linji-zhuang", 1) < 200 )
                return notify_fail("����ټ�ׯ����������������ʹ�á������⡹��\n");       

        if((int)me->query("max_jingli", 1) < 1000 )
                return notify_fail("�����������㣬����ʹ�á������⡹��\n");       

        if((int)me->query("max_neili", 1) < 1800) 
                return notify_fail("�������������㣬����ʹ�á������⡹��\n");      		
        if((int)me->query("neili", 1) < 500) 
                return notify_fail("��ĵ�ǰ�������㣬����ʹ�á������⡹��\n");      		
        if( me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("��������ʹ�õ��ڹ�ͬ�ټ�ׯ��ִ�������ʹ�á������⡹��\n");
        
		if (target->is_busy())
		{
                return notify_fail("�Է��Ѿ���æ�����У��Ͻ������ɣ�\n");   		

		}
		me->add("jingli",-100);
        me->add("neili",-400);
        
        message_vision(HIC"$N����ǰ�ݣ����������˰�Բ�����ֳ��ƣ���ǰ�����Ƴ���ʩչ�������������Ʒ�֮�������⡹������\n"NOR,me,target);
		message_vision(HIW"\n\n$N����֮�䣬����Ͷ��䰵�Ϻ������󣬱仯��λ�������������������仯��һ��ʩչ��$N���绨�к�����Ʈ��������\n "NOR,me,target);
        if(random((int)me->query_skill("sixiang-zhang",1))> (int)target->query_skill("parry",1)/2
          ||random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/2
          ||target->is_busy() )
		{
			message_vision(HIY"\n$N��������������ֱ仯���ں�����ʽ�Ͳ����У�$n�پ��Լ��������У��޷���������˷�����$N��Ӱ�ӡ�\n "NOR,me,target);
			if (!userp(target))
			{
				target->add_busy(3+random(3));
			}
			else target->add_busy(1);
			
			if (objectp(target)&&me->is_fighting(target))
				call_out("attack_damage",1,me,target);     
			  
		}else {
			message_vision(HIY"$n�����������Ժ�����֮ѧ������Ȼ���أ������б�а벽����ʱ�߳�$N��������Ӱ��\n"NOR,me,target);
			me->start_busy(1);
		}
		
		   

		if (me->query_skill("sixiang-zhang",1)<250)
			me->start_perform(2,"������");
        return 1;
}

int attack_damage(object me,object target)
{
		int i,total;
		string result,msg;
		if (!me||!target) return 0;
		
		message_vision(CYN "\n$N��$n�����˳��ʹ��һ�С�"HIW"�����ѩ"CYN"����˫�Ʒ��裬����Ʈ�ݣ��������磬������������Ϣ�ľ�������$n��\n"NOR,me,target);

        total=(int)me->query_skill("sixiang-zhang",1)+(int)me->query_skill("linji-zhuang",1)+(int)me->query_skill("strike",1)+(int)me->query_skill("anying-fuxiang",1);
		if (me->query("class")=="bonze") i=i+me->query_skill("dacheng-fofa",1);
        total += i;
		total=total*2;
        if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
		target->receive_damage("qi", total, me );
		target->receive_wound("qi", total/3 , me);
		result = COMBAT_D->damage_msg(i,"����");
		result = replace_string( result, "$l", "����" );
		msg = result;
		message_vision(msg,me,target);
        COMBAT_D->report_status(target, 0); 
		return 1;
}
string perform_name(){ return HIC"������"NOR; }

int help(object me)
{
   write(HIC"\n������֮�� ������ ����"NOR"\n");
   write(@HELP
	�����ƾ�ѧ�Ƕ�����Ҫ�Ŀ����似�������е�������в���
	�ı��֣����Ͷ��ҵ�����һ������似���־�ʽ�����󣬻�
	����һ���̶ȵķ�Ծ�������������ö������ļ����߶���
	�Ʒ����⣬���Է������Ʒ�֮�е���ʽ��250���Ծ
	
	ָ��: perform strike.sixiang
	
Ҫ��
	������������� 1800 ���ϣ�
	����������� 1000 ���ϣ�
	��ǰ���������� 500 ���ϣ�
	�����Ʒ��ĵȼ� 200 ���ϣ�
	�����Ʒ��ĵȼ� 200 ���ϣ�
	�ټ�ʮ��׮�ȼ� 200 ���ϣ�
	���������˷�ԭ������΢���ơ�
		
HELP
   );
   return 1;
}
