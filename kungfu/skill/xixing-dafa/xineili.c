// xineili.c for xixin-dafa

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;


int exert(object me, object target)
{
        int sp, dp;
        int skill=me->query_skill("xixing-dafa",1);
        if( !target ) target = offensive_target(me);
     
        if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("���Ǵ󷨡���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("����ʹ�õ������ڹ����ԣ��޷�ʵ�֡�����������\n");  
		
		if( !objectp(target) || target->query("id") == "mu ren" )
                return notify_fail("��Ҫ��ȡ˭��������\n");
        if ( me->query("quest/xxdf/pass")<2 )
                return notify_fail("����˵�����Ǵ����⹦�ܣ�����ȴδ�������еĴ��ڣ�����ʹ�ã�\n");
        if ( me->query_temp("xixing/suckneili") )
                return notify_fail("��������ȡ������\n");
      
        if( (int)me->query_skill("xixing-dafa",1) < 400 )
                return notify_fail("������Ǵ󷨹���������������ȡ�Է���������\n");

        if( (int)me->query("neili",1) < 5000 )
                return notify_fail("�����������������ʹ�����Ǵ󷨡�\n");

        if( (int)target->query("max_neili") <= 0 )
                return notify_fail( target->name() +"û���κ�������\n");
        if( (int)target->query("neili") < (int)target->query("max_neili") / 10)
                return notify_fail( target->name() +
                        "�Ѿ�������ɢ�����Ѿ��޷�����������ȡ�κ������ˣ�\n");

        message_vision(
                HIR "$N��ɫһ�䣬����ͻȻ������͵ض�׼$n�����д�Ѩ������ȥ��\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp =( me->query_skill("force",1) + me->query_skill("dodge",1))*me->query("str")/100;
        dp = (target->query_skill("force",1) + target->query_skill("parry",1) )*me->query("con")/100;
        //�趨���
        me->set_temp("xixing/suckneili", 1);              

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "��پ�����΢ʹ����ͬ��������˸�С�ף�ȫ��������ˮ����ѭ�׷�й������\n "+HIY"�����д��һ������Ȼ�ŵô���������" NOR);
                tell_object(me, HIG "�����" + target->name() + "���������͹�ѨԴԴ���������˽�����\n" NOR);

                target->add("neili", -2*skill );
                me->add("neili", skill);
                me->add_busy(2+random(1));
                target->add_busy(2+random(1));
				target->apply_condition("no_exert",2);
                me->add("neili", -100);
                call_out("del_sucked", 1, me,target);
        }
        else
        {       
                message_vision(HIY "����$p������$P����ͼ����������˿�ȥ��\n" NOR, me, target);
                me->start_busy(2+random(1));
                call_out("del_sucked", 2, me,target);
        }
     
        return 1;
}

void del_sucked(object me,object target)
{
       int sp,dp,skill;
		sp =(int)((me->query_skill("force",1) + me->query_skill("dodge",1))*me->query("str")/100);
        dp = (int)(1+(target->query_skill("force",1) + target->query_skill("parry",1))*(target->query("con")+1)/100);
		skill=me->query_skill("xixing-dafa",1)+me->query_skill("force",1);
	   if( random(sp+dp) > dp && me->is_fighting(target))
       {
               tell_object(target, HIR "���;������������̰��ʹ����Ȼ�ܵ��Է����Ǵ󷨵�Ӱ�졣\n" NOR);
               tell_object(me, HIG "�����" + target->name() + "���������������ԴԴ���������˽�����\n" NOR);

               target->add("neili",-skill*3);
               me->add("neili",skill);            
               if (!random(3)) target->add("max_neili",-random(10));
               
               me->start_busy(1+random(2));
               target->start_busy(2+random(3));
			   target->kill_ob(me); 
               me->add("neili", -100);
			   //remove_call_out("del_sucked");
               call_out("del_sucked", 1, me,target);
        }
		else {
          message_vision(HIC "$n�������Ա�һ�������ڶ㿪��$N�����Ǵ󷨵�Ӱ�졣\n" NOR,me,target);
          target->kill_ob(me);  
		  //if ( me->query_temp("xixing/suckneili") )
          me->delete_temp("xixing/suckneili");
		  me->add_busy(2);
		  return;
		}

}
string exert_name(){ return HIG"����������"NOR; }
int help(object me)
{
        write(HIR"\n���Ǵ�"+HIG"����������"NOR"\n");
        write(@HELP
		���Ǵ������������ǰ���������е��ش��似���뵱����������������񼼣�
		��һΪ�������䣬���Ϊ���Ǵ󷨣�ǰ�˽�����������λʱѡ����ϰ���Ǵ󷨡�
		��Ȼ�����ݺ��������ܵ����ɣ������Ǵ󷨵Ĺ����ǿ��Ҳ����ѡ�����Ҫԭ��
		�����ڣ�������Ϊ̸֮��ɫ�䡣����������������һս�������Ǵ��س�����
		�ɼ�������������
		��ӹ�������������޶���Ц�������н����Ǵ󷨹����ڱ�ڤ�񹦣������ڱ�վ
		�����Ǵ��У�����ǿ�����ǵ��ص㡣��վ���Ǵ��ܹ���Ϊ�������⡣		
		����������Ҫ����ȡ�Է����������ǹ��������߲���ʩչ��
		Ҫ��
			�����ڹ��ȼ� 400 ���ϣ�
			���Ǵ󷨵ȼ� 400 ���ϣ�
			��ǰ����     5000 ���ϡ�

HELP
        );
        return 1;
}
