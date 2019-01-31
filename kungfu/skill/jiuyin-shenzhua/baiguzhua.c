// Code of JHSH
// Modified by haiyan@huaxia

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object report;
        int damage,lvl,lvl1,k,l,ap,dp;
        string str;

        if (!target ) target = offensive_target(me);

        if (!target||!target->is_character()||!me->is_fighting(target) )
                return notify_fail("���׹�ץ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������������������ʹ�����׹�ץ����\n");

        if ((lvl=(int)me->query_skill("jiuyin-shenzhua",1))< 450)
                return notify_fail("��ľ�����צ��Ϊ������\n");

        if ((lvl1=(int)me->query_skill("cuixin-zhang",1))< 450)
                return notify_fail("��Ĵ�������Ϊ������\n");

        if (userp(me) && !me->query("quest/jiuyin2/jybgz/pass"))
                return notify_fail("����δ��÷������̣�����ʹ�á��׹�ץ��������У�\n");

        if (me->query("jiali") < 200)
                return notify_fail("��ĳ�����ô�ᣬ�ֺα�ʹ��ɱ���أ�\n");
		if (me->query_skill_mapped("claw")!="jiuyin-baiguzhua"
			||me->query_skill_prepared("claw")!="jiuyin-baiguzhua")
                return notify_fail("����δ����������צ��\n");

        if (me->query("neili")<=lvl*4) return notify_fail("�������������\n");

        if (me->query("jingli")<=lvl) return notify_fail("��ľ���������\n");

        message_vision(HIW+BLU "\n$NͻȻ�����ץ�������漴������硣�����ָ���������������͵ľ�������$n�����顣\n"
			+"����$N�ĳ�����ʽȴ����ǰ����ͬ����ʽ�󿪴�ϣ���Ϊ�������������\n" NOR, me,target);

        ap = me->query_skill("claw",1) + me->query_skill("force",1) + me->query_str()*10; 
        ap += me->query("jiali")*2/3;
        dp = target->query_skill("dodge",1) + target->query_skill("force",1) + target->query_con()*10; 

        me->add("neili", -lvl);
        if (!target->is_killing(me->query("id"))) target->kill_ob(me);

		if( me->query("shen") > -1000000 && me->query("PKS") < 10 )
			return notify_fail("�㲻���ݶ����޷�ʹ�����׹�ץ���ľ�����\n");
		if(me->query("no_pk") )
			return notify_fail("��ϴ����ң��޷�ʹ�����׹�ץ���ľ�����\n");
        
		if (!living(target))
        {
                message_vision(HIR "ֻ���۵�һ���죬$N�������ָ�Ѳ�����$n��ͷ����$n��ʱ����������\n\n" NOR, me,target);
                target->die(me);
                return 1;
        }

        if (ap / 2 + random(ap) < dp )
		{  
                message_vision(CYN "$n��֪���ң�����$N������ǳ����Ȼһ�����У�ȴ����ǿ��֮ĩ����Ҳ��������ȥ�ˡ�\n\n" NOR, me,target);
                me->add_busy(1);
                return 1;
        }

        if (ap / 2 + random(ap) > dp
			||random(me->query("combat_exp"))>target->query("combat_exp")/2
			|| !living(target)) 
        {
                damage = (lvl + lvl1)*2 + me->query_str()*me->query("jiali")*3/target->query_con();
                
				if (damage<=1000) 
                        message_vision(BLU "$n��֪��������������������㡣���ǿ����ܹ������Ѿ�����һ���亹��\n\n" NOR, me,target);
                else {
                        if ((int)damage >= target->query("eff_qi")) 
                        {
                                message_vision(HIR "ֻ���۵�һ���죬$N�������ָ�Ѳ�����$n��ͷ����\n\n" NOR, me,target);
                                target->receive_wound("qi",1,me);
                                target->die(me);
                                return 1;
                        }
                        message_vision(MAG "$n��֪��������������������㡣��Ȼ�ܹ�������Ҫ��������ȴ��ץ�����Ѫ�ۡ�\n\n" NOR, me,target);
                        target->receive_wound("qi",damage,me);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        message_vision("($N"+str+")\n", target);
                }
                target->add_busy(1+random(3));
                me->add("neili", -lvl);
                me->add_busy(1);
                return 1;
        }
        if (ap / 2 + random(ap) > dp * 3/2 || !living(target)){  
                damage=(2+random((me->query_str()*2+me->query("jiali"))/100))*lvl;
                if ((int)damage >= target->query("eff_qi")) {
                        message_vision(HIR "ֻ���۵�һ���죬$N�������ָ�Ѳ�����$n��ͷ����\n\n" NOR, me,target);
                        target->die(me);
                        return 1;
                }
                if ((int)damage/target->query("eff_qi")*100>=50&&(int)damage/target->query("eff_qi")*100<100)
                        message_vision(HIR "ֻ��৵�һ����$n��������ѱ�����һ���ͷƤ����ʱѪ����ע��\n\n" NOR, me,target);
                if ((int)damage/target->query("eff_qi")*100<50)
                        message_vision(HIR "ֻ�����һ����$n�������ѱ�ץ����������Ѫ�����צ�ۡ�\n\n" NOR, me,target);
                target->receive_wound("qi", damage, me);
                str = COMBAT_D->status_msg((int)target->query("eff_qi") * 100 /(int)target->query("max_qi"));
                message_vision("($N"+str+")\n", target);
                target->start_busy(1+random(3));
                me->add("neili", -lvl*2);
                me->start_busy(4);
                return 1;
        }
        message_vision(HIC "$n������������ݵ�������˰벽�����ѱܿ���$N������һ����\n\n" NOR, me,target);
        tell_object(me, HIR"�����һ����ֻ���ʹ˵��֡�����ȴ���������������������ʱ¶���˼���Ŀ��š�\n\n"NOR);
        me->add_busy(2+random(3));
		me->start_perform(2,"");
        return 1;
}


string perform_name(){ return HBWHT+HIB"�׹�צ"NOR; }

int help(object me)
{
        write(RED"\n������צ֮���׹�צ����"NOR"\n\n");
        write(@HELP
	�����׹�צ���Ǿ����澭�¾�Ĺ���Ϊһ������
	�����Ѽ������书�����ɣ����ھ��ף�����������
	��֮����������÷������˲������Ͼ��书��ֻƾ
	���˴�Ħ���� ����ָ�������޼᲻�ƣ��ݵ����ԣ�
	�紩���� ����������ͷ����ϰ���Ź��򡣵��˹�
	���������ף���������������Ҳ�ɾ�����׹�צ��
	�պ�������
	
	�׹�צ��������͸ָ�䣬�ᴩͷ������������ɱ��
	�ĺ��У�ϴ������޷�ʩչ����������÷�������
	
	perform claw.baiguzhua

Ҫ��  
	��ǰ���������� 2500 ���ϣ�
	������������� 15000 ���ϣ�
	��ǰ���������� 800 ���ϣ�
	������צ�ĵȼ� 450 ���ϣ�
	����צ���ĵȼ� 450 ���ϣ�
	�����ڹ��ĵȼ� 450 ���ϣ�
	����צ��Ϊ������צ��                
	��צ��ΪΪ������צ��
	�������1M��ɱ��������10���޷�ʹ��;
	�����ޱ����ҷ�ϴ����ң�	

HELP
        );
        return 1;
}
