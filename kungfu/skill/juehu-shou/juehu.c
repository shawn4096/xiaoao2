#include <ansi.h>
#include <combat.h>

#define JUEHU "��" HIR "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        
        object weapon;
        int ap, dp;
        string wn, msg;
	    int extra;
	    int i,a;
        if (! target) target = offensive_target(me);


        if (! target || ! me->is_fighting(target))
                return notify_fail(JUEHU "ֻ����ս���жԶ���ʹ�á�\n");
        if (!me->query("quest/wudang/juehu"))
                return notify_fail("����Ҫ�õ��������ָ�㷽��ʹ�ô��о����־�����\n");
        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ�þ����־�����\n");
        if( (int)me->query_skill("force", 1) < 300 )
                return notify_fail("��Ļ����ڹ�����̫ǳ�ˡ�\n");
        if( (int)me->query_skill("hand", 1) < 300 )
                return notify_fail("��Ļ����ַ�̫ǳ�ˡ�\n");
		if( (int)me->query("max_neili", 1) < 3500 )
                return notify_fail("��Ĺ���̫ǳ�ˡ�\n");
        if( (int)me->query("neili", 1) < 1500 )
                return notify_fail("��Ĺ�������ʩչ�����似��\n");
		if( (int)me->query("max_jingli", 1) < 1500 )
                return notify_fail("��Ĺ���̫ǳ�ˡ�\n");
       // if (userp(me) && me->query("shen") < 10000)
         //       return notify_fail(HIC "\n��������������ʩչ���У���ͻȻ�뵽����������"
             //                      "��һ����룬���ò���;�����˹�����\n" NOR);

        if ((int)me->query_skill("juehu-shou", 1) < 300)
                return notify_fail("��Ļ�צ�����ֲ�����죬����ʩչ�����־�����\n");

        if (me->query_skill_mapped("hand") != "juehu-shou")
                return notify_fail("��û�м�����צ�����֣�����ʩչ�����־�����\n");
        if (me->query_skill_prepared("hand") != "juehu-shou")
                return notify_fail("��û�м�����צ�����֣�����ʩչ�����־�����\n");
       // if (me->query_skill_mapped("parry") != "juehu-shou")
      //          return notify_fail("��û��׼��ʹ�û�צ�����֣��޷�ʹ��" JUEHU "��\n");

        if (me->query("neili") < 1500)
                return notify_fail("��������������������ʩչ�����־�����\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
	       extra = me->query_skill("juehu-shou",1) / 4;
	       extra += me->query_skill("yinyun-ziqi",1) / 6;
		   a=me->query_skill("juehu-shou",1)/100;
           if (a> 5) a=5;
	       me->add_temp("apply/attack", extra*3/2);	
	       me->add_temp("apply/damage", extra);
           me->add_temp("apply/hand", extra);
		   me->set_temp("wudang/juehu",1);
	       message_vision(HBMAG "$N���һ��������Ϊצ��˫צ��������צӰ����������һ����$nץȥ��\n"NOR,me, target);
		   msg = HIR "$N˫�ֻ���������Ӱ����$n��Ҫ��ץȥ��һצ��\n"NOR;
		   message_vision(msg,me,target);
		  // if (me->is_fighting()&&objectp(target)
			     COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
	       if (me->is_fighting()&&objectp(target))
			  {
			   message_vision(HIR"$N˫�ֻ���������Ӱ����$n��Ҫ��ץȥ�ڶ�צ��\n"NOR,me,target);
			   COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			   }
	        if (me->is_fighting()&&objectp(target))
			  {
			   message_vision(HIR"$N˫�ֻ���������Ӱ����$n��Ҫ��ץȥ����צ��\n"NOR,me,target);
			   COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			   }
	       if (me->is_fighting()&&objectp(target)&& a>=4)
			  {
			   message_vision(HIR"$N˫�ֻ���������Ӱ����$n��Ҫ��ץȥ����צ��\n"NOR,me,target);
			   COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			   }

		   if (me->is_fighting()&&objectp(target)&& a>=5)
			  {
			   message_vision(HIR"$N˫�ֻ���������Ӱ����$n��Ҫ��ץȥ����צ��\n"NOR,me,target);
			   COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			   }
	/*		if (me->is_fighting()&&living(target)&& a>=6)
			  {
			   message_vision(HIR"$N˫�ֻ���������Ӱ����$n��Ҫ��ץȥ����צ��\n"NOR,me,target);
			   COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			   }*/
	        me->add_temp("apply/attack", -extra*3/2);
	        me->add_temp("apply/damage", -extra);
	        me->add_temp("apply/hand", -extra);
	        me->delete_temp("wudang/juehu",1);
            me->add("neili", - 50 * a);      
        
          if (random(me->query_skill("hand",1)) > target->query_skill("parry",1) / 2&&me->query_skill("juehu-shou",1)>350) {
                //me->start_busy(2);
                damage = me->query_skill("juehu-shou", 1);
                damage = damage * 3 + random(damage)* 6;
                target->receive_damge("qi",damage,me);
                target->receive_wound("qi",damage/3,me);
				target->receive_wound("jing",damage/8,me);
                msg =  "\n"NOR;
	            msg += RED HIR "���$p" HIR "һ���Һ���û���м�ס$P"+HIR "�����Ĺ��ƣ���ץ��Ƥ����룬��Ѫ�ɽ���\n" NOR;

                message_vision(msg,me,target);
               if (random(6)>3 && target->query("gender")=="����"
			       && damage>5000
                   && me->query_skill("juehu-shou",1)> 350)
                  {
                    message_vision(HIY"\n$nҪ������ȻӲ������$N˺������������Ƥ����룬��Ѫ�ɽ�\n" NOR, me,target);
                    //target->set("gender","����");
					target->apply_condition("no_exert",1);                    
					target->add_busy(3);
					target->apply_condition("jueshu_hurt",1+random(2));
                  }				
                me->add("neili", -400);               
         } else
          {
                me->start_busy(3);
	            me->add("neili", -400);
                if ((int)me->query("shen") > 0)
                	me->add("shen",  -random(100));
                    msg += CYN "����$p" CYN "������$N"
                       CYN "����ͼ���㿪������ɱ�š�\n" NOR;
        }
        message_combatd(msg, me, target);
        me->start_perform(5, "�������֡�");
        return 1;
}

