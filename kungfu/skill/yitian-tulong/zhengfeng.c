#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string perform_name(){ return HIC"˭������"NOR; }
void remove_effect(object me, int skill);

int perform(object me, object target)
{
      string msg; 
      int i; 
      int skill;	  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "sword")
         return notify_fail("�������޽������ʹ�ó�˭�����棡\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("˭������ֻ����ս���жԶ���ʹ�á�\n");
             
      if((int)me->query_skill("yitian-tulong",1) < 300 )
         return notify_fail("���������������������죬��ʹ����˭�����棡\n");
      
      if((int)me->query_skill("literate",1) < 250 )
         return notify_fail("��Ķ���д�ֵȼ�����������д��˭�����棡\n");

      if((int)me->query_skill("sword",1) < 300)
         return notify_fail("��Ļ��������ȼ�����������д��˭�����棡\n");  
      
      if((int)me->query("max_neili") < 3500 )
         return notify_fail("���������Ϊ�ƺ�����! \n");
      
      if((int)me->query("neili") < 1500 )
         return notify_fail("��ĵ�ǰ�����ƺ�������\n"); 
	  if((int)me->query("neili") < 1000 )
         return notify_fail("��ĵ�ǰ�����ƺ�������\n"); 
	 
	  if(target->query_temp("yttl/zf"))
	       return notify_fail("�Է��Ѿ�����������������\n");
	   
      if( target->is_busy() )
         return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

      if (me->query_skill_mapped("sword") != "yitian-tulong"
       || me->query_skill_mapped("parry") != "yitian-tulong")
         return notify_fail("�������޷�д����˭�����桹��\n");

      i = random((int)(me->query_skill("yitian-tulong",1)/100));
      if(i < 2) i=2;
      if(i > 4) i=4;                                                                                 
      msg = HIC"$N��Хһ��������"+weapon->query("name")+HIC"ֱ���������������ǽ���â����ʸӦ����\n"+
               "����Ͼ�����粻���ɣ���һֱ���ǡ��桱�ֵ����һ�ʣ�\n" NOR;
      me->add("neili", - 200);
	  
	  skill = me->query_skill("yitian-tulong",1);
        if (me->query_skill_mapped("force")=="yinyun-ziqi"
			&& me->query_skill("yinyun-ziqi",1)>350)
			skill += me->query_skill("yinyun-ziqi",1)/5;        			
	  
	  
      if(random(me->query_int(1)) > target->query_int(1)/2
        ||  random(me->query("combat_exp")) > target->query("combat_exp")/2) 
	  {
            target->start_busy(i+1);
            msg += HIR"$n⧲�����������"+weapon->query("name")+HIR"����ѩ����ֻ�������мܣ����޻���֮����\n"NOR;
			target->set_temp("yttl/zf",1);
			target->receive_damage("qi",1000+random(1000),me);
			target->receive_wound("qi",500+random(1000),me);	
			
            target->add_temp("apply/parry",-skill/5); //��������       
            target->add_temp("apply/dodge",-skill/5);
			
			msg += RED"$nΪ��"+weapon->query("name")+RED"����������ǰѨ��������Щ��Ѫ����\n"NOR;
			call_out("remove_effect", 5, target,skill);

      }
      else {
            me->start_busy(2);
            target->start_busy(1);
            msg += HIY"$n��$N��ʽϬ�����������ǰ������裬���³����ˣ��������һ�С�\n"NOR;
      }
      message_vision(msg, me, target);
      if (me->query_skill("yitian-tulong",1)<350)
      {
		  me->start_perform(1,"��˭�����桹");
      }
      return 1;
}

void remove_effect(object target,int skill)
{
	if(!target) return;	
	target->delete_temp("yttl/zf");
	target->add_temp("apply/parry",skill/5);        
    target->add_temp("apply/dodge",skill/5);	
	tell_object(target, HIR"\n������һ����ɫ������ֻ࣬�����ؿڱ���Ѩ����Ѫ��ת����ͨ���ˡ�\n"NOR);
}


int help(object me)
{
   write(HIG"\n����������֮��"HIR"˭������"HIG"����"NOR"\n");
	write(@HELP
	�����ڡ��������𣬱����������������£�Ī�Ҳ��ӡ�
	���첻����˭�����档���Ĺ��´�˵��������������
	�ٵ�֮��,�䵱��������,�����Ϊ�����ˣ�����
	ݱ����������������������֮���������ֻ���������
	��ʮ�ĸ�����Ϊһ�׶������ֵ������书��������
	���Ŵ�ɽ�򽭺��ų��������������鷨���輫���
	�˶�����������
	��˭�����桿Դ�ԣ�������ӿ���죬�����᳤Хһ��
	����ֱ���������������ǽ���â����ʸӦ��������Ͼ
	�����粻���ɣ���һֱ���ǡ��桱�ֵ����һ�ʡ�  
	
	ָ�perform sword.zhengfeng

Ҫ��
	�������Ҫ�� 3500 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	���������ȼ� 300 �����ϣ�
	����д�ֵȼ� 250 �����ϣ�
	����������   300 �����ϣ�
	�����������м�Ϊ����������
	�����г�������          
	˵������������һ��Ϭ����ƥ������⧲�����֮�£�
	����ֻ��ƣ���мܣ����޻���֮����
	350����С�ɡ�
HELP
	);
	return 1;
}
