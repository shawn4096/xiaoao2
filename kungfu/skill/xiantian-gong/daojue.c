// wuqi.c
// action@SJ 2009/1/17

#include <ansi.h>
inherit F_CLEAN_UP;
string exert_name(){ return CYN"������"NOR; }

string *koujue= ({ 
CYN"�������ͨ���ϣ�����ԭ��β��Ѩ"NOR,
MAG"�ȴ�ӿȪ�ŵ׳壬ӿȪ�������ϥ"NOR,
WHT"ϥ��������β�̣����趥�ϻ�����"NOR,
YEL"����ʦ���򱾳�����ʱ����ȥ����"NOR,
BLU"���곾����ĥ������������ҫ̫��"NOR,
RED"�������к�ƾ������Ⱥ�����"NOR,
HBGRN+HIW"������ӯ���оߣ������ҫ����"NOR,
HIC"�����ش���ȵ�ţ���¥ʮ��������"NOR,

}); 


int exert(object me, object target)
{
	int skill,count,i,j;
	string kou_jue;
	
	kou_jue=koujue[random(sizeof(koujue))];
	if( me->query("neili") < 100 )
		return notify_fail("�������������\n");

	if( me->query_skill("xiantian-gong", 1) < 100 )
		return notify_fail("������칦�ȼ�������\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("����ڹ����ԡ�\n");
	
	if (me->is_fighting()&&!me->query("quest/qz/xtg/daojue"))
	{
		return notify_fail("������칦��δ����ͨ�������صĵز����޷���ս�����˹���\n");
	}
	
	if( me->query_temp("xtg/daojue") )
		return notify_fail("���Ѿ����ˡ����������ˡ�\n");

	skill = me->query_skill("xiantian-gong",1);
	
	me->receive_damage("neili", -300);
	
	message_vision(HIW"$NĬ����ҡ���������֮"+kou_jue+HIW",һ�������������ޣ��������档\n" NOR, me);
	
	if (!me->is_fighting() )
	{
		if (CHAR_D->addbuff(me,"parry",to_int(skill/20),to_int(skill/20),"xtg/daojue",HIW"$N��["+HIR+"������"+HIW+"]������ϣ��������ջص��"))
		message_vision(WHT"$N��������������˵�������������⣬��תһ�������Ԫת���⣡\n" NOR, me);	

	}
	else if (me->is_fighting()&&me->query("quest/qz/xtg/daojue/pass"))
	{
	//Ǭ���ڵ����ⵤЧ��
		if (me->query("gender")=="Ů��")
		{			
		if(CHAR_D->addbuff(me,"armor|parry|dodge",to_int(skill/10),to_int(skill/10),"xtg/daojue",MAG"$N�����칦�����չ�����������������۳�һ�ţ�"))
		 {
			
			//me->add_temp("apply/armor", skill/10);
			//me->add_temp("apply/parry", skill/10);
			//me->add_temp("apply/dodge", skill/10);
			//me->add_temp("apply/constitution",skill/15);
			//����Ч��
			message_vision(MAG"$N�����칦������ת�������������������Եó�ӯ���������������ڵ��������ֳ��������������������\n" NOR, me);

		 }
		}
		if (me->query("gender")=="����")
		{
			if(CHAR_D->addbuff(me,"damage",to_int(skill/10),to_int(skill/10),"xtg/daojue",HIR"$N�����칦�����չ����������Ǭ�����۳�һ�ţ�"))			
                   {
	                message_vision(HIR"$N�����칦������ת����������������Ǭ�ڵ��������ֳ��������Ͻ������������\n" NOR, me);
                   }
		}
			
			//me->add_temp("apply/damage", skill/10);
			//me->add_temp("apply/constitution",skill/30);
			//Ǭ��Ч��
			//message_vision(HIR"$N�����칦������ת����������������Ǭ�ڵ��������ֳ��������Ͻ������������\n" NOR, me);

	}
	//	me->set_temp("xtg/dj_fighting",skill);
	
	
    //ÿ����һ�Σ�����һ��������
	 me->add("quest/qz/xtg/daojue/times",1);

	//me->set_temp("xtg/daojue", skill ); 
		
	//call_out("remove_effect", (int)skill/10, me );
	me->add("neili",-50);
	
	
	
	//��������÷��������л���
	
		kou_jue=koujue[random(sizeof(koujue))];		
		count=me->query("quest/qz/xtg/daojue/times");
		
		i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		
		if( i<3
			&& me->query("kar")<31
			&& random(count)>5000
			&& random(me->query("con"))>=30
			&& j > 26 
            && !me->query("quest/qz/xtg/daojue/pass"))			
		{
			tell_object(me,"\n���Ȼ���������������������Լ����������칦�ĵ������ĵã�����ӡ�ա�\n"NOR);
			tell_object(me,HIG"\n��������أ���Ȼ����Ѩһʹ��һ�ɾ����������֣�������ת������ޱȡ�\n"			    
							 +"��������������Ĵ��������ڴ�ɣ��̲�ס���쳤Х��\n"NOR);
			command("shout "+kou_jue);
			command("shout ƶ���������칦����С�ɣ�ȫ������칦��Ȼ���µ�һ��");
			me->set("quest/qz/xtg/daojue/pass",1);
			log_file("quest/xtgdaojue", sprintf("%8s(%8s) ��Ե�ɺ��������칦���������ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ����ȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), i,j,me->query("con"),me->query("combat_exp")) );			
			
			tell_object(me,HIR"��ϲ���칦������Ȼ��ͨ�����칦����һ��¥!\n");    

		}	

	

	return 1;
}

void remove_effect(object me)
{
        int skill,count,i,j;
      	string kou_jue;
		kou_jue=koujue[random(sizeof(koujue))];

        if(!me)  return;

		skill = me->query_temp("xtg/daojue"); 
		count=me->query("quest/qz/xtg/daojue/times");

		if (me->query_temp("xtg/dj_fighting") )
        {
			if (me->query("gender")=="Ů��")
			{
				me->add_temp("apply/armor", -skill/8);
				me->add_temp("apply/parry", -skill/8);
				me->add_temp("apply/dodge", -skill/8);
				me->add_temp("apply/constitution",-skill/15);
				//����Ч��
				message_vision(MAG"$N�����칦�����չ�����������������۳�һ�ţ�\n" NOR, me);

			}
			if (me->query("gender")=="����")
			{
				me->add_temp("apply/damage", -skill/10);
				me->add_temp("apply/constitution",-skill/30);
				//Ǭ��Ч��
				message_vision(HIR"$N�����칦�����չ����������Ǭ�����۳�һ�ţ�\n" NOR, me);

			}
			me->delete_temp("xtg/dj_fighting");

        }
		//��������÷��������л���
		i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		
		if( i<3
			&& me->query("kar")<31
			&& random(count)>5000
			&& random(me->query("con"))>=30
			&& j > 26 ) 
		{
			tell_object(me,"\n���Ȼ���������������������Լ����������칦�ĵ������ĵã�����ӡ�ա�\n"NOR);
			tell_object(me,HIG"\n��������أ���Ȼ����Ѩһʹ��һ�ɾ����������֣�������ת������ޱȡ�\n"			    
							 +"��������������Ĵ��������ڴ�ɣ��̲�ס���쳤Х��\n"NOR);
			command("shout "+kou_jue);
			command("shout ƶ���������칦����С�ɣ�ȫ������칦��Ȼ���µ�һ��");
			me->set("quest/qz/xtg/daojue/pass",1);
			log_file("quest/xtgdaojue", sprintf("%8s(%8s) ��Ե�ɺ��������칦���������ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ����ȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), i,j,me->query("con"),me->query("combat_exp")) );
			
			
			tell_object(me,HIR"��ϲ���칦������Ȼ��ͨ�����칦����һ��¥!\n");      

		}
	
 
	me->delete_temp("xtg/daojue");
       
	tell_object(me, HIW"���["+HIR+"������"+HIW+"]������ϣ��������ջص��\n"NOR);
	return;
}

int help(object me)
{
	write(HIC"\n���칦֮������������"NOR"\n\n");
        write(@HELP
	���칦��ȫ�����������Ϊ��Ҫ���ڹ��ķ����޵�
	����磬�ɷɻ�ժҶ���������Σ����д�����
	�������칦���ŵĻ����ķ�����Ѱ��ʱ��������ʹ
	��������������������ת��Ч���в�С��������
	��ս��ʱ��ת����������Ů������Ǭ����������
	Ч�����Բ�ͬ��������Լ��������顣
	ע�⣺ս������ʹ��������Ҫ����

	ָ�exert daojue

Ҫ��
	�������  100  ���ϣ�
	��ǰ����  100  ���ϣ�
	���칦��  100  ����,
	�����ڹ����칦
HELP
        );
        return 1;
}
