//kunlun-zhang
//luoyan ����������
// By sohu

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
#include <combat.h> 

string perform_name() { return HIG"������"NOR; }


int perform(object me, object target)
{
        int damage,skill;

        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("���������ƾ���ֻ����ս����ʹ�á�\n");       
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("�ȷ������е�������˵�ɣ�\n");
        if((int)me->query_skill("strike", 1) < 250 )
                return notify_fail("��Ļ����Ʒ�̫�ͣ��޷�ʹ��������֮���������ơ�\n");  
        if((int)me->query_skill("kunlun-zhang", 1) < 250 )
                return notify_fail("��������ƻ�������죬����ʹ��������֮���������ơ�\n");
        if (me->query_skill_prepared("strike") != "kunlun-zhang"
           || me->query_skill_mapped("strike") != "kunlun-zhang")
                return notify_fail("�㲻ʹ�������ƣ�������ʹ�û�ȭΪ�ƣ�\n");   
        if( (int)me->query("max_neili", 1) < 2500 )
                return notify_fail("��������Ϊ̫ǳ���޷��˾��˵У�\n");                
        if( (int)me->query("neili", 1) < 1500 )
                return notify_fail("�������������������������������Ƶľ�����\n");
        if(userp(me) && (int)me->query_skill("xuantian-wuji", 1) < 250 )
                return notify_fail("��������޼����ȼ�����������Ӧ�����������Ƶľ�����\n");
        if(userp(me) && me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("����ڹ��ķ����ԣ����Ӳ������������ƾ���֮����\n"); 
        if( me->query_str(1) < 50 )
                return notify_fail("��ĺ����������50���޷�ʹ�����ص���֮�����ơ�\n");  

		if(me->query_temp("klz/luoyan"))
                return notify_fail("����ʱ����ʹ��"HIG"�����������ơ�"NOR"���ˡ�\n");   
                                                                               
        damage=(int)me->query_skill("kunlun-zhang")+(int)me->query_skill("dodge")+(int)me->query_skill("force");
		damage=damage*2+random(damage);
		if (damage>4000) damage=4000+random(1000);
        
		skill=(int)me->query_skill("kunlun-zhang",1);
		
		if (me->query("gender")=="����")
		{
			skill=skill+me->query_skill("xuantian-wuji",1)/6;
		}else
			skill=skill/3;

		me->add_temp("apply/damage", skill/5);
        me->add_temp("apply/attack",skill/4);
        me->add("neili", -200);
		me->add("jingli",-150);
        message_vision(HIY"$N�������ʩչ"HIG"�����������ơ�"HIY"���λζ���˲���������У�Ѹ�����磬���籼�ף�����һƬ��ӡ��\n"NOR,me, target);
		me->set_temp("klz/luoyan",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if (random(me->query_dex())>target->query_dex()/2
			||random(me->query_skill("strike",1))>target->query_skill("parry",1)/2)
		{
			message_vision(HIC"$N��������̤ѩ�޺۵��Ṧ���Ӽ��£�����һƬ��Ӱ����ž����һ������$n������֮�ϣ�\n$n������Щѣ�λ�㱣�\n"NOR,me, target);
			
			target->add_busy(1);
			target->apply_condition("no_exert",1);
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/3,me);

		}

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
		me->add_temp("apply/damage", -skill/5);
        me->add_temp("apply/attack",-skill/4);
		me->delete_temp("klz/luoyan");
        me->start_perform(4, "����������");
		return 1; 
}

int help(object me)
{
	write(WHT"\n������֮��"HIG"������"WHT"����"NOR"\n");
	write(@HELP
	������֮������ʽԴ��¹���ǳ��Ĵ�ʦ
	���������ɵ��·���ʽ�������ƺ�����
	ǧҶ�֣��䵱�ɻط��ƣ�����ɷɷ���
	������ͬ��֮���Ҫ����ʽ�����ޱ�
	��������ɶ��ص������ƣ�ȡ�����
	��Ҫ����Ѹ�ٳ��У����˷���ʤ����
	ע�⣺������������ǿ��Ů�ԡ�
	
	ָ�perform strike.luoyan
	
Ҫ��
	��ǰ���� 1500 ���ϣ�
	������� 2500 ���ϡ�
	�����Ʒ� 250  ���ϡ�
	�����Ʒ� 250  ���ϡ�
	�����޼� 250  ���ϡ�
	������� 50   ���ϣ�
	�����Ʒ�Ϊ�����ƣ�
	�����м�Ϊ�����ƣ�
	�����ڹ������޼�����
	�����ұ��Ʒ�Ϊ������

HELP
	);
	return 1;
}
