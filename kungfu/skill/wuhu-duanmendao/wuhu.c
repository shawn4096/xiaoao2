
//wuhu.c  �����������
//cre by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
string perform_name() {return HBRED+HIY"�廢����"NOR;}


int perform(object me, object target)
{
    int lvl;
	object weapon,tweapon;

    lvl = me->query_skill("wuhu-duanmendao", 1);
    
	if( !target ) target = offensive_target(me);
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))                
        return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ���廢������\n");
    
	if( (int)me->query_skill("wuhu-duanmendao", 1) < 350 )
        return notify_fail("����廢���ŵ�������죬�޷�ʩչ���廢������\n");
    if (!objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "blade") 
                return notify_fail("�������޵������ʹ�����廢��������\n");
    tweapon=target->query_temp("weapon");
	if (me->query_skill_mapped("blade") != "wuhu-duanmendao")
        // || me->query_skill_mapped("parry") != "wuhu-duanmendao")
         return notify_fail("�������޷�ʹ�á��廢��������\n");  

    if ( (int)me->query("max_neili") < 5000)
        return notify_fail("��������������޷�ʩչ���廢������\n");
    if ( (int)me->query("neili") < 1000)
        return notify_fail("��������������޷�ʩչ���廢������\n");
    if ((int)me->query("jingli") < 1000)
        return notify_fail("��ľ����������޷�ʩչ���廢������\n");
    if (!me->query("quest/whdmd/wuhu/pass"))
        return notify_fail("����δ�������о�����������������̣�����ʩչ���廢������\n");

    me->add("neili", -(300 +random(100)) );
    me->add("jingli", -150);
    
    
    me->add_temp("apply/attack",lvl/5);
  //  me->add_temp("apply/strength",lvl/20);
	me->add_temp("apply/damage",lvl/5);
	me->add_temp("apply/blade",lvl/4);
	
	message_vision(HIR"$Nʩչ�廢���ŵ��ռ����������׻���������һХ���������������硹���۰�Ⱥɽ��������ʤʨ����������\n"
						+"�����е�������ʧ���ľ�ѧ�������ڻ��ͨ�󣬶��ŵ���������Ȼ������\n"NOR,me,target);
	
	me->set_temp("whdmd/wuhu",4);
	if (objectp(target)&&me->is_fighting())
    {
		target->receive_damage("qi",1000,me);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->add_temp("whdmd/wuhu",-1);
    }
	if (objectp(target)&&me->is_fighting())
    {
		//target->receive_damage("jingli",1000,me);
		target->add_busy(2);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("whdmd/wuhu",-1);
    }
	if (objectp(target)&&me->is_fighting())
    {
		//target->receive_damage("qi",2000,me);
		
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("whdmd/wuhu",-1);
    }
	if (objectp(target)&&me->is_fighting()&& lvl>400)
    {
		//target->receive_damage("jingli",2000,me);
		//target->apply_condition("no_exert",1);
		
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		message_vision(CYN"$N���С�"HIR"�۰�Ⱥɽ"CYN"��ʩչ���������ƶ�Ȼ��ʢ��\n"NOR,me,target);
		me->add_temp("whdmd/wuhu",-1);
    }
	if (objectp(target)&&me->is_fighting()&& lvl>450)
    {
		//target->receive_damage("jingli",1000,me);
		//target->apply_condition("no_perform",1);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("whdmd/wuhu",-1);
    }
	me->add_temp("apply/attack",-lvl/5);
    //me->add_temp("apply/strength",-lvl/20);
	me->add_temp("apply/damage",-lvl/5);
	me->add_temp("apply/blade",-lvl/4);

	me->start_busy(2);
	me->start_perform(5,"���廢������");
    return 1;
}

int help(object me)
{
        write(HIC"\n�廢���ŵ�֮"HIY"���廢��������"NOR"\n\n");
        write(@HELP
	�廢���ŵ�Ϊ�����ؼ�կ��ѧ������ʮ��ǰ������һ��կ���ع����Դ���
	ȫ�׵�������������ʮ���У������ؼҺ������ˡ��׻�����������һХ������
	���������硱�����۰�Ⱥɽ����������ʤʨ�����У�ֻ����ʮ����������������
	�������ؼ�կ���ε���Ҧ������ʦ����һ��ʱ�����С����Ӷɺӡ��͡��ؽ�
	���塱����ʧ����ֻʣ����ʮ���С�Ҧ����Ϊ��ȫ���棬�������Ӷɺӡ���
	���ؽ����塱���������ԼӸĶ�����������ʮ����֮���������Դ��ŵ�����
	���������˾���ֽ���ʱ�Ա������̿��ơ�
	ע�⣺����������������̷���ϰ��,400,450������ʽ��ȫ��
	
	ָ�perform blade.wuhu

 Ҫ��
	��ǰ���� 1000 ���ϣ�
	������� 5000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	�廢���ŵ��ȼ� 350 ���ϣ�
	����������ȼ� 350 ���ϣ�
	�����м�Ϊ�廢���ŵ���
                

HELP
        );
        return 1;
}

