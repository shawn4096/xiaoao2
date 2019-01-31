//˫�����
//hebi.c �μ�����������
//by sohu@xojh

#include <ansi.h>


int check_fight(object me, object target, int amount);
private int remove_effect(object me, object target, int amount);

int perform(object me, object target)
{
        object *enemy;
        int i,j,k,amount;
        object wep1, wep2;
		wep1 = me->query_temp("weapon");

        if( !target || target == me) return notify_fail("��Ҫ��˭��赣�\n");

        if (me->query_temp("flyd/hebi")) return notify_fail("���Ѿ��ں���ˡ�\n");
        if (target->query_temp("flyd/hebi")) return notify_fail("�Է��Ѿ��ں���ˡ�\n");
        if (me->query("jingli") < 200) return notify_fail("��ľ��������ˡ�\n");
        if (target->query("jingli") < 200) return notify_fail("�Է��ľ��������ˡ�\n");
        if (!me->is_fighting()) return notify_fail("���ֻ����ս����ʹ�á�\n");
        if (me->is_fighting(target)) return notify_fail("�����ںͶԷ���ܣ���赸�ʲô��\n");
        if (me->query_skill("qimen-bagua",1)<200) return notify_fail("������׾�������δ����Բ���������ʩչ�ⷴ���ǵ�����\n");
        if (target->query_skill("qimen-bagua",1)<200) return notify_fail("�Է������׾�������δ����Բ���������ʩչ�ⷴ���ǵ�����\n");
		
		if (!me->query("quest/hs/flyd/hebi/pass"))
			return notify_fail("����δ�����ⷴ���ǵ��İ��壬�����ʩչ�ⷴ���ǵ�����\n");
		if (!target->query("quest/hs/flyd/hebi/pass"))
			return notify_fail("�Է���δ�����ⷴ���ǵ��İ��壬�����ʩչ�ⷴ���ǵ�����\n");

        if( (int)me->query_skill("fanliangyi-dao", 1) < 450 )
                return notify_fail("��ķ����ǵ�������450������δ��죬����ʹ�ú�赡�\n");
        if( (int)me->query_skill("zixia-gong", 1) < 450 )
			if( (int)me->query_skill("huashan-qigong", 1) < 450 )
                return notify_fail("��Ļ�ɽ�ڹ�δ�������λ��к�赵�������\n");
        if (!wep1 || wep1->query("skill_type") != "blade"
			|| me->query_skill_mapped("parry") != "fanliangyi-dao"
			|| me->query_skill_mapped("blade") != "fanliangyi-dao")
                return notify_fail("�����ڼ����������мܲ��ԣ��޷�˫����赡�\n");
        
        enemy = me->query_enemy();
        i = sizeof(enemy);
        
		while (i--) if (target->is_fighting(enemy[i])) break;
        
		if (i<0) return notify_fail(target->name()+"��û�к���Ķ����ڽ�ս��\n");

        if( (int)target->query_skill("fanliangyi-dao", 1) < 450 )
                return notify_fail("�Է��ķ����ǵ���������죬����ʹ�ú�赡�\n");
        if( (int)me->query_skill("zixia-gong", 1) < 450 )
			if( (int)me->query_skill("huashan-qigong", 1) < 450 )
                return notify_fail("�Է��Ļ�ɽ�ڹ�δ�������λ��к�赵�������\n");

        wep2 = target->query_temp("weapon");
        if (target->is_busy() || !wep2 || wep2->query("skill_type") != "blade"
			|| target->query_skill_mapped("parry") != "fanliangyi-dao"
			|| target->query_skill_mapped("blade") != "fanliangyi-dao")
                return notify_fail("�Է������޷���赡�\n");
        
		message_vision(HIY "\n$N��$nʹ�˸���ɫ������ǰ��бб����һС����\n" NOR, me, target);
		message_vision(HIG "\n$n΢΢��ͷ������ǰ��бб��������һС����\n" NOR, me, target);

        message_vision(HIR "\n$N��$n���ó��ַ����ǵķ�λ�����˺�Ȼ˫��һ��,��ʽ��ʱ�㹥���أ����ؼ汸�������ǵ�����������\n" NOR, me, target);
        
		me->set_temp("flyd/hebi", target->query("id"));
        target->set_temp("flyd/hebi", me->query("id"));
        
		me->receive_damage("jingli", 100);
        target->receive_damage("jingli", 100);
        me->receive_damage("neili", 200);
        target->receive_damage("neili", 200);
        
		k = (int)me->query_skill("fanliangyi-dao", 1);
        j = (int)target->query_skill("fanliangyi-dao", 1);
        amount = (k + j)/10;
        
		me->add_temp("apply/dexerity", amount);
        me->add_temp("apply/strength", amount);
		me->add_temp("apply/dodge", amount);
        me->add_temp("apply/armor", amount);
        me->add_temp("apply/blade", amount);
        me->add_temp("apply/parry", amount);
        me->add_temp("apply/damage", amount);
		
        target->add_temp("apply/dexerity", amount);
        target->add_temp("apply/strength", amount);
        target->add_temp("apply/dodge", amount);
        target->add_temp("apply/armor", amount);
        target->add_temp("apply/blade", amount);
        target->add_temp("apply/parry", amount);
        target->add_temp("apply/damage", amount);

		check_fight(me, target, amount);
        return 1;
}