string perform_name(){ return HIR"����"NOR; }

int help(object me)
{
        write(HIC"\n��צ������֮"+HIR"��������"NOR"\n\n");
        write(@HELP
	˵���������������䵱���������������������似������֮ʱΪʦ��������������������
	����Ϊ�˲���ҡͷ��������������Ϊ�Լ�������Ȼɱ�������㣬�����ٴαչأ�ֱ��
	������һ��ʽ�����ľ�������ʽ��˭֪��������ȴΪ�˴�Ϊ��ŭ�������������ۣ�˵
	������ѧ���кݶ���ר���������ۣ�ʹ�˶��Ӿ��ʵ�˽�������֮�о�����������
	�����ǻ֣̿�������ش��С������ں�������Χ���䵱ɽʱ��Ϊ������䵱��Σ����
	�������ٴν����似���ڸ�ͬ��ʦ�ܡ��ɼ���ɱ����������������Ϊ���书���䵱��
	�ڴ���书�Ļ�����Υ��������ֻ���ǳ������ڵ��似����Ե�ɺ�֮�£����������
	����̡���Ҫע����ǣ�ѧ�˴��У��ڰ�ʦ֮ǰ���ܴ���150�������������˻����
	����ȡ���ü��ܣ���������ء�
	
	ָ��;perform hand.juehu

Ҫ��
	��ǰ����Ҫ�� 1500 ���ϣ�
	�������Ҫ�� 3500 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	�����ַ��ȼ� 300 ���ϣ�
	�����ڹ��ȼ� 300 ���ϡ�
	�����ַ�Ϊ��צ�����֣�		            

HELP
        );
        return 1;
}
                                                         