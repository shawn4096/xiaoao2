// sanshi.c ��ʬ����
// cre by sohu@xojh Ͷ����
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
       object co;

       if( !target ) target = offensive_target(me);

       if( !target || !me->is_fighting(target) )
            return notify_fail("����ʬ���񶾡�ֻ����ս���жԶ���ʹ�á�\n");

       if( objectp(me->query_temp("weapon")) )
            return notify_fail("�������ֲ���ʹ�á���ʬ���񶾡���\n");

       if( (int)me->query_skill("mantian-huayu", 1) < 250 )
            return notify_fail("������컨�껹������죬ʹ��������ʬ���񶾡�������\n");
       if( (int)me->query("neili") < 2500 )
            return notify_fail("�������������ʹ��������ʬ���񶾡�������\n");
	   if( (int)me->query("jingli") < 1500 )
            return notify_fail("��ľ���������ʹ��������ʬ���񶾡�������\n");
       if (me->query_skill_mapped("force") != "tianmo-gong" )
          if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("����ʹ�õ������ڹ����ԡ�\n"); 
                
       if(!me->query_skill("xixing-dafa", 1))
          if(me->query_skill("tianmo-gong", 1) < 250)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ��������ʬ���񶾡���\n");  

       if((int)me->query_skill("poison",1)<120)
            return notify_fail("�㶾�Ʋ����޷�ʹ����ʬ���񶾡�\n"); 
       
	   co=present("sanshi dan",me);       

       if (!co)
           return notify_fail("������û����ʬ���񵤣����ʹ����ʬ����!\n");     

       if (me->query_skill_prepared("hand") != "tianmo-shou"
        || me->query_skill_mapped("throwing") != "mantian-huayu"
        || me->query_skill_mapped("parry") != "mantian-huayu")
           return notify_fail("�������޷�ʹ�á���ʬ���񶾡���\n");                                                                                 

       if( (int)me->query("max_neili") < 1500) 
           return notify_fail("������̫����ʹ��������ʬ���񶾡���\n");      

       if( (int)me->query("neili") < 1000)
           return notify_fail("����������̫����ʹ��������ʬ���񶾡���\n");

       message_vision(HIB"\n$N�ӿڴ�������һ����ʬ���񵤣���$n�ſڴ��֮�ʣ���Ȼ������һ����Ӱ����$n�Ŀ��У�\n"NOR,me,target);
       call_out("destroying", 1, co);
       if (!target->is_killing(me))
          me->kill_ob(target);
       me->add("neili", - (250 + me->query_skill("force")));
       if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2
        && me->query_str() > (int)target->query_dex()/2){ 
           message_vision(HIG"\n$n���˹����������һʱ�������޴룬�����޼�������ʶ������������ҩ�衣\n"NOR, me, target);
           me->add("max_neili", -random(1));
		   me->add("neili", -random(1000));
	       if (userp(target))
		      me->add_condition("killer", 90);
           target->set_temp("last_damage_from", "��ʬ��������");
		   target->apply_condition("sansi_poison", 5+random(3));
           target->receive_wound("jing",random(2000),me);
		   message_vision(HIC"$nһ�����¶��������в����㷲�����������������С�������䶯�ĸо������в��ɴ󺧣�\n"NOR,me,target);
		   target->apply_condition("no_exert",1);

           return 1;  
       }
       else if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/3
         || random(me->query("neili")) > target->query("neili")/2){
          message_vision(HIB"\n$n���²��ã���æ����ֱ����ʬ���񵤴������ӹ���û�д��С�\n"NOR,me,target);
          tell_object(target,HIB"\n����Ȼ��ʱ�ܿ��˶�ʬ����һ���ȳ�����ǣ�����������ʬ�����ˡ�\n"NOR);
          me->add("neili", -400);
	      if (userp(target))
		     me->add_condition("killer", 15);
          target->apply_condition("sansi_poison", 3+random(3));
          me->start_busy(1);
          target->add_busy(1);
          return 1;
      }
      message_vision(HIB"\n$n���г���һ����Х��˫����������������������������·��\n"NOR,me,target);
      tell_object(me,HIB"\n���ã���ʬ�����������㣬����Ȼ�㿪��������Ҳ����������塣\n"NOR);
      me->set_temp("last_damage_from", "��ʬ��������");
      me->receive_damage("qi", 2500,me);
      me->receive_wound("qi", 1500,me);
      me->add("neili", -300);
      me->apply_condition("sansi_poison", random(3));
      me->start_perform(2,"��ʬ����");
      return 1;
}

void destroying(object obj)
{
        destruct(obj);
}
string perform_name(){ return HIB"��ʬ����"NOR; }

int help(object me)
{
        write(HIC"\n���컨��"+HIB"����ʬ���񶾡�"NOR"\n");
        write(@HELP
	���컨�����������������������ս�����ܽ�����������
	һ���似���Ⱥ��ɶ�λ�������Ϻͽ������Ͼ������γ�
	��һ��������ѧ�����컨����������밵����ϣ�Ч����
	������������и������ƣ����˱���������һλ�����ö�
	����ҩ�Ĵ�ʦ�������ݻ�����ħ���У���ʬ����������һ
	�ֽ�������ʬ���񶾡����涾���������ⰵ���ַ�ʩչ��
	��������ʩչ��������������Է����У���Ȼ���Է�����
	���Ҳ���Է����أ���������á�������ע�⣺ʩչ��
	���������ʬ���񵤡�
	
	ָ�perform throwing.sanshi
	
Ҫ��
	��ħ�������Ǵ�Ҫ��  250
	���컨��Ҫ��250
	�����ڹ�Ҫ��250
	��������Ҫ��150
	��ǰ����״̬: 2500
	��ǰ����Ҫ��1500
	����Ҫ����ڣ�120

HELP
        );
        return 1;
}
