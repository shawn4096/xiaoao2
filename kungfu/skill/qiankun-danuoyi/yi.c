// yi.c Ǭ����Ų�ơ��ơ��־�
#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return HIB"���־�"NOR; }

int perform(object me, string target)
{
	object ob,ob2,weapon;
	weapon=me->query_temp("weapon");
	if(!target)
		return notify_fail("����ѶԷ��ľ���Ų����˭��\n");
    //if(me->query_temp("weapon"))
		//return notify_fail("�����ձ��У��޷�ʩչŲ���񹦣�\n");
	if(!objectp(ob = present(target, environment(me))))
		return notify_fail("����û������Ų�Ƶ�����ˡ�\n");	

	//if (!me->is_killing(target) || !me->is_fighting(target)) return notify_fail("����û�к�����ս���С�\n");
	
	if (me->query_temp("qkdny/yi"))
	{		
		if (me->query_temp("qkdny/yi")==ob) return notify_fail("��ս�����ת�Ƹ�����Ŀǰ��ʱ�޷��ٴ�ת�ơ�\n");
	}
	
	
	if(!me->is_fighting())
		return notify_fail("��û�ڴ�ܣ���ʲô�ƣ�\n");

    if(!ob->is_character()) 
		return notify_fail("�����һ�㣬�ǲ��������\n");

	if(!living(ob))
		return notify_fail(ob->name()+"�Ѿ��޷�ս���ˡ�\n"); 

	if(ob==me) return notify_fail("�㲻�ܹ����Լ���\n");               
	
	if(userp(ob) && !me->is_killing(ob))
		return notify_fail("���Ǹ��Է�������ޣ��㲻���ݺ���ҡ�\n");

	if(me->is_fighting(ob))
		return notify_fail("�������������ء�\n");

	if(me->query_skill("qiankun-danuoyi", 1) < 450 )
		return notify_fail("���Ǭ����Ų�ƻ�������죬����ʹ�á��ơ��־���\n");

	if (!me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 450 )
		return notify_fail("���ʥ���񹦵ȼ�������\n");

	if(me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("��û��ʹ��Ǭ����Ų����Ϊ�н����޷�ʹ�á��ơ��־���\n"); 
	
	if((int)me->query("neili") < 8000 )
		return notify_fail("�������������\n");
	
	if((int)me->query_skill("force") < 450 )
		return notify_fail("���ơ��־���Ҫ�����ڹ�����������������󻹲�����\n");

	me->add("neili", -300);
	
	message_vision(BLU"�㰵��Ǭ����Ų�ơ��ơ��־�����ͼҪ�ѶԷ���һ�е�����ת�Ƶ�"+ob->name()+"���ϣ�\n"NOR,me,target); 
	//���ñ�ǣ��ĳɷ����Դ�auto�������޷�����ת�޵����� by renlai
/*
	if (random(me->query_int(1))>target->query_int(1)/2 && me->query("mjqkdny/pass"))
	{
      message_vision(HIC"$n��Ȼ�����Լ�����ʩչ����һ�а�;�о�Ȼ��Ȼת�˷��򣬾�ȻĪ������ش���"+ ob->name() +"�����ϣ�\n"NOR,me,target); 
	  
	  COMBAT_D->do_attack(target, ob, target->query_temp("weapon"), 3);
	  
	}
	*/
	if (!me->query("mjqkdny/pass")) me->start_perform(1, "���־�");	
	    me->set_temp("qkdny/yi",ob);
		ob->set_temp("qkdny/yi",me);//�����
	return 1;
}

int help(object me)
{
        write(HIB"\nǬ����Ų�ơ����־�����"NOR"\n");
        write(@HELP
	�����������ǡ������޼ɵ������书������ԭ���̵Ľ�����ϰ�á�
	����Դ�Բ�˹�ݻ�̣������֮������ѧ�����Ԫ����仯��
	�棬�������������۷���书���˹����߲㾳�磬���Ը�����ϰ��
	��һ�������꣬�ڶ���ӱ�������������ѣ��������߱���ֻ��
	�������㣬ϰ�����߲���ʵ�ǹ���������һ�ˡ���Ҫ�оŴ��ܣ�
	�����������Ǳ�������书�����ɣ���������������������
	ճס������ǣ��Ų�Ƶо����������֣�ת��������������������
	�ȡ�
	�ر�ע�⣺���⿪Ǭ����Ų�Ƶĵ��߲���ʱ��Ǭ����Ų�ƿ���
	����ʹ�ø�������,����Ҫǿ������֧�ŷ�����Ч��
	���־��ǽ��Է����似ת�Ƶ����湦������ҵ��Լ�̽�����ء�
	
	perform parry.yi

Ҫ��
	��ǰ���� 8000 ���ϣ�
	Ǭ����Ų�Ƶȼ� 450 ���ϣ�
	�����ڹ��ȼ� 450 ���ϣ�
	ʥ���񹦵ȼ� 450 ���ϣ�
	�����м�ΪǬ����Ų�ơ�
	�����ںϺ�������Ծ��
HELP
        );
        return 1;
}
