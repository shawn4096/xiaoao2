
// yuxue ԡѪ����.c  Ѫ���ź����似������ѪԽ�࣬������ɱ����Խǿ��
// xuedao/dafa/pass Ϊ������
#include <ansi.h>
inherit F_SSERVER;
//inherit F_CLEAN_UP;
int help(object me);

void remove_effect(object me, int amount);

string exert_name(){ return HBRED+HIW"ԡѪ����"NOR; }

int exert(object me)
{
	int skill, i;
	int j;
	string msg;
	if(!me->is_fighting() && me->query_skill("xuedao-jing", 1) < 500 ) 
	     return notify_fail("��ֻ����ս������Ѫ�����������Լ���ս������\n");

	if( (int)me->query("neili") < 400  ) 
		return notify_fail("�������������\n");
	
	if( (int)me->query("max_neili") < 1400  ) 
		return notify_fail("����������������\n");
	
	if( (int)me->query("max_jingli") < 1400  ) 
		return notify_fail("��������������\n");

	if( (int)me->query_skill("xuedao-jing",1) < 100  ) 
		return notify_fail("���Ѫ������������100��\n");
	
	if( (int)me->query_skill("force",1) < 100  ) 
		return notify_fail("��Ļ����ڹ���������100��\n");

	if( (int)me->query_temp("xdj/yuxue") ) 
		return notify_fail("���Ѿ����˹����ˡ�\n");

   // skill = (int)me->query_skill("force",1) + (int)me->query_skill("xuedao-jing",1);
    skill = (int)me->query_skill("xuedao-jing",1);
    
	i = skill/10 + random(skill/10); 

	me->add("neili", -100+random(100));
	if (me->query_skill("xuedao-jing",1)<100) j=1;
	else if (100<=me->query_skill("xuedao-jing",1)<200) j=2;
	else if (200<=me->query_skill("xuedao-jing",1)<300) j=3;
	else if (300<=me->query_skill("xuedao-jing",1)<350) j=4;
	else if (350<=me->query_skill("xuedao-jing",1)<400) j=5;
	else if (400<=me->query_skill("xuedao-jing",1)<450) j=6;
	else if (450<=me->query_skill("xuedao-jing",1)) j=7;
	else j=1;
	
    if (me->query_skill("xuedao-jing",1)>449 
		&& me->query_skill("quest/xd/xdj/xuedao/pass"))
    {
		  message_vision(HBRED "\n$N΢һ��������Ѫ����֮ԡѪ�����ռ��ؼ���������������Ѫ����˲��������\n" NOR, me);
		  message_vision(HBRED "\n����$N�������������������صľ��ģ�$N����������һ���������ֵ�Ѫ����Ȧ��\n" NOR, me);
		  me->add_temp("apply/attack", skill/4);
		  me->add_temp("apply/damage", skill/5);
		  me->add_temp("apply/blade", skill/3);
		  me->add_temp("apply/armor", skill/5);
		  me->add_temp("apply/parry", skill/5);

		  //me->set_temp("xuedao/yuxue",i);
		  call_out("remove_effect", 1, me, skill/20);	
	  
     }
	 else
	  {
		  message_vision(RED "$N΢һ��������Ѫ����֮ԡѪ�ؼ���ֻ��$N��Ѫ��ӿ��ʱ��죬������������ɮ��΢΢����\n" NOR, me);
		  me->add_temp("apply/attack", skill/6);
		  me->add_temp("apply/armor", skill/6);
		  me->add_temp("apply/blade", skill/5);
		  //me->set_temp("xuedao/yuxue",i);
		  call_out("remove_effect", 1, me, skill/30);
	  }
	//���վ�2�ں���������
	if (me->query("quest/xd/szj/ronghe/pass"))
	{
		skill=skill+me->query_skill("shenzhao-jing",1)/5;
		message_vision(HBMAG+HIW "\n$N�����վ��Ĺ����ںϵ�Ѫ�����У�а�д��������д��ᣬѪ����������������\n"NOR, me);
		me->add_temp("apply/parry",skill/6);
		me->add_temp("apply/armor",skill/6);
		me->add_temp("apply/damage",skill/6);

		me->set_temp("xdj/shenzhaoronghe",skill);
	}



		me->set_temp("xdj/yuxue", skill);
		
		if( me->is_fighting() && me->query_skill("xuedao-jing",1) < 349 ) me->start_busy(random(2));
		
	   if (me->query_skill("xuedao-jing",1) > 450 
		   && me->query("env/Ѫ����")=="ԡѪ����"
		   && me->query("eff_qi")< me->query("max_qi"))
	   {
			msg = HIR "$N��������һ��������ɫ�ɺ�ת�ף������ɰ׷���,Ѫ�����������������ƾ�Ȼ�ڻ����ָ���\n" NOR;
			message_vision(msg,me);
			me->receive_curing("qi", skill/10);
			me->receive_healing("qi", skill * 3 / 20);
			me->add("neili", -200);
			if (random(10) < 2 && !me->query("quest/xd/xdj/xuedao/pass"))
			{
					tell_object(me, HIC "��������ȵĴ߶���Ԫ����������������������ġ�\n" NOR);
					me->add("max_neili", -1);
			}
	   }
	   if(me->query_skill("xuedao-jing",1) < 350 ) 
		  me->start_exert(1,"ԡѪ����");
	   return 1;
}

