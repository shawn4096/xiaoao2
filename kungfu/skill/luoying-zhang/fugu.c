// fugu.c by Darken@Sj
// By Spiderii@ty �Ӹ�����ϴ�ֵ�����
inherit F_SSERVER;
#include <ansi.h>

string perform_name() { return HIB"���Ƕ�"NOR; }

int perform(object me, object target)
{
        string msg;
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target))
                return notify_fail("����û������ˡ�\n");
        if(target==me)
                return notify_fail("�㲻�ܹ����Լ���\n");
        if( target->query("combat_exp")< 100000)
                 return notify_fail("����ĳ�̫���ˣ������޸���֮�������Ҳ�µ����֣�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�ø��Ƕ���\n");   
        if( environment(me)->query("no_fight") )
                return notify_fail("���ﲻ��ս����\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 200 )
                return notify_fail("��ı̺���������Ϊδ�����޷�ʹ�ø��Ƕ���\n");
        if( (int)me->query_skill("luoying-zhang",1) < 200 )
                return notify_fail("����Ʒ���Ϊ���㡣\n");
        if( (int)me->query_skill("throwing",1) < 200 )
                return notify_fail("��İ�����Ϊ���㡣\n");
        if( (int)me->query("neili") < 2000 )
                return notify_fail("����������̫����\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("�����ھ���̫����\n");
		if( me->query("no_pk") && userp(target) && (!me->query_temp("xyjob") || !target->query_temp("xyjob")))
				return notify_fail("���Ѿ��˳���������������ʵʵ�İɡ�\n");

		if( target->query("no_pk") && userp(me) && (!me->query_temp("xyjob") || !target->query_temp("xyjob")))
				return notify_fail( target->name()+"�Ѿ��˳������ˣ������˴������˰ɣ�\n");

        msg = HIY"$N�������ߵ�$n���ᣬ���ĵ����������\n"NOR;
        if (random(me->query_dex()) > target->query_int()/2) {
                target->add("thd/fugu",1);
                msg+= HIR"$NͻȻ���������$n��������һ�£�$n�����ú���ʲô����һ�¡�\n"NOR;
                if (me->query_skill("luoying-zhang",1)<350)
                   me->start_busy(2);
        } else {
                me->start_busy(2+random(3));
                msg += CYN"$n��$N��ɫ���죬�첽���˿�ȥ��\n"NOR;
        }
        message_vision(msg, me, target);
        me->add("neili",-200);
        me->add("jing",-100);
        return 1;
}

int help(object me)
{
        write(HIG"\n�����Ƕ�--ʩ�־�����"NOR"\n");
        write(@HELP

	���һ������ƶ��е�ϸС�ֶ�������Ӣ���Ƶ��ٶ�
	��ϱ̺����������ھ���ֲ���������ڡ����ܵ��̺�
	�������ھ��߶�ʱ�����Ծͻᷢ����
	
ָ�perform strike.fugu

Ҫ��
	�̺��������ȼ� 200 ���ϣ�
	��Ӣ���Ƶȼ� 200 ���ϣ�
	���������ĵȼ� 200 ���ϣ�
	������������� 2000 ���ϣ�
	��ս������ʹ�á�
HELP
        );
        return 1;
}


