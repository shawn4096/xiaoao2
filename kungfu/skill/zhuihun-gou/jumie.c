//�ı���snowman��sanhuan
//�ı���:caiji
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int i = me->query_skill("zhuihun-gou", 1)/5;
        int j = me->query("jiali")/4 + 10;
        
        if( !target ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("�����ξ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if(me->query_temp("zhuihun/lpf"))
        return notify_fail("������ʹ�á������硹��\n");
		if(me->query("xx/zhg/pass"))
           return notify_fail("����Ȼ��˵����׷�깳���������Ӳ�û��ѧ�ᡣ\n");
        if( (int)me->query_skill("zhuihun-gou", 1) < 200 )
                return notify_fail("���׷�깳����̫ǳ���������ˡ�\n");

        if( (int)me->query_skill("hook", 1) < 200 )
                return notify_fail("��Ļ�����������̫ǳ���������ˡ�\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 200 )
                return notify_fail("����ڹ�����̫ǳ���������ˡ�\n");
                
        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("�������̫ǳ���������ˡ�\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("��������������������ˡ�\n");
        if (me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("����ʲôΪ�ڹ�������ʹ�����ξ���?\n");
        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "hook"
            || me->query_skill_mapped("hook") != "zhuihun-gou")
                return notify_fail("��ʹ���ˡ����ξ���ô?\n");
                 
        me->add("neili", -150);
        me->add("jingli", -100);
        me->set_temp("zhuihun/jumie", 4); 
        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", j);
        message_vision(GRN "\n$N���һ��������������������$n��࣬��Ȼ����$N����ʽ�˺���һ�еݳ�.\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        if(me->is_fighting(target)){
        message_vision(YEL "\n$N������������ɥ�ӣ�����һ����˫�����٣������ŷ����ڶ��С����ǡ���\n"NOR,me);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        }
        if(me->is_fighting(target)&&(int)me->query_skill("zhuihun-gou", 1) >= 140){
        message_vision(RED "\n$N˫�ֻ�����������һ��������ʽ����꡹����������$n"RED"���ֲ�����\n"NOR,me,target);
        me->add("neili", -50);
		target->add_busy(1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);        
        }
        if(me->is_fighting(target)&&random(me->query("combat_exp"))>target->query("combat_exp")/2
        && (int)me->query_skill("zhuihun-gou", 1) >= 180){
        message_vision(MAG "\n$N���лζ������һʽ�����项���������ǳ���\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);   
        me->add("neili", -80);
        }
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/damage", -j);   
        me->start_busy(1);
        me->delete_temp("zhuihun/jumie"); 
        me->start_perform(4, "�����ξ���");
        return 1;
}

string perform_name(){ return HIG"���ξ���"NOR; }

int help(object me)
{
        write(HIM"\n׷�깳��֮�����ξ��𡹣�"NOR"\n");
        write(@HELP
	׷�깳���������ɵĲ���֮�أ���׷�����֮��
	����������ɶ����书�����󷨣�����书����
	�ա������ص�ͷ������뾡�¡�
	���ξ����ǲ�Ҫ���Ĵ򷨣�����ժ�ǹ��������
	�ƣ�˲������У����кݶ�������
		
	ָ�perform hook.jumie
		
Ҫ��
	�������Ҫ�� 1000 ���ϣ�      
	��ǰ����Ҫ�� 500 ���ϣ�
	�����󷨵ȼ� 200 ���ϣ�
	׷�깳���ȼ� 200 ���ϣ�
	���������ȼ� 200 ���ϣ�
	�����������м�Ϊ׷�깳����
	�����ڹ�Ϊ�����󷨣�
	�ֳֹ��������
	            
                
HELP
        );
        return 1;
}
