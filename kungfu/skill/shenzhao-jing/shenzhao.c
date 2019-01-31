// By Spiderii�޸� shenzhao.c

#include <ansi.h>
#include <combat_msg.h>
void remove_effect(object me,int skill);

int exert(object me)
{      
       int skill;
	   object weapon;
	   string msg;
       skill = me->query_skill("shenzhao-jing",1);
	   
	   weapon = me->query_temp("weapon");
	if (skill < 450 && !me->is_fighting())
		return notify_fail("��ֻ����ս����ʹ�á����ա���\n");

	if( (int)me->query_skill("shenzhao-jing", 1) < 120 )
		return notify_fail("������վ���Ϊ�������޷�ʹ�á����ա���\n");

	if (me->query_skill_mapped("force") != "shenzhao-jing")
		return notify_fail("�����ڹ��С����ա���\n");

	if( (int)me->query("neili") < 1500 )
		return notify_fail("��Ŀǰ������̫���ˣ��޷�ʹ�á����ա���\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("���������Ϊ��ô�����ʹ�á����ա���\n");

	if( me->query_temp("sjz_power"))
		return notify_fail("���������á����ա���\n");

	message_vision(HIW"\n$N����һ��������Ϣ���������������������ӣ���ʱ�о�����������Ȼ���ˣ���Ȼ������\n" NOR, me);
	if (skill < 450) me->add_busy(1);

	if (me->query("quest/shenzhao/dingdian"))
	 {
	  message_vision(HIY"$N�������վ����ƺ�����һ�����Ƶã�������$N�ķ����������������\n" NOR,me);
	  //msg==HIY"$N�������վ����ƺ�����һ�����Ƶã���������ķ����������������\n" NOR;
	  me->add_temp("apply/dexerity", skill/10); //��΢���������
      me->add_temp("apply/parry", skill/5);
	  //me->add_temp("apply/sword",skill/2);
      //me->add_temp("apply/blade",skill/4);
     }  
	if (userp(me) && skill > 449 && me->query("quest/shenzhao/diyun"))
    {
	  message_vision(HBMAG"$N���յ��������ڵ��˹����ţ����վ����Ķ��𣬵���Ӧ�֣����ϵ������ƺ������ˡ�\n" NOR, me);
	
	 // msg==HBMAG"$N���յ��������ڵ��˹����ţ����վ����Ķ��𣬵���Ӧ�֣����ϵ������ƺ������ˡ�\n" NOR;
	  me->add_temp("apply/defense",skill/3);
	  me->add_temp("apply/parry", skill/5);
	  me->add_temp("apply/sword",skill/3);
	  me->add_temp("apply/cuff",skill/3); //Ϊ��Ӱȭ��׼��
      me->add_temp("apply/blade",skill/3);
    }  
	
	if (userp(me) && skill > 549 && (me->query("quest/shenzhao/laozu")|| me->query("quest/szj/pass")==3))
	{  //��Ϊ���յ�һ��ǿ���ڹ�������Ϊ���ԣ���λΪ9��
      message_vision(HBRED"$N�����վ��ڻ��ͨ����ɫ΢΢���죬�½󻺻��������վ���������Ȼ�Ѵﻯ����\n" NOR, me);
     
	 // msg==HBRED"$N�����վ��ڻ��ͨ����ɫ΢΢���죬�½󻺻��������վ���������Ȼ�Ѵﻯ����\n" NOR;
	  //me->add_temp("apply/parry", skill/4);
      me->add_temp("apply/armor", skill/4);
	  me->add_temp("apply/damage", skill/4);
      me->add_temp("apply/strength", skill/9);
	  me->add("neili",-200);
	}
     //message_vision(msg,me);
	 me->add_temp("apply/dodge", me->query_skill("shenzhao-jing", 1)/4);
     me->add_temp("apply/attack", me->query_skill("shenzhao-jing", 1)/4);
	 me->add("neili", -300);
	 me->set_temp("sjz_power",skill);
 	 call_out("remove_effect", 1, me, skill/20);
	 if (!me->query("quest/shenzhao/diyun"))
		 me->start_exert(2, "�����ա�");
	 return 1;
}
void remove_effect(object me, int count)
{
	
	 int skill;
	 if (!me) return;
	 skill=me->query_temp("sjz_power");

     if (count>0) {
                        
		call_out("remove_effect", 1, me, count-1);
        return;
         
	 }
	 
	  if (userp(me) && skill > 549 && (me->query("quest/shenzhao/laozu")|| me->query("quest/szj/pass")==3))
	    {
      
          me->add_temp("apply/armor", -skill/4);
	      me->add_temp("apply/damage", -skill/4);
          me->add_temp("apply/strength", -skill/9);
	   }
	   if (userp(me) && skill > 449 && me->query("quest/shenzhao/diyun"))
        {
	       me->add_temp("apply/defense",-skill/3);
	       me->add_temp("apply/sword",-skill/3);
		   me->add_temp("apply/cuff",-skill/3);
           me->add_temp("apply/blade",-skill/3);
		   me->add_temp("apply/parry", -skill/5);
        }  
	   if (me->query("quest/shenzhao/dingdian"))
        {
		  me->add_temp("apply/dexerity", -skill/10); //��΢���������
          me->add_temp("apply/parry", -skill/5);
        }  
		   
        me->add_temp("apply/dodge", -me->query_skill("shenzhao-jing", 1)/4);
        me->add_temp("apply/attack", -me->query_skill("shenzhao-jing", 1)/4);
      	me->delete_temp("sjz_power");
 
	   message_vision(HIM"$N����������һ������ɢȥ�����վ�����ת������\n"NOR, me);
	   return;

	
}

string perform_name(){ return HIM"���չ�"NOR; }

int help(object me)
{
        write(WHT"\n���վ�֮�����չ�����"NOR"\n");
        write(@HELP
	��������ī��÷���������������̶����һ���ڹ����ؾ�
	����ϰ�ô��ڹ������ִ��ڵ��ƣ����ƿ��Ķ��꣬���վ�
	��ϰ�õ������硣������Ե�õ�����ָ�㣬�ɸ���һ��¥
	Ϊ���������վ���Ϊ���Ǿ��еĶ����书�ص㣬�ܹ���Ϊ
	�����׶Σ���һ���ɶ���ָ�㣬�ڶ����ɵ���ָ�㡣����
	�ν����Ե�ɺ�Ϊ���ճ��״�ɣ���������Ƶ�Ե�ʣ���
	�վ��ں�Ѫ���ŵ��似������ʵ��ļӳ�Ч�������徭��
	���������������
	
	ָ�exert shenzhao
			        
Ҫ��:
	���� 1500 ���ϣ�
	���վ� 120 �����ϣ�

Ч��:   
	���⿪��������վ������������������
	���⿪���Ƶ����վ��������������᳹���ͷš�
	���վ����ξ��в�ͬ�̶ȵķ�Ծ��ԽսԽǿ
	��һ��Ϊ��������
	�ڶ���Ϊ��������
	�������˺�����        
	450�����ɡ�
	550���ҽ⿪�����κ����վ���������������ߡ�
			    
        
HELP
        );
        return 1;
}

