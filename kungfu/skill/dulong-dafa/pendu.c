//pendu.c 
//cre by sohu@xojh


#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_SSERVER;

string exert_name() {return HBBLU+HIW"�綾"NOR;}

int exert(object me, object target)
{
        int skill,i;
		object yaocao;
		string poi;
		if( !target ) target = offensive_target(me);

	 
		if( !objectp(target)
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) )
        	return notify_fail("���綾������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if((int)me->query_skill("dulong-dafa",1) < 200  )
                return notify_fail("��Ķ����󷨹����������޷�ʹ�á��綾��������\n");
		 if((int)me->query_skill("force",1) < 200  )
                return notify_fail("��Ļ����ڹ������������޷�ʹ�á��綾��������\n");
		if((int)me->query_skill("medicine",1) < 100  )
                return notify_fail("��ı������������޷�ʹ�á��綾��������\n");
		if((int)me->query_skill("poison",1) < 150  )
                return notify_fail("��Ķ��Ʋ������޷�ʹ�á��綾��������\n");
        if((int)me->query_skill("shenlong-yaoli",1) < 180  )
                return notify_fail("�������ҩ��ѧ��������ȱ���޷�ʹ�á��綾��������\n");
		//if( target = me)
				//return notify_fail("�㲻�ܶ��Լ�ʹ�á��綾��������\n");
        if((int)me->query("neili") < 500
         || (int)me->query("max_neili")< 2500  )
                return notify_fail("�������������\n");

		if (!userp(target))
		{
			i=3;
		}
		else i=2;

		if (!me->query("quest/sld/dldf/pendu/pass"))
		{
			if (!objectp(yaocao=present("yao cao",me)) || yaocao->query("local")!="sld")
				return notify_fail("������û������������ҩ�ݣ��޷�ʹ���綾��\n");
       // skill= (me->query_skill("dulong-dafa",1)/2 + me->query_skill("shenlong-yaoli",1))*14+ me->query_skill("medicine",1))*14;     
       
			message_vision(HIB"\n$N�ӱ���������һ�Ѳ�֪���Ĳ�ҩ�����پ׽����ڣ�Ȼ���������󷨣������еĲ�ҩ��Ȼ������$n��\n\n"NOR,me,target);
			yaocao->add("amount",-1);
			if ((int)yaocao->query("amount")<1)
			{
				message_vision(HIY"��һ��ҩ�ݿ�Ҫ������,���������������������С�\n"NOR,me);
				destruct(yaocao);
			}

		}else {
			message_vision(HBGRN+HIW"\n$Nʩչ��������ת֮��������������Ķ��Ի���һ�ڶ�������Ȼ������$n���ӡ�\n\n"NOR,me,target);
			i=3;
		}
	   // message_vision(HIb"\n$n��ͷ�󺹣��þ��������ڵĶ��رƳ����⡣\n\n"NOR, me);
	
		if (random(me->query("neili"))>target->query("neili")/i
			||random(me->query("combat_exp"))>target->query("combat_exp")/i)
		{
			message_vision(HIB"\n$nֻ����һ���ȳ��ޱȵ��������Լ�������һ����Ϣ������ȴ��ʶ���Լ��Ѿ��ж��ˡ�\n\n"NOR,me,target);
			poi==(string)me->query("env/�綾");
			if (poi)
			{
					switch (poi)
					{
						case "�߶�":
							target->add_condition("snake_poison",i);break;
						case "ǧ����":
							target->add_condition("qianli_poison",i);break;
						case "�߳��߻���":
							target->add_condition("7bug_poison",i);break;
						case "���Ƕ�":
							target->add_condition("fugu_poison",i);break;
					}
			}else {
					switch (random(6))
					{
						case 0:
							target->add_condition("snake_poison",i);break;
						case 1:
							target->add_condition("qianli_poison",i);break;
						case 2:
							target->add_condition("7bug_poison",i);break;
						case 3:
							target->add_condition("fugu_poison",i);break;
						case 4:
							target->add_condition("snake_poison",i);break;
						case 5:
							target->add_condition("snake_poison",i);break;
				
					}	
			}			

		}else {
			message_vision(HIC"\n$n��æ�˹�������������������֮�⡣\n\n"NOR,me,target);
			target->add("neili",-random(1000));
			me->add_busy(1);
		}
			
        me->add("neili",-300);
		me->add("neili",-400);
		me->start_exert(3,"���綾��");
        return 1;
}

int help(object me)
{
        write(WHT"\n������֮"+HBBLU+HIW"���綾��"WHT"��\n\n"NOR);
        write(@HELP
	�����������������ڹ����������ǿ�ɽ��ʦ
	������������ɶ����ķ����������������߶�
	�����ԣ�������ǿ����һ�档
	���綾�������������������ڹ��ķ��Ͷ���
	������ҩ��֪ʶ���ϣ�������������һ����
	���ֶ���ͨ��ǿ������������⣬Ӱ��Է���
	��ҩֲ���ϸ��ҽ⿪�綾���⣬������������
	ע�⣻set �綾 xx
		xx�����߶���ǧ���㡢�߳��߻��ࡢ���Ƕ�
	�����趨������綾��
	
	ʹ��ָ�yun pendu
		
Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	�������Ҫ�� 2500 ���ϣ�
	�����ڹ��ȼ� 200  ���ϣ�
	�����󷨵ȼ� 200 ���ϣ�
	��������ȼ� 100 ���ϣ�
	����ҩ��ȼ� 180 ���ϣ�
	���Ƽ������� 150 ���ϣ�
	�����ڹ�Ϊ�����󷨣�
	
HELP
        );
        return 1;
}


