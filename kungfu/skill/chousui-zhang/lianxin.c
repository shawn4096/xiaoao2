//lianxin.c ���ĵ�
//���޶��ƣ����ڹ�����������һ�ɵ��裬�����Է���ը���ж�+���+����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
       object dan;
	   int damage;
       if( !target ) target = offensive_target(me);

       if( !target || !me->is_fighting(target) )
            return notify_fail("�����ĵ���ֻ����ս���жԶ���ʹ�á�\n");

       if( objectp(me->query_temp("weapon")) )
            return notify_fail("�������ֲ���ʹ�á����ĵ�����\n");

       if( (int)me->query_skill("chousui-zhang", 1) < 150 )
            return notify_fail("������޶��ƻ�������죬ʹ���������ĵ���������\n");

       if( (int)me->query_skill("huagong-dafa",1) < 150 )
            return notify_fail("��Ļ�������Ϊ����������ʹ�á����ĵ�����\n");

       if((int)me->query_skill("poison",1)<150)
            return notify_fail("�㶾�Ʋ���150�޷�ʹ�����ĵ���\n"); 
      // if(!present("lin huo",me)||!present("liu huang",me))
        //    return notify_fail("���ĵ���Ҫ�׻���Ҫ����׻����ǡ�\n"); 
	  // dan=present("lianxin dan",me);       

      
		 
     

       if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang")
           return notify_fail("�������޷�ʹ�á����ĵ�����\n");                                                                                 

       if( (int)me->query("max_neili") < 2500) 
           return notify_fail("������̫����ʹ���������ĵ�����\n");      

       if( (int)me->query("neili") < 500)
           return notify_fail("����������̫����ʹ���������ĵ�����\n");
		//if (me->me->query_skill("poison",1)<150 || me->query_skill("hugong-dafa",1)<150)
     	  // if (!dan)
			//return notify_fail("������û�����ĵ������ʹ�������������ĵ�!\n");
       
	   //if(dan) message_vision(HIW"\n$N�ӻ���͵͵�ͳ�һö���ĵ�������һЦ������������$n��\n"NOR,me);
      // else 
		   message_vision(HIW"$N�ӵ�������ץ��һ���������ӻ����ͳ�Щ�׻�ͺ�ɫҩĩ����������ת���۳�һ�������ĵ���!\n"NOR,me); 
	   
	   //call_out("destroying", 1, dan);
       
	   if (userp(target)&&!target->is_killing(me))
          me->kill_ob(target);
       
	   me->add("neili", - 250);
       
	   damage=3000+random(500);
	   if( random(me->query("combat_exp")) > (int)target->query("combat_exp")*2/3
        && me->query_str() > (int)target->query_str()*2/3)
	   { 
         message_vision(HIB"\n$n�ۼ�һ���ڹ����Լ������������޴룬�����޼���������$n���ϡ�\n"NOR, me, target);
        // me->add("max_neili", -50);
		 
		 target->receive_damge("qi",damage,me);
         target->set_temp("last_damage_from", "���ĵ�ը��");
         if (!userp(target)&&!random(3))
         	 target->die();
         return 1;  
       }
       else if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/3
         || random(me->query_str()) > (int)target->query_str()/2)
	   {
          message_vision(HIB"\n$n���²��ã���æ����ֱ�����ĵ��������ӹ�����Ȼ��"HIG"��ը"HIB"��$n������ʵ���ᡣ\n"NOR,me,target);
          tell_object(target,HIB"\n���ĵ��ж�����������һ���ȳ�����ǣ��������˾綾�ˡ�\n"NOR);
         // me->add("max_neili", -100);
		  if (userp(target))
			 me->add_condition("killer", 15);
          target->apply_condition("fs_poison", 3);
          target->receive_damge("qi",damage,me);
		  target->receive_damge("qi",damage/2,me);
          target->set_temp("last_damage_from", "���ĵ�ը��");

          target->add_busy(1);
          return 1;
      }
      message_vision(HIB"\n$n���г���һ����Х��˫��������������������ĵ�ѹ����·��\n"NOR,me,target);
      tell_object(me,HIB"\n���ã����ĵ��������㣬����Ȼ�㿪��������Ҳ����������塣\n"NOR);
     
      me->apply_condition("fs_poison",1);
      me->start_perform(3,"���ĵ�");
      return 1;
}

string perform_name(){ return HIY"���ĵ�"NOR; }

int help(object me)
{
        write(HIR"\n������֮�����ĵ�����"NOR"\n\n");
        write(@HELP
	�����ɵĹ�����Ҫ����<��>�����¹������������������ζ
	������������ս���У�ƾ������ڹ������ڴ涾�Ƴ������˵е�
	һ�Ź��򡣡����ĵ��������ǽ���ҩ��ըҩ���ͨ��Ͷ���ķ�ʽ
	�˵��ˣ��Է�����������������ȱ�����������ĵ�ը��������
	�������˵ĺݶ���

	perform strike.lianxin

Ҫ��
	��ǰ�������� 1500 ����;
	����������� 2500 ���ϣ�
	�����Ʒ��ȼ� 150 ���ϣ�
	�����󷨵ȼ� 150 ���ϣ�
	�����Ʒ��ȼ� 150 ���ϣ�
	�����ڹ��ȼ� 150 ����;
	�������Ƶȼ� 150 ����;
	�������ޱ�����
        
HELP
        );
        return 1;
}