void remove_effect(object me, int count)
{    
     int skill;
	 if (!me||!me->query_temp("xdj/yuxue")) return;
	 skill=me->query_temp("xdj/yuxue");
	
     if( !me->is_fighting()
		 ||count-- < 0 )
	{

	   if (me->query_skill("xuedao-jing",1)>449 
		   && me->query_skill("quest/xd/xdj/xuedao/pass"))
       {
		  me->add_temp("apply/attack", -skill/4);
		  me->add_temp("apply/damage", -skill/5);
		  me->add_temp("apply/blade", -skill/3);
		  me->add_temp("apply/armor", -skill/5);
		  me->add_temp("apply/parry",- skill/5);
		  me->delete_temp("xdj/yuxue");
		  tell_object(me, HIR"\n���Ѫ����ԡѪ�ؼ�������ϣ��������ջص��\n"NOR);
		  return;
       } else
	   {
		  me->add_temp("apply/attack", -skill/6);
		  me->add_temp("apply/armor", -skill/6);
		  me->add_temp("apply/blade", -skill/5);		
		  me->delete_temp("xdj/yuxue");

		  tell_object(me, HIR"\n���Ѫ������ԡѪ��������ϣ��������ջص��\n"NOR);
		  return;
       } 
	   if (me->query_temp("xdj/shenzhaoronghe"))
	   {
			  me->add_temp("apply/parry",-skill/6);
			  me->add_temp("apply/armor",-skill/6);
			  me->add_temp("apply/damage",-skill/6);
			  me->delete_temp("xdj/shenzhaoronghe");
		}

					 
					
	 }
					 
	 call_out("remove_effect", 1, me, count);
				
}

int help(object me)
{
        write(HIR"\nѪ����֮��ԡѪ��������"NOR"\n");
        write(@HELP
	Ѫ���������ຣ�ڽ�Ѫ���ŵ�һ��������Ѫ������������
	���ų����ֵ�һа�ɸ��֡���Ҫԭ�������Ϊ�������ص�
	�ڹ��͵������䣬��������벻����Ч����Ѫ����������
	֮����Ǻ�Ѫ���йأ����ϵ�ѪԽ�࣬������Խǿ����
	������Խ�ǹ��졣
	���⿪���վ��ڶ��β���̵��ƺ�ԡѪ����������һ��
	����䣬а�д�������������һ��¥��

	˵����Ѫ�����ڹ�Դ�ԡ�Ѫ�������ؼ�����ʼ����ͨ����
	������ϰ�ڹ�����һ���̶Ⱥ󣬿��Ը�Ѫ���������Ѫ��
	���ŵľ����ķ��󷽿ɵ������ң���Ϊ��ɡ�350����С�ɡ�

	ע�⣺set Ѫ���� ԡѪ���� 

	ʹ��������450������ʹ�ã����û�⿪Ѫ���󷨻����
	��ʧһ���������Ϊ���ۣ�������á�

	ָ�exert yuxue

Ҫ��
	��ǰ���� 800 ���ϣ�
	������� 1400 ���ϣ�
	����� 1400 ���ϣ�
	��ǰ���� 300 ���ϣ�
	Ѫ�����ȼ� 100 ���ϣ�
	�����ڹ�ΪѪ������

���⣺
	350��С�ɣ�ȡ��busy��
	450 ������Զ����ˣ�������������
	���⿪Ѫ���������⣬������������
	Ѫ��������֮Ч��������ȫ���ͷš�
	
HELP
        );
        return 1;
}