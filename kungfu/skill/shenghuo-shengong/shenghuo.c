
// shenghuo.c  ʥ���ع�����λ���������ԣ���λΪ9���������ʥ�����Ǭ����Ų�ƣ���Ѫ�����֮�书����ɣ����㲻������Ҳ����ν�� 

#include <ansi.h>
inherit F_SSERVER;
//inherit F_CLEAN_UP;
int help(object me);

void remove_effect(object me, int amount);

string exert_name(){ return RED"ʥ�����"NOR; }

int exert(object me)
{
	int skill, i;
	int j;
	if(!me->is_fighting() && me->query_skill("shenghuo-shengong", 1) < 100 ) 
	     return notify_fail("��ֻ����ս������ʥ�����������Լ���ս������\n");

	if( (int)me->query("neili") < 400  ) 
		return notify_fail("�������������\n");
		
	if( (int)me->query_temp("mj/shenghuo") ) 
		return notify_fail("���Ѿ����˹����ˡ�\n");

   // skill = (int)me->query_skill("force",1) + (int)me->query_skill("shenghuo-shengong",1);
    skill = (int)me->query_skill("shenghuo-shengong",1);
    i = skill/5; 
	
	me->add("neili", -100+random(100));
	/*if (me->query_skill("qiankun-danuoyi",1)<100) j=1;
	else if (100<=me->query_skill("qiankun-danuoyi",1)<200) j=2;
	else if (200<=me->query_skill("qiankun-danuoyi",1)<300) j=3;
	else if (300<=me->query_skill("qiankun-danuoyi",1)<350) j=4;
	else if (350<=me->query_skill("qiankun-danuoyi",1)<400) j=5;
	else if (400<=me->query_skill("qiankun-danuoyi",1)<450) j=6;
	else if (450<=me->query_skill("qiankun-danuoyi",1)) j=7;
	else j=1;*/
 	j=2+(int)(me->query_skill("qiankun-danuoyi",1)+me->query_skill("shenghuo-shengong",1))/200;
	if (j>7) j=7;
		
	if (me->query_skill("shenghuo-shengong",1)>449 && me->query("mjqkdny/pass"))
    {
	  i=i+me->query_skill("qiankun-danuoyi",1)/10;
	  message_vision(HIW "\n$N΢һ��������ʥ�������ֻ��$N����ɫ��������ף����ɰױ���ת��"+chinese_number(j)+HIW"�Ρ�\n" NOR, me);
      message_vision(HIY "\n����$N�������������һ𣬷��Ҳ�������$N����������һ���������ֵ�����֮���������ƺ������ˡ�\n" NOR, me);
      me->add_temp("apply/attack", i);
      me->add_temp("apply/damage", i);
      me->add_temp("apply/dagger", i);
	  me->add_temp("apply/armor", i);
	  call_out("remove_effect", 1, me, i);	  
     }
	 else
	  {
	  message_vision(WHT "$N΢һ��������ʥ���񹦣�ֻ��$N����ɫ��������ף����ɰױ���ת��"+chinese_number(j)+"�Ρ�\n" NOR, me);
	  me->add_temp("apply/attack", i);
	  me->add_temp("apply/armor", i);
      me->add_temp("apply/dagger", i);
	  call_out("remove_effect", 1, me, i);
	  }
     me->set_temp("mj/shenghuo", i);
	 if( me->is_fighting() && me->query_skill("shenghuo-shengong",1) < 349 ) me->start_busy(random(2));
	   me->start_exert(1,"ʥ����");
	return 1; 
 }

void remove_effect(object me, int count)
{    
     int amount;
	 if (!me) return;
	 
	 amount=me->query_temp("mj/shenghuo");
     
	 if (!me->is_fighting()
		 ||count--<0)
	 {
		if (me->query_skill("shenghuo-shengong",1)>449 && me->query("mjqkdny/pass"))
		 {
		  me->add_temp("apply/attack", -amount);
		  me->add_temp("apply/damage", -amount);
		  me->add_temp("apply/dagger", -amount);
		  me->add_temp("apply/armor", -amount);
		  me->delete_temp("mj/shenghuo");
		 } else  {
		  me->add_temp("apply/attack", -amount);
		  me->add_temp("apply/armor", -amount);
		  me->add_temp("apply/dagger", -amount);
		  me->delete_temp("mj/shenghuo");
		  }	 
		tell_object(me, HIW"\n���"WHT"ʥ�����"HIW"������ϣ��������ջص��\n"NOR);
		return;

	 }
     call_out("remove_effect", 1, me, count);
    // return;
              
}

int help(object me)
{
        write(RED"\nʥ����֮��ʥ�������"NOR"\n");
        write(@HELP
	���̵���һ�����������Ի�Ϊ��ʥ֮��������������ҳ�
	�������Ի�����ľ������������������׷�����������ν
	����λ�������ο࣬�����һ𣬷��Ҳ�����
	350��С�ɣ�ȡ��busy��450��⿪Ǭ����Ų�ơ��ںϡ����⣬��
	�׺�Ǭ����Ų���ںϱ��죬��������������ſ�������������Ϊ
	��Ҫ���ڹ�����

ָ��: exert shenghuo

Ҫ��
	��ǰ���� 800 ���ϣ�
	��ǰ���� 300 ���ϣ�
	ʥ���񹦵ȼ� 100 ���ϣ�
	�����ڹ�Ϊʥ���񹦡�		       
		
HELP
        );
        return 1;
}