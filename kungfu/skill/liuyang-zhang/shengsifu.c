// shengsifu.c by sohu@xojh ������
// 
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
       object obj,obj2,tar;
       string msg;
       int assi_int,damage;
       int me_strike;
       int target_dodge;
       int me_bmsg,tar_bmsg;
       if( !target ) target = offensive_target(me);
       if( !target 
		   ||!living(target)
		   || !me->is_fighting(target) )
                return notify_fail("����������ֻ����ս����ʹ�á�\n");       
       if(!target)
             return notify_fail("�����˭����������\n");
       if(!objectp(tar = present(target, environment(me))))
            return notify_fail("����û������Ը�������ˡ�\n");
       if(!tar->is_character())
                return notify_fail("�����һ�㣬�ǲ���������,�����и��ԡ�\n");
       if(!living(tar))
               return notify_fail(tar->name()+"�������ˣ���Ҫ�ݲ�����������̫����?\n");
       if(tar==me) return notify_fail("��Ҫ���Լ��£��㲻����Ű��ɣ�\n");
       
	   if(me->is_busy())
             return notify_fail("����æ����˵ƴ�����¡�\n");
       if(me->query_temp("weapon"))
             return notify_fail("�������б������޷�ʩչ��������\n");

	   if(environment(me)->query("no_fight"))
                return notify_fail("���������ʩչ������\n");
     
       if( (int)me->query_skill("liuyang-zhang", 1) < 450 )
             return notify_fail("�����ɽ�����Ʋ�����죬��������������\n");
       if( (int)me->query_skill("beiming-shengong", 1) < 450 )
		  if( (int)me->query_skill("bahuang-gong", 1) < 450 )
             return notify_fail("��ı�ڤ�񹦻�˻Ĺ�������죬��������������\n");
	   if( me->query_skill_mapped("strike")!="liuyang-zhang"
			||me->query_skill_prepared("strike")!="liuyang-zhang")
             return notify_fail("��û�м��������ƣ���������������\n");

	   if( (int)me->query("neili", 1) < 5000 )
             return notify_fail("����������̫������������������\n");
       if (!objectp(obj=present("jiudai", me))&&!objectp(obj2=present("hu lu",me)))
             return notify_fail("������û�оƴ�����ƴ���û��Һ�壬���ܻ�ˮΪ����\n");
       
	   if (me->query_skill_mapped("force")=="beiming-shengong")
		   msg = HIB "$N���������а����ڹ�����ת��ڤ�����������о�ˮ�����߰�Ƭ��������$n����������ơ�\n"NOR;
       else if (me->query_skill_mapped("force")=="bahuang-gong")
           msg = HIY "$N���������а����ڹ�����ת�˻�����Ψ�Ҷ��𹦣������о�ˮ�����߰�Ƭ��������$n����������ơ�\n"NOR;
	   if (target->query_condition("shengsi_poison"))
	   {
		   return notify_fail("�Է��Ѿ�������������������˷Ѿ���\n");
	   }
       //me->start_busy(1);
       me_strike=random( (int) me->query_skill("liuyang-zhang",1) );
       target_dodge=random(target->query_skill("dodge")) ;
       assi_int=random(me->query("int")-target->query("int"))+ random(3);
	   
	   damage=me->query_skill("liuyang-zhang",1)+me->query_skill("strike",1)+me->query_skill("force",1);
	   damage=damage*2+random(damage);
       
	   if( assi_int>1 && me->query_int()>50 )
            me_strike = me_strike*assi_int;
       if( me_strike > target_dodge
		  || random(me->query("neili"))>target->query("neili")/2
		  && (int) random(me->query_skill("liuyang-zhang",1)) > (int) tar->query_skill("liuyang-zhang",1)/4            
         ){
             msg += HIW "\n$p���ü��"HIR"��ȱ��Ѩ��"HIW"��΢΢һ��������С��"HIR"������Ѩ��"HIW"������"HIR"������Ѩ��"HIW"���ϱ�"HIR"����ȪѨ��"HIW"Ҳ�����쬵ء�\n" NOR;
             target->apply_condition("shengsi_poison",2+random(2));
             if( (int) me->query_skill("liuyang-zhang",1)> 450 )
             {
                msg += HIY "\n���$pæ�������ֵ�����Ȼ���"HIB"������Ѩ��"HIY"������"HIB"�����Ѩ��"HIY"������"HIB"��־��Ѩ��"HIY"����Ҳ��΢΢һ����\n"NOR;
                target->receive_wound("qi",damage/3,me);
                target->receive_wound("jing", damage/5,me);
                target->add_condition("shengsi_poison", 2+random(2));
             }
             target->receive_wound("qi",damage/2,me);
             target->receive_wound("jing", damage/4,me);
             //target->apply_condition("shengsi_poison",  target->query_condition("shengsi_poison")+ 10);
             me->add("neili", -random(1000));
             target->start_busy(1+random(2));
             
       } else if( (int) me->query_skill("liuyang-zhang",1) < (int) tar->query_skill("liuyang-zhang",1) ||
                random((int) me->query_skill("liuyang-zhang",1)) < (int) tar->query_skill("douzhuan-xingyi",1)
              ){
                        //����
                    msg += HIB "����$p�����ϵ���Ǳ�˱�ڤ������ȫ����ͬ�����ַ�����$P��������!\n"NOR;
                    msg += HIY "$P���һ��������!�������������С�麮�����������Լ����ϡ�\n"NOR;
                    me->apply_condition("shengsi_poison",1+random(1));
                    me->receive_wound("qi",damage/3,me);
                    me->receive_wound("jing", damage/5,me);
                    me->add("neili", -100);
                    me->start_busy(2+random(2));
                  
                  }else
              {
                 msg += "����$p��æ����һ�ԣ����˿�ȥ��\n" NOR;
                 me->start_busy(1+random(2));
              }
    message_vision(msg, me, target);
    //me->start_perform(2,"������");
    return 1;
}
string perform_name(){ return HIB"������"NOR; }
int help(object me)
{
   write(WHT"\n��ɽ������֮��"HIB"������"WHT"��"NOR"\n");
         write(@HELP
	����ɽͯ�ѱ�����������Ļʹ���������ڼ䣬����ɽ��÷�ִ��ڸ������
	Ϊ�Ը�����ˮ�����һ������ɽ�����ƽ̸������������񲻿�����ɱ�ˣ��᲻
	��ѧ�����������뿪��Ϊ�ˣ���ɽͯ����ı�����������������������ټٳƽ�
	���ƽ�֮������������������ɽ�����ƵĹ����������ڡ����������ˮ׷���
	��Ҫɱ��ɽͯ��ʱ������������ʹ���˵ڶ��С�������ѩ���������С�����
	�������Լ���������������н�������ˮ�Ĺ�����
	����ɽͯ����������̳����չ����������ʮ��������ʮ����������������
	���������ʹ����ɽ�����ư����ǰγ���������Ӯ�������������棬����Ҳƾ
	����ɽ����������������������������ͷ����ܡ�
	��Ҫע�⣬����������������תת��������Ϊ����������������Լ�Ϊ��Ҫ��
    ֻ�б�ڤ�񹦡��˻Ĺ���С���෽��ʩչ��

	ָ��: perform strike.shengsifu

Ҫ�� 
	�˻�����Ψ�Ҷ���450�� ��ڤ��450��
	��ɽ�����Ƶȼ� 450 ����
	��ǰ������С�� 5000��
	���ϳ��оƴ����о�ˮ��Һ�壻
        
HELP
    );
        return 1;
}