int check_fight(object me, object target, int amount)
{  
    object wep1, wep2;
    //����һ���뿪���飬���ɢ����
	if(!me || !target) return remove_effect(me, target, amount);
    
	wep1 = me->query_temp("weapon");
    wep2 = target->query_temp("weapon");
    
	if(!me->is_fighting() 
		|| !living(me) 
		|| me->is_ghost() 
		|| !wep1 
		|| !target->is_fighting() 
		|| !living(target) 
		|| environment(me)!=environment(target)
		|| target->is_ghost() 
		|| !wep2)
			remove_effect(me, target, amount);
    else {
        call_out("check_fight", 1, me, target, amount);
    }
    return 1;
}
//�뿪�󷨻�ʧЧ�ж�
private int remove_effect(object me, object target, int amount)
{
	
	
	if(me && target && living(me) && !me->is_ghost() && living(target) && !target->is_ghost())
        message_vision(HIY "\n$N��$nһ·�����ǵ���������꣬����һ����������һЦ���������С�\n" NOR, me, target);

	
	if (me) {
		me->add_temp("apply/dexerity", amount);
        me->add_temp("apply/strength", amount);
		me->add_temp("apply/dodge", amount);
        me->add_temp("apply/armor", amount);
        me->add_temp("apply/blade", amount);
        me->add_temp("apply/parry", amount);
        me->add_temp("apply/damage", amount);
		me->delete_temp("hebi");
	}
	if (target) {
        target->add_temp("apply/dexerity", amount);
        target->add_temp("apply/strength", amount);
        target->add_temp("apply/dodge", amount);
        target->add_temp("apply/armor", amount);
        target->add_temp("apply/blade", amount);
        target->add_temp("apply/parry", amount);
        target->add_temp("apply/damage", amount);

		target->delete_temp("hebi");
	}
	return 0;
}

string perform_name(){ return HIC"˫�����"NOR; }
int help(object me)
{
        write(HIC"\n�����ǵ�֮��˫����赡���"NOR"\n");
        write(@HELP
	���׵����Ĳ��������롸�����ɡ��ġ������ǽ�����һ����
	������������б仯���������а˰���ʮ�İ�仯������
	��ɽ�߰��������ڹ�����һս�����˷�֪���ⷴ���ǵ�Ҳ
	���˲��õľ�ѧ��
	˫���������������ɷ����ǵ��ĵ�����������������
	������λ������̡�

	ָ�perform blade.hebi

Ҫ��
	��ɽ��������ϼ�����ĵȼ� 450  ���ϣ�
	�����ǵ��ĵȼ� 450  ���ϣ�
	���������ĵȼ� 450  ���ϣ�
	���Ű��Եĵȼ� 200  ����
	��ǰ������Ҫ�� 1000  ���ϣ�
	��ǰ������Ҫ�� 1000  ���ϣ�
	��������Ϊ�����ǵ���
	�����м�Ϊ�����ǵ���
	�����ڹ����ޣ�
	�ֳֵ��ҶԷ�������ͬ��
HELP
        );
        return 1;
}
