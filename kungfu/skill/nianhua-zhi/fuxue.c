// fuxue.c �黨ָ ���黨��Ѩ
// by hunthu //99.01.03
#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
		int i=me->query_skill("nianhua-zhi",1)+me->query_skill("sanhua-zhang",1);
		//me->set_temp()
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
           return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if(me->query_temp("weapon"))
      		return notify_fail("��������ʹ�á��黨ָ����\n");
        if((int)me->query_con() < 25)
           return notify_fail("����ǲ���,����ʹ����һ����!\n");

        if((int)me->query_skill("yijin-jing",1) < 120)
           return notify_fail("���׽�Ĺ�����������ʹ���黨��Ѩ!\n");

        if((int)me->query_skill("nianhua-zhi",1) < 120)
           return notify_fail("���ָ����Ϊ����,Ŀǰ������ʹ���黨��Ѩ����!\n");
        if (me->query_skill_prepared("finger") != "nianhua-zhi"
        || me->query_skill_mapped("finger") != "nianhua-zhi" )
                return notify_fail("��������黨ָ���ܳ����湦�� \n");

        if( me->query_skill_mapped("force") != "yijin-jing" )
                return notify_fail("����ڹ����ԡ�\n");

        if((int)me->query("max_neili")<1500)
              return notify_fail("���������Ϊ��Ƿ���\n");  
        if(target->query_temp("nhz/fuxue"))
              return notify_fail("�����˷�ʱ���ˣ��Է��Ѿ������黨ָ��Ѩ��\n");  
        if((int)me->query("neili") < 800)
           return notify_fail("���������ڲ���, ����ʹ���黨��Ѩ! \n");

        if( target->is_busy() )
           return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɢ�\n");
        
         msg = HIY "$N��¶����΢Ц����ָ���ᵯ�����ƺ��ڵ��仨���ϵĳ�¶�����µ��𻨰�һ�㣬\n"+
                  "ָ����������,����֮����һ�������������ס��$n��ȫ��ҪѨ,ʹ$n�������á�\n";
        
		// me->start_perform(6,"��Ѩ");    
         if(random(me->query("combat_exp")) > (int)target->query("combat_exp") / 2 ||random(me->query_skill("finger")) > (int)target->query_skill("parry")/ 2){
           msg +=  HIG"���$p��$P����ҪѨ! \n" NOR;
           target->set_temp("nhz/fuxue",1);
		   target->start_busy( random((int)me->query_skill("nianhua-zhi",1) / 100 + 2));
		   target->receive_damage("qi",random(2*me->query_skill("nianhua-zhi",1)));
           target->receive_damage("jing",random(2*me->query_skill("nianhua-zhi",1)));
		   target->apply_condition("no_exert",1);
		   target->add_temp("apply/attack",-i/2);
		   target->add_temp("apply/dodge",-i/2);
		   target->add_temp("apply/parry",-i/2);

           if (random(me->query_skill("nianhua-zhi",1))>=150)
               target->apply_condition("fx_busy", random(me->query_skill("finger")/20) + 1 + target->query_condition("fx_busy"));
           me->add("neili",-300);
           me->add("jingli",-100);
		   call_out("back", 6, target,i);
        }
        else {
           msg += HIM"����$p���о��������˿�ȥ��$Pһָ����Ǳ����м��š�\n" NOR;
           me->add("neili",-100);
           me->add("jingli",-50);
           me->start_busy(random(1)+1);
        }
		if (me->query_skill_mapped("finger")=="nianhua-zhi"
		&&me->query_skill_mapped("strike")=="sanhua-zhang"
		&&me->query_skill_prepared("strike")
		&&me->query_skill_prepared("finger"))
        {
			me->start_perform(2, "����Ѩ��");
        }
		else me->start_perform(6, "����Ѩ��");
        message_vision(msg, me, target);
        return 1;
}
void back(object target, int i)
{
        if (!target) return;
        target->add_temp("apply/attack", i/2);
        target->add_temp("apply/dodge", i/2);
        target->add_temp("apply/parry", i/2);
		target->delete_temp("nhz/fuxue");
}

int help(object me)
{
        write(HIB"\n�黨ָ֮����Ѩ����"NOR"\n");
        write(@HELP
		�黨ָԴ�ڷ�ҡ������黨����ҶһЦ���ĵ�ʣ���������ʮ������֮һ���黨ָΪ����׳��
		������֮����ר��ָͷ�龢֮һ�ֹ�����ʱ����ͬ�����������֮��������֮����ָ���
		������μ�ʵ֮ʯ������Ӧָ���顣����������֮�У��ǲ��ɶ�õķ������������ɢ������
		��ϣ���ʽ����Υ�����ּ������������ɮϲ�������������ࡣ

		��Ϊ�������ھ����������������������ڲ�֪�����б���Ѩ��������ʱ��Ѩ����Ȼ���㣬����
		�����������⿪�׽���Ķ����ܣ���ô�黨ָ���������Խ��Է���ȫ�������׷�ա�
        Ҫ��  ������� 1500 ���ϣ�      
                ��ǰ���� 800  ���ϣ�  
                �黨ָ�ȼ� 120 ���ϣ�
                �׽�ȼ� 120 ���ϣ�
				������� 25 ���ϣ�
                ����ָ��Ϊ�黨ָ��
                �����ޱ�����
				�����ɢ������ϣ�һ��ʩչ���黨ָ�������������ͷš�
                
                
HELP
        );
        return 1;
}