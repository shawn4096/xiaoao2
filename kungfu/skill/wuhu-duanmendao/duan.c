#include <ansi.h>
inherit F_SSERVER;
string perform_name() {return CYN"���־�"NOR;}

int perform(object me, object target)
{
    int lvl;
	object weapon;
    
	lvl = me->query_skill("wuhu-duanmendao", 1);
    
	if( !target ) target = offensive_target(me);
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))                
        return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�ö��־���\n");
    if( (int)me->query_skill("wuhu-duanmendao", 1) < 220 )
        return notify_fail("����廢���ŵ�������죬�޷�ʩչ�����־���\n");
    if (!objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "blade") 
                return notify_fail("�������޵������ʹ�������־�����\n");
    if (me->query_skill_mapped("blade") != "wuhu-duanmendao")
        // || me->query_skill_mapped("parry") != "wuhu-duanmendao")
         return notify_fail("�������޷�ʹ�á����־�����\n");  
    if ( (int)me->query("max_neili") < 3000)
        return notify_fail("��������������޷�ʩչ�����־���\n");
    if ( (int)me->query("neili") < 1000)
        return notify_fail("��������������޷�ʩչ�����־���\n");
    if ((int)me->query("jingli") < 1000)
        return notify_fail("��ľ����������޷�ʩչ�����־���\n");
     message_vision(HIY"$N��Ȼ���أ�ʹ���廢���ŵ�"NOR+HIR"���ϡ�"NOR+HIY"�־�������һƬ�׹�ֱ��$n��ȥ��\n"NOR,me, target);
    me->add("neili", -(300 +random(100)) );
    me->add("jingli", -150);
   
    //busy_time = me->query_skill("wuhu-duanmendao", 1) / 50;
    
    me->add_temp("apply/attack",lvl/2);
    me->add_temp("apply/strength",lvl/20);
    me->add_temp("apply/damage",lvl/5);
    
	if (userp(target)) target->start_busy(1+random(3));
	else target->start_busy(4);
    
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    
	if (!me->query("family")&&me->is_fighting(target)&&lvl>449&&userp(me))
    {
		message_vision(RED"$N���������ƽ��������ս���۵ľ����Ȼ��ͨ����Ȼʹ��һ���廢���ŵ��ľ�����"NOR,me,target);
        me->add_temp("apply/attack",lvl/2);
		me->add_temp("apply/damage",lvl/5);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?3:1);
        me->add_temp("apply/attack",-lvl/2);
		me->add_temp("apply/damage",-lvl/5);
    }
    me->start_busy(random(2) + 1);
    me->add_temp("apply/attack",-lvl/2);
    me->add_temp("apply/strength",-lvl/20);
    me->add_temp("apply/damage",-lvl/5);

	me->start_perform(4,"�����־���");
    return 1; 
}

int help(object me)
{
        write(HIC"\n�廢���ŵ�֮"HIY"�����־�����"NOR"\n\n");
        write(@HELP
	�廢���ŵ�Ϊ�����ؼ�կ��ѧ������ʮ��ǰ������һ��կ���ع����Դ���
	ȫ�׵�������������ʮ���У������ؼҺ������ˡ��׻�����������һХ������
	���������硱�����۰�Ⱥɽ����������ʤʨ�����У�ֻ����ʮ����������������
	�������ؼ�կ���ε���Ҧ������ʦ����һ��ʱ�����С����Ӷɺӡ��͡��ؽ�
	���塱����ʧ����ֻʣ����ʮ���С�Ҧ����Ϊ��ȫ���棬�������Ӷɺӡ���
	���ؽ����塱���������ԼӸĶ�����������ʮ����֮���������Դ��ŵ�����
	���������˾���ֽ���ʱ�Ա������̿��ơ�
	���廢���Ű���ʹ�ã���ɺ���ٳ�һ�У��������ɺ�NPC��Ч��
	
	ָ�perform blade.duan

 Ҫ��
	��ǰ���� 1000 ���ϣ�
	������� 3000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	�廢���ŵ��ȼ� 220 ���ϣ�
	����������ȼ� 220 ���ϣ�
	�����м�Ϊ�廢���ŵ���
                

HELP
        );
        return 1;
}

