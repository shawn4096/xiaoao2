// chaofeng.c ���񳯷�
// cck 13/6/97
//edit by sohu
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon,tweapon;
        string msg;
        string msg1;
	
		int skill;
		skill=me->query_skill("qingxin-jian",1);

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("�����񳯷ֻ����ս���жԶ���ʹ�á�\n");
		tweapon=target->query_temp("weapon");
        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( (int)me->query_skill("qingxin-jian", 1) < 100 )
                return notify_fail("����������ƽ�������죬����ʹ�á����񳯷��\n");

        if( (int)me->query_skill("tianmo-gong", 1) < 100 )
                return notify_fail("�����ħ���ȼ�����������ʹ�á����񳯷��\n");
		if( me->query_skill_mapped("sword")!="qingxin-jian" 
			||me->query_skill_mapped("parry")!="qingxin-jian" )
                return notify_fail("��û�ܼ����������ƽ�������ʹ�á����񳯷��\n");
		if( (int)me->query_dex() < 30 )
                return notify_fail("�����񳯷��Ҫ�߱�������ĺ���������30������ʹ�á����񳯷��\n");

        if( (int)me->query("neili", 1) < 250 )
                return notify_fail("����������̫��������ʹ�á����񳯷��\n");
        if( (int)me->query("jingli", 1) < 200 )
                return notify_fail("�����ھ���̫��������ʹ�á����񳯷��\n");         
             
		if( me->query_temp("qxj/chaofeng") )
                return notify_fail("������ʹ�á����񳯷��\n");
        
		message_vision(HIM "$N˵�������ȸ�û������ף�������磬һ�������񳯷����˹���,$n�мܲ�����ֻ�ö�����ȥ��\n" NOR,me,target);
       // msg1 = BBLU+HIY "$N��Хһ���������ָ,���ƹ��쵫ȴ�����ޱȡ�\n" NOR;

     //   message_vision(msg, me, target);
		//ǿ���¶�npc�Ĺ���
		if (!userp(target)) {
			skill=skill+me->query_skill("qingxin-jian",1)/6;
			target->start_busy(1);
			
		}
		if (me->query_temp("qxj/qingxin"))
		{
			message_vision(HIR"$n����������������������������ԣ����Ƽ�������ʱΪ$N���ˣ�����������\n"NOR,me,target);
			target->start_busy(1);

		}
		if (me->query("env/���Ľ�")=="���")
			if (objectp(tweapon)&&(random(me->query_skill("qingxin-jian",1))>target->query_skill("parry",1)/2
			||random(me->query_dex(1))>target->query_dex(1)/2))
		{
						
			message_vision(HIW"$n��û�ϵ�$N��һ���������У�������ת֮�ʣ�����һ�ɣ�"+tweapon->query("name")+"��$N���˹�ȥ��\n"NOR,me,target);
			tweapon->move(environment(target));

		}
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/sword",skill/5);
		me->add_temp("apply/damage",skill/5);
		me->set_temp("qxj/chaofeng",1);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	
		
		if (me->query_temp("qxj/qingxin")&&objectp(me)&&objectp(target)) {
			message_vision(HIC"$N���Ӳ�ͣ����$n���γٻ�����˲�����̶��������������У�һģһ����\n"NOR,me,target);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
		}
		
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/sword",-skill/5);
		me->add_temp("apply/damage",-skill/5);
        me->add("neili", -150);
		me->delete_temp("qxj/chaofeng");

		me->start_perform(3,"�����񳯷");   
	    return 1;
}

string perform_name() {return HIC"��"HIR"��"HIW"��"HIM"��"NOR;}

int help(object me)
{
    write(HIY"\n�������ƽ������񳯷��"NOR"\n");
    write(@HELP
	�������ƽ���Դ����ӯӯ����ѧ���ݻ�����ʽ
	�󶼲ɼ�Ц������ԭ�������ֲ��ɿ�����Ϊ��
	������λ������ǣ��ĺ�������СħŮͬʱ��
	������Ů����ҵ����Լ��ص���ɶ��ɡ�
	���Ľ��˳����书��Ϊ�Ժ󽣷���·��������
	�ν���׼���������ڹ���
	���񳯷���ݻ���ӯӯ��ս��ɽ�������书
	�������У����⿪ӯӯС������ʹ����������
	��������£����ٳ����к��С�
	ע�⣬����������ߣ�����Զ���Ѹ�ݶ��
	Ч������Ӧ��������Ч: set ���Ľ� ���
    
	ָ�perform sword.chaofeng
	
Ҫ��
	�������ƽ��ȼ� 100 �����ϣ�
	���������ȼ� 100 �����ϣ�
	��ǰ����Ҫ�� 250 ���ϣ�
	��ǰ����Ҫ�� 200 ���ϣ�
	��ǰ��Ч�� 30 ���ϣ�
	���������������ƽ���
	�����м��������ƽ���
	���ֳֽ���������    

HELP
	);
	return 1;
}

