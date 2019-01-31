//canqu.c ����
// by sohu
#include <ansi.h>

inherit F_SSERVER;


int lydremove_effect(object target);

string perform_name() {return RED"���Ҳ���"NOR;}

int perform(object me, object target)
{
        int lvl,i;
        object weapon = me->query_temp("weapon");
        lvl =  (int)me->query_skill("lieyan-dao", 1)/4 ;

        if( !target ) target = offensive_target(me);
     
        if( !target || !me->is_fighting(target) )
                return notify_fail("�����Ҳ�����ֻ����ս���жԶ���ʹ�á�\n");

        if (!weapon || weapon->query("skill_type") != "blade"
        || me->query_skill_mapped("blade") != "lieyan-dao")
                return notify_fail("������û�е����޷�ʹ�á����Ҳ�������\n");             

        if( (int)me->query_skill("lieyan-dao",1) < 150 )
                return notify_fail("������浶������죬����ʹ�á����Ҳ�������\n");
      
        if( (int)me->query_skill("blade",1) < 150 )
                return notify_fail("��Ļ��������ȼ�����������ʹ�á����Ҳ�������\n");  

        if( !me->query("quest/mj/lyd/canqu/pass") )
                return notify_fail("�����δ�õ��ܵ�ָ�㣬����ʹ�á����Ҳ�������\n");  

        if( (int)me->query_skill("shenghuo-shengong", 1) < 150 )
                return notify_fail("���ʥ���񹦵ȼ�����������ʹ�á����Ҳ�������\n");

        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("����������̫��������ʹ�á����Ҳ�������\n");
      
        if( (int)me->query("neili") < 400 )
                return notify_fail("��ĵ�ǰ����̫���ˣ��޷�ʹ�ó������Ҳ�������\n");   
        if( (int)me->query("jingli") < 300 )
                return notify_fail("��ĵ�ǰ����̫���ˣ��޷�ʹ�ó������Ҳ�������\n");   
        if( (int)target->query_temp("lyd/canqu"))
                return notify_fail("�Է��Ѿ�Ϊ�㡸���Ҳ������ܵ����ţ�\n");   
                                                                        
        message_vision(HIC"\n$N��Ȼ�������㵸����д��£�����һ�����ӻ���ȡ��һ��"+weapon->query("name")+HIC"�������ϡ�\n"
		+"ͬʱ�е������㲻������ҵĹ��ȣ����ӽ��ո������ˡ���һ�����Լ�����һ������ʱ��Ѫ���죡\n"NOR, me,target);
       // me->add("neili", -(300+random(100))); 
        me->add("jingli", -50);      
      
		me->receive_damage("qi",100+random(100),me);
		if (me->query_per()>20)
		{
			i=me->query_per()-20;
			i=i/2;
		}else i=1;
		if (random(me->query_skill("blade",1))>target->query_parry("parry",1)/2
			||random(me->query_per())>target->query_con()/4)
		{
			message_vision(HIY"$n�ۼ�$N��һ����Ȼ�������ϻ�����ɼ��ǵĵ��ۣ���Ѫ���죬�����ֲ������д󾪣�\n"NOR,me,target);
			target->add_busy(i);
			target->apply_condition("no_exert",i);
			target->apply_condition("jiali",0);
			target->add_temp("apply/attack",-lvl);
			target->add_temp("apply/damage",-lvl);
			target->set_temp("lyd/canqu",lvl);
			
			if (objectp(target))
				call_out("lydremove_effect",lvl/30,target);

		}else {
			message_vision(YEL"$N�ۼ�$n��Ϊ������������Цһ�������ֵݳ����У�\n"NOR,me,target);
			me->set_temp("lyd/canqu",1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			if(random(3)>0 && me->is_fighting(target))
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
			if(random(3)>1 && me->is_fighting(target))
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
			me->delete_temp("lyd/canqu");
			me->add_busy(1);
			me->start_perform(3 , "�����Ҳ�����");
        }
		return 1;
}

int lydremove_effect(object target)
{
	int lvl;
	if (!target) return 1;
	lvl=target->query_temp("lieyandao/canqu");
	
		message_vision(HIC"$N������һ�������������ڰ����˷��ŵľ��֣�\n"NOR,target);
		target->delete_temp("lieyandao/canqu");
		target->add_temp("apply/attack",lvl);
		target->add_temp("apply/damage",lvl);
		return 1;
	

}


int help(object me)
{
        write(HIC"\n���浶��"+HIR"�����Ҳ�����"NOR"\n");
        write(@HELP
	���浶�����������ż����书��Դ����ң�����з����Ĵ���
	����ʹ�书��Ϊ���ӣ��������ݶ���������ڲ�����Ϊ����
	�ݺ����̵Ķ�ͷ�����ư�ͷ�ӵ�����ʾ�����⣬ʵ�����̵�
	�󹦳���
	�����һ𣬷��Ҳ����Ǵ�����̵Ľ�ּ������ȡ���ܵ�����
	���´�ս���Ե����Լ�������Ӱ��Է�����ʽ���öԷ�����
	����ɱ�������ܵ�����Ӱ�첢ͬʱ����һ���ľ���æ�ҡ���
	�����л�����������й�����
	���е����к���ò��أ���òԽ�ߴ����ľ���Ч��Խǿ����
	���ܵ���̷�����ϰ��
	
	ָ�perform blade.canqu

Ҫ��
	�������Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 400 ���ϣ�
	��ǰ����Ҫ�� 300 ���ϣ�
	���浶���ȼ� 150 ���ϣ�
	Ʈ�������ȼ� 150 ���ϣ�
	ʥ���񹦵ȼ� 150 ���ϣ�
	��������Ϊ���浶����
	�ֳֵ���������

HELP
        );
        return 1;
}