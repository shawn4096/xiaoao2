//zixu.c ����ٶ�
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIC"����ٶ�"NOR;}

int perform(object me, object target)
{
		object weapon;
        int i; 
		i=(int)me->query_skill("canglang-goufa",1)/100;
        if( !target ) target = offensive_target(me);
		weapon=me->query_temp("weapon");

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("������ٶ���ֻ����ս��ʱʹ�ã�\n");

		if (me->query_skill_prepared("strike") != "huagu-mianzhang"
            || me->query_skill_mapped("strike") != "huagu-mianzhang"
			|| me->query_skill_mapped("hook") != "canglang-goufa"
			|| me->query_skill_mapped("parry") != "canglang-goufa" )
                return notify_fail("�������޷�ʹ�á�����ٶ������й�����\n");  

		 if( !weapon || weapon->query("skill_type")!="hook") 		  
                return notify_fail("��������Ź������á�����ٶ�����\n");     
    

		if( (int)me->query_skill("huagu-mianzhang", 1) < 350 )
                return notify_fail("��Ļ������ƻ���������������ʹ�á�����ٶ�����\n");
     
        if( (int)me->query_skill("canglang-goufa", 1) < 350 )
                return notify_fail("��Ĳ��˹�������������������ʹ�á�����ٶ�����\n");
        
        if( (int)me->query_skill("dulong-dafa", 1) < 350 )
                return notify_fail("��Ķ����󷨹������㣬�����á�����ٶ�����\n");
      
        if( (int)me->query_skill("hook", 1) < 350 )
                return notify_fail("��Ļ�����������������������ʹ�á�����ٶ�����\n");

        if((int)me->query("max_neili") < 5000) 
                return notify_fail("������������Ϊ�еͣ�����ʹ�á�����ٶ�����\n"); 

        if((int)me->query("jingli") < 1000) 
                return notify_fail("�����ھ�����Ϊ���㣬����ʹ�á�����ٶ�����\n"); 

        if((int)me->query("max_jingli") < 2500)
                return notify_fail("��������������㣬����ʹ�á�����ٶ�����\n");       

        if((int)me->query("neili") < 1000) 
                return notify_fail("�����ڵ�ǰ�������㣬����ʹ�á�����ٶ�����\n");  

	    if( target->is_busy() )
		        return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if( (int)me->query_str() < 70  )
                return notify_fail("�������̫�ͣ�����ʹ�á�����ٶ�����\n");

		me->add("jingli",-100);
        me->add("neili",-200);

		message_vision(HIC"$N˫�Ŷ��ֲ�վ�ã���"+weapon->query("name")+HIC"�������֣�ֱ��$n����,Ȼ�����ֵ���������$n���һ����\n"+
			"��Ȼʹ��������洫����"+HIR+"������ٶ���"+HIC+"������˳����ס$n����֫����ͼ��$n��������\n"NOR,me,target);
		if (random(me->query("combat_exp"))>target->query("combat_exp")/2
			||random(me->query_str())>target->query_dex()/2)
		{
			message_vision(HIR"$N����ͻȻ����Ϊץ�����䲻��ץ��$n���󡾴�׵Ѩ����$NҪѨ����ȫ������������ɢ��\n"NOR,me,target);
			message_vision(HIR"$N�첽��ǰ�Ҽ�˳��һ������Ȼ������$n����������$n���д󺧶�ʱ��æ���ҡ�\n"NOR,me,target);
			
			if (userp(target))
			{
				if (random(2))
					target->apply_condition("no_perform",1);
				target->start_busy(2);
			}
			else {
				if (random(2))
					target->apply_condition("no_perform",3);
				target->start_busy(i);
			}

		}else {					
			message_vision(HIW"$n�������ǣ���ͷ���磬�����ܹ������С�\n"NOR,me,target);
			me->start_busy(1);							
		}
		me->add("neili",-random(300));
		me->add("jingli",-random(100));
		
        return 1;

}
int help(object me)
{
   write(WHT"\n���˹�����"HIC"����ٶ�"+WHT"����\n");
   write(@HELP
	���˹�������������������������Լ�����ѧ�似
	��������������һ�׹����似��ȥ���ͼ򣬹���Ϭ
	��������ʤ����������ڱ����ϴ��е��Ӷ��ԣ���
	�Ƿǳ�ʵս�Ĺ�����������ٶ����ǵ��͵�����
	�似�������Լ��ߵı����ͷḻ��ս�����飬����
	������������ʽ��
	
	perform hook.zixu

Ҫ��
	�������Ҫ�� 5000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�������Ƶȼ� 350 ���ϣ�
	�����Ʒ��ȼ� 350 ���ϣ�
	���˹����ȼ� 350 ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	��Ч����Ҫ�� 70  ���ϣ�
	�����ұ��Ʒ�Ϊ�������ƣ�
	��������Ϊ���˹�����
	�����м�Ϊ���˹�����
	װ������������

HELP
   );
   return 1;
}